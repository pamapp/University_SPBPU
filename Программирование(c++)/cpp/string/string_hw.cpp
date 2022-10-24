
//7. Определить, сколько различных букв латинского алфавита содержится в строке.
//==========================================================================================================
//Условия:
// 1. Если строка не содержит буквы латинского алфавита, сообщить об ошибке.
// 2. Если строка пустая, сообщить об ошибке.
// 3. В файле содержится одна строка и ее максимальный размер.
// 4. Заглавные и строчные буквы считаются различными. 
//===========================================================================================================
// Содержание файла string_text.txt:
// 256
// This is my string!
//===========================================================================================================
// Пример работы программы:
// Number of Lattin letters per c string: 9
// Number of Lattin letters per c++ string: 9
//===========================================================================================================

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>

using namespace std;

const string fileName = "C:\\Users\\alinapotapova\\Documents\\cpp\\string\\string_text.txt"; //путь к файлу
const string NO_LATIN_LETTERS = "There are no lattin letters in string."; //в строке отсутствуют буквы латинского алфавита
const string EMPTY_STRING = "Empty string."; //пустая строка

//строки в стиле C
int cStringsLattin (const char *str)
{
    int lattinLetters = 0; //количество латинских букв
    int counter[256] = {0}; //счетчик
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (isalpha(str[i]) == true) //возвращает ненулевое значение, если её аргумент является буквой, в противном случае возвращается нуль.
            counter[str[i]]++; 
    }
    for (int i = 1; i < 256; i++)
    {
        if (counter[i] != 0)
            lattinLetters++;
    }
    if (str[0] == '\0')
        throw EMPTY_STRING;
    if (lattinLetters != 0)
        return lattinLetters;
    else
        throw NO_LATIN_LETTERS;
}


//строки типа string
int sLattin (string& str)
{
    int lattinLetters = 0; //количество латинских букв
    int counter[256] = {0}; //счетчик
    for (int i = 0; i < str.size(); i++)
    {
        if (isalpha(str[i]) == true) //возвращает ненулевое значение, если её аргумент является буквой, в противном случае возвращается нуль.
            counter[str[i]]++;
    }
    for (int i = 1; i < 256; i++)
    {
        if (counter[i] != 0)
            lattinLetters++;
    }
    if (str[0] == '\0')
        throw EMPTY_STRING;
    if (lattinLetters != 0) 
        return lattinLetters;
    else
        throw NO_LATIN_LETTERS;
}

//главная функция
int main ()
{
    try
    {
        int nCharInFile = 0;
        fstream file;
        file.open("string_text.txt");//динамическая строка считанная из файла
        file >> nCharInFile;
        char *cStr = new char[nCharInFile];
        for (int i = 0; i < nCharInFile; i++)
            file >> cStr[i];

        file.close();
        cout << "Number of Lattin letters per c string: " << cStringsLattin(cStr) << endl;

        string sStr("This is my string!"); //строка типа string
        cout << "Number of Lattin letters per c++ string: " <<  sLattin(sStr) << endl;

   
    }
    catch (const string & errorString)
    {
        cerr << endl << errorString << endl;
        return -1;

    }
}
