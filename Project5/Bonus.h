// include/Bonus.h

#ifndef BONUS_H
#define BONUS_H

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "Settings.h"

enum BonusType {
    SIZE = 0,
    SPEED,
    STICKY,
    ONE_DROP,
    RANDOM_DIR
};

class Bonus {
public:
    sf::RectangleShape shape;
    BonusType type;
    float speed;

    Bonus(BonusType t, const sf::Vector2f& position);
    void update(float deltaTime);
    static BonusType getRandomBonusType();
};

#endif // BONUS_H
#pragma once
