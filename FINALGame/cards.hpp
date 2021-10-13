#ifndef _CARDS_HPP_
#define _CARDS_HPP_

//there are 4 types of cards, and 23 kinds of cards 

class Card {
protected:
    short Cost;
    bool IsTapped;  //true for tapped, false for untapped
    string name;
    enum classes kind;  //kind of the card, 23 in total
    bool IsOnHand;  //true if the card is in a player's property
public:
    Card(string name, enum classes kind);
    virtual ~Card();
    virtual enum types getType() = 0;
    enum classes get_Kind() { return kind; }  //23 kinds of cards
    virtual void print_card() {
        cout << "Name: " << name << endl;
        cout << "IsTapped: " << IsTapped << endl;
        cout << "Kind: " << kind << endl; //a number that matches the card's position in the enumeration
    }
    void untap() { IsTapped = 0; }  //not being used by the player
    void tap() { IsTapped = 1; }  //being used by the player
    bool IsonHand() { return IsOnHand; }
    void handit() { IsOnHand = 1; }
    short get_cost() { return Cost; }
    bool getistapped() { return IsTapped; }
};


class GreenCard : public Card {
protected:     //as described in the exercise 
    short AttackBonus;
    short DefenceBonus;
    short MinimumHonor;
    short EffectBonus;
    short EffectCost;
public:
    GreenCard(string name, enum classes kind);
    virtual ~GreenCard();
    virtual enum types getType() = 0;
    short get_AttackBonus() { return AttackBonus; }
    short get_DefenseBonus() { return DefenceBonus; }
    virtual void print_card() {
        cout << "Cost: " << Cost << endl;
        cout << "AttackBonus: " << AttackBonus << endl;
        cout << "DefenceBonus: " << DefenceBonus << endl;
        cout << "MinimumHonor: " << MinimumHonor << endl;
        cout << "EffectBonus: " << EffectBonus << endl;
        cout << "EffectCost: " << EffectCost << endl;
        this->Card::print_card();
    }
    short get_MinimumHonor() { return MinimumHonor; }
    short get_efcost() { return EffectCost; }
    void upgrade() {  //at equipment phase 
        AttackBonus += EffectBonus;
        DefenceBonus += EffectBonus;
    }
};



class BlackCard : public Card {
protected:
    bool isRevealed;  //true for revealed
public:
    BlackCard(string name, enum classes kind);
    virtual ~BlackCard();
    virtual enum types getType() = 0;
    bool get_isRevealed() { return isRevealed; }
    void set_isRevealed(bool a) { isRevealed = a; }
};



class Follower : public GreenCard {

public:
    Follower(string name, enum classes kind);
    virtual ~Follower();
    enum types getType() { return FOLLOWER; }
    void set_stats(short c, short a, short d, short mh, short eb, short ec) {
        Cost = c;
        AttackBonus = a;
        DefenceBonus = d;
        MinimumHonor = mh;
        EffectBonus = eb;
        EffectCost = ec;
    }
};


class Item : public GreenCard
{
private:
    short Durability;
public:
    Item(string name, enum classes kind);
    virtual ~Item();
    enum types getType() { return ITEM; }
    void print_card() {
        this->GreenCard::print_card();
        cout << "Durability: " << Durability << endl;
    }
    void set_stats(short c, short a, short d, short mh, short eb, short ec, short db) {
        Cost = c;
        AttackBonus = a;
        DefenceBonus = d;
        MinimumHonor = mh;
        EffectBonus = eb;
        EffectCost = ec;
        Durability = db;
    }
    void desharpen() { Durability--; } //at battle phase 
    short get_durability() { return Durability; }
};



class Personality : public BlackCard {
private:
    short Attack;
    short Defence;
    short Honor;

    vector<GreenCard*>* inventory;  //followers and items that belong to a personality
public:
    Personality(string, enum classes);
    virtual ~Personality();
    enum types getType() { return PERSONALITY; }
    short get_Attack() { return Attack; }
    short get_Defence() { return Defence; }
    void set_stats(short c, short a, short d, short h) {
        Cost = c;
        Attack = a;
        Defence = d;
        Honor = h;
    }
    void print_card() {
        cout << "Cost: " << Cost << endl;
        cout << "Attack: " << Attack << endl;
        cout << "Defence: " << Defence << endl;
        this->Card::print_card();
    }
    vector<GreenCard*>* get_inventory() { return inventory; }
    short get_honour() { return Honor; }
    int get_defpower();  //a personality's defence including the defence of their inventory    
    int get_attpower(); //a personality's attack including the attack of their inventory    
    void shame() { Honor--; } //loses honour, battle phase

};



class Holding : public BlackCard {
protected:
    short Harvest;
    int connected;  //0 if not in chain, 2 if in full chain, 1 if in simple chain
public:
    Holding(string, enum classes);
    virtual ~Holding();
    short& get_harvest() { return Harvest; }
    short get_Harvest() { return Harvest; }
    enum types getType() { return HOLDING; }
    int get_connected() { return connected; }
    void set_connected(int n) { connected = n; }
    void set_stats(short c, short h) {
        Cost = c;
        Harvest = h;
    }
    void print_card() {
        cout << "Cost: " << Cost << endl;
        cout << "Harvest: " << Harvest << endl;
        cout << "connected: " << connected << endl;
        this->Card::print_card();
    }
    virtual void set_chain(list<Holding*>*);
    void set_Holding(Holding*);// connect in simple chain
    void complete_Holding(Holding*, Holding*);//create the full chain 
};

#endif