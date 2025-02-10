#include <SFML/Graphics.hpp>

int main()
{
    unsigned width = 750;
    unsigned int height = 960;
    sf::RenderWindow window(sf::VideoMode({ width, height }), "Shmobus!");
    window.setFramerateLimit(60);
    sf::CircleShape shape(100.f);
    sf::RectangleShape shmobs({ 100.f, 50.f });
    shape.setOrigin(shape.getGeometricCenter());
    shape.setFillColor(sf::Color::Red);
    shmobs.setFillColor(sf::Color::Yellow);
    shmobs.setPosition({ width/2.0f, height/2.0f });

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape){
                    window.close();
                }
                
            }
        }

        window.clear();
        window.draw(shmobs);
        window.draw(shape);
        window.display();
    }
    return 0;
}