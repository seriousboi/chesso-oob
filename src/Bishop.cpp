#include "Bishop.h"



Bishop::Bishop(bool isDark): Piece(isDark,"bishop"){}



bool Bishop::isMoveValid(Square const & start,Square const & end,bool blackTurn,Board const * board) const
{
  return true;
}
