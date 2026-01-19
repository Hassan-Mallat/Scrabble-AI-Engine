#include "board.hpp"
#include "letterBag.hpp"
#include "playerletters.hpp"
#include "gaddag.hpp"
#include <cstdlib>
#include <iostream>
#include <sstream>


/*
int main() {
  //srand(time(NULL));// On initialise une fois pour toute

    Gaddag* gaddag = new Gaddag();
    gaddag->loadDictionary("dico.txt");

       //gaddag->display();

  letterBag* ba = new letterBag();
   PlayerLetters* p = new PlayerLetters();
   p->addLetters(*ba);
   p->displayLetters();
  Board b ;

  std::cout << b << std::endl ;

  std::stringstream ss ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "....PROJET....." << std::endl ;
  ss << ".......O......." << std::endl ;
  ss << ".......U......." << std::endl ;
  ss << ".......E......." << std::endl ;
  ss << ".......U......." << std::endl ;
  ss << ".....SCRABBLE.." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;

  b.load(ss) ;

    std::vector<Position> pa;
    b.freeNeighborSpots(pa);
    for(auto element:pa) {
      std::cout << element.getCol() << " - " << element.getRow() << std::endl;
    }

  std::cout << b << std::endl ;

  return 0 ;
}
*/

/*
int main() {
  // Initialize board and letter bag
  Board board;
  letterBag lbag;

  // Define the word "CHAT" placed at positions (7,7) to (7,10)
  std::vector<Position> word;

  // Place 'C'
  board.getSpotAt(7, 7).letter = 'C';
  word.emplace_back(7, 7, board.getSpotAt(7, 7), false);

  // Place 'H'
  board.getSpotAt(7, 8).letter = 'H';
  word.emplace_back(7, 8, board.getSpotAt(7, 8), false);

  // Place 'A'
  board.getSpotAt(7, 9).letter = 'A';
  word.emplace_back(7, 9, board.getSpotAt(7, 9), false);

  // Place 'T'
  board.getSpotAt(7, 10).letter = 'T';
  word.emplace_back(7, 10, board.getSpotAt(7, 10), false);

  // Debug print
  std::cout << "---- Word Debug ----" << std::endl;

  int baseScore = 0;
  int wordMultiplier = 1;

  for (const auto& pos : word) {
      const Spot& spot = board.getSpotAt(pos.getRow(), pos.getCol());
      int letterScore = lbag.getLetterPoints(spot.letter);
      baseScore += letterScore * spot.bonus.letter_factor;
      wordMultiplier *= spot.bonus.word_factor;

      std::cout << "Letter: " << spot.letter
                << ", Base Score: " << letterScore
                << ", Bonus x" << spot.bonus.letter_factor
                << ", Word Bonus x" << spot.bonus.word_factor
                << ", Position: (" << pos.getRow() << "," << pos.getCol() << ")"
                << ", fromInit: " << pos.isFromInit()
                << std::endl;
  }

  int finalScore = baseScore * wordMultiplier;

  std::cout << "Score (before multiplier): " << baseScore << std::endl;
  std::cout << "Word multiplier: " << wordMultiplier << std::endl;
  std::cout << "Final score: " << finalScore << std::endl;
  std::cout << "---------------------" << std::endl;

  // Or use your actual scoring function:
  // int score = board.calculateWordScore(word, lbag);
  // std::cout << "Score for word CHAT: " << score << std::endl;

  return 0;
}
*/

/*
int main() {

  letterBag lbag; // ← ✔️ C’est ça qui te manquait !
  PlayerLetters pl;
  Board board;


  // Tu peux soit tirer aléatoirement :
  
  pl.addLetters(lbag);  // Tire jusqu’à 7 lettres
  board.setPlayerLetters(pl);
  
  pl.displayLetters();

  
  board.setPlayerLetters(pl);  // ✔️ maintenant ça marche

  Gaddag gaddag;
  gaddag.loadDictionary("/home/fluffkin/univ/complexite/scrab/almostDone/dico.txt");

  board.search(gaddag.getRootNode(), gaddag, lbag);

  board.printNextWords();  // Affiche les meilleurs coups trouvés

  return 0;
}*/



int main() {
  std::cout << "No previous state found. Initializing default values." << std::endl;

  // 1. Charger le dictionnaire
  Gaddag gaddag;


  gaddag.loadDictionary("dico.txt"); // Assure-toi que le fichier est bien là

  // 2. Initialiser le sac de lettres
  letterBag lbag;

  // 3. Initialiser les lettres du joueur
  PlayerLetters pl;
  pl.addLetters(lbag);
  pl.displayLetters();

  // 4. Préparer le plateau
  Board board;

  std::cout << board << std::endl ;

  std::stringstream ss ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "....PROJET....." << std::endl ;
  ss << ".......O......." << std::endl ;
  ss << ".......U......." << std::endl ;
  ss << ".......E......." << std::endl ;
  ss << ".......U......." << std::endl ;
  ss << ".....SCRABBLE.." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;


  board.load(ss) ;
  board.setPlayerLetters(pl);
  std::cout << board << std::endl ;

  // 5. Lancer la recherche des mots possibles
  GaddagNode root = gaddag.getRootNode();
  board.search(root, gaddag, lbag);

  // 6. Afficher tous les meilleurs mots trouvés
  board.printNextWords();

  // 7. Afficher le meilleur mot
  if (!board.getNextWords().empty()) {
      const ScoredWord& best = board.getNextWords()[0];
      std::cout << "Meilleur coup (score " << best.score << ") : ";
      for (const Position& p : best.positions) {
          std::cout << p.getLetter();
      }
      std::cout << std::endl;
  } else {
      std::cout << "Aucun mot trouvé." << std::endl;
  }

  return 0;
}
