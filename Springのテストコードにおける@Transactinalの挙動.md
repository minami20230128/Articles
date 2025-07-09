# Springのテストコードにおける@Transactinalの挙動
Springでは、Repositoryクラスのテストを行う際、テストクラスにDIコンテナを生成するアノテーションを付与する。
```
package com.example.demo.repository;

import static org.assertj.core.api.Assertions.assertThat;

import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.orm.jpa.DataJpaTest;

import com.example.demo.entity.User;

@DataJpaTest //<-これ
public class UserRepositoryTest {
	@Autowired
	UserRepository userRepository;
	
	@Test
	void test_save() {
		User user = new User();
		user.setName("Taro");
		userRepository.save(user);
		User selectedUser = userRepository.getReferenceById(user.getId()); //*
		assertThat(selectedUser.getName()).isEqualTo("Taro");
	}
}
```
このアノテーションには@Transactionalアノテーションが包含されている。  
@Transactionalは、テストクラスに付与した場合変更をロールバックする性質を持つため、  
テストクラスからデータの追加・更新・削除を行っても次のテストコード実行時にはDBは元の状態に復元される。  

しかし、変更をコミットしていないはずなのに、新しく登録したユーザのデータをDBから取得できているのはなぜだろうか（*の行）。  

## トランザクションの独立性
多くのDBでは**同一トランザクションの変更はコミットされていなくても読み取り可能。**

PostgreSQL
```
the SELECT does see the effects of previous updates executed within this same transaction, even though they are not yet committed.
```
https://www.postgresql.org/docs/7.1/xact-serializable.html

MySQL
```
The query sees the changes made by transactions that committed before that point in time, and no changes made by later or uncommitted transactions. 
The exception to this rule is that the query sees the changes made by earlier statements within the same transaction. 
```
https://dev.mysql.com/doc/refman/8.0/en/innodb-consistent-read.html

このため、コミットされていない変更でも同一テストメソッド内では取得可能。