#include "Pawn.h"



Pawn::Pawn(bool isDark): Piece(isDark,"pawn"){}



bool Pawn::isMoveValid(Square const & start,Square const & end,bool blackTurn,Board const * board) const
{

  return true;
}
