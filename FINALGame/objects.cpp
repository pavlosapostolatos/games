#include "classes.hpp"

player::player(string n) {
	name = n;
	deck = new DeckBuilder();   //whole deck
	property = new DeckBuilder();  //hand for green cards, provinces for black
	deck->createDynastyDeck();
	deck->createFateDeck();
	Stronghold_card = new Stronghold("Ashina Castle");
	army = new list<Personality*>();
	holdings = new list<Holding*>();
}

player::~player() {
	delete property;
	delete deck;
	delete Stronghold_card;
	this->get_holdings()->remove(Stronghold_card);
	list<Personality*>::iterator it;
	list<Holding*>::iterator it2;
	it = army->begin();
	it2 = holdings->begin();
	while (army->empty() == 0 && it != army->end()){ //delete army
		Personality *p = *it;
		delete p;
		army->remove((*it));
		it = army->begin();
	}
	while (holdings->empty() == 0 && it2 != holdings->end()){  //delete holdings
		Holding* h = *it2;
		delete h;
		holdings->remove((*it2));
		it2 = holdings->begin();
	}
	delete army;
	delete holdings;
}

void player::untapEverything() {  //all the cards become untapped, army, holdings
	list<Personality*>::iterator pr;
	list<Holding*>::iterator hld;
	vector<GreenCard*>::iterator inv;
	for (pr = this->get_army()->begin(); this->get_army()->empty() == 0 &&
		pr != this->get_army()->end(); pr++) {
		for (inv = (*pr)->get_inventory()->begin(); (*pr)->get_inventory()->empty() == 0
			&& inv != (*pr)->get_inventory()->end(); inv++) {
			(*inv)->untap();           //followers and equipment of the army
		}
		(*pr)->untap();
	}
	for (hld = this->get_holdings()->begin(); this->get_holdings()->empty() == 0 &&
		hld != this->get_holdings()->end(); hld++) {
		(*hld)->untap();
	}
}

void player::Print_Holdings() {  //bought holdings
	list<Holding*>* hld;
	list<Holding*>::iterator it;
	hld = this->get_holdings();
	if (hld->empty())
		cout << "No holdings" << endl;
	else {
		cout << "HOLDINGS" << endl;
		for (it = hld->begin(); it != hld->end(); it++) {
			(*it)->print_card();
			cout << endl;
		}
	}
}

void player::printPersonalities() {  //army, bought, untapped personalities, without inventory
	list<Personality*>::iterator prs;
	int i = 0;
	if (this->get_army()->empty() == 0) {   //army exists
		cout << "UNTAPPED PERSONALITIES" << endl;
		for (prs = this->get_army()->begin(); prs != this->get_army()->end(); prs++) {
			if ((*prs)->getistapped() == 0) {
				cout << "No " << ++i << endl;
				(*prs)->print_card();
				cout << endl;
			}
		}
	}
}

void player::Print_Arena() {  //army
	list<Personality*>* blc;
	vector<GreenCard*>* grn;
	list<Personality*>::iterator it;
	vector<GreenCard*>::iterator it2;
	blc = this->get_army();
	if (blc->empty())
		cout << "Empty Arena" << endl;
	else {
		cout << "ARENA" << endl;    //army 
		for (it = blc->begin(); it != blc->end(); it++) {
			(*it)->print_card();
			cout << endl;
			grn = (*it)->get_inventory();   //with followers and items is exists
			for (it2 = grn->begin(); it2 != grn->end() && grn->empty() == 0; it2++) {
				(*it2)->print_card();
				cout << endl;
			}
		}
	}
}

void player::Load_into_Battle(list<Personality*>* battle) {
	int ans = -1, i = 0;
	while (ans != 0) {
		list<Personality*>::iterator pers = this->get_army()->begin();
		if (this->get_army()->empty()) {
			cout << "No personalities for selection. " << endl;
			cout << "Press 0 to continue." << endl;
			cin >> ans;
			if (ans == 0)
			return;
		}
		else {
			this->printPersonalities();  //prints untapped personalities
			i = 0;
			cout << "Enter your selection (Press 0 to end this procedure): ";
			cin >> ans;
			if (ans == 0)
				return;
			while (1) {
				while ((*pers)->getistapped() == 1)
					pers++;
				if (++i == ans) {   //found the selected personality
					battle->push_back(*pers);  //goes in the army for the battle
					this->get_army()->erase(pers);  //not in player's army anymore
					break;
				}
				else pers++;
			}
		}
	}
}

