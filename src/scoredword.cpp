#include "scoreword.hpp"

ScoredWord::ScoredWord(const std::vector<Position>& pos, int s)
    : positions(pos), score(s) {}
