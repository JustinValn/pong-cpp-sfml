#include "paddle.h"
#include <SFML/Graphics.hpp>

Paddle::Paddle() {
    position.x = 50.f;
    position.y = 300.f;

    yVelocity = 600.f;
    
    // W:10 x H:80 Paddle
    shape.setSize(sf::Vector2f(5, 80));

    shape.setPosition(sf::Vector2f(position.x, position.y));
    shape.setOrigin(sf::Vector2f(shape.getSize().x / 2, shape.getSize().y / 2));
    shape.setFillColor(sf::Color::White);

}

void Paddle::moveUp(std::pair<unsigned int, unsigned int> windowDimensions, float dt) {
    if (position.y - shape.getSize().y / 2 >= 0.f) {
        position.y -= yVelocity * dt;
        shape.setPosition(sf::Vector2f(position.x, position.y));
    }
}

void Paddle::moveDown(std::pair<unsigned int, unsigned int> windowDimensions, float dt) {
    if (position.y + shape.getSize().y / 2 <= windowDimensions.second) {
        position.y += yVelocity * dt;
        shape.setPosition(sf::Vector2f(position.x, position.y));
    }
}

void Paddle::drawOnScreen(sf::RenderWindow& window) {
    window.draw(shape);
}

Vec2D Paddle::getPosition() const {
    return position;
}

void Paddle::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
    
    shape.setPosition(sf::Vector2f(position.x, position.y));
}

sf::Vector2f Paddle::getSize() const {
    return shape.getSize();
}