//・ライフタイムとは
//変数が生成〜破棄されるまでの期間
//・あるデータにアクセスできるのは一つの変数だけ(似た機能がC++のunique pointer)
//・アクセス権には「読み出し」「書き込み」の2種類がある
//など、Rustではメモリ破壊を防ぐため厳密に管理されている

//・スコープから外れた変数にアクセスしようとするとコンパイルエラーになる
//fn main(){
    //let r;

    // {
    //     let x = 5;
    //     r = &x;
    // } // ここでxがスコープから外れる

    // println!("r: {}", r); 
//}

//実行結果: error[E0597]: `x` does not live long enough

//・ある変数を別の変数に代入するとデータへの所有権を失う
// fn main(){
//     let r = vec![1,2,3];
//     let i = r;

//     println!("r: {}", r[0]);
// }
//実行結果: error[E0382]: borrow of moved value: `r`

//・関数の引数として渡すと所有権を失う
struct Book
{
    title: String
}

fn function(book: Book)
{

}

fn main(){
    let book = Book{title:"title".to_string()};
    function(book);
    println!("{}", book.title);
}

//実行結果: error[E0382]: borrow of moved value: `r`