#include <SFML/Graphics.hpp>

int main()
{
    const int width = 1200, height = 800;
    auto window = sf::RenderWindow(sf::VideoMode({width, height}), "Nameless game");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}
