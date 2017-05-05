
#include "PlayersEV.h"

PlayersEV::PlayersEV() {
	dealer_hits_on_soft_17 = 0;
	blackjack_payout = 1.5;
	init_ev_table();
}

PlayersEV::PlayersEV(int dealer_hits) {
	dealer_hits_on_soft_17 = dealer_hits;
	blackjack_payout = 1.5;
	init_ev_table();
}

void PlayersEV::init_ev_table() {
	map<int, map<string, double> > ev_row;
	init_ev_row(ev_row);
	for(int i = 11; i > 1; i--) {
		for(int j = i; j > 1; j--) {
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

map<string, double> PlayersEV::get_single_hands_ev(pair<int,int>& players_hand, int dealers_hand, DeckOfCards deck) {
	init_ev_table();
	
	if(players_hand.second > players_hand.first) {							//This swap ensures duplicate,reverse pairs will not be input into table
		int temp = players_hand.second;
		players_hand.second = players_hand.first;
		players_hand.first = temp;
	}
	
	calc_single_hands_ev(players_hand, dealers_hand, deck);
	return players_ev_table[players_hand][dealers_hand];
}

void PlayersEV::calc_all_hands_ev(DeckOfCards deck) {
	for(int first_card = 11; first_card > 1; first_card--) {
		//cout << "1===1=====1=====1\n";
		for(int second_card = first_card; second_card > 1; second_card--) {
			//cout << "2*****2*****2\n";
			for(int dealers_hand = 11; dealers_hand > 1; dealers_hand--) {
				//cout << "3____3\n";
				pair<int, int> players_hand (first_card, second_card);
				calc_single_hands_ev(players_hand, dealers_hand, deck);
			}
		}
	}
}

void PlayersEV::calc_single_hands_ev(pair<int,int>& players_hand, int dealers_hand, DeckOfCards deck) {
	deck.remove_from_deck(players_hand.first);
	deck.remove_from_deck(players_hand.second);
	deck.remove_from_deck(dealers_hand);
	int count = players_hand.first + players_hand.second;
	bool soft = ((players_hand.first == 11 || players_hand.second == 11) ? true : false);
	int last_card = 0;
	double odds = 1.0;
	calc_single_hands_ev_rec(players_hand, dealers_hand, count, soft, last_card, deck, odds).first;
}

pair<string, double> PlayersEV::calc_single_hands_ev_rec(pair<int,int>& players_hand, int dealers_hand, int count, bool soft, int last_card, DeckOfCards deck, double odds) {
	pair<string, double> highest_ev;
	map<string, double> hand_ev;
	init_hand_ev(hand_ev);
	DealersOdds dodds(dealer_hits_on_soft_17, deck);
	
	if(count > 21) {
		if(soft) {
			count = count-10;
			soft = false;
		}
		else {
			highest_ev.first = "Hit";
			highest_ev.second = -1.0;
			return highest_ev;
		}
					
	}
	
	//delete-me
	if(odds > 0.0) {cout << "";}
	
	
	if(last_card != 0) 									//last_card == 0 indicates this is initial run, there is no last card
			deck.remove_from_deck(last_card);
			
	hand_ev["Stand"] = calc_stand_ev(count, dodds.get_dealers_odds()[dealers_hand]);
	hand_ev["Hit"] = calc_hit_ev(count, dodds);
	hand_ev["Double"] = calc_double_ev(count, dodds);
	hand_ev["Split"] = calc_split_ev(count, dodds);
	
	if(last_card == 0) {								//last_card == 0 indicates this is initial run, can set object table
		if(count == 21) {
			players_ev_table[players_hand][dealers_hand]["Stand"] = blackjack_payout;
		}
		else {
			players_ev_table[players_hand][dealers_hand]["Stand"] = hand_ev["Stand"];
		}
		players_ev_table[players_hand][dealers_hand]["Hit"] = hand_ev["Hit"];
		players_ev_table[players_hand][dealers_hand]["Double"] = hand_ev["Double"];
		players_ev_table[players_hand][dealers_hand]["Split"] = hand_ev["Split"];
	}
	
	highest_ev = get_highest_ev_option(hand_ev);
	return highest_ev;
}

double PlayersEV::calc_stand_ev(int count, map<string, double>& dealer_hand_odds) {
	double total_ev = 0.0;
	for(map<string, double>::iterator iter = dealer_hand_odds.begin(); iter != dealer_hand_odds.end(); iter++){
		//cout << "\n" << count << " ? " << iter->first;
		if(iter->first != "Bust") {
			if(count > stoi(iter->first)) {
				//cout << "\n" << total_ev << " + " << iter->second;
				total_ev += 1.0 * iter->second;
				//cout << " = " << total_ev;
			}
				
			else if(count < stoi(iter->first)) {
				//cout << "\n" << total_ev << " - " << iter->second;
				total_ev += -1.0 * iter->second;
				//cout << " = " << total_ev;
			}
				
			else if(count == stoi(iter->first)){
				//cout << "\n" << total_ev << " + 0";
				total_ev += 0.0 * iter->second;
				//cout << " = " << total_ev;
			}
			else {
				cout << "Count not correctly evaluated in calc_stand_ev\n";
			}
				
		}
		else {
			//cout << "\nBust!! " << total_ev << " + " << iter->second;;
			total_ev += 1.0 * iter->second;
			//cout << " = " << total_ev;
		}
	}
	return total_ev;
}

double PlayersEV::calc_hit_ev(int count, DealersOdds& dodds) {
	dodds.get_dealers_odds();
	if(count > 0) {cout << "";}
	return 2.0;
}

double PlayersEV::calc_double_ev(int count, DealersOdds& dodds) {
	dodds.get_dealers_odds();
	if(count > 0) {cout << "";}
	return 0.0;
}

double PlayersEV::calc_split_ev(int count, DealersOdds& dodds) {
	dodds.get_dealers_odds();
	if(count > 0) {cout << "";}
	return 0.1;
}

pair<string, double> PlayersEV::get_highest_ev_option(map<string, double>& hand_ev) {
	double highest_ev = -2.1;
	string highest_ev_option = "Stand";
	for(map<string, double>::iterator iter = hand_ev.begin(); iter != hand_ev.end(); iter++) {
		if(iter->second > highest_ev) {
				highest_ev = iter->second;
				highest_ev_option = iter->first;
		}
	}
	pair<string, double> highest(highest_ev_option, highest_ev);
	return highest;
}

void PlayersEV::print_ev_table(int precision, int width) {
	print_ev_header(width, get_divider(width));
	for(int i = 11; i > 1; i--) {
		for(int j = i; j > 1; j--){
			pair<int, int> players_hand(i,j);
			for(int k = 11; k > 1; k --) {
				print_ev_row(players_hand, k, precision, width, get_divider(width));
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
	for(int y = 0; y < 7; y++) {
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
	print_cell("Best  ", width, ' ');
	
	cout << "|\n";
	cout << divider;
}

void PlayersEV::print_ev_row(pair<int, int>& players_hand, int dealers_hand, int precision, int width, string divider) {
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
	
	stemp = get_stemp(players_ev_table[players_hand][dealers_hand]["Stand"], precision);
	print_cell(stemp, width, ' ');
	stemp = get_stemp(players_ev_table[players_hand][dealers_hand]["Hit"], precision);
	print_cell(stemp, width, ' ');
	stemp = get_stemp(players_ev_table[players_hand][dealers_hand]["Double"], precision);
	print_cell(stemp, width, ' ');
	stemp = get_stemp(players_ev_table[players_hand][dealers_hand]["Split"], precision);
	print_cell(stemp, width, ' ');
	
	stemp = get_highest_ev_option(players_ev_table[players_hand][dealers_hand]).first;
	print_cell(stemp+"  ", width, ' ');
	
	cout << "|\n";
	cout << divider;
}

string PlayersEV::get_stemp(double ev, int precision) {
	string stemp;
	if(ev > 0) {
		stemp = to_string(ev).substr(0,2+precision)+"  ";
	}
	else if(ev == 0) {
			stemp = "-    ";
	}
	else {
		stemp = to_string(ev).substr(0,3+precision)+"  ";
	}
	return stemp;
}

template<typename T> void PlayersEV::print_cell(T t, const int& width, const char& seperator) {
	cout << "|" << setw(width) << setfill(seperator) << t;
}