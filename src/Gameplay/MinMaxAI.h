#pragma once

#include <iostream> 

#include "AI.h"

class MinMaxAI : public AI{
public:
    MinMaxAI(Cell symbol, unsigned int maxDepth);
    std::optional<Move> chooseMove(const Board& board) override;

private:
    int evaluate(const Board& board);
    int minimax(Board& board, bool maximizing, int depth, int alpha, int beta);
    std::vector<Move> getPossibleMoves(const Board& board);

    int evaluateWindow(int aiCount, int opponentCount, int symbolsToWin) const;
    int heuristicEvaluation(const Board& board) const;
private:
    const int c_WIN_SCORE;
    const int c_INFINITY;
};