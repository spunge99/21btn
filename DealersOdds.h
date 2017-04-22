
#ifndef __DEALERSODDS_H

#define __DEALERSODDS_H

#include <iostream>
#include <iomanip>
#include <map>
#include "DeckOfCards.h"

using namespace std;

struct deck_of_cards
{
	double deck_size = 0;
	map<int, int> cards_remaining;
};

class DealersOdds{
	private:
		int number_of_decks;
		int hit_on_soft_17;
		map<int, map<string, double> > dealers_odds;
	public:
		DealersOdds();
		DealersOdds(int, DeckOfCards);
		map<int, map<string, double> > get_dealers_odds() {
			return dealers_odds; }
		void init_deck_of_cards(deck_of_cards&, int);
		void print_current_deck(deck_of_cards&);
		void init_odds_matrix(map<int, map<string, double> >&);
		void init_hand_odds(map<string, double>&);

		void print_odds(int);
		void printRow(map<string, double>&, int, int, string);
		template<typename T> void printCell(T t, const int&, const char&);

		void play_all_hands(DeckOfCards);
		int play_all_hands_rec(string, int, bool, int, int, DeckOfCards, double, map<int, map<string, double> >&);
		map<int, map<string, double> > odds_diff(map<int, map<string, double> >&, map<int, map<string, double> >&);
};

#endif