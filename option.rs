//・Option<T>型とは
//無効な値を取ることができる列挙型
//イテレータが配列の終点に達し、それ以上値を読み出せないときなどに備えて作られた

//イテレータで取得された値はSome(T)(値を取得できたとき)かNone(値を取得できなかったとき)の形式で返され、
//以下のようにパターンマッチで値を取り出す

fn main() {
    let a = Some(5);

    match a {
        Some(i) => message(i), // このようにしてSomeの中身iを使うことができる。iはなんと命名してもいい
        None => println!("None"),
    }

    fn message(number_in_some: u32) {
        println!("a = {}", number_in_some);
    }
}

//出力結果：a=5