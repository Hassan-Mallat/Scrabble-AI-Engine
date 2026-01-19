#include "board.hpp"


#include <fstream>

//default initialization
Board::Board() {
  //Triple word spots
  {
    Spot s(1, 3) ;
    static const unsigned char sz = 9 ;
    static unsigned char triple_words[sz] = {
      0, 7, 14,
      105, 119,
      210, 217, 224
    } ;
    for(unsigned char i = 0; i < sz; ++i) {
      spots[triple_words[i]] = s ;
    }
  }
  //Double word spots
  {
    Spot s(1, 2) ;
    static const unsigned char sz = 17 ;
    static unsigned char double_words[sz] = {
      16, 28,
      32, 42,
      48, 56,
      64, 70,
      112,
      154, 160,
      168, 176,
      182, 192,
      196, 208
    } ;
    for(unsigned char i = 0; i < sz; ++i) {
      spots[double_words[i]] = s ;
    }
  }
  //Tripple letter spots
  {
    Spot s(3, 1) ;
    static const unsigned char sz = 12 ;
    static unsigned char triple_letters[sz] = {
      20, 24,
      76, 80, 84, 88,
      136, 140, 144, 148,
      200, 204
    } ;
    for(unsigned char i = 0; i < sz; ++i) {
      spots[triple_letters[i]] = s ;
    }
  }
  //Double letter spots
  {
    Spot s(2, 1) ;
    static const unsigned char sz = 24 ;
    static unsigned char double_letters[sz] = {
      3, 11,
      36, 38,
      45, 52, 59,
      92, 96, 98, 102,
      108, 116,
      122, 126, 128, 132,
      165, 172, 179,
      186, 188,
      213, 221
    } ;
    for(unsigned char i = 0; i < sz; ++i) {
      spots[double_letters[i]] = s ;
    }
  }
}

//i/o to files
void Board::save(std::ostream& out) {
  //write the grid of chars
  for(unsigned char i = 0; i < 225; ++i) {
    if( i%15 == 0) {
      out << std::endl ;
    }
    if(spots[i].letter) {
      //a letter is present, write it
      out << spots[i].letter ;
    } else {
      //no letter, put a dot
      out << "." ;
    }
  }
}

void Board::load(std::istream& in) {
  char c ;
  //read a char for each spot
  for(unsigned char i = 0; i < 225; ++i) {
    in >> c ;
    if(c != '.') {
      //a letter is provided, save it
      spots[i].letter = c ;
    } else {
      //no letter, set to 0
      spots[i].letter = 0 ;
    }
  }
}

//access to the spots by coordinates
Spot Board::operator()(unsigned char l, unsigned char c) const {
  return spots[l*15 + c] ;
}

Spot& Board::operator()(unsigned char l, unsigned char c) {
  return spots[l*15 + c] ;
}

//display on the console
std::ostream& operator<<(std::ostream& out, const Board& b) {

  static const char* grey = "\033[1;90m" ;
  static const char* reset = "\033[1;0m" ;

  //top frame line
  for(int i = 0; i < 67; ++i) {
    out << "#" ;
  }
  out << std::endl ;

  //rows top symbols
  for(unsigned char i = 0; i < 15; ++i) {
    //left frame
    out << "#  " ;
    //columns first line
    for(unsigned char j = 0; j < 15; ++j) {
      //type of the top left corner
      bool above = (i > 0 && (b(i-1,j).letter != 0)) ;
      bool weak_above = (above || (i > 0 && j > 0 && b(i-1,j-1).letter != 0)) ;
      bool below = (b(i,j).letter != 0) ;
      bool weak_below = (below || (j > 0 && b(i, j-1).letter != 0)) ;
      if (weak_above && weak_below) {
        //a letter is placed on both sides
        out << ":" ;
      } else if (weak_above) {
        //letters only above
        out << "'" ;
      } else if (weak_below) {
        //letters only below
        out << "." ;
      } else {
        //no letter around
        out << grey << "+" << reset ;
      }
      //type of the top edge
      if(above && below) {
        //both sides contain letters
        out << "---" ;
      } else if(above || below) {
        //a letter only on one side
        out << "---" ;
      } else {
        //no letter around
        out << "   " ;
      }
      //final top right corner
      if(j == 14) {
        if (above && below) {
          //letters on both sides
          out << ":" ;
        } else if (above) {
          //letter above
          out << "'" ;
        } else if (below) {
          //letter below
          out << "." ;
        } else {
          //no letter around
          out << grey << "+" << reset ;
        }
      }
    }
    //right frame and left frame of next line
    out << "  #" << std::endl << "#  " ;
    //columns second line
    for(unsigned char j = 0; j < 15; ++j) {
      //type of the left vertical edge
      bool left = (j > 0 && b(i,j-1).letter != 0) ;
      bool right = b(i,j).letter != 0 ;
      if(left || right) {
        //a letter is present at least on one side
        out << "| " ;
      } else {
        //no letter around
        out << "  " ;
      }
      //contents of the spot
      out << b(i,j) << " " ;
      //right vertical edge of the last spot on the line
      if(j == 14) {
        if(right) {
          //a letter is present
          out << "|" ;
        } else {
          //no letter around
          out << " " ;
        }
      }
    }
    //final frame
    out << "  #" << std::endl ;
  }
  //lower part of last line
  out << "#  " ;
  for(unsigned char j = 0; j < 15; ++j) {
    //corner type
    bool above = (b(14,j).letter != 0) ;
    bool weak_above = (above || (j > 0 && b(14,j-1).letter != 0)) ;

    if (weak_above) {
      //a letter is above
      out << "'" ;
    } else {
      //no letter around
      out << grey << "+"<< reset ;
    }
    //edge type
    if(above) {
      //a letter is above
      out << "---" ;
    } else {
      //no letter above
      out << "   " ;
    }
    //last corner type
    if(j == 14) {
      if(above) {
        //a letter is present
        out << "." ;
      } else {
        //no letter around
        out << grey << "+" << reset ;
      }
    }
  }
  //finalize frame
  out << "  #" << std::endl ;
  for(int i = 0; i < 67; ++i) {
    out << "#" ;
  }
  out << std::endl ;

  return out ;
}


