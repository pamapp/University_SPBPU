//
//  resource.c
//  Created by Alina Potapova on 22.04.2022.
//

#include "sys.h"
#include "rtos_api.h"
#include "interruption.h"
#include <stdio.h>

void InitResource(int priority) {
    for (int i = 0; i < MAX_RES; i++) {
        if (ResourceQueue[i].priority == 0) {
            ResourceQueue[i].priority = priority;
            break;
        }
    }
}

void GetResource(int priority, char* name)
{
    int task_index;
    int free_occupy;
    
    for (int i = 0; i < MAX_TASK; i++) {
        if (TaskQueue[i].name == name) {
            task_index = i;
            break;
        }
    }
    
    if (TaskQueue[RunningTask].priority > TaskQueue[task_index].priority) {
        ClearResources();
        InterruptionHandler::processInterruption({"This process is handled by task with higher/equal priority"});
        return;
    }
    
	printf("GetResource %s with priority %d\n", name, priority);
    
    free_occupy = GetResourceIndex(priority);
    
    if (free_occupy != -1) {
        ResourceQueue[free_occupy].index = RunningTask;
        ResourceQueue[free_occupy].isFree = false;
    } else {
        ClearResources();
        InterruptionHandler::processInterruption({"No free resources with necessary priority is available now"});
    }

}

void ReleaseResource(int task_index)
{
	printf("Release resource %s\n", TaskQueue[task_index].name);
    
    int index = -1;
    
    for (int i = 0; i < MAX_RES; i++) {
        if (ResourceQueue[i].index == task_index) {
            index = i;
            break;
        }
    }
    
    if (index != -1) {
        ResourceQueue[index].index = -1;
        ResourceQueue[index].isFree = true;
    }
}

int GetResourceIndex(int priority) {
    int index = -1;
    
    for (int i = 0; i < MAX_RES; i++) {
        if (ResourceQueue[i].isFree && ResourceQueue[i].priority >= priority) {
            if (ResourceQueue[i].priority == priority)
                return i;
            if (index == -1 || ResourceQueue[index].priority > ResourceQueue[i].priority)
                index = i;
        }
    }
    
    return index;
}

void ClearResources() {
    for (int i = 0; i < MAX_RES; i++) {
        ResourceQueue[i].index = -1;
        ResourceQueue[i].isFree = true;
    }
    TerminateTask();
}






