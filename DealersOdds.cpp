
#include "DealersOdds.h"

DealersOdds::DealersOdds () {
	hit_on_soft_17 = 0;
	init_odds_matrix(dealers_odds);
}

DealersOdds::DealersOdds (int hit) {
	hit_on_soft_17 = hit;
	init_odds_matrix(dealers_odds);
}

void DealersOdds::init_odds_matrix(map<int, map<string, double> >& dealers_odds) {
	map<string, double> hand_odds;
	init_hand_odds(hand_odds);
	dealers_odds[11] = hand_odds;
	dealers_odds[10] = hand_odds;
	dealers_odds[9] = hand_odds;
	dealers_odds[8] = hand_odds;
	dealers_odds[7] = hand_odds;
	dealers_odds[6] = hand_odds;
	dealers_odds[5] = hand_odds;
	dealers_odds[4] = hand_odds;
	dealers_odds[3] = hand_odds;
	dealers_odds[2] = hand_odds;
}

void DealersOdds::init_hand_odds(map<string, double>& hand_odds) {
	
	hand_odds["Bust"] = 0.0;
	hand_odds["21"] = 0.0;
	hand_odds["20"] = 0.0;
	hand_odds["19"] = 0.0;
	hand_odds["18"] = 0.0;
	hand_odds["17"] = 0.0;
}

void DealersOdds::print_odds(int precision, int width) {
	print_header(width, get_divider(width));
	for(int i = 11; i > 1; i--){
		print_row(dealers_odds[i], i, precision, width, get_divider(width));
	}
}

