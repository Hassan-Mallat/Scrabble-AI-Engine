#include "gaddagnode.hpp"

GaddagNode::GaddagNode(bool _isTerminal) : terminal(_isTerminal){}

bool GaddagNode::isTerminal() const {
    return terminal;
}

GaddagNode* GaddagNode::getOrCreateChild(char letter, bool _isTerminal) {
   // Créer un nouveau nœud et l'ajouter
   if (children.find(letter) == children.end()) {
      children[letter] = new GaddagNode(_isTerminal);  // Création du nœud suivant
      return children[letter];
   }
   return children[letter];
}

void GaddagNode::setAsTerminal() {
    terminal = true;
}



bool GaddagNode::hasChild(char letter) const {
     return children.find(letter) != children.end();
}

GaddagNode::~GaddagNode(){
   //for (auto& pair : children) {
     //  delete pair.second;
       //pair.second = nullptr;
   //}
    //children.clear();
}

/*
GaddagNode* GaddagNode::getChild(char letter) const {
    if (children.find(letter) == children.end()) {
        return children[letter];
    } else {
        return nullptr;
    }
}
*/
GaddagNode* GaddagNode::getChild(char letter) const {
    auto it = children.find(letter);
    if (it != children.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}
