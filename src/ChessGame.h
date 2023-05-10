#ifndef gameFile
#define gameFile
#include "ChessBoard.h"



class ChessGame
{
private:
  bool running;
  bool whiteIsAI;
  bool blackIsAI;

  ChessBoard board;
  bool gameOver;

public:
  ChessGame();
  void run();
  void play();
  void printMenu();
};

#endif
;
