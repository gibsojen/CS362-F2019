#include "dominion.h"
#include "dominion_helpers.h"
#include "kingdom_cards.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int baronTest(int choice, struct gameState *G, int players) {
   struct gameState testGame;
   memcpy (&testGame, G, sizeof(struct gameState));

   int retErr;

   retErr = baronCard(choice, &testGame, players);

   if (choice == -1) {
      printf("With choice1 = %d\n", choice);
      printf("Return Code: %d\n", retErr);
      //gain an estate
      if(G->supplyCount[estate] - 1 == testGame.supplyCount[estate]) {
         printf("OK: supply of estates decreased by 1.\n");
      }
      else {
         printf("ERROR: supply of estates did not decrease by 1.\n");
      }
      if(G->discardCount[players] + 1 == testGame.discardCount[players]) {
         printf("OK: discards increased by 1.\n");
      }
      else {
         printf("ERROR: discards did not increase by 1.\n");
      }
      if(G->numBuys + 1 == testGame.numBuys) {
         printf("OK: numBuys increased by 1.\n");
      }
      else {
         printf("ERROR: numBuys did not increase by 1.\n");
      }
      if(G->coins == testGame.coins) {
         printf("OK: coins stayed the same.\n");
      }
      else {
         printf("ERROR: coins did not stay the same.\n");
      }
   }

   
   if (choice == 0) {
      printf("With choice1 = %d\n", choice);
      printf("Return Code: %d\n", retErr);
      //gain an estate
      if(G->supplyCount[estate] - 1 == testGame.supplyCount[estate]) {
         printf("OK: supply of estates decreased by 1.\n");
      }
      else {
         printf("ERROR: supply of estates did not decrease by 1.\n");
      }
      if(G->discardCount[players] + 1 == testGame.discardCount[players]) {
         printf("OK: discards increased by 1.\n");
      }
      else {
         printf("ERROR: discards did not increase by 1.\n");
      }
      if(G->numBuys + 1 == testGame.numBuys) {
         printf("OK: numBuys increased by 1.\n");
      }
      else {
         printf("ERROR: numBuys did not increase by 1.\n");
      }
      if(G->coins == testGame.coins) {
         printf("OK: coins stayed the same.\n");
      }
      else {
         printf("ERROR: coins did not stay the same.\n");
      }
   }

  
   if (choice == 1) {
      printf("With choice1 = %d\n", choice);
      printf("Return Code: %d\n", retErr);
      //get rid of an estate
      int i;
      int found = 0;


      if(G->numBuys + 1 == testGame.numBuys) {
         printf("OK: numBuys increased by 1.\n");
      }
      else {
         printf("ERROR: numBuys did not increase by 1.\n");
      }


      for (i = 0; i < testGame.handCount[players]; i++) {
         if (testGame.hand[players][i] == estate) {
            found = 1;
         }
      }      
      if (found) {

         if(G->supplyCount[estate] == testGame.supplyCount[estate]) {
            printf("OK: supply of estates stayed the same.\n");
         }
         else {
            printf("ERROR: supply of estates did not stay the same.\n");
         }
         if(G->discardCount[players] + 1 == testGame.discardCount[players]) {
            printf("OK: discards increased by 1.\n");
         }
         else {
            printf("ERROR: discards did not increase by 1.\n");
         }
         if(G->coins + 4 == testGame.coins) {
            printf("OK: coins increased by 4.\n");
         }
         else {
            printf("ERROR: coins did not increase by 4.\n");
         }

      }
      else {

         if(G->supplyCount[estate] - 1 == testGame.supplyCount[estate]) {
            printf("OK: supply of estates decreased by 1.\n");
         }
         else {
            printf("ERROR: supply of estates did not decrease by 1.\n");
         }
         if(G->discardCount[players] + 1 == testGame.discardCount[players]) {
            printf("OK: discards increased by 1.\n");
         }
         else {
            printf("ERROR: discards did not increase by 1.\n");
         }
         if(G->numBuys + 1 == testGame.numBuys) {
            printf("OK: numBuys increased by 1.\n");
         }
         else {
            printf("ERROR: numBuys did not increase by 1.\n");
         }
         if(G->coins == testGame.coins) {
            printf("OK: coins stayed the same.\n");
         }
         else {
            printf("ERROR: coins did not stay the same.\n");
         }

      } 

   }



   if (choice == 2) {
      printf("With choice1 = %d\n", choice);
      printf("Return Code: %d\n", retErr);
      //get rid of an estate
      int i;
      int found = 0;


      if(G->numBuys + 1 == testGame.numBuys) {
         printf("OK: numBuys increased by 1.\n");
      }
      else {
         printf("ERROR: numBuys did not increase by 1.\n");
      }


      for (i = 0; i < testGame.handCount[players]; i++) {
         if (testGame.hand[players][i] == estate) {
            found = 1;
         }
      }      
      if (found) {

         if(G->supplyCount[estate] == testGame.supplyCount[estate]) {
            printf("OK: supply of estates stayed the same.\n");
         }
         else {
            printf("ERROR: supply of estates did not stay the same.\n");
         }
         if(G->discardCount[players] + 1 == testGame.discardCount[players]) {
            printf("OK: discards increased by 1.\n");
         }
         else {
            printf("ERROR: discards did not increase by 1.\n");
         }
         if(G->coins + 4 == testGame.coins) {
            printf("OK: coins increased by 4.\n");
         }
         else {
            printf("ERROR: coins did not increase by 4.\n");
         }

      }
      else {

         if(G->supplyCount[estate] - 1 == testGame.supplyCount[estate]) {
            printf("OK: supply of estates decreased by 1.\n");
         }
         else {
            printf("ERROR: supply of estates did not decrease by 1.\n");
         }
         if(G->discardCount[players] + 1 == testGame.discardCount[players]) {
            printf("OK: discards increased by 1.\n");
         }
         else {
            printf("ERROR: discards did not increase by 1.\n");
         }
         if(G->numBuys + 1 == testGame.numBuys) {
            printf("OK: numBuys increased by 1.\n");
         }
         else {
            printf("ERROR: numBuys did not increase by 1.\n");
         }
         if(G->coins == testGame.coins) {
            printf("OK: coins stayed the same.\n");
         }
         else {
            printf("ERROR: coins did not stay the same.\n");
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
   int choice1;
   for (i = 0; i < 2000; i++) {
      for (j = 0; j < sizeof(struct gameState); j++) {
         ((char*)&G)[j] = rand() % 256;
      }

      G.numBuys = rand() % MAX_DECK;
      players = rand() % 2;
      choice1 = (rand() % 4) - 1; // -1 to 2
      //int temp1 = rand() % MAX_DECK;
      //printf("TEMP1:  %d\n\n", temp1);
      //G.deckCount[players] = floor(rand() * MAX_DECK);
      G.discardCount[players] = rand() % MAX_DECK;
      G.handCount[players] = rand() % MAX_HAND;
      for (m = 0; m < G.handCount[players]; m++) {
         int temp = rand() % 10;
         G.hand[players][m] = set[temp];
      } 
      baronTest(choice1, &G, players);
      //int baronCard (int choice1, struct gameState *state, int currentPlayer) {
   }

   printf("END OF BARON TESTS\n\n\n\n");
   //exit(0);

   return 0;
}
