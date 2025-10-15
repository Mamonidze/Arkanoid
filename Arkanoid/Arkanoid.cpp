#include <SFML/Graphics.hpp>

/**
 * Класс платформы
 */
class Platform
{
    sf::RectangleShape body{{20,20}};
    float velocity{};
    float direction{};
    sf::Color color{};
    sf::Vector2<float> spawn_point{};
    
public:
    void move(float& direction, float& velocity){}
    sf::RectangleShape& get_body() //возвращаем именно ссылку на объект
    {
        return this->body;
    }
};

/**
 * Класс шарика
 */
class Ball
{
    sf::CircleShape body{10,20};
    float velocity{};
    sf::Color color{};
    sf::Vector2<float> spawn_point{};
    
public:
    void move(float& angle, float& velocity){}
    sf::CircleShape& get_body() //возвращаем именно ссылку на объект
    {
        return this->body;
    }
};

/**
 * Класс кирпичика
 */
class Brick
{
    sf::RectangleShape body{{50,50}};
    sf::Color color{};

public:
    void destroy(){}
};


/**
 * Main Game Class
 */
class Game
{
public:
    bool IsRunning{};\
    int points{};
    Platform Player;
    Ball Ball;
    
    void Render(){} //обработка отображения экрана, отрисовка всего
    void InputProcess(){} //обработка инпута игрока
    void Run()
    {
        while (IsRunning)
        {
            //основной игровой цикл 
        }
    }
};

/**
 * Класс, обрабатывающий коллизии
 */
class Collider
{
    
};



int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML works!");

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(PLayer.get_body());
        window.display();
    }
}
