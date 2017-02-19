#pragma once

#include <SFML/OpenGL.hpp>

#include "IState.h"
#include "Ship.h"

class StateGame : public IState
{
public:
    virtual ~StateGame(){};

    StateGame(std::shared_ptr<StateManager> stateManager, sf::RenderWindow & window);
    virtual bool Calculate() override;
    virtual bool Draw() override;
    virtual bool ProcessEvents() override;

private:
    Ship m_ship;
    sf::Clock m_clock;
};
