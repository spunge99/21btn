
#include "DeckOfCards.h"

DeckOfCards::DeckOfCards() {
	init_deck_of_cards(1);
}

DeckOfCards::DeckOfCards(int number_of_decks) {
	init_deck_of_cards(number_of_decks);
}

void DeckOfCards::remove_from_deck(int card) {
	cards_remaining[card] = cards_remaining[card] - 1;
	deck_size--;
}

void DeckOfCards::init_deck_of_cards(int number_of_decks) {
	deck_size = 52 * number_of_decks;
	cards_remaining[11] = 4 * number_of_decks;
	cards_remaining[10] = 16 * number_of_decks;
	for(int i = 9; i > 1; i--) {
		cards_remaining[i] = 4 * number_of_decks;
	}
}

void DeckOfCards::print_current_deck() {
	for(int j = 11; j > 1; j--) {
		if(j == 11)
			cout << "Ace:" << cards_remaining[j] << " ";
		else
			cout << j << ":" << cards_remaining[j] << " ";
	}
	cout << "\n";
}