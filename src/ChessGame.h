#ifndef gameFile
#define gameFile
#include "ChessBoard.h"



class ChessGame
{
private:
  ChessBoard board;
  bool gameOver;

public:
  ChessGame();
  void play();
  void printHelp() const;
};

#endif
