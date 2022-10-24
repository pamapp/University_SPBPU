
#include <iostream>
#include <math.h>
#include <string>
#include <sstream>
#ifndef FLIGHT_NUMBER_CHECKING_H
#define FLIGHT_NUMBER_CHECKING_H

using namespace std;

//проверка Рейса
//ИМЯ:= <ЦИФРЫ> <БУКВЫ>
//ЦИФРЫ:= <ЦИФРА> <ЦИФРЫ>
//ЦИФРА:= <0> | <1> | <2> | .. | <9>
//БУКВЫ:= <БУКВА> <БУКВЫ>
//БУКВА:= <A> | <B> | <C> | .. | <Z>

bool isLetterD (const char* str, unsigned int& item)
{
    if (item < 2)
    {
        if (str[item] >= 'A' && str[item] <= 'Z')
        {
            item++;
            return true;
        }
    }
    return false;
}


bool isNumberD (const char* str, unsigned int& item)
{
    if (item >= 2 and item < 6)
    {
        if (str[item] >= '0' and str[item] <= '9')
        {
            item++;
            return true;
        }
    }
    return false;
}

bool isLettersD (const char* str, unsigned int& item)
{
    if (isLetterD(str, item) == true)
    {
        if (isLettersD(str, item) == true)
            return true;
        return true;
    }
    return false;
}

bool isNumbersD (const char* str, unsigned int& item)
{
    if (isNumberD(str, item) == true)
    {
        if (isNumbersD(str, item) == true)
            return true;
        return true;
    }
    return false;
}

bool isFlightNumber (const char* str, unsigned int& item)
{
    if (isLettersD(str, item) == true)
    {
        if (isNumbersD(str, item) == true)
            return true;
    }
    return false;
}

bool is_(const char* str, unsigned int& item)
{
     if (str[item] == '_')
     {
        item++;
        return true;
     }
     else
     return false;
}

#endif //FLIGHT_NUMBER_CHECKING_H
