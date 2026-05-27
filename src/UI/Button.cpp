#include "Button.h"




Button::Button(StateMachine &stateMachine, Context& context, const sf::Vector2f& pos)
    :m_StateMachine(stateMachine)
    ,m_Context(context)
    ,m_Shape({100,100})
    ,m_Font(m_Context.resourceManager->getFont("Roboto-Variable"))
    ,m_Text(m_Font)
    ,m_Position(pos)
    ,m_Hovered()
    ,m_Pressed()
    ,m_Style()
{
    //m_Font = m_Context.resourceManager->getFont("Roboto-Variable");
    setText("TEST");
    setPosition(pos);

}
void Button::handleEvent(const sf::Event& e){
    if(const auto* mouseMoved = e.getIf<sf::Event::MouseMoved>())
    {
        sf::Vector2f mousePos(
            static_cast<float>(mouseMoved->position.x),
            static_cast<float>(mouseMoved->position.y)
        );

        m_Hovered = isMouseOver(mousePos);
    }

    if(const auto* mousePressed= e.getIf<sf::Event::MouseButtonPressed>())
    {
        if(m_Hovered)
            m_Pressed = true;
    }

    if(const auto* mouseReleased= e.getIf<sf::Event::MouseButtonReleased>())
    {
        if(m_Pressed && m_Hovered)
        {
            if(m_OnClick)
                m_OnClick();
        }

        m_Pressed = false;
    }
}
void Button:: update(float dt){
    if(m_Pressed){
        // Pressed
        m_Shape.setFillColor(m_Style.pressedColor);
    }
    else if(m_Hovered){
        // Hovered
        m_Shape.setFillColor(m_Style.hoverColor);
    }else{
        // Normal
        m_Shape.setFillColor(m_Style.normalColor);
    }
}
void Button::render(){
    
    m_Context.window->draw(m_Shape);
    m_Context.window->draw(m_Text);
}

void Button::setPosition(const sf::Vector2f pos){
    m_Position = pos;
    m_Shape.setPosition(pos);
    /*
    m_Text.setPosition({
        pos.x + (m_Shape.getSize().x/2) - (m_Text.getGlobalBounds().size.x/2),
        pos.y + (m_Shape.getSize().y/2) - (m_Text.getGlobalBounds().size.y/2)
    });
    */

    sf::FloatRect textBounds = m_Text.getLocalBounds();
    m_Text.setOrigin({
        textBounds.getCenter().x,
        textBounds.getCenter().y
    });

    m_Text.setPosition({
        pos.x + m_Shape.getSize().x / 2.f,
        pos.y + m_Shape.getSize().y / 2.f
    });
}
void Button::setCallback(std::function<void()> callback){
    m_OnClick = callback;
}
void Button::setStyle(const ButtonStyle& style){
    m_Style.disabledColor = style.disabledColor;
    m_Style.hoverColor = style.hoverColor;
    m_Style.normalColor = style.normalColor;
    m_Style.outlineColor = style.outlineColor;
    m_Style.pressedColor = style.pressedColor;
    m_Style.textColor = style.textColor;
    m_Style.outlineThickness = style.outlineThickness;
    m_Style.buttonSize = style.buttonSize;

    m_Shape.setOutlineThickness(m_Style.outlineThickness);
    m_Shape.setFillColor(m_Style.normalColor);
    m_Shape.setOutlineColor(m_Style.outlineColor);
    m_Shape.setSize(m_Style.buttonSize);

    m_Text.setFillColor(m_Style.textColor);

}


void Button::setText(const std::string& text){
    m_Text.setString(text);
    sf::FloatRect textBounds = m_Text.getLocalBounds();
    m_Text.setOrigin({
        textBounds.getCenter().x,
        textBounds.getCenter().y
    });
}

bool Button::isMouseOver(const sf::Vector2f& pos) const{
    return m_Shape.getGlobalBounds().contains(pos);
}