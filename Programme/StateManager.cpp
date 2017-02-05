
#include "StateManager.h"

StateManager::StateManager()
  : m_endAsked(false)
  , m_noStateRemaining(false)
{
}

bool StateManager::ProcessEvents()
{
    return (m_noStateRemaining) ? false : m_statesList.back()->ProcessEvents();
}

bool StateManager::Calculate()
{
    return (m_noStateRemaining) ? false : m_statesList.back()->Calculate();
}

bool StateManager::Draw()
{
    return (m_noStateRemaining) ? false : m_statesList.back()->Draw();
}

void StateManager::PushState(std::shared_ptr<IState> p_state)
{
    m_statesList.push_back(p_state);
}

void StateManager::PopState(std::shared_ptr<IState> p_state)
{
    m_statesList.pop_back();
    if (m_statesList.size() == 0)
        m_noStateRemaining = true;
}
