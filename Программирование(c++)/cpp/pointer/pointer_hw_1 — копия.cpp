
// Индивидуальное задание. Массивы в динамической памяти.
// 2) Число локальных минимумов. Элемент матрицы называется локальным минимумом, если он строго меньше всех имеющихся у него соседей.
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
#define sizeArray 8
using namespace std;
const string fileName = "C:\\Users\\alinapotapova\\Documents\\cpp\\pointer\\pointer_hw_1.txt"; //путь к файлу
const string FILE_ERROR = "File open error!"; //сообщение об ошибке, в случае, если файл не открыт
const string INT_ERROR = "Invalid type in file!"; //сообщение об ошибке, в случае, если в файле присутствует тип, отличный от целочисленного
const string NO_ZERO_ERROR = "There are no lines in the file containing zero."; //сообщение об ошибке, в случае, если отсутствуют строки, содержащие нулевой элемент

////функция вывода двумерного массива (матрицы) из файла
//void outMatrix(int** arr, const int sArray)
//{
//    for (int i = 0; i < sArray; i++)
//    {
//        for (int j = 0; j < sArray; j++)
//            cout << *(*(arr + i) + j) << " ";
//        cout << "\n";
//    }
//}

int funcMin(int** arr, const int s)
{
    int localMin = 0;
    int lineUp = 0;
    int lineDown = 0;
    int columnRight = 0;
    int columnLeft = 0;
    bool e = 1;
    for (int i = 0; i < s; ++i)
    {
       for (int j = 0; j < s; ++j)
       {
           if (i == 0)
               lineUp = i;
           else
               lineUp = i - 1;
           if (j == 0)
               columnLeft = j;
           else
               columnLeft = j - 1;
           if (i < (s - 1))
               lineDown = i + i;
           else
               lineDown = i;
           if (j < (s - 1))
               columnRight = i + i;
           else
               columnRight = j;
           for (int line = lineUp; line <= lineDown; line++)
           {
                   for (int column = columnLeft; column <= columnRight; column++)
                   {
                       if (arr[line][column] <= arr[i][j] && (i != line || j != column))
                           break;
                   }
           }
           localMin++;
        }
    }
    return localMin;
}

int main()
{
    try
    {
        int mas[sizeArray][sizeArray];
        cout << "Matrix :"<<endl;
        for(int i = 0; i < sizeArray; i++)
        {
            for(int j = 0; j < sizeArray; j++)
            {
                mas[i][j] = rand() % 100 - 10;
                cout<<mas[i][j]<<"  ";
            }
            cout<<endl;
        }
//        outMatrix(arrayDin, sizeArray); //вывод двумерного массива
        cout << "MinLocal: " << funcMin(mas, sizeArray);
    }
    catch (const string & errorString)
    {
        cerr << endl << errorString << endl;
        return -1;

    }
}


int IsLocalMinimum(int **matrix, int matrix_size, size_t i, size_t j) {
  size_t k, l;
  size_t k_from = ((i == 0) ? i : i - 1);
  size_t l_from = ((j == 0) ? j : j - 1);
  size_t k_to   = ((i < (matrix_size - 1)) ? i + 1 : i);
  size_t l_to   = ((j < (matrix_size - 1)) ? j + 1 : j);
  for (k = k_from; k <= k_to; ++k)
    for (l = l_from; l <= l_to; ++l)
      if (matrix[k][l] <= matrix[i][j] && (i != k || j != l))
        e = 0;
  e = 1;
}
