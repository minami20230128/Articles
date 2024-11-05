//・変なカレンダー

#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <array>

class SgStrangeCalender
{
    public:
    SgStrangeCalender(int year)
    {
        for(int i = 1; i <= 12; i++)
        {
            auto month_calender = this->GenerateEachMonthCalender(year, i);

            for(auto&& date : month_calender)
            {
                std::cout << date << std::endl;
            }
        }
    }

    private:
    const std::array<std::string, 12> month_names = {
            "Jan", "Feb", "Mar", "Apr", "May", "Jun",
            "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
        };

    std::vector<std::string> GenerateEachMonthCalender(int year, int month)
    {
        //各月の最初の日の曜日を求める
        int weekDay = this->DayOfWeek(year, month, 1);
        //各月の日数を求める
        unsigned int dayNum = this->DayNumInMonth(year, month);
        std::cout << dayNum << std::endl;
        //0番目の要素が月名の配列を作る
        std::vector<std::string> month_calender{this->month_names[month - 1]};
        //1日の曜日が日曜なら1番目、月曜なら2番目...から順に配列に日付を格納していく

        for(int i = 1; i <= weekDay; i++)
        {
            month_calender.push_back("");
        }

        int date = 1;
        for(int i = 0; i < dayNum; i++)
        {
            month_calender.push_back(std::to_string(date));
            date++;
        }

        return month_calender;
    }

    int DayOfWeek(int y, unsigned int m, unsigned int d)
    {
        std::chrono::year year{y};
        std::chrono::month month{m};
        std::chrono::day day{d};

        std::chrono::year_month_day ymd{year/month/day};
        auto sys_days = std::chrono::sys_days{ymd};
        std::chrono::weekday wd = std::chrono::weekday{sys_days};

        return wd.c_encoding();
    }

    unsigned int DayNumInMonth(int y, unsigned int m)
    {
        std::chrono::year year{y};
        std::chrono::month month{m};

        std::chrono::year_month_day_last ymdl{year/month/std::chrono::last};
        auto day = ymdl.day();

        return static_cast<unsigned int>(day);
    }

};

int main()
{
    SgStrangeCalender* sgStangeCalender = new SgStrangeCalender(2024);

    return 0;
}