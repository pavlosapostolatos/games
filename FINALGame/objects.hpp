#ifndef _OBJECTS_HPP_
#define _OBJECTS_HPP_
#include "DeckBuilder.hpp" 
enum types { PERSONALITY = 1, HOLDING, FOLLOWER, ITEM };  //4 types of cards
enum classes {
    ATTACKER = 1, DEFENDER, SHOGUN, CHANCELLOR, CHAMPION,
    PLAIN, MINE, GOLD_MINE, CRYSTAL_MINE, FARMS, SOLO, STRONGHOLD,
    FOOTSOLDIER, ARCHER, SIEGER, CAVALRY, NAVAL, BUSHIDO,
    KATANA, SPEAR, BOW, NINJATO, WAKIZASHI
};//23 kinds of cards 

class Mine;
class GoldMine;
class CrystalMine;
class Stronghold;

class player {
private:
    string name;
    DeckBuilder* property;  //cards that belong to the player 
    DeckBuilder* deck;  //all the player's cards, max 60
    int money;
    int honour;
    Stronghold* Stronghold_card;
    list <Personality*>* army;
    list <Holding*>* holdings;

public:
    player(string);
    ~player();
    void set_money(int a) { money = a; }
    void set_honour(int a) { honour = a; }
    string get_name() { return name; }
    int see_money() { return money; }
    int& get_money() { return money; }  //the value can be changed
    int get_honour() { return honour; }
    DeckBuilder* get_deck() { return deck; }  //cards not used yet
    DeckBuilder* get_property() { return property; } //cards belong to the player
    list <Personality*>* get_army() { return army; }
    list <Holding*>* get_holdings() { return holdings; }
    Stronghold* get_stronghold_card() { return Stronghold_card; } //stronghold
    void untapEverything();
    //void create_chain(Holding*, list<Holding*>*, short&);
    void Print_Holdings();
    void printPersonalities();
    void Print_Arena();
    void Load_into_Battle(list<Personality*>*);  //part of the army comes to the battle
    void Lose_all_Army_in_Battle(list<Personality*>*);
};


class Gameboard {
private:
    vector <player*> players;
public:
    Gameboard();
    ~Gameboard();
    void sort_players();  //determines the players' turn
    bool checkWinningCondition(); //if a winner has been found
    void initializehands(); //builds the decks
    void starting_phase();
    void equip_phase();
    void battle_phase();
    void economy_phase();
    void final_phase();
    void discardSurplusFateCards();  //throw away the additional cards (>6)
    void print_Game_Statistics();  //money, total attack, total defense
};

void consequences(list<Personality*>*, int);

#endif