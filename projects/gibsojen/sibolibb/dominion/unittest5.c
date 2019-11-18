#include "dominion.h"
#include "dominion_helpers.h"
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

   int handPos = -1;
   int currPlayer = 0;
   int choice1 = 0;
   int choice2 = 0;
   int retError;
   int played = G.playedCardCount;
   int i;
   int pos = -1;
   int found = 0;

   // begin testing
   printf("\n\n** BEGIN TEST No. 1 *************************************************************\n");
   printf("** choice1 = 3 (silver), choice2 = 6 (gold)\n");
   printf("** silver will be trashed, gain a gold in hand, supply should decrease by 1\n");
   printf("** number of actions should stay the same, number of coins should stay the same\n\n\n");


   G.hand[currPlayer][0] = copper;
   G.hand[currPlayer][1] = copper;
   G.hand[currPlayer][2] = copper;
   G.hand[currPlayer][3] = silver;
   G.hand[currPlayer][4] = silver;
   G.handCount[currPlayer] = 5;


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

   handPos = 3;
   choice1 = 3;
   choice2 = gold;
   //cardEffect(minion, choice1, choice2, choice3, &testGame, handPos, &bonus);
   retError = mineEffect (choice1, choice2, handPos, &testGame, currPlayer);


   if (retError == 0) {
      printf("OK:  the return code of mine was 0.\n\n");
   }
   else if (retError == -1) {
      printf("ERROR:  the return code of mine was -1, however it should be 0.\n\n");
   }


   if (G.numActions  == testGame.numActions) {
      printf("OK:  the number of actions stayed the same.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }
   else {
      printf("ERROR:  the number of actions did not stay the same.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }


   if (G.coins == testGame.coins) {
      printf("OK:  the number of coins stayed the same.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins);
   }
   else {
      printf("ERROR:  the number of coins did not stay the same.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins);
   }


   if (testGame.discardCount[currPlayer] == G.discardCount[currPlayer] + 1) {
      printf("OK:  the number of discards increased by 1.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[currPlayer] + 1);
   }
   else {
      printf("ERROR:  the number of discards did not increase by 1.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[currPlayer] + 1);
   }

   if (testGame.playedCardCount == 0) {
      printf("OK:  the played card count is 0.\n");
      printf("Number of played cards before play = %d\n", played);
      printf("Number of played cards after play = %d,  ", testGame.playedCardCount);
      printf("Number of played cards expected = %d\n\n", played);
   }
   else {
      printf("ERROR:  the played card count is not 0.\n");
      printf("Number of played cards before play = %d\n", played);
      printf("Number of played cards after play = %d,  ", testGame.playedCardCount);
      printf("Number of played cards expected = %d\n\n", played);
      int i;
         for (i = 0; i < testGame.playedCardCount; i++) {
            int card = testGame.playedCards[i];
            char name[32];
            cardNumToName(card, name);
            printf("Played Card #%d is: %-13s \n", i, name);
         }
         printf("\n");
   }

   if (testGame.handCount[currPlayer] == G.handCount[currPlayer]) {
      printf("OK:  the number of card in players hand should remain the same, for exchanging two cards.\n");
      printf("Number of cards in players hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in players hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of card in players hand expected = %d\n\n", G.handCount[currPlayer]);
   }
   else {
      printf("ERROR:  the number of card in players hand changed.\n");
      printf("Number of cards in players hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in players hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of card in players hand expected = %d\n\n", G.handCount[currPlayer]);
   }


   
   if (testGame.supplyCount[choice2] == G.supplyCount[choice2] - 1) {
      printf("OK:  the supply decreased by 1.\n");
      printf("Number in supply before play = %d\n", G.supplyCount[choice2]);
      printf("Number in supply after play = %d,  ", testGame.supplyCount[choice2]);
      printf("Number in supply expected = %d\n\n", G.supplyCount[choice2] - 1);
   }
   else {
      printf("ERROR:  the supply did not decrease by 1.\n");
      printf("Number in supply before play = %d\n", G.supplyCount[choice2]);
      printf("Number in supply after play = %d,  ", testGame.supplyCount[choice2]);
      printf("Number in supply expected = %d\n\n", G.supplyCount[choice2] - 1);
   }

   pos = -1;
   found = 0;
   for (i = 0; i < testGame.handCount[currPlayer]; i++) {
      int card = testGame.hand[currPlayer][i];
      if (card == gold) {
         found = 1;
         pos = i;
      }
   }

   if (found) {
      printf("OK:  Gold was added to hand at position %d.\n\n", pos);
      if (pos == choice1) {
         printf("Gold was added to the correct position.\n\n");
      }
      else {
         printf("ERROR:  Gold was added to the wrong hand position.\n\n");
      }
   }
   else {
      printf("ERROR: Gold was not added to hand.\n");
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




   // begin testing
   printf("\n\n** BEGIN TEST No. 2 *************************************************************\n");
   printf("** choice1 = 3 (silver), choice2 = duchy\n");
   printf("** nothing should happen because you can't buy duchy with silver\n");
   printf("** number of actions should stay the same, number of coins should stay the same\n\n\n");


   G.hand[currPlayer][0] = copper;
   G.hand[currPlayer][1] = mine;
   G.hand[currPlayer][2] = copper;
   G.hand[currPlayer][3] = silver;
   G.hand[currPlayer][4] = silver;
   G.handCount[currPlayer] = 5;


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


   handPos = 1;
   choice1 = 3;
   choice2 = duchy;
   //cardEffect(minion, choice1, choice2, choice3, &testGame, handPos, &bonus);
   retError = mineEffect (choice1, choice2, handPos, &testGame, currPlayer);


   if (retError == -1) {
      printf("ERROR:  there was a return error in mineCard of -1 because you can't buy duchy with silver.\n\n");
   }
   else if (retError == 0) {
      printf("OK:  the return code of mine is 0.\n\n");
   }


   if (G.numActions  == testGame.numActions) {
      printf("OK:  the number of actions stayed the same.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }
   else {
      printf("ERROR:  the number of actions did not stay the same.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }


   if (G.coins == testGame.coins) {
      printf("OK:  the number of coins stayed the same.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins);
   }
   else {
      printf("ERROR:  the number of coins did not stay the same.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins);
   }


   if (testGame.discardCount[currPlayer] == G.discardCount[currPlayer]) {
      printf("OK:  the number of discards should remain the same\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[currPlayer]);
   }
   else {
      printf("ERROR:  the number of discards did not remain the same.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[currPlayer]);
   }


   if (testGame.playedCardCount == 0) {
      printf("OK:  the played card count is 0.\n");
      printf("Number of played cards before play = %d\n", played);
      printf("Number of played cards after play = %d,  ", testGame.playedCardCount);
      printf("Number of played cards expected = %d\n\n", played);
   }
   else {
      printf("ERROR:  the played card count is not 0.\n");
      printf("Number of played cards before play = %d\n", played);
      printf("Number of played cards after play = %d,  ", testGame.playedCardCount);
      printf("Number of played cards expected = %d\n\n", played);
      int i;
         for (i = 0; i < testGame.playedCardCount; i++) {
            int card = testGame.playedCards[i];
            char name[32];
            cardNumToName(card, name);
            printf("Played Card #%d is: %-13s \n", i, name);
         }
         printf("\n");
   }

   if (testGame.handCount[currPlayer] == G.handCount[currPlayer]) {
      printf("OK:  the number of card in players hand should remain the same.\n");
      printf("Number of cards in players hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in players hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of card in players hand expected = %d\n\n", G.handCount[currPlayer]);
   }
   else {
      printf("ERROR:  the number of card in players hand changed.\n");
      printf("Number of cards in players hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in players hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of card in players hand expected = %d\n\n", G.handCount[currPlayer]);
   }


   
   if (testGame.supplyCount[choice2] == G.supplyCount[choice2]) {
      printf("OK:  the supply should remain the same.\n");
      printf("Number in supply before play = %d\n", G.supplyCount[choice2]);
      printf("Number in supply after play = %d,  ", testGame.supplyCount[choice2]);
      printf("Number in supply expected = %d\n\n", G.supplyCount[choice2]);
   }
   else {
      printf("ERROR:  the supply did not remain the same.\n");
      printf("Number in supply before play = %d\n", G.supplyCount[choice2]);
      printf("Number in supply after play = %d,  ", testGame.supplyCount[choice2]);
      printf("Number in supply expected = %d\n\n", G.supplyCount[choice2]);
   }


   pos = -1;
   found = 0;
   for (i = 0; i < testGame.handCount[currPlayer]; i++) {
      int card = testGame.hand[currPlayer][i];
      if (card == duchy) {
         found = 1;
         pos = i;
      }
   }

   if (!found) {
      printf("OK:  Duchy was not added to hand.\n\n");
   }
   else {
      printf("ERROR: Duchy has been added to hand.\n");
      printf("Duchy was found in position %d\n\n", pos);
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
   printf("** choice1 = 1 (copper), choice2 = gold\n");
   printf("** cannot buy gold from copper, so nothing will happen\n");
   printf("** number of actions should stay the same, number of coins should stay the same\n\n\n");


   G.hand[currPlayer][0] = copper;
   G.hand[currPlayer][1] = copper;
   G.hand[currPlayer][2] = copper;
   G.hand[currPlayer][3] = mine;
   G.hand[currPlayer][4] = silver;
   G.handCount[currPlayer] = 5;


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


   handPos = 3;
   choice1 = 1;
   choice2 = gold;
   //cardEffect(minion, choice1, choice2, choice3, &testGame, handPos, &bonus);
   retError = mineEffect (choice1, choice2, handPos, &testGame, currPlayer);


   if (retError == -1) {
      printf("ERROR:  there was a return error in mineCard of -1 because you can't buy gold with copper.\n\n");
   }
   else if (retError == 0) {
      printf("OK:  the return code of mine was 0, however it should be -1 because you can't buy gold with copper.\n\n");
   }



   if (G.numActions  == testGame.numActions) {
      printf("OK:  the number of actions stayed the same.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }
   else {
      printf("ERROR:  the number of actions did not stay the same.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }


   if (G.coins == testGame.coins) {
      printf("OK:  the number of coins stayed the same.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins);
   }
   else {
      printf("ERROR:  the number of coins did not stay the same.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins);
   }



   if (testGame.discardCount[currPlayer] == G.discardCount[currPlayer]) {
      printf("OK:  the number of discards should remain the same\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[currPlayer]);
   }
   else {
      printf("ERROR:  the number of discards did not remain the same.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[currPlayer]);
   }

   if (testGame.playedCardCount == 0) {
      printf("OK:  the played card count is 0.\n");
      printf("Number of played cards before play = %d\n", played);
      printf("Number of played cards after play = %d,  ", testGame.playedCardCount);
      printf("Number of played cards expected = %d\n\n", played);
   }
   else {
      printf("ERROR:  the played card count is not 0.\n");
      printf("Number of played cards before play = %d\n", played);
      printf("Number of played cards after play = %d,  ", testGame.playedCardCount);
      printf("Number of played cards expected = %d\n\n", played);
      int i;
         for (i = 0; i < testGame.playedCardCount; i++) {
            int card = testGame.playedCards[i];
            char name[32];
            cardNumToName(card, name);
            printf("Played Card #%d is: %-13s \n", i, name);
         }
         printf("\n");
   }

   if (testGame.handCount[currPlayer] == G.handCount[currPlayer]) {
      printf("OK:  the number of card in players hand should remain the same.\n");
      printf("Number of cards in players hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in players hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of card in players hand expected = %d\n\n", G.handCount[currPlayer]);
   }
   else {
      printf("ERROR:  the number of card in players hand changed.\n");
      printf("Number of cards in players hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in players hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of card in players hand expected = %d\n\n", G.handCount[currPlayer]);
   }


   
   if (testGame.supplyCount[choice2] == G.supplyCount[choice2]) {
      printf("OK:  the supply should remain the same.\n");
      printf("Number in supply before play = %d\n", G.supplyCount[choice2]);
      printf("Number in supply after play = %d,  ", testGame.supplyCount[choice2]);
      printf("Number in supply expected = %d\n\n", G.supplyCount[choice2]);
   }
   else {
      printf("ERROR:  the supply did not remain the same.\n");
      printf("Number in supply before play = %d\n", G.supplyCount[choice2]);
      printf("Number in supply after play = %d,  ", testGame.supplyCount[choice2]);
      printf("Number in supply expected = %d\n\n", G.supplyCount[choice2]);
   }


   pos = -1;
   found = 0;
   for (i = 0; i < testGame.handCount[currPlayer]; i++) {
      int card = testGame.hand[currPlayer][i];
      if (card == gold) {
         found = 1;
         pos = i;
      }
   }

   if (!found) {
      printf("OK:  Gold was not added to hand.\n\n");
   }
   else {
      printf("ERROR: Gold has been added to hand.\n");
      printf("Gold was found in position %d\n\n", pos);
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
   printf("** choice1 = 3 (gold), choice2 = copper\n");
   printf("** should be possible, though not smart. gain a copper in hand, supply should decrease by 1\n");
   printf("** number of actions should stay the same, number of coins should stay the same\n\n\n");


   G.hand[currPlayer][0] = minion;
   G.hand[currPlayer][1] = mine;
   G.hand[currPlayer][2] = silver;
   G.hand[currPlayer][3] = gold;
   G.hand[currPlayer][4] = silver;
   G.handCount[currPlayer] = 5;


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

   handPos = 1;
   choice1 = 3;
   choice2 = copper;
   //cardEffect(minion, choice1, choice2, choice3, &testGame, handPos, &bonus);
   retError = mineEffect (choice1, choice2, handPos, &testGame, currPlayer);


   if (retError == 0) {
      printf("OK:  the return code of mine was 0.\n\n");
   }
   else if (retError == -1) {
      printf("ERROR:  the return code of mine was -1, however it should be 0.\n\n");
   }


   if (G.numActions  == testGame.numActions) {
      printf("OK:  the number of actions stayed the same.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }
   else {
      printf("ERROR:  the number of actions did not stay the same.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }


   if (G.coins == testGame.coins) {
      printf("OK:  the number of coins stayed the same.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins);
   }
   else {
      printf("ERROR:  the number of coins did not stay the same.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins);
   }


   if (testGame.discardCount[currPlayer] == G.discardCount[currPlayer] + 1) {
      printf("OK:  the number of discards increased by 1.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[currPlayer] + 1);
   }
   else {
      printf("ERROR:  the number of discards did not increase by 1.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[currPlayer] + 1);
   }

   if (testGame.playedCardCount == 0) {
      printf("OK:  the played card count is 0.\n");
      printf("Number of played cards before play = %d\n", played);
      printf("Number of played cards after play = %d,  ", testGame.playedCardCount);
      printf("Number of played cards expected = %d\n\n", played);
   }
   else {
      printf("ERROR:  the played card count is not 0.\n");
      printf("Number of played cards before play = %d\n", played);
      printf("Number of played cards after play = %d,  ", testGame.playedCardCount);
      printf("Number of played cards expected = %d\n\n", played);
      int i;
         for (i = 0; i < testGame.playedCardCount; i++) {
            int card = testGame.playedCards[i];
            char name[32];
            cardNumToName(card, name);
            printf("Played Card #%d is: %-13s \n", i, name);
         }
         printf("\n");
   }

   if (testGame.handCount[currPlayer] == G.handCount[currPlayer]) {
      printf("OK:  the number of card in players hand should remain the same, for exchanging two cards.\n");
      printf("Number of cards in players hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in players hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of card in players hand expected = %d\n\n", G.handCount[currPlayer]);
   }
   else {
      printf("ERROR:  the number of card in players hand changed.\n");
      printf("Number of cards in players hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in players hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of card in players hand expected = %d\n\n", G.handCount[currPlayer]);
   }


   
   if (testGame.supplyCount[choice2] == G.supplyCount[choice2] - 1) {
      printf("OK:  the supply decreased by 1.\n");
      printf("Number in supply before play = %d\n", G.supplyCount[choice2]);
      printf("Number in supply after play = %d,  ", testGame.supplyCount[choice2]);
      printf("Number in supply expected = %d\n\n", G.supplyCount[choice2] - 1);
   }
   else {
      printf("ERROR:  the supply did not decrease by 1.\n");
      printf("Number in supply before play = %d\n", G.supplyCount[choice2]);
      printf("Number in supply after play = %d,  ", testGame.supplyCount[choice2]);
      printf("Number in supply expected = %d\n\n", G.supplyCount[choice2] - 1);
   }


   pos = -1;
   found = 0;
   for (i = 0; i < testGame.handCount[currPlayer]; i++) {
      int card = testGame.hand[currPlayer][i];
      if (card == copper) {
         found = 1;
         pos = i;
      }
   }

   if (found) {
      printf("OK:  Copper was added to hand at position %d.\n", pos);
      if (pos == choice1) {
         printf("Copper was added to the correct position.\n\n");
      }
      else {
         printf("ERROR:  Copper was added to the wrong hand position.\n\n");
      }
   }
   else {
      printf("ERROR: Copper was not added to hand.\n\n");
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



   // begin testing
   printf("\n\n** BEGIN TEST No. 5 *************************************************************\n");
   printf("** choice1 = 1 (estate), choice2 = silver\n");
   printf("** nothing should happen because you can't buy duchy with silver\n");
   printf("** number of actions should stay the same, number of coins should stay the same\n\n\n");


   G.hand[currPlayer][0] = copper;
   G.hand[currPlayer][1] = estate;
   G.hand[currPlayer][2] = copper;
   G.hand[currPlayer][3] = mine;
   G.hand[currPlayer][4] = gold;
   G.handCount[currPlayer] = 5;


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


   handPos = 3;
   choice1 = 1;
   choice2 = silver;
   //cardEffect(minion, choice1, choice2, choice3, &testGame, handPos, &bonus);
   retError = mineEffect (choice1, choice2, handPos, &testGame, currPlayer);


   if (retError == -1) {
      printf("ERROR:  there was a return error in mineCard of -1 because you can't buy silver with estate.\n\n");
   }
   else if (retError == 0) {
      printf("OK:  the return code of mine was 0, however it should be -1 because you can't buy silver with estate.\n\n");
   }


   if (G.numActions  == testGame.numActions) {
      printf("OK:  the number of actions stayed the same.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }
   else {
      printf("ERROR:  the number of actions did not stay the same.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }


   if (G.coins == testGame.coins) {
      printf("OK:  the number of coins stayed the same.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins);
   }
   else {
      printf("ERROR:  the number of coins did not stay the same.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins);
   }


   if (testGame.discardCount[currPlayer] == G.discardCount[currPlayer]) {
      printf("OK:  the number of discards should remain the same\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[currPlayer]);
   }
   else {
      printf("ERROR:  the number of discards did not remain the same.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[currPlayer]);
   }


   if (testGame.playedCardCount == 0) {
      printf("OK:  the played card count is 0.\n");
      printf("Number of played cards before play = %d\n", played);
      printf("Number of played cards after play = %d,  ", testGame.playedCardCount);
      printf("Number of played cards expected = %d\n\n", played);
   }
   else {
      printf("ERROR:  the played card count is not 0.\n");
      printf("Number of played cards before play = %d\n", played);
      printf("Number of played cards after play = %d,  ", testGame.playedCardCount);
      printf("Number of played cards expected = %d\n\n", played);
      int i;
         for (i = 0; i < testGame.playedCardCount; i++) {
            int card = testGame.playedCards[i];
            char name[32];
            cardNumToName(card, name);
            printf("Played Card #%d is: %-13s \n", i, name);
         }
         printf("\n");
   }

   if (testGame.handCount[currPlayer] == G.handCount[currPlayer]) {
      printf("OK:  the number of card in players hand should remain the same.\n");
      printf("Number of cards in players hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in players hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of card in players hand expected = %d\n\n", G.handCount[currPlayer]);
   }
   else {
      printf("ERROR:  the number of card in players hand changed.\n");
      printf("Number of cards in players hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in players hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of card in players hand expected = %d\n\n", G.handCount[currPlayer]);
   }


   
   if (testGame.supplyCount[choice2] == G.supplyCount[choice2]) {
      printf("OK:  the supply should remain the same.\n");
      printf("Number in supply before play = %d\n", G.supplyCount[choice2]);
      printf("Number in supply after play = %d,  ", testGame.supplyCount[choice2]);
      printf("Number in supply expected = %d\n\n", G.supplyCount[choice2]);
   }
   else {
      printf("ERROR:  the supply did not remain the same.\n");
      printf("Number in supply before play = %d\n", G.supplyCount[choice2]);
      printf("Number in supply after play = %d,  ", testGame.supplyCount[choice2]);
      printf("Number in supply expected = %d\n\n", G.supplyCount[choice2]);
   }



   pos = -1;
   found = 0;
   for (i = 0; i < testGame.handCount[currPlayer]; i++) {
      int card = testGame.hand[currPlayer][i];
      if (card == silver) {
         found = 1;
         pos = i;
      }
   }

   if (!found) {
      printf("OK:  Silver was not added to hand.\n\n");
   }
   else {
      printf("ERROR: Silver has been added to hand.\n");
      printf("Silver was found in position %d\n\n", pos);
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


   printf("** END TEST No. 5 *************************************************************\n\n\n\n");



   // begin testing
   printf("\n\n** BEGIN TEST No. 6 *************************************************************\n");
   printf("** choice1 = 4 (copper), choice2 = silver\n");
   printf("** this is testing silver (5) in the 5 position of the hand\n");
   printf("** number of actions should stay the same, number of coins should stay the same\n");
   printf("** supply decrease by 1, hand count remains the same, discard increase by 1\n\n\n");


   G.hand[currPlayer][0] = mine;
   G.hand[currPlayer][1] = province;
   G.hand[currPlayer][2] = curse;
   G.hand[currPlayer][3] = estate;
   G.hand[currPlayer][4] = copper;
   G.hand[currPlayer][5] = duchy;
   G.handCount[currPlayer] = 6;


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

   handPos = 0;
   choice1 = 4;
   choice2 = silver;
   //cardEffect(minion, choice1, choice2, choice3, &testGame, handPos, &bonus);
   retError = mineEffect (choice1, choice2, handPos, &testGame, currPlayer);


   if (retError == 0) {
      printf("OK:  the return code of mine was 0.\n\n");
   }
   else if (retError == -1) {
      printf("ERROR:  the return code of mine was -1, however it should be 0.\n\n");
   }


   if (G.numActions  == testGame.numActions) {
      printf("OK:  the number of actions stayed the same.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }
   else {
      printf("ERROR:  the number of actions did not stay the same.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }


   if (G.coins == testGame.coins) {
      printf("OK:  the number of coins stayed the same.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins);
   }
   else {
      printf("ERROR:  the number of coins did not stay the same.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins);
   }


   if (testGame.discardCount[currPlayer] == G.discardCount[currPlayer] + 1) {
      printf("OK:  the number of discards increased by 1.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[currPlayer] + 1);
   }
   else {
      printf("ERROR:  the number of discards did not increase by 1.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[currPlayer] + 1);
   }

   if (testGame.playedCardCount == 0) {
      printf("OK:  the played card count is 0.\n");
      printf("Number of played cards before play = %d\n", played);
      printf("Number of played cards after play = %d,  ", testGame.playedCardCount);
      printf("Number of played cards expected = %d\n\n", played);
   }
   else {
      printf("ERROR:  the played card count is not 0.\n");
      printf("Number of played cards before play = %d\n", played);
      printf("Number of played cards after play = %d,  ", testGame.playedCardCount);
      printf("Number of played cards expected = %d\n\n", played);
      int i;
         for (i = 0; i < testGame.playedCardCount; i++) {
            int card = testGame.playedCards[i];
            char name[32];
            cardNumToName(card, name);
            printf("Played Card #%d is: %-13s \n", i, name);
         }
         printf("\n");
   }

   if (testGame.handCount[currPlayer] == G.handCount[currPlayer]) {
      printf("OK:  the number of card in players hand should remain the same, for exchanging two cards.\n");
      printf("Number of cards in players hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in players hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of card in players hand expected = %d\n\n", G.handCount[currPlayer]);
   }
   else {
      printf("ERROR:  the number of card in players hand changed.\n");
      printf("Number of cards in players hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in players hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of card in players hand expected = %d\n\n", G.handCount[currPlayer]);
   }


   
   if (testGame.supplyCount[choice2] == G.supplyCount[choice2] - 1) {
      printf("OK:  the supply decreased by 1.\n");
      printf("Number in supply before play = %d\n", G.supplyCount[choice2]);
      printf("Number in supply after play = %d,  ", testGame.supplyCount[choice2]);
      printf("Number in supply expected = %d\n\n", G.supplyCount[choice2] - 1);
   }
   else {
      printf("ERROR:  the supply did not decrease by 1.\n");
      printf("Number in supply before play = %d\n", G.supplyCount[choice2]);
      printf("Number in supply after play = %d,  ", testGame.supplyCount[choice2]);
      printf("Number in supply expected = %d\n\n", G.supplyCount[choice2] - 1);
   }


   pos = -1;
   found = 0;
   for (i = 0; i < testGame.handCount[currPlayer]; i++) {
      int card = testGame.hand[currPlayer][i];
      if (card == silver) {
         found = 1;
         pos = i;
      }
   }

   if (found) {
      printf("OK:  Silver was added to hand at position %d.\n\n", pos);
      if (pos == choice1) {
         printf("Silver was added to the correct position.\n\n");
      }
      else {
         printf("ERROR:  Silver was added to the wrong hand position.\n\n");
      }
   }
   else {
      printf("ERROR: Silver was not added to hand.\n\n");
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



   printf("** END TEST No. 6 *************************************************************\n\n\n\n");


   return 0;	
}
