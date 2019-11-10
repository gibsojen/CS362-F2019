#include "dominion.h"
#include "dominion_helpers.h"
#include "kingdom_cards.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


void cardNumToName(int card, char *name) {
    switch(card) {
    case curse:
        strcpy(name,"Curse");
        break;
    case estate:
        strcpy(name,"Estate");
        break;
    case duchy:
        strcpy(name,"Duchy");
        break;
    case province:
        strcpy(name,"Province");
        break;
    case copper:
        strcpy(name,"Copper");
        break;
    case silver:
        strcpy(name,"Silver");
        break;
    case gold:
        strcpy(name,"Gold");
        break;
    case adventurer:
        strcpy(name,"Adventurer");
        break;
    case council_room:
        strcpy(name,"Council Room");
        break;
    case feast:
        strcpy(name,"Feast");
        break;
    case gardens:
        strcpy(name,"Gardens");
        break;
    case mine:
        strcpy(name,"Mine");
        break;
    case remodel:
        strcpy(name,"Remodel");
        break;
    case smithy:
        strcpy(name,"Smithy");
        break;
    case village:
        strcpy(name,"Village");
        break;
    case baron:
        strcpy(name,"Baron");
        break;
    case great_hall:
        strcpy(name,"Great Hall");
        break;
    case minion:
        strcpy(name,"Minion");
        break;
    case steward:
        strcpy(name,"Steward");
        break;
    case tribute:
        strcpy(name,"Tribute");
        break;
    case ambassador:
        strcpy(name,"Ambassador");
        break;
    case cutpurse:
        strcpy(name,"Cutpurse");
        break;
    case embargo:
        strcpy(name,"Embargo");
        break;
    case outpost:
        strcpy(name,"Outpost");
        break;
    case salvager:
        strcpy(name,"Salvager");
        break;
    case sea_hag:
        strcpy(name,"Sea Hag");
        break;
    case treasure_map:
        strcpy(name,"Treasure Map");
        break;

    default:
        strcpy(name,"?");
    }

}




