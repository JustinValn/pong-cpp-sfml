#pragma once

#include <cmath>
#include "vec2D.h"
#include "paddle.h"
#include "ballState.h"
#include <SFML/Graphics.hpp>

constexpr float pi_f = 3.1415926535f; 

// Class that generates a ball in 2D space.
class Ball {
    public:
        Ball(); // Generates ball

        void setPosition(float x, float y);
        void setVelocity(float x, float y);
        void setRadius(float x);

        Vec2D getPosition() const;

        void drawOnScreen(sf::RenderWindow& window);

        BallState moveBall(std::pair<unsigned int, unsigned int> windowDimensions, float dt, Paddle& player1, Paddle& player2);

        void resetBall();

    private:
        sf::CircleShape shape; // SFML Ball Render

        Vec2D position;
        Vec2D velocity;
        float radius;
        float speed;
        const float maxAngle = (60 * (pi_f / 180.f)); // 65 degrees in radians;
};