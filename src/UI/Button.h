#pragma once

#include "SFML/Graphics.hpp" 

#include "Core/Context.h"
#include "Core/StateMachine.h"

struct ButtonStyle
{
    sf::Vector2f buttonSize = {50.f,50.f};

    sf::Color normalColor = sf::Color::Blue;
    sf::Color hoverColor = sf::Color::Yellow;
    sf::Color pressedColor = sf::Color::Green;
    sf::Color disabledColor = sf::Color::Red;

    sf::Color textColor = sf::Color::White;

    float outlineThickness = 0.f;
    sf::Color outlineColor = sf::Color::Magenta;
};

class Button{
public:
    

    enum class ButtonState
    {
        Normal,
        Hovered,
        Pressed,
        Disabled
    };


    Button(StateMachine &stateMachine, Context& context, const sf::Vector2f& pos);
    void handleEvent(const sf::Event& e);
    void update(float dt = 0);
    void render();

    void setPosition(const sf::Vector2f pos);
    void setCallback(std::function<void()> callback);
    void setStyle(const ButtonStyle& style);
    void setText(const std::string& text);

private:
    bool isMouseOver(const sf::Vector2f& pos) const;


private:
    StateMachine& m_StateMachine;
    Context& m_Context;

    sf::RectangleShape m_Shape;
    sf::Font& m_Font;
    sf::Text m_Text;
    sf::Vector2f m_Position;

    bool m_Hovered;
    bool m_Pressed;

    std::function<void()> m_OnClick;

    ButtonStyle m_Style;
    ButtonState m_State;

    
};