string DealersOdds::get_divider(int width) {
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

void DealersOdds::print_header(int width, string divider) {
	cout << divider;
	print_cell("     ", width, ' ');
	print_cell("17   ", width, ' ');
	print_cell("18   ", width, ' ');
	print_cell("19   ", width, ' ');
	print_cell("20   ", width, ' ');
	print_cell("21   ", width, ' ');
	print_cell("Bust  ", width, ' ');
	cout << "|\n";
	cout << divider;

}

void DealersOdds::print_row(map<string, double>& hand_odds, int hand_number, int precision, int width, string divider){
	string stemp = "";
	
	stemp = to_string(hand_number);
	if(hand_number == 11){
		stemp = "Ace";
	}
	print_cell(stemp+"   ", width, ' ');
	
	for(map<string, double>::iterator iter = hand_odds.begin(); iter!=hand_odds.end(); iter++){
		if(iter->second > 0) {
			stemp = to_string(iter->second).substr(1,1+precision);
			print_cell(stemp+"   ", width, ' ');
		}
		else if(iter->second == 0) {
			stemp = "-    ";
			print_cell(stemp, width, ' ');
		}
		else {
			stemp = to_string(iter->second).substr(0,3+precision);
			print_cell(stemp+" ", width, ' ');
		}
	}

	//Totals row of odds for error checking, should be 1.000
	if(false){
		double row_total = hand_odds["17"]+hand_odds["18"]+hand_odds["19"]+hand_odds["20"]+hand_odds["21"]+hand_odds["Bust"];
		stemp = to_string(row_total).substr(0,5);
		print_cell(" "+stemp+"  ", width, ' ');
	}
	
	cout << "|\n";
	cout << divider;
}

template<typename T> void DealersOdds::print_cell(T t, const int& width, const char& seperator) {
	cout << "|" << setw(width) << setfill(seperator) << t;
}

map<string, double> DealersOdds::get_single_hand_odds(int initial_card, DeckOfCards deck) {
	init_odds_matrix(dealers_odds);
	string hand = to_string(initial_card);
	int count = initial_card;
	bool soft = ((initial_card == 11) ? true : false);
	int last_card = initial_card;
	double odds = 1.0;
	play_single_hand_rec(hand, count, soft, initial_card, last_card, deck, odds, dealers_odds);
	
	return dealers_odds[initial_card];
}

void DealersOdds::play_all_hands(DeckOfCards deck) {
	
	init_odds_matrix(dealers_odds);
	string hand = "A";
	int count = 11;
	bool soft = true;
	int initial_card = 11;
	int last_card = 11;
	double odds = 1.0;
	play_single_hand_rec(hand, count, soft, initial_card, last_card, deck, odds, dealers_odds);
	
	for(int i = 2; i < 11; i++) {
		hand = to_string(i);
		count = i;
		soft = false;
		initial_card = i;
		last_card = i;
		odds = 1.0;
		play_single_hand_rec(hand, count, soft, initial_card, last_card, deck, odds, dealers_odds);
	}
}

int DealersOdds::play_single_hand_rec(string hand, int count, bool soft, int initial_card, int last_card, DeckOfCards deck, double odds, map<int, map<string, double> >& dealers_odds) {
	string new_hand;
	int new_count;
	bool new_soft;
	deck.remove_from_deck(last_card);
	double new_odds;
	
//Add Ace
	if(deck.get_cards_remaining(11) > 0) {
		new_hand = hand+", A";
		new_odds = (deck.get_cards_remaining(11) / deck.get_deck_size()) * odds;
		if(soft) {
			new_count = count + 1;
			new_soft = soft;
		}
		else {
			if(count < 11) {
				new_count = count + 11;
				new_soft = true;
			}
			else {
				new_count = count + 1;
				new_soft = soft;
			}
		}
		
		if(new_count > 16){
				if(new_count > 21) {
					cerr << "Error, Ace caused bust.\n";
					
				}
				else {
					switch(new_count) {
						case 21:
							dealers_odds[initial_card]["21"] = dealers_odds[initial_card]["21"] + new_odds;
							break;
						case 20:
							dealers_odds[initial_card]["20"] = dealers_odds[initial_card]["20"] + new_odds;
							break;
						case 19:
							dealers_odds[initial_card]["19"] = dealers_odds[initial_card]["19"] + new_odds;
							break;
						case 18:
							dealers_odds[initial_card]["18"] = dealers_odds[initial_card]["18"] + new_odds;
							break;
						case 17:
							if(hit_on_soft_17 && new_soft) {
								//cout << "Ace into Hit soft 17 \n";
								play_single_hand_rec(new_hand, new_count, new_soft, initial_card, 11, deck, new_odds, dealers_odds);
							}
							else {
								dealers_odds[initial_card]["17"] = dealers_odds[initial_card]["17"] + new_odds;
								break;
							}
					}
				}	
			}
			else {
				play_single_hand_rec(new_hand, new_count, new_soft, initial_card, 11, deck, new_odds, dealers_odds);
			}
	} 
	
//Add 2-10	
	for(int i =2; i < 11; i++){
		if(deck.get_cards_remaining(i) > 0) {
			new_hand = hand+", "+to_string(i);
			new_count = count+i;
			new_soft = soft;
			new_odds = (deck.get_cards_remaining(i) / deck.get_deck_size()) * odds;
			if(new_count > 16){
				if(new_count > 21) {
					if(soft) {
						new_count = new_count-10;
						new_soft = false;
						play_single_hand_rec(new_hand, new_count, new_soft, initial_card, i, deck, new_odds, dealers_odds);
					}
					else {
						dealers_odds[initial_card]["Bust"] = dealers_odds[initial_card]["Bust"] + new_odds;
					}
					
				}
				else {
					switch(new_count) {
						case 21:
							dealers_odds[initial_card]["21"] = dealers_odds[initial_card]["21"] + new_odds;
							break;
						case 20:
							dealers_odds[initial_card]["20"] = dealers_odds[initial_card]["20"] + new_odds;
							break;
						case 19:
							dealers_odds[initial_card]["19"] = dealers_odds[initial_card]["19"] + new_odds;
							break;
						case 18:
							dealers_odds[initial_card]["18"] = dealers_odds[initial_card]["18"] + new_odds;
							break;
						case 17:
							if(hit_on_soft_17 && new_soft) {
								//cout << i << " into Hit soft 17 \n";
								play_single_hand_rec(new_hand, new_count, new_soft, initial_card, i, deck, new_odds, dealers_odds);
							}
							else {
								dealers_odds[initial_card]["17"] = dealers_odds[initial_card]["17"] + new_odds;
								break;
							}
					}
				}
					
			}
			else {
				play_single_hand_rec(new_hand, new_count, new_soft, initial_card, i, deck, new_odds, dealers_odds);
			}
		}
	}
	return 21;
}

map<int, map<string, double> > DealersOdds::odds_diff(map<int, map<string, double> >& first_odds, map<int, map<string, double> >& second_odds) {
	map<int, map<string, double> > return_odds_diff;
	init_odds_matrix(return_odds_diff);
	
	for(int i = 11; i > 2; i--) {
		return_odds_diff[i]["17"] = first_odds[i]["17"] - second_odds[i]["17"];
		return_odds_diff[i]["18"] = first_odds[i]["18"] - second_odds[i]["18"];
		return_odds_diff[i]["19"] = first_odds[i]["19"] - second_odds[i]["19"];
		return_odds_diff[i]["20"] = first_odds[i]["20"] - second_odds[i]["20"];
		return_odds_diff[i]["21"] = first_odds[i]["21"] - second_odds[i]["21"];
		return_odds_diff[i]["Bust"] = first_odds[i]["Bust"] - second_odds[i]["Bust"];
	}
	
	return return_odds_diff;
}