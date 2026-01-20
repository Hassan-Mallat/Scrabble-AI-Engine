#include <iostream>
#include "letterBag.hpp"
#include <fstream>  // For file handling
//#include <random>

/*
std::array<int, 26> letterCounts = {9, 2, 2, 4, 12, 2, 3, 2, 9, 1, 
    1, 4, 2, 6, 8, 2, 1, 6, 4, 6, 
    4, 2, 2, 1, 2, 1};

// Letter points (A-Z) based on Scrabble points
std::array<int, 26> letterPoints = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 
    5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 
    1, 4, 4, 8, 4, 10};
*/
/*
letterBag::letterBag() : gen(rd()) {
    // Letter counts (A-Z) based on Scrabble distribution
    letterCounts = {9, 2, 2, 3, 15, 2, 2, 2, 8, 1, 1, 5, 3, 6, 6, 2, 1, 6, 6, 6,
        6, 2, 1, 1, 1, 1};

    // Letter points (A-Z) based on Scrabble points
    letterPoints = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 10, 1, 2, 1, 1, 3, 8, 1, 1, 1,
            1, 4, 10, 10, 10, 10};

    // Initialize cumulative counts and total tiles
    updateCumulativeCounts();
}
*/

letterBag::letterBag() : gen(rd()) {
    // Default Scrabble distribution
    letterCounts = {9, 2, 2, 3, 15, 2, 2, 2, 8, 1, 1, 5, 3, 6, 6, 2, 1, 6, 6, 6,
        6, 2, 1, 1, 1, 1};

    letterPoints = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1,
            1, 4, 4, 8, 4, 10};

    // Load saved state if available
    loadState();
    
    // Initialize cumulative counts
    updateCumulativeCounts();
}

//letterBag::letterBag(/*int sz, */std::array<int, 26> arrC, std::array<int, 26> arrP) :
    //size(sz),
//    letterCounts(arrC),
//    letterPoints(arrP)
//{};

/*
char letterBag::drawnLetter(){

    // Randomly select a letter using the cumulative counts
    std::uniform_int_distribution<int> dist(0, totalTiles - 1);
    int randomIndex = dist(gen);

    // Find the letter corresponding to the random index
    char drawnLetter;
    for (int i = 0; i < 26; ++i) {
        if (randomIndex < cumulativeCounts[i]) {
            drawnLetter = 'A' + i;
            letterCounts[i]--;  // Remove one occurrence of the letter
            totalTiles--;  // Decrease total tiles
            break;
        }
    }

    // Update cumulative counts after removing the letter
    updateCumulativeCounts();

    return drawnLetter; 
}
*/
/*
char letterBag::drawnLetter(){
    std::uniform_int_distribution<int> dist(0, totalTiles - 1);
    int randomIndex = dist(gen);

    char drawnLetter = '?';  // Default unknown letter

    for (int i = 0; i < 26; ++i) {
        if (randomIndex < cumulativeCounts[i]) {
            if (letterCounts[i] > 0) {  // Ensure the letter still has tiles left
                drawnLetter = 'A' + i;
                letterCounts[i]--;  // Remove one occurrence
                totalTiles--;  // Decrease total count
                updateCumulativeCounts();  // Fix count immediately
                return drawnLetter;
            }
        }
    }

    return drawnLetter; // Should never reach here if totalTiles > 0
}
*/

char letterBag::drawnLetter(){
    if (totalTiles == 0) {
        std::cout << "No more tiles left to draw!" << std::endl;
        return '?';  // Return a placeholder if bag is empty
    }

    std::uniform_int_distribution<int> dist(0, totalTiles - 1);
    int randomIndex = dist(gen);

    char drawnLetter = '?';  // Default unknown letter

    for (int i = 0; i < 26; ++i) {
        if (randomIndex < cumulativeCounts[i]) {
            if (letterCounts[i] > 0) {  // Ensure letter is available
                drawnLetter = 'A' + i;
                letterCounts[i]--;  // Remove one occurrence of the letter
                totalTiles--;  // Decrease total tiles
                updateCumulativeCounts();  // Update cumulative counts
                return drawnLetter;  
            }
        }
    }

    return drawnLetter;  // Should never reach here if totalTiles > 0
}

int letterBag::getLetterPoints(char letter) const{
    //return letterPoints[drawnLetter() - 'A']; 
    return letterPoints[letter - 'A'];
} 

int letterBag::getRemainingTiles() {
    return totalTiles;
}

/*
void letterBag::updateCumulativeCounts() {
    cumulativeCounts[0] = letterCounts[0];
    for (int i = 1; i < 26; ++i) {
        cumulativeCounts[i] = cumulativeCounts[i - 1] + letterCounts[i];
    }
    totalTiles = cumulativeCounts[25];  // Update the total tiles count
}
*/
void letterBag::updateCumulativeCounts() {
    cumulativeCounts[0] = letterCounts[0]; // First letter count
    for (int i = 1; i < 26; ++i) {
        cumulativeCounts[i] = cumulativeCounts[i - 1] + letterCounts[i]; // Keep sum
    }
    totalTiles = cumulativeCounts[25];  // Ensure total tiles remain accurate
}

void letterBag::printStatus() {
    //updateCumulativeCounts();
    std::cout << "Remaining Tiles: " << totalTiles << std::endl;
    for (int i = 0; i < 26; ++i) {
        std::cout << (char)('A' + i) << ": " << letterCounts[i] << " tiles\n";
    }
}

void letterBag::saveState() {
    std::ofstream file("state.txt");
    if (!file) {
        std::cerr << "Error opening file for saving!" << std::endl;
        return;
    }
    
    file << totalTiles << std::endl;
    for (int i = 0; i < 26; i++) {
        file << letterCounts[i] << " ";
    }
    file << std::endl;

    file.close();
}

void letterBag::loadState() {
    std::ifstream file("state.txt");
    if (!file) {
        std::cerr << "No previous state found. Initializing default values." << std::endl;
        return;  // Keep default initialization
    }

    file >> totalTiles;
    for (int i = 0; i < 26; i++) {
        file >> letterCounts[i];
    }

    file.close();
    updateCumulativeCounts();  // Recalculate cumulative counts
}