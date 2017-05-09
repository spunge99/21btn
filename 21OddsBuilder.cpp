/*
Copyright © 2017 Matt Share.

*/
/*Use "g++ -std=c++0x 21OddsBuilder.cpp" to compile*/

#include <getopt.h>
#include <iostream>
#include <iomanip>
#include <map>
#include <fstream>
#include <sstream>
#include "DeckOfCards.h"
#include "DealersOdds.h"
#include "PlayersEV.h"

using namespace std;
static const string CONFIG_FILE_NAME = "config.txt";
static map<string, string> CONFIG;
static int HIT_ON_SOFT_17 = 0;

struct option long_options[] =
{
  {"number_of_decks",   required_argument, NULL, 'd'},
  {"hit",   no_argument, &HIT_ON_SOFT_17, 1},
  { 0, 0, 0, 0 }
};

void load_Config(string);
void init_Config();

int main(int argc, char** argv)
{
    int c, option_index=0;
	load_Config(CONFIG_FILE_NAME);
	
	while ((c = getopt_long (argc, argv, "d:", long_options, &option_index)) != EOF)
    {
 	    switch (c)
	    {
			case 0:
				break;
			case 'd':
					CONFIG["NUMBER_OF_DECKS"] = optarg;
					break;
 	    }
    }
	cout << "number of decks = "<< CONFIG["NUMBER_OF_DECKS"] <<"\n";
	if(HIT_ON_SOFT_17)
		CONFIG["HIT_ON_SOFT_17"] = to_string(HIT_ON_SOFT_17);
	string message = stoi(CONFIG["HIT_ON_SOFT_17"]) ? "Dealer hits on soft 17\n" : "Dealer stands on soft 17\n";
	cout << message;
	
	DeckOfCards deck(stoi(CONFIG["NUMBER_OF_DECKS"]));

	DealersOdds dodds(stoi(CONFIG["HIT_ON_SOFT_17"]));
	
	//dodds.print_odds(stoi(CONFIG["PRECISION"]), stoi(CONFIG["CELL_WIDTH"]));
	
	dodds.get_single_hand_odds(6, deck);
	dodds.print_header(stoi(CONFIG["CELL_WIDTH"]), dodds.get_divider(stoi(CONFIG["CELL_WIDTH"])));
	dodds.print_row(dodds.get_dealers_odds()[6], 6, stoi(CONFIG["PRECISION"]), stoi(CONFIG["CELL_WIDTH"]), dodds.get_divider(stoi(CONFIG["CELL_WIDTH"])));
	
	PlayersEV pev(stoi(CONFIG["HIT_ON_SOFT_17"]));
	pair<int, int> players_hand1(8,10);
	int dealers_hand1 = 3;
	pair<int, int> players_hand2(2,3);
	int dealers_hand2 = 11;
	pair<int, int> players_hand3(11,6);
	int dealers_hand3 = 6;
	
	//pev.calc_all_hands_ev(deck);
	
	pev.print_ev_header(stoi(CONFIG["CELL_WIDTH"]), pev.get_divider(stoi(CONFIG["CELL_WIDTH"])));
	
	pev.get_single_hands_ev(players_hand1, dealers_hand1, deck);
	pev.print_ev_row(players_hand1, dealers_hand1, stoi(CONFIG["PRECISION"]), stoi(CONFIG["CELL_WIDTH"]), pev.get_divider(stoi(CONFIG["CELL_WIDTH"])));
	pev.get_single_hands_ev(players_hand2, dealers_hand2, deck);
	pev.print_ev_row(players_hand2, dealers_hand2, stoi(CONFIG["PRECISION"]), stoi(CONFIG["CELL_WIDTH"]), pev.get_divider(stoi(CONFIG["CELL_WIDTH"])));
	pev.get_single_hands_ev(players_hand3, dealers_hand3, deck);
	pev.print_ev_row(players_hand3, dealers_hand3, stoi(CONFIG["PRECISION"]), stoi(CONFIG["CELL_WIDTH"]), pev.get_divider(stoi(CONFIG["CELL_WIDTH"])));
	
	//pev.print_ev_table(stoi(CONFIG["PRECISION"]), stoi(CONFIG["CELL_WIDTH"]));
	
    return 0;
}

void load_Config(string config_file_name) {
	init_Config();
	ifstream file;
	file.open(config_file_name);
	string line;
	while(getline(file, line)) {
		istringstream iss(line);
		string key, value;
		if(getline(iss, key, '=')) {
			if(getline(iss, value)) {
				CONFIG[key] = value;
			}
		}
	}
	file.close();
}

void init_Config() {
	CONFIG["NUMBER_OF_DECKS"] = "1";
	CONFIG["HIT_ON_SOFT_17"] = "0";
}