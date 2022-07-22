#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <vector>

struct Cubo
{
private:
    sf::RectangleShape retangulo;
    sf::Vector2f posR;
public:
    float x, y;
    short timer = 40;
    bool canChange = true;
    Cubo(sf::Vector2f size)
    {
        retangulo.setSize(size);
        retangulo.setOrigin({ retangulo.getSize().x / 2, retangulo.getSize().y / 2 });
        posR = { 450, 300 };
    };

    void initRandomCubo()
    {
        x = static_cast<float>(rand() % 8 - 0);
        y = static_cast<float>(rand() % 10 - 0);
        canChange = false;
    }
    void updateCubo()
    {
        if (x > 5)
        {
            posR.x += x;
        }
        else
        {
            posR.x -= x * 1.5f;
        }

        if (y > 5)
            posR.y += y;
        else
            posR.y -= y * 1.5f;

        retangulo.setPosition(posR);
        retangulo.setFillColor(sf::Color(rand() % 250 - 20, rand() % 250 - 20, rand() % 250 - 20));
        timer--;
        
    }
    sf::RectangleShape getRetangulo() { return retangulo;  }

};

int main()
{
    sf::RenderWindow window(sf::VideoMode(900, 600), "SFML works!");
    window.setFramerateLimit(60);
    std::srand(static_cast<unsigned>(time(NULL)));
    Cubo* cubo = new Cubo({ 40,40 });

    std::vector<Cubo> cubos;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        
        cubos.push_back(*cubo);

        for (int i = 0; i < cubos.size(); i++)
        {
            if (cubos[i].canChange)
                cubos[i].initRandomCubo();
            cubos[i].updateCubo();
            if (cubos[i].timer <= 0)
                cubos.erase(cubos.begin() + i);
        }
        for (int i = 0; i < cubos.size(); i++)
        {
            window.draw(cubos[i].getRetangulo());
        }

        window.display();
    }
    return 0;
}
