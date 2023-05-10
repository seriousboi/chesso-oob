#ifndef queenFile
#define queenFile
#include "Piece.h"



class Queen: public Piece
{
public:
  Queen(bool isDark);
  ~Queen();
  bool targets(Square const & start,Square const & end,Board const * board) const;
  bool isMoveValid(Square const & start,Square const & end,bool blackTurn,Board const * board) const;
};

#endif
