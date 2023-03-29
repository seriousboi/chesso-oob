#ifndef chessBoardFile
#define chessBoardFile
#include "Board.h"
#include <string>
using namespace std;



class ChessBoard: public Board
{
public:
  ChessBoard();

  void init();
  string toString() const;
  string toFen() const;
};

#endif
