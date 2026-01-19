#ifndef STATE_HPP
#define STATE_HPP

#include "position.hpp"
#include "playerletters.hpp"
#include "gaddagnode.hpp"
#include "direction.hpp"
#include "gaddag.hpp"

//#include "board.hpp"
#include <vector>


struct SecondaryWord {
    Position startPos;
    Direction direction;
    std::string word;
};

class Board;


class State {
private:

    Position initial;
    Position current;
    PlayerLetters playableLetter;
    std::vector<Position> playedLetter;
    GaddagNode currentNode;
    Direction direction;
    bool forward;
    std::vector<SecondaryWord> secondaryWords;
    //const letterBag& lbag;


public:
    State(Position _initial, Position _current, PlayerLetters _playableLetter,
          std::vector<Position> const& _playedLetter, GaddagNode _currentNode, Direction _direction, 
          bool _forward/*, const letterBag& _lbag*/);

    Position determineNextPosition(Board& board) const;
    void run(std::vector<State>& stack, Board& board,Gaddag const& gaddag,const letterBag& lbag);
    bool isSecondaryWordValid(Position pos, Direction dir, Board& board,Gaddag const& gaddag);
    void display() const;
};


#endif
