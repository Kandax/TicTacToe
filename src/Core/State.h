#pragma once
#include <SFML/Graphics.hpp>

#include "Core/Context.h"

class StateMachine;

class State {
protected:
	StateMachine& m_StateMachine;
	Context& m_Context;
public:
	State(StateMachine& stateMachine, Context& context) :m_StateMachine(stateMachine), m_Context(context){}
	virtual void handleEvent(const sf::Event& e) = 0;
	virtual void input() = 0;
	virtual void update(float dt) = 0;
	virtual void render() = 0;
	virtual ~State() = default;


};