#include "DeckBuilder.hpp"
#include "classes.hpp"

using namespace std;

DeckBuilder::DeckBuilder()
{
	black = new list<BlackCard*>();
	green = new list<GreenCard*>();
	srand(unsigned(time(NULL)));
}

DeckBuilder::~DeckBuilder()
{
	list<BlackCard*>::iterator it;
	list<GreenCard*>::iterator it2;
	it = black->begin();
	it2 = green->begin();
	while (it != black->end() && black->empty()==0){
		BlackCard* bl = *it;
		delete bl;
		black->remove((*it));
		it = black->begin();
	}
	while (it2 != green->end() && green->empty() == 0) {
		GreenCard* gr = *it2;
		delete gr;
		green->remove((*it2));
		it2 = green->begin();
	}
	delete black;
	delete green;
}

list<GreenCard*>* DeckBuilder::createFateDeck()
{
	int i;
	for (i = 0; i < NO_FOOTSOLDIER; i++)
		green->push_back(new Footsoldier("Peasants"));
	for (i = 0; i < NO_ARCHER; i++)
		green->push_back(new Archer("Elite Troops"));
	for (i = 0; i < NO_SIEGER; i++)
		green->push_back(new Sieger("Immortal Bushi"));
	for (i = 0; i < NO_CAVALRY; i++)
		green->push_back(new Cavalry("Unicorn Horses"));
	for (i = 0; i < NO_NAVAL; i++)
		green->push_back(new Atakebune("Yomi Ships"));
	for (i = 0; i < NO_BUSHIDO; i++)
		green->push_back(new Bushido("7 Samurai"));

	for (i = 0; i < NO_KATANA; i++)
		green->push_back(new Katana("Daijtso"));
	for (i = 0; i < NO_BOW; i++)
		green->push_back(new Bow("Yumi"));
	for (i = 0; i < NO_SPEAR; i++)
		green->push_back(new Spear("Kama"));
	for (i = 0; i < NO_NINJATO; i++)
		green->push_back(new Ninjato("Butterfly Dagger"));
	for (i = 0; i < NO_WAKIZASHI; i++)
		green->push_back(new Wakizashi("Kusanagi"));
	this->deckShuffler(green);
	return green;
}

list<BlackCard*>* DeckBuilder::createDynastyDeck()
{
	int i;
	//Create Personalities
	//NO_DEFENSIVE 10
	for (i = 0; i < NO_DEFENSIVE; i++)
		black->push_back(new Defender("Footsoldiers"));
	//NO_ATTACKING 10
	for (i = 0; i < NO_ATTACKING; i++)
		black->push_back(new Attacker("Steadfast bushi"));
	//NO_SHOGUN	2
	black->push_back(new Shogun("Akodo Kaneka"));
	black->push_back(new Shogun("Isawa Shi en"));
	//NO_CHANCELLOR 2
	black->push_back(new Chancellor("Hida Shozen"));
	black->push_back(new Chancellor("Mirimuto Enishi"));
	//NO_CHAMPION 1
	black->push_back(new Champion("Hida Kisada"));
	//Create holdings
	for (i = 0; i < NO_PLAIN; i++)
		black->push_back(new Plain("Rice Fields"));
	for (i = 0; i < NO_FARMS; i++)
		black->push_back(new Farmland("Fish Farms"));
	for (i = 0; i < NO_MINE; i++)
		black->push_back(new Mine("Ashio Copper Mine"));
	for (i = 0; i < NO_GOLD_MINE; i++)
		black->push_back(new GoldMine("Konomai Gold Mine"));
	for (i = 0; i < NO_CRYSTAL_MINE; i++)
		black->push_back(new CrystalMine("Ichinokawa Crystal Mine"));
	for (i = 0; i < NO_SOLO; i++)
		black->push_back(new GiftsandFavour("Gifts and Favors"));
	this->deckShuffler(black);
	return black;
}

void DeckBuilder::deckShuffler(list<BlackCard*>* black)
{
	vector<BlackCard*> vect;
	list<BlackCard*>::iterator it;
	for (it = black->begin(); it != black->end(); it++)
		vect.push_back((*it));
	random_shuffle(vect.begin(), vect.end());
	black->clear();
	vector<BlackCard*>::iterator it2;
	for (it2 = vect.begin(); it2 != vect.end(); it2++)
		black->push_back((*it2));
}

void DeckBuilder::deckShuffler(list<GreenCard*>* green)
{
	vector<GreenCard*> vect;
	list<GreenCard*>::iterator it;
	for (it = green->begin(); it != green->end(); it++)
		vect.push_back((*it));
	random_shuffle(vect.begin(), vect.end());
	green->clear();
	vector<GreenCard*>::iterator it2;
	for (it2 = vect.begin(); it2 != vect.end(); it2++)
		green->push_back((*it2));
}

