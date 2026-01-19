#include "playerletters.hpp"

PlayerLetters::PlayerLetters()
{

}

void PlayerLetters::addLetters(letterBag& lbag){
    while(letters.size()<7 && lbag.getRemainingTiles() > 0){
        //Letter* lettre = bag.pickLetterFromBag(); // tirer une lettre du sac
        char c = lbag.drawnLetter();
        Letter lettre = Letter(c, lbag.getLetterPoints(c));
        //letters.push_back(lettre); // lettre ne peut être nullptr
        add(lettre);
    }
}

void PlayerLetters::displayLetters() const {
           std::cout << "Lettres sélectionnées : " << std::endl;
           for (int i=0; i<(int)letters.size();i++) {
               std::cout << letters[i].getLetter() << " (" << letters[i].getPoint() << " points)" << std::endl;
           }
}

const std::vector<Letter>& PlayerLetters::getLetters() const {
    return letters;
}



void PlayerLetters::removeLetter(Letter letterToRemove) {
    // Cherche la lettre à retirer dans le vecteur letters
    // std::find renvoie un itérateur vers la première occurrence trouvée (ou letters.end() si non trouvée)
    auto it = std::find(letters.begin(), letters.end(), letterToRemove);

    // Si la lettre a bien été trouvée dans le vecteur
    if (it != letters.end()) {
        // On la retire du vecteur grâce à erase
        letters.erase(it);
    }
}

// Taille de la main
    size_t PlayerLetters::size() const {
        return letters.size();
    }

    // Accès à une lettre par index
    
    Letter& PlayerLetters::get(size_t index) {
        return letters.at(index);
    }
    const Letter& PlayerLetters::get(size_t index) const {
        return letters.at(index);
    }

    // Suppression d'une lettre par index
    void PlayerLetters::remove(size_t index) {
        if (index < letters.size()) {
            letters.erase(letters.begin() + index);
        }
    }

    // Ajout d'une lettre (utile si tu veux réutiliser les lettres retirées)
    void PlayerLetters::add(Letter const& letter) {
        letters.push_back(letter);
    }

    // Pour itérer dans les boucles si besoin
    std::vector<Letter>::const_iterator PlayerLetters :: begin() const { return letters.begin(); }
    std::vector<Letter>::const_iterator PlayerLetters :: end() const { return letters.end(); }

