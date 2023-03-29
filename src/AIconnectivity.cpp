#include <iostream>
#include <fstream>
#include "AIconnectivity.h"



Move getAImove(ChessBoard const & board,bool blackTurn,bool whiteHasCastlingRights,bool blackHasCastlingRights,string gameDataPath)
{
  writeInput(board,blackTurn,whiteHasCastlingRights,blackHasCastlingRights,gameDataPath);
  system(("python3 '"+gameDataPath+"../playOutside.py'").c_str());
  return getOutput(gameDataPath);
}



void writeInput(ChessBoard const & board,bool blackTurn,bool whiteHasCastlingRights,bool blackHasCastlingRights,string gameDataPath)
{
  string fileName = gameDataPath + "input.txt";
  ofstream outStream(fileName);
  outStream << "Board FEN:\n";
  outStream << board.toFen();
  if(blackTurn)
  {
    outStream << " b";
  }
  else
  {
    outStream << " w";
  }
  outStream << " KQkq - 0 1\n"; //à améliorer
  outStream << "Its black's turn:\n";
  outStream << blackTurn << endl;
  outStream.close();
}



Move getOutput(string gameDataPath)
{
  string fileName = gameDataPath + "output.txt";
  ifstream dataStream(fileName);
  if(!dataStream)
  {
    cout << "oof, cannot open file '" << fileName << "'\n";
    return {Square(-1,-1),Square(-1,-1)};
  }

  string buffer;
  bool moveUpdated = false;
  while(not moveUpdated)
  {
    dataStream = ifstream(fileName);
    dataStream >> buffer;
    if(buffer == "New")
    {
      moveUpdated = true;
    }
    else
    {
      dataStream.close();
    }
  }
  string startOuput;
  string endOutput;
  dataStream >> startOuput;
  dataStream >> endOutput;
  dataStream.close();

  ofstream outStream(fileName);
  outStream << "Old\n";
  outStream << startOuput << endl;
  outStream << endOutput << endl;
  outStream.close();
  return {Square(startOuput),Square(endOutput)};
}
