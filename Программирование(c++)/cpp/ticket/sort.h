#include <iostream>
#include <math.h>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <cctype>
#include <stdio.h>

using namespace std;
 
const string fileName = "C:\\Users\\alinapotapova\\Documents\\cpp\\ticket\\input.txt";
const string fileName2 = "C:\\Users\\alinapotapova\\Documents\\cpp\\ticket\\output.txt";

using namespace std;
 
struct Flight
{
    char name[20];
    char surname[20];
    struct
    {
        unsigned int day,month,year;
    }
    brithday;
};
 
int main()
{
    FILE *input, *output;
    int i,n = 5;
    char s[255];
    struct Flight bd [20];
    Flight sort[20];
    input = fopen("input.txt","r");
    i = 0;
    while(i < n)
    {
        fscanf(input,"%s",&bd[i].name);
        fscanf(input,"%s",&bd[i].surname);
        fscanf(input,"%d",&bd[i].brithday.day);
        fscanf(input,"%d",&bd[i].brithday.month);
        fscanf(input,"%d",&bd[i].brithday.year);
        i++;
    }
    
    
    setlocale(LC_ALL,"Russian");
    
    
    cout<<"\tСписок заказщиков:"<<endl;
    cout<<"--------------------------------------------------------------------------------"<<endl;
    setlocale(LC_ALL,"Russian");
    for(i = 0; i < n; i++)
    {
        cout<<"№ "<<i+1<<"| Ф.И.О. заказщика: ";
        setlocale(LC_ALL,"Russian");
        cout << bd[i].surname << " " << bd[i].name;
        setlocale(LC_ALL,"Russian");
        cout << "|Дата рождения: "<<bd[i].brithday.day<<"/"<<bd[i].brithday.month<<"/"<<bd[i].brithday.year<<"|"<<endl;
    }
    
    cout<<"------------------------------------------------------------------------------";
 
 
for (i=0;i<n-1;i++)
{
    for (int g=i+1;g<n;g++)
    {
        if(bd[i].brithday.year>bd[g].brithday.year)
        {
            sort[1]=bd[i];
            bd[i]=bd[g];
            bd[g]=sort[1];
            continue;
        }
        if(bd[i].brithday.year==bd[g].brithday.year && bd[i].brithday.month>bd[g].brithday.month)
        {
            sort[1]=bd[i];
            bd[i]=bd[g];
            bd[g]=sort[1];
            continue;
        }
        if (bd[i].brithday.year==bd[g].brithday.year && bd[i].brithday.month==bd[g].brithday.month && bd[i].brithday.day>bd[g].brithday.day)
        {
            sort[1]=bd[i];
            bd[i]=bd[g];
            bd[g]=sort[1];
        }
    }
}
 
 
 
 
cout<<"\tСписок группы упорядоченный по возрастанию году рождения :"<<endl;
cout<<"--------------------------------------------------------------------------------"<<endl;
    setlocale(LC_ALL,"Russian");
    for(i = 0; i < n; i++)
    {
        cout<<"№ "<<i + 1<<"| Ф.И.О. студента: ";
        setlocale(LC_ALL,"Russian");
        cout << bd[i].surname << bd[i].name;
        setlocale(LC_ALL,"Russian");
        cout<<"|Дата рождения: "<<bd[i].brithday.day<<"/"<<bd[i].brithday.month<<"/"<<bd[i].brithday.year<<"|"<<endl;
    }
cout<<"------------------------------------------------------------------------------";

}
