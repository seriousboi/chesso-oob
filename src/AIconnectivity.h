#ifndef connecticFile
#define connecticFile
#include <string>
#include "ChessBoard.h"
#include "Square.h"



struct Move{
  Square start;
  Square end;
};



Move getAImove(ChessBoard const & board,string gameDataPath = "../ChessAI/gameData/");
void writeInput(ChessBoard const & board,string gameDataPath);
Move getOutput(string gameDataPath);

#endif
