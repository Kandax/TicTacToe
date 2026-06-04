#include "Board.h"


Board::Board(int size, int symbolsToWin)
:m_Size(size)
,m_Cells(size*size,Cell::None)
,m_SymbolsToWin(symbolsToWin)
,m_WinConO(m_SymbolsToWin,'O')
,m_WinConX(m_SymbolsToWin,'X' )
{
}

bool Board::placeSymbol(int x, int y, Cell value){
    if( x >= 0 && x < m_Size &&
        y >= 0 && y < m_Size &&
        m_Cells[x + m_Size*y] == Cell::None){
            m_Cells[x + m_Size*y] = value;
            return true;
        }
    return false;
}

bool Board::clearCell(int x, int y){
    if( x >= 0 && x < m_Size &&
        y >= 0 && y < m_Size ){
            m_Cells[x + m_Size*y] = Cell::None;
            return true;
        }
    return false;
}



std::optional<Cell> Board::get(int x, int y) const{
    if( x >= 0 && x < m_Size &&
        y >= 0 && y < m_Size){

            return m_Cells[x + m_Size*y];
        }
    return  std::nullopt;
}

int Board::getSize() const{ return m_Size; }



int Board::getSymbolsToWin() const{ return m_SymbolsToWin;}



Cell Board::checkWin() const{
    Cell isWon = checkWinHorizontal();
    if(isWon != Cell::None){
        std::cout << "Win detected: Horizontal" << std::endl;
        return isWon;
    }

    isWon = checkWinVertical();
    if(isWon != Cell::None){
        std::cout << "Win detected: Vertical" << std::endl;
        return isWon;
    }

    isWon = checkWinDiagonal();

    if(isWon != Cell::None){
        std::cout << "Win detected: Diagonal" << std::endl;
        return isWon;
    }
    return Cell::None;
}

bool Board::checkDraw() const{
    bool isDraw = true;
    for(int i = 0; i< m_Size*m_Size; i++){
        if(m_Cells[i] == Cell::None){
            isDraw = false;
        }
    }
    return isDraw;
}


Cell Board::checkWinHorizontal() const{

    

    for(int y = 0; y < m_Size; y++){
        std::string horizontal = "";
        for(int x = 0; x < m_Size; x++){
            if(m_Cells[x + m_Size*y] == Cell::None){
                horizontal.append("-");
            }
            else if(m_Cells[x + m_Size*y] == Cell::X){
                horizontal.append("X");
            }
            else if(m_Cells[x + m_Size*y] == Cell::O){
                horizontal.append("O");
            }

        }

        std::size_t found = horizontal.find(m_WinConO);
        if(found != std::string::npos)
            return Cell::O;
        found = horizontal.find(m_WinConX);
        if(found != std::string::npos)
            return Cell::X;
    }
    return Cell::None;
}


Cell Board::checkWinVertical() const{

    for(int x = 0; x < m_Size; x++){
        std::string vertical = "";

        for(int y = 0; y < m_Size; y++){
            if(m_Cells[x + m_Size*y] == Cell::None){
                vertical.append("-");
            }
            else if(m_Cells[x + m_Size*y] == Cell::X){
                vertical.append("X");
            }
            else if(m_Cells[x + m_Size*y] == Cell::O){
                vertical.append("O");
            }
        }

        std::size_t found = vertical.find(m_WinConO);
        if(found != std::string::npos)
            return Cell::O;

        found = vertical.find(m_WinConX);
        if(found != std::string::npos)
            return Cell::X;
    }

    return Cell::None;
}



Cell Board::checkWinDiagonal() const{

    // \ direction 
    for(int startX = 0; startX < m_Size; startX++){
        std::string diagonal = "";

        int x = startX;
        int y = 0;

        while(x < m_Size && y < m_Size){

            if(m_Cells[x + m_Size*y] == Cell::None){
                diagonal.append("-");
            }
            else if(m_Cells[x + m_Size*y] == Cell::X){
                diagonal.append("X");
            }
            else if(m_Cells[x + m_Size*y] == Cell::O){
                diagonal.append("O");
            }

            x++;
            y++;
        }

        if(diagonal.find(m_WinConO) != std::string::npos)
            return Cell::O;

        if(diagonal.find(m_WinConX) != std::string::npos)
            return Cell::X;
    }

    for(int startY = 1; startY < m_Size; startY++){
        std::string diagonal = "";

        int x = 0;
        int y = startY;

        while(x < m_Size && y < m_Size){

            if(m_Cells[x + m_Size*y] == Cell::None){
                diagonal.append("-");
            }
            else if(m_Cells[x + m_Size*y] == Cell::X){
                diagonal.append("X");
            }
            else if(m_Cells[x + m_Size*y] == Cell::O){
                diagonal.append("O");
            }

            x++;
            y++;
        }

        if(diagonal.find(m_WinConO) != std::string::npos)
            return Cell::O;

        if(diagonal.find(m_WinConX) != std::string::npos)
            return Cell::X;
    }

    // / direction 
    for(int startX = 0; startX < m_Size; startX++){
        std::string diagonal = "";

        int x = startX;
        int y = 0;

        while(x >= 0 && y < m_Size){

            if(m_Cells[x + m_Size*y] == Cell::None){
                diagonal.append("-");
            }
            else if(m_Cells[x + m_Size*y] == Cell::X){
                diagonal.append("X");
            }
            else if(m_Cells[x + m_Size*y] == Cell::O){
                diagonal.append("O");
            }

            x--;
            y++;
        }

        if(diagonal.find(m_WinConO) != std::string::npos)
            return Cell::O;

        if(diagonal.find(m_WinConX) != std::string::npos)
            return Cell::X;
    }

    for(int startY = 1; startY < m_Size; startY++){
        std::string diagonal = "";

        int x = m_Size - 1;
        int y = startY;

        while(x >= 0 && y < m_Size){

            if(m_Cells[x + m_Size*y] == Cell::None){
                diagonal.append("-");
            }
            else if(m_Cells[x + m_Size*y] == Cell::X){
                diagonal.append("X");
            }
            else if(m_Cells[x + m_Size*y] == Cell::O){
                diagonal.append("O");
            }

            x--;
            y++;
        }

        if(diagonal.find(m_WinConO) != std::string::npos)
            return Cell::O;

        if(diagonal.find(m_WinConX) != std::string::npos)
            return Cell::X;
    }

    return Cell::None;
}