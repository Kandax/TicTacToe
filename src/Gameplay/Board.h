#pragma once

#include <iostream>
#include <vector>
#include <optional>
#include <string>


#include "Move.h"

enum class Cell{
    None,
    X,
    O
};

class Board
{
public:
    Board(int size, int symbolsToWin);

    bool placeSymbol(int x, int y, Cell value);
    bool clearCell(int x, int y);

    std::optional<Cell> get(int x, int y) const;

    int getSize() const;
    int getSymbolsToWin() const;

    Cell checkWin() const;
    bool checkDraw() const;

private:
    Cell checkWinHorizontal() const;
    Cell checkWinVertical() const;
    Cell checkWinDiagonal() const;


private:
    std::vector<Cell> m_Cells;

    int m_Size;
    int m_SymbolsToWin;
    std::string m_WinConX;
    std::string m_WinConO;
};