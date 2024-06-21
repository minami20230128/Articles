// ・Stream APIとは
// JavaのList、ArrayListなどの配列オブジェクトに対し、Pythonのmap()、reduce()、filter()のように一行で操作を適用できるAPI
//以下はarrから偶数の要素だけを抜き出すプログラム

import java.util.ArrayList;
import java.util.Arrays;

public class Main
{
    public static void main(String[] args)
    {
        var arr = new ArrayList<>(Arrays.asList(1, 2, 3, 4, 5, 6));
        arr.stream()
        .filter(i -> i % 2 == 0)
        .forEach(System.out::println);
    }
}

//出力結果：
2
4
6