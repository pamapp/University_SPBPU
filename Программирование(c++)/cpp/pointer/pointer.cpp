#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;
const string INT_ERROR = "Integer type expected!"; //сообщение об ошибке, в случае, если введено не целое число
const string QUANLITY_ERROR = "Enter quality greater than zero!"; //сообщение об ошибке, в случае, если введенное значение противоречит условию задачи

void inArray (int *array, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> *(array + i*m + j);
            if (!cin)
                throw INT_ERROR;
        }
    }
}

void outArray (const int *array, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cout << *(array + i*m + j) << endl;
    }
}

void outArrayDin (int **array, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cout << *(*(array + i) + j) << endl;
    }
}

// void numberOfRowsOrdered (int **array, int dinArray)
// void isOrderArray(const int *array, const int nArray) //порядок по возрастанию
// {
//     int count = 0;
//     int minArray = array[0];
//     bool flag = false;
//     cout << "Elements in ascending order." << endl;
//     for (int i = 1; i < nArray; ++i)
//     {
//         if (array[i] > minArray)
//         {
//             minArray = array[i];
//             count = count + 1;
//         }
//     }
//     if (count == (nArray - 1))
//     {
//         flag = true;
//         cout << flag << endl;
//     }
//     else
//         cout << flag << endl;
//     cout << endl;
// }
int main()
{
    try
    {
        const int N = 2;
        const int M = 2;
        int array[N][M];
        inArray(*array, N, M);
        
        int A = 0;
        int B = 0;
        cout << "Enter the number of columns adn lines: ";
        cin >> A >> B;
        if (!cin)
            throw INT_ERROR;
        if (A < 0 or B < 0)
            throw QUANLITY_ERROR;
        int** dinArray = new int*[A];
        for (int i = 0; i < A; i++)
            dinArray[i] = new int[M];
        inArrayDin(dinArray, A, B);
        
        
        cout << "Your array:" << endl;
        outArray(*array, N, M);
        cout << "Your dinamic array:" << endl;
        outArrayDin(dinArray, A, B);
        
        
    }
    catch (const string & errorString)
    {
        cerr << endl << errorString << endl;
        return -1;

    }
    
    
}



void inArrayDin (int **array, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> *(*(array + i) + j);
            if (!cin)
                throw INT_ERROR;
        }
    }
}