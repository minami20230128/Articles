// ワイルドカードとは

// 非境界ワイルドカード
import java.util.ArrayList;

public class Main {
    public static void main(String[] args) throws Exception {
        ArrayList<?> list = new ArrayList<>();

        ArrayList<String> strList = new ArrayList<>(asList("AA"));
        
        list = strList;
        String s = list.get(0); // エラー
        Object s = list.get(0); // 通る。静的にはObject型としてしか使えない
        
        list.add(null); // nullは渡せる
        list.add("BB"); // これはNG
    }
}

// 上限境界ワイルドカード
//import java.util.ArrayList;
//import static java.util.Arrays.asList;
//
//class Parent {
//    String name;
//    Parent(String name) {
//        this.name = name;
//    }
//}
//
//class Child extends Parent {
//    String name;
//    Child(String name) {
//        super(name);
//        this.name = name;
//    }
//}
//
//class GrandChild extends Child {
//    String name;
//    GrandChild(String name) {
//        super(name);
//        this.name = name;
//    }
//}
//
//public class Main {
//    public static void main(String[] args) throws Exception {
//        ArrayList<? extends Child> list = new ArrayList<>();
//
//        ArrayList<Child> childList = new ArrayList<>(asList(new Child("AA"), new GrandChild("BB")));
//        
//        list = childList;
//
//        Child c = list.get(0); // 返り値を任意の型で受け取れる
//        Object o = list.get(0);
//        
//        list.add(null);
//        list.add(new Child("CC")); // 引数はnullしか渡せない
//    }
//}
//
//// 下限境界ワイルドカード
//import java.util.ArrayList;
//import static java.util.Arrays.asList;
//
//class Parent {
//    String name;
//    Parent(String name) {
//        this.name = name;
//    }
//}
//
//class Child extends Parent {
//    String name;
//    Child(String name) {
//        super(name);
//        this.name = name;
//    }
//}
//
//class GrandChild extends Child {
//    String name;
//    GrandChild(String name) {
//        super(name);
//        this.name = name;
//    }
//}
//
//public class Main {
//    public static void main(String[] args) throws Exception {
//        ArrayList<? super Child> list = new ArrayList<>();
//
//        ArrayList<Parent> childList = new ArrayList<>(asList(new Child("AA"), new Parent("BB")));
//        
//        list = childList;
//
//        Child c = list.get(0); // 返り値はObjectでしか扱えない
//        Object o = list.get(0);
//        
//        list.add(null);
//        list.add(new Child("CC")); // 任意の型の引数を渡せる
//    }
//}