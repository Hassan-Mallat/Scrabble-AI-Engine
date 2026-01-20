#ifndef GADDAG_HPP
#define GADDAG_HPP
#include "gaddagnode.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <unistd.h> // Pour readlink
#include <cstring>
#include <limits.h> //Pour PATH_MAX

class Gaddag
{
private:
    GaddagNode *root;
public:
    Gaddag();
    void insertWord(const std::string& word);
    void display() const; // Fonction publique pour afficher
    void displayRecursive(GaddagNode* node, std::string currentWord) const;
    void loadDictionary(const std::string& filename);
    bool contains(const std::string& word) const;
    GaddagNode getRootNode() const;
    ~Gaddag();
};

#endif // GADDAG_HPP
