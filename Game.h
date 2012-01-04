#ifndef _GAME_H
#define _GAME_H

#include <vector>
#include <string>
#include <set>
#include <queue>
#include <stack>

#include "Board.h"
#include "Node.h"

class Game
{
public:
    Game(std::vector<std::string> s)
        {
            if (s.size() < 2)
                throw InitException();
            else  {
                int rows = s.size();
                int cols = s[0].length();
                if (cols < 2)
                    throw InitException();
                else {
                    Board * board = new Board(rows, cols);
                    for (int i = 0; i < rows; i++)
                        if (s[i].length() != cols)
                            throw InitException();
                        else
                            for (int j = 0; j < cols; j++) {
                                board->setCell(s[i][j], i, j);
                                validMoves.insert(s[i][j]);
                            }
                    root = new Node(board);
                }
            }
        }
    std::string solve()
        {
            DFS(root,15);
            return "";
        }
    void print(Board * b)
        {
            int rows = b->size().first;
            int cols = b->size().second;
            for (int j = 0; j < cols+2; j++)
                std::cout << "-";
            std::cout << std::endl;
            for (int i = 0; i < rows; i++) {
                std::cout << "|";
                for (int j = 0; j < cols; j++)
                    std::cout << b->getCell(i,j);
                std::cout << "|" << std::endl;
            }
            for (int j = 0; j < cols+2; j++)
                std::cout << "-";
            std::cout << std::endl;
        }
private:
    bool isGoalNode(Node * node)
        {
            Board * b = node->getBoard();
            int rows = b->size().first;
            int cols = b->size().second;
            char firstCell = b->getCell(0,0);
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    if (b->getCell(i, j) != firstCell)
                        return false;
            return true;
        }
    bool BFS(Node * root)
        {
            std::queue<Node *> frontier;
            frontier.push(root);
            while (!frontier.empty()) {
                Node * node = frontier.front(); frontier.pop();
                print(node->getBoard());
                if (isGoalNode(node))
                    return true;
                Board * board = node->getBoard();
                for (std::set<char>::iterator it = validMoves.begin();
                     it != validMoves.end(); it++) {
                    Board * newBoard = new Board(*board);
                    if (makeMove(*it, newBoard)) {
                        Node * newNode = new Node(newBoard, node);
                        node->addChild(newNode);
                        frontier.push(newNode);
                    }
                }
            }
            return false;
        }
    bool DFS(Node * root, int d)
        {
            std::stack<Node *> frontier;
            frontier.push(root);
            while (!frontier.empty()) {
                Node * node = frontier.top(); frontier.pop();
                print(node->getBoard());
                if (isGoalNode(node))
                    return true;
                if (frontier.size() > d) continue;
                Board * board = node->getBoard();
                for (std::set<char>::iterator it = validMoves.begin();
                     it != validMoves.end(); it++) {
                    Board * newBoard = new Board(*board);
                    if (makeMove(*it, newBoard)) {
                        Node * newNode = new Node(newBoard, node);
                        node->addChild(newNode);
                        frontier.push(newNode);
                    }
                }
            }
            return false;
        }
    bool mark(Board * board, int ** b, int i, int j, char color)
        {
            int rows = board->size().first;
            int cols = board->size().second;
            if (i >= rows && j >= cols) return false;
            char first = board->getCell(0,0);
            char cur = board->getCell(i,j);
            if (cur == first) {
                bool ret = false;
                if (i < rows - 1)
                    ret |= mark(board, b, i+1, j, color);
                if (j < cols - 1)
                    ret |= mark(board, b, i, j+1, color);
                b[i][j] = 1;
                return ret;
            }
            else if (cur == color)
                return true;
            else return false;
        }
    bool makeMove(char move, Board * board)
        {
            if (move == board->getCell(0,0))
                return false;
            int rows = board->size().first;
            int cols = board->size().second;
            int ** b = new int* [rows];
            for (int i = 0; i < rows; i++) {
                b[i] = new int [cols];
                for (int j = 0; j < cols; j++)
                    b[i][j] = 0;
            }
            bool ret = mark(board, b, 0, 0, move);
            if (ret)
                for (int i = 0; i < rows; i++)
                    for (int j = 0; j < cols; j++)
                        if (b[i][j] == 1)
                            board->setCell(move,i,j);

            for (int i = 0; i < rows; i++)
                delete [] b[i];
            delete [] b;

            return ret;
        }
    Node * root;
    std::set<char> validMoves;
};

#endif
