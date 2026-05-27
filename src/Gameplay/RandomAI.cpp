#include "RandomAI.h"


std::optional<Move> RandomAI::chooseMove(const Board &board) {
    for(int y = 0; y < board.getSize(); y++){
        for(int x = 0; x < board.getSize(); x++){
            if(board.get(x, y) == Cell::None){
                m_PossibleMoves.push_back(Move({x,y}));
            }
        }
    }

    if(m_PossibleMoves.empty())
        return {};

    int index = rand() % m_PossibleMoves.size();
    Move move = m_PossibleMoves[index];
    m_PossibleMoves.clear();
    return move;
}