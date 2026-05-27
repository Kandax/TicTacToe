#pragma once

#include <vector>
#include <cstdlib>

#include "AI.h"

class RandomAI : public AI{
public:
    std::optional<Move> chooseMove(const Board &board) override;

private:
    std::vector<Move> m_PossibleMoves;
};