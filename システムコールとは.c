//・システムコールとは
//アプリケーションに対して、通常特権モードでしか使えないOSの機能を使用できるようにするためのインターフェース。

//例えば、ファイルの開閉を行うコードをDebian 12.9で実行した場合に呼ばれるシステムコールを確認してみる。

//観察方法
//1. 以下のコードをコンパイル
//2. strace (実行ファイル)を実行

#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1) {
        // エラーハンドリング
        return 1;
    }
    close(fd);
    return 0;
}

//出力結果

//execve("./a.out", ["./a.out"], 0x7ffdb8f597e0 /* 42 vars */) = 0
//brk(NULL)                               = 0x55baae42e000
//mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f9eaa4ce000
//access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
//openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
//newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=70622, ...}, AT_EMPTY_PATH) = 0
//mmap(NULL, 70622, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f9eaa4bc000
//close(3)                                = 0
//openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
//read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\20t\2\0\0\0\0\0"..., 832) = 832
//pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
//newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=1922136, ...}, AT_EMPTY_PATH) = 0
//pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
//mmap(NULL, 1970000, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f9eaa2db000
//mmap(0x7f9eaa301000, 1396736, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x26000) = 0x7f9eaa301000
//mmap(0x7f9eaa456000, 339968, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x17b000) = 0x7f9eaa456000
//mmap(0x7f9eaa4a9000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1ce000) = 0x7f9eaa4a9000
//mmap(0x7f9eaa4af000, 53072, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f9eaa4af000
//close(3)                                = 0
//mmap(NULL, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f9eaa2d8000
//arch_prctl(ARCH_SET_FS, 0x7f9eaa2d8740) = 0
//set_tid_address(0x7f9eaa2d8a10)         = 3149
//set_robust_list(0x7f9eaa2d8a20, 24)     = 0
//rseq(0x7f9eaa2d9060, 0x20, 0, 0x53053053) = 0
//mprotect(0x7f9eaa4a9000, 16384, PROT_READ) = 0
//mprotect(0x55ba73eba000, 4096, PROT_READ) = 0
//mprotect(0x7f9eaa500000, 8192, PROT_READ) = 0
//prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
//munmap(0x7f9eaa4bc000, 70622)           = 0
//openat(AT_FDCWD, "test.txt", O_RDONLY)  = 3
//close(3)                                = 0
//exit_group(0)                           = ?
//+++ exited with 0 +++

//これだけのコードでも多くのシステムコールが実行されていることがわかる。