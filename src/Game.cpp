#include "Game.h"

Game::Game()
:WINDOW_WIDTH(1200)
,WINDOW_HEIGHT(720)
,WINDOW_TITLE("Tic Tac Toe")
,m_IsRunning(true)
,m_Window(sf::VideoMode({WINDOW_WIDTH,WINDOW_HEIGHT}), WINDOW_TITLE)
,m_Context({&m_Window,&m_ResourceManager, {0,0},&m_IsRunning})
{
    m_ResourceManager.loadFont("Roboto-Variable", "assets/fonts/Roboto-Variable.ttf");
    //m_StateMachine.changeState(std::make_unique<MenuState>(m_StateMachine,m_Context));
    m_StateMachine.changeState(std::make_unique<GameSetupState>(m_StateMachine,m_Context,m_GameConfig));
}

Game::~Game(){

}

void Game::run(){
    while(m_IsRunning){
        processEvent();
        input();
        update(m_Time.deltaTime);
        render();
        m_Time.runAtFps();
    }
}

void Game::processEvent(){
    while (const std::optional event = m_Window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            m_IsRunning = false;
        }
        m_StateMachine.handelEvent(*event);
    }
}

void Game::input(){
    m_StateMachine.input();
}

void Game::update(float dt){
    m_StateMachine.update(dt);
}

void Game::render(){
    m_Window.clear(sf::Color(27,31,36)); // #121417 #1B1F24
    m_StateMachine.render();
    m_Window.display();
}
