//・トレイトとは
//ある手続きの塊をひとまとめにしたもので、複数のクラスによって実装される。
//Interfaceと異なり、具象メソッドをメンバーに持つことができる。
//これにより、異なるクラスの共通処理をひとまとめにすることができる。

//たとえば、以下はある店の夏期と通常期の割引率を求めるコードである。
//この店には客の年齢を割引率に反映する独自のシステムがあり、季節にかかわらず常に同じロジックで計算される。
//このようなとき、年齢による割引率の計算ロジックをtraitで実装し、夏期と通常期のクラスに継承させることで共通化を図ることができる。

pub struct RegularDiscountedPrice
{
    rate_by_age : f32
}

impl RegularDiscountedPrice
{
    pub fn get_discounted_price(&self, age : i32, price : i32) -> i32{
        let rate_by_age = self.get_discount_rate(age);
        const DISCOUNT_RATE : f32 = 0.1;
        return ((1.0 - DISCOUNT_RATE * rate_by_age) * price as f32).ceil() as i32;
    }
}

pub struct SummerDiscountedPrice
{
    rate_by_age : f32
}

impl SummerDiscountedPrice
{
    pub fn get_discounted_price(&self, age : i32, price : i32) -> i32{
        let rate_by_age = self.get_discount_rate(age);
        const DISCOUNT_RATE : f32 = 0.12;
        return ((1.0 - DISCOUNT_RATE * rate_by_age) * price as f32).ceil() as i32;
    }
}

trait DiscountRateByAge
{
    fn get_discount_rate(&self, age : i32) -> f32;
}

impl DiscountRateByAge for RegularDiscountedPrice
{
    fn get_discount_rate(&self, age : i32) -> f32{
        return 1.0 + (age / 100) as f32;
    }
}

impl DiscountRateByAge for SummerDiscountedPrice
{
    fn get_discount_rate(&self, age : i32) -> f32{
        return 1.0 + (age / 100) as f32;
    }
}

fn main()
{
    let regular = RegularDiscountedPrice{rate_by_age : 0.0};
    let summer = SummerDiscountedPrice{rate_by_age : 0.0};

    let age = 20;
    let price = 400;

    println!("Regular : {}", regular.get_discounted_price(age, price));
    println!("Regular : {}", summer.get_discounted_price(age, price));
}

//出力結果
//352
//360