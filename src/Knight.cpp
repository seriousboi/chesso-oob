#include "Knight.h"



Knight::Knight(bool isDark): Piece(isDark,"knight"){}



bool Knight::isMoveValid(Square const & start,Square const & end,bool blackTurn,Board const * board) const
{
  return true;
}
