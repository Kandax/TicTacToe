#pragma once

#include <iostream>
#include <functional>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Core/Context.h"
#include "Core/State.h"
#include "Core/StateMachine.h"
#include "Core/GameConfig.h"

#include "State/GameSetupState.h"

#include "UI/Button.h"
#include "UI/Colors.h"

#include "Gameplay/Board.h"


class GameplayState: public State {
public:
	GameplayState(StateMachine& stateMachine, Context& context, GameConfig gameConfig);
	void handleEvent(const sf::Event& e);
	void input();
	void update(float dt);
	void render();

private:
	void onCellClicked(int x, int y);
	void switchTurn();
	void checkWin();
	void checkDraw();

private:
	Board m_Board;

	GameConfig m_GameConfig;

	std::vector<Button> m_BoardButtons;
	Button m_GoBackButton;
	sf::Text m_WinnerText;

	Cell m_CurrentPlayer;

	bool m_IsGameOver;
	Cell m_Winner;
};