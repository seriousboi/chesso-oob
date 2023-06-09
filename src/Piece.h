#ifndef pieceFile
#define pieceFile
#include "Square.h"
#include "Board.h"
#include <string>
using namespace std;



class Board;

class Piece
{
private:
  string name;
  bool isBlack;

public:
  Piece(bool isDark,string const & noun);
  virtual ~Piece();

  bool getIsBlack() const;
  string getName() const;

  virtual bool targets(Square const & start,Square const & end,Board const * board)const = 0;
  virtual bool isMoveValid(Square const & start,Square const & end,bool blackTurn,Board const * board) const = 0;
  string toString() const;
};

#endif
