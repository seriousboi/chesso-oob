#ifndef movefile
#define movefile
using namespace std;
#include <string>
#include "Square.h"
#include "Piece.h"
#include "Board.h"
#include "ChessBoard.h"



class ChessMove
{
private:
  Square start;
  Square end;
  Piece * pieceMoved;

  bool isTake;
  Piece * pieceTaken;

  bool isSpecialMove;
  string specialMoveCode;
  Piece * pieceCreated;

public:
  //le board utilisé est celui avant le move!!
  ChessMove(Square const & startPos,Square const & endPos,Board const * board);

  bool isMoveSpecial() const;
  bool isCastle() const;
  bool isPromotion() const;
  bool isCastleLegal(ChessBoard const * board) const;

  void applySpecialMove(ChessBoard * board);
  void applyCastle(ChessBoard * board);
  void applyPromotion(ChessBoard * board);

  void undoMove(ChessBoard * board);
  void undoSpecialMove(ChessBoard * board);
  void undoCastle(ChessBoard * board);
  void undoPromotion(ChessBoard * board);
};

#endif
