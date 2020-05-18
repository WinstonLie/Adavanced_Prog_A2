#ifndef SAVELOAD_H
#define SAVELOAD_H

#include "Game.h"

bool saveGame(Game* game, int currentPlayer, std::string filePath);

bool loadGame(Game** game, std::string filePath, int& currentPlayerIndex);

void readTiles(bool& validLoad, std::vector<std::string>& inputLines, 
  int& currentLineCounter, std::vector<Tile*>& tiles);

bool checkLoad(bool& validLoad, std::vector<std::string>& inputLines, int currentLineCounter);

#endif //SAVELOAD_H