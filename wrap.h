#ifndef WRAP_H
#define WRAP_H

#define MAX_WRAP_FUNS 1024
#define MAX_FUN_LEN 256
//share memory struct
typedef struct shm_wrap_funs
{
	int written;
	unsigned int num;
	char wrap_funs[MAX_WRAP_FUNS][MAX_FUN_LEN];
}shm_wrap_funs;


void wrap_init();

#endif
