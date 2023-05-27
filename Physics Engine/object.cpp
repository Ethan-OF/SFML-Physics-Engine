#include "object.h"

object::object(engine *p, float r, sf::Vector2f pos, sf::Color col)
{
    std::cout << "Object Created!" << std::endl;

    shape.setRadius(r);
    shape.setPosition(pos);
    shape.setFillColor(col);
}

void object::plusEquals(sf::Vector2f *a, sf::Vector2f b)
{
    *a = sf::Vector2f(a->x = +b.x, a->y = +b.y);
    return;
}

sf::Vector2f object::plusEquals(sf::Vector2f a, sf::Vector2f b)
{
    return sf::Vector2f(sf::Vector2f(a.x = +b.x, a.y = +b.y));
}

sf::Vector2f object::times(sf::Vector2f a, sf::Vector2f b)
{
    return sf::Vector2f(a.x * b.x, a.y * b.y);
}

void object::calcPhysics(float delta, sf::Vector2i screenSize, sf::Vector2f mouseMult, bool mouseDown, sf::Vector2i mousePos, bool gravity)
{


    float norm = 0.0001f;
    float drag = 100000;

    //Acceleration!
    //sf::Vector2i mousePos = sf::Mouse::getPosition();
    sf::Vector2f shapePos = shape.getPosition();
    sf::Vector2f shapeCorePos = sf::Vector2f(shape.getPosition().x + shape.getRadius(), shape.getPosition().y + shape.getRadius());
    float shapeRadius = shape.getRadius();


    if (mouseDown)
    {
        sf::Vector2f distanceToMouse(mousePos.x - shapePos.x, mousePos.y - shapePos.y);
        velocity += (distanceToMouse * delta);

        //DRAG!
        //velocity -= velocity / 500.0f;
    }

    else if (gravity)
    {
        //Gravity
        velocity += sf::Vector2f(0, 9.8 * delta * 40);
        velocity -= velocity / drag;
    }
    else
    {
        //sf::Vector2f vel = sf::Vector2f(mousePos.x - (shapePos.x + shape.getRadius()), 0);
        // mousePos.y - (shapePos.y + shape.getRadius())
        //velocity += vel / (shape.getRadius() / 3) * 0.00005f;

        //Sine wave?

        //Calculate distance!
        float distanceToSin = ((sin(shapePos.x / mouseMult.x) * mouseMult.y) + screenSize.y / 2) - shapePos.y;
        velocity += sf::Vector2f(0, distanceToSin * norm) * 100.0f;
        velocity -= velocity / 500.0f;

        //sf::Vector2f velTemp(0.0f, 0.0f);
        //velTemp = plusEquals(velocity, times(acceleration, mult) * parent->dT.getSeconds());
        //std::cout << velocity.x << velocity.y << std::endl;
    }


    //Bounds Check!

    if (shapePos.x < 0)
    {
        velocity.x = -velocity.x;
        shape.setPosition(0, shapePos.y);
    }

    if (shapeCorePos.x + shapeRadius > screenSize.x)
    {
        velocity.x = -velocity.x;
        shape.setPosition(screenSize.x - (shapeRadius * 2), shapePos.y);
    }


    if (shapePos.y < 0)
    {
        velocity.y = -velocity.y;
        shape.setPosition(shapePos.x, 0);
    }

    if (shapeCorePos.y + shapeRadius > screenSize.y)
    {
        velocity.y = -velocity.y;
        shape.setPosition(shapePos.x, screenSize.y - (shapeRadius * 2));
    }


    //Final Move
    shape.move(velocity * delta);
}

sf::CircleShape object::giveShape()
{
    return shape;
}