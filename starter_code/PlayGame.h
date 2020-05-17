
#ifndef PLAYGAME_H
#define PLAYGAME_H

#include "Game.h"
#include "SaveLoad.h"

// Starts the game
void startGame(Game* game);

void startGame(Game* game, int startPlayer);

void nextPlayer(Game* game, int& currentPlayerIndex);


#endif //PLAYGAME_H