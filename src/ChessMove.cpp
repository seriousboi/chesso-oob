using namespace std;
#include <iostream>
#include "Queen.h"
#include "ChessMove.h"



ChessMove::ChessMove(Square const & startPos,Square const & endPos,Board const * board)
{
  start = startPos;
  end = endPos;
  pieceMoved = board->getPiece(start);

  if(pieceMoved == NULL)
  {
    throw string("No playable piece in start square\n");
  }

  pieceTaken = board->getPiece(end);
  isTake = (pieceTaken != NULL);


  string pieceName = pieceMoved->getName();
  int xStart = start.getX();
  int yStart = start.getY();
  int xEnd = end.getX();
  int yEnd = end.getY();

  if((pieceName == "Pawn" or pieceName == "pawn") and (yEnd == 0 or yEnd == 7))
  {
    isSpecialMove = true;
    specialMoveCode = "promotion";
  }
  else if((pieceName == "King" or pieceName == "king") and xStart == 4 and yStart == yEnd)
  {
    if(xEnd == 2)
    {
      if(yStart == 0)
      {
        isSpecialMove = true;
        specialMoveCode = "castle long white";
      }
      else if(yStart == 7)
      {
        isSpecialMove = true;
        specialMoveCode = "castle long black";
      }
    }
    else if(xEnd == 6)
    {
      if(yStart == 0)
      {
        isSpecialMove = true;
        specialMoveCode = "castle short white";
      }
      else if(yStart == 7)
      {
        isSpecialMove = true;
        specialMoveCode = "castle short black";
      }
    }
  }
  else
  {
    isSpecialMove = false;
  }
  //Piece * pieceCreated;
}



bool ChessMove::isMoveSpecial() const
{return isSpecialMove;}



bool ChessMove::isCastle() const
{
  if(specialMoveCode == "castle long white"
  or specialMoveCode == "castle long black"
  or specialMoveCode == "castle short white"
  or specialMoveCode == "castle short black")
  {
    return true;
  }
  else
  {
    return false;
  }
}



bool ChessMove::isPromotion() const
{
  return specialMoveCode == "promotion";
}




bool ChessMove::isCastleLegal(ChessBoard const * board) const
{ // rajouter le check de certaines cases!!
  bool targetIsBlack = true;
  bool targetIsWhite = not targetIsBlack;

  if(specialMoveCode == "castle long white"
  and board->getWhiteHasLongCastlingRights()
  and (not board->isKingInCheck(targetIsWhite))
  and (not board->isSquareTargeted(Square(3,0),targetIsWhite))
  and (not board->isSquareTargeted(Square(2,0),targetIsWhite)))
  {
    return true;
  }
  else if(specialMoveCode == "castle long black"
  and board->getBlackHasLongCastlingRights()
  and (not board->isKingInCheck(targetIsBlack))
  and (not board->isSquareTargeted(Square(3,7),targetIsBlack))
  and (not board->isSquareTargeted(Square(2,7),targetIsBlack)))
  {
    return true;
  }
  else if(specialMoveCode == "castle short white"
  and board->getWhiteHasShortCastlingRights()
  and (not board->isKingInCheck(targetIsWhite))
  and (not board->isSquareTargeted(Square(5,0),targetIsWhite))
  and (not board->isSquareTargeted(Square(6,0),targetIsWhite)))
  {
    return true;
  }
  else if(specialMoveCode == "castle short black"
  and board->getBlackHasShortCastlingRights()
  and (not board->isKingInCheck(targetIsBlack))
  and (not board->isSquareTargeted(Square(5,7),targetIsBlack))
  and (not board->isSquareTargeted(Square(6,7),targetIsBlack)))
  {
    return true;
  }
  else
  {
    return false;
  }
}



void ChessMove::applySpecialMove(ChessBoard * board)
{
  if(isCastle())
  {
    applyCastle(board);
  }
  else if(isPromotion())
  {
    applyPromotion(board);
  }
}



void ChessMove::applyCastle(ChessBoard * board)
{
  Square rookStart;
  Square rookEnd;
  if(specialMoveCode == "castle long white")
  {
    rookStart = Square(0,0);
    rookEnd = Square(3,0);
  }
  else if(specialMoveCode == "castle long black")
  {
    rookStart = Square(0,7);
    rookEnd = Square(3,7);
  }
  else if(specialMoveCode == "castle short white")
  {
    rookStart = Square(7,0);
    rookEnd = Square(5,0);
  }
  else if(specialMoveCode == "castle short black")
  {
    rookStart = Square(7,7);
    rookEnd = Square(5,7);
  }

  Piece * rook = board->getPiece(rookStart);
  if(rook == NULL){cout << "found an empty square in " << rookStart.toString() << " where rook should be when castling\n";return;}
  board->move(rookStart,rookEnd);
}



void ChessMove::applyPromotion(ChessBoard * board)
{
  Queen * promQueen = new Queen(pieceMoved->getIsBlack());
  pieceCreated = promQueen;
  board->add(promQueen,end);
  board->createdPieces.push(promQueen);
}



void ChessMove::undoMove(ChessBoard * board)
{
  if(not isSpecialMove)
  {
    board->move(end,start);
    if(isTake)
    {
      board->add(pieceTaken,end);
    }
  }
  else
  {
    undoSpecialMove(board);
  }
  board->movesPlayed.pop();
}



void ChessMove::undoSpecialMove(ChessBoard * board)
{
  if(isCastle())
  {
    undoCastle(board);
  }
  else if(isPromotion())
  {
    undoPromotion(board);
  }
}



void ChessMove::undoCastle(ChessBoard * board)
{
  board->move(end,start); //on remet le roi en place

  Square rookStart;
  Square rookEnd;
  if(specialMoveCode == "castle long white")
  {
    rookStart = Square(0,0);
    rookEnd = Square(3,0);
  }
  else if(specialMoveCode == "castle long black")
  {
    rookStart = Square(0,7);
    rookEnd = Square(3,7);
  }
  else if(specialMoveCode == "castle short white")
  {
    rookStart = Square(7,0);
    rookEnd = Square(5,0);
  }
  else if(specialMoveCode == "castle short black")
  {
    rookStart = Square(7,7);
    rookEnd = Square(5,7);
  }

  board->move(end,start); //on remet la tour en place
}



void ChessMove::undoPromotion(ChessBoard * board)
{
  delete board->createdPieces.top(); //dealloc la piece promue
  board->createdPieces.pop(); //supprime l'adresse de la piece supprimée
  //on sait qu'on revient toujours sur la promotion la plus récente, donc l'adresse du dessus de la pile est la bonne

  if(isTake)
  {
    board->add(pieceTaken,end);
  }
  else
  {
    board->add(NULL,end);
  }

  board->add(pieceMoved,start);
}
