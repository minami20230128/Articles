// ワイルドカードとは

// 非境界ワイルドカード
import java.util.ArrayList;

class Parent {
    String name;
    Parent(String name) {
        this.name = name;
    }
}

class Child extends Parent {
    String name;
    Child(String name) {
        super(name);
        this.name = name;
    }
}

class GrandChild extends Child {
    String name;
    GrandChild(String name) {
        super(name);
        this.name = name;
    }
}

public class Main {
    public static void main(String[] args) throws Exception {
        ArrayList<? super Child> list = new ArrayList<>();

        ArrayList<Parent> childList = new ArrayList<>(asList(new Child("AA"), new Parent("BB")));
        
        list = childList;

        Child c = list.get(0); // 返り値はObjectでしか扱えない
        Object o = list.get(0);
        
        list.add(null);
        list.add(new Child("CC")); // 任意の型の引数を渡せる
    }
}