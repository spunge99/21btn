
#ifndef __PLAYERSEV_H

#define __PLAYERSEV_H

#include <iostream>
#include <map>
#include "DeckOfCards.h"
#include "DealersOdds.h"

using namespace std;

class PlayersEV{
	private:
		int dealer_hits_on_soft_17; 
		double blackjack_payout;
		map<pair<int,int>, map<int, map<string, double> > > players_ev_table;
	public:
		PlayersEV();
		PlayersEV(int);
		map<pair<int, int>, map<int, map<string, double> > > get_players_ev_table() {
			return players_ev_table; }
		
		void init_ev_table();
		void init_ev_row(map<int, map<string, double> >&);
		void init_hand_ev(map<string, double>&);
		
		map<string, double> get_single_hands_ev(pair<int,int>&, int, DeckOfCards);
		void calc_all_hands_ev(DeckOfCards);
		void calc_single_hands_ev(pair<int,int>&, int, DeckOfCards);
		pair<string, double> calc_single_hands_ev_rec(pair<int,int>&, int, int, bool, int, DeckOfCards, double odds);
		double calc_stand_ev(int, map<string, double>&);
		double calc_hit_ev(int, DealersOdds&);
		double calc_double_ev(int, DealersOdds&);
		double calc_split_ev(int, DealersOdds&);
		pair<string, double> get_highest_ev_option(map<string, double>&);
		
		void print_ev_table(int, int);
		string get_divider(int);
		void print_ev_header(int, string);
		void print_ev_row(pair<int, int>&, int, int, int, string);
		string get_stemp(double, int);
		template<typename T> void print_cell(T t, const int&, const char&);
};

#endif