#define __WRAP

#include <stdio.h>
#include <unistd.h>

#ifdef __WRAP
#include "wrap.h"
#endif
#include "fun1.h"


int main(int argc, char* argv[])
{
	wrap_init();
	int a = 2;
	int b = 3;


	while(1)
	{
		sleep(2);
//		printf("%d\n",add(a, b));
//		printf("%d\n",add(a, b));
//		printf("%d\n",add(a, b));
//		printf("%d\n",add(a, b));
		printf("%d\n",add(a, b));
		printf("%d\n",mul(a, b));
	}

	return 0;	
}

