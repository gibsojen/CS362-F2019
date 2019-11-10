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

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o kingdom_cards.o interface.o $(CFLAGS)

all: playdom player 

randomtestresults: dominion.o
	echo "Results for random test 1:" > randomtestresults.out
	echo "randomtestcard1.c:" >> randomtestresults.out
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o kingdom_cards.o $(CFLAGS)
	./randomtestcard1 >> randomtestresults.out
	#./randomtestcard1


	echo "Results for random test 2:" >> randomtestresults.out
	echo "randomtestcard2.c:" >> randomtestresults.out
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o kingdom_cards.o $(CFLAGS)
	./randomtestcard2 >> randomtestresults.out
	#./randomtestcard2

	echo "Results for random test 3:" >> randomtestresults.out
	echo "randomtestcard3.c:" >> randomtestresults.out
	gcc -o randomtestcard3 -g randomtestcard3.c dominion.o rngs.o kingdom_cards.o $(CFLAGS)
	./randomtestcard3 >> randomtestresults.out
	#./randomtestcard3
	gcov kingdom_cards.c -f -b >> randomtestresults.out

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe randomtestcard1 randomtestcard2 randomtestcard3
