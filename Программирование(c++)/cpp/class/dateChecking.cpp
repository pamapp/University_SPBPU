//#include <iostream>
//
//using namespace std;
//
//const string DAY_ERROR = "Error: invalid day!";
//const string MONTH_ERROR = "Error: invalid month!";
//const string YEAR_ERROR = "Error: invalid year!";
//const string FEBRUARY_EXCEPTION = "Error: there are not so many days in February!";
//const string FLIGHT_NUMBER_ERROR = "Ошибка: некорректный номер рейса!";
//
//class Date
//{
//private:
//    int day;
//    int month;
//    int year;
//public:
//    Date(): day(0), month(0), year(0) {}
//    Date (int d = 0, int m = 0, int y = 0)
//    {
//        day = d;
//        month = m;
//        year = y;
//    }
//    int day_()
//    {
//        return day;
//    }
//    int month_()
//    {
//        return month;
//    }
//    int year_()
//    {
//        return year;
//    }
//    void setDay(int daY)
//    {
//        day = daY;
//    }
//    void setMonth(int montH)
//    {
//        month = montH;
//    }
//    void setYear(int yeaR)
//    {
//        year = yeaR;
//    }
//    friend ostream& operator<<(ostream &out, Date &date);
//    friend bool checkCorrection(Date &date);
//};
//
//bool checkCorrection(Date &date)
//{
//    if (( date.day < 1 || date.day > 31 ) or  (date.month < 1 || date.month > 12 ) or ( date.day > 30 + date.month % 2 && date.month < 8) or ( date.day <= 30 + date.month % 2 && date.month >= 8) or (date.month == 2 && date.year % 4 == 0 && date.day > 29) or (date.year % 4 != 0 && date.month == 2 && date.day > 28))
//    {
//        return false;
//    }
//    else
//    {
//        return true;
//    }
//
//
//
//}
//
//ostream& operator<<(ostream &out, Date &date)
//{
//    if (date.day < 10 and date.month > 10)
//        out << "0" << date.day << "." << date.month << "." << date.year << endl;
//    else if (date.day > 10 and date.month < 10)
//        out << date.day << "." << "0" << date.month << "." << date.year << endl;
//    else if (date.day < 10 and date.month < 10)
//        out << "0" << date.day << "." << "0" << date.month << "." << date.year << endl;
//    else
//        out << date.day << "." << date.month << "." << date.year << endl;
//}
//
//int main()
//{
//    int d = 0;
//    int y = 0;
//    int m = 0;
//
//    Date date(d, m, y);
//    cout << "Enter the date: " << endl;
//    cin >> d >> m >> y;
//
//    date.setDay(d);
//    date.setMonth(m);
//    date.setYear(y);
//
//    if (checkCorrection(date) == true)
//        cout << "Yout date: " << date;
//    else
//        cout << "WRONG DATE!" << endl;
//}


#include <iostream>
#include <math.h>
using namespace std;

class MyTime
{
private:
    int hour;
    int minute;
    int second;
public:
    MyTime(int h = 0, int m = 0, int s = 0)
    {
        hour = h;
        minute = m;
        second = s;
    }
    void setHours(int h_)
    {
        hour = h_;
    }
    void setMinuts(int m_)
    {
        minute = m_;
    }
    void setSeconds(int s_)
    {
        second = s_;
    }
    void NormTime(MyTime &time)
    {
        if (time.second > 59)
        {
            time.minute++;
            time.minute = time.minute - 60;
        }
        if (time.minute > 59)
        {
            time.hour++;
            time.minute = time.minute - 60;
        }
        if (time.hour >= 24)
        {
            time.hour = time.hour - 24;
        }
    }
    void decTimeSec(MyTime &time, int sec)
    {
        int toSeconds = 0;
        toSeconds = (time.hour * 60 * 60) + (time.minute * 60) + time.second;
        
        if (sec == 0)
        {
            toSeconds = toSeconds - 1;
            time.hour = toSeconds / 60 / 60;
            time.minute = (toSeconds - time.hour * 60 * 60) / 60;
            time.second = (toSeconds % 60 % 60) % 60;
        }
        
        if (sec > 0)
        {
            toSeconds = toSeconds - sec;
            time.hour = toSeconds / 60 / 60;
            time.minute = (toSeconds - time.hour * 60 * 60) / 60;
            time.second = (toSeconds % 60 % 60) % 60;
        }
    }
    friend ostream& operator<< (ostream &out, MyTime &time);
    friend MyTime compMyTime(MyTime &time1, MyTime &time2);
    friend bool operator<= (const MyTime &time1, const MyTime &time2);
};
ostream& operator<< (ostream &out, MyTime &time)
{
    out << time.hour << ":" << time.minute << ":" << time.second << endl;
}
MyTime compMyTime(MyTime &time1, MyTime &time2)
{
    int toSeconds1_ = 0;
    int toSeconds2_ = 0;
    toSeconds1_ = (time1.hour * 60 * 60) + (time1.minute * 60) + time1.second;
    toSeconds2_ = (time2.hour * 60 * 60) + (time2.minute * 60) + time2.second;
    if (toSeconds1_ > toSeconds2_)
    {
        cout << time1;
//        return time1;
    }
    else
    {
        cout << time2;
//        return time2;
    }
}
bool operator<= (const MyTime &time1, const MyTime &time2)
{
    int toSeconds1 = 0;
    int toSeconds2 = 0;
    toSeconds1 = (time1.hour * 60 * 60) + (time1.minute * 60) + time1.second;
    toSeconds2 = (time2.hour * 60 * 60) + (time2.minute * 60) + time2.second;
    return (toSeconds1 <= toSeconds2);
}
int main()
{
    int mazafaka = 0;
    int h1 = 0;
    int m1 = 0;
    int s1 = 0;
    
    int h2 = 0;
    int m2 = 0;
    int s2 = 0;
    
    MyTime t1(h1, m1, s1);
    MyTime t2(h1, m1, s1);
    
    cout << "Введите первое время:" << endl;
    cin >> h1 >> m1 >> s1;
    
    t1.setHours(h1);
    t1.setMinuts(m1);
    t1.setSeconds(s1);
    
//    t1.NormTime(t1);
//    cout << t1;

    
//    cout << "На какое время вы хотите уменьшить?" << endl;
//    cin >> mazafaka;
//
//    t1.decTimeSec(t1, mazafaka);
//    cout << "Ответ: " << t1 << endl;
    
    
    cout << "Введите второе время:" << endl;
    cin >> h2 >> m2 >> s2;
    
    t2.setHours(h2);
    t2.setMinuts(m2);
    t2.setSeconds(s2);
    
//    cout << "Первое время меньше или равно второму:" << endl;
//    if (t1 <= t2)
//    {
//        cout << "YES" << endl;
//    }
//    else
//    {
//        cout << "NO" << endl;
//    }
    cout << "Большее время: " << endl;
    compMyTime(t1, t2);

}
