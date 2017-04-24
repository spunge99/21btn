/*Use "g++ -std=c++0x -o test 21OddsBuilder.cpp" to compile*/

#include <getopt.h>
#include <iostream>
#include <iomanip>
#include <map>
#include "DeckOfCards.h"
#include "DealersOdds.h"
#include "PlayersEV.h"

using namespace std;
static int number_of_decks = 1;
static int hit_on_soft_17 = 0;

int total = 0;

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

	DealersOdds dodds(hit_on_soft_17, deck);

	dodds.print_odds(8);
	
	PlayersEV pev;
	pev.print_out();

	
    return 0;
}