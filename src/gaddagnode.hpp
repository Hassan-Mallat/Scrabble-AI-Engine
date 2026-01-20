#ifndef GADDAGNODE_HPP
#define GADDAGNODE_HPP
#include<unordered_map>

class GaddagNode
{
private:
    std::unordered_map<char, GaddagNode*> children;
    bool terminal; // j'ai change du isTerminal a terminal
public:
    GaddagNode(bool _isTerminal);
    bool isTerminal() const; // j'ai change du getIsTerminal a isTerminal

    GaddagNode* getOrCreateChild(char letter, bool _isTerminal);
    void setAsTerminal();
    GaddagNode* getChild(char letter) const;
    bool hasChild(char letter) const;
    ~GaddagNode();

};

#endif // GADDAGNODE_HPP
