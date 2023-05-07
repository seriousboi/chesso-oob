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
  bool blackTurn;

public:
  int getWidth() const;
  int getHeight() const;
  bool getTurn() const;
  void setTurn(bool isBlackTurn);
  virtual void init() = 0;
  bool isInBounds(Square const & square) const;
  Piece * getPiece(Square const & square) const;
  virtual void play(Square const & start,Square const & end);

protected:
  Board(int length,int depth);
  void add(Piece * piece,Square const & square);
  virtual void move(Square const & start,Square const & end);
};

#endif
