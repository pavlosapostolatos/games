#include <iostream>
#include "objects.hpp"


int main() {
    Gameboard game;
    game.initializehands();
    while (!game.checkWinningCondition()) {
        game.starting_phase();
        game.equip_phase();
        game.battle_phase();
        game.economy_phase();
        game.final_phase();
    }
    return 0;
}