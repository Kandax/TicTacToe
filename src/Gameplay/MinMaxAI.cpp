#include "MinMaxAI.h"



MinMaxAI::MinMaxAI(Cell symbol, unsigned int maxDepth)
:AI(symbol, maxDepth)
,c_WIN_SCORE(5000000)
,c_INFINITY(10000000)
,m_VisitedNodes(0)
{}

/*
std::optional<Move> MinMaxAI::chooseMove(const Board& board){

    std::vector<Move> moves = getPossibleMoves(board);

    if(moves.empty())
        return std::nullopt;

    int bestScore = -c_INFINITY;
    Move bestMove = moves[0];

    for(const Move& move : moves)
    {
        Board simulation = board;

        simulation.placeSymbol(move.x, move.y, m_Symbol);

        int score = minimax(simulation, false, 0, -c_INFINITY, c_INFINITY);

        std::cout << "Move (" << move.x << "," << move.y << ") score: " << score << std::endl;

        if(score > bestScore)
        {
            bestScore = score;
            bestMove = move;
        }
    }

    std::cout << "Best move: (" << bestMove.x << "," << bestMove.y << ") score: " << bestScore << std::endl;

    return bestMove;


}
*/

std::optional<Move> MinMaxAI::chooseMove(const Board& board){


    m_VisitedNodes = 0;




    std::vector<Move> moves = getPossibleMoves(board);

    if(moves.empty())
        return std::nullopt;

    // Run on diffrent threads 
    std::vector<std::future<int>> futures;

    for(const Move& move : moves)
    {
        futures.push_back(
            std::async(std::launch::async, [this, &board, move](){
                Board simulation = board;
                simulation.placeSymbol(move.x, move.y, m_Symbol);
                return minimax(simulation, false, 0, -c_INFINITY, c_INFINITY);
            })
        );
    }

    // collect results 
    int bestScore = -c_INFINITY;
    Move bestMove = moves[0];

    for(int i = 0; i < moves.size(); i++)
    {
        int score = futures[i].get();
        if(score > bestScore)
        {
            bestScore = score;
            bestMove = moves[i];
        }
    }


    //std::cout << "Best move: (" << bestMove.x << "," << bestMove.y << ") score: " << bestScore << std::endl;
    m_BestScore = bestScore;
    return bestMove;
}



uint64_t MinMaxAI::getVisitedNodes() const {return m_VisitedNodes;}
int MinMaxAI::getBestScore() const{return m_BestScore;}

int MinMaxAI::evaluate(const Board& board){
   
    Cell winner = board.checkWin();
    if(m_Symbol == Cell::X){
        if(winner == Cell::X)
            return c_WIN_SCORE;
        if(winner == Cell::O)
            return -c_WIN_SCORE;
    }else if(m_Symbol == Cell::O){
        if(winner == Cell::O)
            return c_WIN_SCORE;
        if(winner == Cell::X) 
            return -c_WIN_SCORE;
    }
    bool draw = board.checkDraw();
        if(draw)
            return 0;
    return 0;
}



int MinMaxAI::minimax(Board& board, bool maximizing, int depth, int alpha, int beta){


    ++m_VisitedNodes;

    int score = evaluate(board);



    if(score == c_WIN_SCORE)
        return score - depth;

    if(score == -c_WIN_SCORE)
        return score + depth;

    if(board.checkDraw())
        return 0;


    if(depth >= m_MaxDepth){
        return heuristicEvaluation(board);
    }

    if(maximizing){
        int bestScore = -c_INFINITY;
        std::vector<Move> possibleMoves;

        for(int y = 0; y < board.getSize(); y++){
            for(int x = 0; x < board.getSize(); x++){
                if(board.get(x, y) == Cell::None){
                    possibleMoves.push_back(Move({x,y}));
                }
            }
        }

        for(int i = 0; i< possibleMoves.size(); i++){
            Move move = possibleMoves[i];
            // Make move
            board.placeSymbol(move.x, move.y, m_Symbol);

            score = minimax(board, !maximizing, depth + 1, alpha, beta);


            // Undo move
            board.clearCell(move.x, move.y);

            bestScore = std::max(bestScore,score);
            alpha = std::max(alpha,score);
            if(beta <= alpha)
                break;
        }

        return bestScore;

    }else{
        int bestScore = c_INFINITY;
        std::vector<Move> possibleMoves;

        for(int y = 0; y < board.getSize(); y++){
            for(int x = 0; x < board.getSize(); x++){
                if(board.get(x, y) == Cell::None){
                    possibleMoves.push_back(Move({x,y}));
                }
            }
        }

        for(int i = 0; i< possibleMoves.size(); i++){
            Move move = possibleMoves[i];
            // Make move
            if(m_Symbol == Cell::X)
                board.placeSymbol(move.x, move.y, Cell::O);
            else if(m_Symbol == Cell::O)
                board.placeSymbol(move.x, move.y, Cell::X);

            score = minimax(board, !maximizing, depth + 1, alpha, beta);


            // Undo move
            board.clearCell(move.x, move.y);

            bestScore = std::min(bestScore,score);
            beta = std::min(beta, score);
            if(beta <= alpha)
                break;
        }

        return bestScore;
    }
}




std::vector<Move> MinMaxAI::getPossibleMoves(const Board& board){
    std::vector<Move> possibleMoves;

    for(int y = 0; y < board.getSize(); y++){
        for(int x = 0; x < board.getSize(); x++){
            if(board.get(x, y) == Cell::None){
                possibleMoves.push_back(Move({x,y}));
            }
        }
    }
    return possibleMoves;
}



