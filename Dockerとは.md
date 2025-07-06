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

## namespaceとは？
Linux上でさまざまな操作の影響範囲を分けるためのもの。  
コンテナを分割するためにも使われるが、単独でも使用可能。  
- マウント名前空間...マウントの影響範囲を限定できる  
- UTS名前空間...ホスト名・ドメイン名を独自に保持できる
- IPC名前空間...プロセス間通信（IPC）オブジェクトを名前空間ごとに独立して持てる
- PID名前空間...プロセスIDを独立して保持できる
- ネットワーク名前空間...ネットワークリソース（IPアドレス、ポート番号、ルーティングテーブルなど）を独立して保持できる
- ユーザ名前空間...UID、GIDの空間を名前空間ごとに独立して持てる  
