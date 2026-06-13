//・Factoryパターンとは
//抽象クラスでインスタンスの作り方を定義し、具象クラスで具体的な処理内容を決めるパターン
//長所：具象クラスへの依存度を減らせる

//例えば、
//Stationeryクラスを継承したScissorクラス、Pencilクラス、Eraserクラスがあったとする
//通常各クラスにアクセスするには、

//auto scissor = Scissor::Scissor();

//のようにコンストラクタを使用すれば良い。

//しかし、

//if(...) auto stationery = Scissor::Scissor();
//else if(///) auto stationery = Pencil::Pencil();
//else if(###) auto stationery = Eraser::Eraser();

//のように、場合によってどのクラスのインスタンスを作るか変わる場合、
//例えば新たにStationeryクラスを実装するTapeクラスができるとif文を書き足さねばならず、保守性が悪くなる。

//そこで、

public class Stationery
{

};

public class Scissor:Stationery
{

}

public class StationeryFactory//Stationeryクラスを継承する下位クラスのインスタンスを生成する「ファクトリークラス」のインターフェイス
{
    public:
        virtual Stationery CreateStationery();
};

public class ScissorFactory:StationeryFactory//StationeryFactoryクラスを実装する
{
    public:
        Scissor CreateScissor();
};

//のように、インスタンスを生成するファクトリークラスを作成することで、if文を減らすことができる。

//ただし、記述量はコンストラクタを用いた場合より増える
