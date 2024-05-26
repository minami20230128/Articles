//・依存性の注入
//クラスAがクラスBのインスタンスを保持している状態を「依存」という。
//（クラス図の書き方.mdも参照）
//クラスAの中でクラスBのインスタンスを作成していると、AがBの動作の影響を受けやすく、テストがしにくい。
//そこで、クラスAの外でBのインスタンスを作って渡すようにする。

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

//上記のコードでは、CartクラスがUserRepositryクラスのインスタンスを保持しているので、CartクラスがUserRepositryクラスに依存していると言える。
//このとき、CheckValidCart()がCheckavailableUserForPurchase()の結果に左右される。
//CheckAvailablePurchase()はDBに接続する処理があるため、DBの状態、種類によって動きが安定しない場合がある。
//すると、CheckValidCart()のロジックに問題がないにも関わらずDBのせいで不具合が発生する場合があり、問題の切り分けが難しい。
//そこで、「依存性の注入」の出番である。

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

public class UserRepositoryDb implements IUserRepository
{
    public bool CheckAvailableUserForPurchase(string userId)
    {
        //DBの会員情報にアクセスして有効かを判定するコードを記述
    }
}

public class UserRepositoryMock implements IUserRepository
{
    public bool CheckAvailableUserForPurchase(string userId)
    {
        // テスト用のデータを返すようにする
    }
}

//UserRepositryクラスをインターフェース化し、テスト用に使うUserRepositoryMockと、本番で使うUserRepositoryDbに分けた。
//こうすることで、Cartクラスの動作とその他の要因を切り離すことが可能。