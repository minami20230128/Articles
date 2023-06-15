#・辞書内包表記
#反復可能オブジェクトの要素を辞書に割り当てるための方法
keys = ["0", "1", "2", "3"]
values = ["Spring", "Summer", "Autumn", "Winter"]

dict = {key:value for key, value in zip(keys, values)}
print(dict)