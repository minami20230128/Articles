# AOPとは
あるクラスの本質から外れた処理（横断的関心事）を外出しすること。  
例えば、ユーザ登録を行う処理(UserService.createUser())をトランザクションとして管理する場合、  
@Transactionalアノテーションを付与すると、トランザクション管理を担うコードがProxyオブジェクトに自動生成される。  

## 確認方法
まず、@Transactionalアノテーションを利用したコードを用意する。
```
package com.example.demo.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.example.demo.entity.User;
import com.example.demo.repository.UserRepository;

import jakarta.transaction.Transactional;

@Service
public class UserService {

    @Autowired
    private UserRepository userRepository;

    @Transactional
    public void createUser(String name) {
        User user = new User();
        user.setName(name);
        userRepository.save(user);
    }
}
```

このメソッドの呼び元で、userServiceインスタンスのクラス名を表示してみる。
```
package com.example.demo.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import com.example.demo.service.UserService;

@RestController
public class UserController {

    @Autowired
    private UserService userService;

    @PostMapping("/users")
    public String createUser(@RequestParam String name) {
        userService.createUser(name);
        System.out.println("Class: " + userService.getClass());
        return "OK";
    }
}
```  
すると、**Class: class com.example.demo.service.UserService$$SpringCGLIB$$0**と表示される。  
UserServiceクラス内でクラス名を表示するとClass: class com.example.demo.service.UserServiceとなるため、UserControllerクラス内で呼ばれているuserServiceは**UserServiceクラスのインスタンスではない**と言える。  

この正体はDIコンテナによってインジェクションされた**Proxyオブジェクト**。  
DIコンテナは、UserService.createUser()を呼びつつ前後でトランザクション管理を行うメソッド（イメージとしては以下）をProxyオブジェクトに自動生成する。  
そしてそれをUserControllerクラスにインジェクションしている。
```
public class UserService$$SpringCGLIB$$0 extends UserService {
    private UserService originalService; 
    private TransactionManager txManager; 

    @Override
    public void createUser(String name) {
        try {
            txManager.begin();              // ① トランザクション開始
            super.createUser(name);         // ② 元の処理を呼び出す

            txManager.commit();            // ③ 正常ならコミット
        } catch (Exception e) {
            txManager.rollback();          // ④ エラー時はロールバック
            throw e;
        }
    }
}

```

## AOPを使わなかったらどうなる？
仮にトランザクション管理をUserService.createUser()に自前で実装すると、以下のようなコードになる。
```
public class UserService {

    private final TransactionManager txManager;
    private final Logger logger;

    public UserService(TransactionManager txManager, Logger logger) {
        this.txManager = txManager;
        this.logger = logger;
    }

    public void createUser(String name) {
        logger.info("Start createUser");

        txManager.begin();
        try {
            // 本来の業務ロジック
            System.out.println("Creating user: " + name);

            txManager.commit();
            logger.info("createUser succeeded");
        } catch (Exception e) {
            txManager.rollback();
            logger.error("createUser failed", e);
            throw e;
        }
    }
}
```
元のコードと比べると非常に可読性が低く、単一責任の原則にも違反している。  
ここからProxyクラスを利用してトランザクション管理を外出ししたものが冒頭のコードで、一目でなんの処理をしているかわかる上に、分岐が少なくテストコードも圧倒的に書きやすい。