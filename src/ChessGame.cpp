#include <iostream>
#include <string>
#include "ChessGame.h"
#include "AIconnectivity.h"
#include "ChessMove.h"
using namespace std;



ChessGame::ChessGame()
{
  board.init();
  gameOver = false;
}



void ChessGame::play()
{
  bool whiteIsAI = false;
  bool blackIsAI = true;

  //board.loadFile("../data/castle.txt");
  //board.loadFile("../data/prom.txt");
  //board.loadFile("../data/bug.txt");
  //board.loadFile("../data/checkmate.txt");
  //board.loadFile("../data/whereking.txt");
  //board.loadFen("8/8/6k1/5pB1/5K2/5N2/5nPP/4RB1R w KQkq");
  //board.loadFen("8/1b13p1/pN3k2/3Ppp2/2P5/3K2P1/8/5R2 w");
  //board.loadFen("8/2P2kp1/3B1p2/1p3r2/8/P6p/8/3KR3 b");
  //board.loadFen("k7/6R1/8/3K4/8/8/1R6/8 w");

  printHelp();
  while(not gameOver)
  {
    bool moveInputted;
    bool moveMade = false;
    string startInput;
    string endInput;
    Square start;
    Square end;

    while(not moveMade)
    {
      cout << board.toFen() << endl;
      cout << board.toString();

      if(board.getTurn())
      {
        cout << "Black turn:\n";
      }
      else
      {
        cout << "White turn:\n";
      }

      if((whiteIsAI and not board.getTurn()) or (blackIsAI and board.getTurn()))
      {
        Move move = getAImove(board);
        start = move.start;
        end = move.end;
        cout << start.toString() << endl;
        cout << end.toString() << endl;
        moveInputted = true;
      }
      else
      {
        cin >> startInput;

        if(startInput == "quit")
        {
          gameOver=true;
          break;
        }
        else if(startInput == "undo")
        {
          board.undoLastMove();
          if(whiteIsAI or blackIsAI)  //si on joue contre une IA on retire aussi son dernier move
          {
            board.undoLastMove();
          }
          moveInputted = false;
        }
        else
        {
          cin >> endInput;
          moveInputted = true;

          start = Square(startInput);
          end = Square(endInput);
        }
      }

      if(moveInputted)
      {
        try
        {
          board.play(start,end);
          moveMade = true;
          if(board.isCheckMate or board.isStaleMate)
          {
            gameOver = true;
            cout << board.toString();
          }
        }
        catch(string const & msg)
        {
          cerr << "Invalid move: "+msg;

          if((whiteIsAI and not board.getTurn()) or (blackIsAI and board.getTurn()))
          {
            cout << "Skipping AI turn\n";
            board.setTurn(not board.getTurn());
          }
        }
      }
    }
  }
}



void ChessGame::printHelp() const
{
  cout << "Type 'quit' to close the game\n";
  cout << "Type 'undo' to undo the last move\n";
}
