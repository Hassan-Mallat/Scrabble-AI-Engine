#include "gaddag.hpp"

Gaddag::Gaddag()
{
    root = new GaddagNode(false);
}

void Gaddag::insertWord(const std::string& word) {
    int n = word.size();
    for (int i = 0; i < n; ++i) {
        GaddagNode* current = root;

        // Partie gauche (renversée)
        for (int j = i; j >= 0; --j) {
            current = current->getOrCreateChild(word[j], false);
        }

        // Le +
        current = current->getOrCreateChild('+', false);

        // Partie droite (normale)
        for (int j = i + 1; j < n; ++j) {
            current = current->getOrCreateChild(word[j], false);
        }

        // Marquer le mot comme terminé
        current->setAsTerminal();
    }

}


void Gaddag::display() const {
    displayRecursive(root, "");
}

void Gaddag::displayRecursive(GaddagNode* node, std::string currentWord) const {
    if (node->isTerminal()) {
        std::cout << currentWord << std::endl;
    }

    // Maintenant, parcourons les enfants
    for (char c = 'A'; c <= 'Z'; ++c) {
        if (node->hasChild(c)) {
            displayRecursive(node->getOrCreateChild(c, false), currentWord + c);
        }
    }

    // Et on vérifie aussi pour le séparateur +
    if (node->hasChild('+')) {
        displayRecursive(node->getOrCreateChild('+', false), currentWord + '+');
    }

}

void Gaddag::loadDictionary(const std::string& filename) {
    std::string cheminAbsolu = "";  // Initialisation d'une chaîne de caractères vide pour stocker le chemin absolu
    char buffer[PATH_MAX];  // Buffer pour stocker le chemin complet de l'exécutable
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);  // readlink récupère le chemin de l'exécutable dans /proc/self/exe

    // Si readlink réussit, len sera la longueur du chemin de l'exécutable
    if (len != -1) {
        buffer[len] = '\0';  // Ajouter un caractère nul à la fin de la chaîne pour la terminer correctement
        std::string execPath(buffer);  // Convertir le buffer en chaîne de caractères pour obtenir le chemin complet de l'exécutable

        // Trouver la dernière barre oblique pour récupérer uniquement le répertoire contenant l'exécutable
        // find_last_of('/') recherche la dernière occurrence du caractère '/' dans execPath
        size_t pos = execPath.find_last_of('/');  // 'pos' contient la position de la dernière barre oblique
        cheminAbsolu = execPath.substr(0, pos + 1);  // Récupérer la sous-chaîne du chemin jusqu'à la dernière barre oblique, incluant celle-ci

        // `npos` est une constante spéciale dans C++ qui indique une position invalide. Elle est utilisée pour vérifier si une recherche a échoué.
        // Si find_last_of('/') n'a pas trouvé de '/' dans execPath, `pos` sera égal à `std::string::npos` (ce qui signifie "pas trouvé").
        // Si le fichier exécutable est dans le répertoire racine, cette ligne pourrait donner un comportement inattendu.

        // Ajouter le chemin relatif pour accéder au fichier 'filename' dans le dossier 'data'
        cheminAbsolu += filename;  // Construire le chemin absolu en ajoutant "../data/" et le nom du fichier passé en argument
    }

    // Ouvrir le fichier à partir du chemin construit
    std::ifstream file(cheminAbsolu);

    // Vérifier si le fichier s'est ouvert correctement
    if (!file) {
        // Si l'ouverture échoue, afficher une erreur
        std::cout << "Error : le fichier ne peut être lu !" << std::endl;
    } else {
        // Si l'ouverture est réussie, lire le fichier ligne par ligne
        std::string word;
        while (file >> word) {  // Lire chaque mot du fichier
            if (!word.empty())  // Vérifier si le mot n'est pas vide
                insertWord(word);  // Insérer le mot dans le Gaddag (ou toute autre structure)
        }
        std::cout << "Insertion terminée" << std::endl;  // Afficher un message quand le traitement est terminé
    }


}

/*
void Gaddag::loadDictionary(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "❌ Erreur : impossible d’ouvrir le fichier '" << filename << "' depuis le dossier courant." << std::endl;
        perror("💡 Détail système");
        return;
    }

    std::string word;
    while (file >> word) {
        if (!word.empty())
            insertWord(word);
    }

    std::cout << "✅ Insertion terminée depuis '" << filename << "'." << std::endl;
}
*/
bool Gaddag::contains(const std::string& word) const {
    int n = word.size();
    for (int pivot = 0; pivot < n; ++pivot) {
        GaddagNode* current = root;

        // Partie gauche (inversée)
        for (int j = pivot; j >= 0; --j) {
            if (!current->hasChild(word[j])) {
                current = nullptr;
                break;
            }
            current = current->getChild(word[j]);
        }

        if (current == nullptr || !current->hasChild('+')) continue;

        current = current->getChild('+');

        // Partie droite (normale)
        for (int j = pivot + 1; j < n; ++j) {
            if (!current->hasChild(word[j])) {
                current = nullptr;
                break;
            }
            current = current->getChild(word[j]);
        }

        if (current != nullptr && current->isTerminal()) {
            return true;
        }
    }
    return false;
}


Gaddag::~Gaddag() {
    //delete root;
}

GaddagNode Gaddag :: getRootNode() const{
    return *root;
}
