/*
	Programmer: Liana Wu
	Date: 11/18/2019
	Description: Play the stupid game of Poker. I am tramatized by this game. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/* Poker Card Max Values */
#define ARRAY_CONVERTION -1 /* Face is One Less Than Rank & Subsitutes the beginning number of arrays (Between array index of 0 & game's display of the number 1)*/
#define EMPTY -1
#define MAX_CARD_REPLACEMENT 3
#define SUITS 4
#define HAND 5
#define RANKS 13

/* Poker Hand - Counters/Deals */
#define NONE 0 
#define ONE_PAIR 1
#define PAIR 2		// Or Two_Pair
#define THREE_KIND 3
#define FOUR_KIND 4
#define STRAIGHT 5 
#define FLUSH 6

/* Player's Actions */
#define DEAL 1
#define REPLACE 2 

typedef struct card {
	int index_of_suit;
	int index_of_rank;
} Card;

typedef struct hand {
	Card cards_array[5];
} Hand;

/*
	Function: menu()
	Date Created: 11/18/2019
	Description: Displays menu and gets player menu option 
	Input Parameters: N/A
	Returns: Player option of the menu
	Preconditions: Start of program
	Postconditions: Returns player menu option 
*/

int menu();

/*
	Function: rules()
	Date Created: 11/18/2019
	Description: Displays game rules
	Input Parameters: N/A
	Returns: N/A
	Preconditions: Start of program
	Postconditions: Display rules
*/
void rules();

/*
	Function: play_game()
	Date Created: 11/18/2019
	Description: Starts the game
	Input Parameters: N/A
	Returns: N/A
	Preconditions: Start of program
	Postconditions: Starts game
*/

void play_game();

/*
	Function: display_goodbye_message()
	Date Created: 11/18/2019
	Description: Displays goodbye message
	Input Parameters: N/A
	Returns: N/A
	Preconditions: Start of program
	Postconditions: Displays goodbye message
*/

void display_goodbye_message();

/*
	Function:
	Date Created: 11/18/2019
	Description:
	Input Parameters:
	Returns:
	Preconditions: Start of program
	Postconditions:
*/

void shuffle(int wDeck[][13]);

/*
	Function: shuffle()
	Date Created: 11/18/2019
	Description: Shuffles the deck
	Input Parameters: Deck
	Returns: N/A
	Preconditions: Start of program
	Postconditions: Shuffles deck
*/

void deal(const int wDeck[][13], const char* wFace[], const char* wSuit[], Hand *player_hand, int* card_position);

/*
	Function: display_player_hand()
	Date Created: 11/18/2019
	Description: Display's the player's hand 
	Input Parameters: Player's hand + Face & suit arrays  
	Returns: N/A
	Preconditions: Start of program
	Postconditions: Display player hand 
*/

void display_player_hand(const char* wFace[], const char* wSuit[], Hand* player_hand);

/*
	Function: count_card_ranks()
	Date Created: 11/18/2019
	Description: Counts how many of each rank there is in the hand
	Input Parameters: Player's hand + Card rank count array
	Returns: N/A
	Preconditions: Start of program
	Postconditions: card rank count array filled 
*/

void count_card_ranks(Hand* player_hand, int card_count[RANKS]);

/*
	Function: count_card_suits()
	Date Created: 11/18/2019
	Description: Counts how many of each suit there is in the hand
	Input Parameters: Hand + Card suit count array
	Returns: N/A
	Preconditions: Start of program
	Postconditions: card suit count array filled 
*/

void count_card_suits(Hand* player_hand, int card_count[SUITS]);

/*
	Function: pair()
	Date Created: 11/18/2019
	Description: Checks for a pair
	Input Parameters: Hand + Card rank count array, face, suit, arrays + Points
	Returns: If pair is found or not 
	Preconditions: Start of program
	Postconditions: If pair is found or not
*/

int pair(Hand* player_hand, int card_rank_count[RANKS], const char* wFace[], const char* wSuit[], int *pts);

/*
	Function: two_pair()
	Date Created: 11/18/2019
	Description: Checks for a two pair
	Input Parameters: Hand + Card rank count array, face, suit, arrays + Points
	Returns: If two pair is found or not
	Preconditions: Start of program
	Postconditions: If two pair is found or not
*/


int two_pair(Hand* player_hand, int card_rank_count[RANKS], const char* wFace[], const char* wSuit[], int* pts);

/*
	Function: three_kind()
	Date Created: 11/18/2019
	Description: Checks for a three of a kind
	Input Parameters: Hand + Card rank count array, face, suit, arrays + Points
	Returns: If three of a kind is found or not
	Preconditions: Start of program
	Postconditions: If three of a kind is found or not
*/

int three_kind(Hand* player_hand, int card_rank_count[RANKS], const char* wFace[], const char* wSuit[], int* pts);

