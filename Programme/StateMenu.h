#pragma once

#include <SFML/OpenGL.hpp>

#include "IState.h"

class StateMenu : public IState
{
public:
    virtual ~StateMenu(){};

    StateMenu(std::shared_ptr<StateManager> stateManager, sf::RenderWindow & window);
    virtual bool Calculate() override;
    virtual bool Draw() override;
    virtual bool ProcessEvents() override;

private:
    sf::Font m_font;
    sf::Text m_textPlay;
    sf::Text m_textOptions;
    sf::Text m_textQuit;
    /*bool hover;*/
    char m_selectedAction;
    bool m_isActionClicked;
    char m_actionThatHaveBeenClicked;
    sf::Texture m_backgroundTexture;
};
