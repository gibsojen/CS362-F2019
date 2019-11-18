#include "dominion.h"
#include "dominion_helpers.h"
#include "kingdom_cards.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


int minionTest(int choice1, int choice2, struct gameState *G, int handPos, int players, int player2) {
   struct gameState testGame;
   memcpy (&testGame, G, sizeof(struct gameState));

   int retErr;


   //int minionCard (int choice1, int choice2, struct gameState *state, int handPos, int currentPlayer) {
   retErr = minionEffect(choice1, choice2, &testGame, handPos, players);


   if (choice1 >= 1) {
      printf("With choice1 = %d and choice2 = %d\n", choice1, choice2);
      printf("Return Code: %d\n", retErr);

      if(G->numActions + 1 == testGame.numActions) {
         printf("OK: numActions increased by 1.\n");
      }
      else {
         printf("ERROR: numActions did not increase by 1.\n");
         printf("numActions before = %d\n", G->numActions);
         printf("numActions after = %d\n", testGame.numActions);
      }

      if(G->coins + 2 == testGame.coins) {
         printf("OK: coins increased by 2.\n");
      }
      else {
         printf("ERROR: coins did not increase by 2.\n");
         printf("coins before = %d\n", G->coins);
         printf("coins after = %d\n", testGame.coins);
      }

      if(G->discardCount[players] == testGame.discardCount[players]) {
         printf("OK: discards stayed the same.\n");
      }
      else {
         printf("ERROR: discards did not stay the same.\n");
         printf("discard count before = %d\n", G->discardCount[players]);
         printf("discard count after = %d\n", testGame.discardCount[players]);
      }

      if(G->handCount[players] == testGame.handCount[players]) {
         printf("OK: hand count stayed the same.\n");
      }
      else {
         printf("ERROR: hand count did not stay the same.\n");
         printf("hand count before = %d\n", G->handCount[players]);
         printf("hand count after = %d\n", testGame.handCount[players]);
      }
   }
   
   else if (choice1 < 1 && choice2 < 1) {
      printf("With choice1 = %d and choice2 = %d\n", choice1, choice2);
      printf("Return Code: %d\n", retErr);

      if(G->numActions + 1 == testGame.numActions) {
         printf("OK: numActions increased by 1.\n");
      }
      else {
         printf("ERROR: numActions did not increase by 1.\n");
         printf("numActions before = %d\n", G->numActions);
         printf("numActions after = %d\n", testGame.numActions);
      }

      if(G->coins == testGame.coins) {
         printf("OK: coins stayed the same.\n");
      }
      else {
         printf("ERROR: coins did not stay the same.\n");
         printf("coins before = %d\n", G->coins);
         printf("coins after = %d\n", testGame.coins);
      }

      if(G->discardCount[players] + 1 == testGame.discardCount[players]) {
         printf("OK: discards increased by 1 for discarding minion.\n");
      }
      else {
         printf("ERROR: discards did not increase by 1 for discarding minion.\n");
         printf("discard count before = %d\n", G->discardCount[players]);
         printf("discard count after = %d\n", testGame.discardCount[players]);
      }

      if(G->handCount[players] - 1 == testGame.handCount[players]) {
         printf("OK: hand count decreased by 1 for discarding minion.\n");
      }
      else {
         printf("ERROR: hand count did not decrease by 1 for discarding minion.\n");
         printf("hand count before = %d\n", G->handCount[players]);
         printf("hand count after = %d\n", testGame.handCount[players]);
      }

      if(G->discardCount[player2] == testGame.discardCount[player2]) {
         printf("OK: discards of player2 stayed the same.\n");
      }
      else {
         printf("ERROR: discards of player2 did not stay the same.\n");
         printf("discard count before = %d\n", G->discardCount[player2]);
         printf("discard count after = %d\n", testGame.discardCount[player2]);
      }

      if(G->handCount[player2] == testGame.handCount[player2]) {
         printf("OK: hand count of player2 stayed the same.\n");
      }
      else {
         printf("ERROR: hand count of player2 did not stay the same.\n");
         printf("hand count before = %d\n", G->handCount[player2]);
         printf("hand count after = %d\n", testGame.handCount[player2]);
      }


   }

   else if (choice2 >= 1) {
      printf("With choice1 = %d and choice2 = %d\n", choice1, choice2);
      printf("Return Code: %d\n", retErr);

      if(G->numActions + 1 == testGame.numActions) {
         printf("OK: numActions increased by 1.\n");
      }
      else {
         printf("ERROR: numActions did not increase by 1.\n");
         printf("numActions before = %d\n", G->numActions);
         printf("numActions after = %d\n", testGame.numActions);
      }

      if(G->coins == testGame.coins) {
         printf("OK: coins stayed the same.\n");
      }
      else {
         printf("ERROR: coins did not stay the same.\n");
         printf("coins before = %d\n", G->coins);
         printf("coins after = %d\n", testGame.coins);
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
   int choice1;
   int choice2;
   int handPos;


   for (i = 0; i < 2000; i++) {
      for (j = 0; j < sizeof(struct gameState); j++) {
         ((char*)&G)[j] = rand() % 256;
      }
      // int num = (rand() % (upper - lower + 1)) + lower;
      //
      G.numBuys = rand() % MAX_DECK;
      G.coins = rand() % 40;
   
      //set number of players
      G.numPlayers = 2;


      players = rand() % 2; //  0 and 1

      if (players == 0) {
         player2 = 1;
      }
      else {
         player2 = 0;
      }

      choice1 = (rand() % 4) - 1; // -1 to 2
      choice2 = (rand() % 4) - 1; // -1 to 2
      G.whoseTurn = players;

      G.deckCount[players] = rand() % MAX_DECK;
      G.deckCount[player2] = rand() % MAX_DECK;
     
      G.discardCount[players] = rand() % MAX_DECK;
      G.discardCount[player2] = rand() % MAX_DECK;

      G.handCount[players] = rand() % MAX_HAND;
      G.handCount[player2] = G.handCount[players];

      G.playedCardCount = 0;
      if (G.handCount[players] != 0) {
         handPos = rand() % G.handCount[players];
      }
      else {
         handPos = 0;
      }
      
      for (m = 0; m < G.handCount[players]; m++) {
         if (m != handPos) {
            int temp = rand() % 10;
            G.hand[players][m] = set[temp];
         }
      }
      G.hand[players][handPos] = minion; 

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


      minionTest(choice1, choice2, &G, handPos, players, player2);
   }

   printf("END OF MINION TESTS\n\n");
   //exit(0);

   return 0;
}