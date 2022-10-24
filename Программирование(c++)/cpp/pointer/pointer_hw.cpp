// Индивидуальное задание. Встроенные массивы.
// 2) Количество строк, содержащих хотя бы один нулевой элемент.
//==========================================================================================================
//Условия:
// 1. Если отсутствуют строки, содержащие нулевой элемент, сообщить об ошибке.
// 2. Если в файле присутствует тип, отличный от целочисленного, сообщить об ошибке.
// 3. В файле содержится размерность массива (количество строк и столбцов), а так же сам массив.
//===========================================================================================================
// Содержание файла pointer_hw.txt:
// 3 5
// 1 -4 3 0 0 5 0 5 2 4 1 1 5 -1 8
//===========================================================================================================
// Пример работы программы:
// 1 -4 3 0 0
// 5 0 5 2 4
// 1 1 5 -1 8
// The number of lines, that include zero: 2
//===========================================================================================================

#include <fstream>
#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;
const string fileName = "C:\\Users\\alinapotapova\\Documents\\cpp\\pointer\\pointer_hw.txt"; //путь к файлу
const string FILE_ERROR = "File open error!"; //сообщение об ошибке, в случае, если файл не открыт
const string INT_ERROR = "Invalid type in file!"; //сообщение об ошибке, в случае, если в файле присутствует тип, отличный от целочисленного
const string NO_ZERO_ERROR = "There are no lines in the file containing zero."; //сообщение об ошибке, в случае, если отсутствуют строки, содержащие нулевой элемент

//функция вывода двумерного массива(матрицы) из файла
void outMatrix(int** arr, const int n, const int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cout << *(*(arr + i) + j) << " ";
        cout << "\n";
    }
}
//функция поиска нуля в строках
int cArray(int **array, const int n, const int m)
{
    int count = 0; // количество строк, содержащих хотя бы один нулевой элемент
    bool foundZero = false; // переменная, которая в случае истинного значения способствует выходу из цикла
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (foundZero == false)
            {
                if (*(*(array + i) + j) == 0)
                {
                    count ++;
                    foundZero = true; // найден ноль, выход из цикла => переход на другую строку
                }
            }
        }
        foundZero = false;
    }
    if (count == 0)
        throw NO_ZERO_ERROR;
    else
        return count;
}

int main()
{
    try
    {
        ifstream file;
        file.open("pointer_hw.txt");
        if (!file.is_open())
        {
            throw FILE_ERROR;
        }
        int line = 0; //количество строк
        int column = 0; //количество столбцов
        file >> line; //считывание количества строк
        if (!file)
        {
            throw INT_ERROR;
        }
        file >> column; //считывание количества столбцов
        if (!file)
        {
            throw INT_ERROR;
        }
        int** arrayDin = new int* [line];
        for (int i = 0; i < line; ++i)
            arrayDin[i] = new int[column];

        for (int i = 0; i < line; ++i)
        {
            for (int j = 0; j < column; ++j)
            {
                file >> *(*(arrayDin + i) + j); //считывание элементов массива
                if (!file)
                {
                    throw INT_ERROR;
                }
            }
        }
        outMatrix(arrayDin, line, column); //вывод двумерного массива
        cArray(arrayDin, line, column);
        cout << "The number of lines, that include zero: " << cArray(arrayDin, line, column) << endl;
    }
    catch (const string & errorString)
    {
        cerr << endl << errorString << endl;
        return -1;

    }
}

// Индивидуальное задание. Массивы в динамической памяти.
// 2) Число локальных минимумов. Элемент матрицы называется локальным минимумом, если он строго меньше всех имеющихся у него соседей.
//==========================================================================================================
//Условия:
// 1. Если отсутствуют строки, содержащие нулевой элемент, сообщить об ошибке.
// 2. Если в файле присутствует тип, отличный от целочисленного, сообщить об ошибке.
// 3. В файле содержится размерность массива (количество строк и столбцов), а так же сам массив.
//===========================================================================================================
// Содержание файла pointer_hw.txt:
// 8
// 5 0 4 6 2 0 9 6 6 6 2 9 9 8 4 4 8 3 0 8 8 7 5 8 9 1 6 0 1 2 9 2 9 7 0 7 1 4 7 4 2 6 4 7 7 6 4 4 9 3 6 3 4 6 7 8 5 6 4 8 5 5 6 0 7 3 4 8 9 7 3 4
//===========================================================================================================
// Пример работы программы:
// 1 -4 3 0 0
// 5 0 5 2 4
// 1 1 5 -1 8
// The number of lines, that include zero: 2
//===========================================================================================================

#include <fstream>
#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;
const string fileName = "C:\\Users\\alinapotapova\\Documents\\cpp\\pointer\\pointer_hw_1.txt"; //путь к файлу
const string FILE_ERROR = "File open error!"; //сообщение об ошибке, в случае, если файл не открыт
const string INT_ERROR = "Invalid type in file!"; //сообщение об ошибке, в случае, если в файле присутствует тип, отличный от целочисленного

//функция вывода двумерного массива (матрицы) из файла
void outMatrix(int** arr, const int sArray)
{
    for (int i = 0; i < sArray; i++)
    {
        for (int j = 0; j < sArray; j++)
            cout << *(*(arr + i) + j) << " ";
        cout << "\n";
    }
}

int localLows(int **arr, const int s)
{
    int count = 0;
    for (int i = 0; i < s; i++)
    {
        for (int j = 0; j < s; j++)
        {
            if ((i == 0 || j == 0 || *(*(arr + i) + j) < *(*(arr + i - 1) + j - 1)) && //сравнение с левым верхним элементом
                (i == 0 || *(*(arr + i) + j) < *(*(arr + i - 1) + j)) && //сравнение верхним элементом
                (i == 0 || j == s - 1 || *(*(arr + i) + j) < *(*(arr + i - 1) + j + 1)) && //сравнение с правым верхним элементом
                (j == 0 || *(*(arr + i) + j) < *(*(arr + i) + j - 1)) && //сравнение с левым элементом
                (j == s - 1 || *(*(arr + i) + j) < *(*(arr + i) + j + 1)) && //сравнение с правым элементом
                (i == s - 1 || j == 0 || *(*(arr + i) + j) < *(*(arr + i + 1) + j - 1)) && //сравнение с левым нижним элементом
                (i == s - 1 || *(*(arr + i) + j) < *(*(arr + i + 1) + j)) && //сравнение с нижним элементом
                (i == s - 1 || j == s - 1 || *(*(arr + i) + j) < *(*(arr + i + 1) + j + 1))) //сравнение с правым нижним элементом
                count++;
        }
    }
    return count;
}

int main()
{
    try
    {
        ifstream file;
        file.open("pointer_hw_1.txt");
        if (!file.is_open())
        {
            throw FILE_ERROR;
        }
        int sizeArray = 0; //размерность массива
        file >> sizeArray;
        if (!file)
        {
            throw INT_ERROR;
        }
        int** arrayDin = new int* [sizeArray];
        for (int i = 0; i < sizeArray; ++i)
            arrayDin[i] = new int[sizeArray];

        for (int i = 0; i < sizeArray; ++i)
        {
            for (int j = 0; j < sizeArray; ++j)
            {
                file >> *(*(arrayDin + i) + j); //считывание элементов массива
                if (!file)
                {
                    throw INT_ERROR;
                }
            }
        }
        outMatrix(arrayDin, sizeArray); //вывод двумерного массива
        cout << "Number of local lows in the matrix: " << localLows(arrayDin, sizeArray) << endl;
    }
    catch (const string & errorString)
    {
        cerr << endl << errorString << endl;
        return -1;

    }
}


