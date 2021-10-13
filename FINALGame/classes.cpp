#include "classes.hpp"

//set_stats(args) initialises the data memebers of the cards, according to their type

Katana::Katana(string name) : Item(name, KATANA) {
    this->set_stats(0, 2, 0, 1, 1, 2, 3);
}
Katana::~Katana() {}


Spear::Spear(string name) : Item(name, SPEAR) {
    this->set_stats(0, 0, 2, 1, 1, 2, 3);
}
Spear::~Spear() {}


Bow::Bow(string name) : Item(name, BOW) {
    this->set_stats(2, 2, 2, 2, 3, 4, 5);
}
Bow::~Bow() {}


Ninjato::Ninjato(string name) : Item(name, NINJATO) {
    this->set_stats(4, 3, 3, 3, 2, 2, 4);
}
Ninjato::~Ninjato() {}


Wakizashi::Wakizashi(string name) : Item(name, WAKIZASHI) {
    this->set_stats(8, 5, 5, 3, 3, 3, 8);
}
Wakizashi::~Wakizashi() {}


Footsoldier::Footsoldier(string name) : Follower(name, FOOTSOLDIER) {
    this->set_stats(0, 2, 0, 1, 1, 2);
}
Footsoldier::~Footsoldier() {}


Archer::Archer(string name) : Follower(name, ARCHER) {
    this->set_stats(0, 0, 2, 1, 1, 2);
}
Archer::~Archer() {}


Cavalry::Cavalry(string name) : Follower(name, CAVALRY) {
    this->set_stats(3, 4, 2, 3, 3, 4);
}
Cavalry::~Cavalry() {}


Bushido::Bushido(string name) : Follower(name, BUSHIDO) {
    this->set_stats(8, 8, 8, 6, 3, 8);
}
Bushido::~Bushido() {}


Sieger::Sieger(string name) : Follower(name, SIEGER) {
    this->set_stats(5, 3, 3, 2, 2, 3);
}
Sieger::~Sieger() {}


Atakebune::Atakebune(string name) : Follower(name, NAVAL) {
    this->set_stats(3, 2, 4, 3, 3, 4);
}
Atakebune::~Atakebune() {}


Attacker::Attacker(string name) : Personality(name, ATTACKER) {
    this->set_stats(5, 3, 2, 2);
}
Attacker::~Attacker() {}


Defender::Defender(string name) : Personality(name, DEFENDER) {
    this->set_stats(5, 2, 3, 2);
}
Defender::~Defender() {}


Champion::Champion(string name) : Personality(name, CHAMPION) {
    this->set_stats(30, 20, 20, 12);
}
Champion::~Champion() {}


Chancellor::Chancellor(string name) : Personality(name, CHANCELLOR) {
    this->set_stats(15, 5, 10, 8);
}
Chancellor::~Chancellor() {}


Shogun::Shogun(string name) : Personality(name, SHOGUN) {
    this->set_stats(15, 10, 5, 8);
}
Shogun::~Shogun() {}


Plain::Plain(string name) : Holding(name, PLAIN) {
    this->set_stats(2, 2);
}
Plain::~Plain() {}


Mine::Mine(string name) : Holding(name, MINE) {
    this->set_stats(5, 3);
}
Mine::~Mine() {}


GoldMine::GoldMine(string name) : Holding(name, GOLD_MINE) {
    this->set_stats(7, 5);
}
GoldMine::~GoldMine() {}


CrystalMine::CrystalMine(string name) : Holding(name, CRYSTAL_MINE) {
    this->set_stats(12, 6);
}
CrystalMine::~CrystalMine() {}


Farmland::Farmland(string name) : Holding(name, FARMS) {
    this->set_stats(3, 4);
}
Farmland::~Farmland() {}


GiftsandFavour::GiftsandFavour(string name) : Holding(name, SOLO) {
    this->set_stats(2, 2);
}
GiftsandFavour::~GiftsandFavour() {}


Stronghold::Stronghold(string name) : Holding(name, STRONGHOLD) {
    Starting_Honour = rand() % 10 + 1;
    InitialDefense = 5;
    Harvest = 5;
    this->set_isRevealed(1);
    this->handit();   //it belongs to the player
    Cost = 0;
}
Stronghold::~Stronghold() {}

