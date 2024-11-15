// include/Paddle.h

#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>
#include "Settings.h"

class Paddle {
public:
    sf::RectangleShape shape;
    float speed;
    float original_width;
    float size_multiplier;

    Paddle();
    void update(float deltaTime, const sf::RenderWindow& window);
    void changeSize(float multiplier);
};

#endif // PADDLE_H
#pragma once
