#pragma once
#include <iostream>
#include <string>
#include <exception>
#include <math.h>
#include "Spot.h"
#include "IllegalCoordinateException.h"
#include "IllegalCharException.h"
using namespace std;

struct RGB {
  uint8_t red, green, blue;
public:
  RGB() {}
  RGB(uint8_t red, uint8_t green, uint8_t blue): red(red), green(green), blue(blue) {}
};


class Board{  
    public:
       Spot **b;
       uint length;
       uint size()const{return length;}
       Board();
       Board(uint length);
       Board(const Board& b2);
       Spot& operator[](Coordinate p2)const;
       Board& operator=(char in);
       Board& operator=(const Board& b2);
       bool operator==(const Board &b2) const;
       string draw (int Pixels);
       friend ostream& operator<< (ostream& os, const Board& b);//output
       friend istream& operator>> (istream& input, Board& b);//input
        ~Board();
};