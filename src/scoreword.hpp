#ifndef SCOREDWORD_HPP
#define SCOREDWORD_HPP
#include <vector>
#include "position.hpp"

struct ScoredWord {
    std::vector<Position> positions;
    int score;

    ScoredWord(const std::vector<Position>& pos, int s);
};

#endif // SCOREDWORD_HPP
