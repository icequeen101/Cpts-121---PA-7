/*
	Programmer: Liana Wu
	Date: 11/18/2019
	Description: Play the stupid game of Poker. I am tramatized by this game.
*/

#include "poker.h"

int main(void)
{
	srand((unsigned)time(NULL)); /* seed random-number generator */

	int user_game_option = 0, card_pos = 0, deal_or_replace = 0, player_points = 20, computer_points = 21,
		player_card_rank_count[RANKS] = { 0 }, player_card_suit_count[SUITS] = { 0 }, player_remove_card_array[MAX_CARD_REPLACEMENT] = { 0 },
		computer_card_rank_count[RANKS] = { 0 }, computer_card_suit_count[SUITS] = { 0 }, computer_remove_card_array[MAX_CARD_REPLACEMENT] = { 0 };

	int* card_pos_ptr = &card_pos, * player_pts = &player_points, * computer_pts = &computer_points;

	/*BEGIN TEST CASE*/
	Card test_card1;
	test_card1.index_of_suit = 0;
	test_card1.index_of_rank = 1;


	Card test_card2;
	test_card2.index_of_suit = 0;
	test_card2.index_of_rank = 10;

	Card test_card3;
	test_card3.index_of_suit = 0;
	test_card3.index_of_rank = 12;

	Card test_card4;
	test_card4.index_of_suit = 0;
	test_card4.index_of_rank = 1;

	Card test_card5;
	test_card5.index_of_suit = 0;
	test_card5.index_of_rank = 5;

	Card test_card_array[] = { test_card1, test_card2, test_card3, test_card4, test_card5 };
	Hand computer_hand, player_hand;
	Hand test_hand;

	for (int i = 0; i < HAND; i++) {
		test_hand.cards_array[i] = test_card_array[i];
	}

	/*END OF TEST CASE*/

	/* initialize suit array */
	const char* suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	/* initialize face array */
	const char* face[13] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
		"Nine", "Ten", "Jack", "Queen", "King" };

	/* initalize deck array */
	int deck[4][13] = { 0 };

	/*for (int i = 0; i < HAND; i++) {
		int rank = test_hand.cards_array[i].index_of_rank;
		int suit_test = test_hand.cards_array[i].index_of_suit;

		printf("IDX: %d, Rank: %d", i, rank);
			printf("TEST_HAND: %5s of %-8s\n", face[rank], suit[suit_test]);

	}

	system("pause");*/
	/*count_card_ranks(&test_hand, player_card_rank_count);

	pair(&test_hand, player_card_rank_count, face, suit, player_pts);
	system("pause");*/
	while (user_game_option != 3) {
		do {
			user_game_option = menu();
		} while (user_game_option < 1 || user_game_option > 3);

		switch (user_game_option) {
		case 1:
			rules();
			break;
		case 2:
			


			shuffle(deck);
			deal(deck, face, suit, &player_hand, card_pos_ptr);
			deal(deck, face, suit, &computer_hand, card_pos_ptr);

			display_player_hand(face, suit, &player_hand);

			count_card_ranks(&player_hand, player_card_rank_count);
			/*printf("MAIN\n");
				for (int card = 0; card < RANKS; card++) {
				printf("Card Pos: %d\n", card);
				printf("Array %d - Stored In Face: %d \n", card, player_card_rank_count[card]);
			}
			system("pause");*/
			count_card_suits(&player_hand, player_card_suit_count);
			count_card_ranks(&computer_hand, computer_card_rank_count);
			count_card_suits(&computer_hand, computer_card_suit_count);

			deal_or_replace = player_turn();

			if (deal_or_replace == DEAL) {
				check_card_deals(&player_hand, player_card_rank_count, player_card_suit_count, face, suit, player_pts);
				dealer_deal(&computer_hand, computer_card_rank_count, computer_card_suit_count, face, suit, computer_pts);
				winner(player_pts, computer_pts);
			}
			else if (deal_or_replace == REPLACE) {
				replace_cards(&player_hand, player_card_rank_count, player_card_suit_count, face, suit, player_remove_card_array);
				deal_replacement_cards(deck, face, suit, &player_hand, card_pos_ptr, player_remove_card_array);
				system("pause");
				dealer_replace(computer_remove_card_array);

				count_card_ranks(&player_hand, player_card_rank_count);
				count_card_suits(&player_hand, player_card_suit_count);
				count_card_ranks(&computer_hand, computer_card_rank_count);
				count_card_suits(&computer_hand, computer_card_suit_count);

				check_card_deals(&player_hand, player_card_rank_count, player_card_suit_count, face, suit, player_pts);
				dealer_deal(&computer_hand, computer_card_rank_count, computer_card_suit_count, face, suit, computer_pts);
				winner(player_pts, computer_pts);

			}

			printf("\nPress Enter To Continue\n");
			printf(">> ");
			system("pause >nul");
			break;
		case 3:
			display_goodbye_message();
			break;
		}
	}

	return 0;
}

