#include "dominion.h"
#include "dominion_helpers.h"
#include "kingdom_cards.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>


int main() {

   // set players and seed
   int numOfPlayers = 2;
   int seed = 232;
   int currPlayer = 0;
   // declare game state
   struct gameState G, testGame;

   // set card array
   int k[10] = {adventurer, baron, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute};

   // initialize game
   initializeGame(numOfPlayers, k, seed, &G);

   int choice1 = mine;  // if province, infinite loop
   G.coins = 0;

   // begin testing scoreFor
   printf("\n\n** BEGIN TEST No. 1 *************************************************************\n");
   
   
   // copy game state for test game
   memcpy(&testGame, &G, sizeof(struct gameState));


   printf("Coins before play: %d\n\n", G.coins);
 
   //int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
   cardEffect(feast, choice1 ,0 ,0, &testGame, 0, 0);


   if (G.coins == testGame.coins) {
      printf("OK:  the number of coins remains the same.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins);
   }
   else {
      printf("ERROR:  the number of coins changed.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins);
   }
 
 
   if (G.discardCount[currPlayer] + 1 == testGame.discardCount[currPlayer]) {
      printf("OK:  the number of discards increased by 1.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[currPlayer]);
   }
   else {
      printf("ERROR:  the number of discards did not increase by 1.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[currPlayer]);
   }

   printf("\n\n");


   printf("** END TEST No. 1 *************************************************************\n\n\n\n");



   return 0;	
}
