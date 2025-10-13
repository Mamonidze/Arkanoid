
#include <iostream>
#include <SFML/Graphics.hpp>


class Platform
{
public:
    sf::RectangleShape Platform_Body{{100,20}};                
    static constexpr float Platform_Speed{0.1f};
    sf::Vector2<float> Platform_Spawn_Point{400,790};


    //движение платформы в зависимости от direction
    void Move_Left_Right(const float& direction, const float& speed)
    {
        this->Platform_Body.move({direction*speed, 0.f});
    }

    

    
};

class Ball
{
public:
    bool IsReleased{false};
    sf::CircleShape Ball_Body{10}; //размер шарика
    float Ball_Speed{0.1f};

    void Detect_Collision(float &Collision_Point){}

    
    void Ball_Movement(const float& direction, const float& speed)
    {
        this->Ball_Body.move({0.f, direction*speed});
    }

    //выпуск мячика в начале игры
    void Release_The_Ball()
    {
        this->IsReleased = true;
        std::cout << "Released";
    }
    
};




int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 800}), "SFML works!");
    
    Platform Player{};
    Player.Platform_Body.setOrigin({50,10});
    Player.Platform_Body.setPosition(Player.Platform_Spawn_Point);
    Player.Platform_Body.setFillColor(sf::Color::Red);

    Ball Ball{};
    Ball.Ball_Body.setOrigin({10,10});
    Ball.Ball_Body.setFillColor(sf::Color::Green);

    float Direction{};

    sf::FloatRect boundingBox = Player.Platform_Body.getGlobalBounds();
    sf::Vector2f point {400,790};
    

    


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scan::Space)
                {
                    Ball.Release_The_Ball();
                }
            }
        }

        if (!Ball.IsReleased) {
            sf::Vector2f platformPos = Player.Platform_Body.getPosition();
            float platformTop = platformPos.y - Player.Platform_Body.getSize().y / 2.f;
            Ball.Ball_Body.setPosition({platformPos.x, platformTop - Ball.Ball_Body.getRadius()});

            if (isKeyPressed(sf::Keyboard::Key::Space))
                Ball.Release_The_Ball();
        }
        else {
            Ball.Ball_Movement(-1, 0.1f);
        }
        
        window.clear();
        window.draw(Player.Platform_Body);
        window.draw(Ball.Ball_Body);
        window.display();


        if (isKeyPressed(sf::Keyboard::Key::Left))
        {
            Direction = -1;
            Player.Move_Left_Right(Direction, Platform::Platform_Speed);
        }

        if (isKeyPressed(sf::Keyboard::Key::Right))
        {
            Direction = 1;
            Player.Move_Left_Right(Direction, Platform::Platform_Speed);
        }

        if (boundingBox.contains(point))
        {
            //std::cout << "Collision";
        }

        
    }
}