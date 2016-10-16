#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/shm.h>
#include "wrap.h"
#include "fun2.h"

#include "funs_list.h"

int wrap_enabled[MAX_WRAP_FUNS];
shm_wrap_funs* shared;

void get_wrap_funs()
{
	while(1)
	{
		if(!shared->written)
		{
			printf("waiting shared memory writtern...\n");
			sleep(1);
		}
		else
		{
			for(int i = 0; i < shared->num; i++)
			{
				char *wrap_fun = shared->wrap_funs[i];
				for(int j = 0; j < funs_num; j++)
				{
					if(!strcmp(wrap_fun, funs_list[j]))
					{
						wrap_enabled[j] = 1;	
						break;
					}
				}
			}
			break;	
		}
	}
}

int getoption()
{
	char filename[256],cmd[1024];
	FILE* fp;

	sprintf(filename, "/proc/%d/cmdline",getpid()); 
	fp = fopen(filename, "r");
	if(fp == NULL)
	{
		printf("%s open failed\n",filename);
		exit(-1);
	}

//	wrap = 0;
	int cmd_size = fread(cmd, 1, 1024, fp);
	char *cmd_p = cmd;
	while(cmd_size > 0)
	{
//		printf("%s\n",cmd_p);
		if(!strcmp(cmd_p, "--wrap"))
		{
//			wrap = 1;
			get_wrap_funs();
			return 1;
		}
		cmd_size -= (strlen(cmd_p)+1);
		cmd_p += (strlen(cmd_p)+1);
	}

	return 0;
}


void signal_handler(int signum)
{
	signal(SIGINT, SIG_DFL);
//	wrap = 1;
	get_wrap_funs();
}

void wrap_init()
{
//	wrap = 0;
	memset(wrap_enabled, 0, sizeof(int)*MAX_WRAP_FUNS);
	//share memory init
	int shmid;
	void* shm = NULL;

	shmid = shmget((key_t)getpid(), sizeof(shm_wrap_funs), IPC_CREAT|0666);
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
	memset(shared, 0, sizeof(shm_wrap_funs));
#if 1

	shared->written = 1;
	shared->num = 1;
	memcpy(shared->wrap_funs[0], "mul",3);
	shared->wrap_funs[0][3] = '\0';

#endif

	
	if(!getoption())
	{
		if(signal(SIGINT, SIG_IGN) != SIG_IGN)
			signal(SIGINT, signal_handler);
	}
}


//each function have a index, which is specified in generation script
//index 0
int __real_add(int a, int b);
int __wrap_add(int a, int b)
{
	static int i = 0;
	i++;
	if(wrap_enabled[0])
		f_enter();
	return __real_add(a, b);	
}

//index 1
int __real_mul(int a, int b);
int __wrap_mul(int a, int b)
{
	if(wrap_enabled[1])
		f_enter();
	return __real_mul(a, b);	
}


