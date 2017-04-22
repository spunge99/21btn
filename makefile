CC = g++
CFLAGS= -Wall -Wextra -std=c++0x
OUT= test

all: DealersOdds.o 21OddsBuilder.o DeckOfCards.o
	$(CC) $(CFLAGS) DeckOfCards.o DealersOdds.o 21OddsBuilder.o -o $(OUT)

DeckOfCards.o: DeckOfCards.h DeckOfCards.cpp
	$(CC) $(CFLAGS) -c DeckOfCards.cpp
	
DealersOdds.o: DealersOdds.h DealersOdds.cpp DeckOfCards.h
	$(CC) $(CFLAGS) -c DealersOdds.cpp

21OddsBuilder.o: 21OddsBuilder.cpp DeckOfCards.h DealersOdds.h
	$(CC) $(CFLAGS) -c 21OddsBuilder.cpp
	
clean:
	rm -f *.o
	rm -f $(OUT)