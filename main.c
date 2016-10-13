#define __WRAP

#include <stdio.h>

#ifdef __WRAP
#include "wrap.h"
#endif
#include "fun1.h"


int main(int argc, char* argv[])
{
	getopt(argc, argv);
	int a = 2;
	int b = 3;

	printf("%d\n",add(a, b));
	printf("%d\n",add(a, b));
	printf("%d\n",add(a, b));
	printf("%d\n",add(a, b));
	printf("%d\n",add(a, b));
	printf("%d\n",mul(a, b));
	

	return 0;	
}

