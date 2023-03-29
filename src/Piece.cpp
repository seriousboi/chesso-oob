#include <string.h>
#include <cctype>
#include "Piece.h"



Piece::Piece(bool isDark,string const & noun)
{
  isBlack = isDark;
  name = noun;
  if(not isBlack)
  {
    name[0] = toupper(name[0]);
  }
}

bool Piece::getIsBlack() const{return isBlack;}

string Piece::getName() const{return name;}



string Piece::toString() const
{
  return name.substr(0,2);
}
