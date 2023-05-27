#pragma once

#ifndef OBJECT_H_
#define OBJECT_H_

#include <SFML/Graphics.hpp>
#include "engine.h"
#include <thread>

#include <stdio.h>
#include <math.h>
#define PI 3.14159265

class engine;
class object
{
public:

	object(engine *p, float r, sf::Vector2f pos, sf::Color col);
	sf::CircleShape shape;

	//Logic
	void plusEquals(sf::Vector2f *a, sf::Vector2f b);
	sf::Vector2f plusEquals(sf::Vector2f a, sf::Vector2f b);
	sf::Vector2f times(sf::Vector2f a, sf::Vector2f b);
	void calcPhysics(float delta, sf::Vector2i screenSize, sf::Vector2f mouseMult, bool mouseDown, sf::Vector2i mousePos, bool gravity);
	sf::Vector2f velocity;

	sf::CircleShape giveShape();


private:
	engine *parent;
};

#endif