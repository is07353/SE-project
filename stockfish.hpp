#ifndef STOCKFISH_HPP
#define STOCKFISH_HPP

#include <string>

// Sends a UCI position string to Stockfish and returns the best move (e.g., "e2e4")
std::string getBestMoveFromStockfish(const std::string& uciPosition, int depth);
bool getCheckStatusFromStockfish(const std::string& uciPosition);

#endif // STOCKFISH_HPP
