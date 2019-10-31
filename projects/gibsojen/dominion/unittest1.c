#include "dominion.h"
#include "dominion_helpers.h"
#include "kingdom_cards.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>

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




int main() {

   // set players and seed
   int numOfPlayers = 2;
   int seed = 232;

   // declare game state
   struct gameState G, testGame;

   // set card array
   int k[10] = {adventurer, baron, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute};

   // initialize game
   initializeGame(numOfPlayers, k, seed, &G);

   int handPos = 0;
   int bonus = 0;
   int currPlayer = 0;
   int choice1 = 0;
   int choice2 = -1;
   int choice3 = -1;




   // begin testing
   printf("\n\n** BEGIN TEST No. 1 *************************************************************\n");
   printf("** choice1 = 0, gain an estate, +1 buy\n");
   printf("** supply decreases by 1 and discards increase by 1 (for new estate), buys increases by 1 \n\n\n");

   // copy game state for test game
   memcpy(&testGame, &G, sizeof(struct gameState));

 
   // Players Hand
   printf("Players Hand Before Play:\n");
    int handCount = testGame.handCount[currPlayer];
    int handIndex;
    printf("Player %d's hand:\n", currPlayer);
    if(handCount > 0) printf("#  Card\n");
    for(handIndex = 0; handIndex < handCount; handIndex++) {
        int card = testGame.hand[currPlayer][handIndex];
        char name[32];
        cardNumToName(card, name);
        printf("%-2d %-13s\n", handIndex, name);
    }
    printf("\n");


   choice1 = 0;
   cardEffect(baron, choice1, choice2, choice3, &testGame, handPos, &bonus);


   if (testGame.supplyCount[estate] == G.supplyCount[estate] - 1) {
      printf("OK:  the number of Estates in the supply is one less than before playing baron.\n");
      printf("Number of estates in supply before play = %d\n", G.supplyCount[estate]);
      printf("Number of estates in supply after play = %d,  ", testGame.supplyCount[estate]);
      printf("Number of estates in supply expected = %d\n\n", G.supplyCount[estate] -1);
   }

   else {
      printf("ERROR:  the number of Estates in the supply is not one less than before playing baron.\n");
      printf("Number of estates in supply before play = %d\n", G.supplyCount[estate]);
      printf("Number of estates in supply after play = %d,  ", testGame.supplyCount[estate]);
      printf("Number of estates in supply expected = %d\n\n", G.supplyCount[estate] -1);

   }

   if (testGame.discardCount[currPlayer] == G.discardCount[currPlayer] + 1) {
      printf("OK:  the number of discards has increased by 1 for gaining an estate.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = 1\n\n");
      int card = testGame.discard[currPlayer][0];
      char name[32];
      cardNumToName(card, name);
      printf("Discard is: %-13s \n\n", name);
   }
   else {
      printf("ERROR:  the number of discards did not increase by 1 for gaining an estate.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = 1\n\n");
   }
 
   if (G.numBuys + 1 == testGame.numBuys) {
      printf("OK:  the number of buys has increased by 1.\n");
      printf("Number of buys before play = %d\n", G.numBuys);
      printf("Number of buys after play = %d,  ", testGame.numBuys);
      printf("Number of buys expected = %d\n\n", G.numBuys + 1);
   }
   else {
      printf("ERROR:  the number of buys did not increase by 1.\n");
      printf("Number of buys before play = %d\n", G.numBuys);
      printf("Number of buys after play = %d,  ", testGame.numBuys);
      printf("Number of buys expected = %d\n\n", G.numBuys + 1);
   }


   // Players Hand
   printf("Players Hand After Play:\n");
   handCount = testGame.handCount[currPlayer];
   printf("Player %d's hand:\n", currPlayer);
   if(handCount > 0) printf("#  Card\n");
   for(handIndex = 0; handIndex < handCount; handIndex++) {
      int card = testGame.hand[currPlayer][handIndex];
      char name[32];
      cardNumToName(card, name);
      printf("%-2d %-13s\n", handIndex, name);
   }
   printf("\n\n");


   printf("** END TEST No. 1 *************************************************************\n\n\n\n");



   printf("\n\n** BEGIN TEST No. 2 *************************************************************\n");
   printf("** choice1 = 1, +1 buy, discard estate and gain +4 coins\n");
   printf("** discards increase by 1, buys increase by 1, coins increase by 4 \n\n\n");

   // copy game state for test game
   memcpy(&testGame, &G, sizeof(struct gameState));


   // Players Hand
   printf("Players Hand Before Play:\n");
   handCount = testGame.handCount[currPlayer];
   printf("Player %d's hand:\n", currPlayer);
   if(handCount > 0) printf("#  Card\n");
   for(handIndex = 0; handIndex < handCount; handIndex++) {
      int card = testGame.hand[currPlayer][handIndex];
      char name[32];
      cardNumToName(card, name);
      printf("%-2d %-13s\n", handIndex, name);
   }
   printf("\n");



   choice1 = 1;
   cardEffect(baron, choice1, choice2, choice3, &testGame, handPos, &bonus);
   
   if (G.numBuys + 1 == testGame.numBuys) {
      printf("OK:  the number of buys has increased by 1.\n");
      printf("Number of buys before play = %d\n", G.numBuys);
      printf("Number of buys after play = %d,  ", testGame.numBuys);
      printf("Number of buys expected = %d\n\n", G.numBuys + 1);
   }
   else {
      printf("ERROR:  the number of buys did not increase by 1.\n");
      printf("Number of buys before play = %d\n", G.numBuys);
      printf("Number of buys after play = %d,  ", testGame.numBuys);
      printf("Number of buys expected = %d\n\n", G.numBuys + 1);
   }


   if (testGame.discardCount[currPlayer] == G.discardCount[currPlayer] + 1) {
      printf("OK:  the number of discards has increased by 1 for discarding an estate.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = 1\n");
      int card = testGame.discard[currPlayer][0];
      char name[32];
      cardNumToName(card, name);
      printf("Discard is: %-13s \n\n", name);
   }
   else {
      printf("ERROR:  the number of discards did not increase by 1 for discarding an estate.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = 1\n\n");
   }


   if (G.coins + 4 == testGame.coins) {
      printf("OK:  the number of coins has increased by 4.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins + 4);
   }
   else {
      printf("ERROR:  the number of coins did not increase by 4.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins + 4);
   }


   // Players Hand
   printf("Players Hand After Play:\n");
   handCount = testGame.handCount[currPlayer];
   printf("Player %d's hand:\n", currPlayer);
   if(handCount > 0) printf("#  Card\n");
   for(handIndex = 0; handIndex < handCount; handIndex++) {
      int card = testGame.hand[currPlayer][handIndex];
      char name[32];
      cardNumToName(card, name);
      printf("%-2d %-13s\n", handIndex, name);
   }
   printf("\n\n");



   printf("** END TEST No. 2 *************************************************************\n\n\n\n");




   // begin testing
   printf("\n\n** BEGIN TEST No. 3 *************************************************************\n");
   printf("** choice1 = -1, gain an estate, +1 buy\n");
   printf("** supply decreases by 1 and discards increase by 1 (for new estate), buys increases by 1 \n\n\n");

   // copy game state for test game
   memcpy(&testGame, &G, sizeof(struct gameState));

 
   // Players Hand
   printf("Players Hand Before Play:\n");
    handCount = testGame.handCount[currPlayer];
    printf("Player %d's hand:\n", currPlayer);
    if(handCount > 0) printf("#  Card\n");
    for(handIndex = 0; handIndex < handCount; handIndex++) {
        int card = testGame.hand[currPlayer][handIndex];
        char name[32];
        cardNumToName(card, name);
        printf("%-2d %-13s\n", handIndex, name);
    }
    printf("\n");


   choice1 = -1;
   cardEffect(baron, choice1, choice2, choice3, &testGame, handPos, &bonus);


   if (testGame.supplyCount[estate] == G.supplyCount[estate] - 1) {
      printf("OK:  the number of Estates in the supply is one less than before playing baron.\n");
      printf("Number of estates in supply before play = %d\n", G.supplyCount[estate]);
      printf("Number of estates in supply after play = %d,  ", testGame.supplyCount[estate]);
      printf("Number of estates in supply expected = %d\n\n", G.supplyCount[estate] -1);
   }

   else {
      printf("ERROR:  the number of Estates in the supply is not one less than before playing baron.\n");
      printf("Number of estates in supply before play = %d\n", G.supplyCount[estate]);
      printf("Number of estates in supply after play = %d,  ", testGame.supplyCount[estate]);
      printf("Number of estates in supply expected = %d\n\n", G.supplyCount[estate] -1);

   }

   if (testGame.discardCount[currPlayer] == G.discardCount[currPlayer] + 1) {
      printf("OK:  the number of discards has increased by 1 for gaining an estate.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = 1\n");
      int card = testGame.discard[currPlayer][0];
      char name[32];
      cardNumToName(card, name);
      printf("Discard is: %-13s \n\n", name);
   }
   else {
      printf("ERROR:  the number of discards did not increase by 1 for gaining an estate.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = 1\n\n");
   }
 
   if (G.numBuys + 1 == testGame.numBuys) {
      printf("OK:  the number of buys has increased by 1.\n");
      printf("Number of buys before play = %d\n", G.numBuys);
      printf("Number of buys after play = %d,  ", testGame.numBuys);
      printf("Number of buys expected = %d\n\n", G.numBuys + 1);
   }
   else {
      printf("ERROR:  the number of buys did not increase by 1.\n");
      printf("Number of buys before play = %d\n", G.numBuys);
      printf("Number of buys after play = %d,  ", testGame.numBuys);
      printf("Number of buys expected = %d\n\n", G.numBuys + 1);
   }


   // Players Hand
   printf("Players Hand After Play:\n");
   handCount = testGame.handCount[currPlayer];
   printf("Player %d's hand:\n", currPlayer);
   if(handCount > 0) printf("#  Card\n");
   for(handIndex = 0; handIndex < handCount; handIndex++) {
      int card = testGame.hand[currPlayer][handIndex];
      char name[32];
      cardNumToName(card, name);
      printf("%-2d %-13s\n", handIndex, name);
   }
   printf("\n\n");


   printf("** END TEST No. 3 *************************************************************\n\n\n\n");




   // begin testing
   printf("\n\n** BEGIN TEST No. 4 *************************************************************\n");
   printf("** choice1 = 0, gain an estate, +1 buy\n");
   printf("** supply decreases by 1 and discards increase by 1 (for new estate), buys increases by 1 \n\n\n");

   G.hand[currPlayer][0] = copper;
   G.hand[currPlayer][1] = copper;
   G.hand[currPlayer][2] = copper;
   G.hand[currPlayer][3] = copper;
   G.hand[currPlayer][4] = copper;

   // copy game state for test game
   memcpy(&testGame, &G, sizeof(struct gameState));


   // Players Hand
   printf("Players Hand Before Play:\n");
    handCount = testGame.handCount[currPlayer];
    printf("Player %d's hand:\n", currPlayer);
    if(handCount > 0) printf("#  Card\n");
    for(handIndex = 0; handIndex < handCount; handIndex++) {
        int card = testGame.hand[currPlayer][handIndex];
        char name[32];
        cardNumToName(card, name);
        printf("%-2d %-13s\n", handIndex, name);
    }
    printf("\n");

   choice1 = 0;
   cardEffect(baron, choice1, choice2, choice3, &testGame, handPos, &bonus);


   if (G.numBuys + 1 == testGame.numBuys) {
      printf("OK:  the number of buys has increased by 1.\n");
      printf("Number of buys before play = %d\n", G.numBuys);
      printf("Number of buys after play = %d,  ", testGame.numBuys);
      printf("Number of buys expected = %d\n\n", G.numBuys + 1);
   }
   else {
      printf("ERROR:  the number of buys did not increase by 1.\n");
      printf("Number of buys before play = %d\n", G.numBuys);
      printf("Number of buys after play = %d,  ", testGame.numBuys);
      printf("Number of buys expected = %d\n\n", G.numBuys + 1);
   }


   if (testGame.discardCount[currPlayer] == G.discardCount[currPlayer] + 1) {
      printf("OK:  the number of discards has increased by 1 for gaining an estate.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = 1\n");
      int card = testGame.discard[currPlayer][0];
      char name[32];
      cardNumToName(card, name);
      printf("Discard is: %-13s \n\n", name);
   }
   else {
      printf("ERROR:  the number of discards did not increase by 1 for gaining an estate.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = 1\n\n");
   }


   if (G.coins == testGame.coins) {
      printf("OK:  the number of coins remained the same.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins);
   }
   else {
      printf("ERROR:  the number of coins did not remain the same.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins);
   }


   // Players Hand
   printf("Players Hand After Play:\n");
   handCount = testGame.handCount[currPlayer];
   printf("Player %d's hand:\n", currPlayer);
   if(handCount > 0) printf("#  Card\n");
   for(handIndex = 0; handIndex < handCount; handIndex++) {
      int card = testGame.hand[currPlayer][handIndex];
      char name[32];
      cardNumToName(card, name);
      printf("%-2d %-13s\n", handIndex, name);
   }
   printf("\n\n");



 
   printf("** END TEST No. 4 *************************************************************\n\n\n\n");
   

   return 0;	
}