/*
int MinMaxAI::evaluateWindow(int aiCount, int opponentCount) const
{
    /*
    if(aiCount > 0 && opponentCount > 0)
        return 0;

    if(aiCount == 0 && opponentCount == 0)
        return 0;

    static const int scores[] =
    {
        0,
        10,
        20,
        30,
        40,
        50,
        60,
        70,
        80,
        90,
        100,
        110,

    };

    if(aiCount > 0)
    {
        int index = std::min(aiCount, 5);
        return scores[index];
    }

    int index = std::min(opponentCount, 5);
    return -scores[index];




    // Okno zawiera oba symbole — bez wartości
    if(aiCount > 0 && opponentCount > 0)
        return 0;

    if(aiCount == 0 && opponentCount == 0)
        return 0;

    // Skala wykładnicza: 1, 10, 100, 1000...
    // żeby AI mocniej ceniła dłuższe sekwencje
    auto expScore = [](int count) -> int {
        int score = 1;
        for(int i = 0; i < count - 1; i++)
            score *= 10;
        return score;
    };

    if(aiCount > 0)
        return expScore(aiCount);

    // Sekwencje przeciwnika — zwracamy ujemny wynik
    // z wagą x2, żeby AI priorytetowo blokowała
    return -expScore(opponentCount) * 2;

}

*/

int MinMaxAI::evaluateWindow(int aiCount, int opponentCount, int symbolsToWin) const
{
    if(aiCount > 0 && opponentCount > 0)
        return 0;
    if(aiCount == 0 && opponentCount == 0)
        return 0;

    auto expScore = [](int count) -> int {
        int score = 1;
        for(int i = 0; i < count - 1; i++)
            score *= 10;
        return score;
    };

    if(aiCount > 0)
        return expScore(aiCount);

    // Sekwencja o długości winLength-1 to natychmiastowe zagrożenie
    // — karaj ją tak samo jak własną wygraną
    int opponentScore = expScore(opponentCount);
    int blockWeight = (opponentCount >= symbolsToWin - 1) ? 1000 : 3;
    return -opponentScore * blockWeight;
}



int MinMaxAI::heuristicEvaluation(const Board& board) const
{
    Cell opponent =
        (m_Symbol == Cell::X)
            ? Cell::O
            : Cell::X;

    int totalScore = 0;

    const int size = board.getSize();
    const int winLength = board.getSymbolsToWin();

    // Horiziontal 
    for(int y = 0; y < size; y++)
    {
        for(int startX = 0;
            startX <= size - winLength;
            startX++)
        {
            int aiCount = 0;
            int opponentCount = 0;

            for(int i = 0; i < winLength; i++)
            {
                std::optional<Cell> cell = board.get(startX + i, y);

                if(!cell.has_value()){
                    std::cout<<"ERROR: heurisiticEvaluation, horizontal: ("<<startX + i <<", "<<y<<")"<<std::endl;
                    return 0;
                }
                if(cell == m_Symbol)
                    aiCount++;
                else if(cell == opponent)
                    opponentCount++;
            }

            totalScore += evaluateWindow(
                aiCount,
                opponentCount,
                board.getSymbolsToWin()
            );
        }
    }

    // Pionowe
    for(int x = 0; x < size; x++)
    {
        for(int startY = 0;
            startY <= size - winLength;
            startY++)
        {
            int aiCount = 0;
            int opponentCount = 0;

            for(int i = 0; i < winLength; i++)
            {
                std::optional<Cell> cell = board.get(x, startY + i);
                if(!cell.has_value()){
                    std::cout<<"ERROR: heurisiticEvaluation, vertical: ("<<x<<", "<<startY + i<<")"<<std::endl;
                    return 0;
                }

                if(cell == m_Symbol)
                    aiCount++;
                else if(cell == opponent)
                    opponentCount++;
            }

            totalScore += evaluateWindow(
                aiCount,
                opponentCount,
                board.getSymbolsToWin()
            );
        }
    }

    // diagonal \
    
    for(int startY = 0;
        startY <= size - winLength;
        startY++)
    {
        for(int startX = 0;
            startX <= size - winLength;
            startX++)
        {
            int aiCount = 0;
            int opponentCount = 0;

            for(int i = 0; i < winLength; i++)
            {
                std::optional<Cell>cell =
                    board.get(startX + i,
                              startY + i);

                if(!cell.has_value()){
                    std::cout<<"ERROR: heurisiticEvaluation, diagonal \\: ("<<startX + i<<", "<<startY + i<<")"<<std::endl;
                    return 0;
                }
                if(cell == m_Symbol)
                    aiCount++;
                else if(cell == opponent)
                    opponentCount++;
            }

            totalScore += evaluateWindow(
                aiCount,
                opponentCount,
                board.getSymbolsToWin()
            );
        }
    }

    // /
    for(int startY = winLength - 1;
        startY < size;
        startY++)
    {
        for(int startX = 0;
            startX <= size - winLength;
            startX++)
        {
            int aiCount = 0;
            int opponentCount = 0;

            for(int i = 0; i < winLength; i++)
            {
                std::optional<Cell>cell =
                    board.get(startX + i,
                              startY - i);

                if(!cell.has_value()){
                    std::cout<<"ERROR: heurisiticEvaluation, diagonal /: ("<<startX + i<<", "<<startY - i<<")"<<std::endl;
                    return 0;
                }
                if(cell == m_Symbol)
                    aiCount++;
                else if(cell == opponent)
                    opponentCount++;
            }

            totalScore += evaluateWindow(
                aiCount,
                opponentCount,
                board.getSymbolsToWin()
            );
        }
    }

    return totalScore;
}