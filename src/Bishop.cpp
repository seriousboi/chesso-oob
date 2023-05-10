#include "Bishop.h"



Bishop::Bishop(bool isDark): Piece(isDark,"bishop"){}

Bishop::~Bishop(){}



bool Bishop::targets(Square const & start,Square const & end,Board const * board) const
{
  int Xvar = end.getX() - start.getX();
  int Yvar = end.getY() - start.getY();
  int absXvar = abs(Xvar);
  int absYvar = abs(Yvar);

  // doit être sur une diagonale et ne pas être sur la même case
  if((not (absXvar == absYvar)) or (Xvar == 0))
  {
    return false;
  }

  int Xdirection;
  if(Xvar > 0){Xdirection=1;}
  else{Xdirection=-1;}

  int Ydirection;
  if(Yvar > 0){Ydirection=1;}
  else{Ydirection=-1;}

  // les cases entre le départ et l'arrivée doivent être vides
  for(int step=1;step<abs(Xvar);++step)
  {
    if(board->getPiece(Square(start,step*Xdirection,step*Ydirection)) != NULL)
    {
      return false;
    }
  }
  return true;
}




bool Bishop::isMoveValid(Square const & start,Square const & end,bool blackTurn,Board const * board) const
{
  return targets(start,end,board);
}
