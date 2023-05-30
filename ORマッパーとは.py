#・ORマッパー(ORM)とは
#オブジェクトとデータベースの項目の相互変換を行う機能・ソフト
#オブジェクトからSQL文を自動生成することができるため、文字列連結に比べて操作ミスが減る
#さらに、データベースとアプリケーションの独立性が高くなるという利点もある
#（データベースの種類を変えても、自分でSQLを書き換えなくてよいなど）

#ただし、複雑なクエリを書くことが出来ない、細かいチューニングが難しい等のデメリットもある

#使い方

import dataset

class Book:
    title = ""
    publisher = ""
    date = ""
    author = []

def main():
    dbconn = dataset.connect("postgresql://toshokanriuser:toshokanripass@localhost/toshokanri")
    table = dbconn['book']
    books = table.find()
    for book in books:
        print(f"題名:{book['title']} 出版社:{book['publisher']} 出版年月日:{book['date']} 著者:{book['author']}")#1. "book"テーブルに入っているデータを読み出し・表示
    print(books.result_proxy.context.statement)#2. 内部で使われたクエリ文を表示
 
if __name__ == "__main__":
    main()

#出力結果
#1
#題名:title 出版社:publisher 出版年月日:20220901 著者:['author']
#題名:dokushuC 出版社:shoeisha 出版年月日:20220807 著者:['herbert schildt']
#題名:seven habits 出版社:steven covey 出版年月日:20080306 著者:['steven covey']
#題名:bookofjava 出版社:impress 出版年月日:20191121 著者:['kunimoto daigo', 'nakayama kiyotaka']

#2
#SELECT book.title, book.publisher, book.date, book.author
#FROM book
#WHERE true
# LIMIT ALL OFFSET %(param_1)s