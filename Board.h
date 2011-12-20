#ifndef _BOARD_H
#define _BOARD_H

#include <vector>
#include <utility>

#include "Exceptions.h" 

class Board
{
public:
    Board(int rows, int cols)
        {
            if (rows >= 2 && cols >= 2) {
                cells.resize(rows);
                for (int i = 0; i < rows; i++)
                    cells[i].resize(cols);
            }
            else
                throw InitException();
        }
    char getColorOfCell(int row, int col) const
        {
            if (row >= 0 && row < cells.size() && col >= 0 && col < cells[0].size())
                return cells[row][col];
            else
                throw InternalException();
        }
    void setColorOfCell(char color, int row, int col)
        {
            if (row >= 0 && row < cells.size() && col >= 0 && col < cells[0].size())
                cells[row][col] = color;
            else
                throw InternalException();
        }
    std::pair<size_t,size_t> size() const
        {
            return std::make_pair(cells.size(), cells[0].size());
        }
private:
    std::vector<std::vector<char> > cells;
};

#endif