void player::Lose_all_Army_in_Battle(list<Personality*>* lost_army) {
list<Personality*>::iterator loser;
vector<GreenCard*>::iterator grn;

	if (lost_army->empty())
		return;       //no army to be destroyed
	loser = lost_army->begin();
	grn = (*loser)->get_inventory()->begin();
	while (lost_army->empty() == 0 && loser != lost_army->end()) {
		while (grn != (*loser)->get_inventory()->end() && (*loser)->get_inventory()->empty() == 0) {
			GreenCard* gr = *grn;
			delete gr;
			(*loser)->get_inventory()->erase(grn);
			grn = (*loser)->get_inventory()->begin();
		}
		(*loser)->get_inventory()->clear();
		Personality* p = *loser;
		delete p;
		lost_army->remove(*loser);
		loser = lost_army->begin();
	}   //destroy the army
	lost_army->clear();
}

Gameboard::Gameboard() {
	players.push_back(new player("Pavlos"));
	players.push_back(new player("Eftychia"));
}

Gameboard::~Gameboard() {
	vector<player*>::iterator it;
	it = players.begin();
	while (players.empty() == 0 && it != players.end()) {
		player* pl = *it;
		delete pl;
		players.erase(it);
		it = players.begin();
	}
}

void Gameboard::initializehands() {
	vector<player*>::iterator it;
	DeckBuilder* temp, * temp2;
	Stronghold* init;
	for (it = players.begin(); it != players.end(); it++) {
		temp = (*it)->get_property();
		temp2 = (*it)->get_deck();
		init = (*it)->get_stronghold_card();
		temp->drawFateCard(temp2);
		temp->drawFateCard(temp2);//2 cards out of max 6
		list<BlackCard*>* prov = temp->get_provinces();
		for (int i = 0; i < 4; i++)
			temp->drawDynastyCard(temp2, 1);  //the rest 4 cards, not revealed
		(*it)->get_holdings()->push_back(init);  //stronghold at lists with holdings
		(*it)->set_honour((*it)->get_stronghold_card()->Starting_Honour);
		(*it)->set_money((*it)->get_stronghold_card()->get_Harvest());
	}
	this->sort_players();  //determines the turn of play
}

void Gameboard::sort_players() {
	int i, j, n = players.size();
	player* b;
	player** a = players.data();
	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - i - 1; j++) {
			if (a[j]->get_honour() < a[j + 1]->get_honour()) {
				b = a[j];
				a[j] = a[j + 1];
				a[j + 1] = b;
			}
		}
	}
}

bool Gameboard::checkWinningCondition() {
	vector<player*>::iterator it;
	DeckBuilder* temp;
	it = players.begin();
	while ( players.empty() == 0 && it != players.end()) {
		temp = (*it)->get_property();
		if (temp->get_provinces()->empty()) {
			cout << (*it)->get_name() << " lost the game." << endl;
			player* pl = *it;
			delete pl;
			players.erase(it);
			it = players.begin();
		}
		else {
			it++;
		}
	}
	if (players.size() == 1) {
		it = players.begin();
		cout << (*it)->get_name() << " won the game." << endl;
		return 1;
	}
	return 0;
}


void Gameboard::starting_phase() {   //as described in exercise
	vector<player*>::iterator it;
	DeckBuilder* temp;
	for (it = players.begin(); it != players.end(); it++) {
		cout << "PLAYER: " << (*it)->get_name() << endl;
		temp = (*it)->get_property();
		(*it)->untapEverything();   //untap army, holdings
		temp->drawFateCard((*it)->get_deck());  //pick a green card from fate deck
		temp->Reveal_provinces();
		temp->printHand();
		temp->printProvinces();
	}
}

