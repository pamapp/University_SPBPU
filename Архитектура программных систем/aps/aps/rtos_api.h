//
//  rtos_api.h
//  Created by Alina Potapova on 22.04.2022.
//

#define DeclareTask(TaskID,priority)\
	TASK(TaskID);					\
enum {TaskID##prior=priority}

#define DeclareResource(ResID,priority)\
enum {ResID=priority}

#define TASK(TaskID) void TaskID(void)

typedef void TTaskCall(void);

void ActivateTask(TTaskCall entry,int priority,char* name);
void TerminateTask(void);

int StartOS(TTaskCall entry,int priority,char* name);
void ShutdownOS();

void InitResource(int priority);
void GetResource(int priority, char* name);
void ReleaseResource(int priority);
int GetResourceIndex(int priority);
void ClearResources();

