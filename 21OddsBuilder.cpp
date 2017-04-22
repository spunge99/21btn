/*Use "g++ -std=c++0x -o test 21OddsBuilder.cpp" to compile*/

#include <getopt.h>
#include <iostream>
#include <iomanip>
#include <map>
#include "DeckOfCards.h"
#include "DealersOdds.h"

using namespace std;
static int number_of_decks = 1;
static int hit_on_soft_17 = 0;

int total = 0;

/*struct deck_of_cards
{
	double deck_size = 0;
	map<int, int> cards_remaining;
};*/

/*void init_deck_of_cards(deck_of_cards&, int);
void print_current_deck(deck_of_cards&);
void init_odds_matrix(map<int, map<string, double> >&);
void init_hand_odds(map<string, double>&);

void print_odds(map<int, map<string, double> >&, int);
void printRow(map<string, double>&, int, int, string);
template<typename T> void printCell(T t, const int&, const char&);

void play_all_hands(map<int, map<string, double> >&);
int play_all_hands_rec(string, int, bool, int, int, deck_of_cards, double, map<int, map<string, double> >&);
map<int, map<string, double> > odds_diff(map<int, map<string, double> >&, map<int, map<string, double> >&);*/

struct option long_options[] =
{
  {"number of decks",   required_argument, NULL, 'd'},
  {"hit",   no_argument, &hit_on_soft_17, 1},
  { 0, 0, 0, 0 }
};

int main(int argc, char** argv)
{
    int c, option_index=0;
	
	while ((c = getopt_long (argc, argv, "d:", long_options, &option_index)) != EOF)
    {
 	    switch (c)
	    {
			case 0:
				break;
			case 'd':
					number_of_decks = atoi(optarg);
					cout << "number of decks = "<< number_of_decks <<"\n";
					break;
 	    }
    } 
	if(hit_on_soft_17){
		cout << "Dealer hits on soft 17\n";
	}
	
	DeckOfCards deck;
	//deck.remove_from_deck(11);
	//deck.print_current_deck();
	
	//map<int, map<string, double> > dealers_odds;
	DealersOdds dodds(hit_on_soft_17, deck);
	//dodds.play_all_hands(deck);
	//dealers_odds = dodds.get_dealers_odds();
	dodds.print_odds(8);
	//dodds.play_all_hands(dodds.dealers_odds);
	//dodds.printOdds(dodds.dealers_odds, 8);
	/*init_odds_matrix(dealers_odds);
	play_all_hands(dealers_odds);
	print_odds(dealers_odds, 8);
	
	map<int, map<string, double> > dealers_odds_hit;
	hit_on_soft_17 = 1;
	cout << "Dealer hits on soft 17\n";
	init_odds_matrix(dealers_odds_hit);
	play_all_hands(dealers_odds_hit);
	print_odds(dealers_odds_hit, 8);
	
	map<int, map<string, double> > odds_difference;
	odds_difference = odds_diff(dealers_odds, dealers_odds_hit);
	cout << "Difference: No Hit - Hit\n";
	print_odds(odds_difference, 9);*/
	
    return 0;
}

void init_deck_of_cards(deck_of_cards& deck, int number_of_decks) {
	deck.deck_size = 52 * number_of_decks;
	deck.cards_remaining[11] = 4 * number_of_decks;
	deck.cards_remaining[10] = 16 * number_of_decks;
	for(int i = 9; i > 1; i--) {
		deck.cards_remaining[i] = 4 * number_of_decks;
	}
	//print_current_deck(deck);
}

