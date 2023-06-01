//・遅延評価とは
//その値が必要とされるまで処理が行われないこと

using System;
using System.Linq;
using System.Collections.Generic;

namespace LazyEvaluation
{
    class Program
    {
        static void Main(string[] args)
        {
            var list = new List<int>();
            var orderedlist = list.OrderBy(x => x);//1(配列の要素をソート)

            list.Add(10);//2
            list.Add(9);
            list.Add(22);
            list.Remove(22);
            list.Add(13);

            foreach(var elem in orderedlist)
            {
                Console.WriteLine(elem);//3
            }
        }
    }
}

//出力結果:
//9
//10
//13

//変数orderedlistが生成されたのは1の時点であり、要素の追加・削除が行われたのはその後の2である
//しかし、配列の内容を表示してみる(3)と、1の後に行われたはずの2が反映され、そのうえでOrderByが実行されていることがわかる

//遅延評価の利点としては、上記のプログラムにおける22のように最終的には削除されるような要素にまで処理を行うような無駄を省けることなどがある
//ただし、評価が行われるタイミングが予想しにくいというデメリットもある