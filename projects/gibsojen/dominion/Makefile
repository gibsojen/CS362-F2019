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

fin: dominion.o
	
	#echo "Result for running Unit 1 tests:" > unittestresults.out
	#echo "unittest1.c:" >> unittestresults.out
	gcc -o fin -g final.c dominion.o rngs.o kingdom_cards.o $(CFLAGS)
	gcc -o fin2 -g final2.c dominion.o rngs.o kingdom_cards.o $(CFLAGS)
	gcc -o fin3 -g final3.c dominion.o rngs.o kingdom_cards.o $(CFLAGS)
	gcc -o fin4 -g final4.c dominion.o rngs.o kingdom_cards.o $(CFLAGS)
	#./unittest1 >> unittestresults.out
	#gcov kingdom_cards.c -f -b >> unittestresults.out


clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe fin fin2 fin3 fin4
