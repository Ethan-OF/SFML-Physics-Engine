#pragma once

#ifndef ENGINE_H_
#define ENGINE_H_

#include "object.h"

#include <iostream>
#include <functional>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include <cstdlib>


struct deltaTime
{
public:
    sf::Clock _Clock;
    sf::Time time;

    void tick()
    {
        time = _Clock.restart();
        return;
    }
    float getSeconds()
    {
        return time.asSeconds();
    }
};


//class object;
class object;
class engine
{

public:
	engine(int n);
	void run();

	deltaTime dT;

    sf::RenderWindow *getUI();
    std::vector<object*> getList();
    float* deltaSeconds();

	void drawThread();
    void physicsUpdates();
    object* newObject(float r, sf::Vector2f pos, sf::Color col);

private:
	//std::vector<object*> drawList;
    //std::vector<object*> drawList;
};
#endif