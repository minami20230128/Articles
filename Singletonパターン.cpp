//・Singletonパターン
//クラスのインスタンスが常に１つしか存在できないようにする
//DBの設定など、システム全体で使うインスタンスが上書きされないようにする


#include <libpq-fe.h>
#include <pqxx/pqxx>
#include <string>
#include <iostream>

class DataBase
{
    private:
    static DataBase* instance;
    pqxx::read_transaction work;
    DataBase()
    {
        auto connection = new pqxx::connection{"postgresql:///shop?host=localhost&port=/*5432*/&user=/*hirataminami*/"};
        this->work = new pqxx::read_transaction(*connection);
    }

    public:
    static DataBase* get_instance()
    {
        if(DataBase::instance == nullptr)
        {
            DataBase::instance = new DataBase();
        }

        return DataBase::instance;
    }

    void execute_query(std::string query)
    {
        try
        {
           this->work.exec(query);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}

int main()
{
    DataBase* db = DataBase::get_instance():
    db.execute_query("select * from 'public'.employee;");
    
    return 0;
}
