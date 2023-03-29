#include "Rook.h"



Rook::Rook(bool isDark): Piece(isDark,"rook"){}



bool Rook::isMoveValid(Square const & start,Square const & end,bool blackTurn,Board const * board) const
{
  return true;
}
