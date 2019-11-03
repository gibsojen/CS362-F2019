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
   int k[10] = {adventurer, baron, ambassador, embargo, village, minion, mine, cutpurse, sea_hag, tribute};

   // initialize game
   initializeGame(numOfPlayers, k, seed, &G);

   //int handPos = -1;
   //int bonus = 0;
   int currPlayer = 0;
   int nextPlayer = 1;
   //int choice1 = 0;
   //int choice2 = 0;
   //int choice3 = 0;



   // begin testing
   printf("\n\n** BEGIN TEST No. 1 *************************************************************\n");
   printf("** 2 different treasure cards revealed, so +4 coins\n");
   printf("** current players actions remain the same, current players hand count should not change\n");
   printf("** next players deck should decrease by 2, next players discards should increase by 2 \n\n\n");


   G.hand[currPlayer][0] = baron;
   G.hand[currPlayer][1] = duchy;
   G.hand[currPlayer][2] = mine;
   G.hand[currPlayer][3] = minion;
   G.hand[currPlayer][4] = ambassador;
   G.handCount[currPlayer] = 5;


   G.deck[nextPlayer][0] = silver;
   G.deck[nextPlayer][1] = gold;
   G.deck[nextPlayer][2] = silver;
   G.deck[nextPlayer][3] = gold;
   G.deck[nextPlayer][4] = silver;
   G.deck[nextPlayer][5] = gold;
   G.deck[nextPlayer][6] = silver;
   G.deckCount[nextPlayer] = 5;

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



   // Next Players Deck
   printf("Next Players Deck Before Play:\n");
   int deckCount = testGame.deckCount[nextPlayer];
   int deckIndex; 
   printf("Player %d's deck:\n", nextPlayer);
   if(deckCount > 0) printf("#  Card\n");
   for(deckIndex = 0; deckIndex < deckCount; deckIndex++) {
       int card = testGame.deck[nextPlayer][deckIndex];
       char name[32];
       cardNumToName(card, name);
       printf("%-2d %-13s\n", deckIndex, name);
   }
   printf("\n");

   tributeCard (&testGame, currPlayer);


   if (G.deckCount[nextPlayer] - 2 == testGame.deckCount[nextPlayer]) {
      printf("OK:  the deck count of next player has decreased by 2.\n");
      printf("Number of cards in deck before play = %d\n", G.deckCount[nextPlayer]);
      printf("Number of cards in deck after play = %d,  ", testGame.deckCount[nextPlayer]);
      printf("Number of cards in deck expected = %d\n\n", G.deckCount[nextPlayer] - 2);
   }
   else {
      printf("ERROR:  the deck count of next player did not decrease by 2.\n");
      printf("Number of cards in deck before play = %d\n", G.deckCount[nextPlayer]);
      printf("Number of cards in deck after play = %d,  ", testGame.deckCount[nextPlayer]);
      printf("Number of cards in deck expected = %d\n\n", G.deckCount[nextPlayer] - 2);

   }


   if (G.discardCount[nextPlayer] + 2 == testGame.discardCount[nextPlayer]) {
      printf("OK:  the discard count of next player has increased by 2.\n");
      printf("Number of discards before play = %d\n", G.discardCount[nextPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[nextPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[nextPlayer] + 2);
   }
   else {
      printf("ERROR:  the discard count of next player did not decrease by 2.\n");
      printf("Number of discards before play = %d\n", G.discardCount[nextPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[nextPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[nextPlayer] + 2);
   }


   if (G.coins +4 == testGame.coins) {
      printf("OK:  the number of coins increased by 4, 2 for each treasure card.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins + 4);
   }
   else {
      printf("ERROR:  the number of coins did not increase by 4, 2 for each treasure card.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins + 4);
   }



   if (G.numActions == testGame.numActions) {
      printf("OK:  the number of actions remained the same.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }
   else if (G.numActions < testGame.numActions) {
      printf("ERROR:  the number of actions increased.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }
   else {
      printf("ERROR:  the number of actions decreased.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }



   if (G.handCount[currPlayer] == testGame.handCount[currPlayer]) {
      printf("OK:  the hand count of the current player has not changed.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.handCount[currPlayer]);
   }
   else if (G.handCount[currPlayer] < testGame.handCount[currPlayer]) {
      printf("ERROR:  the hand count of the current player has increased.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.deckCount[currPlayer]);
   }
   else {
      printf("ERROR:  the hand count of the current player has decreased.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.deckCount[currPlayer]);
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




   // Next Players Deck
   printf("Next Players Deck After Play:\n");
   deckCount = testGame.deckCount[nextPlayer];
   printf("Player %d's deck:\n", nextPlayer);
   if(deckCount > 0) printf("#  Card\n");
   for(deckIndex = 0; deckIndex < deckCount; deckIndex++) {
      int card = testGame.deck[nextPlayer][deckIndex];
      char name[32];
      cardNumToName(card, name);
      printf("%-2d %-13s\n", deckIndex, name);
   }
   printf("\n");



   printf("** END TEST No. 1 *************************************************************\n\n\n\n");




   // begin testing
   printf("\n\n** BEGIN TEST No. 2 *************************************************************\n");
   printf("** 2 different action cards revealed, so +2 actions per card\n");
   printf("** current players coins remain the same, current players hand count should not change\n");
   printf("** next players deck should decrease by 2, next players discards should increase by 2 \n\n\n");


   G.hand[currPlayer][0] = baron;
   G.hand[currPlayer][1] = duchy;
   G.hand[currPlayer][2] = mine;
   G.hand[currPlayer][3] = minion;
   G.hand[currPlayer][4] = ambassador;
   G.handCount[currPlayer] = 5;


   G.deck[nextPlayer][0] = remodel;
   G.deck[nextPlayer][1] = outpost;
   G.deck[nextPlayer][2] = feast;
   G.deck[nextPlayer][3] = adventurer;
   G.deck[nextPlayer][4] = tribute;
   G.deckCount[nextPlayer] = 5;

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



   // Next Players Deck
   printf("Next Players Deck Before Play:\n");
   deckCount = testGame.deckCount[nextPlayer];
   printf("Player %d's deck:\n", nextPlayer);
   if(deckCount > 0) printf("#  Card\n");
   for(deckIndex = 0; deckIndex < deckCount; deckIndex++) {
       int card = testGame.deck[nextPlayer][deckIndex];
       char name[32];
       cardNumToName(card, name);
       printf("%-2d %-13s\n", deckIndex, name);
   }
   printf("\n");

   tributeCard (&testGame, currPlayer);


   if (G.deckCount[nextPlayer] - 2 == testGame.deckCount[nextPlayer]) {
      printf("OK:  the deck count of next player has decreased by 2.\n");
      printf("Number of cards in deck before play = %d\n", G.deckCount[nextPlayer]);
      printf("Number of cards in deck after play = %d,  ", testGame.deckCount[nextPlayer]);
      printf("Number of cards in deck expected = %d\n\n", G.deckCount[nextPlayer] - 2);
   }
   else {
      printf("ERROR:  the deck count of next player did not decrease by 2.\n");
      printf("Number of cards in deck before play = %d\n", G.deckCount[nextPlayer]);
      printf("Number of cards in deck after play = %d,  ", testGame.deckCount[nextPlayer]);
      printf("Number of cards in deck expected = %d\n\n", G.deckCount[nextPlayer] - 2);

   }


   if (G.discardCount[nextPlayer] + 2 == testGame.discardCount[nextPlayer]) {
      printf("OK:  the discard count of next player has increased by 2.\n");
      printf("Number of discards before play = %d\n", G.discardCount[nextPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[nextPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[nextPlayer] + 2);
   }
   else {
      printf("ERROR:  the discard count of next player did not decrease by 2.\n");
      printf("Number of discards before play = %d\n", G.discardCount[nextPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[nextPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[nextPlayer] + 2);
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



   if (G.numActions + 2 == testGame.numActions) {
      printf("OK:  the number of actions increased by 2.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions + 2);
   }
   else {
      printf("ERROR:  the number of actions did not increase by 2.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions + 2);
   }



   if (G.handCount[currPlayer] == testGame.handCount[currPlayer]) {
      printf("OK:  the hand count of the current player has not changed.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.handCount[currPlayer]);
   }
   else if (G.handCount[currPlayer] < testGame.handCount[currPlayer]) {
      printf("ERROR:  the hand count of the current player has increased.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.deckCount[currPlayer]);
   }
   else {
      printf("ERROR:  the hand count of the current player has decreased.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.deckCount[currPlayer]);
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




   // Next Players Deck
   printf("Next Players Deck After Play:\n");
   deckCount = testGame.deckCount[nextPlayer];
   printf("Player %d's deck:\n", nextPlayer);
   if(deckCount > 0) printf("#  Card\n");
   for(deckIndex = 0; deckIndex < deckCount; deckIndex++) {
      int card = testGame.deck[nextPlayer][deckIndex];
      char name[32];
      cardNumToName(card, name);
      printf("%-2d %-13s\n", deckIndex, name);
   }
   printf("\n");



   printf("** END TEST No. 2 *************************************************************\n\n\n\n");


   
   // begin testing
   printf("\n\n** BEGIN TEST No. 3 *************************************************************\n");
   printf("** 2 different victory cards revealed, so +2 cards per card\n");
   printf("** current players coins remain the same, current players hand count should increase by 4, actions remain the same\n");
   printf("** next players deck should decrease by 2, next players discards should increase by 2 \n\n\n");


   G.hand[currPlayer][0] = baron;
   G.hand[currPlayer][1] = duchy;
   G.hand[currPlayer][2] = mine;
   G.hand[currPlayer][3] = minion;
   G.hand[currPlayer][4] = ambassador;
   G.handCount[currPlayer] = 5;


   G.deck[nextPlayer][0] = province;
   G.deck[nextPlayer][1] = duchy;
   G.deck[nextPlayer][2] = estate;
   G.deck[nextPlayer][3] = province;
   G.deck[nextPlayer][4] = duchy;
   G.deckCount[nextPlayer] = 5;

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



   // Next Players Deck
   printf("Next Players Deck Before Play:\n");
   deckCount = testGame.deckCount[nextPlayer];
   printf("Player %d's deck:\n", nextPlayer);
   if(deckCount > 0) printf("#  Card\n");
   for(deckIndex = 0; deckIndex < deckCount; deckIndex++) {
       int card = testGame.deck[nextPlayer][deckIndex];
       char name[32];
       cardNumToName(card, name);
       printf("%-2d %-13s\n", deckIndex, name);
   }
   printf("\n");

   tributeCard (&testGame, currPlayer);


   if (G.deckCount[nextPlayer] - 2 == testGame.deckCount[nextPlayer]) {
      printf("OK:  the deck count of next player has decreased by 2.\n");
      printf("Number of cards in deck before play = %d\n", G.deckCount[nextPlayer]);
      printf("Number of cards in deck after play = %d,  ", testGame.deckCount[nextPlayer]);
      printf("Number of cards in deck expected = %d\n\n", G.deckCount[nextPlayer] - 2);
   }
   else {
      printf("ERROR:  the deck count of next player did not decrease by 2.\n");
      printf("Number of cards in deck before play = %d\n", G.deckCount[nextPlayer]);
      printf("Number of cards in deck after play = %d,  ", testGame.deckCount[nextPlayer]);
      printf("Number of cards in deck expected = %d\n\n", G.deckCount[nextPlayer] - 2);

   }


   if (G.discardCount[nextPlayer] + 2 == testGame.discardCount[nextPlayer]) {
      printf("OK:  the discard count of next player has increased by 2.\n");
      printf("Number of discards before play = %d\n", G.discardCount[nextPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[nextPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[nextPlayer] + 2);
   }
   else {
      printf("ERROR:  the discard count of next player did not decrease by 2.\n");
      printf("Number of discards before play = %d\n", G.discardCount[nextPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[nextPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[nextPlayer] + 2);
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



   if (G.numActions == testGame.numActions) {
      printf("OK:  the number of actions remains the same.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }
   else {
      printf("ERROR:  the number of actions did not remain the same.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }



   if (G.handCount[currPlayer] + 4 == testGame.handCount[currPlayer]) {
      printf("OK:  the hand count has increased by 4 cards, +2 cards for each card by next player.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.handCount[currPlayer] + 4);
   }
   else {
      printf("ERROR:  the hand count has not increased by 4 cards, +2 cards for each card by next player.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.deckCount[currPlayer] + 4);
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



   // Next Players Deck
   printf("Next Players Deck After Play:\n");
   deckCount = testGame.deckCount[nextPlayer];
   printf("Player %d's deck:\n", nextPlayer);
   if(deckCount > 0) printf("#  Card\n");
   for(deckIndex = 0; deckIndex < deckCount; deckIndex++) {
      int card = testGame.deck[nextPlayer][deckIndex];
      char name[32];
      cardNumToName(card, name);
      printf("%-2d %-13s\n", deckIndex, name);
   }
   printf("\n");



   printf("** END TEST No. 3 *************************************************************\n\n\n\n");




   // begin testing
   printf("\n\n** BEGIN TEST No. 4 *************************************************************\n");
   printf("** 1 treasure card revealed (in next player's deck), +2 coins\n");
   printf("** current players hand count should not increase, actions remain the same\n");
   printf("** next players deck should decrease by 1, next players discards should increase by 1 \n\n\n");


   G.hand[currPlayer][0] = baron;
   G.hand[currPlayer][1] = duchy;
   G.hand[currPlayer][2] = mine;
   G.hand[currPlayer][3] = minion;
   G.hand[currPlayer][4] = ambassador;
   G.handCount[currPlayer] = 5;


   G.deck[nextPlayer][0] = gold;
   G.deckCount[nextPlayer] = 1;

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



   // Next Players Deck
   printf("Next Players Deck Before Play:\n");
   deckCount = testGame.deckCount[nextPlayer];
   printf("Player %d's deck:\n", nextPlayer);
   if(deckCount > 0) printf("#  Card\n");
   for(deckIndex = 0; deckIndex < deckCount; deckIndex++) {
       int card = testGame.deck[nextPlayer][deckIndex];
       char name[32];
       cardNumToName(card, name);
       printf("%-2d %-13s\n", deckIndex, name);
   }
   printf("\n");

   tributeCard (&testGame, currPlayer);


   if (G.deckCount[nextPlayer] - 1 == testGame.deckCount[nextPlayer]) {
      printf("OK:  the deck count of next player has decreased by 1.\n");
      printf("Number of cards in deck before play = %d\n", G.deckCount[nextPlayer]);
      printf("Number of cards in deck after play = %d,  ", testGame.deckCount[nextPlayer]);
      printf("Number of cards in deck expected = %d\n\n", G.deckCount[nextPlayer] - 1);
   }
   else {
      printf("ERROR:  the deck count of next player did not decrease by 1.\n");
      printf("Number of cards in deck before play = %d\n", G.deckCount[nextPlayer]);
      printf("Number of cards in deck after play = %d,  ", testGame.deckCount[nextPlayer]);
      printf("Number of cards in deck expected = %d\n\n", G.deckCount[nextPlayer] - 1);

   }


   if (G.discardCount[nextPlayer] + 1 == testGame.discardCount[nextPlayer]) {
      printf("OK:  the discard count of next player has increased by 1.\n");
      printf("Number of discards before play = %d\n", G.discardCount[nextPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[nextPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[nextPlayer] + 1);
   }
   else {
      printf("ERROR:  the discard count of next player did not decrease by 1.\n");
      printf("Number of discards before play = %d\n", G.discardCount[nextPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[nextPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[nextPlayer] + 1);
   }


   if (G.coins + 2 == testGame.coins) {
      printf("OK:  the number of coins increased by 2.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins + 2);
   }
   else {
      printf("ERROR:  the number of coins did not increase by 2.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins + 2);
   }



   if (G.numActions == testGame.numActions) {
      printf("OK:  the number of actions remains the same.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }
   else {
      printf("ERROR:  the number of actions did not remain the same.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }



   if (G.handCount[currPlayer] == testGame.handCount[currPlayer]) {
      printf("OK:  the hand count remains the same.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.handCount[currPlayer]);
   }
   else if(G.handCount[currPlayer] < testGame.handCount[currPlayer]) {
      printf("ERROR:  the hand count increased.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.deckCount[currPlayer]);
   }
   else {
      printf("ERROR:  the hand count decreased.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.deckCount[currPlayer]);
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



   // Next Players Deck
   printf("Next Players Deck After Play:\n");
   deckCount = testGame.deckCount[nextPlayer];
   printf("Player %d's deck:\n", nextPlayer);
   if(deckCount > 0) printf("#  Card\n");
   for(deckIndex = 0; deckIndex < deckCount; deckIndex++) {
      int card = testGame.deck[nextPlayer][deckIndex];
      char name[32];
      cardNumToName(card, name);
      printf("%-2d %-13s\n", deckIndex, name);
   }
   printf("\n");


   printf("** END TEST No. 4 *************************************************************\n\n\n\n");


   // begin testing
   printf("\n\n** BEGIN TEST No. 5 *************************************************************\n");
   printf("** 1 treasure card revealed (in next player's discards), +2 coins\n");
   printf("** current players hand count should not increase, actions remain the same\n");
   printf("** next players deck should decrease by 1, next players discards should increase by 1 \n\n\n");


   G.hand[currPlayer][0] = baron;
   G.hand[currPlayer][1] = duchy;
   G.hand[currPlayer][2] = mine;
   G.hand[currPlayer][3] = minion;
   G.hand[currPlayer][4] = ambassador;
   G.handCount[currPlayer] = 5;


   //G.deck[nextPlayer][0] = gold;
   G.deckCount[nextPlayer] = 0;
   G.discard[nextPlayer][0] = gold;
   G.discardCount[nextPlayer] = 1;

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



   // Next Players Deck
   printf("Next Players Deck Before Play:\n");
   deckCount = testGame.deckCount[nextPlayer];
   printf("Player %d's deck:\n", nextPlayer);
   if(deckCount > 0) printf("#  Card\n");
   for(deckIndex = 0; deckIndex < deckCount; deckIndex++) {
       int card = testGame.deck[nextPlayer][deckIndex];
       char name[32];
       cardNumToName(card, name);
       printf("%-2d %-13s\n", deckIndex, name);
   }
   printf("\n");


   // Next Players Discards
   printf("Next Players Discards Before Play:\n");
   int discardCount = testGame.discardCount[nextPlayer];
   printf("Player %d's discards:\n", nextPlayer);
   if(discardCount > 0) printf("#  Card\n");
   for(deckIndex = 0; deckIndex < discardCount; deckIndex++) {
       int card = testGame.discard[nextPlayer][deckIndex];
       char name[32];
       cardNumToName(card, name);
       printf("%-2d %-13s\n", deckIndex, name);
   }
   printf("\n");



   tributeCard (&testGame, currPlayer);



   if (G.discardCount[nextPlayer]  == testGame.discardCount[nextPlayer]) {
      printf("OK:  the discard count of next players remains the same since card came from discards, not deck.\n");
      printf("Number of discards before play = %d\n", G.discardCount[nextPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[nextPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[nextPlayer]);
   }
   else {
      printf("ERROR:  the discard count of next players did not remain the same.  The card came from discards not deck, so count should not change.\n");
      printf("Number of discards before play = %d\n", G.discardCount[nextPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[nextPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[nextPlayer]);
   }


   if (G.coins + 2 == testGame.coins) {
      printf("OK:  the number of coins increased by 2.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins + 2);
   }
   else {
      printf("ERROR:  the number of coins did not increase by 2.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins + 2);
   }



   if (G.numActions == testGame.numActions) {
      printf("OK:  the number of actions remains the same.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }
   else {
      printf("ERROR:  the number of actions did not remain the same.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }



   if (G.handCount[currPlayer] == testGame.handCount[currPlayer]) {
      printf("OK:  the hand count remains the same.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.handCount[currPlayer]);
   }
   else if(G.handCount[currPlayer] < testGame.handCount[currPlayer]) {
      printf("ERROR:  the hand count increased.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.deckCount[currPlayer]);
   }
   else {
      printf("ERROR:  the hand count decreased.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.deckCount[currPlayer]);
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



   // Next Players Deck
   printf("Next Players Deck After Play:\n");
   deckCount = testGame.deckCount[nextPlayer];
   printf("Player %d's deck:\n", nextPlayer);
   if(deckCount > 0) printf("#  Card\n");
   for(deckIndex = 0; deckIndex < deckCount; deckIndex++) {
      int card = testGame.deck[nextPlayer][deckIndex];
      char name[32];
      cardNumToName(card, name);
      printf("%-2d %-13s\n", deckIndex, name);
   }
   printf("\n");



   // Next Players Discards
   printf("Next Players Discards Before Play:\n");
   discardCount = testGame.discardCount[nextPlayer];
   printf("Player %d's discards:\n", nextPlayer);
   if(discardCount > 0) printf("#  Card\n");
   for(deckIndex = 0; deckIndex < discardCount; deckIndex++) {
       int card = testGame.discard[nextPlayer][deckIndex];
       char name[32];
       cardNumToName(card, name);
       printf("%-2d %-13s\n", deckIndex, name);
   }
   printf("\n");


   printf("** END TEST No. 5 *************************************************************\n\n\n\n");



   // begin testing
   printf("\n\n** BEGIN TEST No. 6 *************************************************************\n");
   printf("** 2 of the same treasure cards revealed, so +2 coins total\n");
   printf("** current players hand count should remain the same, actions remain the same\n");
   printf("** next players deck should decrease by 2, next players discards should increase by 2 \n\n\n");


   G.hand[currPlayer][0] = baron;
   G.hand[currPlayer][1] = duchy;
   G.hand[currPlayer][2] = mine;
   G.hand[currPlayer][3] = minion;
   G.hand[currPlayer][4] = ambassador;
   G.handCount[currPlayer] = 5;


   G.deck[nextPlayer][0] = silver;
   G.deck[nextPlayer][1] = silver;
   G.deck[nextPlayer][2] = gold;
   G.deck[nextPlayer][3] = gold;
   G.deck[nextPlayer][4] = gold;
   G.deckCount[nextPlayer] = 5;

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



   // Next Players Deck
   printf("Next Players Deck Before Play:\n");
   deckCount = testGame.deckCount[nextPlayer];
   printf("Player %d's deck:\n", nextPlayer);
   if(deckCount > 0) printf("#  Card\n");
   for(deckIndex = 0; deckIndex < deckCount; deckIndex++) {
       int card = testGame.deck[nextPlayer][deckIndex];
       char name[32];
       cardNumToName(card, name);
       printf("%-2d %-13s\n", deckIndex, name);
   }
   printf("\n");

   tributeCard (&testGame, currPlayer);


   if (G.deckCount[nextPlayer] - 2 == testGame.deckCount[nextPlayer]) {
      printf("OK:  the deck count of next player has decreased by 2.\n");
      printf("Number of cards in deck before play = %d\n", G.deckCount[nextPlayer]);
      printf("Number of cards in deck after play = %d,  ", testGame.deckCount[nextPlayer]);
      printf("Number of cards in deck expected = %d\n\n", G.deckCount[nextPlayer] - 2);
   }
   else {
      printf("ERROR:  the deck count of next player did not decrease by 2.\n");
      printf("Number of cards in deck before play = %d\n", G.deckCount[nextPlayer]);
      printf("Number of cards in deck after play = %d,  ", testGame.deckCount[nextPlayer]);
      printf("Number of cards in deck expected = %d\n\n", G.deckCount[nextPlayer] - 2);

   }


   if (G.discardCount[nextPlayer] + 2 == testGame.discardCount[nextPlayer]) {
      printf("OK:  the discard count of next player has increased by 2.\n");
      printf("Number of discards before play = %d\n", G.discardCount[nextPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[nextPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[nextPlayer] + 2);
   }
   else {
      printf("ERROR:  the discard count of next player did not decrease by 2.\n");
      printf("Number of discards before play = %d\n", G.discardCount[nextPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[nextPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[nextPlayer] + 2);
   }


   if (G.coins + 2 == testGame.coins) {
      printf("OK:  the number of coins increased by 2.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins + 2);
   }
   else {
      printf("ERROR:  the number of coins did not increase by 2.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins + 2);
   }



   if (G.numActions == testGame.numActions) {
      printf("OK:  the number of actions remains the same.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }
   else {
      printf("ERROR:  the number of actions did not remain the same.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }



   if (G.handCount[currPlayer] == testGame.handCount[currPlayer]) {
      printf("OK:  the hand count remains the same.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.handCount[currPlayer]);
   }
   else {
      printf("ERROR:  the hand count remains the same.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.deckCount[currPlayer]);
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



   // Next Players Deck
   printf("Next Players Deck After Play:\n");
   deckCount = testGame.deckCount[nextPlayer];
   printf("Player %d's deck:\n", nextPlayer);
   if(deckCount > 0) printf("#  Card\n");
   for(deckIndex = 0; deckIndex < deckCount; deckIndex++) {
      int card = testGame.deck[nextPlayer][deckIndex];
      char name[32];
      cardNumToName(card, name);
      printf("%-2d %-13s\n", deckIndex, name);
   }
   printf("\n");


   printf("** END TEST No. 6 *************************************************************\n\n\n\n");







   // begin testing
   printf("\n\n** BEGIN TEST No. 7 *************************************************************\n");
   printf("** next player has 0 cards in deck and discards\n");
   printf("** current players hand count should not increase, actions remain the same, coins remain the same\n\n");


   G.hand[currPlayer][0] = baron;
   G.hand[currPlayer][1] = duchy;
   G.hand[currPlayer][2] = mine;
   G.hand[currPlayer][3] = minion;
   G.hand[currPlayer][4] = ambassador;
   G.handCount[currPlayer] = 5;


   G.deckCount[nextPlayer] = 0;
   G.discardCount[nextPlayer] = 0;

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



   // Next Players Deck
   printf("Next Players Deck Before Play:\n");
   deckCount = testGame.deckCount[nextPlayer];
   printf("Player %d's deck:\n", nextPlayer);
   if(deckCount > 0) printf("#  Card\n");
   for(deckIndex = 0; deckIndex < deckCount; deckIndex++) {
       int card = testGame.deck[nextPlayer][deckIndex];
       char name[32];
       cardNumToName(card, name);
       printf("%-2d %-13s\n", deckIndex, name);
   }
   printf("\n");


   // Next Players Discards
   printf("Next Players Discards Before Play:\n");
   discardCount = testGame.discardCount[nextPlayer];
   printf("Player %d's discards:\n", nextPlayer);
   if(discardCount > 0) printf("#  Card\n");
   for(deckIndex = 0; deckIndex < discardCount; deckIndex++) {
       int card = testGame.discard[nextPlayer][deckIndex];
       char name[32];
       cardNumToName(card, name);
       printf("%-2d %-13s\n", deckIndex, name);
   }
   printf("\n");



   tributeCard (&testGame, currPlayer);



   if (G.discardCount[nextPlayer]  == testGame.discardCount[nextPlayer]) {
      printf("OK:  the discard count of next players remains the same.\n");
      printf("Number of discards before play = %d\n", G.discardCount[nextPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[nextPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[nextPlayer]);
   }
   else {
      printf("ERROR:  the discard count of next players did not remain the same.\n");
      printf("Number of discards before play = %d\n", G.discardCount[nextPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[nextPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[nextPlayer]);
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



   if (G.numActions == testGame.numActions) {
      printf("OK:  the number of actions remains the same.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }
   else {
      printf("ERROR:  the number of actions did not remain the same.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }



   if (G.handCount[currPlayer] == testGame.handCount[currPlayer]) {
      printf("OK:  the hand count remains the same.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.handCount[currPlayer]);
   }
   else if(G.handCount[currPlayer] < testGame.handCount[currPlayer]) {
      printf("ERROR:  the hand count increased.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.deckCount[currPlayer]);
   }
   else {
      printf("ERROR:  the hand count decreased.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.deckCount[currPlayer]);
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



   // Next Players Deck
   printf("Next Players Deck After Play:\n");
   deckCount = testGame.deckCount[nextPlayer];
   printf("Player %d's deck:\n", nextPlayer);
   if(deckCount > 0) printf("#  Card\n");
   for(deckIndex = 0; deckIndex < deckCount; deckIndex++) {
      int card = testGame.deck[nextPlayer][deckIndex];
      char name[32];
      cardNumToName(card, name);
      printf("%-2d %-13s\n", deckIndex, name);
   }
   printf("\n");



   // Next Players Discards
   printf("Next Players Discards Before Play:\n");
   discardCount = testGame.discardCount[nextPlayer];
   printf("Player %d's discards:\n", nextPlayer);
   if(discardCount > 0) printf("#  Card\n");
   for(deckIndex = 0; deckIndex < discardCount; deckIndex++) {
       int card = testGame.discard[nextPlayer][deckIndex];
       char name[32];
       cardNumToName(card, name);
       printf("%-2d %-13s\n", deckIndex, name);
   }
   printf("\n");


   printf("** END TEST No. 7 *************************************************************\n\n\n\n");



   // begin testing
   printf("\n\n** BEGIN TEST No. 8 *************************************************************\n");
   printf("** 2 different treasure card revealed (in next player's discards), +4 coins, +2 coins per card\n");
   printf("** current players hand count should not increase, actions remain the same\n");
   printf("** next players discards should remain the same \n\n\n");


   G.hand[currPlayer][0] = baron;
   G.hand[currPlayer][1] = duchy;
   G.hand[currPlayer][2] = mine;
   G.hand[currPlayer][3] = minion;
   G.hand[currPlayer][4] = ambassador;
   G.handCount[currPlayer] = 5;


   //G.deck[nextPlayer][0] = gold;
   G.deckCount[nextPlayer] = 0;
   G.discard[nextPlayer][0] = gold;
   G.discard[nextPlayer][1] = silver;
   G.discardCount[nextPlayer] = 2;

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



   // Next Players Deck
   printf("Next Players Deck Before Play:\n");
   deckCount = testGame.deckCount[nextPlayer];
   printf("Player %d's deck:\n", nextPlayer);
   if(deckCount > 0) printf("#  Card\n");
   for(deckIndex = 0; deckIndex < deckCount; deckIndex++) {
       int card = testGame.deck[nextPlayer][deckIndex];
       char name[32];
       cardNumToName(card, name);
       printf("%-2d %-13s\n", deckIndex, name);
   }
   printf("\n");


   // Next Players Discards
   printf("Next Players Discards Before Play:\n");
   discardCount = testGame.discardCount[nextPlayer];
   printf("Player %d's discards:\n", nextPlayer);
   if(discardCount > 0) printf("#  Card\n");
   for(deckIndex = 0; deckIndex < discardCount; deckIndex++) {
       int card = testGame.discard[nextPlayer][deckIndex];
       char name[32];
       cardNumToName(card, name);
       printf("%-2d %-13s\n", deckIndex, name);
   }
   printf("\n");



   tributeCard (&testGame, currPlayer);


   // should be the same because the cards get moved to the deck and then back to discards
   if (G.discardCount[nextPlayer]  == testGame.discardCount[nextPlayer]) {
      printf("OK:  the discard count of next player should remain the same.\n");
      printf("Number of discards before play = %d\n", G.discardCount[nextPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[nextPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[nextPlayer]);
   }
   else {
      printf("ERROR:  the discard count of next player did not remain the same\n");
      printf("Number of discards before play = %d\n", G.discardCount[nextPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[nextPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[nextPlayer]);
   }


   if (G.coins + 4 == testGame.coins) {
      printf("OK:  the number of coins increased by 4.\n");
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



   if (G.numActions == testGame.numActions) {
      printf("OK:  the number of actions remains the same.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }
   else {
      printf("ERROR:  the number of actions did not remain the same.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }



   if (G.handCount[currPlayer] == testGame.handCount[currPlayer]) {
      printf("OK:  the hand count remains the same.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.handCount[currPlayer]);
   }
   else if(G.handCount[currPlayer] < testGame.handCount[currPlayer]) {
      printf("ERROR:  the hand count increased.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.deckCount[currPlayer]);
   }
   else {
      printf("ERROR:  the hand count decreased.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.deckCount[currPlayer]);
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



   // Next Players Deck
   printf("Next Players Deck After Play:\n");
   deckCount = testGame.deckCount[nextPlayer];
   printf("Player %d's deck:\n", nextPlayer);
   if(deckCount > 0) printf("#  Card\n");
   for(deckIndex = 0; deckIndex < deckCount; deckIndex++) {
      int card = testGame.deck[nextPlayer][deckIndex];
      char name[32];
      cardNumToName(card, name);
      printf("%-2d %-13s\n", deckIndex, name);
   }
   printf("\n");



   // Next Players Discards
   printf("Next Players Discards Before Play:\n");
   discardCount = testGame.discardCount[nextPlayer];
   printf("Player %d's discards:\n", nextPlayer);
   if(discardCount > 0) printf("#  Card\n");
   for(deckIndex = 0; deckIndex < discardCount; deckIndex++) {
       int card = testGame.discard[nextPlayer][deckIndex];
       char name[32];
       cardNumToName(card, name);
       printf("%-2d %-13s\n", deckIndex, name);
   }
   printf("\n");


   printf("** END TEST No. 8 *************************************************************\n\n\n\n");



   return 0;	
}
