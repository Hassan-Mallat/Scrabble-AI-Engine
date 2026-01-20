#include "position.hpp"
//#include "spot.hpp"

Position :: Position(int r, int c, const Spot& s, bool fromInit) : row(r), col(c), spot(s) {}
Position::Position() : row(0), col(0), spot(Spot()) {}

int Position::getRow() const {
    return row;
}

int Position::getCol() const {
    return col;
}

// Vérifie si une lettre est placée
bool Position :: isOccupied() const {
    return spot.letter != 0;
}

// Récupère la lettre à cette position
char Position :: getLetter() const {
    return spot.letter;
}

// Place une lettre à cette position
void Position :: placeLetter(char c) {
     spot.letter = c;
}

bool Position::isValid() const {
    return row >= 0 && row < 15 && col >= 0 && col < 15;
}

void Position::isInit(bool _fromInit){
    fromInit = _fromInit;
}
bool Position::isFromInit() const {
    return fromInit;
}
