// Nurlan Mammadli
// due date 12-01-2023
// creating a poker game

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//  Declaring card
struct Card{
    int face;
    int suit;
};

//  Each hand is a set of five cards
struct Hand{
    struct Card cards[5];
};

// The deck only holds generated cards and tracks the number of cards dealt.
struct Deck{
    struct Card dealtCards[52];
    int numCardsDealt;
};
 
struct Hand hand1, hand2;
struct Deck deck;

// These array hold all of the strings
static const char *faceStrings[] = {
    "Two","Three","Four","Five","Six","Seven","Eight","Nine",
    "Ten","Jack","Queen","King","Ace"};
static const char *suitStrings[] = {
    "Hearts","Clubs","Diamonds","Spades"};
static const char *rankStrings[] = {
    "High Card","Single Pair","Two Pair","Three of a Kind","Straight",
    "Flush","Full House","Four of a Kind","Straight Flush"};

//  We need functions for generating hands, printing hands and determining which hand won.
void createHands();
struct Card dealCard();
void printHands();
void analyzeHand();

int main(){
    // Initializing deck
    deck.numCardsDealt=0;

    srand(time(NULL));

    // creating cards
    createHands();

    // Print them
    printHands();

    // Find the winner
    analyzeHand();

    return 0;
}

void createHands(){
    int i;

    // This would be like the dealer alternating giving cards to one player or the other.
    for(i=0; i<5; i++){
        hand1.cards[i] = dealCard();
        hand2.cards[i] = dealCard();
    }
}

struct Card dealCard(){
    int i;
    int unique; // This variable keeps track if there are other matching cards
    struct Card cardToDeal; 
    while(1){
        cardToDeal.face = rand()%13;
        cardToDeal.suit = rand()%4;
        unique = 1;
        // We only need to check from 0 to the last card we dealt
        for(i=0; i<deck.numCardsDealt; i++){
            if(deck.dealtCards[i].face == cardToDeal.face && deck.dealtCards[i].suit == cardToDeal.suit)
                unique = 0;
        }
        // If cardToDeal hasn't been dealt
        if(unique){
            deck.numCardsDealt++;
            deck.dealtCards[deck.numCardsDealt] = cardToDeal;
            return cardToDeal;
        }
    }
}

// Getting the string that is at the index of our face or suit.
void printHands(){
    int i;
    printf("Player one has:\n");
    for(i=0; i<5; i++)
        printf("%s of %s\n", faceStrings[hand1.cards[i].face], suitStrings[hand1.cards[i].suit]);
    printf("\nPlayer two has:\n");
    for(i=0; i<5; i++)
        printf("%s of %s\n", faceStrings[hand2.cards[i].face], suitStrings[hand2.cards[i].suit]);
}

void analyzeHand(){
    int i,j;
    // Counts of each face and suit 
    int hand1Face[13];
    int hand1Suit[4];
    int hand2Face[13];
    int hand2Suit[4];

    memset(hand1Face,0,sizeof(hand1Face));
    memset(hand1Suit,0,sizeof(hand1Suit));
    memset(hand2Face,0,sizeof(hand2Face));
    memset(hand2Suit,0,sizeof(hand2Suit));

    // Getting those numbers
    for(i=0; i<5; i++){
        hand1Face[hand1.cards[i].face]++;
        hand1Suit[hand1.cards[i].suit]++;
        hand2Face[hand2.cards[i].face]++;
        hand2Suit[hand2.cards[i].suit]++;
    }

    // Variables to keep track of what each hand has
    int h1Rank=0, h1Consec=0, h1Straight=0, h1Flush=0, h1Four=0, h1Three=0, h1Pairs=0;
    int h2Rank=0, h2Consec=0, h2Straight=0, h2Flush=0, h2Four=0, h2Three=0, h2Pairs=0;

    // check for flush – 5 cards of the same suit
	for(i=0; i<5; i++){
        if(hand1Suit[i]==5)
            h1Flush=1;
        if(hand2Suit[i]==5)
            h2Flush=1;
	}

	// check for straight – One each of 5,6,7,8,9
	i = 0;
	while (hand1Face[i] == 0)
		i++;
	for (; i < 3 && hand1Face[i]; i++)
		h1Consec++;
	if (h1Consec == 5)
		h1Straight = 1;

    // check for straight – eg. One each of 5,6,7,8,9
	i = 0;
	while (hand2Face[i] == 0)
		i++;
	//     count the consecutive non-zero faces
	for (; i < 3 && hand2Face[i]; i++)
		h2Consec++;
	if (h2Consec == 5)
		h2Straight = 1;

	/* check for 4-of-a-kind, 3-of-a-kind, and pairs */
	for (i = 0; i < 14; i++) {
		if (hand1Face[i] == 4)
			h1Four = 1;
		if (hand1Face[i] == 3)
			h1Three = 1;
		if (hand1Face[i] == 2)
			h1Pairs++;
	}
	for (i = 0; i < 14; i++) {
		if (hand2Face[i] == 4)
			h2Four = 1;
		if (hand2Face[i] == 3)
			h2Three = 1;
		if (hand2Face[i] == 2)
			h2Pairs++;
	}

	// Hand 1 ranking
	if (h1Straight && h1Flush)
		h1Rank=8;
	else if (h1Four)
		h1Rank=7;
	else if (h1Three && h1Pairs == 1)
		h1Rank=6;
	else if (h1Flush)
		h1Rank=5;
	else if (h1Straight)
		h1Rank=4;
	else if (h1Three)
		h1Rank=3;
	else if (h1Pairs == 2)
		h1Rank=2;
	else if (h1Pairs == 1)
		h1Rank=1;
	else
		h1Rank=0;

    // Hand 2 ranking
    if (h2Straight && h2Flush)
		h2Rank=8;
	else if (h2Four)
		h2Rank=7;
	else if (h2Three && h2Pairs == 1)
		h2Rank=6;
	else if (h2Flush)
		h2Rank=5;
	else if (h2Straight)
		h2Rank=4;
	else if (h2Three)
		h2Rank=3;
	else if (h2Pairs == 2)
		h2Rank=2;
	else if (h2Pairs == 1)
		h2Rank=1;
	else
		h2Rank=0;

    // Print what each player has
    printf("\nPlayer one has a %s.\n",rankStrings[h1Rank]);
    printf("Player two has a %s.\n",rankStrings[h2Rank]);

    // Determine winner
    if(h1Rank>h2Rank)
        printf("Player one wins!\n");
    else if(h2Rank>h1Rank)
        printf("Player two wins!\n");
    else
        printf("Two players tie!!!\n");
}