void DeckBuilder::printHand() {  //green cards on the hand
	list<GreenCard*>::iterator it;
	short i = 0;
	cout << "GREEN CARDS ON HAND" << endl;
	for (it = green->begin(); it != green->end(); it++) {
		cout << "No " << ++i << endl;
		(*it)->print_card();
		cout << endl;
	}

}

void DeckBuilder::printProvinces() {
	list<BlackCard*>::iterator it;
	short i = 0;
	cout << "ALL PROVINCES" << endl;
	for (it = black->begin(); it != black->end(); it++) {
		cout << "No " << ++i << endl;
		(*it)->print_card();
		cout << endl;
	}
}

void DeckBuilder::print_revealed_provinces() {
	list<BlackCard*>::iterator it;
	short i = 0;
	cout << "REVEALED PROVINCES" << endl;
	for (it = black->begin(); it != black->end(); it++) {
		if ((*it)->get_isRevealed()) {
			cout << "No " << ++i << endl;
			(*it)->print_card();
			cout << endl;
		}
	}
}

void DeckBuilder::Reveal_provinces() {
	list<BlackCard*>::iterator it;
	for (it = black->begin(); it != black->end(); it++)
		(*it)->set_isRevealed(1); //black cards revealed
}

void DeckBuilder::drawFateCard(DeckBuilder* deck) { //picks the next card from the
	list<GreenCard*>::iterator it2;              //fate deck and puts it in the player's
	list<GreenCard*>* temp = deck->green;       //property
	if (temp->empty())
		cout << "No more Fate Cards" << endl;
	else {
		it2 = temp->begin();  //first card
		this->green->push_back(*it2);    //being put in the list
		(*it2)->handit();
		temp->remove(*it2);   //removed from the fate deck
	}
}

void DeckBuilder::drawDynastyCard(DeckBuilder* deck, int n) {//picks the next card from the
	list<BlackCard*>::iterator it2;       //Dynasty deck and puts it in the player's
	list<BlackCard*>* temp = deck->black;      //property
	if (temp->empty())
		cout << "No more Dynasty Cards" << endl;
	else {
		it2 = temp->begin();   //first card
		BlackCard* a = *it2;
		temp->remove(*it2);   //removed from the Dynasty deck
		this->black->push_back(a);  //being put in the list
		(a)->handit();
		a->set_isRevealed(n);   //true, is revealed
	}
}


BlackCard* DeckBuilder::BuyDynastyCard(int ans, list<Personality*>* pers, list<Holding*>* hold, int& money) {
	int i = 0, k;
	Personality* prs;
	Holding* hld;
	list<BlackCard*>::iterator it;
	list<Holding*>::iterator it2;

	for (it = this->black->begin(); it != this->black->end(); it++) {
		if ((*it)->get_isRevealed()) {
			++i;
			if (ans == i) {
				if (money >= (k = (*it)->get_cost())) {
					money -= k;
				}
				else {
					if (!hold->empty()) {  //list of player's holdings
						for (it2 = hold->begin(); it2 != hold->end() && money < k; it2++) {
							if ((*it2)->getistapped() == 0) {
								(*it2)->tap();
								money += (*it2)->get_Harvest();
							}
						}
					}
					if (money < k) {
						cout << "Not enough money. Purchase failed" << endl;
						return NULL;
					}
					else money = 0;
				}
				if ((*it)->getType() == PERSONALITY) {
					prs = (Personality*)(*it);
					pers->push_back(prs);
					this->black->remove(*it);   //remove it from provinces
					return prs;
				}
				else {
					hld = (Holding*)(*it);
					hold->push_back(hld);
					this->black->remove(*it);    //remove it from provinces
					return hld;
				}
			}
		}
	}
	return NULL;
}


GreenCard* DeckBuilder::BuyFateCard(int ans, list<Holding*>* hold, int& money) {
	int i = 0, k;
	GreenCard* grn;
	list<GreenCard*>::iterator it;
	list<Holding*>::iterator it3;
	for (it = this->green->begin(); it != this->green->end(); it++) {
		++i;
		if (ans == i) {
			if (money > (k = (*it)->get_cost())) {
				money -= k;
			}
			else {
				if (!hold->empty()) {  //check player's holdings
					for (it3 = hold->begin(); it3 != hold->end(); it3++) {
						if ((*it3)->getistapped() == 0) {
							(*it3)->tap();
							money += (*it3)->get_Harvest();
						}
					}
				}
				if (money < k) {
					cout << "Not enough money. Purchase failed" << endl;
					return NULL;
				}
				else money = 0;
			}
			grn = *it;
			this->green->remove(*it);   //remove from hand
			return (grn);  //return the card. With this card the loaded blackcard
						   //will be equiped
		}
	}
	return NULL;
}
