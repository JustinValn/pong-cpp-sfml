#include "ball.h"
#include <SFML/Graphics.hpp>

// Constructor that spawns in ball.
Ball::Ball() {
    radius = 15.f;
    position.x = 400.f;
    position.y = 500.f;

    velocity.x = -500.f;
    velocity.y = 75.f;

    shape.setRadius(radius);
    shape.setOrigin(sf::Vector2f(radius, radius)); // Sets it's origin at center of ball

    shape.setPosition(sf::Vector2f(position.x, position.y));
    shape.setFillColor(sf::Color::White);
}

void Ball::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
    
    shape.setPosition(sf::Vector2f(position.x, position.y));
}

void Ball::setVelocity(float x, float y) {
    velocity.x = x;
    velocity.y = y;
}

void Ball::setRadius(float x) {
    radius = x;
    shape.setRadius(radius);
}

Vec2D Ball::getPosition() const {
    return position;
}

void Ball::drawOnScreen(sf::RenderWindow& window) {
    window.draw(shape);
}

void Ball::resetBall() {
    position.x = 400.f;
    position.y = 500.f;

    shape.setPosition(sf::Vector2f(position.x, position.y));
}

BallState Ball::moveBall(std::pair<unsigned int, unsigned int> windowDimensions, float dt, Paddle& player1, Paddle& player2) {
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    // Left paddle collision
    if (position.x - radius <= player1.getPosition().x + player1.getSize().x / 2 &&
        position.x + radius >= player1.getPosition().x - player1.getSize().x / 2 &&
        position.y + radius >= player1.getPosition().y - player1.getSize().y / 2 &&
        position.y - radius <= player1.getPosition().y + player1.getSize().y / 2) {
            float hit = ((position.y - player1.getPosition().y) / (player1.getSize().y / 2.f));

            hit = std::clamp(hit, -1.0f, 1.0f);

            speed = std::sqrt(std::pow(velocity.x, 2) + std::pow(velocity.y, 2));
            //speed = std::min(speed * 1.005f, 1200.0f);

            float angle = hit * maxAngle;

            velocity.x = std::abs(speed * std::cos(angle));
            velocity.y = speed * std::sin(angle);

            // Avoids Ball stuck within paddle
            position.x = player1.getPosition().x + player1.getSize().x / 2.f + radius;
            //position.x = player1.getPosition().x + player1.getSize().x / 2 + radius;
            //velocity.x = std::abs(velocity.x);
    }

    // Right paddle collision
    else if (position.x + radius >= player2.getPosition().x - player2.getSize().x / 2 &&
        position.x - radius <= player2.getPosition().x + player2.getSize().x / 2 &&
        position.y + radius >= player2.getPosition().y - player2.getSize().y / 2 &&
        position.y - radius <= player2.getPosition().y + player2.getSize().y / 2) {
        
            float hit = ((position.y - player2.getPosition().y) / (player2.getSize().y / 2.f));

            hit = std::clamp(hit, -1.0f, 1.0f);

            speed = std::sqrt(std::pow(velocity.x, 2) + std::pow(velocity.y, 2));
            //speed = std::min(speed * 1.005f, 1200.0f);

            float angle = hit * maxAngle;

            velocity.x = -std::abs(speed * std::cos(angle));
            velocity.y = speed * std::sin(angle);

            // Avoids Ball stuck within paddle
            position.x = player2.getPosition().x - player2.getSize().x / 2.f - radius;
    }

    // Left Side Collision
    if (position.x - radius <= 0.f) {
        return BallState::LeftGoal;
    }

    // Right Side Collision
    if (position.x + radius >= windowDimensions.first) {
        return BallState::RightGoal;
    }
    // Top Window Collision
    if (position.y - radius <= 0.f) {
        position.y = radius;
        velocity.y = std::abs(velocity.y);
    }

    // Bottom Collision
    if (position.y + radius >= windowDimensions.second) {
        position.y = windowDimensions.second - radius;
        velocity.y = -std::abs(velocity.y);
    }
    
    shape.setPosition(sf::Vector2f(position.x, position.y));

    return BallState::None;
}