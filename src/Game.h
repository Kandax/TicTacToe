#pragma once
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>


#include "Core/Context.h"
#include "Core/Time.h"
#include "Core/State.h"
#include "Core/StateMachine.h"
#include "Core/ResourceManager.h"

#include "State/MenuState.h"
#include "State/GameplayState.h"
#include "State/GameSetupState.h"



class Game {
public:

    Game();
    ~Game();
    void run();

private:

    void processEvent();
    void input();
    void update(float dt);
    void render();

private:

    const unsigned int WINDOW_WIDTH;
    const unsigned int WINDOW_HEIGHT;
    const std::string WINDOW_TITLE;

    bool m_IsRunning;
    sf::RenderWindow m_Window;

    Time m_Time;
    StateMachine m_StateMachine;
    ResourceManager m_ResourceManager;


    Context m_Context;

    GameConfig m_GameConfig;

};