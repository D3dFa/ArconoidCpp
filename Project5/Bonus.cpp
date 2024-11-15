// src/Bonus.cpp

#include "Bonus.h"

Bonus::Bonus(BonusType t, const sf::Vector2f& position) {
    type = t;
    shape.setSize(sf::Vector2f(BONUS_WIDTH, BONUS_HEIGHT));
    shape.setOrigin(BONUS_WIDTH / 2, BONUS_HEIGHT / 2);
    shape.setPosition(position);
    speed = BONUS_SPEED;

    switch (type) {
    case SIZE:
        shape.setFillColor(COLOR_GREEN);
        break;
    case SPEED:
        shape.setFillColor(COLOR_YELLOW);
        break;
    case STICKY:
        shape.setFillColor(COLOR_BLUE);
        break;
    case ONE_DROP:
        shape.setFillColor(COLOR_RED);
        break;
    case RANDOM_DIR:
        shape.setFillColor(COLOR_ORANGE);
        break;
    default:
        shape.setFillColor(COLOR_WHITE);
        break;
    }
}

void Bonus::update(float deltaTime) {
    shape.move(0.f, speed * deltaTime);
}

BonusType Bonus::getRandomBonusType() {
    return static_cast<BonusType>(rand() % 5);
}
