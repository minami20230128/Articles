//・UNIXドメインソケット通信とは
//ファイルシステム上にデータ送受信を行う特殊な領域を作成し、通信を行う。
//(あらゆるものをシステムとして扱うというUNIX思想から便宜上ファイルの形を取っているだけで、実際はファイルではない)
//同一マシン上でしか通信できない代わりに、INETドメイン通信に比べてスループットが高い。

//データ送受信方法としては、ストリーム型とデータグラム型の２種類があり、
//前者ははTCP通信と同様にデータを一つの流れのように送信する方式、
//後者はUDP通信のようにデータをパケットとしてぶつ切りに送る方式である。
//なお、送り方がTCP・UDP通信と同じなだけで、そのものではない。

//送信側
#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>

int main() {
    int sockfd;
    struct sockaddr_un server_addr;

    // ソケットを作成
    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return 1;
    }

    // サーバーのアドレスを設定
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, "/tmp/socket_file", sizeof(server_addr.sun_path) - 1);//ソケットファイルのパスを指定

    // サーバーに接続
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        close(sockfd);
        return 1;
    }

    // メッセージを送信
    const char* message = "Hello, server!";
    if (send(sockfd, message, strlen(message), 0) == -1) {
        perror("send");
    }

    // ソケットを閉じる
    close(sockfd);

    return 0;
}


//受信側
#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>

int main() {
    int sockfd, newsockfd;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_un serv_addr, cli_addr;

    // ソケットを作成
    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return 1;
    }

    // サーバーのアドレスを設定
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strncpy(serv_addr.sun_path, "/tmp/socket_file", sizeof(serv_addr.sun_path) - 1);

    // ソケットにアドレスをバインド
    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("bind");
        close(sockfd);
        return 1;
    }

    // 接続待ち状態にする
    if (listen(sockfd, 5) == -1) {
        perror("listen");
        close(sockfd);
        return 1;
    }

    std::cout << "Waiting for connection..." << std::endl;

    // クライアントからの接続を受け付ける
    clilen = sizeof(cli_addr);
    if ((newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen)) == -1) {
        perror("accept");
        close(sockfd);
        return 1;
    }

    std::cout << "Connection accepted." << std::endl;

    // データを受信
    int n = read(newsockfd, buffer, sizeof(buffer));
    if (n == -1) {
        perror("read");
    } else if (n == 0) {
        std::cerr << "Client disconnected." << std::endl;
    } else {
        std::cout << "Received message: " << buffer << std::endl;
    }

    // ソケットを閉じる
    close(newsockfd);
    close(sockfd);

    return 0;
}

