#ifndef _NODE_H
#define _NODE_H

#include <vector>

#include "Exceptions.h"

class Node
{
public:
    Node(Board * board, Node * parent=NULL)
        {
            if (board == NULL)
                throw InternalException();
            else {
                this->board = board;
                this->parent = parent;
            }
        }
    void addChild(Node * child)
        {
            if (child == NULL)
                throw InternalException();
            else {
                child->setParent(this);
                children.push_back(child);
            }
        }
    std::vector<Node *> getChildren() const
        {
            return children;
        }
    Node * getParent() const
        {
            return parent;
        }
    void setParent(Node * parent)
        {
            this->parent = parent;
        }
    Board * getBoard() const
        {
            return board;
        }
private:
    Board * board;
    Node * parent;
    std::vector<Node *> children;
};

#endif
