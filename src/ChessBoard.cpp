#include <iostream>
#include <map>
#include <cctype>
#include <fstream>
#include "ChessBoard.h"
#include "ChessMove.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

using namespace std;



void ChessBoard::move(Square const & start,Square const & end)
{
  Board::move(start,end);
}



ChessBoard::ChessBoard(): Board(8,8)
{
  init();
}



ChessBoard::~ChessBoard()
{
  deallocPieces();
}



void ChessBoard::init()
{
  // on désalloue l'es pieces de l'ancien plateau car on peut appeller init() pour recommancer une partie
  deallocPieces();

  /* variables de partie */
  isCheckMate = false;
  isStaleMate = false;
  whiteHasShortCastlingRights = true;
  whiteHasLongCastlingRights = true;
  blackHasShortCastlingRights = true;
  blackHasLongCastlingRights = true;
  hasEnPassantTarget = false;

  initalPieces = vector<Piece *>(32);

  /* pieces blanches */
  Queen * queenW = new Queen(false);
  add(queenW,Square(3,0));
  initalPieces[0] = queenW;
  King * kingW = new King(false);
  add(kingW,Square(4,0));
  initalPieces[1] = kingW;
  Bishop * bishopW1 = new Bishop(false);
  add(bishopW1,Square(2,0));
  initalPieces[2] = bishopW1;
  Bishop * bishopW2 = new Bishop(false);
  add(bishopW2,Square(5,0));
  initalPieces[3] = bishopW2;
  Knight * knightW1 = new Knight(false);
  add(knightW1,Square(1,0));
  initalPieces[4] = knightW1;
  Knight * knightW2 = new Knight(false);
  add(knightW2,Square(6,0));
  initalPieces[5] = knightW2;
  Rook * rookW1 = new Rook(false);
  add(rookW1,Square(0,0));
  initalPieces[6] = rookW1;
  Rook * rookW2 = new Rook(false);
  add(rookW2,Square(7,0));
  initalPieces[7] = rookW2;

  for(int column=0;column<width;++column)
  {
    Pawn * pawnW = new Pawn(false);
    add(pawnW,Square(column,1));
    initalPieces[8+column] = pawnW;
  }

  /*pieces noires */
  Queen * queenB = new Queen(true);
  add(queenB,Square(3,7));
  initalPieces[16] = queenB;
  King * kingB = new King(true);
  add(kingB,Square(4,7));
  initalPieces[17] = kingB;
  Bishop * bishopB1 = new Bishop(true);
  add(bishopB1,Square(2,7));
  initalPieces[18] = bishopB1;
  Bishop * bishopB2 = new Bishop(true);
  add(bishopB2,Square(5,7));
  initalPieces[19] = bishopB2;
  Knight * knightB1 = new Knight(true);
  add(knightB1,Square(1,7));
  initalPieces[20] = knightB1;
  Knight * knightB2 = new Knight(true);
  add(knightB2,Square(6,7));
  initalPieces[21] = knightB2;
  Rook * rookB1 = new Rook(true);
  add(rookB1,Square(0,7));
  initalPieces[22] = rookB1;
  Rook * rookB2 = new Rook(true);
  add(rookB2,Square(7,7));
  initalPieces[23] = rookB2;

  for(int column=0;column<width;++column)
  {
    Pawn * pawnB = new Pawn(true);
    add(pawnB,Square(column,height-2));
    initalPieces[24+column] = pawnB;
  }
}



void ChessBoard::deallocPieces()
{
  for(Piece * piece:initalPieces) //dealloc les piceces initiales
  {
    delete piece;
  }
  initalPieces.clear(); //supprime les adresses des piceces initiales


  for(int y=0;y<8;++y) //supprime les adresses des piceces initiales dans le plateau
  {
    for(int x=0;x<8;++x)
    {
      pieces[x][y] = NULL;
    }
  }

  while(not createdPieces.empty()) //dealloc les piceces crées par promotion
  {
    delete createdPieces.top();
    createdPieces.pop(); //supprime les adresses des piceces crées par promotion
  }

  movesPlayed = stack<ChessMove>(); //supprime les moves qui contiennent les adresses des pieces dealloc
}



