#pragma once

#include "IState.h"
#include "Projectile.h"
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
    double m_posZGameplay;
    double m_posZBackground;
    Vector2d m_posDestroyObject;
    Ship m_ship;
    sf::Clock m_clock;
    std::vector<Projectile> m_projectiles;
};
