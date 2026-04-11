# Javaもメソッドに自身を渡すのか
## 気になったきっかけ
Cでオブジェクト指向を実現したいとき、構造体のポインタをメソッドに見立てた関数に渡す。
```
# include <stdio.h>
# include <stdlib.h>
typedef struct Calc {
    int num;
} CALC;

int square(int num, CALC* calc) {
    return num * calc->num;
}

int main(void) {
    CALC* calc = malloc(sizeof(CALC));
    calc->num = 4;
    printf("%d", square(4, calc));
    return 0;
}
```

また、Pythonでもメソッドには明示的にselfを渡す。
```
# coding: utf-8
# Your code here!
class Calc:
    def __init__(self, num):
        self.num = num
        
    def square(self, num):
        return num * self.num

def main():
  calc = Calc(4)
  print(calc.square(4))
 
if __name__ == "__main__":
  main()
```
一方、Javaをはじめ、自身を明示的にメソッドには渡さない言語もある。  
こうした言語は内部的にどういう処理になっているのか？

## 結論  
Javaでも内部的にthisを渡している。  
たとえば、以下のコードをコンパイルし、classを逆アセンブルする。
```
import java.util.*;

class Calc {
    int num;
    Calc(int num) {
        this.num = num;
    }
    public int square(int num) {
        return num * this.num;
    }
}

public class Main {
    public static void main(String[] args) throws Exception {
        var calc = new Calc(4);
        System.out.println(calc.square(4));
    }
}

```
すると、出力されるのは以下。
```
  Last modified 2026/04/13; size 617 bytes
  SHA-256 checksum 9ec9282f01daf58bf355452b7f72588cfb7468ca1dd0ac9c8fe75fdbd40c96a9
  Compiled from "Main.java"
public class Main
  minor version: 0
  major version: 67
  flags: (0x0021) ACC_PUBLIC, ACC_SUPER
  this_class: #27                         // Main
  super_class: #2                         // java/lang/Object
  interfaces: 0, fields: 0, methods: 2, attributes: 1
Constant pool:
   #1 = Methodref          #2.#3          // java/lang/Object."<init>":()V
   #2 = Class              #4             // java/lang/Object
   #3 = NameAndType        #5:#6          // "<init>":()V
   #4 = Utf8               java/lang/Object
   #5 = Utf8               <init>
   #6 = Utf8               ()V
   #7 = Class              #8             // Calc
   #8 = Utf8               Calc
   #9 = Methodref          #7.#10         // Calc."<init>":(I)V
  #10 = NameAndType        #5:#11         // "<init>":(I)V
  #11 = Utf8               (I)V
  #12 = Fieldref           #13.#14        // java/lang/System.out:Ljava/io/PrintStream;
  #13 = Class              #15            // java/lang/System
  #14 = NameAndType        #16:#17        // out:Ljava/io/PrintStream;
  #15 = Utf8               java/lang/System
  #16 = Utf8               out
  #17 = Utf8               Ljava/io/PrintStream;
  #18 = Methodref          #7.#19         // Calc.square:(I)I
  #19 = NameAndType        #20:#21        // square:(I)I
  #20 = Utf8               square
  #21 = Utf8               (I)I
  #22 = Methodref          #23.#24        // java/io/PrintStream.println:(I)V
  #23 = Class              #25            // java/io/PrintStream
  #24 = NameAndType        #26:#11        // println:(I)V
  #25 = Utf8               java/io/PrintStream
  #26 = Utf8               println
  #27 = Class              #28            // Main
  #28 = Utf8               Main
  #29 = Utf8               Code
  #30 = Utf8               LineNumberTable
  #31 = Utf8               LocalVariableTable
  #32 = Utf8               this
  #33 = Utf8               LMain;
  #34 = Utf8               main
  #35 = Utf8               ([Ljava/lang/String;)V
  #36 = Utf8               args
  #37 = Utf8               [Ljava/lang/String;
  #38 = Utf8               calc
  #39 = Utf8               LCalc;
  #40 = Utf8               Exceptions
  #41 = Class              #42            // java/lang/Exception
  #42 = Utf8               java/lang/Exception
  #43 = Utf8               SourceFile
  #44 = Utf8               Main.java
{
  public Main();
    descriptor: ()V
    flags: (0x0001) ACC_PUBLIC
    Code:
      stack=1, locals=1, args_size=1
         0: aload_0
         1: invokespecial #1                  // Method java/lang/Object."<init>":()V
         4: return
      LineNumberTable:
        line 11: 0
      LocalVariableTable:
        Start  Length  Slot  Name   Signature
            0       5     0  this   LMain;

  public static void main(java.lang.String[]) throws java.lang.Exception;
    descriptor: ([Ljava/lang/String;)V
    flags: (0x0009) ACC_PUBLIC, ACC_STATIC
    Code:
      stack=3, locals=2, args_size=1
         0: new           #7                  // class Calc
         3: dup
         4: iconst_4
         5: invokespecial #9                  // Method Calc."<init>":(I)V
         8: astore_1
         9: getstatic     #12                 // Field java/lang/System.out:Ljava/io/PrintStream;
        12: aload_1
        13: iconst_4
        14: invokevirtual #18                 // Method Calc.square:(I)I
        17: invokevirtual #22                 // Method java/io/PrintStream.println:(I)V
        20: return
      LineNumberTable:
        line 13: 0
        line 14: 9
        line 15: 20
      LocalVariableTable:
        Start  Length  Slot  Name   Signature
            0      21     0  args   [Ljava/lang/String;
            9      12     1  calc   LCalc;
    Exceptions:
      throws java.lang.Exception
}
SourceFile: "Main.java"
```
LocalVariableTableに「this」が記載されている。