int tributeTest(struct gameState *G, int players, int player2) {
   struct gameState testGame;
   memcpy (&testGame, G, sizeof(struct gameState));

   int retErr;
   int same = 0;
   int treas = 0;
   int vict = 0;
   int act = 0;
   int moreThanOne = 0;

   //int tributeCard (struct gameState *state, int currentPlayer) {
   retErr = tributeCard(&testGame, players);

   if (G->deckCount[player2] > 1) {
      moreThanOne = 1;
   }


   // are top two cards the same
   
   if (moreThanOne) {
      if (G->deck[player2][G->deckCount[player2] - 1] == G->deck[player2][G->deckCount[player2] - 2]) {
         same = 1;
      }
   }


   if (G->deck[player2][G->deckCount[player2] - 1] == copper || G->deck[player2][G->deckCount[player2] - 1] == silver ||
       G->deck[player2][G->deckCount[player2] - 1] == gold) {
          treas++;
   }
   else if (G->deck[player2][G->deckCount[player2] - 1] == estate || G->deck[player2][G->deckCount[player2] - 1] == duchy ||
       G->deck[player2][G->deckCount[player2] - 1] == province || G->deck[player2][G->deckCount[player2] - 1] == gardens ||
       G->deck[player2][G->deckCount[player2] - 1] == great_hall) {
          vict++;
   }
   else {       
      act++;
   }

   if (!same && moreThanOne) {
      if (G->deck[player2][G->deckCount[player2] - 2] == copper || G->deck[player2][G->deckCount[player2] - 2] == silver ||
          G->deck[player2][G->deckCount[player2] - 2] == gold) {
         treas++;
      }
      else if (G->deck[player2][G->deckCount[player2] - 2] == estate || G->deck[player2][G->deckCount[player2] - 2] == duchy ||
          G->deck[player2][G->deckCount[player2] - 2] == province || G->deck[player2][G->deckCount[player2] - 2] == gardens ||
          G->deck[player2][G->deckCount[player2] - 2] == great_hall) {
             vict++;
      }
      else {       
         act++;
      }
   }



   printf("Return Code: %d\n", retErr);
   if (same && moreThanOne) {
      printf("Top two cards of next player are the same.\n");
   }
   else {
      printf("Top two cards of next player are different.\n");
   }
   printf("%d different treasure cards.\n", treas);
   printf("%d different victory cards.\n", vict);
   printf("%d different action cards.\n", act);


  int card = G->deck[player2][G->deckCount[player2] - 1];
  char name[32];
  cardNumToName(card, name);

   printf("card 1 is = %s\n", name);
   if (G->deckCount[player2] > 1) {
      card = G->deck[player2][G->deckCount[player2] - 2];
      cardNumToName(card, name);
      printf("card 2 is = %s\n", name);
   }


   if(G->numActions + (act * 2) == testGame.numActions) {
      printf("OK: numActions increased by %d.\n", act * 2);
   }
   else {
      printf("ERROR: numActions did not increase by %d.\n", act * 2);
      printf("actions before = %d\n", G->numActions);
      printf("actions after = %d\n", testGame.numActions);
   }


   if(G->coins + (treas * 2) == testGame.coins) {
      printf("OK: coins increased by %d.\n", treas * 2);
   }
   else {
      printf("ERROR: coins did not increase by %d.\n", treas * 2);
      printf("coins before = %d\n", G->coins);
      printf("coins after = %d\n", testGame.coins);
   }

   if(G->handCount[players] + (vict * 2) == testGame.handCount[players]) {
      printf("OK: hand count increased by %d.\n", vict * 2);
   }
   else {
      printf("ERROR: hand count did not increase by %d.\n", treas * 2);
      printf("hand count before = %d\n", G->handCount[players]);
      printf("hand count after = %d\n", testGame.handCount[players]);
   }


   if (moreThanOne) {
      if (G->discardCount[player2] + 2 == testGame.discardCount[player2]) {
         printf("OK: next player's discards increased by 2.\n");
      }
      else {
         printf("ERROR: next player's discards did not increase by 2.\n");
         printf("next player's discard count before = %d\n", G->discardCount[player2]);
         printf("next player's discard count after = %d\n", testGame.discardCount[player2]);
      }
   }
   else {
      if (G->discardCount[player2] + 1 == testGame.discardCount[player2]) {
         printf("OK: next player's discards increased by 1.\n");
      }
      else {
         printf("ERROR: next player's discards did not increase by 1.\n");
         printf("next player's discard count before = %d\n", G->discardCount[player2]);
         printf("next player's discard count after = %d\n", testGame.discardCount[player2]);
      }

   }


   if (moreThanOne) {
      if (G->deckCount[player2] - 2 == testGame.deckCount[player2]) {
         printf("OK: next player's deck decreased by 2.\n");
      }
      else {
         printf("ERROR: next player's deck did not decrease by 2.\n");
         printf("next player's deck count before = %d\n", G->deckCount[player2]);
         printf("next player's deck count after = %d\n", testGame.deckCount[player2]);
      }
   }
   else {
      if (G->deckCount[player2] - 1 == testGame.deckCount[player2]) {
         printf("OK: next player's deck decreased by 1.\n");
      }
      else {
         printf("ERROR: next player's deck did not decrease by 1.\n");
         printf("next player's deck count before = %d\n", G->deckCount[player2]);
         printf("next player's deck count after = %d\n", testGame.deckCount[player2]);
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

   int set[10] = {copper, gold, silver, estate, duchy, mine, province,
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
      G.numActions = rand() % MAX_DECK;
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

      G.whoseTurn = players;

      G.deckCount[players] = rand() % MAX_DECK;
      G.deckCount[player2] = rand() % MAX_DECK;
     
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

      for (m = 0; m < G.discardCount[players]; m++) {
         int temp = rand() % 10;
         G.discard[players][m] = set[temp];
      }

      for (m = 0; m < G.discardCount[player2]; m++) {
         int temp = rand() % 10;
         G.discard[player2][m] = set[temp];
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
