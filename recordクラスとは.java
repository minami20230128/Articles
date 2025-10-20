//・recordクラスとは
//データキャリア（データを保持するために使うクラス）の作成に役立つ修飾子。
//この修飾子をつけると、
//・クラスのすべてのフィールドがprivate finalになる
//・コンストラクタが作成される
//・toString()などが自動作成される
//・フィールドと同名のアクセサメソッド（getter的なもの）
// が生成される。

//このコードは
record Rectangle(double length, double width) { }

//これと同じ
public final class Rectangle {
    private final double length;
    private final double width;

    public Rectangle(double length, double width) {
        this.length = length;
        this.width = width;
    }

    double length() { return this.length; }
    double width()  { return this.width; }

    public boolean equals...
    public int hashCode...

    public String toString() {...}
}

// recordクラスのコンストラクタには2種類ある。
// 1. カノニカルコンストラクタ
// public Rectangle(double length, double width) {
//        this.length = length;
//        this.width = width;
//    }
// のように、すべてのフィールドを引数に取るコンストラクタ。
// 自動生成されるが、自分で定義することも可能。

// 2. コンパクトコンストラクタ
// public Rectangle {
//     if length < 0 {
//         throw new IllegalException("lengthは0以上である必要があります。");
//     }
// }
// バリデーションチェックなどを書くためのコンストラクタ。
// 引数は書かなくてよい。
// また、フィールドへの代入（this.〇〇 = 〇〇）はコンストラクタの最後で暗黙的に行われる。。
// このコンストラクタの中で「this.〇〇」でフィールドにアクセスするとコンパイルエラーが発生する。
// (代入前のfinalフィールドにアクセスしていることになるから)