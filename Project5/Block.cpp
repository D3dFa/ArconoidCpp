// src/Block.cpp

#include "Block.h"

Block::Block(BlockType t, const sf::Vector2f& position) {
    type = t;
    shape.setSize(sf::Vector2f(BLOCK_WIDTH, BLOCK_HEIGHT));
    shape.setOrigin(BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2);
    shape.setPosition(position);
    hasBonus = false;

    switch (type) {
    case INDESTRUCTIBLE:
        shape.setFillColor(COLOR_GREY); // Изменено на серый для видимости
        health = -1; // Нерасторжимый
        break;
    case WITH_BONUS:
        shape.setFillColor(COLOR_BLUE);
        health = 1;
        hasBonus = true;
        bonusType = Bonus::getRandomBonusType();
        break;
    case SPEED_UP:
        shape.setFillColor(COLOR_YELLOW);
        health = 1;
        break;
    case DESTRUCTIBLE:
        shape.setFillColor(COLOR_RED);
        health = rand() % 3 + 1; // От 1 до 3
        break;
    default:
        shape.setFillColor(COLOR_WHITE);
        health = 1;
        break;
    }
}

bool Block::hit() {
    if (type == INDESTRUCTIBLE) {
        return false;
    }
    health--;
    if (health <= 0) {
        return hasBonus;
    }
    return false;
}
