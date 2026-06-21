#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "ball.h"
#include "paddle.h"
#include "vec2D.h"
#include "ballState.h"

int main() {
    std::pair<unsigned int, unsigned int> winDimens = {800, 600};

    sf::RenderWindow window(sf::VideoMode({winDimens.first, winDimens.second}), "Pong");

    sf::Font font;
    if (!(font.openFromFile("../assets/upheavtt.ttf"))) {
        std::cerr << "Error Loading Font!" << std::endl;
        return -1;
    }

    sf::Text leftScore(font, "0");
    sf::Text rightScore(font, "0");

    leftScore.setCharacterSize(75);
    leftScore.setPosition({330.f, 10.f});

    rightScore.setCharacterSize(75);
    rightScore.setPosition({425.f, 10.f});

    leftScore.setString("0");
    rightScore.setString("0");

    sf::Clock clock;

    int player1Score = 0;
    int player2Score = 0;

    Ball ball;

    Paddle player1;

    Paddle player2;
    player2.setPosition(750, 300);

    // Game Loop
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Black Background
        window.clear(sf::Color::Black);

        //if (player1Score == 10 || player2Score == 10) {
            //window.close();
        //}

        leftScore.setString(std::to_string(player1Score));
        rightScore.setString(std::to_string(player2Score));

        window.draw(leftScore);
        window.draw(rightScore);


        // Dash-Line Down the Middle
        for (size_t i = 0; i < winDimens.second; i = i + 20) {
            sf::Vertex dash[] = {
                sf::Vertex(sf::Vector2f(winDimens.first / 2.f, i), sf::Color::White),
                sf::Vertex(sf::Vector2f(winDimens.first / 2.f, i + 10), sf::Color::White)
            };

            window.draw(dash, 2, sf::PrimitiveType::Lines);
        }
        
        // Clock gets time since last frame AND resets the clock..
        float dt = clock.restart().asSeconds();

        // Check Win State
        BallState result = ball.moveBall(winDimens, dt, player1, player2);

        if (result == BallState::LeftGoal) {
            player2Score++;
            std::cout << "Left Win \n";
            ball.resetBall();
        }

        if (result == BallState::RightGoal) {
            player1Score++;
            ball.resetBall();
            std::cout << "Right Win \n";
            ball.resetBall();
        }

        ball.drawOnScreen(window);

        player1.drawOnScreen(window);
        player2.drawOnScreen(window);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            player1.moveUp(winDimens, dt);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            player1.moveDown(winDimens, dt);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            player2.moveUp(winDimens, dt);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            player2.moveDown(winDimens, dt);
        }

        window.display();
    }

}