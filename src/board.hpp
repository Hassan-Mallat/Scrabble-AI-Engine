#ifndef BOARD_HPP
#define BOARD_HPP

#pragma once

#include "spot.hpp"
#include "position.hpp"
#include "playerletters.hpp"
#include <iostream>
#include <vector>
#include "state.hpp"
#include "gaddag.hpp"
#include "gaddagnode.hpp"
#include "direction.hpp"
#include "scoreword.hpp"
#include "letterBag.hpp"
class State;
/* Scrabble board */

struct Board {
  //default initialization of a scrabble board
  Board() ;
  letterBag lbag;
  //i/o to files
  void save(std::ostream& out) ;
  void load(std::istream& in) ;

  //access to the spots by coordinates
  Spot operator()(unsigned char l, unsigned char c) const ;
  Spot& operator()(unsigned char l, unsigned char c) ;

  //spots are public, and can therefore also be accessed b index
  Spot spots[225] ;
  std::vector<ScoredWord> nextWords;
  //std::vector<PlayerLetters> playerLetters;
  PlayerLetters playerLetters;
  // trouver les voisins libres
  void freeNeighborSpots(std::vector<Position>& freeNeighbor);

  //On commence par vérifier si une position reste bien dans les limites du plateau.
  bool isInBounds(const Position& pos) const;


  //Spot getSpotAt(int row, int col) const;

   //“Essaie de remplacer l’appel à cette fonction par son code directement, au lieu de faire un vrai saut d’exécution.”
  Spot& getSpotAt(int row, int col);
  const Spot& getSpotAt(int row, int col) const;
  
  void search(GaddagNode gaddagRoot, Gaddag const& gaddag, const letterBag& lbag);
  void addWordToNextWords(const std::vector<Position>& word, const letterBag& lbag, Direction dir);
  int calculateWordScore(const std::vector<Position>& word, const letterBag& lbag, Direction dir) const;
  void printNextWords() const;
  bool isInBoard(char row, char col) const;
  const std::vector<ScoredWord>& getNextWords() const;
  void setPlayerLetters(const PlayerLetters& pl);
  //void setLetterBag(const letterBag& lb);
} ;

//board display on the console
std::ostream& operator<<(std::ostream& out, const Board& b) ;




#endif