/*
	Function: four_kind()
	Date Created: 11/18/2019
	Description: Checks for a four of a kind
	Input Parameters: Hand + Card rank count array, face, suit, arrays + Points
	Returns: If four of a kind is found or not
	Preconditions: Start of program
	Postconditions: If four of a kind is found or not
*/

int four_kind(Hand* player_hand, int card_rank_count[RANKS], const char* wFace[], const char* wSuit[], int* pts);

/*
	Function: straight()
	Date Created: 11/18/2019
	Description: Checks for a straight
	Input Parameters: Hand + Card rank count array + Points
	Returns: If straight is found or not
	Preconditions: Start of program
	Postconditions: If staight is found or not
*/

int straight(Hand* player_hand, int card_rank_count[RANKS], int* pts);

/*
	Function: flush()
	Date Created: 11/18/2019
	Description: Checks for a flush
	Input Parameters: Hand + Card suit count, face, suit arrays + Points
	Returns: If flush is found or not
	Preconditions: Start of program
	Postconditions: If flush is found or not
*/

int flush(Hand* player_hand, int card_suit_count[SUITS], const char* wFace[], const char* wSuit[], int* pts);

/*
	Function: player_turn()
	Date Created: 11/18/2019
	Description: Asks user whether he/she wants to deal or replace
	Input Parameters: N/A
	Returns: Player's choice
	Preconditions: Start of program
	Postconditions: Player's choice
*/

int player_turn();

/*
	Function: player_deal_cards()
	Date Created: 11/18/2019
	Description: Player deal hand
	Input Parameters: Hand + Card suit count, face, suit arrays
	Returns: Number of which hand type to place down 
	Preconditions: Start of program
	Postconditions: Number of which hand type to place down 
*/

int player_deal_cards(Hand* player_hand, int card_suit_count[SUITS], const char* wFace[], const char* wSuit[]);

/*
	Function: check_card_deals()
	Date Created: 11/18/2019
	Description: Checks if hand method is present in hand
	Input Parameters: Hand + Card suit count, face, suit arrays + Points
	Returns: N/A
	Preconditions: Start of program
	Postconditions: Checks if hand method is present in hand
*/

void check_card_deals(Hand* player_hand, int card_rank_count[RANKS], int card_suit_count[SUITS], const char* wFace[], const char* wSuit[], int *pts);

/*
	Function: player_decide_card_replacement()
	Date Created: 11/18/2019
	Description: Player decide how many and which cards to replace
	Input Parameters: Hand + Card suit count, face, suit, remove card arrays
	Returns: Number of cards to replace
	Preconditions: Start of program
	Postconditions: Number of cards to replace
*/

int player_decide_card_replacement(Hand* player_hand, int card_rank_count[RANKS], int card_suit_count[SUITS], const char* wFace[], const char* wSuit[], int remove_card_array[MAX_CARD_REPLACEMENT]);

/*
	Function: replace_cards()
	Date Created: 11/18/2019
	Description: Player replaces cards
	Input Parameters: Hand + Card suit count, face, suit, replace card arrays
	Returns: N/A
	Preconditions: Start of program
	Postconditions: Replaces cards
*/

void replace_cards(Hand* player_hand, int card_rank_count[RANKS], int card_suit_count[SUITS], const char* wFace[], const char* wSuit[], int remove_card_array[MAX_CARD_REPLACEMENT]);

/*
	Function: deal_replacement_cards()
	Date Created: 11/18/2019
	Description: Deal the replacement cards
	Input Parameters: Hand + Card suit count, face, suit, remove card arrays
	Returns: N/A
	Preconditions: Start of program
	Postconditions: Deal the replacement cards
*/

void deal_replacement_cards(const int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* player_hand, int* card_position, int remove_card_array[MAX_CARD_REPLACEMENT]);

/*
	Function: dealer_deal()
	Date Created: 11/18/2019
	Description: Dealer deals
	Input Parameters: Hand + Card suit count, face, suit arrays + Point
	Returns: N/A
	Preconditions: Start of program
	Postconditions: Dealer deals
*/

void dealer_deal(Hand* computer_hand, int card_rank_count[RANKS], int card_suit_count[SUITS], const char* wFace[], const char* wSuit[], int*pts);

/*
	Function: dealer_replace()
	Date Created: 11/18/2019
	Description: Dealer replaces cards
	Input Parameters: Remove card arrays
	Returns: N/A
	Preconditions: Start of program
	Postconditions: Replaces cards
*/

void dealer_replace(int remove_card_array[MAX_CARD_REPLACEMENT]);

/*
	Function: winner()
	Date Created: 11/18/2019
	Description: Displays winner
	Input Parameters: Player and computer points
	Returns: N/A
	Preconditions: Start of program
	Postconditions: Displays winner
*/

void winner(int* player_pts, int *computer_pts);

