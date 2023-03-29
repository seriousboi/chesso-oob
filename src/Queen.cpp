#include "Queen.h"



Queen::Queen(bool isDark): Piece(isDark,"queen"){}



bool Queen::isMoveValid(Square const & start,Square const & end,bool blackTurn,Board const * board) const
{
  return true;
}
