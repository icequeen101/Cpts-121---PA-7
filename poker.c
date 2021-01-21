/*
	Programmer: Liana Wu
	Date: 11/18/2019
	Description: Play the stupid game of Poker. I am tramatized by this game.
*/

#include "poker.h"

int menu() {
	int user_game_option = 0;

	system("cls");
	printf("Welcome to Poker: Five-Card Draw!\n");
	printf("1. Rules\n");
	printf("2. Play Game\n");
	printf("3. Exit\n");
	printf("\nPlease enter an option: \n");
	printf(">> ");
	scanf("%d", &user_game_option);

	return user_game_option;
}

void rules() {
	system("cls");

	printf("GAME RULES\n");
	printf("Play begins with the player and computer being dealt five cards, one at a time, all face down, before a round of betting occurs.\n");
	printf("If both the computer and player remains after the first round, the \"draw\" phase begins.\n");
	printf("Player specifies how many of his/her cards he/she wish to replace and discards them.\n");
	printf("The deck is retrieved, and the player is dealt from the deck the same number of cards he/she discarded so that the player again has five cards.\n");
	printf("This process is also done by the computer dueing its turn.\n");
	printf("A second \"after the draw\" betting round occurs.\n");
	printf("This is followed by a showdown - if no winners are decided - which the player with the best hand wins.\n");

	printf("Press Enter To Continue\n");
	printf(">> ");
	system("pause >nul");
}

void play_game(void) {
	printf("Meh\n");
	printf("Press Enter To Continue\n");
	system("pause >nul");

}

void display_goodbye_message() {
	printf("Thanks for playing!\n");
}

/* shuffle cards in deck */
void shuffle(int wDeck[][13]) {
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */

	/* for each of the 52 cards, choose slot of deck randomly */
	for (card = 1; card <= 52; card++)
	{
		/* choose new random location until unoccupied slot found */
		do
		{
			row = rand() % 4;
			column = rand() % 13;
		} while (wDeck[row][column] != 0);

		/* place card number in chosen slot of deck */
		wDeck[row][column] = card;
	}
}

/* deal cards in deck */
void deal(const int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* player_hand, int* card_position)
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */
	int card_index = 0; /* array index for which card is stored */

	/* loop through rows of wDeck */
	for (row = 0; row < SUITS; row++)
	{
		/* loop through columns of wDeck for current row */
		for (column = 0; column < RANKS; column++)
		{
			/* deal each of the 5 cards */
			for (card = *card_position; card <= *card_position + HAND; card++)
			{
				/* if slot contains current card, display card */
				if (wDeck[row][column] == card)
				{
					player_hand->cards_array[card_index].index_of_rank = column + 1;
					player_hand->cards_array[card_index].index_of_suit = row;

					card_index++;
				}
			}
		}
	}
	*card_position += HAND;
}

void display_player_hand(const char* wFace[], const char* wSuit[], Hand* player_hand) {
	system("cls");
	printf("                               YOUR HAND\n");
	printf("----------------------------------------------------------------------\n");

	for (int i = 0; i < HAND; i++) {
		int rank = player_hand->cards_array[i].index_of_rank - 1;
		int suit = player_hand->cards_array[i].index_of_suit;

		printf("- %5s of %-8s\n", wFace[rank], wSuit[suit]);
	}
	printf("\n\n");
	system("pause");
}
/* deal cards in deck */
void deal_replacement_cards(const int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* player_hand, int* card_position, int remove_card_array[MAX_CARD_REPLACEMENT]) {
	int total_replace_card = 3;

	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */
	int array_loop_counter = 0; /* array index to loop through replacement cards*/
	int replace_card_index = 0; /* array index for which card needs to be replaced */

	/* loop through rows of wDeck */
	for (row = 0; row < SUITS; row++)
	{
		/* loop through columns of wDeck for current row */
		for (column = 0; column < RANKS; column++)
		{
			//printf("row=%d column=%d deck=%d card=%d\n", row, column, wDeck[row][column], card);
			/* deal each of the 5 cards */
			for (card = *card_position; card <= *card_position + total_replace_card; card++)
			{
				if (array_loop_counter == total_replace_card) {
					break;
				}
				/* if slot contains current card, display card */
				if (wDeck[row][column] == card)
				{
					replace_card_index = remove_card_array[array_loop_counter];

					player_hand->cards_array[replace_card_index].index_of_rank = column + 1;
					player_hand->cards_array[replace_card_index].index_of_suit = row;

					array_loop_counter++;
				}
			}
		}
		*card_position += total_replace_card;
	}
	for (int i = 0; i < HAND; i++) {
		int rank = player_hand->cards_array[i].index_of_rank - 1;
		int suit = player_hand->cards_array[i].index_of_suit;

		printf("NEW HAND: %5s of %-8s\n", wFace[rank], wSuit[suit]);
	}
}

