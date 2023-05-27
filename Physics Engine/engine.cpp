//Main Window

#include "engine.h"

#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

sf::RenderWindow ui(sf::VideoMode(), "Main Window", sf::Style::Fullscreen);

std::vector<object*> drawList;

sf::Vector2i screenSize;

sf::Vector2f mouseMult;

engine::engine(int n)
{
    return;
}


object* engine::newObject(float r, sf::Vector2f pos, sf::Color col)
{
    return new object(this, r, pos, col);
    //drawList.push_back(&temp);
}

bool mouseDown;
bool gravity;

sf::Vector2i mousePosition;

void engine::run()
{
    screenSize = sf::Vector2i(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
    bool toggleDraw = false;

    //Initialize
    ui.setActive(false);
    //ui.setVerticalSyncEnabled(true);

    sf::Thread physicsThread(&engine::physicsUpdates, this);
    sf::Thread renderThread(&engine::drawThread, this);
    renderThread.launch();

    //newObject(5, sf::Vector2f(30, 60), sf::Color::Red);

    //object b(this, 15, sf::Vector2f(30, 60), sf::Color::Blue);
    //drawList.push_back(&b);


    //sf::Thread thread([]() {
    //    std::cout << "I am in thread!" << std::endl;
    //    });

    mouseMult = sf::Vector2f(60, 270);
    mouseDown = false;
    gravity = false;

    while (ui.isOpen())
    {
        //physicsThread.launch();
        //std::cout << "ASDASD: " << c.shape.getPosition().x << std::endl;

        sf::Event e;
        while (ui.pollEvent(e))
        {
            switch (e.type)
            {

            case sf::Event::Closed:
                ui.close();
                break;

            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) ui.close();

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                {
                    toggleDraw = !toggleDraw;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
                {
                    gravity = !gravity;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                {
                    sf::Color randomColor;
                    randomColor.r = rand() % 256;
                    randomColor.g = rand() % 256;
                    randomColor.b = rand() % 256;
                    randomColor.a = rand() % 196 + 50;

                    float randomSize = rand() % 26 + 5;

                    drawList.push_back(new object(this, randomSize, (sf::Vector2f)sf::Mouse::getPosition(), randomColor));
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    mouseMult.y = mouseMult.y + 30;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    mouseMult.y = mouseMult.y - 30;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    mouseMult.x = mouseMult.x + 1;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    mouseMult.x = mouseMult.x - 1;
                }
                break;

            case sf::Event::MouseMoved:

                mousePosition = sf::Vector2i(e.mouseMove.x, e.mouseMove.y);

                //std::cout << "Mouse: " << e.mouseMove.x << ", " << e.mouseMove.y << std::endl;

                //p.setPosition(e.mouseMove.x, e.mouseMove.y);

                if (toggleDraw)
                {
                    sf::Color randomColor;
                    randomColor.r = rand() % 256;
                    randomColor.g = rand() % 256;
                    randomColor.b = rand() % 256;
                    randomColor.a = rand() % 196 + 50;

                    float randomSize = rand() % 26 + 5;

                    drawList.push_back(new object(this, randomSize, (sf::Vector2f)sf::Mouse::getPosition(), randomColor));
                }

                break;

            case sf::Event::TextEntered:
                if (e.text.unicode)
                {
                    //printf("Key: %c", e.text.unicode);
                }
                break;

            case sf::Event::MouseButtonPressed:
                if (e.mouseButton.button == sf::Mouse::Left)
                {
                    mouseDown = true;
                }
                break;

            case sf::Event::MouseButtonReleased:
                if (e.mouseButton.button == sf::Mouse::Left)
                {
                    mouseDown = false;
                }
                break;
            }
        }

        ui.clear();

        //drawList.push_back(newObject(30.0f, sf::Vector2f(0, 0), sf::Color::Red));


        //for (unsigned int i = 0; i < drawList.size(); i++)
        //{
        //    sf::CircleShape x = drawList[i]->giveShape();
        //    std::cout << i << " : " << x.getRadius() << std::endl;

        //    x.setFillColor(sf::Color::Green);
        //    //x.setRadius(50);
        //    x.setPosition(i * 150, 512);

        //    ui.draw(x);
        //}

        //window.draw(iA);

        ui.display();

    }

    return;
}

void engine::physicsUpdates()
{
    sf::Clock physicsTime;
    float pS = 0.0f;
    while (true)
    {
        pS = physicsTime.restart().asSeconds();
        for (object* x : drawList)
        {
            x->calcPhysics(pS, screenSize, mouseMult, mouseDown, mousePosition, gravity);
        }
    }
}

float* engine::deltaSeconds()
{
    return new float(dT.getSeconds());
}

std::vector<object*> engine::getList()
{
    //return drawList;
}


void engine::drawThread()
{
    sf::Thread physicsThread(&engine::physicsUpdates, this);
    ui.setActive(true);
    ui.setVerticalSyncEnabled(true);
    physicsThread.launch();

    //sf::Sprite screen;
    //sf::Texture temp;

    while (ui.isOpen())
    {
        dT.tick();
        //std::cout << "Delta Time of: " << dT.getSeconds() << std::endl;

        //Mandatory Clear
        ui.clear();

        //screen.setPosition(0, 0);


        for (unsigned int i = 0; i < drawList.size(); i++)
        {
            sf::CircleShape x = drawList[i]->giveShape();
            //std::cout << i << " : " << x.getRadius() << std::endl;

            //x.setFillColor(sf::Color::Green);
            //x.setRadius(50);
            //x.setPosition(i * 150, 512);

            //ui.draw(screen);
            //ui.clear(sf::Color::Black);
            ui.draw(x);
            
        }
        //Draw to window
        ui.display();

        //temp.create(ui.getSize().x, ui.getSize().y);
        //temp.update(ui);
        //screen.setTexture(temp);
    }

    return;
}

sf::RenderWindow* getUI()
{
    return &ui;
}