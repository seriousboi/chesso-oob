#ifndef bishopFile
#define bishopFile
#include "Piece.h"



class Bishop: public Piece
{
public:
  Bishop(bool isDark);
  ~Bishop();
  bool targets(Square const & start,Square const & end,Board const * board) const;
  bool isMoveValid(Square const & start,Square const & end,bool blackTurn,Board const * board) const;
};

#endif
