//・recordクラスとは
//データキャリア（データを保持するために使うクラス）の作成に役立つ修飾子。
//この修飾子をつけると、
//・クラスのすべてのフィールドがprivate finalになる
//・コンストラクタが作成される
//・toString()などが自動作成される

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

    // Implementation of equals() and hashCode(), which specify
    // that two record objects are equal if they
    // are of the same type and contain equal field values.
    public boolean equals...
    public int hashCode...

    // An implementation of toString() that returns a string
    // representation of all the record class's fields,
    // including their names.
    public String toString() {...}
}