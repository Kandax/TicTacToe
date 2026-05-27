#include "MenuState.h"

MenuState::MenuState(StateMachine& stateMachine, Context& context)
	:State(stateMachine, context)
	,m_PlayerVsAIButton(stateMachine,context,{100,100})
	,m_PlayerVsPlayerButton(stateMachine,context,{100,100})
	,m_ExitButton(stateMachine,context,{100,100})
{
	ButtonStyle buttonStyle = {
    .buttonSize = {300.f, 70.f},

    .normalColor   = sf::Color(37, 43, 51),   // #252B33
    .hoverColor    = sf::Color(49, 56, 68),   // #313844
    .pressedColor  = sf::Color(27, 31, 36),   // #1B1F24
    .disabledColor = sf::Color(59, 68, 82),   // #3B4452

    .textColor     = sf::Color(245, 247, 250), // #F5F7FA

    .outlineThickness = 1.f,
    .outlineColor     = sf::Color(59, 68, 82)  // #3B4452
};

	m_PlayerVsAIButton.setStyle(buttonStyle);
	m_PlayerVsAIButton.setText("Gracz vs AI");
	m_PlayerVsAIButton.setPosition({600 - 150,100});
	m_PlayerVsAIButton.setCallback([this](){
		GameConfig config;
		config.gameMode = GameMode::PvAI;
		m_StateMachine.changeState(std::make_unique<GameSetupState>(m_StateMachine,m_Context,config));
		//std::cout<<"p vs ai"<<std::endl;
	});

	m_PlayerVsPlayerButton.setStyle(buttonStyle);
	m_PlayerVsPlayerButton.setText("Gracz vs Gracz");
	m_PlayerVsPlayerButton.setPosition({600 - 150,300});
	m_PlayerVsPlayerButton.setCallback([this](){
		GameConfig config;
		config.gameMode = GameMode::PvP;
		m_StateMachine.changeState(std::make_unique<GameSetupState>(m_StateMachine,m_Context,config));
		//std::cout<<"p vs p"<<std::endl;
	});

	m_ExitButton.setStyle(buttonStyle);
	m_ExitButton.setTextColor(Colors::Danger);
	m_ExitButton.setText("Wyjscie");
	m_ExitButton.setPosition({600 - 150,600});
	m_ExitButton.setCallback([this](){(*m_Context.isRunning) = false;});

}

void MenuState::handleEvent(const sf::Event& e){

	m_PlayerVsAIButton.handleEvent(e);
	m_PlayerVsPlayerButton.handleEvent(e);
	m_ExitButton.handleEvent(e);
}

void MenuState::input()
{
}

void MenuState::update(float dt)
{
	m_PlayerVsAIButton.update();
	m_PlayerVsPlayerButton.update();
	m_ExitButton.update();
}

void MenuState::render()
{
	m_PlayerVsAIButton.render();
	m_PlayerVsPlayerButton.render();
	m_ExitButton.render();
}