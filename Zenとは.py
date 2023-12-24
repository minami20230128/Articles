#・Python Zennとは
#Pythonを書く際の心構え

import this

#を実行すると、以下の文章が表示される

#The Zen of Python, by Tim Peters

#Beautiful is better than ugly.
#Explicit is better than implicit.
#Simple is better than complex.
#Complex is better than complicated.
#Flat is better than nested.
#Sparse is better than dense.
#Readability counts.
#Special cases aren't special enough to break the rules.
#Although practicality beats purity.
#Errors should never pass silently.
#Unless explicitly silenced.
#In the face of ambiguity, refuse the temptation to guess.
#There should be one-- and preferably only one --obvious way to do it.
#Although that way may not be obvious at first unless you're Dutch.
#Now is better than never.
#Although never is often better than *right* now.
#If the implementation is hard to explain, it's a bad idea.
#If the implementation is easy to explain, it may be a good idea.
#Namespaces are one honking great idea -- let's do more of those!


1. Explicit is better than implicit.
どのモジュールから呼ばれているかなど明確にするべき

NG: 
from os import *
print(getcwd())

OK:
import os
print(os.getcwd())

2. Complex is better than complicated.
複雑(誰でも知っている関数・機能でごちゃごちゃ書く)より、難解(知らない関数でシンプルに書く)のほうがよい
ロジックを読み解くコスト > 知らない関数を調べるコスト

NG:
counter = 0
while counter < 5:
   print(counter)
   counter += 1

OK:
for i in xrange(5):
   print(i)