/*
void print_current_deck(deck_of_cards& deck) {
	for(int j = 11; j > 1; j--) {
		if(j == 11)
			cout << "Ace:" << deck.cards_remaining[j] << " ";
		else
			cout << j << ":" << deck.cards_remaining[j] << " ";
	}
	cout << "\n";
}

void init_odds_matrix(map<int, map<string, double> >& dealers_odds) {
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

void init_hand_odds(map<string, double>& hand_odds) {
	
	hand_odds["Bust"] = 0.0;
	hand_odds["21"] = 0.0;
	hand_odds["20"] = 0.0;
	hand_odds["19"] = 0.0;
	hand_odds["18"] = 0.0;
	hand_odds["17"] = 0.0;
}

void print_odds(map<int, map<string, double> >& dealers_odds, int width) {
	string divider;
	string div_char = " ";
	for(int x = 0; x < width; x++) {
		div_char += "-";
	}
	for(int y = 0; y < 7; y++) {
		divider += div_char;
	}
	divider += " \n";
	
	cout << divider;
	printCell("     ", width, ' ');
	printCell("17   ", width, ' ');
	printCell("18   ", width, ' ');
	printCell("19   ", width, ' ');
	printCell("20   ", width, ' ');
	printCell("21   ", width, ' ');
	printCell("Bust  ", width, ' ');
	cout << "|\n";
	cout << divider;
	for(int i = 11; i > 1; i--){
		printRow(dealers_odds[i], i, width, divider);
	}
}

void printRow(map<string, double>& hand_odds, int hand_number, int width, string divider){
	string stemp = "";
	
	stemp = to_string(hand_number);
	if(hand_number == 11){
		stemp = "Ace";
	}
	printCell(stemp+"   ", width, ' ');
	
	for(map<string, double>::iterator iter = hand_odds.begin(); iter!=hand_odds.end(); iter++){
		if(iter->second > 0) {
			stemp = to_string(iter->second).substr(1,4);
			printCell(stemp+"   ", width, ' ');
		}
		else if(iter->second == 0) {
			stemp = "- ";
			printCell(stemp+"   ", width, ' ');
		}
		else {
			stemp = to_string(iter->second).substr(0,6);
			printCell(stemp+" ", width, ' ');
		}
	}

	
	if(false){
		double row_total = hand_odds["17"]+hand_odds["18"]+hand_odds["19"]+hand_odds["20"]+hand_odds["21"]+hand_odds["Bust"];
		stemp = to_string(row_total).substr(0,5);
		printCell(" "+stemp+"  ", width, ' ');
	}
	
	cout << "|\n";
	cout << divider;
}

template<typename T> void printCell(T t, const int& width, const char& seperator) {
	cout << "|" << setw(width) << setfill(seperator) << t;
}

void play_all_hands(map<int, map<string, double> >& dealers_odds) {
	deck_of_cards deck;
	init_deck_of_cards(deck, number_of_decks);
	
	string hand = "A";
	int count = 11;
	bool soft = true;
	int initial_card = 11;
	int last_card = 11;
	double odds = 1.0;
	play_all_hands_rec(hand, count, soft, initial_card, last_card, deck, odds, dealers_odds);
	
	for(int i = 2; i < 11; i++) {
		hand = to_string(i);
		count = i;
		soft = false;
		initial_card = i;
		last_card = i;
		odds = 1.0;
		play_all_hands_rec(hand, count, soft, initial_card, last_card, deck, odds, dealers_odds);
	}
}

int play_all_hands_rec(string hand, int count, bool soft, int initial_card, int last_card, deck_of_cards deck, double odds, map<int, map<string, double> >& dealers_odds) {
	string new_hand;
	int new_count;
	bool new_soft;
	deck.cards_remaining[last_card] = deck.cards_remaining[last_card] - 1;
	deck.deck_size = deck.deck_size - 1;
	double new_odds;
	
//Add Ace
	if(deck.cards_remaining[11] > 0) {
		new_hand = hand+", A";
		new_odds = (deck.cards_remaining[11] / deck.deck_size) * odds;
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
								play_all_hands_rec(new_hand, new_count, new_soft, initial_card, 11, deck, new_odds, dealers_odds);
							}
							else {
								dealers_odds[initial_card]["17"] = dealers_odds[initial_card]["17"] + new_odds;
								break;
							}
					}
				}	
			}
			else {
				play_all_hands_rec(new_hand, new_count, new_soft, initial_card, 11, deck, new_odds, dealers_odds);
			}
	} 
	
//Add 2-10	
	for(int i =2; i < 11; i++){
		if(deck.cards_remaining[i] > 0) {
			new_hand = hand+", "+to_string(i);
			new_count = count+i;
			new_soft = soft;
			new_odds = (deck.cards_remaining[i] / deck.deck_size) * odds;
			if(new_count > 16){
				if(new_count > 21) {
					if(soft) {
						new_count = new_count-10;
						new_soft = false;
						play_all_hands_rec(new_hand, new_count, new_soft, initial_card, i, deck, new_odds, dealers_odds);
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
								play_all_hands_rec(new_hand, new_count, new_soft, initial_card, i, deck, new_odds, dealers_odds);
							}
							else {
								dealers_odds[initial_card]["17"] = dealers_odds[initial_card]["17"] + new_odds;
								break;
							}
					}
				}
					
			}
			else {
				play_all_hands_rec(new_hand, new_count, new_soft, initial_card, i, deck, new_odds, dealers_odds);
			}
		}
	}
	return 21;
}

map<int, map<string, double> > odds_diff(map<int, map<string, double> >& first_odds, map<int, map<string, double> >& second_odds) {
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
} */