#include <iostream>
#include <math.h>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <cctype>
#include <stdio.h>

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



class String
{
private:
    char* a_;
    int size_;
public:
    //конструкторы
    String()
    {
        a_ = nullptr;
        size_ = 0;
    }

    String(const char a[])
    {
        int n = 0;
        for (int n; a[n] != 0; ++n);
        a_ = new char[n];
        for (int i = 0; i < n; ++i)
        {
            a_[i] = a[i];
        }
        size_ = n;
    }

    String(int size)
    {
        if (size <= 0)
            throw "Invalid size!";
        a_ = new char[size];
        if (a_ == nullptr)
            throw "Memory allocation error!";
        size_ = size;
    }

    String(const String& temp)
    {
        a_ = new char[temp.size_];
        for (int i = 0; i < temp.size_; ++i)
        {
            a_[i] = temp.a_[i];
        }
        size_ = temp.size_;
    }
    
    //перегрузка опертора индексации
    char& operator[] (int i) const
    {
        if (i < 0 or i >= size_)
            throw "Array bounds violated!";
        return a_[i];
    }
    
    //диструктор
    ~String()
    {
        delete[] a_;
    }
    
    //метод, который возвращает размер строки
    unsigned int getSize() const
    {
        return size_;
    }
    
    //функция для подстрок
    String substr(const unsigned int first, const unsigned int last);

    //перегрузка операторов
    friend ostream& operator<<(ostream& out, const String& str);
    friend istream& operator>>(istream& in, String& str);

    
    bool operator== (const String& str) const;
    bool operator== (const char* str) const;

    String& operator= (const String& str);
    String& operator+ (const String& str) const;
    String& operator+ (const char& tempChar) const;
};

ostream& operator<<(ostream& out, const String& str)
{
    for (int i = 0; i < str.size_; ++i)
    {
        out << str.a_[i];
    }
    return out;
}

istream& operator>>(istream& in, String& str)
{
    char t;
    int size = 0;
    char* buf = new char[256];
    in >> noskipws;

    while (in >> t)
    {
        if (t == '\n')
            break;
        buf[size] = t;
        ++size;
    }
    buf[size] = '\0';

    str.a_ = buf;
    str.size_ = size;
    return in;
}

bool String::operator==(const String& str) const
{
    if (size_ != str.size_)
        return false;
    bool result = true;
    for (int i = 0; i < str.size_; ++i)
    {
        result *= (a_[i] == str.a_[i]);
    }
    return result;
}

bool String::operator==(const char* str) const
{
    unsigned int size;
    for (size = 0; str[size]; ++size);
    if (size_ != size)
        return false;
    bool result = true;
    for (int i = 0; i < size; ++i)
    {
        result &= (a_[i] == str[i]);
    }
    return result;
}

String& String::operator=(const String& str)
{
    if (&str == this)
        return *this; // проверка на самоприсваивание
    if (str.size_ == 0)
    {
        delete[] a_;
        a_ = nullptr;
        size_ = 0;
    }
    else
    {
        delete[] a_;
        a_ = new char[str.size_];
        if (a_ == nullptr)
            throw "Memory allocation error";
        size_ = str.size_;
        for (int i = 0; i < str.size_; i++)
            a_[i] = str.a_[i];
    }
    return *this;
}
//
//String& String::operator+(const String& str) const
//{
//    String temp(size_ + str.size_);
//    for (int i = 0; i < size_; ++i)
//    {
//        temp.a_[i] = a_[i];
//    }
//    for (int i = 0; i < str.size_; ++i)
//    {
//        temp.a_[size_ + i] = str.a_[i];
//    }
//    return temp;
//}
//
//String& String::operator+(const char& tempChar) const
//{
//    String temp(size_ + 1);
//    for (int i = 0; i < size_; ++i)
//    {
//        temp.a_[i] = a_[i];
//    }
//    temp.a_[size_] = tempChar;
//    return temp;
//}

