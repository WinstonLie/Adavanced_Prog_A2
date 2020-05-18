
#ifndef PLAYGAME_H
#define PLAYGAME_H

#include "Game.h"
#include "SaveLoad.h"

// Starts the game
void startGame(Game* game);

void startGame(Game* game, int startPlayerIndex, bool isInProgress = false);

void nextPlayer(Game* game, int& currentPlayerIndex);

bool moveTiles(Game* game,Player* player, int factory, Types colourType, int patternRow);

void addToBoard(Player* player, int patternRow, int tileAmount, Tile** tiles);

bool updateEndRoundDetails(Game* game, int currentPlayerIndex);

#endif //PLAYGAME_H