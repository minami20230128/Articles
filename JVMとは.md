# JVMとは
Javaバイトコードを解釈・実行するための仮想マシン。

## なぜ仮想マシンと呼ばれるのか？
単にJavaを解釈できるだけでなく、Javaバイトコードと呼ばれる命令セットを持ち、
以下のようなCPUやOSの差を吸収するための抽象層を提供するから。

- 仮想スタック／レジスタ	
...JVMはスタックベースのアーキテクチャを持ち、レジスタの代わりに操作する

- JVMヒープ	
...OSのメモリとは独立したJava専用ヒープを持つ

- JVMガベージコレクタ
...実メモリと連動しながらJavaのメモリモデルを保つ

- JVMスレッドモデル
...OSスレッドAPIを隠蔽してJavaのThreadやRunnableを提供

- Java API + JVMネイティブ連携	
...java.io, java.nio, java.netなどのAPIから抽象的にアクセスできる

## その他機能
・JITコンパイル
...規定回数以上実行されたメソッドを機械語に翻訳し、最適化を行う。

## Javaバイトコードを実際に見てみよう！
### 手順
1. ソースコードをコンパイル  
   javac 〇〇.java
2. クラスファイルを逆アセンブル&詳細表示  
   javap -v 〇〇.class

Javaのソースコード
```java
class Main
{
    public static void main(String args[])
    {
        System.out.println("hello");
    }
}
```

バイトコード
```
class Main
  minor version: 0
  major version: 67
  flags: (0x0020) ACC_SUPER
  this_class: #21                         // Main
  super_class: #2                         // java/lang/Object
  interfaces: 0, fields: 0, methods: 2, attributes: 1
Constant pool:
   #1 = Methodref          #2.#3          // java/lang/Object."<init>":()V
   #2 = Class              #4             // java/lang/Object
   #3 = NameAndType        #5:#6          // "<init>":()V
   #4 = Utf8               java/lang/Object
   #5 = Utf8               <init>
   #6 = Utf8               ()V
   #7 = Fieldref           #8.#9          // java/lang/System.out:Ljava/io/PrintStream;
   #8 = Class              #10            // java/lang/System
   #9 = NameAndType        #11:#12        // out:Ljava/io/PrintStream;
  #10 = Utf8               java/lang/System
  #11 = Utf8               out
  #12 = Utf8               Ljava/io/PrintStream;
  #13 = String             #14            // hello
  #14 = Utf8               hello
  #15 = Methodref          #16.#17        // java/io/PrintStream.println:(Ljava/lang/String;)V
  #16 = Class              #18            // java/io/PrintStream
  #17 = NameAndType        #19:#20        // println:(Ljava/lang/String;)V
  #18 = Utf8               java/io/PrintStream
  #19 = Utf8               println
  #20 = Utf8               (Ljava/lang/String;)V
  #21 = Class              #22            // Main
  #22 = Utf8               Main
  #23 = Utf8               Code
  #24 = Utf8               LineNumberTable
  #25 = Utf8               main
  #26 = Utf8               ([Ljava/lang/String;)V
  #27 = Utf8               SourceFile
  #28 = Utf8               Main.java
{
  Main();
    descriptor: ()V
    flags: (0x0000)
    Code:
      stack=1, locals=1, args_size=1
         0: aload_0
         1: invokespecial #1                  // Method java/lang/Object."<init>":()V
         4: return
      LineNumberTable:
        line 1: 0

  public static void main(java.lang.String[]);
    descriptor: ([Ljava/lang/String;)V
    flags: (0x0009) ACC_PUBLIC, ACC_STATIC
    Code:
      stack=2, locals=1, args_size=1
         0: getstatic     #7                  // Field java/lang/System.out:Ljava/io/PrintStream;
         3: ldc           #13                 // String hello
         5: invokevirtual #15                 // Method java/io/PrintStream.println:(Ljava/lang/String;)V
         8: return
      LineNumberTable:
        line 5: 0
        line 6: 8
}
```

Codeという項目に書かれているのがバイトコード。  
それぞれのニーモニックの意味については以下を参照。  
https://docs.oracle.com/javase/specs/jvms/se7/html/

## 補足
Pythonなど他の言語でも、仮想環境を使って環境差を吸収する実装は行われている。  
サードパーティライブラリとの連携のしやすさなど細かいところではJavaに敵わなくとも「どこでも動く」のは他の言語でも当たり前になりつつある。