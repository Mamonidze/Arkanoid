#include <SFML/Graphics.hpp>

/**
 * Общий родительский класс для всех объектов
 * Что общего у всех объектов?
 *  - Они все рендерятся на экране
 */
class GameObject
{
public:
    virtual void render(sf::RenderWindow& window){}
    virtual ~GameObject() = default;
};

/**
 * Класс, отвечающий за инпут
 */
class InputController
{
public:
    bool move_Left {};
    bool move_Right {};
    bool release_ball {};
    
    void update()
    {
        move_Left    = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
        move_Right   = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
        release_ball = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
    }
};

/**
 * Класс платформы, которой управляет игрок
 *  - рендерится
 *  - ей можно управлять на A и D
 *  - Не может выезжать за край экрана
 *  - в начале игры появляется в середине нижней границы экрана
 *  - длинная, невысокая
 * Переменные:
 *  - тело
 *  - Скорость - константа
 *  - Bounding box - для проверки коллизий
 * Конструктор:
 *  - Измененный локальный ориджин - чтобы был не в правом верхнем углу, а в центре
 *  - стартовая позиция
 *  - цвет
 * Функции:
 *  - move - движение объекта при нажатии на клавиши
 *  - render - отображение платформы
 */
class Paddle : GameObject
{
    sf::RectangleShape body{{100,20}};
    float speed{0.1f};
    sf::FloatRect boundingBox = body.getGlobalBounds();


public:
    Paddle ()
    {
        body.setFillColor(sf::Color::Blue);
        body.setOrigin({body.getSize().x/2,body.getSize().y/2});
        body.setPosition({400,590});
    }

    void move(const InputController& input)
    {
        if (input.move_Right)
        {
            body.move({speed, 0});
        }
        if (input.move_Left)
        {
            body.move({-speed, 0});
        }
        check_paddle_collision();
    }
    
    /**
    * коллизия платформы со стенками экрана
    * проблема в том, что привязано к залоченному разрешению
    */
    void check_paddle_collision()
    {
        float halfWidth = body.getSize().x / 2.f;
        sf::Vector2f pos = body.getPosition();
        if (pos.x - halfWidth < 0)
        {
            body.setPosition({halfWidth, pos.y});
        }
        if (pos.x + halfWidth > 800)
        {
            body.setPosition({800 - halfWidth, pos.y});
        }
    }
    
    void render(sf::RenderWindow& window) override
    {
        window.draw(body);
    }
    ~Paddle() override = default;
};

/**
 * Класс шарика
 *  - рендерится
 *  - в начале игры находится на центре платформе и перемещается вместе с ней
 *  - Не может вылетать за край экрана
 *  - небольшой, радиус около 20
 *  - при столкновении с объектом или границей экрана должен отлетать от них под определенным углом
 * Переменные:
 *  - тело
 *  - Скорость - константа
 *  - Bounding circle? - для проверки коллизий
 * Конструктор:
 *  - Измененный локальный ориджин - чтобы был в центре
 *  - стартовая позиция
 *  - цвет
 * Функции:
 *  - move - движение объекта
 *  - render - отображение шарика
 *  - Release - отвязывание шарика от платформы по нажатию клавиши 
 */

class Ball : GameObject
{
    sf::CircleShape body{20,20};
    float speed{0};
    sf::FloatRect boundingBox = body.getGlobalBounds();
    bool IsReleased{false};

public:
    Ball ()
    {
        body.setFillColor(sf::Color::Yellow);
        body.setOrigin({10,10});
        body.setPosition({400,580});
    }
    
    bool Release_Ball(InputController& input)
    {
        if (input.release_ball)
        {
            speed = 0.01f;
            return IsReleased = true;
        }
        return IsReleased = false;
    }

    void move()
    {
        if (IsReleased)
        {
            body.move({0, -speed});
        }
    }

    void render(sf::RenderWindow& window) override
    {
        window.draw(body);
    }
};



/**
 * Основной класс игрового лупа
 * Что в нем должно быть:
 *  - функции которые все рендерят пока крутится луп
 *  - отображение окна
 *  - он должен знать о всех других классах
 *  - Функции:
 *      Run() - функция с основным игровым циклом
 */
class Game
{
private:
    sf::RenderWindow window;
    InputController input;
    Paddle Player;
    Ball Ball;
    
public:
    Game(): window(sf::VideoMode({800, 600}), "Arkanoid"){}
    
    void Run()
    {
        while (window.isOpen())
        {
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    window.close();
            }

            input.update();

            window.clear();
            Player.render(window);
            Player.move(input);
            Ball.render(window);
            Ball.move();
            Ball.Release_Ball(input);
            window.display();
        }
    }
    
};

int main()
{
    Game G;
    G.Run();
}
