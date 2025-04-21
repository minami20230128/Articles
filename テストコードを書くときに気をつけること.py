# テストコードを書くときに気をつけること

# テストしやすい小さい関数を作るためには「責務を一つに絞れ」とよく言われるが、分かりにくいので調べてみた。

# （PJの状況にもよるので絶対の正解はないが、）とりあえずこのあたりが基準になる？
# ・関数を境界値で分ける
# ・ビジネスドメインに基づき、意味のある最小単位で分割する

# 以下、この基準を使って分割してみる。

# 例題：ユーザーの年齢でカテゴリを判定する関数
# 要件
# 入力としてユーザーの年齢（整数）を受け取り、以下のカテゴリを返す関数を作る。
# 
# 0歳未満 → "invalid"
# 
# 0歳〜12歳 → "child"
# 
# 13歳〜19歳 → "teen"
# 
# 20歳〜64歳 → "adult"
# 
# 65歳以上 → "senior"

import pytest

class AgeJudgement:
    def is_child(self, age):
        return 0 <= age < 13

    def is_teen(self, age):
        return 13 <= age < 20

    def is_adult(self, age):
        return 20 <= age < 65

    def is_senior(self, age):
        return age >= 65

    def judge(self, age):
        if age < 0:
            return "invalid"
        elif self.is_child(age):
            return "child"
        elif self.is_teen(age):
            return "teen"
        elif self.is_adult(age):
            return "adult"
        elif self.is_senior(age):
            return "senior"
        

def test_invalid():
    judgement = AgeJudgement()
    assert judgement.judge(-1) == "invalid"

def test_child():
    judgement = AgeJudgement()
    assert judgement.is_child(12) == "child"
    
def test_teen():
    judgement = AgeJudgement()
    assert judgement.is_teen(19) == "teen"

def test_adult():
    judgement = AgeJudgement()
    assert judgement.is_adult(64) == "adult"

def test_senior():
    judgement = AgeJudgement()
    assert judgement.is_senior(65) == "senior"