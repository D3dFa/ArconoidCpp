// include/Game.h

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Paddle.h"
#include "Ball.h"
#include "Block.h"
#include "Bonus.h"

class Game {
private:
    sf::RenderWindow window;
    sf::Clock clock;
    Paddle paddle;
    Ball ball;
    std::vector<Block> blocks;
    std::vector<Bonus> bonuses;
    sf::Font font;
    sf::Text scoreText;
    sf::Text livesText;
    int score;
    int lives;
    bool oneDrop;
    bool gameOverFlag;

    void createBlocks();
    void handleEvents();
    void updateGame(float deltaTime);
    void render();
    void applyBonus(BonusType type);
    void displayGameOver();

public:
    Game();
    void run();
};

#endif // GAME_H
#pragma once
