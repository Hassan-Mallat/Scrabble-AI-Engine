#ifndef POSITION
#define POSITION
#include "spot.hpp"

class Position {

    private:
        int row;
        int col;
        Spot spot;
        bool fromInit;

    public:
        Position(int r, int c, const Spot& s, bool _fromInit = false);
        Position();
        int getRow() const;
        int getCol() const;

        void isInit(bool _fromInit); // setting a position to from inital phase
        bool isFromInit() const; // getting if a position is from inital phase
        bool isOccupied() const;
        char getLetter() const;
        void placeLetter(char c);
        bool isValid() const;
};

#endif
