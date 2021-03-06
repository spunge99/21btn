
#ifndef __DEALERSODDS_H

#define __DEALERSODDS_H

#include <iostream>
#include <iomanip>
#include <map>
#include "DeckOfCards.h"

using namespace std;

class DealersOdds{
	private:
		int hit_on_soft_17;
		map<int, map<string, double> > dealers_odds;
	public:
		DealersOdds();
		DealersOdds(int);
		map<int, map<string, double> > get_dealers_odds() {
			return dealers_odds; }
		void init_odds_matrix(map<int, map<string, double> >&);
		void init_hand_odds(map<string, double>&);

		void print_odds(int, int);
		string get_divider(int);
		void print_header(int, string);
		void print_row(map<string, double>&, int, int, int, string);
		template<typename T> void print_cell(T t, const int&, const char&);

		map<string, double> get_single_hand_odds(int, DeckOfCards);
		void play_all_hands(DeckOfCards);
		int play_single_hand_rec(string, int, bool, int, int, DeckOfCards, double, map<int, map<string, double> >&);
		map<int, map<string, double> > odds_diff(map<int, map<string, double> >&, map<int, map<string, double> >&);
};

#endif