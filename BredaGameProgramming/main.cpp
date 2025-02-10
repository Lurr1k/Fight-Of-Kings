#include <SFML/Graphics.hpp>
#include <iostream>

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

    void go_up() {
        circle.move({ 0,-10 });
    }
    void go_down() {
        circle.move({ 0,10 });
    }
    void go_right() {
        circle.move({ 10,0 });
    }
    void go_left() {
        circle.move({ -10,0 });
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

                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    std::cout << "Exit";
                    window.close();
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::W) {
                    std::cout << "W";
                    myCircle.go_up();

                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::A) {
                    std::cout << "W";
                    myCircle.go_left();

                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::S) {
                    std::cout << "W";
                    myCircle.go_down();

                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::D) {
                    std::cout << "W";
                    myCircle.go_right();

                }
            }
        }

        window.clear();
        myCircle.draw_circle(window);
        window.display();
    }
    return 0;
}