# ・ダックタイピングとは
# 動的型付け言語で、同じ関数を持つクラスのインスタンスを全てポリモーフィズム的に扱えること。

# 以下はPythonでのダックタイピングの例:
# def test(tmp):
#     print(tmp.cry())
# 
# class Dog:
#     def cry(self):
#         return "わん"
# 
# class Bird:
#     def cry(self):
#         return "ぴよぴよ"
# 
# dog = Dog()
# bird = Bird()
# test(dog)
# test(bird)

# 出力結果
# わん
# ぴよぴよ

# 問題点
# 静的型付け言語では同じインターフェースを継承しているかどうかのチェックが入るが、
# ダックタイピングだと、全く違う意図で作られたクラスでも、同じ関数があると言うだけでポリモーフィズムが適用できてしまう。

# そこで、各動的型付け言語には「同一インターフェースに準拠しているかどうか」をチェックできるライブラリ・ツールが存在する。
# Pythonの場合、Protocolというライブラリを使うと関数が実装されていない場合エラーを出すことが可能。

from typing import Protocol

class Animal(Protocol):
    def cry(self) -> str:
        ...

class Dog:
    def cry(self) -> str:
        return "わん"

class Bird:
    def cry(self) -> str:
        return "ぴよぴよ"

class Cat:
    def meow(self) -> str:
        return "にゃーん"

def test(animal: Animal):
    print(animal.cry())

dog = Dog()
bird = Bird()
cat = Cat()
test(dog)
test(bird)
test(cat)

# 出力結果：
# わん
# ぴよぴよ
# Traceback (most recent call last):
#   File "/Users/hirataminami/Desktop/Articles/ダックタイピングとは.py", line 58, in <module>
#     test(cat)
#     ~~~~^^^^^
#   File "/Users/hirataminami/Desktop/Articles/ダックタイピングとは.py", line 51, in test
#     print(animal.cry())
#           ^^^^^^^^^^
# AttributeError: 'Cat' object has no attribute 'cry'

#　Catクラスにcry関数が実装されていないというエラーが発生している。
# Protocolのお陰で、より安全にダックタイピングを扱うことが可能。


# *静的型付け言語への導入
# ダックタイピングは動的型付け言語でポリモーフィズムを実現するためのテクニックに近かったが、
# 最近ではC++などの静的型付け言語にも取り入れられている。
# 理由：
# ・インターフェースを用意しなくて良い分オーバーヘッドが減るから
# ・一部の関数だけを継承させたい場合、インターフェースを作るより自由度が高いから