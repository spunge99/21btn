
#ifndef __DECKOFCARDS_H

#define __DECKOFCARDS_H

#include <iostream>
#include <map>

using namespace std;

class DeckOfCards{
	private:
		double deck_size;
		map<int, int> cards_remaining;
	public:
		DeckOfCards();
		DeckOfCards(int);
		
		double get_deck_size() {
			return deck_size;}
		int get_cards_remaining(int card) {
			return cards_remaining[card];}
		
		void remove_from_deck(int);
		void init_deck_of_cards(int);
		void print_current_deck();
};

#endif