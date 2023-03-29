#include <cctype>
#include <bits/stdc++.h>
#include "Square.h"



Square::Square()
{
  if(charValue.size() == 0)
  {
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string figures = "0123456789";
    int value = 0;
    for(char letter:alphabet)
    {
      isLetter.insert({letter,true});
      charValue.insert({letter,value+1});
      valueChar.insert({1+value,letter});
      value++;
    }
    value = 0;
    for(char figure:figures)
    {
      isLetter.insert({figure,false});
      charValue.insert({figure,value});
      value++;
    }
  }
}



Square::Square(int a,int b): Square()
{
  x = a;
  y = b;
}



Square::Square(string str): Square()
{
  x = 0;
  y = 0;
  bool readingLetters = true;
  for(char symbol:str)
  {
    symbol = tolower(symbol);

    if(isLetter[symbol])
    {
      x = x*26 + charValue[symbol];
    }
    else
    {
      if(readingLetters)
      {
        readingLetters = false;
      }
      y = y*10 + charValue[symbol];
    }
  }
  x -= 1; /* /!\ les positions commencent à 1  /!\ */
  y -= 1;
}



Square::Square(Square & square,int dx,int dy): Square()
{
  x = square.x + dx;
  y = square.y + dy;
}



int Square::getX() const{return x;}

int Square::getY() const{return y;}



string Square::toString() const
{
  /* on trouve la nom de la colonne */
  string word = "";
  int xCopy = x+1;
  while(xCopy != 0)
  {
    int leftover = ((xCopy-1)%26)+1;
    xCopy = (xCopy-leftover)/26;
    word += valueChar[leftover];
  }
  /* on inverse le string de la colonne */
  int len = word.length();
  int pos = len-1;
  for(int step=0;step<(len/2);step++){
    swap(word[step],word[pos]);
    pos -= 1;
  }
  /* on trouve la nom de la ligne */
  string number = to_string(y+1);
  return word+number;
}