void Mine::set_chain(list<Holding*>* hld) { //this: the card that was bought
	list <Holding*>::iterator it;
	list <Holding*>::iterator it2;
	for (it = hld->begin(); it != hld->end(); it++) { //search the list with the player's holdings
		if ((*it)->get_connected() != 2) { //if holding not fully connected
			if ((*it)->get_Kind() == GOLD_MINE) {
				//harv += this->get_harvest() + 2;  //mine
				this->get_harvest() += 2;  //mine
				if ((*it)->get_connected() == 0) {
					//harv += (*it)->get_harvest() + 4;  //gold mine
					(*it)->get_harvest() += 4;  //gold mine
					(*it)->set_Holding(this);
					return;
				}
				else if ((*it)->get_connected() == 1) {
					for (it2 = hld->begin(); it2 != hld->end() && (*it2)->get_connected() != 2; it2++) {
						if ((*it2)->get_Kind() == CRYSTAL_MINE && (*it2)->get_connected() == 1) {
							Holding* hold = *it2;
							(*it)->complete_Holding(this, hold);
							return;	//*it is gold mine, this: mine, hold is crystal mine
						}
					}
				}
			}
		}
	}
}

void GoldMine::set_chain(list<Holding*>* hld) {
	list <Holding*>::iterator it;
	list <Holding*>::iterator it2;
	bool con1 = false, con2 = false;
	for (it = hld->begin(); it != hld->end(); it++) { //search the list with the player's holdings
		if ((*it)->get_connected() != 2) { //if holding not fully connected
			if ((*it)->get_Kind() == MINE) {
				if ((*it)->get_connected() == 0) {
					//harv += this->get_harvest() + 4;  //gold mine
					//harv += (*it)->get_harvest() + 2;   //mine
					this->get_harvest() += 4;  //gold mine
					(*it)->get_harvest() += 2;   //mine
					this->set_Holding(*it);
					con1 = true;
				}
				//search the list with the player's holdings again
				for (it2 = hld->begin(); it2 != hld->end() && (*it2)->get_connected() != 2; it2++) {
					if ((*it2)->get_Kind() == CRYSTAL_MINE && (*it2)->get_connected() == 0) {
						Holding* hold1 = *it;
						Holding* hold2 = *it2;
						this->complete_Holding(hold1, hold2);
						return;	//this: gold mine, hold1 is mine, hold2 is crystal mine
					}
				}
				if (con1)
					return; //connection has been made
			}
			else if ((*it)->get_Kind() == CRYSTAL_MINE) {
				if ((*it)->get_connected() == 0) {
					//harv += this->get_harvest() + 5;  //gold mine
					//harv += 2 * (*it)->get_harvest();   //crystal mine
					this->get_harvest() += 5;  //gold mine
					(*it)->get_harvest() *= 2;   //crystal mine
					this->set_Holding(*it);
					con2 = true;
				}
				//search the list with the player's holdings again
				for (it2 = hld->begin(); it2 != hld->end() && (*it2)->get_connected() != 2; it2++) {
					if ((*it2)->get_Kind() == MINE && (*it2)->get_connected() == 0) {
						(*it2)->get_harvest() += 2;
						Holding* hold1 = *it;
						Holding* hold2 = *it2;
						this->complete_Holding(hold1, hold2);
						return;	//this: gold mine, hold2 is mine, hold1 is crystal mine
					}
				}
				if (con2)
					return; //connection has been made
			}
		}
	}
	
}

void CrystalMine::set_chain(list<Holding*>* hld) { //this: the card that was bought
	list <Holding*>::iterator it;
	list <Holding*>::iterator it2;
	for (it = hld->begin(); it != hld->end(); it++) { //search the list with the player's holdings
		if ((*it)->get_connected() != 2) {  //if holding not fully connected
			if ((*it)->get_Kind() == GOLD_MINE) {
				//harv += 2 * this->get_harvest();   //crystal mine
				this->get_harvest() *= 2;   //crystal mine
				if ((*it)->get_connected() == 0) {
					//harv += (*it)->get_harvest() + 5;  //gold mine
					(*it)->get_harvest() += 5;  //gold mine
					(*it)->set_Holding(this);
					return;
				}
				else if ((*it)->get_connected() == 1) {
					for (it2 = hld->begin(); it2 != hld->end() && (*it2)->get_connected() != 2; it2++) {
						if ((*it2)->get_Kind() == MINE && (*it2)->get_connected() == 1) {
							Holding* hold = *it2;
							(*it)->complete_Holding(hold, this);
							return;
							//*it is gold mine, hold is mine, this: crystal mine
						}
					}
				}
			}
		}
	}
}
