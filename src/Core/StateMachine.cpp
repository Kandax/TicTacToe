#include "StateMachine.h"

StateMachine::StateMachine()
{
}

void StateMachine::handelEvent(const sf::Event& e)
{
	if (m_ActiveState)
		m_ActiveState->handleEvent(e);
}

void StateMachine::input()
{
	if (m_ActiveState)
		m_ActiveState->input();
}

void StateMachine::update(float dt)
{
	if (m_ActiveState)
		m_ActiveState->update(dt);
}

void StateMachine::render()
{
	if (m_ActiveState)
		m_ActiveState->render();
}

void StateMachine::changeState(std::unique_ptr<State> newState)
{
	m_ActiveState = std::move(newState);
}