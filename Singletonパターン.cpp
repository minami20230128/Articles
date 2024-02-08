//・Singletonパターン
//クラスのインスタンスが常に１つしか存在できないようにする
//DBの設定など、システム全体で使うインスタンスが上書きされないようにする


#include <libpq-fe.h>
#include <pqxx/pqxx>
#include <string>

class DataBase
{
    private:
    static DataBase instance;
    pqxx::work work;
    DataBase()
    {
        auto connection = pqxx::connection connection{"postgresql:///shop?host=localhost&port=/*5432*/&user=/*hirataminami*/"};
        this->work = pqxx::work work(connection);
    }

    public:
    static DataBase get_instance()
    {
        if(this->instance == null)
        {
            this->instance = new DataBase();
        }

        return this->instance;
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
    DataBase db = DataBase.get_instance():
    db.execute_query("select * from 'public'.employee;");
    
    return 0;
}
