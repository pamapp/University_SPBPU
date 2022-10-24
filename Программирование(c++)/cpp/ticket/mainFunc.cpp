
#include <iostream>
#include <math.h>
#include <string>
#include <fstream>

#include "flightNumberChecking.h"
#include "nameChecking.h"
#include "dateChecking.h"

using namespace std;

const string fileName = "C:\\Users\\alinapotapova\\Documents\\cpp\\ticket\\text.txt";
const string FILE_ERROR = "File open error!";
const string VALUE_ERROR = "Invalid value in file!";
const string NAME_ERROR = "Ошибка: некорректное имя!";
const string SURNAME_ERROR = "Ошибка: некорректная фамилия!";
const string DISTANATION_ERROR = "Ошибка: некорректный пункт назначния!";
const string DATE_ERROR = "Ошибка: некорректная дата!";
const string FLIGHT_NUMBER_ERROR = "Ошибка: некорректный номер рейса!";

template <typename T1, typename T2, typename T3, typename T4, typename T5>
class MyClass
{
    private:
        T1 _name;
        T2 _surname;
        T3 _distanation;
        T4 _date;
        T5 _flightNumber;
    public:
        MyClass (T1 name, T2 surname, T3 distanation, T4 date, T5 flightNumber)
        {
            this ->_name = name;
            this ->_surname = surname;
            this ->_distanation = distanation;
            this ->_date = date;
            this ->_flightNumber = flightNumber;
        }
        
        void DataTypeSize ()
        {
            cout << _name.size() << endl;
            cout << _surname.size() << endl;
            cout << _distanation.size() << endl;
            cout << _date.size() << endl;
            cout << _flightNumber.size() << endl;
        }
    
    
};
int main()
{
    try
    {
        string n1 = "Ivanov";
        string s1 = "Sidr";
        string d1 = "Surgut";
        string d2 = "10.12.2012";
        string f1 = "SJ1234";
        
        MyClass<string, string, string, string, string> c(n1, s1, d1, d2, f1);
        c.DataTypeSize();
        
        
        
//        cout << "Result of cheking: " << endl;
//        unsigned int currentItem = 0;
//        if (isNameOrSurnameOrDistanation(n1, currentItem))
//            cout << n1 << endl;
//        else
//            throw NAME_ERROR;
//        currentItem = 0;
//
//
//        if (isNameOrSurnameOrDistanation(s1, currentItem))
//            cout << s1 << endl;
//        else
//            throw NAME_ERROR;
//        currentItem = 0;
//
//
//        if (isNameOrSurnameOrDistanation(d1, currentItem))
//            cout << d1 << endl;
//        else
//            throw NAME_ERROR;
//        currentItem = 0;
//
//
//        if (isDate(d2, currentItem))
//            cout << d2 << endl;
//        else
//            throw SURNAME_ERROR;
//        currentItem = 0;
//
//
//        if (isFlightNumber(f1, currentItem))
//            cout << f1 << endl;
//        else
//            throw SURNAME_ERROR;
//        currentItem = 0;
//        cout << endl;

        
        
        return 0;
    }
    catch (const string & errorString)
    {
        cerr << endl << errorString << endl;
        return -1;
    }
}

