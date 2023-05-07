#include "King.h"
#include "ChessMove.h"



King::King(bool isDark): Piece(isDark,"king"){}



bool King::targets(Square const & start,Square const & end,Board const * board) const
{
  int Xvar = end.getX() - start.getX();
  int Yvar = end.getY() - start.getY();

  //ne soit pas être sur la même case
  if(Xvar == 0 and Yvar == 0)
  {
    return false;
  }

  if(abs(Xvar) <= 1 and abs(Yvar) <= 1)
  {
    return true;
  }
  else
  {
    return false;
  }
}




bool King::isMoveValid(Square const & start,Square const & end,bool blackTurn,Board const * board) const
{
  return targets(start,end,board);
}
