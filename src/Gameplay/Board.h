#pragma once

#include <vector>
#include <optional>
#include <string>

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

    std::optional<Cell> get(int x, int y) const;

    int getSize() const;

    Cell checkWin();
    bool checkDraw();

private:
    Cell checkWinHorizontal();
    Cell checkWinVertical();
    Cell checkWinDiagonal();


private:
    std::vector<Cell> m_Cells;

    int m_Size;
    int m_SymbolsToWin;
    std::string m_WinConX;
    std::string m_WinConO;
};