#include <iostream>
#include <string>
#include "Square.h"
#include "Board.h"
#include "Piece.h"
#include "ChessBoard.h"
#include "Rook.h"
#include "ChessGame.h"
using namespace std;



int main() {
  //ChessBoard board;
  //board.loadFen("r3k2r/ppp2ppp/5bb1/8/8/1BB5/PPP2PPP/R3K2R b");
  //cout << board.toString();
  ChessGame game;
  game.play();
  return 0;
}
