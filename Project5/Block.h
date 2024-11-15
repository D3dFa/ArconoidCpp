// include/Block.h

#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Settings.h"
#include "Bonus.h"

enum BlockType {
    INDESTRUCTIBLE = 1,
    WITH_BONUS,
    SPEED_UP,
    DESTRUCTIBLE
};

class Block {
public:
    sf::RectangleShape shape;
    BlockType type;
    int health;
    bool hasBonus;
    BonusType bonusType;

    Block(BlockType t, const sf::Vector2f& position);
    bool hit();
};

#endif // BLOCK_H
#pragma once
