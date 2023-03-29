#ifndef bishopFile
#define bishopFile
#include "Piece.h"



class Bishop: public Piece
{
public:
  Bishop(bool isDark);
  bool isMoveValid(Square const & start,Square const & end,bool blackTurn,Board const * board) const;
};

#endif
