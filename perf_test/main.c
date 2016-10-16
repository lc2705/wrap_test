#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include "../wrap.h"


int main(int argc, char* argv[])
{
	int pid;
	char* funs[MAX_WRAP_FUNS];
	int funs_num = 0;

	//usage: ./myperf pid fun1 fun2 ...
	pid = atoi(argv[1]);
	for(int i = 2; i < argc; i++)
	{
		funs[funs_num] = argv[i];
		funs_num++;
	}

	void* shm = NULL;
	int shmid;
	shm_wrap_funs* shared = NULL;

	shmid = shmget((key_t)pid, sizeof(shm_wrap_funs), 0666|IPC_CREAT);
	if(shmid == -1)
	{
		printf("shmget error\n");
		exit(-1);
	}

	shm = shmat(shmid, 0, 0);
	if(shm == (void*)-1)
	{
		printf("shmat error\n");
		exit(-1);	
	}

	shared = (shm_wrap_funs*)shm;
	shared->num = funs_num;
	for(int i = 0; i < funs_num; i++)
		memcpy(shared->wrap_funs[i], funs[i], strlen(funs[i])+1);
	shared->written = 1;	

//	getchar();	
	return 0;
}
