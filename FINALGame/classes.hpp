#ifndef _CLASSES_HPP_
#define _CLASSES_HPP_
#include "objects.hpp"
#include "cards.hpp"

//23 kinds of cards, constructors, destructors

class Katana : public Item {
public:
    Katana(string);
    ~Katana();
};


class Spear : public Item {
public:
    Spear(string);
    ~Spear();
};


class Bow : public Item {
public:
    Bow(string);
    ~Bow();
};


class Ninjato : public Item {
public:
    Ninjato(string);
    ~Ninjato();
};


class Wakizashi : public Item {
public:
    Wakizashi(string);
    ~Wakizashi();
};


class Footsoldier : public Follower {
public:
    Footsoldier(string);
    ~Footsoldier();
};


class Archer : public Follower {
public:
    Archer(string);
    ~Archer();
};


class Cavalry : public Follower {
public:
    Cavalry(string);
    ~Cavalry();
};


class Bushido : public Follower {
public:
    Bushido(string);
    ~Bushido();
};


class Sieger : public Follower {
public:
    Sieger(string);
    ~Sieger();
};


class Atakebune : public Follower {
public:
    Atakebune(string);
    ~Atakebune();
};


class Attacker : public Personality {
public:
    Attacker(string);
    ~Attacker();
};


class Defender : public Personality {
public:
    Defender(string);
    ~Defender();
};


class Champion : public Personality {
public:
    Champion(string);
    ~Champion();
};


class Chancellor : public Personality {
public:
    Chancellor(string);
    ~Chancellor();
};



class Shogun : public Personality {
public:
    Shogun(string);
    ~Shogun();
};


class Plain : public Holding {
public:
    Plain(string);
    ~Plain();
};


class Mine : public Holding {
public:
    Mine(string);
    ~Mine();
    void set_chain(list<Holding*>*);
};


class GoldMine : public Holding {
public:
    GoldMine(string);
    ~GoldMine();
    void set_chain(list<Holding*>*);
};


class CrystalMine : public Holding {
public:
    CrystalMine(string);
    ~CrystalMine();
    void set_chain(list<Holding*>*);
};


class Farmland : public Holding {
public:
    Farmland(string);
    ~Farmland();
};

class GiftsandFavour : public Holding {
public:
    GiftsandFavour(string);
    ~GiftsandFavour();
};


class Stronghold : public Holding {
public:
    short Starting_Honour;
    short InitialDefense;
    Stronghold(string);
    ~Stronghold();
};
#endif