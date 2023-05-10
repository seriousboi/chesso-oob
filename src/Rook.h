#ifndef rookFile
#define rookFile
#include "Piece.h"



class Rook: public Piece
{
public:
  Rook(bool isDark);
  ~Rook();
  bool targets(Square const & start,Square const & end,Board const * board) const;
  bool isMoveValid(Square const & start,Square const & end,bool blackTurn,Board const * board) const;
};

#endif
