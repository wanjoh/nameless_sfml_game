#include <SFML/Graphics.hpp>
#include <iostream>

static constexpr int WIDTH = 1200, HEIGHT = 800;

bool isSupported() { return sf::Shader::isAvailable(); }

sf::VertexArray createFullscreenQuad()
{
    sf::VertexArray quad(sf::PrimitiveType::TriangleStrip, 4);
    quad[0].position = sf::Vector2f(0, 0);
    quad[1].position = sf::Vector2f(WIDTH, 0);
    quad[2].position = sf::Vector2f(0, HEIGHT);
    quad[3].position = sf::Vector2f(WIDTH, HEIGHT);

    quad[0].texCoords = sf::Vector2f(0, 0);
    quad[1].texCoords = sf::Vector2f(1, 0);
    quad[2].texCoords = sf::Vector2f(0, 1);
    quad[3].texCoords = sf::Vector2f(1, 1);

    return quad;
}

int main()
{
    if (!isSupported())
    {
        std::cout << "Shaders are not supported" << std::endl;
        return 1;
    }
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 16;

    auto window = sf::RenderWindow(sf::VideoMode({WIDTH, HEIGHT}), "Nameless game",
                                   sf::Style::Default, sf::State::Windowed, settings);
    window.setVerticalSyncEnabled(true);
    sf::VertexArray fsQuad = createFullscreenQuad();

    sf::Shader shader;
    if (!shader.loadFromFile("resources/shaders/post_process/vignette.frag",
                             sf::Shader::Type::Fragment))
    {
        std::cout << "Failed to load shader" << std::endl;
        return 1;
    }

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        shader.setUniform("u_resolution", sf::Vector2f(WIDTH, HEIGHT));

        window.clear();
        window.draw(fsQuad, &shader);
        window.display();
    }
}
