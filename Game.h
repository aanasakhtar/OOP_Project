#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "GameClasses.h"

class Game
{
private:
    // Window
    sf::RenderWindow window;

    // Fonts and Text
    sf::Font font;
    sf::Text scoreText;
    sf::Text introText;
    sf::Text fireBallCount;

    // Background
    sf::Texture bgTexture;
    sf::Sprite bgSprite1, bgSprite2;
    float backgroundOffset;
    float backgroundVelocity;

    // Platform
    sf::Texture platformTexture;
    sf::Sprite platformSprite;
    float platformOffset;
    float platformVelocity;
    int platformTileWidth;
    int platformTileHeight;
    int numTiles;

    // Player
    Player player;

    // FireBalls
    std::vector<FireBall> fireballs;

    // Player's fireball count
    sf::Texture fireBallTexture;
    sf::Sprite fireBallSprite;

    // Enemy
    std::vector<std::unique_ptr<Enemy>> enemies;

    // Collectables
    std::vector<Collectible> collectibles;

    // Score and Game State
    int scoreCounter;
    sf::Clock scoreClock;
    sf::Clock enemySpawnTimer;
    enum class GameState
    {
        Intro,
        Running,
        GameOver
    };
    GameState gameState;

    // Private Methods
    void loadAssets();
    void handleEvents();
    void updateGame();
    void renderGame();
    void updatePlatform();
    void updateBackground();
    void updateScore();
    void updateFireBallCount();
    void updateFireBalls();
    void resetGame();
    void spawnRandomEnemy();

public:
    Game();     // Constructor
    void run(); // Main game loop
};

#endif
