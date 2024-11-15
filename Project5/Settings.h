// include/Settings.h

#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Graphics.hpp>

// Размеры окна
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

// Цвета
const sf::Color COLOR_WHITE = sf::Color::White;
const sf::Color COLOR_BLACK = sf::Color::Black;
const sf::Color COLOR_RED = sf::Color::Red;
const sf::Color COLOR_GREEN = sf::Color::Green;
const sf::Color COLOR_BLUE = sf::Color::Blue;
const sf::Color COLOR_YELLOW = sf::Color::Yellow;
const sf::Color COLOR_ORANGE = sf::Color(255, 165, 0);
const sf::Color COLOR_GREY = sf::Color(128, 128, 128); // Новый цвет для видимости

// Настройки каретки
const float PADDLE_WIDTH = 100.f;
const float PADDLE_HEIGHT = 20.f;
const float PADDLE_SPEED = 400.f; // пикселей в секунду

// Настройки мяча
const float BALL_RADIUS = 10.f;
const float BALL_SPEED = 300.f; // пикселей в секунду

// Настройки блоков
const float BLOCK_WIDTH = 60.f;
const float BLOCK_HEIGHT = 30.f;
const float BLOCK_PADDING = 5.f;
const float BLOCK_OFFSET_TOP = 50.f;
const float BLOCK_OFFSET_LEFT = 35.f;

// Настройки бонусов
const float BONUS_WIDTH = 20.f;
const float BONUS_HEIGHT = 20.f;
const float BONUS_SPEED = 150.f; // пикселей в секунду

// Настройки игры
const unsigned int FPS = 60;

#endif // SETTINGS_H
#pragma once
