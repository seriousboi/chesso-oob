#ifndef kingFile
#define kingFile
#include "Piece.h"



class King: public Piece
{
public:
  King(bool isDark);
  ~King();
  bool targets(Square const & start,Square const & end,Board const * board) const;
  bool isMoveValid(Square const & start,Square const & end,bool blackTurn,Board const * board) const;
};

#endif
