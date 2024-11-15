// src/Ball.cpp

#include "Ball.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

Ball::Ball() {
    shape.setRadius(BALL_RADIUS);
    shape.setFillColor(COLOR_RED);
    shape.setOrigin(BALL_RADIUS, BALL_RADIUS);
    reset();
    sticky = false;
}

void Ball::reset(const sf::Vector2f& paddle_pos) {
    shape.setPosition(paddle_pos);
    // ”станавливаем начальное направление м€ча под углом -60 градусов
    float angle = -60.f;
    float rad = angle * 3.14159265f / 180.f;
    speed = BALL_SPEED;
    velocity.x = speed * std::cos(rad);
    velocity.y = speed * std::sin(rad);
    attached = true;
}

void Ball::update(float deltaTime, const sf::RenderWindow& window) {
    if (attached) {
        // ћ€ч прикреплен к каретке, позици€ будет обновл€тьс€ извне
        return;
    }

    shape.move(velocity * deltaTime);

    // ќтскок от стен
    if (shape.getPosition().x - shape.getRadius() <= 0.f) {
        shape.setPosition(shape.getRadius(), shape.getPosition().y);
        velocity.x = -velocity.x;
    }
    if (shape.getPosition().x + shape.getRadius() >= window.getSize().x) {
        shape.setPosition(window.getSize().x - shape.getRadius(), shape.getPosition().y);
        velocity.x = -velocity.x;
    }
    if (shape.getPosition().y - shape.getRadius() <= 0.f) {
        shape.setPosition(shape.getPosition().x, shape.getRadius());
        velocity.y = -velocity.y;
    }
}

void Ball::collideWithPaddle(Paddle& paddle) {
    if (shape.getGlobalBounds().intersects(paddle.shape.getGlobalBounds())) {
        // ќтскок м€ча от каретки с учетом положени€ попадани€
        float paddle_center = paddle.shape.getPosition().x;
        float hit_pos = shape.getPosition().x - paddle_center;
        float normalized = hit_pos / (paddle.shape.getSize().x / 2); // от -1 до 1
        float angle = normalized * 60.f; // ћаксимальный угол 60 градусов
        float rad = angle * 3.14159265f / 180.f;
        velocity.x = speed * std::sin(rad);
        velocity.y = -speed * std::cos(rad);

        if (sticky) {
            attached = true;
        }
    }
}

void Ball::collideWithBlock(const sf::FloatRect& blockBounds, int& collisionSide) {
    // ќпределение стороны столкновени€
    sf::FloatRect ballBounds = shape.getGlobalBounds();
    float overlapLeft = ballBounds.left + ballBounds.width - blockBounds.left;
    float overlapRight = blockBounds.left + blockBounds.width - ballBounds.left;
    float overlapTop = ballBounds.top + ballBounds.height - blockBounds.top;
    float overlapBottom = blockBounds.top + blockBounds.height - ballBounds.top;

    bool ballFromLeft = (std::abs(overlapLeft) < std::abs(overlapRight));
    bool ballFromTop = (std::abs(overlapTop) < std::abs(overlapBottom));

    float minOverlapX = ballFromLeft ? overlapLeft : overlapRight;
    float minOverlapY = ballFromTop ? overlapTop : overlapBottom;

    if (std::abs(minOverlapX) < std::abs(minOverlapY)) {
        velocity.x = -velocity.x;
        collisionSide = ballFromLeft ? 1 : 2; // 1 - left, 2 - right
    }
    else {
        velocity.y = -velocity.y;
        collisionSide = ballFromTop ? 3 : 4; // 3 - top, 4 - bottom
    }
}

void Ball::increaseSpeed() {
    speed += 50.f;
    // Ќормализуем вектор скорости и умножаем на новую скорость
    float angle = std::atan2(velocity.y, velocity.x);
    velocity.x = speed * std::cos(angle);
    velocity.y = speed * std::sin(angle);
}

void Ball::changeDirectionRandomly() {
    srand(static_cast<unsigned>(time(0)));
    float angle = static_cast<float>(rand() % 120 - 60); // от -60 до +60 градусов
    float rad = angle * 3.14159265f / 180.f;
    velocity.x = speed * std::cos(rad);
    velocity.y = speed * std::sin(rad);
}
