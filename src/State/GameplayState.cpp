#include "GameplayState.h"

GameplayState::GameplayState(StateMachine& stateMachine, Context& context,GameConfig gameConfig)
	:State(stateMachine, context)
	,m_GameConfig(gameConfig)
	,m_GoBackButton(m_StateMachine, m_Context, {0,0})
	,m_WinnerText(m_Context.resourceManager->getFont("Roboto-Variable"))
	,m_Board(gameConfig.boardSize, gameConfig.symbolsToWin)
	,m_CurrentPlayer(Cell::O)
	,m_IsGameOver(false)
	,m_IsPvAI(false)
	,m_IsTurnForPlayer(true)
{
	std::cout << "GameplayState" << std::endl;

	

	ButtonStyle buttonStyle = {
    .buttonSize = {100.f, 100.f},
	.characterSize = 30,

    .normalColor   = sf::Color(37, 43, 51),   // #252B33
    .hoverColor    = sf::Color(49, 56, 68),   // #313844
    .pressedColor  = sf::Color(27, 31, 36),   // #1B1F24
    .disabledColor = sf::Color(59, 68, 82),   // #3B4452

    .textColor     = sf::Color(245, 247, 250), // #F5F7FA

    .outlineThickness = 1.f,
    .outlineColor     = sf::Color(59, 68, 82)  // #3B4452
	};

	m_GoBackButton.setStyle(buttonStyle);
	m_GoBackButton.setText("<");
	m_GoBackButton.setTextColor(Colors::Danger);
	m_GoBackButton.setCallback([this](){
		m_StateMachine.changeState(std::make_unique<GameSetupState>(m_StateMachine,m_Context,m_GameConfig));
	});

	m_WinnerText.setPosition({50,150});
	m_WinnerText.setFillColor(Colors::Success);

	if(m_GameConfig.boardSize > 6){
		const int s = m_GameConfig.boardSize - 2; 
		// s8 10
		// s7 9
		// s6 8
		// s5 7
		// s4 6
		buttonStyle.buttonSize = {100.f / (m_GameConfig.boardSize - s), 100.f / (m_GameConfig.boardSize - s)};
		buttonStyle.characterSize = 20;
	}

	const int spacing = 10;
	const int paddingX = m_Context.window->getSize().x / 2 
						- (m_GameConfig.boardSize * (buttonStyle.buttonSize.x + spacing))/2;
	const int paddingY = m_Context.window->getSize().y / 2
						- (m_GameConfig.boardSize * (buttonStyle.buttonSize.y + spacing))/2;

	for(int y = 0; y < m_GameConfig.boardSize; y++){
    	for(int x= 0; x < m_GameConfig.boardSize; x++)
		{
			float tx = x*(buttonStyle.buttonSize.x + spacing) + paddingX;
			float ty = y*(buttonStyle.buttonSize.y + spacing) + paddingY;
			m_BoardButtons.push_back(Button(m_StateMachine,m_Context, {tx,ty}));
			m_BoardButtons.back().setStyle(buttonStyle);
			m_BoardButtons.back().setText("");
			m_BoardButtons.back().setCallback([this,x,y](){
				onCellClicked(x, y);
			});

		}
	}




	m_AI = std::make_unique<RandomAI>();

	if(m_GameConfig.gameMode == GameMode::PvAI)
		m_IsPvAI = true;





}

void GameplayState::handleEvent(const sf::Event& e){
	for(auto& button : m_BoardButtons){
		button.handleEvent(e);
	}
	m_GoBackButton.handleEvent(e);
}

void GameplayState::input()
{
}

void GameplayState::update(float dt)
{
	for(auto& button : m_BoardButtons){
		button.update();
	}

	m_GoBackButton.update();


	if(m_IsPvAI){
		if(!m_IsTurnForPlayer){
			std::optional<Move> m= m_AI->chooseMove(m_Board);
			if(m.has_value()){
				Move move = m.value();
				m_Board.placeSymbol(move.x,move.y, m_CurrentPlayer);
				if(m_CurrentPlayer == Cell::X){
					m_BoardButtons[move.x + move.y*m_GameConfig.boardSize].setText("X");
					m_BoardButtons[move.x + move.y*m_GameConfig.boardSize].setTextColor(Colors::XColor);
				}else if(m_CurrentPlayer == Cell::O){
					m_BoardButtons[move.x + move.y*m_GameConfig.boardSize].setText("O");
					m_BoardButtons[move.x + move.y*m_GameConfig.boardSize].setTextColor(Colors::OColor);
				}
				checkWin();
				switchTurn();

			}

		}
	}

}

void GameplayState::render()
{
	for(auto& button : m_BoardButtons){
		button.render();
	}
	m_GoBackButton.render();

	if(m_IsGameOver){
		// Render winner text
		m_Context.window->draw(m_WinnerText);
	}
}


void GameplayState::onCellClicked(int x, int y){
	std::cout<<"x: "<<x<<" y: "<<y<<std::endl;

	if(m_Board.placeSymbol(x,y,m_CurrentPlayer) && !m_IsGameOver && m_IsTurnForPlayer){
		if(m_CurrentPlayer == Cell::X){
			m_BoardButtons[x + y*m_GameConfig.boardSize].setText("X");
			m_BoardButtons[x + y*m_GameConfig.boardSize].setTextColor(Colors::XColor);
		}else if(m_CurrentPlayer == Cell::O){
			m_BoardButtons[x + y*m_GameConfig.boardSize].setText("O");
			m_BoardButtons[x + y*m_GameConfig.boardSize].setTextColor(Colors::OColor);
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
	if(m_IsPvAI){
		m_IsTurnForPlayer = !m_IsTurnForPlayer; 
	}
}



void GameplayState::checkWin(){
	Cell won = m_Board.checkWin();
	if(won == Cell::O){
		m_Winner = Cell::O;
		m_IsGameOver = true;
		m_WinnerText.setString("Wygral O!");
		std::cout<<"Won O"<<std::endl;
		return;
	}else if(won == Cell::X){
		m_Winner = Cell::X;
		m_IsGameOver = true;
		std::cout<<"Won X"<<std::endl;
		m_WinnerText.setString("Wygral X!");
		return;
	}

	if(m_Board.checkDraw()){
		m_Winner = Cell::None;
		m_IsGameOver = true;
		std::cout<<"DRAW"<<std::endl;
		m_WinnerText.setString("Remis!");
	}
}

void GameplayState::checkDraw(){
	bool isDraw = m_Board.checkDraw();
	if(isDraw){
		m_Winner = Cell::None;
		m_IsGameOver = true;
	}
}