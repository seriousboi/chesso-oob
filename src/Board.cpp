#include <string>
#include "Board.h"
#include <iostream>



Board::Board(int length,int depth)
{
  width = length;
  height = depth;
  pieces = vector<vector<Piece *>>(width,vector<Piece *>(height));
  blackTurn = false;
}



int Board::getWidth() const
{return width;}

int Board::getHeight() const
{return height;}

bool Board::getTurn() const
{return blackTurn;}

void Board::setTurn(bool isBlackTurn)
{blackTurn = isBlackTurn;}



bool Board::isInBounds(Square const & square) const
{
  return (square.getX() >= 0 and square.getX() < width and square.getY() >= 0 and square.getY() < height);
}



Piece * Board::getPiece(Square const & square) const
{
  if(isInBounds(square))
  {
    return pieces[square.getX()][square.getY()];
  }
  else
  {
    return NULL;
  }
}



void Board::play(Square const & start,Square const & end)
{
  if(isInBounds(start) and isInBounds(end))
  {
    Piece * pieceToMove = getPiece(start);
    if(pieceToMove != NULL and (pieceToMove->getIsBlack() == blackTurn))
    {
      Piece * pieceToSquash = getPiece(end);
      if(pieceToSquash == NULL or (pieceToSquash->getIsBlack() != blackTurn))
      {
        if(pieceToMove->isMoveValid(start,end,blackTurn,this))
        {
          move(start,end);
          blackTurn = not blackTurn;
        }
        else
        {
          throw string(pieceToMove->getName()+" cannot move here\n");
        }
      }
      else
      {
        throw string("Cannot move onto your own pieces\n");
      }
    }
    else
    {
      throw string("No playable piece in start square\n");
    }
  }
  else
  {
    throw string("Move out of bounds\n");
  }
}



void Board::add(Piece * piece,Square const & square)
{
  if(isInBounds(square))
  {
    pieces[square.getX()][square.getY()] = piece;
  }
}



void Board::move(Square const & start,Square const & end)
{
  Piece * piece = getPiece(start);
  add(NULL,start);
  add(piece,end);
}
