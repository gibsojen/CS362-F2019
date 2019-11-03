CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

kingdom_cards.o:  kingdom_cards.h kingdom_cards.c
	gcc -c kingdom_cards.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o kingdom_cards.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o kingdom_cards.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o kingdom_cards.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o kingdom_cards.o $(CFLAGS)

unittest1:  unittest1.c dominion.o rngs.o kingdomcards.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o kingdom_cards.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o kingdom_cards.o interface.o $(CFLAGS)

all: playdom player 

unittestresults: dominion.o
	
	echo "Result for running Unit 1 tests:" > unittestresults.out
	echo "unittest1.c:" >> unittestresults.out
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o kingdom_cards.o $(CFLAGS)
	./unittest1 >> unittestresults.out
	gcov kingdom_cards.c -f -b >> unittestresults.out

	echo "------------------------------------------------------------------------------------------" >> unittestresults.out
	echo "Result for running Unit 2 tests:" >> unittestresults.out
	echo "unittest2.c:" >> unittestresults.out
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o kingdom_cards.o $(CFLAGS)
	./unittest2 >> unittestresults.out
	gcov kingdom_cards.c -f -b >> unittestresults.out
	
	echo "------------------------------------------------------------------------------------------" >> unittestresults.out
	echo "Result for running Unit 3 tests:" >> unittestresults.out
	echo "unittest3.c:" >> unittestresults.out
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o kingdom_cards.o $(CFLAGS)
	./unittest3 >> unittestresults.out
	gcov kingdom_cards.c -f -b >> unittestresults.out
	
	echo "------------------------------------------------------------------------------------------" >> unittestresults.out
	echo "Result for running Unit 4 tests:" >> unittestresults.out
	echo "unittest4.c:" >> unittestresults.out
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o kingdom_cards.o $(CFLAGS)
	./unittest4 >> unittestresults.out
	gcov kingdom_cards.c -f -b >> unittestresults.out
	
#	echo "unittest5.c:" >> tests.out
#	gcc -o unittest5 compare.c bst.c unittest5.c $(CFLAGS)
#	./unittest5 >> tests.out
#	gcov bst.c >> tests.out

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest1
