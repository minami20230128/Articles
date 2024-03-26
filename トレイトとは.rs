//・トレイトとは
//ある手続きの塊をひとまとめにしたもので、複数のクラスによって実装される
//Interfaceと異なり、具象メソッドをメンバーに持つことができる
//これにより、異なるクラスの共通処理をひとまとめにすることができる

//たとえば、以下はある店の夏期と通常期の割引率を求めるコードである
//この店には客の年齢を割引率に反映する独自のシステムがあり、季節にかかわらず常に同じロジックで計算される
//このようなとき、年齢による割引率の計算ロジックをtraitで実装し、夏期と通常期のクラスに継承させることで共通化を図ることができる

pub struct RegularDiscountedPrice
{
    
}

impl RegularDiscountedPrice
{
    pub fn get_discounted_price(price : i32) -> i32{
        const DISCOUNT_RATE : f64 = 0.1;
        return DISCOUNT_RATE * price;
    }
}

pub struct SummerDiscountedPrice
{
    
}

impl SummerDiscountedPrice
{
    pub fn get_discounted_price(price : i32) -> i32{
        const DISCOUNT_RATE : f64 = 0.12;
        return DISCOUNT_RATE * price;
    }
}

trait DiscountRateByAge
{
    fn get_discounted_price(age : i32) -> f32;
}

impl DiscountRateByAge for RegularDiscountedPrice
{
    fn get_discounted_price(age : i32) -> f32{
        return 1 + age / 100;
    }
}

impl DiscountRateByAge for SummerDiscountedPrice
{
    fn get_discounted_price(age : i32) -> f32{
        return 1 + age / 100;
    }
}