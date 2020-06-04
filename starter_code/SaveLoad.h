#ifndef SAVELOAD_H
#define SAVELOAD_H

#include "Game.h"
#include <stdexcept>

// Saves the game to the specified file path
// Returns true if saving was successful, else false
bool saveGame(Game* game, int currentPlayer, std::string filePath, bool gameInProgress);

// Loads the game from the specified file path
// If no file is found or save file doesn't match format, then return false
// else true
bool loadGame(Game** game, std::string filePath, int& currentPlayerIndex, bool& isInProgress);

// For use in loadGame
// Reads in tiles from the inputted line until a $ character is reached
// Sets validLoad to false if unexpected characters were encountered
void readTiles(bool& validLoad, std::vector<std::string>& inputLines, 
  int& currentLineCounter, std::vector<Tile*>& tiles);

// Checks to see if valid load is true and that the current index in within
// the bounds of the inputLines array. If not true, then set validLoad to false
// and return false
bool checkLoad(bool& validLoad, std::vector<std::string>& inputLines, int currentLineCounter);

#endif //SAVELOAD_H
