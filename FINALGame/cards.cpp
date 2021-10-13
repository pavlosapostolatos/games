#include"classes.hpp"

Card::Card(string name, enum classes kind) {
	this->name = name;
	this->kind = kind;
	IsTapped = 0;
}
Card::~Card() {}


GreenCard::GreenCard(string name, enum classes kind) : Card(name, kind) {}
GreenCard::~GreenCard() {}


BlackCard::BlackCard(string name, enum classes kind) : Card(name, kind) {
	isRevealed = 0; //not revealed at the beginning
}
BlackCard::~BlackCard() {}


Follower::Follower(string name, enum classes kind) : GreenCard(name, kind) {}
Follower::~Follower() {}

Item::Item(string name, enum classes kind) : GreenCard(name, kind) {}
Item::~Item() {}

Personality::Personality(string name, enum classes kind) : BlackCard(name, kind) {
	inventory = new vector<GreenCard*>();  //its followers and items
}
Personality::~Personality() {
	vector<GreenCard*>::iterator it;   //delete the inventory
	it = inventory->begin();
	while ( inventory->empty() == 0 && it != inventory->end()) {
		GreenCard* gr = *it;
		delete gr;
		inventory->erase(it);
		it = inventory->begin();
	}
	delete inventory;
}


Holding::Holding(string name, enum classes kind) : BlackCard(name, kind) {
	connected = 0;    //at the beginning not in a chain
}
Holding::~Holding() {}


void Holding::set_Holding(Holding* bought) {  //connect in simple chain
	bought->set_connected(1);
	this->set_connected(1);
}

void Holding::complete_Holding(Holding* h1, Holding* h2/*, short& harv*/) {//create the full chain
	h1->set_connected(2);
	h2->set_connected(2);
	this->set_connected(2);
	//harv += 3 * this->get_harvest();   //from gold mine
	//harv += 4 * h2->get_harvest();     //from crystal mine
	this->get_harvest() *= 3;   //from gold mine
	h2->get_harvest() *= 4;     //from crystal mine
}

int Personality::get_defpower() {
	int defence = 0;
	vector<GreenCard*>::iterator grn;
	defence += this->get_Defence();  //personality's defense
	for (grn = this->get_inventory()->begin(); grn != this->get_inventory()->end()
		&& (this)->get_inventory()->empty() == 0; grn++)
		defence += (*grn)->get_DefenseBonus();  //inventory's defence
	return defence;  //total defense
}

int Personality::get_attpower() {
	int attack = 0;
	vector<GreenCard*>::iterator grn;
	attack += this->get_Attack();  //personality's attack
	for (grn = this->get_inventory()->begin(); grn != this->get_inventory()->end()
		&& (this)->get_inventory()->empty() == 0; grn++)
		attack += (*grn)->get_AttackBonus();  //inventory's attack
	return attack;  //total attack
}

void Holding::set_chain(list<Holding*>* hld){}
//implemented only for mine, gold mine, crystal mine
//every other holding is not connected in chain

/*void player::create_chain(Holding* bought, list<Holding*>* hld, short& harv) {
	list <Holding*>::iterator it;
	list <Holding*>::iterator it2;
	if ((bought)->get_Kind() == MINE) {
		for (it = hld->begin(); it != hld->end(); it++) { //search the list with the player's holdings
			if ((*it)->get_connected() != 2) { //if holding not fully connected
				if ((*it)->get_Kind() == GOLD_MINE) {
					harv += bought->get_harvest() + 2;  //mine
					if ((*it)->get_connected() == 0) {
						harv += (*it)->get_harvest() + 4;  //gold mine
						(*it)->set_Holding(bought);
						return;
					}
					else if ((*it)->get_connected() == 1) {
						for (it2 = hld->begin(); it2 != hld->end() && (*it2)->get_connected() != 2; it2++) {
							if ((*it2)->get_Kind() == CRYSTAL_MINE && (*it2)->get_connected() == 1) {
								Holding* hold = *it2;
								(*it)->complete_Holding(bought, hold, harv);
								return;	//*it is gold mine, bought is mine, hold is crystal mine
							}
						}
					}
				}
			}
		}
	}
	else if (bought->get_Kind() == GOLD_MINE) {
		for (it = hld->begin(); it != hld->end(); it++) { //search the list with the player's holdings
			if ((*it)->get_connected() != 2) { //if holding not fully connected
				if ((*it)->get_Kind() == MINE) {
					if ((*it)->get_connected() == 0) {
						harv += bought->get_harvest() + 4;  //gold mine
						harv += (*it)->get_harvest() + 2;   //mine
						bought->set_Holding(*it);
					}
					//search the list with the player's holdings again
					for (it2 = hld->begin(); it2 != hld->end() && (*it2)->get_connected() != 2; it2++) {
						if ((*it2)->get_Kind() == CRYSTAL_MINE && (*it2)->get_connected() == 0) {
							Holding* hold1 = *it;
							Holding* hold2 = *it2;
							bought->complete_Holding(hold1, hold2, harv);
							return;	//bought is gold mine, hold1 is mine, hold2 is crystal mine
						}
					}

				}
			}
		}
	}
	else if (bought->get_Kind() == CRYSTAL_MINE) {
		for (it = hld->begin(); it != hld->end(); it++) { //search the list with the player's holdings
			if ((*it)->get_connected() != 2) {  //if holding not fully connected
				if ((*it)->get_Kind() == GOLD_MINE) {
					harv += 2 * bought->get_harvest();   //crystal mine
					if ((*it)->get_connected() == 0) {
						harv += (*it)->get_harvest() + 5;  //gold mine
						(*it)->set_Holding(bought);
						return;
					}
					else if ((*it)->get_connected() == 1) {
						for (it2 = hld->begin(); it2 != hld->end() && (*it2)->get_connected() != 2; it2++) {
							if ((*it2)->get_Kind() == MINE && (*it2)->get_connected() == 1) {
								Holding* hold = *it2;
								(*it)->complete_Holding(hold, bought, harv);
								return;
								//*it is gold mine, hold is mine, bought is crystal mine
							}
						}
					}
				}
			}
		}
	}
}
*/