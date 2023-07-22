--パターンマッチ
--関数を引数によって異なる動きをするように定義すること
func :: Int->Int
func 7 = 7 * 3 --7のときだけ分岐するようにする
func n = n `mod` 3 

main = do{print(func 8); print(func 7)}

--実行結果：
--2
--21