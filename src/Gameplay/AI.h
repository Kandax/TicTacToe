#pragma once 

#include <optional>

#include "Board.h"
#include "Move.h"


class AI{
public:
    AI(Cell symbol, unsigned int maxDepth) :m_Symbol(symbol), m_MaxDepth(maxDepth) {}

    virtual std::optional<Move> chooseMove(const Board& board) = 0;
    virtual ~AI() = default;

protected:
    Cell m_Symbol;
    unsigned int m_MaxDepth;
};