// Trouver les voisins vides:

void Board::freeNeighborSpots(std::vector<Position>& freeNeighbor) {

  // Déclaration des déplacements sans static
  const int dx[] = { 0, 0, -1, 1 };
  const int dy[] = { -1, 1, 0, 0 };

  // Parcours de toutes les cases du plateau (15x15)
  for (int row = 0; row < 15; ++row) {
      for (int col = 0; col < 15; ++col) {
          // Vérification si la case est occupée
          Spot& s = (*this)(row, col);
          if (s.letter != 0) { // Si la case est occupée (contient une lettre)
              // Parcours des voisins (haut, bas, gauche, droite)
              for (int dir = 0; dir < 4; ++dir) {
                  int newRow = row + dy[dir];
                  int newCol = col + dx[dir];

                  // Vérification des limites du plateau
                  if (newRow >= 0 && newRow < 15 && newCol >= 0 && newCol < 15) {
                      Spot& neighbor = (*this)(newRow, newCol);
                      // Ajouter la case voisine si elle est libre (letter == 0)
                      if (neighbor.letter == 0) {
                          freeNeighbor.emplace_back(newRow, newCol, neighbor);
                      }
                  }
              }
          }
      }
  }
}


//Assume que le plateau fait 15x15 cases.
bool Board::isInBounds(const Position& pos) const {
    int row = pos.getRow();
    int col = pos.getCol();
    return row >= 0 && row < 15 && col >= 0 && col < 15;
}

void Board::search(GaddagNode gaddagRoot, Gaddag const& gaddag, const letterBag& lbag) {
    std::vector<Position> freeNeighbors;
    freeNeighborSpots(freeNeighbors); // Remplit le vecteur avec les cases adjacentes vides

    Direction directions[2] = { HORIZONTAL, VERTICAL };

        //pour chaque case voisine
    for (auto& neighbor : freeNeighbors) {
        for (int i = 0; i < 2; ++i) { //je choisis une direction
            Direction dir = directions[i];

            // Initialiser le premier état pour démarrer l'exploration
            State initialState(
                neighbor,           // Position de départ (la case vide)
                neighbor,           // Position courante (la case vide)
                playerLetters,      // Lettres disponibles du joueur courant
                {},                 // Aucune lettre jouée au départ
                gaddagRoot,         // Racine du GADDAG
                dir,                 // Direction actuelle
                false/*,
                lbag*/
            );

            // Stack d'états à explorer
            std::vector<State> stack;
            stack.push_back(initialState);

            // Exploration en profondeur
            while (!stack.empty()) {

                State currentState = stack.back();
                stack.pop_back();

                // Exécute la logique de traitement de l’état
                currentState.run(stack, *this, gaddag, lbag);
            }
        }
    }
}


Spot& Board::getSpotAt(int row, int col) {
    return spots[row * 15 + col];
}

const Spot& Board::getSpotAt(int row, int col) const {
    return spots[row * 15 + col];
}

void Board::addWordToNextWords(const std::vector<Position>& word,  const letterBag& lbag, Direction dir) {


    int score = calculateWordScore(word, lbag,dir);

    if (nextWords.empty() || score > nextWords[0].score) {
        nextWords.clear();
        nextWords.emplace_back(word, score);
    } else if (score == nextWords[0].score) {
        nextWords.emplace_back(word, score); // garder toutes les options avec le même score
    }
}

