#ifndef LETTERBAG
#define LETTERBAG

#include <array>
#include <random>

class letterBag{
    private:
        //int size;
        std::array<int, 26> letterCounts;
        std::array<int, 26> letterPoints;
        std::array<int, 26> cumulativeCounts;
        int totalTiles;
        std::random_device rd;
        std::mt19937 gen;
        void updateCumulativeCounts();

    public:
        letterBag();
        char drawnLetter();
        int getLetterPoints(char letter) const;
        void printStatus();
        int getRemainingTiles();
        void saveState();
        void loadState();
        
};


#endif