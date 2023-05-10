#include "Knight.h"



Knight::Knight(bool isDark): Piece(isDark,"knight"){}

Knight::~Knight(){}



bool Knight::targets(Square const & start,Square const & end,Board const * board) const
{
  int absXvar = abs(end.getX() - start.getX());
  int absYvar = abs(end.getY() - start.getY());

  //le cavalier ne peut pas se faire obstruer par une autre piece, le paramètre board n'est donc pas pris en compte
  if((((absXvar == 2) or (absXvar == 1)) and ((absYvar == 2) or (absYvar == 1))) and (absXvar != absYvar))
  {
    return true;
  }
  else
  {
    return false;
  }
}




bool Knight::isMoveValid(Square const & start,Square const & end,bool blackTurn,Board const * board) const
{
  return targets(start,end,board);
}
