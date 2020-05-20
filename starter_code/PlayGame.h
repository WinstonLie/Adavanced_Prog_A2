
#ifndef PLAYGAME_H
#define PLAYGAME_H

#include "Game.h"
#include "SaveLoad.h"
#include <stdexcept>

// Starts the game
void startGame(Game* game);

void startGame(Game* game, int startPlayerIndex, bool fromLoadedGame = false);

void nextPlayer(Game* game, int& currentPlayerIndex);

bool moveTiles(Game* game,Player* player, int factory, Types colourType, int patternRow);

// Adds the tiles into the players board, then deletes the tiles array
// Assumes pattern row being inserted into is valid (1-6)
void addToBoard(Player* player, int patternRow, int tileAmount, Tile**& tiles);

bool updateEndRoundDetails(Game* game, int& currentPlayerIndex);

void getCommands(std::vector<std::string> commands);

void updateEndGameDetails(Game* game);

// Processes the line into the differ
bool processLine(std::string line, std::size_t charAfterFirstWordIndex, int& factory, Types& colourType, int& patternRow);

std::string getNextWord(std::string line, std::size_t& currentIndex, bool toUpper = true);

#endif //PLAYGAME_H