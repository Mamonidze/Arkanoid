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
    virtual ~GameObject(){}
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
    const float speed{0.1f};

public:
    Paddle ()
    {
        body.setFillColor(sf::Color::Blue);
        body.setOrigin({body.getSize().x/2,body.getSize().y/2});
        body.setPosition({400,590});
    }

    void move()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            body.move({speed, 0});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            body.move({-speed, 0});
        }
    }
    
    void render(sf::RenderWindow& window) override
    {
        window.draw(body);
    }
    ~Paddle() override {}
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
    sf::RenderWindow window; //();
    Paddle Player;
    
public:
    Game(): window(sf::VideoMode({800, 600}), "My window"){}
    
    void Run()
    {
        while (window.isOpen())
        {
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    window.close();
            }

            window.clear();
            Player.render(window);
            Player.move();
            window.display();
        }
    }
    
};

int main()
{
    Game G;
    G.Run();
}
