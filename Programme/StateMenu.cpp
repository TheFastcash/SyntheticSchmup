
#include <iostream>

#include "StateMenu.h"

StateMenu::StateMenu(std::shared_ptr<StateManager> p_stateManager, sf::RenderWindow & p_window)
	: IState(p_stateManager, p_window)
	//, hover(false)
	//, m_selectedAction(0)
{
	if (!m_font.loadFromFile("arial.ttf"))
	{
		std::cout << "FONT ERROR" << std::endl;
	}
	else
	{
		//std::cout << __func__ << std::endl;
		m_textPlay.setFont(m_font); // select the font, font is a sf::Font
		m_textPlay.setCharacterSize(50); // set the character size, in pixels, not points!
		m_textPlay.setFillColor(sf::Color::Red);// set the color
		m_textPlay.setStyle(sf::Text::Bold | sf::Text::Underlined);// set the text style
		m_textOptions.setFont(m_font); // select the font, font is a sf::Font
		m_textOptions.setCharacterSize(50); // set the character size, in pixels, not points!
		m_textOptions.setFillColor(sf::Color::Red);// set the color
		m_textOptions.setStyle(sf::Text::Bold | sf::Text::Underlined);// set the text style
		m_textQuit.setFont(m_font); // select the font, font is a sf::Font
		m_textQuit.setCharacterSize(50); // set the character size, in pixels, not points!
		m_textQuit.setFillColor(sf::Color::Red);// set the color
		m_textQuit.setStyle(sf::Text::Bold | sf::Text::Underlined);// set the text style


		m_textPlay.setString("Play");// set the string to display
		m_textOptions.setString("Options");// set the string to display
		m_textQuit.setString("Quit");// set the string to display

		m_textPlay.setPosition(50, 50);
		m_textOptions.setPosition(50, 120);
		m_textQuit.setPosition(50, 190);
	}
}

bool StateMenu::Calculate()
{
	//sf::Vector2i pos = sf::Mouse::getPosition(m_window);
	//if (pos.x > m_text.getGlobalBounds().left && pos.x < m_text.getGlobalBounds().left+m_text.getGlobalBounds().width &&
	//	pos.y > m_text.getGlobalBounds().top && pos.y < m_text.getGlobalBounds().top+m_text.getGlobalBounds().height)
	//{
	//	hover = true;
	//}
	//else
	//	hover = false;
	return true;
}

bool StateMenu::Draw()
{
	m_window.draw(m_textPlay);
	m_window.draw(m_textOptions);
	m_window.draw(m_textQuit);

	sf::Text * textSelected;
	textSelected =	(m_selectedAction == 0) ? &m_textPlay :
					(m_selectedAction == 1) ? &m_textOptions :
					(m_selectedAction == 2) ? &m_textQuit :
					&m_textPlay;

	sf::FloatRect bounds = textSelected->getGlobalBounds();
	//std::cout << bounds.height << std::endl;
	//std::cout << bounds.width << std::endl;
	//std::cout << bounds.top << std::endl;
	//std::cout << bounds.left << std::endl;
	//if (hover)
	//{
		sf::RectangleShape rect(sf::Vector2f(bounds.width+2, bounds.height+2));
		rect.setPosition(textSelected->getPosition()+sf::Vector2f(1,1));
		rect.move(2, 6);
		rect.setOutlineColor(sf::Color(200, 50, 50, 255));
		rect.setFillColor(sf::Color(0, 0, 0, 0));
		rect.setOutlineThickness(3);
		m_window.draw(rect);
	//}
	return true;
}

bool StateMenu::ProcessEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		// Window closed or escape key pressed: exit
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
			break;
		}
		// Space key pressed: play
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			    case sf::Keyboard::Space:
                case sf::Keyboard::Return:
                    m_isActionClicked = true;
                    m_actionThatHaveBeenClicked = m_selectedAction;
                    break;
                case sf::Keyboard::Up:
                    m_selectedAction = (m_selectedAction > 0) ? m_selectedAction - 1 : 0;
                    break;
                case sf::Keyboard::Down:
                    m_selectedAction = (m_selectedAction < 2) ? m_selectedAction + 1 : m_selectedAction;
                    break;
                case sf::Keyboard::Escape:
                    if (m_selectedAction == 2)
                        m_window.close();
                    else
                        m_selectedAction = 2;
                    break;
			}
		}
        //if (event.type == sf::Event::JoystickMoved)
        //{
            //switch (event.joystickMove.axis)
            //{
                //case sf::Joystick::Axis::PovX:
                    //std::cout << "joystick : " << event.joystickMove.joystickId << "(" << "PovX" << "); value : " << event.joystickMove.position << std::endl;
                    //break;
                //case sf::Joystick::Axis::PovY:
                    //std::cout << "joystick : " << event.joystickMove.joystickId << "(" << "PovY" << "); value : " << event.joystickMove.position << std::endl;
                    //break;
                //case sf::Joystick::Axis::R:
                    //std::cout << "joystick : " << event.joystickMove.joystickId << "(" << "R" << "); value : " << event.joystickMove.position << std::endl;
                    //break;
                //case sf::Joystick::Axis::U:
                    //std::cout << "joystick : " << event.joystickMove.joystickId << "(" <<"U" << "); value : " << event.joystickMove.position << std::endl;
                    //break;
                //case sf::Joystick::Axis::V:
                    //std::cout << "joystick : " << event.joystickMove.joystickId << "(" <<"V" << "); value : " << event.joystickMove.position << std::endl;
                    //break;
                //case sf::Joystick::Axis::X:
                    //std::cout << "joystick : " << event.joystickMove.joystickId << "(" << "X" << "); value : " << event.joystickMove.position << std::endl;
                    //break;
                //case sf::Joystick::Axis::Y:
                    //std::cout << "joystick : " << event.joystickMove.joystickId << "(" << "Y" << "); value : " << event.joystickMove.position << std::endl;
                    //break;
                //case sf::Joystick::Axis::Z:
                    //std::cout << "joystick : " << event.joystickMove.joystickId << "(" <<"Z" << "); value : " << event.joystickMove.position << std::endl;
                    //break;
            //}
        //}
	}
	return true;
}
