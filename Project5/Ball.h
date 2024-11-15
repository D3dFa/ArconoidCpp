// include/Ball.h

#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Settings.h"

class Ball {
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float speed;
    bool attached;
    bool sticky;

    Ball();
    void reset(const sf::Vector2f& paddle_pos = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 30 - PADDLE_HEIGHT / 2 - BALL_RADIUS - 1));
    void update(float deltaTime, const sf::RenderWindow& window);
    void collideWithPaddle(Paddle& paddle);
    void collideWithBlock(const sf::FloatRect& blockBounds, int& collisionSide);
    void increaseSpeed();
    void changeDirectionRandomly();
};

#endif // BALL_H
#pragma once
