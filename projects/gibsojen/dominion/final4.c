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


   // begin testing scoreFor
   printf("\n\n** BEGIN TEST No. 1 *************************************************************\n");
   
   int choice1 = 2;

   G.hand[currPlayer][0] = steward;
   G.hand[currPlayer][1] = gold;
   G.hand[currPlayer][2] = gold;
   G.hand[currPlayer][3] = gold;
   G.hand[currPlayer][4] = gold;
   G.handCount[currPlayer] = 5;

   G.coins = 0;
   
   // copy game state for test game
   memcpy(&testGame, &G, sizeof(struct gameState));


   printf("Coins before play: %d\n\n", G.coins);
 
   //int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
   cardEffect(steward, choice1 ,0 ,0, &testGame, 0, 0);


   if (G.coins + 2 == testGame.coins) {
      printf("OK:  the number of coins increased by 2.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins);
   }
   else {
      printf("ERROR:  the number of coins did not increase by 2.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins);
   }
 
 
   printf("\n\n");


   printf("** END TEST No. 1 *************************************************************\n\n\n\n");




   // begin testing
   printf("\n\n** BEGIN TEST No. 2 *************************************************************\n");
   
  
   choice1 = 2; 

   G.hand[currPlayer][0] = steward;
   G.hand[currPlayer][1] = gold;
   G.hand[currPlayer][2] = gold;
   G.hand[currPlayer][3] = gold;
   G.hand[currPlayer][4] = gold;
   G.handCount[currPlayer] = 5;

   G.coins = 0;
 
   // copy game state for test game
   memcpy(&testGame, &G, sizeof(struct gameState));


   //int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
   //cardEffect(steward, choice1 ,0 ,0, &testGame, 0, 0);
   playCard(0, choice1, 0, 0, &testGame);


   if (G.coins + 2 == testGame.coins) {
      printf("OK:  the number of coins increased by 2.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins);
   }
   else {
      printf("ERROR:  the number of coins did not increase by 2.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins);
   }
 
 
   printf("\n\n");


   printf("** END TEST No. 2 *************************************************************\n\n\n\n");



   return 0;	
}
