#include <iostream>

using namespace std;

const string DAY_ERROR = "Error: invalid day!";
const string MONTH_ERROR = "Error: invalid month!";
const string YEAR_ERROR = "Error: invalid year!";
const string FEBRUARY_EXCEPTION = "Error: there are not so many days in February!";
const string FLIGHT_NUMBER_ERROR = "Ошибка: некорректный номер рейса!";

class Date
{
private:
    int day;
    int month;
    int year;
public:
    Date(): day(0), month(0), year(0) {}
    Date (int d = 0, int m = 0, int y = 0)
    {
        day = d;
        month = m;
        year = y;
    }
    int day_()
    {
        return day;
    }
    int month_()
    {
        return month;
    }
    int year_()
    {
        return year;
    }
    void setDay(int daY)
    {
        day = daY;
    }
    void setMonth(int montH)
    {
        month = montH;
    }
    void setYear(int yeaR)
    {
        year = yeaR;
    }
    friend ostream& operator<<(ostream &out, Date &date);
    friend bool checkCorrection(Date &date);
};

bool checkCorrection(Date &date)
{
    if (( date.day < 1 || date.day > 31 ) or  (date.month < 1 || date.month > 12 ) or ( date.day > 30 + date.month % 2 && date.month < 8) or ( date.day <= 30 + date.month % 2 && date.month >= 8) or (date.month == 2 && date.year % 4 == 0 && date.day > 29) or (date.year % 4 != 0 && date.month == 2 && date.day > 28))
    {
        return false;
    }
    else
    {
        return true;
    }
        


}

ostream& operator<<(ostream &out, Date &date)
{
    if (date.day < 10 and date.month > 10)
        out << "0" << date.day << "." << date.month << "." << date.year << endl;
    else if (date.day > 10 and date.month < 10)
        out << date.day << "." << "0" << date.month << "." << date.year << endl;
    else if (date.day < 10 and date.month < 10)
        out << "0" << date.day << "." << "0" << date.month << "." << date.year << endl;
    else
        out << date.day << "." << date.month << "." << date.year << endl;
}

int main()
{
    int d = 0;
    int y = 0;
    int m = 0;
    
    Date date(d, m, y);
    cout << "Enter the date: " << endl;
    cin >> d >> m >> y;
    
    date.setDay(d);
    date.setMonth(m);
    date.setYear(y);
        
    if (checkCorrection(date) == true)
        cout << "Yout date: " << date;
    else
        cout << "WRONG DATE!" << endl;
}
