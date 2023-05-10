#include "Queen.h"



Queen::Queen(bool isDark): Piece(isDark,"queen"){}

Queen::~Queen(){}



bool Queen::targets(Square const & start,Square const & end,Board const * board) const
{
  int Xvar = end.getX() - start.getX();
  int Yvar = end.getY() - start.getY();
  int absXvar = abs(Xvar);
  int absYvar = abs(Yvar);

  //ne soit pas être sur la même case
  if(Xvar == 0 and Yvar == 0)
  {
    return false;
  }

  int nbSteps;
  //même colonne
  if(Xvar*Yvar == 0)
  {
    nbSteps = absXvar + absYvar;
  }
  //même diagonale
  else if(absXvar == absYvar)
  {
    nbSteps = absXvar;
  }
  else
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

  for(int step=1;step<nbSteps;++step)
  {
    if(board->getPiece(Square(start,step*Xdirection,step*Ydirection)) != NULL)
    {
      return false;
    }
  }

  return true;
}




bool Queen::isMoveValid(Square const & start,Square const & end,bool blackTurn,Board const * board) const
{
  return targets(start,end,board);
}
