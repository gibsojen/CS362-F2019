CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme:  testme.c
	echo "Coverage" > testme.out
	gcc -o testme testme.c -g  $(CFLAGS)
	-./testme
	gcov testme.c -b >> testme.out

clean:
	rm -f *.o testme *.gcov *.gcda *.gcno *.so *.out
