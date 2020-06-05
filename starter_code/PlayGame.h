
#ifndef PLAYGAME_H
#define PLAYGAME_H

#include "Game.h"
#include "SaveLoad.h"
#include <stdexcept>

// Starts the game
// if fromLoadedGame == true, then factories will be re-generated
void startGame(Game* game, int startPlayerIndex = 0, bool fromLoadedGame = false, bool isInProgress = true, bool replayMode = false);

// Sets currentPlayerIndex to the next player, going up in index before going back to start
// eg 0, 1, 0 etc
void nextPlayer(Game* game, int& currentPlayerIndex);

// Moves the tiles from the inputted factory row into the inputted pattern
// row of player. If input is invalid, then no moving will take place.
// Returns true if tiles were moved, else false.
bool moveTiles(Game* game,Player* player, int factory, Types colourType, int patternRow);

// Adds the tiles into the players board, then deletes the tiles array
// Assumes pattern row being inserted into is valid (1-6)
void addToBoard(Player* player, int patternRow, int tileAmount, Tile**& tiles, Game* game);

// Adds the tiles to wall for all players, and displays points earned from
// those placements. Also sets current player index to whoever had the first
// player marker in their floor line.
// Returns true if end of game has been reached (completed row), else false
bool updateEndRoundDetails(Game* game, int& currentPlayerIndex);

// Displays the commands that the user used
void getCommands(std::vector<std::string> commands);

// Adds the end of game points for each player (from completed rows,columns
// and colour sets), and ranks all players by how many points they scored.
void updateEndGameDetails(Game* game);

// Processes the input into the different parameters expected for a turn
// If types of input inserted match input, then return true, else false
bool processTurn(std::string line, std::size_t currentIndex, int& factory, Types& colourType, int& patternRow);

// Returns the next word in the line, starting from the current index.
std::string getNextWord(std::string line, std::size_t& currentIndex, bool toUpper = true);

void colorizeOutput(std::string output);

#endif //PLAYGAME_H