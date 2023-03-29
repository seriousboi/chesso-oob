#ifndef squareFile
#define squareFile
#include <string>
#include <map>
using namespace std;



class Square
{
private:
  int x;
  int y;

public:
  Square();
  Square(int a,int b);
  Square(string str);
  Square(Square & square,int dx,int dy);

  int getX() const;
  int getY() const;

  string toString() const;

  static inline map<char,bool> isLetter;
  static inline map<char,int> charValue;
  static inline map<int,char> valueChar;
};

#endif
