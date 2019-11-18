CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

unittest1:  unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

unittestresults: dominion.o
	
	echo "Result for running Unit 1 tests:" > unittestresults.out
	#echo "unittest1.c:" >> unittestresults.out
	#gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	#./unittest1 >> unittestresults.out
	#gcov kingdom_cards.c -f -b >> unittestresults.out

	echo "--------------------------------------------------------------------------------------------------------------------------------" >> unittestresults.out
	echo "Result for running Unit 2 tests:" >> unittestresults.out
	echo "unittest2.c:" >> unittestresults.out
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	./unittest2 >> unittestresults.out
	#gcov kingdom_cards.c -f -b >> unittestresults.out
	
	echo "--------------------------------------------------------------------------------------------------------------------------------" >> unittestresults.out
	echo "Result for running Unit 3 tests:" >> unittestresults.out
	echo "unittest3.c:" >> unittestresults.out
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	./unittest3 >> unittestresults.out
	#gcov kingdom_cards.c -f -b >> unittestresults.out
	
	#echo "--------------------------------------------------------------------------------------------------------------------------------" >> unittestresults.out
	#echo "Result for running Unit 4 tests:" >> unittestresults.out
	#echo "unittest4.c:" >> unittestresults.out
	#gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
	#./unittest4 >> unittestresults.out
	#gcov kingdom_cards.c -f -b >> unittestresults.out
	
	echo "--------------------------------------------------------------------------------------------------------------------------------" >> unittestresults.out
	echo "Result for running Unit 5 tests:" >> unittestresults.out
	echo "unittest5.c:" >> unittestresults.out
	gcc -o unittest5 -g unittest5.c dominion.o rngs.o $(CFLAGS)
	./unittest5 >> unittestresults.out
	gcov dominion.c -f -b >> unittestresults.out

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest1 unittest2 unittest3 unittest4 unittest5