void Gameboard::equip_phase() {
	vector<player*>::iterator it;
	list <Personality*>* cards;
	list <Personality*>::iterator it2;
	int bans = -1, gans = -1, ans, i = 0;
	char an;
	for (it = players.begin(); it != players.end(); it++) {
		GreenCard* bought = NULL;
		list <Personality*>* cards = (*it)->get_army();
		bans = -1;

		while (bans != 0 && !cards->empty()) {  //if army exists
			cout << (*it)->get_name() << "'s TURN" << endl;
			i = 0;
			cards = (*it)->get_army();           
			for (it2 = cards->begin(); it2 != cards->end(); it2++) {
				cout << "No " << ++i << endl;
				(*it2)->print_card();      //print army
				cout << endl;
			}
			cout << "Choose which black card to load. Enter 0 to end this phase." << endl;
			cin >> bans;  //this black card will be equiped next if a green is bought
			if (bans == 0) break;
			ans = -1;
			while (ans != 0) {
				(*it)->get_property()->printHand();    //print green cards on hand
				cout << "Choose which green card to buy. Enter 0 not to buy." << endl;
				cin >> ans;
				if (ans == 0) {
					cout << "No Green Card was bought." << endl;
					break;
				}
				bought = (*it)->get_property()->BuyFateCard(ans, (*it)->get_holdings(), (*it)->get_money());
				if (bought != NULL) {
					it2 = cards->begin();
					i = 1;
					while (i != bans) {  //find the black card
						i++;
						it2++;
					}
					Personality* npc = *it2;  //loaded card from army
					vector<GreenCard*>* equips = npc->get_inventory();
					if (equips->size() < MAX_EQUIPS && (npc->get_honour() >= (bought)->get_MinimumHonor())) {
						equips->push_back(bought);
						(*it)->get_property()->get_hand()->remove(bought);   //delete later
						cout << "Do you want to upgrade the green card? Press y" << endl;
						cin >> an;
						if (an == 'y' && (*it)->see_money() > (bought)->get_efcost()) {
							(*it)->set_money((*it)->see_money() - (bought)->get_efcost());
							(bought)->upgrade();   //upgrade the card
						}
					}
				}
			}
		}
	}
}

void Gameboard::battle_phase() {
	vector<player*>::iterator it, it2;
	int i, ans, damage = 0, defense = 0, result, province_def;
	list<Personality*>* atk = new list<Personality*>(), * def = new list<Personality*>();
	list<Personality*>::iterator tempatk, tempdef;
	list<BlackCard*>::iterator prov;
	BlackCard* target = NULL;
	player* attacker, * defender;
	vector<GreenCard*>::iterator grn;
	for (it = players.begin(); it != players.end(); it++) {
		if (!(*it)->get_army()->empty()) {  //if the player has army
			i = 0, damage = 0, defense = 0;
			attacker = *it;   //player who attacks
			cout << attacker->get_name() << " select which player you want to attack:" << endl;
			for (it2 = players.begin(); it2 != players.end(); it2++) {
				if (it != it2) {  //cannot attack themrselves
					cout << ++i << ". " << (*it2)->get_name() << endl;
				}
			}
			cin >> ans;
			it2 = players.begin();
			if (it == it2)   //cannot attack themselves
				it2++;
			for (i = 1; i < ans; i++) {  //find the above chosen player to attack
				it2++;
				if (it == it2)
					it2++;
			}
			defender = *it2;   //player who defends

			defender->get_property()->printProvinces();
			cout << attacker->get_name() << " select which province you want to attack: " << endl;
			cin >> ans;  //selects a province
			prov = defender->get_property()->get_provinces()->begin();
			for (int k = 1; k < ans; k++)
				prov++;
			target = *prov;
			cout << "Attacker " << (attacker)->get_name() << " choose which personalities to attack with from the below: " << endl;
			attacker->Load_into_Battle(atk);
			cout << "Defender " << (defender)->get_name() << " choose which personalities to defend with from the below: " << endl;
			defender->Load_into_Battle(def);
			for (tempatk = atk->begin(); tempatk != atk->end() && atk->empty() == 0; tempatk++) {
				damage += (*tempatk)->get_attpower();
			}
			for (tempdef = def->begin(); tempdef != def->end() && def->empty() == 0; tempdef++) {
				defense += (*tempdef)->get_defpower();
			}
			province_def = defender->get_stronghold_card()->InitialDefense;
			result = damage - defense - province_def;

			if (result > province_def) {
				cout << attacker->get_name() << " attacker destoyed a province." << endl;
				defender->Lose_all_Army_in_Battle(def);
				BlackCard* tar = target;
				delete tar;
				defender->get_property()->get_provinces()->remove(target);
			}
			else {
				if (result < 0) {   //attack < defence
					cout << defender->get_name() << " defender won" << endl;
					attacker->Lose_all_Army_in_Battle(atk);
					consequences(def, result);
				}
				else if (result == 0) {  //attack == defence
					cout << "Tie" << endl;
					defender->Lose_all_Army_in_Battle(def);
					attacker->Lose_all_Army_in_Battle(atk);
				}
				else {   //attack > defence
					cout << attacker->get_name() << " attacker won" << endl;
					defender->Lose_all_Army_in_Battle(def);
					consequences(atk, result);
				}
			}
			//load troops back to army
			for (tempatk = atk->begin(); atk->empty() == 0 && tempatk != atk->end(); tempatk++)
				attacker->get_army()->push_back(*tempatk);
			for (tempdef = def->begin(); def->empty() == 0 && tempdef != def->end(); tempdef++)
				defender->get_army()->push_back(*tempdef);
			atk->clear();
			def->clear();
		}
	}
	//delete target;
	delete atk;
	delete def;
}

