#include "letter.hpp"

Letter::Letter(char letter, int point) : letter(letter), point(point){}

Letter::Letter(const Letter &other):letter(other.letter), point(other.point) {}

Letter& Letter::operator=(const Letter& other)
{
  if (this != &other)
  {
    letter = other.letter;
    point = other.point;
  }
  return *this;
}

int Letter::getPoint() const{
    return point;
}
char Letter::getLetter() const{
    return letter;
}