String String::substr(const unsigned int first, const unsigned int last)
{
    if ((first > last) or (last > size_))
    {
        return "...";
    }

    String res;
    res.a_ = new char[last - first + 1];
    for (size_t i = first; i < last+1; i++)
    {
        res.a_[i - first] = a_[i];
    }
    res.size_ = last - first+1;
    return res;

}


bool isLetter (String& str , unsigned int& item)
{
    if (str[item] >= 'a' && str[item] <= 'z')
    {
        item++;
        return true;
    }
    else
        return false;
}

bool isCapital (String& str , unsigned int& item)
{
    if (str[item] >= 'A' && str[item] <= 'Z')
    {
        item++;
        return true;
    }
    else
        return false;
}

bool isDash (String& str , unsigned int& item)
{
    if (str[item] == '-')
    {
        item++;
        return true;
    }
    else
        return false;
}

bool isLetters (String& str , unsigned int& item)
{
    if (isLetter(str, item) == true)
    {
        if (isLetters(str, item) == true)
            return true;
        return true;
    }
    return false;
}

bool isNameOrSurnameOrDistanation (String& str , unsigned int& item)
{
    if (isCapital(str, item) == true)
    {
        if (isLetters(str, item) == true)
        {
            if (isDash(str, item) == true)
            {
                if (isCapital(str, item) == true)
                {
                    if (isLetters(str, item) == true)
                        return true;
                }
            }
            else
                return true;
        }
    }
    return false;
}


int main()
{
    try
    {
        String n1 = "I1vanov";

        unsigned int currentItem = 0;
        if (isNameOrSurnameOrDistanation(n1, currentItem))
            cout << n1 << endl;
        else
            throw NAME_ERROR;
        currentItem = 0;
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



















//template <typename T1>
//
//class MyClass
//{
//    private:
//        T1 *_name;
//        int _size;
//    public:
//        MyClass(T1 *_name)  //конструктор принимает строку текста
//        {
//            _size = strlen(_name);
//            _name = new T1[_size + 1]; //массив размера char
//
//            strcpy(_name, _name); //копирует содержимое str в pStr
//
//        }
////
//        void DataTypeSize()
//        {
//            _size = strlen(_name);
//            cout << _size << endl;
//        }
//
//        void Output()
//        {
//
//            for (int i = 0; i < strlen(_name); i++)
//            {
//                cout << _name[i];
//            }
//
//        }
////        void massiv(char* _name, int _size)
////        {
////            for (int i = 0; _name[_size] != "\0"; i++)
////                _name[i] = new char[_size];
////        }
//
//};
//
//int main()
//{
//    try
//    {
//        char n1[256] = "Ivanfov";
//
//        MyClass <char> c(n1);
//        c.DataTypeSize();
//        c.Output();
//
//
//
////        cout << "Result of cheking: " << endl;
////        unsigned int currentItem = 0;
////        if (isNameOrSurnameOrDistanation(n1, currentItem))
////            cout << n1 << endl;
////        else
////            throw NAME_ERROR;
////        currentItem = 0;
////
////
////        if (isNameOrSurnameOrDistanation(s1, currentItem))
////            cout << s1 << endl;
////        else
////            throw NAME_ERROR;
////        currentItem = 0;
////
////
////        if (isNameOrSurnameOrDistanation(d1, currentItem))
////            cout << d1 << endl;
////        else
////            throw NAME_ERROR;
////        currentItem = 0;
////
////
////        if (isDate(d2, currentItem))
////            cout << d2 << endl;
////        else
////            throw SURNAME_ERROR;
////        currentItem = 0;
////
////
////        if (isFlightNumber(f1, currentItem))
////            cout << f1 << endl;
////        else
////            throw SURNAME_ERROR;
////        currentItem = 0;
////        cout << endl;
//
//
//
//        return 0;
//    }
//    catch (const string & errorString)
//    {
//        cerr << endl << errorString << endl;
//        return -1;
//    }
//}

