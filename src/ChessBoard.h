#ifndef chessBoardFile
#define chessBoardFile
#include "Piece.h"
#include "Board.h"
#include <string>
#include <vector>
#include <stack>
using namespace std;

class ChessMove; //pour éviter des inclusions cycliques



class ChessBoard: public Board
{
private:
  vector<Piece *> initalPieces;
  stack<Piece *> createdPieces;
  stack<ChessMove> movesPlayed;

  bool isCheckMate;
  bool isStaleMate;

  bool whiteHasShortCastlingRights;
  bool whiteHasLongCastlingRights;
  bool blackHasShortCastlingRights;
  bool blackHasLongCastlingRights;

  bool hasEnPassantTarget;
  Square enPassantTarget;

protected:
  void move(Square const & start,Square const & end);

public:
  ChessBoard();
  ~ChessBoard();

  void init();
  void deallocPieces();
  void play(Square const & start,Square const & end) override;
  void undoLastMove();

  void loadFen(string const & fen);
  void loadFile(string const & fileName);
  string toString() const;
  string toFen() const;

  bool isSquareTargeted(Square const & target,bool targetIsBlack) const;
  bool isKingInCheck(bool targetIsBlack) const;
  bool isKingCheckMated(bool targetIsBlack); //pas const car on modifie le plateau popur faire des tests
  bool isStaleMated(bool targetIsBlack);
  bool hasLegalMoves(bool targetIsBlack);

  bool getWhiteHasShortCastlingRights() const;
  bool getWhiteHasLongCastlingRights() const;
  bool getBlackHasShortCastlingRights() const;
  bool getBlackHasLongCastlingRights() const;

  bool getIsCheckMate() const;

  friend class ChessGame;
  friend class ChessMove;
};

#endif
