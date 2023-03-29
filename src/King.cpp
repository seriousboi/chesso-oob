#include "King.h"



King::King(bool isDark): Piece(isDark,"king"){}



bool King::isMoveValid(Square const & start,Square const & end,bool blackTurn,Board const * board) const
{
  return true;
}
