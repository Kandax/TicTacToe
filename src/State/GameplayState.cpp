#include "GameplayState.h"

GameplayState::GameplayState(StateMachine& stateMachine, Context& context,GameConfig gameConfig)
	:State(stateMachine, context)
	,m_GameConfig(gameConfig)
	,m_Board(gameConfig.boardSize, gameConfig.symbolsToWin)
	,m_CurrentPlayer(Cell::O)
	,m_IsGameOver(false)
{
	std::cout << "GameplayState" << std::endl;

	ButtonStyle buttonStyle = {
    .buttonSize = {100.f, 100.f},

    .normalColor   = sf::Color(37, 43, 51),   // #252B33
    .hoverColor    = sf::Color(49, 56, 68),   // #313844
    .pressedColor  = sf::Color(27, 31, 36),   // #1B1F24
    .disabledColor = sf::Color(59, 68, 82),   // #3B4452

    .textColor     = sf::Color(245, 247, 250), // #F5F7FA

    .outlineThickness = 1.f,
    .outlineColor     = sf::Color(59, 68, 82)  // #3B4452
	};

	for(int y = 0; y < m_GameConfig.boardSize; y++){
    	for(int x= 0; x < m_GameConfig.boardSize; x++)
		{
			float tx = x*100;
			float ty = y*100;
			m_BoardButtons.push_back(Button(m_StateMachine,m_Context, {tx,ty}));
			m_BoardButtons.back().setStyle(buttonStyle);
			m_BoardButtons.back().setText("");
			m_BoardButtons.back().setCallback([this,x,y](){
				onCellClicked(x, y);
			});

		}
	}
}

void GameplayState::handleEvent(const sf::Event& e){
	for(auto& button : m_BoardButtons){
		button.handleEvent(e);
	}
}

void GameplayState::input()
{
}

void GameplayState::update(float dt)
{
	for(auto& button : m_BoardButtons){
		button.update();
	}
}

void GameplayState::render()
{
	for(auto& button : m_BoardButtons){
		button.render();
	}
}


void GameplayState::onCellClicked(int x, int y){
	std::cout<<"x: "<<x<<" y: "<<y<<std::endl;

	if(m_Board.placeSymbol(x,y,m_CurrentPlayer) && !m_IsGameOver){
		if(m_CurrentPlayer == Cell::X){
			m_BoardButtons[x + y*m_GameConfig.boardSize].setText("X");
		}else if(m_CurrentPlayer == Cell::O){
			m_BoardButtons[x + y*m_GameConfig.boardSize].setText("O");
		}
		checkWin();
		switchTurn();

	}
	

	
}


void GameplayState::switchTurn(){
	if(m_CurrentPlayer == Cell::O){
		m_CurrentPlayer = Cell::X;
	}else if(m_CurrentPlayer == Cell::X){
		m_CurrentPlayer = Cell::O;
	}
	
}



void GameplayState::checkWin(){
	Cell won = m_Board.checkWin();
	if(won == Cell::O){
		m_Winner = Cell::O;
		m_IsGameOver = true;
		std::cout<<"Won O"<<std::endl;
		return;
	}else if(won == Cell::X){
		m_Winner = Cell::X;
		m_IsGameOver = true;
		std::cout<<"Won X"<<std::endl;
		return;
	}

	if(m_Board.checkDraw()){
		m_Winner = Cell::None;
		m_IsGameOver = true;
		std::cout<<"DRAW"<<std::endl;
	}
}

void GameplayState::checkDraw(){
	bool isDraw = m_Board.checkDraw();
	if(isDraw){
		m_Winner = Cell::None;
		m_IsGameOver = true;
	}
}