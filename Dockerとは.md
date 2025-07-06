# Dockerとは  
一つのサーバ上で複数のアプリケーションの実行環境を整えるためのプラットフォーム。

## 仮想マシンと比較しての長所  
仮想マシン（ハイパーバイザ型）は、ホストOS上にゲストOSをインストールし、その上にアプリケーションを展開する。  
一方DockerはゲストOSを必要としないため、容量を食わず起動時間も短い。  

![ハイパーバイザーとDockerの比較](/image/仮想マシン_Docker_比較.png)

## 用語
- **Dockerコンテナ**...アプリケーションの実行環境
- **Dockerイメージ**...Dockerコンテナの元になるもの
- **Dockerfile**...Dockerイメージの設計図  
- **Docker Hub**...Dockerイメージを保存・共有する場所  
Dockerイメージは、Docker Hubからpullしてくることも可能だが、Dockerfileから自前で構築することも可能。  
また、DockerイメージをDocker HubからpullしてきたうえでパッケージインストールなどをDockerfileで自動化する場合もある。  

## 構造  
ホストOS上でDocker DesktopアプリがLinux仮想マシンを立ち上げる。 
仮想マシン上で**namespace**によって隔離されたプロセスがコンテナ。  

**ホストがMacOSの場合**
```
macOS（Darwinカーネル）
└── Docker Desktop（アプリ）
    └── 内部で Linux VM（例：Alpineベースの軽量VM）
        └── docker デーモン（dockerd）
            └── Linuxカーネルのnamespaceなどでコンテナを分離

```

**ホストがWindowsの場合**
```
Windows
└── Docker Desktop
    └── WSL2 (実質Linux)
        └── dockerd
            └── Linuxコンテナ（namespace + cgroups）

```

## 仕組み
namespaceとは、Linux上でさまざまな操作の影響範囲を分けるためのもの。  
- マウント名前空間...マウントの影響範囲を限定できる  
- UTS名前空間...ホスト名・ドメイン名を独自に保持できる
- IPC名前空間...プロセス間通信（IPC）オブジェクトを名前空間ごとに独立して持てる
- PID名前空間...プロセスIDを独立して保持できる
- ネットワーク名前空間...ネットワークリソース（IPアドレス、ポート番号、ルーティングテーブルなど）を独立して保持できる
- ユーザ名前空間...UID、GIDの空間を名前空間ごとに独立して持てる  
この仕組みを使ってコンテナ同士を分離している。  
なお、namespace自体はDocker関係なくLinux単体でも使用可能。

### 実験：実際にコンテナを作ってnamespaceが分割されていることを確認してみよう！
Mac・Windowsの場合、Docker Desktop上に起動したLinuxカーネルの中を見ることはできない。  
そのため、この実験を行うにはLinux上でDockerコンテナを複数立ち上げる必要がある。  
今回はDebian12.11を使用。  

1. 下記の手順に従ってDockerをインストール。  
```
# Add Docker's official GPG key:
sudo apt-get update
sudo apt-get install ca-certificates curl
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/debian/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc

# Add the repository to Apt sources:
echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/debian \
  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
sudo apt-get update
sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
```

2. 2つのDockerコンテナを作成し、PIDを取得  
```
docker run -d --name container1 debian sleep infinity
docker run -d --name container2 debian sleep infinity  
pid1=$(docker inspect -f '{{.State.Pid}}' container1)
pid1=$(docker inspect -f '{{.State.Pid}}' container2)
echo "PID1: $pid1"
echo "PID2: $pid2"
```

3. コンテナごとの名前空間情報を表示  
今回は、container1のPIDは43370、container2のPIDは43438が表示されたので、
container1の情報を取得するには以下を実行。  
```
ls -l /proc/43370/ns/
```

実行結果
```
lrwxrwxrwx 1 root root 0 Jul  6 23:32 cgroup -> 'cgroup:[4026532414]'
lrwxrwxrwx 1 root root 0 Jul  6 23:32 ipc -> 'ipc:[4026532412]'
lrwxrwxrwx 1 root root 0 Jul  6 23:31 mnt -> 'mnt:[4026532410]'
lrwxrwxrwx 1 root root 0 Jul  6 23:31 net -> 'net:[4026532415]'
lrwxrwxrwx 1 root root 0 Jul  6 23:32 pid -> 'pid:[4026532413]'
lrwxrwxrwx 1 root root 0 Jul  6 23:32 pid_for_children -> 'pid:[4026532413]'
lrwxrwxrwx 1 root root 0 Jul  6 23:32 time -> 'time:[4026531834]'
lrwxrwxrwx 1 root root 0 Jul  6 23:32 time_for_children -> 'time:[4026531834]'
lrwxrwxrwx 1 root root 0 Jul  6 23:32 user -> 'user:[4026531837]'
lrwxrwxrwx 1 root root 0 Jul  6 23:32 uts -> 'uts:[4026532411]'
```

container2の情報を取得するには以下を実行。  
```
ls -l /proc/43438/ns/
```

```
lrwxrwxrwx 1 root root 0 Jul  6 23:32 cgroup -> 'cgroup:[4026532490]'
lrwxrwxrwx 1 root root 0 Jul  6 23:32 ipc -> 'ipc:[4026532488]'
lrwxrwxrwx 1 root root 0 Jul  6 23:31 mnt -> 'mnt:[4026532486]'
lrwxrwxrwx 1 root root 0 Jul  6 23:31 net -> 'net:[4026532491]'
lrwxrwxrwx 1 root root 0 Jul  6 23:32 pid -> 'pid:[4026532489]'
lrwxrwxrwx 1 root root 0 Jul  6 23:32 pid_for_children -> 'pid:[4026532489]'
lrwxrwxrwx 1 root root 0 Jul  6 23:32 time -> 'time:[4026531834]'
lrwxrwxrwx 1 root root 0 Jul  6 23:32 time_for_children -> 'time:[4026531834]'
lrwxrwxrwx 1 root root 0 Jul  6 23:32 user -> 'user:[4026531837]'
lrwxrwxrwx 1 root root 0 Jul  6 23:32 uts -> 'uts:[4026532487]'

```

以上の結果から、コンテナ同士すべてのnamespaceが分離されていることが確認できた。