#include "Rook.h"



Rook::Rook(bool isDark): Piece(isDark,"rook"){}

Rook::~Rook(){}



bool Rook::targets(Square const & start,Square const & end,Board const * board) const
{
  int Xvar = end.getX() - start.getX();
  int Yvar = end.getY() - start.getY();

  // doit être soit sur la même colonne soit sur la même ligne
  if((Xvar*Yvar != 0) or ((Xvar == 0) and (Yvar==0)))
  {
    return false;
  }

  int Xdirection;
  if(Xvar > 0){Xdirection=1;}
  else if(Xvar < 0){Xdirection=-1;}
  else{Xdirection=0;}

  int Ydirection;
  if(Yvar > 0){Ydirection=1;}
  else if(Yvar < 0){Ydirection=-1;}
  else{Ydirection=0;}

  for(int step=1;step<abs(Xvar+Yvar);++step)
  {
    if(board->getPiece(Square(start,step*Xdirection,step*Ydirection)) != NULL)
    {
      return false;
    }
  }

  return true;
}




bool Rook::isMoveValid(Square const & start,Square const & end,bool blackTurn,Board const * board) const
{
  return targets(start,end,board);
}
