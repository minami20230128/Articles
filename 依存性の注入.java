・依存性の注入
あるクラスが別のクラスのインスタンスを保持している状態を「依存」という。
（クラス図の書き方.mdも参照）
このとき、依存している側のクラスの動作がもう一方の実装に影響を受けやすく、テストがしにくい。

public class Cart
{
    private string userId;
    public Cart(string userId)
    {
        this.userId = userId;
    }

    public bool CheckValidCart()
    {
        var userRepository = new UserRepository();
        var isAvailableUser = userRepository.CheckAvailableUserForPurchase(this.userId);

        return isAvaliable;
    }
}

public class UserRepository
{
    public bool CheckAvailableUserForPurchase(string userId)
    {
        ///DBの会員情報にアクセスして有効かを判定するコードを記述
    }
}

上記のコードでは、CartクラスがUserRepositryクラスのインスタンスを保持しているので、CartクラスがUserRepositryクラスに依存していると言える。
このとき、CheckValidCart()がCheckavailableUserForPurchase()の結果に左右される。
CheckAvailablePurchase()はDBに接続する処理があるため、DBの状態、種類によって動きが安定しない場合がある。
すると、CheckValidCart()のロジックに問題がないにも関わらずDBのせいで不具合が発生する場合があり、問題の切り分けが難しい。
そこで、「依存性の注入」の出番である。

public class Cart
{
    private string userId;
    private IUserRepository userRepository;

    public Cart(string userId, IUserRepository userRepository)
    {
        this.userId = userId;
        this.userRepository = userRepository;
    }

    public bool CheckValidCart()
    {
        var isAvailableUser = this.userRepository.CheckAvailableUserForPurchase(this.userId);

        return isAvaliable;
    }
}

public interface IUserRepository
{
    bool CheckAvailableUserForPurchase(string userId);
}

public class UserRepositoryDb : IUserRepository
{
    public bool CheckAvailableUserForPurchase(string userId)
    {
        //DBの会員情報にアクセスして有効かを判定するコードを記述
    }
}

public class UserRepositoryMock : IUserRepository
{
    public bool CheckAvailableUserForPurchase(string userId)
    {
        // テスト用のデータを返すようにする
    }
}

UserRepositryクラスを