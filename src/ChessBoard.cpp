#include <iostream>
#include <map>
#include "ChessBoard.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

using namespace std;



ChessBoard::ChessBoard(): Board(8,8)
{
  init();
}



void ChessBoard::init()
{
  /* pieces blanches */
  Queen * queenW = new Queen(false);
  add(queenW,Square(3,0));
  King * kingW = new King(false);
  add(kingW,Square(4,0));
  Bishop * bishopW1 = new Bishop(false);
  add(bishopW1,Square(2,0));
  Bishop * bishopW2 = new Bishop(false);
  add(bishopW2,Square(5,0));
  Knight * knightW1 = new Knight(false);
  add(knightW1,Square(1,0));
  Knight * knightW2 = new Knight(false);
  add(knightW2,Square(6,0));
  Rook * rookW1 = new Rook(false);
  add(rookW1,Square(0,0));
  Rook * rookW2 = new Rook(false);
  add(rookW2,Square(7,0));

  for(int column=0;column<width;++column)
  {
    Pawn * pawnW = new Pawn(false);
    add(pawnW,Square(column,1));
  }

  /*pieces noires */
  Queen * queenB = new Queen(true);
  add(queenB,Square(3,7));
  King * kingB = new King(true);
  add(kingB,Square(4,7));
  Bishop * bishopB1 = new Bishop(true);
  add(bishopB1,Square(2,7));
  Bishop * bishopB2 = new Bishop(true);
  add(bishopB2,Square(5,7));
  Knight * knightB1 = new Knight(true);
  add(knightB1,Square(1,7));
  Knight * knightB2 = new Knight(true);
  add(knightB2,Square(6,7));
  Rook * rookB1 = new Rook(true);
  add(rookB1,Square(0,7));
  Rook * rookB2 = new Rook(true);
  add(rookB2,Square(7,7));

  for(int column=0;column<width;++column)
  {
    Pawn * pawnB = new Pawn(true);
    add(pawnB,Square(column,height-2));
  }
}



string ChessBoard::toString() const
{
  bool usingIcons = true;
  map<string, string> icons;
  icons = {{"pa","\u265F"},{"Pa","\u2659"},{"kn","\u265E"},{"Kn","\u2658"},{"bi","\u265D"},{"Bi","\u2657"},{"ro","\u265C"},{"Ro","\u2656"},{"qu","\u265B"},{"Qu","\u2655"},{"ki","\u265A"},{"Ki","\u2654"},};

  string topLine = "\u250c";
  string middleLine = "\u251c";
  string bottomLine = "\u2514";
  for(int column=0;column<width-1;++column)
  {
    if(usingIcons)
    {
      topLine += "\u2500\u2500\u2500\u252c";
      bottomLine += "\u2500\u2500\u2500\u2534";
      middleLine += "\u2500\u2500\u2500\u253c";
    }
    else
    {
      topLine += "\u2500\u2500\u252c";
      bottomLine += "\u2500\u2500\u2534";
      middleLine += "\u2500\u2500\u253c";
    }
  }
  if(usingIcons)
  {
    topLine += "\u2500\u2500\u2500\u2510\n";
    bottomLine += "\u2500\u2500\u2500\u2518\n";
    middleLine += "\u2500\u2500\u2500\u2524\n";
  }
  else
  {
    topLine += "\u2500\u2500\u2510\n";
    bottomLine += "\u2500\u2500\u2518\n";
    middleLine += "\u2500\u2500\u2524\n";
  }

  string boardStr = topLine;
  for(int y=height-1;y>=0;--y)
  {
    for(int x=0;x<width;++x)
    {
      boardStr += "\u2502";
      Piece * piece = getPiece(Square(x,y));
      if(piece != NULL)
      {
        if(usingIcons)
        {
          boardStr += " "+icons[piece->toString()]+" ";
        }
        else
        {
          boardStr += piece->toString();
        }
      }
      else
      {
        if(usingIcons)
        {
          boardStr += "   ";
        }
        else
        {
          boardStr += "  ";
        }
      }
    }
    boardStr += "\u2502";
    boardStr += "\n";
    if(y != 0)
    {
      boardStr += middleLine;
    }
  }
  boardStr += bottomLine;
  return boardStr;
}



string ChessBoard::toFen() const
{
  string fen = "";
  int emptyCounter = 0;
  for(int line=height-1;line>=0;--line)
  {
    for(int column=0;column<width;++column)
    {
      Piece * piece = getPiece(Square(column,line));
      if(piece != NULL)
      {
        if(emptyCounter > 0)
        {
          fen += to_string(emptyCounter);
          emptyCounter = 0;
        }
        if(piece->getName() == "Knight")
        {
          fen += "N";
        }
        else if(piece->getName() == "knight")
        {
          fen += "n";
        }
        else
        {
          fen += (piece->toString())[0];
        }
      }
      else
      {
        emptyCounter += 1;
      }
    }
    if(emptyCounter > 0)
    {
      fen += to_string(emptyCounter);
      emptyCounter = 0;
    }
    if(line != 0)
    {
      fen += "/";
    }

  }
  return fen;
}
