#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

//Base variables

sf::Vector2i winSize(600, 512);
sf::Vector2f objSize(20, 20);

sf::Vector2i mousePos(0, 0);

float deltaTime = 0.0f;

sf::Vector2f preSize(winSize.x - (objSize.x / 2), winSize.y - (objSize.y / 2));


void calcPos(sf::CircleShape *i)
{
    /// <summary>
    /// Values intended to be temporary, before I moved on. The 'div' variable was used throughout the development process to
    /// help determine a good multiplier to the speed of objects. Due to screen sizes changing, this version is specifically
    /// setup for my screen, the size being 1920x1080. This is revised and fixed in later projects.
    /// </summary>

    float div = 25;
    float mult = 1;
    float xV = 0;
    float yV = 0;

    sf::Vector2f pos(0, 0);

    while (true)
    {
        pos = i->getPosition() + sf::Vector2f(i->getRadius(), i->getRadius());

        //Mouse Distance

        float xC = (mousePos.x - pos.x) / div;
        float yC = (mousePos.y - pos.y) / div;

        //Mouse Distance to Acceletration
        xV += xC += -xV / 80;
        yV += yC += -yV / 80;

        std::cout << "Movement::: Velocity of:: X: " << xV << " Y: " << yV << " :: deltaTime of: " << deltaTime << std::endl;

        i->move(sf::Vector2f(xV, yV) * deltaTime * mult);
    }
    return;
}


sf::CircleShape instance(float size, sf::Color color, sf::Vector2f startPos)
{
    sf::CircleShape i(size);
    i.setFillColor(color);
    i.setPosition(startPos);

    return i;
}


sf::Clock deltaClock;

void DeltaTime()
{
    
    sf::Time dt;

    for (;;)
    {
        dt = deltaClock.restart();
        deltaTime = dt.asSeconds();
    }
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(winSize.x, winSize.y), "Test", sf::Style::Fullscreen);

    sf::CircleShape iB(instance(15, sf::Color::Blue, sf::Vector2f(20, 0)));
    sf::Thread iBposCalc(&calcPos, &iB);
    iBposCalc.launch();

    window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {
        deltaTime = deltaClock.restart().asSeconds();


        sf::Event e;
        while (window.pollEvent(e))
        {
            switch (e.type)
            {

            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

            case sf::Event::MouseMoved:

                mousePos.x = e.mouseMove.x; mousePos.y = e.mouseMove.y;

                break;

            case sf::Event::TextEntered:
                if (e.text.unicode)
                {
                    printf( "Key: %c", e.text.unicode);
                }
                break;
            }
        }

        window.clear();

        window.draw(iB);

        window.display();

    }

    return 0;
}