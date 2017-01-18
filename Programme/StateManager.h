#pragma once

#include <memory>

#include "IState.h"
class IState;

class StateManager
{
public:
	StateManager();
	bool ProcessEvents();
	bool Calculate();
	bool Draw();
	void PushState(std::shared_ptr<IState> state);
	void PopState(std::shared_ptr<IState> state);

private:
	bool m_noStateRemaining;
	bool m_endAsked;
	std::vector<std::shared_ptr<IState>> m_statesList;
	//sf::RenderWindow & m_window;
};
