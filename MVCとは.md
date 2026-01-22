# ・MVCとは
Model, View, Controllerの3層に分かれる構造。  
Model...ビジネスロジックなどを担当  
View...UIを担当しユーザ入力を受け取る  
Controller...Modelの処理結果を元にViewを操作

## 例：ログイン処理を行う場合の流れ
1. ユーザがユーザ名・パスワードを入力する
2. Viewがユーザ入力を受け取る
3. Modelが入力された情報をDBと称号し、認証結果を返す
4. ControllerがModelの返した結果を受け取り、それに応じた画面を表示するようにViewに命令

![](images/MVC.png)