void ChessBoard::play(Square const & start,Square const & end) //override pas clean, faute à l'UML initial
{
  if(isInBounds(start) and isInBounds(end))
  {
    Piece * pieceToMove = getPiece(start);
    if(pieceToMove != NULL and (pieceToMove->getIsBlack() == blackTurn))
    {
      Piece * pieceToSquash = getPiece(end);
      if(pieceToSquash == NULL or (pieceToSquash->getIsBlack() != blackTurn))
      {
        ChessMove chessMove(start,end,this);
        if(pieceToMove->isMoveValid(start,end,blackTurn,this)
        or (chessMove.isMoveSpecial() and chessMove.isCastle() and chessMove.isCastleLegal(this)) ) //seul le roque fait se déplacer les pieces de manière inhabituelle (si on oublie la prise en passant)
        {
          move(start,end);
          movesPlayed.push(chessMove);
          if(chessMove.isMoveSpecial())
          {
            chessMove.applySpecialMove(this);
          }

          if(not isKingInCheck(blackTurn))
          {
            blackTurn = not blackTurn; //passage au tour suivant

            if(isKingInCheck(blackTurn)) //vérifie si on met le roi adverse en échec
            {
              if(isKingCheckMated(blackTurn))
              {
                cout << "CheckMate\n";
                isCheckMate = true;
              }
              else
              {
                cout << "Check\n";
              }
            }
            else if(isStaleMated(blackTurn))
            {
              cout << "Stalemate\n";
              isStaleMate = true;
            }
          }
          else
          {
            chessMove.undoMove(this);
            throw string("Cannot let your king be checked\n");
          }
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



void ChessBoard::undoLastMove()
{
  if(not movesPlayed.empty())
  {
    movesPlayed.top().undoMove(this);
    blackTurn = not blackTurn;
  }
  else
  {
    cout << "No moves to undo\n";
  }
}



bool ChessBoard::isSquareTargeted(Square const & target,bool targetIsBlack) const
{
  for(int x=0;x<8;++x)
  {
    for(int y=0;y<8;++y)
    {
      if((pieces[x][y] != NULL) and (pieces[x][y]->getIsBlack() != targetIsBlack))
      {
        if(pieces[x][y]->targets(Square(x,y),target,this))
        {
          return true;
        }
      }
    }
  }
  return false;
}



bool ChessBoard::isKingInCheck(bool targetIsBlack) const
{
  for(int x=0;x<8;++x)
  {
    for(int y=0;y<8;++y)
    {
      Piece * piece = pieces[x][y];
      if((piece != NULL)
      and (piece->getIsBlack() == targetIsBlack)
      and (piece->getName() == "King" or piece->getName() == "king"))
      {
        Square target(x,y);
        if(isSquareTargeted(target,targetIsBlack))
        {
          return true;
        }
      }
    }
  }
  return false;
}



bool ChessBoard::isKingCheckMated(bool targetIsBlack)
{
  return ( isKingInCheck(targetIsBlack) and (not hasLegalMoves(targetIsBlack)) );
}



bool ChessBoard::isStaleMated(bool targetIsBlack)
{
  return ( (not isKingInCheck(targetIsBlack)) and (not hasLegalMoves(targetIsBlack)) );
}



bool ChessBoard::hasLegalMoves(bool targetIsBlack)
{
  //on cherche les pieces de même couleur
  for(int x=0;x<8;++x)
  {
    for(int y=0;y<8;++y)
    {
      Piece * piece = pieces[x][y];
      if((piece != NULL)  and (piece->getIsBlack() == targetIsBlack))
      {
        Square start(x,y);
        //on cherche les moves valides de la piece
        for(int a=0;a<8;++a)
        {
          for(int b=0;b<8;++b)
          {
            Square end(a,b);
            Piece * pieceToSquash = getPiece(end);
            if( (pieceToSquash == NULL or (pieceToSquash->getIsBlack() != targetIsBlack))
            and piece->isMoveValid(start,end,targetIsBlack,this))
            {
              ChessMove chessMove(start,end,this);
              move(start,end);
              if(chessMove.isMoveSpecial()){chessMove.applySpecialMove(this);}
              movesPlayed.push(chessMove);

              if(not isKingInCheck(targetIsBlack))
              {
                chessMove.undoMove(this);
                return true;
              }
              else
              {
                chessMove.undoMove(this);
              }
            }
          }
        }
      }
    }
  }
  return false;
}



void ChessBoard::loadFen(string const & fen)
{
  deallocPieces();

  blackTurn = false;
  isCheckMate = false;
  isStaleMate = false;
  whiteHasShortCastlingRights = true;
  whiteHasLongCastlingRights = true;
  blackHasShortCastlingRights = true;
  blackHasLongCastlingRights = true;
  hasEnPassantTarget = false;

  int index = 0;
  char symbol;
  int x = 0;
  int y = 7; //notation fen se lit de haut en bas

  while(y > 0 or x < 8) //boucle pour les pieces
  {
    symbol = fen[index];
    //pas propre, améliorable pour des plateaux de taille non conventionelle
    if(symbol == '1' or symbol == '2' or symbol == '3' or symbol == '4' or symbol == '5' or symbol == '6' or symbol == '7' or symbol == '8')
    {
      int space = symbol - '0'; //marche avec tout les compilateur?
      x += space;
    }
    else if(symbol == '/')
    {
      x = 0;
      y--;
    }
    else
    {
      bool symbolIsPiece = false;
      bool blackPiece;
      if(symbol == 'P' or symbol == 'N' or symbol == 'B' or symbol == 'R' or symbol == 'Q' or symbol == 'K')
      {
        symbolIsPiece = true;
        blackPiece = false;
      }
      else if(symbol == 'p' or symbol == 'n' or symbol == 'b' or symbol == 'r' or symbol == 'q' or symbol == 'k')
      {
        symbolIsPiece = true;
        blackPiece = true;
      }

      if(symbolIsPiece)
      {
        symbol = tolower(symbol);
        if(symbol == 'p')
        {
          Pawn * pawn = new Pawn(blackPiece);
          add(pawn,Square(x,y));
          initalPieces.push_back(pawn);
        }
        else if(symbol == 'n')
        {
          Knight * knight = new Knight(blackPiece);
          add(knight,Square(x,y));
          initalPieces.push_back(knight);
        }
        else if(symbol == 'b')
        {
          Bishop * bishop = new Bishop(blackPiece);
          add(bishop,Square(x,y));
          initalPieces.push_back(bishop);
        }
        else if(symbol == 'r')
        {
          Rook * rook = new Rook(blackPiece);
          add(rook,Square(x,y));
          initalPieces.push_back(rook);
        }
        else if(symbol == 'q')
        {
          Queen * queen = new Queen(blackPiece);
          add(queen,Square(x,y));
          initalPieces.push_back(queen);
        }
        else if(symbol == 'k')
        {
          King * king = new King(blackPiece);
          add(king,Square(x,y));
          initalPieces.push_back(king);
        }
      }
      else{cout << "unkown symbol\n";}

      x++;
    }

    index++;
  }

  int length = fen.length();
  index++;
  if(index < length)
  {
    symbol = fen[index];
    if(symbol == 'w'){blackTurn = false;}
    else if(symbol == 'b'){blackTurn = true;}
    else{cout << "unkown symbol\n";}
    index += 2;
  }
  else{return;}

  if(index < length)
  {
    whiteHasShortCastlingRights = false;
    whiteHasLongCastlingRights = false;
    blackHasShortCastlingRights = false;
    blackHasLongCastlingRights = false;

    while(fen[index] != ' ' and index < length)
    {
      symbol = fen[index];
      if(symbol == 'K'){whiteHasShortCastlingRights = true;}
      else if(symbol == 'Q'){whiteHasLongCastlingRights = true;}
      else if(symbol == 'k'){blackHasShortCastlingRights = true;}
      else if(symbol == 'q'){blackHasLongCastlingRights = true;}
      index++;
    }
  }
}



void ChessBoard::loadFile(string const & fileName)
{
  ifstream dataStream(fileName);
  if(!dataStream)
  {
    throw string("oof, cannot open file '" + fileName + "'\n");
  }
  string fen = "";
  string buffer;
  while(not dataStream.eof())
  {
    dataStream >> buffer;
    fen += buffer + " ";
  }
  loadFen(fen);
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
  if(blackTurn)
  {
    fen += " b ";
  }
  else
  {
    fen += " w ";
  }
  if(whiteHasShortCastlingRights or whiteHasLongCastlingRights or blackHasShortCastlingRights or blackHasLongCastlingRights)
  {
    if(whiteHasShortCastlingRights)
    {fen += "K";}
    if(whiteHasLongCastlingRights)
    {fen += "Q";}
    if(blackHasShortCastlingRights)
    {fen += "k";}
    if(blackHasLongCastlingRights)
    {fen += "q";}
  }
  else
  {
    fen += " -";
  }
  if(hasEnPassantTarget)
  {
    fen += " "+enPassantTarget.toString();
  }
  else
  {
    fen += " -";
  }
  return fen;
}



bool ChessBoard::getWhiteHasShortCastlingRights() const
{return whiteHasShortCastlingRights;}

bool ChessBoard::getWhiteHasLongCastlingRights() const
{return whiteHasLongCastlingRights;}

bool ChessBoard::getBlackHasShortCastlingRights() const
{return blackHasShortCastlingRights;}

bool ChessBoard::getBlackHasLongCastlingRights() const
{return blackHasLongCastlingRights;}

bool ChessBoard::getIsCheckMate() const
{
  return isCheckMate;
}
