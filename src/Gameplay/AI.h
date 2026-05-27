#pragma once 

#include <optional>

#include "Board.h"
#include "Move.h"


class AI{
public:
    virtual std::optional<Move> chooseMove(const Board& board) = 0;
    virtual ~AI() = default;
};