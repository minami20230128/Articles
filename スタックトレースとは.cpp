//・スタックトレースとは
//プログラムの実行過程（スタックフレーム）を記録したもの
//これを確かめることで、関数の呼び出し経路、引数・ローカル変数の内容などを確認することができる

// 用語
// ・スタックフレーム...サブルーチン（関数）を呼び出したとき、
// 「コールスタック」という場所に積まれる戻り先のアドレス・戻り値・引数などの情報のこと
// サブルーチンを抜けるとこの情報は取り除かれる
// ・サブルーチン...関数・メソッド
// ・コールスタック...スタックの一種で、スタックフレームを置くための場所
// ・スタックポインタ...コールスタックの最上段を指すポインタ
// これを動かすことでコールスタックの中身にアクセス可能

#include <execinfo.h>
#include <string>
#include <iostream>
#include <vector>

/* アドレス型 */
using address_t = void*;
/* スタックトレース情報 */
struct StackTrace
{
    /* トレース数 */
    uint32_t trace_size;
    /* トレースアドレスリスト */
    std::vector<address_t> traces;
    /* トレースシンボルリスト */
    std::vector<std::string> symbols;
};

/* Stack Tracerクラス宣言 */
class StackTracer
{
public:
    /* スタックトレース情報取得 */
    static const StackTrace GetStackTrace();
};

/* スタックトレース情報取得 */
const StackTrace StackTracer::GetStackTrace()
{
    /* 最大トレースサイズ */
    constexpr size_t MaxSize = 256;
    /* トレースリスト */
    void* traces[MaxSize] = {};
    /* スタックトレース取得 */
    int trace_size = backtrace(traces, MaxSize);
    /* シンボルリスト取得 */
    char** symbols = backtrace_symbols(traces, trace_size);
    /* スタックトレース情報生成 */
    StackTrace stack_trace;
    /* トレースサイズ  */
    stack_trace.trace_size = (uint32_t)trace_size;
    /* トレースリストメモリ確保 */
    stack_trace.traces.reserve(trace_size);
    /* シンボルリストメモリ確保 */
    stack_trace.symbols.reserve(trace_size);
    /* トレースサイズ分ループ */
    for (int i = 0; i < trace_size; i++)
    {
        /* トレースアドレスをリストに追加 */
        stack_trace.traces.push_back(traces[i]);
        /* シンボル情報をシンボルリストに追加 */
        stack_trace.symbols.push_back(symbols[i]);
    }
    /* シンボルリスト解放 */
    free(symbols);
    return stack_trace;
}

int main()
{
    StackTracer* stacktracer;
    auto trace = stacktracer->GetStackTrace();

    for(int i = 0; i < trace.symbols.size(); i++)
    {
        std::cout << trace.symbols[i] << std::endl;
    }

    return 0;
}

//出力結果：
// 0   main                                0x000000010d1e9d85 _ZN11StackTracer13GetStackTraceEv + 101
// 1   main                                0x000000010d1ea238 main + 24
// 2   dyld                                0x000000010dd2b52e start + 462

//dyldとは、ダイナミックライブラリを呼び出すためのmacのプログラム