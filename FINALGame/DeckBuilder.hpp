#ifndef _DECKBUILDER_HPP_
#define _DECKBUILDER_HPP_

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <functional>
#include <ctime>
#include <cstdlib>

#define MAX_EQUIPS 4

#define DECKSIZE          40
#define MAXDECKSIZE       60

#define NO_PERSONALITIES  25
#define NO_DEFENSIVE      10
#define NO_ATTACKING      10
#define NO_SHOGUN         2
#define NO_CHANCELLOR     2
#define NO_CHAMPION       1

#define NO_HOLDINGS       17
#define NO_PLAIN          3
#define NO_MINE           3
#define NO_GOLD_MINE      3
#define NO_CRYSTAL_MINE   3
#define NO_FARMS          3
#define NO_SOLO           2

#define NO_FOLLOWERS      28
#define NO_FOOTSOLDIER    6
#define NO_ARCHER         6
#define NO_SIEGER         4
#define NO_CAVALRY        5
#define NO_NAVAL          5
#define NO_BUSHIDO        2

#define NO_ITEMS          12
#define NO_KATANA         4
#define NO_SPEAR          3
#define NO_BOW            2
#define NO_NINJATO        2
#define NO_WAKIZASHI      1

class GreenCard;
class BlackCard;
class player;
class Personality;
class Holding;

using namespace std;

class DeckBuilder {
private:
	list<GreenCard*>* green;
	list<BlackCard*>* black;


public:
	DeckBuilder();
	~DeckBuilder();
	list<GreenCard*>* createFateDeck();
	list<BlackCard*>* createDynastyDeck();
	void deckShuffler(list<BlackCard*>* black);
	void deckShuffler(list<GreenCard*>* green);
	list<GreenCard*>* get_hand() { return green; }  //green cards
	list<BlackCard*>* get_provinces() { return black; } //black cards
	void drawFateCard(DeckBuilder*);  //pick a green card
	void drawDynastyCard(DeckBuilder*, int);  //pick a black card
	void printHand();  //print green cards
	void printProvinces();  //print black cards except for Stronghold
	void print_revealed_provinces();
	void Reveal_provinces();  //reveal true for all provinces
	BlackCard* BuyDynastyCard(int, list<Personality*>*, list<Holding*>*, int&);  //at economy phase
	GreenCard* BuyFateCard(int ans, list<Holding*>*, int&);  //at equipment phase
	//void Load_into_Battle(vector<Personality*>*);  //pick personalities to come to the battle
};

#endif
