#include "dominion.h"
#include "dominion_helpers.h"
#include "kingdom_cards.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


int tributeTest(struct gameState *G, int players, int player2) {
   struct gameState testGame;
   memcpy (&testGame, G, sizeof(struct gameState));

   int retErr;


   //int tributeCard (struct gameState *state, int currentPlayer) {
   retErr = tributeCard(&testGame, players);

   printf("Return Code: %d\n", retErr);

/*
   else if (choice2 >= 1) {
      printf("With choice1 = %d and choice2 = %d\n", choice1, choice2);
      printf("Return Code: %d\n", retErr);

      if(G->numActions + 1 == testGame.numActions) {
         printf("OK: numActions increased by 1.\n");
      }
      else {
         printf("ERROR: numActions did not increase by 1.\n");
      }

      if(G->handCount[players] + G->discardCount[players] == testGame.discardCount[players]) {
         printf("OK: discards increased by the number of cards in the current player's hand.\n");
      }
      else {
         printf("ERROR: discards did not increase by the number of cards in the current player's hand.\n");
         printf("original hand count = %d, new discard count = %d.\n", G->handCount[players], testGame.discardCount[players]);
         printf("original discard count = %d.\n", G->discardCount[players]);
      }

      if(testGame.handCount[players] == 4) {
         printf("OK: hand count is now 4.\n");
      }
      else {
         printf("ERROR: hand count is not 4, it is %d.\n", testGame.handCount[players]);
         printf("original hand count = %d\n", G->handCount[players]);
      }

      if (G->handCount[player2] >= 5) {
         printf("Handcount of next player is >= 5, so must discard hand and gain 4.\n");

         if(G->handCount[player2] + G->discardCount[player2] == testGame.discardCount[player2]) {
            printf("OK: discards increased by the number of cards in the next player's hand.\n");
         }
         else {
            printf("ERROR: discards did not increase by the number of cards in the next player's hand.\n");
            printf("original hand count = %d, new discard count = %d.\n", G->handCount[player2], testGame.discardCount[player2]);
            printf("original discard count = %d.\n", G->discardCount[player2]);
         }

         if(testGame.handCount[player2] == 4) {
            printf("OK: hand count is now 4.\n");
         }
         else {
            printf("ERROR: hand count is not 4, it is %d.\n", testGame.handCount[player2]);
            printf("original hand count = %d\n", G->handCount[player2]);
         }

      }

   }
*/

   printf("\n\n");
   return 0;
}



int main() {
   struct gameState G;
   srand(time(NULL));

/*
   int k[10] = {adventurer, baron, gardens, embargo, village, minion, mine, 
		cutpurse, sea_hag, tribute};
*/

   int set[10] = {copper, gold, silver, estate, village, mine, province,
		  cutpurse, tribute, baron};
   int i;
   int j;
   int m;
   int players;
   int player2;


   for (i = 0; i < 2000; i++) {
      for (j = 0; j < sizeof(struct gameState); j++) {
         ((char*)&G)[j] = rand() % 256;
      }
      // int num = (rand() % (upper - lower + 1)) + lower;
      //
      G.numBuys = rand() % MAX_DECK;
   
      //set number of players
      G.numPlayers = 2;


      players = rand() % 2; //  0 and 1

      if (players == 0) {
         player2 = 1;
      }
      else {
         player2 = 0;
      }

      G.whoseTurn = players;

      G.deckCount[players] = rand() * MAX_DECK;
      G.deckCount[player2] = rand() * MAX_DECK;
     
      G.discardCount[players] = rand() % MAX_DECK;
      G.discardCount[player2] = rand() % MAX_DECK;

      G.handCount[players] = rand() % MAX_HAND;
      G.handCount[player2] = G.handCount[players];

      G.playedCardCount = 0;

      for (m = 0; m < G.handCount[players]; m++) {
         int temp = rand() % 10;
         G.hand[players][m] = set[temp];
      }

      for (m = 0; m < G.handCount[player2]; m++) {
         int temp = rand() % 10;
         G.hand[player2][m] = set[temp];
      }

      for (m = 0; m < G.deckCount[players]; m++) {
         int temp = rand() % 10;
         G.deck[players][m] = set[temp];
      }

      for (m = 0; m < G.deckCount[player2]; m++) {
         int temp = rand() % 10;
         G.deck[player2][m] = set[temp];
      }
/*
      for (m = 0; m < 50; m++) {
         G.supplyCount[m] = 30;
      }
*/


      tributeTest(&G, players, player2);
   }

   printf("END OF TRIBUTE TESTS\n\n");
   //exit(0);

   return 0;
}