/*

int Board::calculateWordScore(const std::vector<Position>& word, const letterBag& lbag) const {
    int score = 0;
    for (const auto& pos : word) {
        //const Spot& spot = getSpotAt(pos.getRow(), pos.getCol());//pas correcte à revoir
        score += lbag.getLetterPoints(pos.getLetter());
        //score += lbag.getpol etterPoints(spot.letter); // ou spot.getScore(), selon le design
    }
    return score;
}
*/

/*
int Board::calculateWordScore(const std::vector<Position>& word, const letterBag& lbag) const {
  int totalScore = 0;
  int wordMultiplier = 1;

  for (const Position& pos : word) {
      const Spot& spot = getSpotAt(pos.getRow(), pos.getCol());
      char letter = spot.getLetter();
      int letterScore = lbag.getLetterPoints(letter);

      if (pos.isFromInit()) {
          // Existing letter on the board: no bonuses
          totalScore += letterScore;
      } else {
          // New letter: apply letter multiplier and collect word multipliers
          totalScore += letterScore * spot.bonus.letter_factor;
          wordMultiplier *= spot.bonus.word_factor;
      }
  }

  return totalScore * wordMultiplier;
}
*/

int Board::calculateWordScore(const std::vector<Position>& word, const letterBag& lbag, Direction dir) const {
    int totalScore = 0;
    int wordMultiplier = 1;

    // Parcourt chaque lettre du mot principal
    for (const Position& pos : word) {
        const Spot& spot = getSpotAt(pos.getRow(), pos.getCol());
        int letterValue = lbag.getLetterPoints(pos.getLetter());

        if (spot.getLetter() == 0) { // Nouvelle lettre jouée
            // Appliquer le bonus de lettre
            letterValue *= spot.bonus.letter_factor;
            // Accumuler le multiplicateur de mot
            wordMultiplier *= spot.bonus.word_factor;
        }

        totalScore += letterValue;

        // ========== GESTION DES MOTS PERPENDICULAIRES ==========
        // Si cette lettre est nouvelle, on vérifie s’il y a un mot perpendiculaire à scorer
        if (spot.getLetter() == 0) {
            std::vector<Position> perpendicularWord;

            // Déterminer la direction perpendiculaire
            Direction perpDir = (dir == HORIZONTAL) ? VERTICAL : HORIZONTAL;

            // Étendre vers l'arrière
            int row = pos.getRow();
            int col = pos.getCol();

            while (true) {
                int r = (perpDir == VERTICAL) ? row - 1 : row;
                int c = (perpDir == HORIZONTAL) ? col - 1 : col;

                if (!isInBoard(r, c)) break;
                if (getSpotAt(r, c).getLetter() == 0) break;

                row = r;
                col = c;
            }

            // Repartir depuis le début du mot perpendiculaire
            int perpendicularScore = 0;
            int wordMult = 1;

            while (isInBoard(row, col)) {
                Spot s;
                if (row == pos.getRow() && col == pos.getCol()) {
                    s.letter = pos.getLetter(); // lettre posée temporairement
                } else {
                    s = getSpotAt(row, col);
                    if (s.getLetter() == 0) break;
                }

                Position p(row, col, s);

                // Calculer le score de cette lettre
                int val = lbag.getLetterPoints(p.getLetter());
                if (s.getLetter() == 0) { // Lettre posée, bonus applicable
                    val *= s.bonus.letter_factor;
                    wordMult *= s.bonus.word_factor;
                }

                perpendicularScore += val;
                perpendicularWord.push_back(p);

                // Aller à la case suivante
                if (perpDir == VERTICAL)
                    row++;
                else
                    col++;
            }

            // Si on a formé un mot secondaire (au moins deux lettres)
            if (perpendicularWord.size() > 1) {
                totalScore += perpendicularScore * wordMult;
            }
        }
    }

    // Appliquer le multiplicateur principal au total du mot
    return totalScore * wordMultiplier;
}



void Board::printNextWords() const {
    for (const auto& sw : nextWords) {
        std::cout << "Mot (score " << sw.score << ") : ";
        for (const auto& pos : sw.positions) {
            std::cout << pos.getLetter() << " ";
        }
        std::cout << std::endl;
    }
}

bool Board::isInBoard(char row, char col) const {
    return row >=0 && row < 15 && col >= 0 && col < 15;
}

const std::vector<ScoredWord>& Board::getNextWords() const {
  return nextWords;
}

void Board :: setPlayerLetters(const PlayerLetters& pl){
  playerLetters = pl;
}

