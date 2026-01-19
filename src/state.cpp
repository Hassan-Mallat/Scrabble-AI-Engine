#include "state.hpp"
#include "board.hpp"



State::State(Position _initial, Position _current, PlayerLetters _playableLetter,
             std::vector<Position> const& _playedLetter, GaddagNode _currentNode, Direction _direction, bool _forward/*,const letterBag& _lbag*/)
    : initial(_initial), current(_current), playableLetter(_playableLetter),
      playedLetter(_playedLetter), currentNode(_currentNode), direction(_direction), forward(_forward)/*, lbag(_lbag)*/ {}

Position State::determineNextPosition(Board& board) const {
    int row = current.getRow();
    int col = current.getCol();

    if (direction == HORIZONTAL) {
        col += (forward ? 1 : -1);
    } else {
        row += (forward ? 1 : -1);
    }
    if(board.isInBoard(row,col)) {
        return Position(row, col, board.getSpotAt(row, col));
    }  else {
       return current;
    }

}


void State::run(std::vector<State>& stack, Board& board, Gaddag const& gaddag,const letterBag& lbag) {
    // Si la case actuelle est occupée
    if (current.isOccupied()) {
        char letterToPlace = current.getLetter();
        current.isInit(true);


        // Vérifie si la lettre est un enfant du noeud courant dans le Gaddag
        if (currentNode.hasChild(letterToPlace)) {
            GaddagNode* nextNode = currentNode.getChild(letterToPlace);
            playedLetter.push_back(current);  // Ajoute la position actuelle et la lettre jouée

            currentNode = *nextNode;           // Mise à jour du noeud courant
            Position next = determineNextPosition(board);     // Détermine la prochaine case à explorer
            if(next.getRow() != current.getRow() || next.getCol() != current.getCol()) {
                stack.emplace_back(State(
                    initial, next, playableLetter,
                    playedLetter, *nextNode, direction, forward
                ));
                return;
            } else {
                if(nextNode->isTerminal()) {
                    //
                    display();
                    board.addWordToNextWords(playedLetter,lbag, direction);
                }
                return;
            }

        } else {
            // Si la lettre n'est pas présente dans les enfants, l'exploration s'arrête ici
            return;
        }
    }
    // Si la case est vide, on essaie de jouer toutes les lettres possibles
    else {
        // Vérifie si le noeud courant est terminal (mot complet formé)

        if (currentNode.isTerminal()) {
            display();
            board.addWordToNextWords(playedLetter, lbag,direction);  // On enregistre le mot formé dans nextWords
        }



        // Si on n'a pas encore exploré la direction après le '+'
        if (currentNode.hasChild('+') && !forward) {
            GaddagNode* nextNode = currentNode.getChild('+');

            Position next;
            if (direction == HORIZONTAL) {
                // Si c'est une direction horizontale, on passe à la case suivante dans cette direction
                if(board.isInBoard(initial.getRow(), initial.getCol()+1)) {
                    next = Position(initial.getRow(), initial.getCol() + 1, board.getSpotAt(initial.getRow(), initial.getCol() + 1));
                    State newState(initial, next, playableLetter, playedLetter, *nextNode, direction, true);// Crée un nouvel état pour la direction après le '+'
                    stack.push_back(newState);
                } //sinon on part au return
            } else {
                // Si c'est une direction verticale, on passe à la case suivante dans cette direction
                if(board.isInBoard(initial.getRow()+1, initial.getCol())) {
                    next = Position(initial.getRow()+1, initial.getCol(), board.getSpotAt(initial.getRow()+1, initial.getCol()));
                    State newState(initial, next, playableLetter, playedLetter, *nextNode, direction, true);// Crée un nouvel état pour la direction après le '+'
                    stack.push_back(newState);//sinon on part au return
                }
            }



            //return; // On arrête pas , cet état peut encore créer d'autres direction.
        }


        // Teste chaque lettre jouable à la position actuelle
        for (size_t i = 0; i < playableLetter.size(); ++i) {
            char letter = playableLetter.get(i).getLetter();
            // Place la lettre sur la case actuelle
            current.placeLetter(letter);

            // Vérifie si la lettre est un enfant du noeud courant dans le Gaddag
            if (currentNode.hasChild(letter)) {
                // Vérification du mot secondaire
                if (isSecondaryWordValid(current, direction, board, gaddag)) {
                    //board.addWordToNextWords(playedLetter);  // Enregistre le mot secondaire formé
                    GaddagNode* nextNode = currentNode.getChild(letter);  // Noeud suivant dans le Gaddag

                    std::vector<Position> playedLetterCopy = playedLetter;
                    PlayerLetters playableLetterCopy = playableLetter;

                    // Modifier les copies
                    playedLetterCopy.push_back(current);
                    playableLetterCopy.remove(i);
                    //playedLetter.push_back(current);       // Ajoute la position et la lettre à playedLetter

                    //auto removed = playableLetter.get(i);
                    //playableLetter.remove(i);              // Suppression

                    // On sauvegarde l'état et continue l'exploration
                    Position next = determineNextPosition(board);
                    if(next.getRow() != current.getRow() || next.getCol() != current.getCol()) {
                        stack.emplace_back(
                            initial, next, playableLetterCopy,
                            playedLetterCopy, *nextNode, direction, forward
                        );
                    } else {
                        if(nextNode->isTerminal()) {
                            display();
                           board.addWordToNextWords(playedLetter, lbag,direction);//ajout si c'est un noeud terminal et on est au bord
                        }
                    }

                }
                //GaddagNode savedNode = currentNode; //pas besoin

            }

            // Nettoyage : on retire la lettre posée
            current.placeLetter(0);
        }

    }

    // Vérifie si l'exploration est terminée (aucune lettre à jouer)
    if (playedLetter.empty()) {
        return;  // L'exploration est terminée pour cet état
    }
}