void consequences(list<Personality*>* troops, int key) {

	list<Personality*>::iterator temp;
	vector<GreenCard*>::iterator eqp;
	bool tapped = false;
	int att = 0;
	if (key > 0) {   //attack > defence
		tapped = true;
	}
	else {  //attack < defence
		key = -key;
	}
	
	if (troops->empty())     //no army exists any more
		return;
	temp = troops->begin();
	eqp = (*temp)->get_inventory()->begin();
	while (temp != troops->end() && troops->empty() == 0 && att < key) {
		while (eqp != (*temp)->get_inventory()->end() &&
			(*temp)->get_inventory()->empty() == 0 && att < key) {
			if ((*eqp)->getType() == FOLLOWER) {
				att += (*eqp)->get_AttackBonus();
				GreenCard* g = *eqp;
				delete g;
				(*temp)->get_inventory()->erase(eqp);
				eqp = (*temp)->get_inventory()->begin();
			}
			else {
				eqp++;
			}
		}
		att += (*temp)->get_Attack();
		if ((*temp)->get_inventory()->empty() == 0)
			(*temp)->get_inventory()->clear();    //items have to be deleted too
		Personality* p = *temp;
		delete p;
		troops->remove(*temp);
		temp = troops->begin();
	}

	if (troops->empty())
		return;
	for (temp = troops->begin(); temp != troops->end() && troops->empty() == 0; temp++) {
		for (eqp = (*temp)->get_inventory()->begin(); eqp != (*temp)->get_inventory()->end()
			&& (*temp)->get_inventory()->empty() == 0; eqp++) {
			if (tapped) {     //attack > defence
				if ((*eqp)->getType() == FOLLOWER)
					(*eqp)->tap();
			}
			if ((*eqp)->getType() == ITEM) {
				((Item*)(*eqp))->desharpen();
				if (((Item*)*eqp)->get_durability() == 0) {
					GreenCard* g = *eqp;
					delete g;
					(*temp)->get_inventory()->erase(eqp);
				}
			}
		}
		(*temp)->shame();
		if (tapped) {    //attack > defence
			(*temp)->tap();
		}
		if ((*temp)->get_honour() == 0) {
			(*temp)->print_card();
			cout << endl << "Performed Seppuku" << endl;
			Personality* p = *temp;
			delete p;
			troops->remove(*temp);
		}
	}
}

