#include <iostream>
#include <string>
#include "ChessGame.h"
#include "AIconnectivity.h"
using namespace std;



ChessGame::ChessGame()
{
  board = ChessBoard();
  board.init();
  blackTurn = false;
  whiteHasCastlingRights = true;
  blackHasCastlingRights = true;
  gameOver = false;
}



void ChessGame::play()
{
  bool whiteIsAI = true;
  bool blackIsAI = true;

  printHelp();
  while(not gameOver)
  {
    cout << board.toString();

    bool moveMade = false;
    string startInput;
    string endInput;
    Square start;
    Square end;

    while(not moveMade)
    {
      if(blackTurn)
      {
        cout << "Black turn:\n";
      }
      else
      {
        cout << "White turn:\n";
      }

      if((whiteIsAI and not blackTurn) or (blackIsAI and blackTurn))
      {
        Move move = getAImove(board,blackTurn,whiteHasCastlingRights,blackHasCastlingRights);
        start = move.start;
        end = move.end;
        cout << start.toString() << endl;
        cout << end.toString() << endl;
      }
      else
      {
        cin >> startInput;
        if(startInput == "quit"){gameOver=true;break;}
        cin >> endInput;
        if(endInput == "quit"){gameOver=true;break;}

        start = Square(startInput);
        end = Square(endInput);
      }

      try
      {
        board.play(start,end,blackTurn);
        moveMade = true;
      }
      catch(string const & msg)
      {
        cerr << "Invalid move: "+msg;

        if((whiteIsAI and not blackTurn) or (blackIsAI and blackTurn))
        {
          cout << "Skipping AI turn\n";
          blackTurn = not blackTurn;
        }
      }
    }
    blackTurn = not blackTurn;
  }
}



void ChessGame::printHelp() const
{
  cout << "Type 'quit' to close the game\n";
}
