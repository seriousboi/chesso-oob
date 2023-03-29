#ifndef connecticFile
#define connecticFile
#include <string>
#include "ChessBoard.h"
#include "Square.h"



struct Move{
  Square start;
  Square end;
};



Move getAImove(ChessBoard const & board,bool blackTurn,bool whiteHasCastlingRights,bool blackHasCastlingRights,string gameDataPath = "../ChessAI/gameData/");
void writeInput(ChessBoard const & board,bool blackTurn,bool whiteHasCastlingRights,bool blackHasCastlingRights,string gameDataPath);
Move getOutput(string gameDataPath);

#endif
