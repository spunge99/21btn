CC = g++
CFLAGS= -Wall -Wextra -std=c++0x
OUT= test

all: DeckOfCards.o DealersOdds.o PlayersEV.o 21OddsBuilder.o  
	$(CC) $(CFLAGS) DeckOfCards.o DealersOdds.o PlayersEV.o 21OddsBuilder.o -o $(OUT)

DeckOfCards.o: DeckOfCards.h DeckOfCards.cpp
	$(CC) $(CFLAGS) -c DeckOfCards.cpp
	
DealersOdds.o: DealersOdds.h DealersOdds.cpp DeckOfCards.h
	$(CC) $(CFLAGS) -c DealersOdds.cpp
	
PlayersEV.o: PlayersEV.h PlayersEV.cpp DeckOfCards.h DealersOdds.h
	$(CC) $(CFLAGS) -c PlayersEV.cpp

21OddsBuilder.o: 21OddsBuilder.cpp DeckOfCards.h DealersOdds.h PlayersEV.h
	$(CC) $(CFLAGS) -c 21OddsBuilder.cpp
	
clean:
	rm -f *.o
	rm -f $(OUT)