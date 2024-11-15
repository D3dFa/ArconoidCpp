// src/Game.cpp

#include "Game.h"
#include <algorithm>
#include <iostream>

// Конструктор игры
Game::Game() : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Arconoid"), score(0), lives(3), oneDrop(false), gameOverFlag(false) {
    window.setFramerateLimit(FPS);
    srand(static_cast<unsigned>(time(0)));

    // Загрузка шрифта
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        std::cerr << "Не удалось загрузить шрифт.\n";
    }

    // Настройка текста
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(COLOR_WHITE);
    scoreText.setPosition(10.f, 10.f);

    livesText.setFont(font);
    livesText.setCharacterSize(24);
    livesText.setFillColor(COLOR_WHITE);
    livesText.setPosition(SCREEN_WIDTH - 150.f, 10.f);

    createBlocks();
}

// Создание блоков
void Game::createBlocks() {
    int rows = 5;
    int cols = static_cast<int>((SCREEN_WIDTH - 2 * BLOCK_OFFSET_LEFT) / (BLOCK_WIDTH + BLOCK_PADDING));
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            float x = BLOCK_OFFSET_LEFT + col * (BLOCK_WIDTH + BLOCK_PADDING) + BLOCK_WIDTH / 2;
            float y = BLOCK_OFFSET_TOP + row * (BLOCK_HEIGHT + BLOCK_PADDING) + BLOCK_HEIGHT / 2;
            // Определение типа блока с весами
            int rand_val = rand() % 100;
            BlockType type;
            if (rand_val < 20)
                type = INDESTRUCTIBLE;
            else if (rand_val < 50)
                type = WITH_BONUS;
            else if (rand_val < 70)
                type = SPEED_UP;
            else
                type = DESTRUCTIBLE;

            blocks.emplace_back(type, sf::Vector2f(x, y));
        }
    }
}

// Основной игровой цикл
void Game::run() {
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        handleEvents();
        updateGame(deltaTime);
        render();

        if (gameOverFlag) {
            displayGameOver();
            window.close();
        }
    }
}

// Обработка событий
void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        // Запуск мяча
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            if (ball.attached) {
                ball.attached = false;
            }
        }
    }
}

// Обновление состояния игры
void Game::updateGame(float deltaTime) {
    paddle.update(deltaTime, window);

    // Если мяч прикреплен к каретке, обновляем его позицию
    if (ball.attached) {
        ball.shape.setPosition(paddle.shape.getPosition().x, paddle.shape.getPosition().y - PADDLE_HEIGHT / 2 - BALL_RADIUS - 1);
    }

    ball.update(deltaTime, window);
    ball.collideWithPaddle(paddle);

    // Обновление бонусов
    for (auto& bonus : bonuses) {
        bonus.update(deltaTime);
    }
    // Удаление бонусов, вышедших за экран
    bonuses.erase(std::remove_if(bonuses.begin(), bonuses.end(),
        [&](Bonus& b) -> bool {
            if (b.shape.getPosition().y - BONUS_HEIGHT / 2 > SCREEN_HEIGHT) {
                return true;
            }
            return false;
        }), bonuses.end());

    // Проверка столкновения мяча с блоками
    for (auto it = blocks.begin(); it != blocks.end(); ) {
        if (ball.shape.getGlobalBounds().intersects(it->shape.getGlobalBounds())) {
            int collisionSide = 0;
            ball.collideWithBlock(it->shape.getGlobalBounds(), collisionSide);
            bool hasBonus = it->hit();
            if (hasBonus) {
                bonuses.emplace_back(static_cast<BonusType>(it->bonusType), it->shape.getPosition());
            }
            // Увеличение очков
            score += 1;
            // Изменение цвета блока при попадании
            if (it->type != INDESTRUCTIBLE && it->health > 0) {
                if (it->health == 2)
                    it->shape.setFillColor(COLOR_YELLOW);
                else if (it->health == 1)
                    it->shape.setFillColor(COLOR_RED);
                else
                    it->shape.setFillColor(COLOR_WHITE);
            }
            if (it->health <= 0) {
                it = blocks.erase(it);
            }
            else {
                ++it;
            }
        }
        else {
            ++it;
        }
    }

    // Проверка столкновения каретки с бонусами
    for (auto it = bonuses.begin(); it != bonuses.end(); ) {
        if (it->shape.getGlobalBounds().intersects(paddle.shape.getGlobalBounds())) {
            applyBonus(it->type);
            it = bonuses.erase(it);
        }
        else {
            ++it;
        }
    }

    // Проверка падения мяча
    if (ball.shape.getPosition().y - BALL_RADIUS > SCREEN_HEIGHT) {
        if (oneDrop) {
            oneDrop = false;
        }
        else {
            lives--;
            if (lives <= 0) {
                gameOverFlag = true;
            }
            ball.reset(sf::Vector2f(paddle.shape.getPosition().x, paddle.shape.getPosition().y - PADDLE_HEIGHT / 2 - BALL_RADIUS - 1));
        }
    }

    // Проверка победы
    if (blocks.empty()) {
        gameOverFlag = true;
    }

    // Обновление текста
    scoreText.setString("Score: " + std::to_string(score));
    livesText.setString("Lives: " + std::to_string(lives));
}

// Применение бонусов
void Game::applyBonus(BonusType type) {
    switch (type) {
        case SIZE:
            paddle.changeSize(1.5f);
            break;
        case SPEED:
            ball.increaseSpeed();
            break;
        case STICKY:
            ball.sticky = true;
            break;
        case ONE_DROP:
            oneDrop = true;
            break;
        case RANDOM_DIR:
            ball.changeDirectionRandomly();
            break;
        default:
            break;
    }
}

// Отрисовка всех элементов
void Game::render() {
    window.clear(COLOR_BLACK);

    // Отрисовка блоков
    for (auto& block : blocks) {
        window.draw(block.shape);
    }

    // Отрисовка бонусов
    for (auto& bonus : bonuses) {
        window.draw(bonus.shape);
    }

    // Отрисовка каретки и мяча
    window.draw(paddle.shape);
    window.draw(ball.shape);

    // Отрисовка HUD
    window.draw(scoreText);
    window.draw(livesText);

    window.display();
}

// Отображение экрана окончания игры
void Game::displayGameOver() {
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(COLOR_WHITE);
    gameOverText.setString("Game Over");
    gameOverText.setPosition(SCREEN_WIDTH / 2 - gameOverText.getLocalBounds().width / 2, SCREEN_HEIGHT / 2 - 50);

    sf::Text finalScoreText;
    finalScoreText.setFont(font);
    finalScoreText.setCharacterSize(36);
    finalScoreText.setFillColor(COLOR_WHITE);
    finalScoreText.setString("Your Score: " + std::to_string(score));
    finalScoreText.setPosition(SCREEN_WIDTH / 2 - finalScoreText.getLocalBounds().width / 2, SCREEN_HEIGHT / 2 + 10);

    window.clear(COLOR_BLACK);
    window.draw(gameOverText);
    window.draw(finalScoreText);
    window.display();

    // Пауза перед закрытием
    sf::sleep(sf::seconds(3));
}
