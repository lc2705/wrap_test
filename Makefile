wrap:main.o wrap.o libfun1.so fun2.o
	gcc -o wrap main.o wrap.o fun2.o -lfun1 -Wl,--wrap=add,--wrap=mul

libfun1.so:fun1.o
	gcc -g -fPIC -shared -o libfun1.so fun1.o
	cp libfun1.so /usr/lib

main.o:
	gcc -g -c main.c
fun2.o:
	gcc -g -c fun2.c
fun1.o:
	gcc -g -c fun1.c
wrap.o:
	gcc -g -c wrap.c

clean:
	rm -f /usr/lib/libfun1.so
	rm -f *.o *.h.gch wrap *.a *.so
