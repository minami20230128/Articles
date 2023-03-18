//・例外クラスについて
//アプリ内で共通の例外処理を作りたい場合、例外クラスを自作する場合がある

#include <exception>
#include <string>

class myException : std::exception
{
    public:
        myException(const string &msg)
        {
            this->message = msg;
        }

        const char* what() const noexcept
        {
            return this->message.c_str();
        }
    
    private:
        std::string message;

};

int main()
{
    try
    {
        throw myException("aaa");
    }
    catch(const myException& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}