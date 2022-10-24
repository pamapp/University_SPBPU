//
//  test.c
//  Created by Alina Potapova on 22.04.2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "rtos_api.h"

DeclareTask(Task1,1);
DeclareTask(Task2,2);
DeclareTask(Task3,3);
DeclareTask(Task4,4);
DeclareTask(Task5,4);
DeclareTask(Task6,3);
DeclareTask(Task7,6);
DeclareTask(Task8,7);
DeclareTask(Task9,8);

DeclareResource(Res1,1);
DeclareResource(Res2,2);
DeclareResource(Res3,3);
DeclareResource(Res4,4);
DeclareResource(Res5,5);
DeclareResource(Res6,6);
DeclareResource(Res7,7);
DeclareResource(Res8,8);
DeclareResource(Res9,9);
DeclareResource(Res10,10);
DeclareResource(Res11,11);
DeclareResource(Res12,12);
DeclareResource(Res13,13);
DeclareResource(Res14,14);
DeclareResource(Res15,15);
DeclareResource(Res16,16);

int main()
{
    int n = 0;
    std::cout << "Test nember: ";
    std::cin >> n;
    
	printf("Hello!\n");
    
    switch (n) {
        case 1:
            StartOS(Task9, Task9prior, (char *)"Task9");
            break;
        case 2:
            for (int i = 0; i < 17; i++) {
                InitResource(i);
            }
            StartOS(Task7, Task7prior, (char *)"Task7");
            break;
        case 3:
            StartOS(Task1, Task1prior, (char *)"Task1");
            break;
        case 4:
            InitResource(6);
            StartOS(Task5, Task5prior, (char *)"Task5");
            break;
        case 5:
            StartOS(Task8, Task8prior, (char *)"Task8");
            TerminateTask();
        default:
            break;
    }
    ShutdownOS();
	return 0;
}


TASK(Task1)
{
	printf("Task1\n");
	ActivateTask(Task2,Task2prior, (char*)"Task2");
	TerminateTask();
}

TASK(Task2)
{
	printf("Task2\n");
	ActivateTask(Task3,Task3prior, (char*)"Task3");
	TerminateTask();
}

TASK(Task3)
{
    printf("Task3\n");
    ActivateTask(Task4,Task4prior, (char*)"Task4");
    TerminateTask();
}

TASK(Task4)
{
	printf("Task4\n");
	TerminateTask();
}

TASK(Task5)
{
    printf("Task5\n");
    GetResource(6, (char*)"Task5");
    ActivateTask(Task6,Task6prior, (char*)"Task6");
    TerminateTask();
}

TASK(Task6)
{
    printf("Task6\n");
    GetResource(6, (char*)"Task6");
    TerminateTask();
}

TASK(Task7)
{
    printf("Task7\n");
    for (int i = 0; i < 16; i++) {
        GetResource(i + 1, (char*)"Task7");
    }
    TerminateTask();
}

TASK(Task8)
{
    printf("Task8\n");
    TerminateTask();
}

TASK(Task9)
{
    printf("Task9\n");
    for(int i = 0; i < 31; i++) {
        ActivateTask(Task4, Task4prior, (char*)"Task4");
    }
    TerminateTask();
}






