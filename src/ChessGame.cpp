#include <iostream>
#include <string>
#include "ChessGame.h"
#include "AIconnectivity.h"
#include "ChessMove.h"
using namespace std;



ChessGame::ChessGame()
{
  running = true;
  whiteIsAI = false;
  blackIsAI = true;
}



void ChessGame::run()
{
  string input;
  string fileName;

  printMenu();

  while(running)
  {
    getline(cin, input);

    if(input == "quit")
    {
      running = false;
    }
    else if(input == "load")
    {
      cout << "Type the name of file to load\n";
      getline(cin, fileName);
      try
      {
        board.loadFile(fileName);
        play();
        printMenu();
      }
      catch(string const & msg)
      {
        cout << msg;
        cout << endl;
      }
    }
    else if(input == "play")
    {
      board.init();
      play();
      printMenu();
    }
    else if(input == "set white manual")
    {
      whiteIsAI = false;
      cout << "White set to manual control\n";
    }
    else if(input == "set black manual")
    {
      blackIsAI = false;
      cout << "Black set to manual control\n";
    }
    else if(input == "set white AI")
    {
      whiteIsAI = true;
      cout << "White set to AI control\n";
    }
    else if(input == "set black AI")
    {
      blackIsAI = true;
      cout << "Black set to AI control\n";
    }
    else
    {
      cout << "Unkown command\n";
    }
  }
}



void ChessGame::play()
{
  gameOver = false;

  cout << endl;
  cout << "Type 'quit' to return to the menu\n";
  cout << "Type 'undo' to undo the last move\n";
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
      //cout << board.toFen() << endl; debug
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
        getline(cin, startInput);

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
          getline(cin, endInput);
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



void ChessGame::printMenu()
{
  cout << endl;
  cout << "Type 'play' to start a chess game\n";
  cout << "Type 'quit' to close the program\n";
  cout << "Type 'load' to load a board\n";
  cout << "Type 'set <color> <user>' to choose if a side is controlled by a player or an AI\n";
  cout << "<color> can be 'black' or 'white', <user> can be 'AI' or 'manual'\n";
  cout << "By default white is controlled manually and black is an AI\n";
  cout << endl;
}
