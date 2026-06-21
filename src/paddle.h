#pragma once

#include "vec2D.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Paddle {
    public:
        Paddle();

        void moveUp(std::pair<unsigned int, unsigned int> windowDimensions, float dt);
        void moveDown(std::pair<unsigned int, unsigned int> windowDimensions, float dt);

        void drawOnScreen(sf::RenderWindow& window);

        void setPosition(float x, float y);

        Vec2D getPosition() const;
        sf::Vector2f getSize() const;

    private:
        sf::RectangleShape shape;
        Vec2D position;
        float yVelocity;
};