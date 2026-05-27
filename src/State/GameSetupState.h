#pragma once

#include <iostream>
#include <functional>

#include <SFML/Graphics.hpp>

#include "Core/Context.h"
#include "Core/State.h"
#include "Core/StateMachine.h"
#include "Core/GameConfig.h"

#include "State/GameplayState.h"
#include "State/MenuState.h"

#include "UI/Button.h"



class GameSetupState: public State {
public:
	GameSetupState(StateMachine& stateMachine, Context& context, const GameConfig& gameConfig);
	void handleEvent(const sf::Event& e);
	void input();
	void update(float dt);
	void render();

private:

	GameConfig m_GameConfig;

	Button m_BoardSizeMinusButton;
	Button m_BoardSizePlusButton;


	Button m_RowToWinMinusButton;
	Button m_RowToWinPlusButton;

	Button m_AIMinusButton;
	Button m_AIPlusButton;

	Button m_GoBackButton;
	Button m_PlayButton;

	sf::Text m_BoardSizeText;
	sf::Text m_BoardSizeValueText;
	sf::Text m_RowToWinText;
	sf::Text m_RowToWinValueText;
	sf::Text m_AIText;
	sf::Text m_AIValueText;
};