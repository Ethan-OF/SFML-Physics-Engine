#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

sf::Vector2i winSize(600, 512);
sf::Vector2f objSize(20, 20);

sf::Vector2i mousePos(0, 0);

float deltaTime = 0.0f;

sf::Vector2f preSize(winSize.x - (objSize.x / 2), winSize.y - (objSize.y / 2));


void calcPos(sf::CircleShape *i)
{
    float div = 25;
    float mult = 1;
    float xV = 0;
    float yV = 0;

    sf::Vector2f pos(0, 0);

    while (true)
    {
        pos = i->getPosition() + sf::Vector2f(i->getRadius(), i->getRadius());
        //Distance to acceleration
        float xC = (mousePos.x - pos.x) / div;
        float yC = (mousePos.y - pos.y) / div;

        //Acceletration
        xV += xC += -xV / 80;
        yV += yC += -yV / 80;

        //pos.x += xV;
        //pos.y += yV;

        //i->setPosition(pos);

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
        // ...
        dt = deltaClock.restart();
        deltaTime = dt.asSeconds();
        //std::cout << "Delta Tick: " << deltaTime << std::endl;
    }
}

int main()
{
    //Delta Time thread.
    //sf::Thread _deltaTimeThread(&DeltaTime);
    //_deltaTimeThread.launch();


    sf::RenderWindow window(sf::VideoMode(winSize.x, winSize.y), "Test", sf::Style::Fullscreen);

    //sf::RectangleShape iA(instance(sf::Vector2f(20, 20), sf::Color::Red, sf::Vector2f(0, 0)));
    //sf::Thread iAposCalc(&calcPos, &iA);
    //iAposCalc.launch();

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
                //std::cout << "Mouse: " << e.mouseMove.x << ", " << e.mouseMove.y << std::endl;
                mousePos.x = e.mouseMove.x; mousePos.y = e.mouseMove.y;

                //p.setPosition(e.mouseMove.x, e.mouseMove.y);

                break;

            case sf::Event::TextEntered:
                if (e.text.unicode)
                {
                    printf( "Key: %c", e.text.unicode);
                }
                break;
            }
        }

        //Physics Slingshot

        // If the mouse position is 50, 50         25, 25



        //if (pos.x < 0 || pos.x > preSize.x) xV *= -1;
        //if (pos.y < 0 || pos.y > preSize.y) yV *= -1;

        

        // run it

        window.clear();

        //window.draw(iA);
        window.draw(iB);

        window.display();

    }

    return 0;
}