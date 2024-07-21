・マクロとは
コードを生成するコード。メタプログラミングを行うための機能。
以下の5種類がある。

1. 宣言的マクロ
コードをパターンに当てはめる

#[macro_export]
macro_rules! vec {
    ( $( $x:expr ),* ) => {
        {
            let mut temp_vec = Vec::new();
            $(
                temp_vec.push($x);
            )*
            temp_vec
        }
    };
}

2. 手続き的マクロ
関数のように動作する

use proc_macro;

#[some_attribute]
pub fn some_name(input: TokenStream) -> TokenStream {
}

3. 関数風マクロ

4. Deriveマクロ

5. 属性風マクロ