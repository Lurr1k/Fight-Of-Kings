#include <SFML/Graphics.hpp>

class Circle {
public:
    float radius = 7.0;
    sf::CircleShape circle;
    Circle(float circleX, float circleY) {
        circle.setRadius(radius);
        circle.setOrigin(circle.getGeometricCenter());
        circle.setFillColor(sf::Color::Cyan);
        circle.setPosition({ circleX, circleY });
    }

    
    void draw_circle(sf::RenderWindow& window) {
        window.draw(this->circle);
    }
};

int main()
{   
    unsigned int height = 950;
    unsigned int width = 750;
    sf::RenderWindow window(sf::VideoMode({ width, height }), "SFML Circle");
    Circle myCircle(width/2, height/2);
    


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
        myCircle.draw_circle(window);
        window.display();
    }
    return 0;
}