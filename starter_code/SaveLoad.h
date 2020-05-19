#ifndef SAVELOAD_H
#define SAVELOAD_H

#include "Game.h"
#include <stdexcept>

bool saveGame(Game* game, int currentPlayer, std::string filePath);

bool loadGame(Game** game, std::string filePath, int& currentPlayerIndex, bool& isInProgress);

void readTiles(bool& validLoad, std::vector<std::string>& inputLines, 
  int& currentLineCounter, std::vector<Tile*>& tiles);

bool checkLoad(bool& validLoad, std::vector<std::string>& inputLines, int currentLineCounter);

// Reads the string inputted, sets integer to first parameter if valid and sets second boolean
// false if 
// void readInt()
#endif //SAVELOAD_H
