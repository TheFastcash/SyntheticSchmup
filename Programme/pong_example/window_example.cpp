#include <iostream>

#include <SFML/Window.hpp>

int main()
{
    sf::Window window(sf::VideoMode(800, 600), "My window");

    //for(;;);
    // window.display();
    while(window.isOpen())
    // while(1)
    {
        window.display();
    }
    return 0;
}
