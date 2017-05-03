
#include "PlayersEV.h"

PlayersEV::PlayersEV() {
	init_ev_table();
}

void PlayersEV::init_ev_table() {
	map<int, map<string, double> > ev_row;
	init_ev_row(ev_row);
	for(int i = 11; i > 1; i--) {
		for(int j = 11; j > 1; j--) {
			pair<int,int> hand(i,j);
			players_ev_table[hand] = ev_row;
		}
	}
}

void PlayersEV::init_ev_row(map<int, map<string, double> >& ev_row) {
	map<string, double> hand_ev;
	init_hand_ev(hand_ev);
	for(int i = 11; i > 1; i--) {
		ev_row[i] = hand_ev;
	}
}

void PlayersEV::init_hand_ev(map<string, double>& hand_ev) {
	hand_ev["Stand"] = 0.0;
	hand_ev["Hit"] = 0.0;
	hand_ev["Double"] = 0.0;
	hand_ev["Split"] = 0.0;
}

void PlayersEV::calc_all_hands_ev(DeckOfCards deck) {
	for(int first_card = 11; first_card > 1; first_card--) {
		for(int second_card = first_card; second_card > 1; second_card--) {
			for(int dealer_card = 11; dealer_card > 1; dealer_card--) {
				pair<int, int> players_hand (first_card, second_card);
				calc_all_hands_ev_rec(players_hand, dealer_card, deck);
			}
		}
	}
}

int PlayersEV::calc_all_hands_ev_rec(pair<int,int> players_hand, int dealers_hand, DeckOfCards deck) {
	deck.remove_from_deck(players_hand.first);
	return 0;
}

void PlayersEV::print_ev_table(int width) {
	print_ev_header(width, get_divider(width));
	for(int i = 11; i > 1; i--) {
		//cout << "here\n";
		for(int j = i; j > 1; j--){
			pair<int, int> players_hand(i,j);
			for(int k = 11; k > 1; k --) {
				print_ev_row(players_hand, k, width, get_divider(width));
			}
		}
	}
}

string PlayersEV::get_divider(int width) {
	string divider;
	string div_char = " ";
	for(int x = 0; x < width; x++) {
		div_char += "-";
	}
	for(int y = 0; y < 6; y++) {
		divider += div_char;
	}
	divider += " \n";
	return divider;
}

void PlayersEV::print_ev_header(int width, string divider) {
	cout << divider;
	print_cell("Player ", width, ' ');
	print_cell("Dealer ", width, ' ');
	print_cell("Stand  ", width, ' ');
	print_cell("Hit   ", width, ' ');
	print_cell("Double ", width, ' ');
	print_cell("Split  ", width, ' ');
	
	cout << "|\n";
	cout << divider;
}

void PlayersEV::print_ev_row(pair<int, int>& players_hand, int dealers_hand, int width, string divider) {
	string stemp1 = to_string(players_hand.first);
	if(players_hand.first == 11){
		stemp1 = "A";
	}
	string stemp2 = to_string(players_hand.second);
	if(players_hand.second == 11){
		stemp2 = "A";
	}
	string stemp = stemp1 + "," + stemp2;
	print_cell(" "+stemp+"  ", width, ' ');
	stemp = to_string(dealers_hand);
	if(dealers_hand == 11){
		stemp = "Ace";
	}
	print_cell(" "+stemp+"   ", width, ' ');
	
	for(map<string, double>::iterator iter = players_ev_table[players_hand][dealers_hand].begin(); iter!=players_ev_table[players_hand][dealers_hand].end(); iter++){
		if(iter->second > 0) {
			stemp = to_string(iter->second).substr(1,4);
			print_cell(stemp+"   ", width, ' ');
		}
		else if(iter->second == 0) {
			stemp = "- ";
			print_cell(stemp+"   ", width, ' ');
		}
		else {
			stemp = to_string(iter->second).substr(0,6);
			print_cell(stemp+" ", width, ' ');
		}
	}
	
	cout << "|\n";
	cout << divider;
}

template<typename T> void PlayersEV::print_cell(T t, const int& width, const char& seperator) {
	cout << "|" << setw(width) << setfill(seperator) << t;
}