void Gameboard::economy_phase() {
	vector<player*>::iterator it;
	BlackCard* blc = NULL;
	Holding* hld;
	int ans;
	for (it = players.begin(); it != players.end(); it++) {
		ans = -1;
		while (ans != 0) {
			//the cards are revealed already from starting phase
			cout << "PLAYER: " << (*it)->get_name() << endl;
			(*it)->get_property()->print_revealed_provinces();
			cout << "Choose which black card to buy. Enter 0 to end this phase" << endl;
			cin >> ans;
			if (ans == 0) continue;  //go to the next player
			blc = (*it)->get_property()->BuyDynastyCard(ans, (*it)->get_army(), (*it)->get_holdings(), (*it)->get_money());
			if (blc != NULL) {   //a black card was bought
				(*it)->get_property()->drawDynastyCard((*it)->get_deck(), 0);  //replace the card, new card not revealed
				if (blc->getType() == HOLDING) { //check if a connection is possible
					hld = (Holding*)(blc);
					//(*it)->create_chain(hld, (*it)->get_holdings(), hld->get_harvest());
					hld->set_chain((*it)->get_holdings()/*, hld->get_harvest()*/);
				}
			}
		}
	}
}

void Gameboard::final_phase() {

	this->discardSurplusFateCards();  //throw away additial cards
	vector<player*>::iterator it;
	list<Holding*>* blc;
	list<Holding*>::iterator it2;
	for (it = players.begin(); it != players.end(); it++) {
		blc = (*it)->get_holdings();
		cout << "PLAYER: " << (*it)->get_name() << endl;
		(*it)->get_property()->printHand();
		cout << "PLAYER: " << (*it)->get_name() << endl;
		(*it)->get_property()->printProvinces();
		for (it2 = blc->begin(); it2 != blc->end(); it2++) {  //add the money from the holdings
			if ((!(*it2)->getistapped()) && (*it2)->getType() == HOLDING) {
				(*it)->get_money() += (*it2)->get_Harvest();
			}
		}
		cout << "PLAYER: " << (*it)->get_name() << endl;
		(*it)->Print_Holdings();
		cout << "PLAYER: " << (*it)->get_name() << endl;
		(*it)->Print_Arena();
	}
	cout << endl;
	this->print_Game_Statistics();
}

void Gameboard::discardSurplusFateCards() {
	vector<player*>::iterator it;
	for (it = players.begin(); it != players.end(); it++) {
		list<GreenCard*>* hand = (*it)->get_property()->get_hand();
		if (hand->size() > 6) {  //more than 6 green cards on hand
			int i;
			(*it)->get_property()->printHand();
			cout << "PLAYER: " << (*it)->get_name() << endl;
			cout << "Choose which card to abandon" << endl;
			cin >> i;
			list<GreenCard*>::iterator it2 = hand->begin();
			for (int k = 1; k < i; k++)
				it2++;
			GreenCard* gr = *it2;
			delete gr;
			hand->remove(*it2);  //being removed from hand and from gameboard
		}
	}
}

void Gameboard::print_Game_Statistics() {
	vector<player*>::iterator it;
	list<Personality*>* prs;
	list<Personality*>::iterator it1;
	int att = 0, def = 0;

	for (it = players.begin(); it != players.end(); it++) {
		int i = 0;
		prs = (*it)->get_army();
		if (prs->empty()) {
			cout << "PLAYER: " << (*it)->get_name() << endl;
			cout << "No army" << endl;
		}
		else {
			int att = 0, def = 0;
			cout << "PLAYER: " << (*it)->get_name() << endl;
			cout << "GAME STATISTICS: " << endl;
			for (it1 = prs->begin(); it1 != prs->end(); it1++) {
				att += (*it1)->get_attpower();
				def += (*it1)->get_defpower();
			}
			cout << "Total attack:  " << att << endl;
			cout << "Total defense:  " << def << endl;
		}
		cout << "Money:  " << (*it)->get_money() << endl << endl;
	}
}