
#include <iostream>

#include "StateGame.h"
#include "StateMenu.h"

StateMenu::StateMenu(std::shared_ptr<StateManager> p_stateManager,
                     sf::RenderWindow & p_window)
  : IState(p_stateManager, p_window)
  , m_selectedAction(0)
{                                                                     // Prepare the menu
    m_textPlay.setFont(instance->font);                               // select the font, font is a sf::Font
    m_textPlay.setCharacterSize(50);                                  // set the character size, in pixels, not points!
    m_textPlay.setFillColor(sf::Color::Red);                          // set the color
    m_textPlay.setStyle(sf::Text::Bold | sf::Text::Underlined);       // set the text style
    m_textOptions.setFont(instance->font);                            // select the font, font is a sf::Font
    m_textOptions.setCharacterSize(50);                               // set the character size, in pixels, not points!
    m_textOptions.setFillColor(sf::Color::Red);                       // set the color
    m_textOptions.setStyle(sf::Text::Bold | sf::Text::Underlined);    // set the text style
    m_textQuit.setFont(instance->font);                               // select the font, font is a sf::Font
    m_textQuit.setCharacterSize(50);                                  // set the character size, in pixels, not points!
    m_textQuit.setFillColor(sf::Color::Red);                          // set the color
    m_textQuit.setStyle(sf::Text::Bold | sf::Text::Underlined);       // set the text style

    m_textPlay.setString("Play");          // set the string to display
    m_textOptions.setString("Options");    // set the string to display
    m_textQuit.setString("Quit");          // set the string to display

    m_textPlay.setPosition(50, 50);
    m_textOptions.setPosition(50, 120);
    m_textQuit.setPosition(50, 190);
}

bool StateMenu::Calculate()
{
    // sf::Vector2i pos = sf::Mouse::getPosition(m_window);
    // if (pos.x > m_text.getGlobalBounds().left && pos.x <
    // m_text.getGlobalBounds().left+m_text.getGlobalBounds().width &&
    //	pos.y > m_text.getGlobalBounds().top && pos.y <
    // m_text.getGlobalBounds().top+m_text.getGlobalBounds().height)
    //{
    //	hover = true;
    //}
    // else
    //	hover = false;
    return true;
}

bool StateMenu::Draw()
{
    // Draw the background
    glPushMatrix();
    {
        glColor3d(1, 1, 1);    // Needed, or the texture will tend to the last color chosen when drawing an other object
        sf::Texture::bind(&instance->textureMap["background"]);
        double depth = -2.;
        Vector2d limits = instance->GetXYLimits(depth);
        double right = limits.x;
        double top = limits.y;
        double left = -right;
        double bottom = -top;
        //glTranslated(0., 0., depth);
        glBegin(GL_QUADS);    //draw some squares
        {
            glTexCoord2d(0, 0);
            glVertex3d(left, top, depth);
            glTexCoord2d(1, 0);
            glVertex3d(right, top, depth);
            glTexCoord2d(1, 1);
            glVertex3d(right, bottom, depth);
            glTexCoord2d(0, 1);
            glVertex3d(left, bottom, depth);
        }
        glEnd();
        sf::Texture::bind(NULL);    // Needed, or the next shaped drown with glColor will provoke an error in the console
    }
    glPopMatrix();

    // Draw menu
    m_window.pushGLStates();
    m_window.draw(m_textPlay);
    m_window.draw(m_textOptions);
    m_window.draw(m_textQuit);

    sf::Text * textSelected;
    textSelected = (m_selectedAction == 0) ? &m_textPlay : (m_selectedAction == 1) ? &m_textOptions : (m_selectedAction == 2) ? &m_textQuit : &m_textPlay;

    sf::FloatRect bounds = textSelected->getGlobalBounds();
    sf::RectangleShape rect(sf::Vector2f(bounds.width + 2, bounds.height + 2));
    rect.setPosition(textSelected->getPosition() + sf::Vector2f(1, 1));
    rect.move(2, 6);
    rect.setOutlineColor(sf::Color(200, 50, 50, 255));
    rect.setFillColor(sf::Color(0, 0, 0, 0));
    rect.setOutlineThickness(3);
    m_window.draw(rect);
    m_window.popGLStates();
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
            //std::cout << "KeyPressed " << (int)event.key.code << std::endl;
            switch (event.key.code)
            {
                case sf::Keyboard::Space:
                case sf::Keyboard::Return:
                    if (!m_isActionClicked)    // Avoid clicking enter very quickly and push more than 1 state
                    {
                        m_isActionClicked = true;
                        m_actionThatHaveBeenClicked = m_selectedAction;
                        switch (m_actionThatHaveBeenClicked)
                        {
                            case 0:
                                m_stateManager->PushState(std::make_shared<StateGame>(m_stateManager, m_window));
                                break;
                            case 1:
                                break;
                            case 2:
                                m_stateManager->PopState();
                                break;
                        }
                    }
                    break;
                case sf::Keyboard::Up:
                    m_selectedAction = (m_selectedAction > 0) ? m_selectedAction - 1 : 0;
                    break;
                case sf::Keyboard::Down:
                    //std::cout << "KeyPressed down" << std::endl;
                    m_selectedAction = (m_selectedAction < 2) ? m_selectedAction + 1 : m_selectedAction;
                    break;
                case sf::Keyboard::Escape:
                    if (m_selectedAction == 2)
                        m_window.close();
                    else
                        m_selectedAction = 2;
                    break;
                default:
                    break;
            }
        }
        // if (event.type == sf::Event::JoystickMoved)
        //{
        // switch (event.joystickMove.axis)
        //{
        // case sf::Joystick::Axis::PovX:
        // std::cout << "joystick : " << event.joystickMove.joystickId << "(" <<
        // "PovX" << "); value : " << event.joystickMove.position << std::endl;
        // break;
        // case sf::Joystick::Axis::PovY:
        // std::cout << "joystick : " << event.joystickMove.joystickId << "(" <<
        // "PovY" << "); value : " << event.joystickMove.position << std::endl;
        // break;
        // case sf::Joystick::Axis::R:
        // std::cout << "joystick : " << event.joystickMove.joystickId << "(" << "R"
        // << "); value : " << event.joystickMove.position << std::endl;
        // break;
        // case sf::Joystick::Axis::U:
        // std::cout << "joystick : " << event.joystickMove.joystickId << "(" <<"U"
        // << "); value : " << event.joystickMove.position << std::endl;
        // break;
        // case sf::Joystick::Axis::V:
        // std::cout << "joystick : " << event.joystickMove.joystickId << "(" <<"V"
        // << "); value : " << event.joystickMove.position << std::endl;
        // break;
        // case sf::Joystick::Axis::X:
        // std::cout << "joystick : " << event.joystickMove.joystickId << "(" << "X"
        // << "); value : " << event.joystickMove.position << std::endl;
        // break;
        // case sf::Joystick::Axis::Y:
        // std::cout << "joystick : " << event.joystickMove.joystickId << "(" << "Y"
        // << "); value : " << event.joystickMove.position << std::endl;
        // break;
        // case sf::Joystick::Axis::Z:
        // std::cout << "joystick : " << event.joystickMove.joystickId << "(" <<"Z"
        // << "); value : " << event.joystickMove.position << std::endl;
        // break;
        //}
        //}
    }
    m_isActionClicked = false;
    return true;
}
