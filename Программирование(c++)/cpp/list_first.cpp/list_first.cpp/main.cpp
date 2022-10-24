#include <iostream>
#include "MyList.h"
using namespace std;
                
int main ()
{
    MyList list1;
    MyList list2;
    MyList listAnd;
    MyList listOr;

    //Test1
//    list1 += 1;
//    list1 += 6;
//    list1 += 9;
//
//    list2 += 3;
//    list2 += 4;
//    list2 += 8;
        
    //Test2
//    листы пустые
        
    //Test3
//    list1 += 1;
//    list1 += 4;
//    list1 += 2;
//
//    list2 += 4;
//    list2 += 3;
//    list2 += 6;

    //Test4
//    list1 += 2;
//    list1 += 3;

    //Test5
//    list2 += 5;
//    list2 += 5;

    //Test6
//    list1 += 1;
//    list1 += 3;
//    list1 += 5;
//
//    list2 += 2;
//    list2 += 4;
//    list2 += 6;
        
    //Test6
//    list1 += 5;
//    list1 += 4;
//    list1 += 6;
//    list1 += 7;
//
//    list2 += 2;
//    list2 += 5;
//    list2 += 4;

    //Test7
//    list1 += 1;
//    list1 += 2;
//    list1 += 3;
//
//    list2 += 4;
//    list2 += 5;
//    list2 += 6;
        
    //Test8
//    list1 += 4;
//    list1 += 5;
//    list1 += 6;
//
//    list2 += 1;
//    list2 += 2;
//    list2 += 3;
    
    //Test8
    list1 += 0;
    list1 += 2;
    list1 += 1;

    list2 += 7;
    list2 += 1;
    list2 += 4;
    list2 += 3;
        
    //Test8
//    list1 += 0;
//    list1 += 2;
//    list1 += 7;
//    list1 += 1;
//
//    list2 += 0;
//    list2 += 2;
//    list2 += 7;
//    list2 += 1;
        
        
    //Проверка "<<" и проверка "+="
    cout << "First list: " << list1 << endl;
    cout << "Second list: " << list2 << endl;
    
    //Проверка "=="
    cout << endl;
    cout << "Are they equal?" << endl;
    if (list1 == list2)
        cout << "True" << endl;
    else
        cout << "False" << endl;
    
    //Проверка "&"
    cout << endl;
    cout << "Operator &" << endl;
    listAnd = (list1 & list2);
    cout << listAnd << endl;
    
    //Проверка "|"
    cout << endl;
    cout << "Operator |" << endl;
    listOr = (list1 | list2);
    cout << listOr << endl;

    //Проверка "merge"
    cout << endl;
    cout << "Merge:" << endl;
    list1.merge(list2);
    cout << list1 << endl;
    cout << list2 << endl;
    
    int i = 10;
    i=i+1;
    cout << i << endl;
    
    return 0;
}
