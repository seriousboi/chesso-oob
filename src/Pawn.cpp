#include "Pawn.h"
#include <cstdlib>



Pawn::Pawn(bool isDark): Piece(isDark,"pawn"){}



bool Pawn::targets(Square const & start,Square const & end,Board const * board) const
{
  int Yvar;
  if(getIsBlack())
  {
    Yvar = -1;
  }
  else
  {
    Yvar = 1;
  }

  if((start.getX()+1 == end.getX() or start.getX()-1 == end.getX())
  and start.getY()+Yvar == end.getY())
  {
    return true;
  }
  else
  {
    return false;
  }
}



bool Pawn::isMoveValid(Square const & start,Square const & end,bool blackTurn,Board const * board) const
{
  //sens de déplacement du pion en fonction de sa couleur
  int Yvar;
  if(getIsBlack())
  {
    Yvar = -1;
  }
  else
  {
    Yvar = 1;
  }

  //avance d'une case, il faut que la case devant soit vide
  if((start.getX() == end.getX())
  and (start.getY()+Yvar == end.getY())
  and (board->getPiece(end) == NULL))
  {
    return true;
  }
  //avance de deux cases, les deux doivent être vides et le pion doit être sur sa rangée de départ
  else if((start.getX() == end.getX())
  and (start.getY()+2*Yvar == end.getY())
  and (board->getPiece(end) == NULL)
  and (board->getPiece(Square(start,0,Yvar)) == NULL)
  and ( (getIsBlack() and (start.getY() == 6)) or ((not getIsBlack()) and (start.getY() == 1)) ))
  {
    return true;
  }
  //capture, il doit y avoir une piece adverse sur la case ciblée
  else if(targets(start,end,board) and (board->getPiece(end) != NULL) and (board->getPiece(end)->getIsBlack() != blackTurn))
  {
    return true;
  }
  else
  {
    return false;
  }
}
