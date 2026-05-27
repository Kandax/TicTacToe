#pragma once

#include <iostream>
#include <functional>

#include <SFML/Graphics.hpp>

#include "Core/Context.h"
#include "Core/State.h"
#include "Core/StateMachine.h"

#include "State/GameSetupState.h"
#include "Core/GameConfig.h"

#include "UI/Button.h"
#include "UI/Colors.h"



class MenuState : public State {
public:
	MenuState(StateMachine& stateMachine, Context& context);
	void handleEvent(const sf::Event& e);
	void input();
	void update(float dt);
	void render();

private:
	Button m_PlayerVsAIButton;
	Button m_PlayerVsPlayerButton;
	Button m_ExitButton;
};