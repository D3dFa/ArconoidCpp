// src/Paddle.cpp

#include "Paddle.h"

Paddle::Paddle() {
    shape.setSize(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
    shape.setFillColor(COLOR_GREEN);
    shape.setOrigin(PADDLE_WIDTH / 2, PADDLE_HEIGHT / 2);
    shape.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 30);
    speed = PADDLE_SPEED;
    original_width = PADDLE_WIDTH;
    size_multiplier = 1.0f;
}

void Paddle::update(float deltaTime, const sf::RenderWindow& window) {
    sf::Vector2f movement(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        movement.x -= speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        movement.x += speed * deltaTime;
    }

    shape.move(movement);

    // Ограничение движения каретки по экрану
    if (shape.getPosition().x - shape.getSize().x / 2 < 0)
        shape.setPosition(shape.getSize().x / 2, shape.getPosition().y);
    if (shape.getPosition().x + shape.getSize().x / 2 > window.getSize().x)
        shape.setPosition(window.getSize().x - shape.getSize().x / 2, shape.getPosition().y);
}

void Paddle::changeSize(float multiplier) {
    size_multiplier = multiplier;
    shape.setSize(sf::Vector2f(original_width * size_multiplier, PADDLE_HEIGHT));
    shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
}
