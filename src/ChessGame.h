#ifndef gameFile
#define gameFile
#include "ChessBoard.h"



class ChessGame
{
private:
  ChessBoard board;
  bool blackTurn;
  bool whiteHasCastlingRights;
  bool blackHasCastlingRights;
  bool gameOver;

public:
  ChessGame();
  void play();
  void printHelp() const;
};

#endif
