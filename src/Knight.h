#ifndef knightFile
#define knightFile
#include "Piece.h"



class Knight: public Piece
{
public:
  Knight(bool isDark);
  ~Knight();
  bool targets(Square const & start,Square const & end,Board const * board) const;
  bool isMoveValid(Square const & start,Square const & end,bool blackTurn,Board const * board) const;
};

#endif
