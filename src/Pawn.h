#ifndef pawnFile
#define pawnFile
#include "Piece.h"



class Pawn: public Piece
{
public:
  Pawn(bool isDark);
  bool isMoveValid(Square const & start,Square const & end,bool blackTurn,Board const * board) const;
};

#endif
