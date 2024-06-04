・GPG Keyとは
GNU Privacy Guardというオープンソースの公開鍵。
パッケージのインストール時には、正しい発行元からインストールできているかをGPG鍵を使って確認するために使われる。
それ以外にも、署名やメールの暗号化・復号化など一般的な公開鍵と同じ用途で使用される。

*Fluent BitのインストールにおけるGPG Keyの使用の流れ
1. 配布元のコミュニティが秘密鍵でパッケージを暗号化
2. インストールする人が公開鍵をインストール
curl https://packages.fluentbit.io/fluentbit.key | gpg --dearmor > /usr/share/keyrings/fluentbit-keyring.gpg
を実行。
3. フィンガープリントの確認
公開鍵のインストールを実行すると、インストールした鍵のフィンガープリントが表示される。
配布元が提示するフィンガープリント（以下の数字）と表示されたフィンガープリントが一致したら、公開鍵が正当であると言える。
C3C0 A285 34B9 293E AF51  FABD 9F9D DC08 3888 C1CD
4. GPG Keyでパッケージを復号化


参考：
https://docs.fluentbit.io/manual/installation/linux/ubuntu