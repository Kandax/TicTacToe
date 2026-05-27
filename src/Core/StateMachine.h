#pragma once
#include <memory>

#include <SFML/Graphics.hpp>
#include "State.h"

class StateMachine {
public:
	StateMachine();
	void handelEvent(const sf::Event& e);
	void input();
	void update(float dt);
	void render();

	void changeState(std::unique_ptr<State> newState);

private:
	std::unique_ptr<State> m_ActiveState;
};