#ifndef boardFile
#define boardFile
#include "Piece.h"
#include "Square.h"
#include <string>
#include <vector>
using namespace std;



class Piece;

class Board
{
protected:
  int width;
  int height;
  vector<vector<Piece *> > pieces;

public:
  int getWidth() const;
  int getHeight() const;
  virtual void init() = 0;
  bool isInBounds(Square const & square) const;
  Piece * getPiece(Square const & square) const;
  void play(Square const & start,Square const & end,bool blackTurn);

protected:
  Board(int length,int depth);
  void add(Piece * piece,Square const & square);
  void move(Square const & start,Square const & end);

  friend class ChessGame;
};

#endif
