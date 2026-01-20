#ifndef PLAYERLETTERS_HPP
#define PLAYERLETTERS_HPP
#include "letter.hpp"
#include "letterBag.hpp"
#include <iostream>
#include <algorithm>
#include <vector>


class PlayerLetters
{
private:
    std::vector<Letter> letters;

public:
    PlayerLetters();
    void addLetters(letterBag& lbag);
    void displayLetters() const;
    const std::vector<Letter>& getLetters() const;
    void removeLetter(Letter letterToRemove);
    // Taille de la main
        size_t size() const;

        // Accès à une lettre par index
        Letter& get(size_t index);
        const Letter& get(size_t index) const; 

        // Suppression d'une lettre par index
        void remove(size_t index);

        // Ajout d'une lettre (utile si tu veux réutiliser les lettres retirées)
        void add(Letter const& letter);

        // Pour itérer dans les boucles si besoin
        std::vector<Letter>::const_iterator begin() const;
        std::vector<Letter>::const_iterator end() const;

};

#endif // PLAYERLETTERS_HPP
