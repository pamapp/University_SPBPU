
#include <iostream>
#include <math.h>
#include <string>
#include <sstream>
#ifndef NAME_CHECKING_H
#define NAME_CHECKING_H

using namespace std;

//проверка ИФ и Города
//ИМЯ:= <ЗАГЛАВНАЯ> <БУКВЫ> | <ЗАГЛАВНАЯ> <БУКВЫ> <ТИРЕ> <ЗАГЛАВНАЯ> <БУКВЫ>
//ТИРЕ:= <->
//ЗАГЛАВНАЯ:= <A> | <B> | <C> | .. | <Z>
//БУКВЫ:= <БУКВА> | <БУКВЫ> <БУКВА>
//БУКВА:= <a> | <b> | <c> | .. | <z>

bool isLetter (const char* str, unsigned int& item)
{
    if (str[item] >= 'a' && str[item] <= 'z')
    {
        item++;
        return true;
    }
    else
        return false;
}

bool isCapital (const char* str, unsigned int& item)
{
    if (str[item] >= 'A' && str[item] <= 'Z')
    {
        item++;
        return true;
    }
    else
        return false;
}

bool isDash (const char* str, unsigned int& item)
{
    if (str[item] == '-')
    {
        item++;
        return true;
    }
    else
        return false;
}

bool isLetters (const char* str, unsigned int& item)
{
    if (isLetter(str, item) == true)
    {
        if (isLetters(str, item) == true)
            return true;
        return true;
    }
    return false;
}

bool isNameOrSurnameOrDistanation (const char* str, unsigned int& item)
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

#endif //NAME_CHECKING_H
