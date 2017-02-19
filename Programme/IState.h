#pragma once

#include <SFML/Graphics.hpp>

#include "StateManager.h"
class StateManager;

class IState
{
public:
    virtual ~IState(){};

    IState(std::shared_ptr<StateManager> stateManager, sf::RenderWindow & window)
      : m_stateManager(stateManager)
      , m_window(window){};
    virtual bool ProcessEvents() = 0;
    virtual bool Calculate() = 0;
    virtual bool Draw() = 0;

protected:
    std::shared_ptr<StateManager> m_stateManager;
    sf::RenderWindow & m_window;
};
