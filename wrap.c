#include <stdio.h>
#include <string.h>
#include "wrap.h"
#include "fun2.h"


void getopt(int argc, char* argv[])
{
	wrap = 0;
	for(int i = 1; i < argc; i++)
	{
		if(!strcmp(argv[i],"--wrap"))
			wrap = 1;
	}
}


int __real_add(int a, int b);
int __real_mul(int a, int b);

#if 1
int __wrap_add(int a, int b)
{
	static int i = 0;
	i++;
	if(wrap)
		f_enter();
	return __real_add(a, b);	
}
#endif

#if 1
int __wrap_mul(int a, int b)
{
	if(wrap)
		f_enter();
	return __real_mul(a, b);	
}
#endif

