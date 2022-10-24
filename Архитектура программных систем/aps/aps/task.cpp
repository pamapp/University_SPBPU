//
//  task.c
//  Created by Alina Potapova on 22.04.2022.
//

#include "sys.h"
#include "rtos_api.h"
#include "interruption.h"
#include <setjmp.h>
#include <stdio.h>

void ActivateTask(TTaskCall entry, int priority, char* name)
{
    int task;
    int occupy;

	printf("ActivateTask %s\n", name);

	task = RunningTask;
	occupy = FreeTask;
    
	FreeTask = TaskQueue[occupy].ref;

	TaskQueue[occupy].priority = priority;
	TaskQueue[occupy].name = name;
	TaskQueue[occupy].entry = entry;
	
    Schedule(occupy);
    
	if (task != RunningTask)
	{
		Dispatch(task);
	}

	printf("End of ActivateTask %s\n", name);
}

void TerminateTask(void)
{
	int task;

	task = RunningTask;

    if (task == -1) {
        InterruptionHandler::processInterruption({"Try to terminate not existing task"});
        return;
    }
    
    printf("Terminate Task %s\n", TaskQueue[task].name);
    
	RunningTask = TaskQueue[task].ref;

	TaskQueue[task].ref = FreeTask;

	FreeTask = task;
    
    ReleaseResource(task);

	printf("End of TerminateTask %s\n",TaskQueue[task].name);

}

void Schedule(int index)
{
    int cur;
    int prev;

	printf("Schedule %s\n", TaskQueue[index].name);

	cur = RunningTask;
	prev = -1;

	while(cur != -1 && TaskQueue[cur].priority >= TaskQueue[index].priority)
	{
		prev = cur;
		cur = TaskQueue[cur].ref;
	}

	TaskQueue[index].ref = cur;

	if (prev == -1)
        RunningTask = index;
	else
        TaskQueue[prev].ref = index;

	printf("End of Schedule %s\n", TaskQueue[index].name);

}

void Dispatch(int task)
{
	printf("Dispatch\n");

	do
	{
		TaskQueue[RunningTask].entry();
	}
	while(RunningTask != task);

	printf("End of Dispatch\n");

}