void count_card_ranks(Hand* player_hand, int card_rank_count[RANKS]) {
	int card_num = 0;

	for (int card = 0; card < HAND; card++) {
		card_num = player_hand->cards_array[card].index_of_rank;
		//printf("Hand %d - Stored In Face: %d \n",card,  player_hand->cards_array[card].index_of_rank);

		card_rank_count[card_num] ++;
	}

	/*for (int card = 0; card < RANKS; card++) {
		printf("Card Pos: %d\n", card);
		printf("Array %d - Stored In Face: %d \n", card, card_rank_count[card]);
	}
	system("pause");*/
}

void count_card_suits(Hand* player_hand, int card_rank_count[SUITS]) {
	int card_num = 0;

	for (int card = 0; card < HAND; card++) {
		card_num = player_hand->cards_array[card].index_of_suit;
		//printf("Hand %d - Stored In Suit: %d \n", card, player_hand->cards_array[card].index_of_suit);

		card_rank_count[card_num] ++;
	}

	//for (int card = 0; card < SUITS; card++) {
		//printf("Card Pos: %d\n", card);
		//printf("Array %d - Stored In Suit: %d \n", card, card_rank_count[card]);
	//}
}

int pair(Hand* player_hand, int card_rank_count[RANKS], const char* wFace[], const char* wSuit[], int* pts) {
	int card_rank = 0, card_suit = 0;
	bool one_pair = false;


	for (int card = 0; card < RANKS; card++) {

		if (card_rank_count[card] >= PAIR && !one_pair) {
			card_rank = player_hand->cards_array[card].index_of_rank;

			system("pause >nul");
			//printf("%d", player_hand->cards_array[card].index_of_rank);
			printf("Pair Found\n");
			//printf(" % -8s\n", wFace[card_rank]);

			one_pair = true;
			*pts = (card_rank + 1);
			//printf("after *pts:%d\n", *pts);
			/*for (int i = 0; i < RANKS; i++) {
				printf("IDx:%d, Inside:%d\n", i, card_rank_count[i]);
			}*/
		}

		
	}
	return one_pair;
}

	int two_pair(Hand * player_hand, int card_rank_count[RANKS], const char* wFace[], const char* wSuit[], int* pts) {
		int card_rank = 0, card_suit = 0, two_pair_count = 0,
			two_pair_array_count = 0, /* Initialize starting index for two_pair_card_idx array */
			two_pair_card_idx[2]; /* Stores the indexed of pairs in hand*/
		bool two_pair = false;

		for (int card = 0; card < RANKS; card++) {
			if (card_rank_count[card] >= PAIR) {

				two_pair_card_idx[two_pair_array_count] = card; /* Stores the pairs in the array */
				//printf("2 Pair Card Index %d : Content %d \n", two_pair_array_count, two_pair_card_idx[two_pair_array_count]);

				two_pair_array_count++;
				two_pair_count++;
			}
		}
		if (two_pair_count == 2) {
			two_pair = true;
			*pts = (card_rank + 1) * 2;

			system("cls");
			printf("Two Pair Found\n");
			/*for (int i = 0; i < 2; i++) {
				card_rank = player_hand->cards_array[two_pair_card_idx[i]].index_of_rank + ARRAY_CONVERTION;

				printf("%-8s\n", wFace[card_rank]);

			}*/
		}
		return two_pair;
	}

	int three_kind(Hand * player_hand, int card_rank_count[RANKS], const char* wFace[], const char* wSuit[], int* pts) {
		int card_rank = 0, card_suit = 0;
		bool three_kind = false;

		for (int card = 0; card < RANKS; card++) {
			if (card_rank_count[card] >= THREE_KIND && !three_kind) {
				card_rank = player_hand->cards_array[card].index_of_rank + ARRAY_CONVERTION;
				card_suit = player_hand->cards_array[card].index_of_suit;

				system("cls");
				printf("Three Of A Kind Found-\n");
			//	printf("%-8s\n", wFace[card_rank]);

				three_kind = true;
				*pts = (card_rank + 1) * 3;
			}
		}
		return three_kind;
	}

	int four_kind(Hand * player_hand, int card_rank_count[RANKS], const char* wFace[], const char* wSuit[], int* pts) {
		int card_rank = 0, card_suit = 0;
		bool four_kind = false;

		for (int card = 0; card < RANKS; card++) {
			if (card_rank_count[card] >= FOUR_KIND && !four_kind) {
				card_rank = player_hand->cards_array[card].index_of_rank + ARRAY_CONVERTION;
				card_suit = player_hand->cards_array[card].index_of_suit;

				system("cls");
				printf("Four Of A Kind:\n");
				printf("%-8s\n", wFace[card_rank]);

				four_kind = true;
				*pts = (card_rank + 1) * 4;
			}
		}
		return four_kind;
	}

	int straight(Hand * player_hand, int card_rank_count[RANKS], int* pts) {
		int sequence_sum_checker = 0;
		bool straight = false;

		for (int card = 0; card < RANKS; card++) {
			sequence_sum_checker = 0;
			for (int i = 0; i < HAND; i++) {
				if (card_rank_count[card + i] >= 1) {
					sequence_sum_checker++;
				}
			}
			if (sequence_sum_checker >= 5) {
				straight = true;
				*pts += 25;

				system("cls");
				printf("Straight!\n");
				break;
			}
		}
		return straight;
	}

	int flush(Hand * player_hand, int card_suit_count[SUITS], const char* wFace[], const char* wSuit[], int* pts) {
		int card_suit = 0, flush_card_idx = 0;
		bool flush = false;

		for (int card = 0; card < SUITS; card++) {
			if (card_suit_count[card] == 5) {
				flush = true;
				*pts += 26;

				flush_card_idx = card;
				//printf("Flush Index %d : Content %d \n", card, card_suit_count[card]);
			}
		}
		if (flush) {
			//system("cls");
			printf("Flush:\n");
			card_suit = player_hand->cards_array[flush_card_idx].index_of_suit;

			printf("%5s Suit\n", wSuit[card_suit]);
		}
		return flush;
	}

	int player_turn() {
		int player_option = 0;

		system("cls");
		while (player_option != DEAL && player_option != REPLACE) {
			printf("Would you like to: \n");
			printf("1. Deal A Hand\n");
			printf("2. Replace A Few Cards\n");
			printf(">> ");
			scanf("%d", &player_option);
		}
		return player_option;
	}

	int player_deal_cards(Hand * player_hand, int card_suit_count[SUITS], const char* wFace[], const char* wSuit[]) {
		int card_rank = 0, card_suit = 0, player_card_deal = -1;

		system("cls");

		printf("Possible Card Deals: \n");
		printf("1. Pair\n");
		printf("2. Two Pair\n");
		printf("3. Three of A Kind\n");
		printf("4. Four of A Kind\n");
		printf("5. Straight\n");
		printf("6. Flush\n\n");

		printf("Your Current Hand Includes: \n");
		printf("----------------------------\n");
		for (int card = 0; card < HAND; card++) {
			card_rank = player_hand->cards_array[card].index_of_rank + ARRAY_CONVERTION;
			card_suit = player_hand->cards_array[card].index_of_suit;
			printf("     %5s of %-8s\n", wSuit[card_suit], wFace[card_rank]);
		}
		printf("----------------------------\n");

		while (player_card_deal != NONE && player_card_deal != ONE_PAIR && player_card_deal != PAIR &&
			player_card_deal != THREE_KIND && player_card_deal != FOUR_KIND &&
			player_card_deal != STRAIGHT && player_card_deal != FLUSH) {

			printf("\nPlease Enter A Card Deal: \n");
			printf(">> ");
			scanf("%d", &player_card_deal);
		}
		return player_card_deal;
	}

	void check_card_deals(Hand * player_hand, int card_rank_count[RANKS], int card_suit_count[SUITS], const char* wFace[], const char* wSuit[], int* pts) {

		int player_card_deal = -1;
		bool check_card_deal = false;

		while (!check_card_deal) {
			player_card_deal = player_deal_cards(player_hand, card_rank_count, wFace, wSuit);
			printf("Checking Card Deal...\n\n");

			if (player_card_deal == ONE_PAIR) {
				check_card_deal = pair(player_hand, card_rank_count, wFace, wSuit, pts);
				system("pause");
				if (check_card_deal) {
					printf("\nYou Have Dealed A Pair!\n");

				}
				else {
					printf("No Pair Detected.");
					system("pause >nul");
				}
			}

			else if (player_card_deal == PAIR) {
				check_card_deal = two_pair(player_hand, card_rank_count, wFace, wSuit, pts);
				if (check_card_deal) {
					printf("\nYou Have Dealed A Two-Pair!\n");
				}
				else {
					printf("No Two-Pair Detected.");
					system("pause >nul");
				}
			}

			else if (player_card_deal == THREE_KIND) {
				check_card_deal = three_kind(player_hand, card_rank_count, wFace, wSuit, pts);
				if (check_card_deal) {
					printf("\nYou Have Dealed A Three Of A Kind!\n");
				}
				else {
					printf("No Three Of A Kind Detected.");
					system("pause >nul");
				}
			}

			else if (player_card_deal == FOUR_KIND) {
				check_card_deal = four_kind(player_hand, card_rank_count, wFace, wSuit, pts);
				if (check_card_deal) {
					printf("\nYou Have Dealed A Four Of A Kind!\n");
				}
				else {
					printf("No Four Of A Kind Detected.");
					system("pause >nul");
				}
			}

			else if (player_card_deal == STRAIGHT) {
				check_card_deal = straight(player_hand, card_rank_count, pts);
				if (check_card_deal) {
					printf("\nYou Have Dealed A Straight!\n");
				}
				else {
					printf("No Straight Detected.");
					system("pause >nul");
				}
			}

			else if (player_card_deal == FLUSH) {
				check_card_deal = flush(player_hand, card_suit_count, wFace, wSuit, pts);
				if (check_card_deal) {
					printf("\nYou Have Dealed A Flush!\n");
				}
				else {
					printf("No Flush Detected.");
					system("pause >nul");
				}
			}
			else if (player_card_deal == NONE) {
				check_card_deal = true;
				if (check_card_deal) {
					printf("\nYou Have Dealed A None - Literally nothing!\n");
				}
			}
		}
	}


	int player_decide_card_replacement(Hand * player_hand, int card_rank_count[RANKS], int card_suit_count[SUITS], const char* wFace[], const char* wSuit[], int remove_card_array[MAX_CARD_REPLACEMENT]) {

		int card_rank = 0, card_suit = 0, replace_card_num = 0, remove_card_num = 0;

		system("cls");
		printf("                                      REPLACEMENT\n");
		printf("------------------------------------------------------------------------------------\n");
		printf("You may replace 1-3 cards. Please enter how many cards you would like to replace. \n");
		printf(">> ");
		scanf("%d", &replace_card_num);

		printf("Your Current Hand Includes: \n");
		printf("----------------------------\n");
		for (int card = 0; card < HAND; card++) {
			card_rank = player_hand->cards_array[card].index_of_rank + ARRAY_CONVERTION;
			card_suit = player_hand->cards_array[card].index_of_suit;
			printf("[%d]     %5s of %-8s\n", card, wSuit[card_suit], wFace[card_rank]);
		}
		printf("----------------------------\n");

		while (replace_card_num > 0) {
			printf("Please enter which cards to replace by entering the corresponding number.\n");
			scanf("%d", &remove_card_num);

			remove_card_array[replace_card_num + ARRAY_CONVERTION] = remove_card_num;
			//printf("Index: %d -- Num: %d\n", replace_card_num + ARRAY_CONVERTION, remove_card_num);

			replace_card_num--;

		}
		return replace_card_num;
	}

	void replace_cards(Hand * player_hand, int card_rank_count[RANKS], int card_suit_count[SUITS], const char* wFace[], const char* wSuit[], int remove_card_array[MAX_CARD_REPLACEMENT]) {
		int replace_card_num = 0, replace_card_idx = 0;

		replace_card_num = player_decide_card_replacement(player_hand, card_rank_count, card_suit_count, wFace, wSuit, remove_card_array);

		for (int card = 0; card < replace_card_num; card++) {
			//printf("Card Index: %d || Card: %d \n", card, remove_card_array[card]);
			replace_card_idx = remove_card_array[card];
			player_hand->cards_array[replace_card_idx].index_of_rank = EMPTY;
			player_hand->cards_array[replace_card_idx].index_of_suit = EMPTY;
		}

		/*for (int card = 0; card < 5; card++) {
			printf("INDEX: %d\n", card);
			printf("Player Hand Rank Card: %d \n", player_hand->cards_array[card].index_of_rank);
			printf("Player Hand Suit Card: %d \n", player_hand->cards_array[card].index_of_suit);
		}*/
	}

	void dealer_deal(Hand * computer_hand, int card_rank_count[RANKS], int card_suit_count[SUITS], const char* wFace[], const char* wSuit[], int* pts) {
		int computer_deal_card = 0;
		bool check_card_deal = false;

		while (!check_card_deal && computer_deal_card > -1) {

			if (computer_deal_card == ONE_PAIR) {
				check_card_deal = pair(computer_hand, card_rank_count, wFace, wSuit, pts);
			}

			else if (computer_deal_card == PAIR) {
				check_card_deal = two_pair(computer_hand, card_rank_count, wFace, wSuit, pts);
			}

			else if (computer_deal_card == THREE_KIND) {
				check_card_deal = three_kind(computer_hand, card_rank_count, wFace, wSuit, pts);
			}

			else if (computer_deal_card == FOUR_KIND) {
				check_card_deal = four_kind(computer_hand, card_rank_count, wFace, wSuit, pts);
			}

			else if (computer_deal_card == STRAIGHT) {
				check_card_deal = straight(computer_hand, card_rank_count, pts);
			}

			else if (computer_deal_card == FLUSH) {
				check_card_deal = flush(computer_hand, card_suit_count, wFace, wSuit, pts);
			}

			else if (computer_deal_card == NONE) {
				check_card_deal = true;
			}
			computer_deal_card--;
		}
	}


	void dealer_replace(int remove_card_array[MAX_CARD_REPLACEMENT]) {
		int total_replace_cards, replace_card_idx;

		total_replace_cards = rand() % 3;

		for (int card = 0; card < total_replace_cards; card++) {
			replace_card_idx = rand() % 3;
			remove_card_array[card] = replace_card_idx;
			//printf("TOTAL: %d, Card: %d, replace_Card_idx: %d", total_replace_cards, card, remove_card_array[card]);
		}
	}

	void winner(int* player_pts, int* computer_pts) {
		//printf("P: %d, C:%d", *player_pts, *computer_pts);
		if (*player_pts > * computer_pts) {
			printf("PLAYER WINS!\n");
		}
		else if (*player_pts < *computer_pts) {
			printf("COMPUTER WINS!\n");
		}
		else {
			printf("TIE!\n");
		}
	}