bool State::isSecondaryWordValid(Position pos, Direction dir, Board& board, Gaddag const& gaddag) {
    // Déterminer la direction perpendiculaire
    Direction perpendicularDir = (dir == HORIZONTAL) ? VERTICAL : HORIZONTAL;

    // Initialiser les positions pour avancer et reculer dans la direction perpendiculaire
    Position before = pos;
    Position after = pos;

    // 1. Vérifier la direction arrière (avant la position de la lettre)

    // Se déplacer vers la gauche (HORIZONTAL) ou vers le haut (VERTICAL) (case non vide consécutif)
    if(perpendicularDir == HORIZONTAL) {
        Position tmp = before;
        while (board.isInBoard(before.getRow(), before.getCol() - 1)){

           tmp = Position(before.getRow(), before.getCol() - 1, board.getSpotAt(before.getRow(), before.getCol() - 1));

            // on s'arrete si case vide
           if(tmp.getLetter()!= 0) {
               before = tmp;
           }else {
               break;
           }

       };// on s'arrete au bord ou


    } else {
        Position tmp = before;
        while (board.isInBoard(before.getRow() - 1, before.getCol())){
           tmp = Position(before.getRow() - 1, before.getCol(), board.getSpotAt(before.getRow() - 1, before.getCol()));

            // on s'arrete si case vide
           if(tmp.getLetter()!= 0) {
               before = tmp;
           }else {
               break;
           }

       };// on s'arrete au bord ou

    }


    // 2. Reconstituer le mot à partir de la direction inverse

    std::string wordBackward = "";
    while (before.isValid() && before.getLetter() != 0) {
        wordBackward = before.getLetter() + wordBackward; // Ajouter à la gauche
        if (perpendicularDir == HORIZONTAL) {
            before = Position(before.getRow(), before.getCol() + 1, board.getSpotAt(before.getRow(), before.getCol() + 1));
        } else {
            before = Position(before.getRow() + 1, before.getCol(), board.getSpotAt(before.getRow() + 1, before.getCol()));
        }
    }


    // 4. Reconstituer le mot dans la direction avant
    std::string wordForward = "";
    if(perpendicularDir == HORIZONTAL) {
        Position tmp = after;
        while (board.isInBoard(after.getRow(), after.getCol()+1)) {
            tmp = Position(after.getRow(), after.getCol()+1, board.getSpotAt(after.getRow(), after.getCol()+1));
            if(tmp.getLetter()!= 0) {
                 after = tmp;
                 wordForward += after.getLetter();  // Ajouter à la droite
            } else {
                break;
            }

        }
    }else{
        Position tmp = after;
while (board.isInBoard(after.getRow()+1, after.getCol())) {

        tmp = Position(after.getRow()+1, after.getCol(), board.getSpotAt(after.getRow()+1, after.getCol()));
     if(tmp.getLetter()!= 0) {
         after = tmp;
         wordForward += after.getLetter();  // Ajouter à la droite
        } else {
            break;
        }
}
    }


    // Combiner les deux parties du mot perpendiculaire
    std::string secondaryWord = wordBackward + current.getLetter() + wordForward;
    if(secondaryWord.size() < 2) {
        return true; // pas de mot secondaire donc c'est bon
    }
    // Vérifier si le mot secondaire formé est valide dans le Gaddag
    //return currentNode.hasChild(secondaryWord);
    return gaddag.contains(secondaryWord);
    //GaddagNode node = currentNode;  // copie locale
    //for (char c : secondaryWord) {
        //if (!node.hasChild(c)) return false;
        //node = *node.getChild(c); // car getChild retourne un pointeur
    //}
    //return node.isTerminal();
}

void State::display() const {
    std::cout << "----- État actuel -----" << std::endl;
    std::cout << "Initial: (" << initial.getRow() << ", " << initial.getCol() << ")" << std::endl;
    std::cout << "Courant: (" << current.getRow() << ", " << current.getCol() << ")" << std::endl;

    std::cout << "Direction: " << (direction == HORIZONTAL ? "HORIZONTAL" : "VERTICAL") << std::endl;
    std::cout << "Avance: " << (forward ? "Oui" : "Non") << std::endl;

    std::cout << "Lettres jouables: ";
    for (size_t i = 0; i < playableLetter.size(); ++i) {
        std::cout << playableLetter.get(i).getLetter() << " ";
    }
    std::cout << std::endl;

    std::cout << "Lettres déjà jouées: ";
    for (auto const& pos : playedLetter) {
        std::cout << pos.getLetter() << "(" << pos.getRow() << "," << pos.getCol() << ") ";
    }
    std::cout << std::endl;

    std::cout << "Noeud courant: ";
    std::cout << (currentNode.isTerminal() ? "[Terminal]" : "[Non-terminal]") << std::endl;

    std::cout << "-----------------------" << std::endl;
}
