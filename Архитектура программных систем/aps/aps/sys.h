//
//  sys.h
//  Created by Alina Potapova on 22.04.2022.
//

#include "defs.h"

#define INSERT_TO_TAIL 1
#define INSERT_TO_HEAD 0

typedef struct Type_Task
{
	int ref;
	int priority;
	int ceiling_priority;
	void (*entry)(void);
	char* name;

} TTask;

typedef struct Type_resource
{
	int index;
    bool isFree;
	int priority;
	char* name;

} TResource;

extern TTask TaskQueue[MAX_TASK];

extern TResource ResourceQueue[MAX_RES];

extern int RunningTask;

extern int FreeTask;

void Schedule(int index);

void Dispatch(int task);


