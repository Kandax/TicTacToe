#include "GameSetupState.h"	
    
GameSetupState::GameSetupState(StateMachine& stateMachine, Context& context, const GameConfig& gameConfig)
	:State(stateMachine, context)
	,m_GameConfig(gameConfig)
	,m_BoardSizeMinusButton(m_StateMachine,m_Context,{100,100})
	,m_BoardSizePlusButton(m_StateMachine,m_Context,{100,100})
	,m_RowToWinMinusButton(m_StateMachine,m_Context,{100,100})
	,m_RowToWinPlusButton(m_StateMachine,m_Context,{100,100})
	,m_AIMinusButton(m_StateMachine,m_Context,{100,100})
	,m_AIPlusButton(m_StateMachine,m_Context,{100,100})
	,m_GoBackButton(m_StateMachine,m_Context,{100,100})
	,m_PlayButton(m_StateMachine,m_Context,{100,100})
	,m_BoardSizeText(m_Context.resourceManager->getFont("Roboto-Variable"),"Rozmiar planszy")
	,m_BoardSizeValueText(m_Context.resourceManager->getFont("Roboto-Variable"), std::to_string(m_GameConfig.boardSize))
	,m_RowToWinText(m_Context.resourceManager->getFont("Roboto-Variable"),"ilosc w rzedzie")
	,m_RowToWinValueText(m_Context.resourceManager->getFont("Roboto-Variable"), std::to_string(m_GameConfig.symbolsToWin))
	,m_AIText(m_Context.resourceManager->getFont("Roboto-Variable"), "AI Level")
	,m_AIValueText(m_Context.resourceManager->getFont("Roboto-Variable"), std::to_string(m_GameConfig.ai.depth))
{
	// 1. board size
	// 2. symbols to win
	// 3. if ai, choose AI num

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

	float buttonMinusPosX = 450;
	float buttonPlusPosX = 650;
	float row1 = 100;
	float row2 = 200;
	float row3 = 300;

	// ------------------Board size-----------------------------
	m_BoardSizeMinusButton.setStyle(buttonStyle);
	m_BoardSizeMinusButton.setText("-");
	m_BoardSizeMinusButton.setPosition({buttonMinusPosX,row1});
	m_BoardSizeMinusButton.setCallback([this](){
		//std::cout<<"B S -"<<std::endl;
		if(m_GameConfig.boardSize > 3){
			m_GameConfig.boardSize = m_GameConfig.boardSize - 1;
		}

		if(m_GameConfig.symbolsToWin > m_GameConfig.boardSize){
			m_GameConfig.symbolsToWin = m_GameConfig.boardSize;
			m_RowToWinValueText.setString(std::to_string(m_GameConfig.symbolsToWin));
		}
		m_BoardSizeValueText.setString(std::to_string(m_GameConfig.boardSize));
	});

	m_BoardSizePlusButton.setStyle(buttonStyle);
	m_BoardSizePlusButton.setText("+");
	m_BoardSizePlusButton.setPosition({buttonPlusPosX,row1});
	m_BoardSizePlusButton.setCallback([this](){
		//std::cout<<"B S +"<<std::endl;
		if(m_GameConfig.boardSize < 10){
			m_GameConfig.boardSize = m_GameConfig.boardSize + 1;
		}
		m_BoardSizeValueText.setString(std::to_string(m_GameConfig.boardSize));
	});
	// ------------------Row To win-----------------------------
	m_RowToWinMinusButton.setStyle(buttonStyle);
	m_RowToWinMinusButton.setText("-");
	m_RowToWinMinusButton.setPosition({buttonMinusPosX,row2});
	m_RowToWinMinusButton.setCallback([this](){
		//std::cout<<"Rtw -"<<std::endl;
		if(m_GameConfig.symbolsToWin > 3){
			m_GameConfig.symbolsToWin = m_GameConfig.symbolsToWin - 1;
		}
		m_RowToWinValueText.setString(std::to_string(m_GameConfig.symbolsToWin));
	});

	m_RowToWinPlusButton.setStyle(buttonStyle);
	m_RowToWinPlusButton.setText("+");
	m_RowToWinPlusButton.setPosition({buttonPlusPosX,row2});
	m_RowToWinPlusButton.setCallback([this](){
		//std::cout<<"Rtw +"<<std::endl;
		if(m_GameConfig.symbolsToWin < m_GameConfig.boardSize){
			m_GameConfig.symbolsToWin = m_GameConfig.symbolsToWin + 1;
		}
		m_RowToWinValueText.setString(std::to_string(m_GameConfig.symbolsToWin));
	});

	// ------------------AI-----------------------------
	m_AIMinusButton.setStyle(buttonStyle);
	m_AIMinusButton.setText("-");
	m_AIMinusButton.setPosition({buttonMinusPosX,row3});
	m_AIMinusButton.setCallback([this](){
		//std::cout<<"AI -"<<std::endl;
		if(m_GameConfig.ai.depth > 1){
			m_GameConfig.ai.depth = m_GameConfig.ai.depth- 1;
		}
		m_AIValueText.setString(std::to_string(m_GameConfig.ai.depth));
	});

	m_AIPlusButton.setStyle(buttonStyle);
	m_AIPlusButton.setText("+");
	m_AIPlusButton.setPosition({buttonPlusPosX,row3});
	m_AIPlusButton.setCallback([this](){
		//std::cout<<"AI +"<<std::endl;
		if(m_GameConfig.ai.depth < 10){
			m_GameConfig.ai.depth = m_GameConfig.ai.depth + 1;
		}
		m_AIValueText.setString(std::to_string(m_GameConfig.ai.depth));
	});
	// -------------Other buttons----------------------------
	buttonStyle.buttonSize = {150,70};
	m_GoBackButton.setStyle(buttonStyle);
	m_GoBackButton.setTextColor(Colors::Danger);
	m_GoBackButton.setText("Wroc");
	m_GoBackButton.setPosition({0,0});
	m_GoBackButton.setCallback([this](){m_StateMachine.changeState(std::make_unique<MenuState>(m_StateMachine,m_Context));});

	buttonStyle.buttonSize = {150,70};
	m_PlayButton.setStyle(buttonStyle);
	m_PlayButton.setTextColor(Colors::Success);
	m_PlayButton.setText("Graj");
	m_PlayButton.setPosition({1200 - 150,0});
	m_PlayButton.setCallback([this](){
		//std::cout<<"play button"<<std::endl;
		m_StateMachine.changeState(std::make_unique<GameplayState>(m_StateMachine,m_Context,m_GameConfig));
	});
	/*
    sf::FloatRect textBounds = m_BoardSizeValueText.getLocalBounds();
    m_BoardSizeValueText.setOrigin({
        textBounds.getCenter().x,
        textBounds.getCenter().y
    });

	*/
	float textPosX1 = 200;
	float textPosX2 = 600;
	float textOffsetY = 30;
	float textOffsetX2 = -15;
	m_BoardSizeText.setPosition({textPosX1,row1 + textOffsetY});
	m_BoardSizeValueText.setPosition({textPosX2 + textOffsetX2,row1 + textOffsetY});
	m_RowToWinText.setPosition({textPosX1,row2 + textOffsetY});
	m_RowToWinValueText.setPosition({textPosX2 + textOffsetX2,row2 + textOffsetY});
	m_AIText.setPosition({textPosX1,row3 + textOffsetY});
	m_AIValueText.setPosition({textPosX2 + textOffsetX2,row3 + textOffsetY});
}
void GameSetupState::handleEvent(const sf::Event& e){
	m_BoardSizeMinusButton.handleEvent(e);
	m_BoardSizePlusButton.handleEvent(e);
	m_RowToWinMinusButton.handleEvent(e);
	m_RowToWinPlusButton.handleEvent(e);
	if(m_GameConfig.gameMode == GameMode::PvAI){
		m_AIMinusButton.handleEvent(e);
		m_AIPlusButton.handleEvent(e);
	}

	m_GoBackButton.handleEvent(e);
	m_PlayButton.handleEvent(e);
}
void GameSetupState::input(){
}
void GameSetupState::update(float dt){
	m_BoardSizeMinusButton.update();
	m_BoardSizePlusButton.update();
	m_RowToWinMinusButton.update();
	m_RowToWinPlusButton.update();
	if(m_GameConfig.gameMode == GameMode::PvAI){
		m_AIMinusButton.update();
		m_AIPlusButton.update();
	}
	m_GoBackButton.update();
	m_PlayButton.update();
}
void GameSetupState::render(){
	m_BoardSizeMinusButton.render();
	m_BoardSizePlusButton.render();
	m_RowToWinMinusButton.render();
	m_RowToWinPlusButton.render();
	if(m_GameConfig.gameMode == GameMode::PvAI){
		m_AIMinusButton.render();
		m_AIPlusButton.render();
	}
	m_GoBackButton.render();
	m_PlayButton.render();



	m_Context.window->draw(m_BoardSizeText);
	m_Context.window->draw(m_BoardSizeValueText);
	m_Context.window->draw(m_RowToWinText);
	m_Context.window->draw(m_RowToWinValueText);
	if(m_GameConfig.gameMode == GameMode::PvAI){
		m_Context.window->draw(m_AIText);
		m_Context.window->draw(m_AIValueText);
	}
}