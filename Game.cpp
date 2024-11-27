#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Game::Game()
    : window(sf::VideoMode(1800, 960), "SFML Game"),
      backgroundOffset(0.0f),
      backgroundVelocity(0.5f),
      platformOffset(0.0f),
      platformVelocity(1.5f),
      scoreCounter(0),
      gameStart(false)
{
    loadAssets();
}

void Game::loadAssets()
{
    std::cout << "Loading assets..." << std::endl;

    // Load Background
    if (!bgTexture.loadFromFile("Background\\Bright\\Background.png"))
    {
        std::cerr << "Error: Could not load Background.png" << std::endl;
        exit(EXIT_FAILURE); // Exit the program if resource fails
    }

    bgSprite1.setTexture(bgTexture);
    bgSprite2.setTexture(bgTexture);

    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = bgTexture.getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    bgSprite1.setScale(scaleX, scaleY);
    bgSprite2.setScale(scaleX, scaleY);
    bgSprite2.setPosition(static_cast<float>(textureSize.x) * scaleX, 0);

    // Load Font
    if (!font.loadFromFile("SFML-Progs\\fonts\\arial.ttf"))
    {
        std::cerr << "Error: Could not load arial.ttf" << std::endl;
        exit(EXIT_FAILURE);
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(sf::Color(119, 105, 78));
    scoreText.setPosition(100, 100);

    introText.setFont(font);
    introText.setCharacterSize(50);
    introText.setFillColor(sf::Color(255, 255, 255, 100));
    introText.setString("Press Space to continue");
    introText.setPosition((window.getSize().x - introText.getLocalBounds().width) / 2,
                          (window.getSize().y - introText.getLocalBounds().height) / 2);

    fireBallCount.setFont(font);
    fireBallCount.setCharacterSize(35);
    fireBallCount.setFillColor(sf::Color(255, 255, 255, 100));
    fireBallCount.setString(std::to_string(player.getFireBallCount()) + "x");
    fireBallCount.setPosition(window.getSize().x - 250, 105);

    // Load Platform
    if (!platformTexture.loadFromFile("Tiles_rock\\tile2.png"))
    {
        std::cerr << "Error: Could not load tile2.png" << std::endl;
        exit(EXIT_FAILURE);
    }

    platformSprite.setTexture(platformTexture);
    platformSprite.setScale(2.0f, 2.0f);

    platformTileWidth = platformTexture.getSize().x * platformSprite.getScale().x;
    platformTileHeight = platformTexture.getSize().y * platformSprite.getScale().y;
    numTiles = window.getSize().x / platformTileWidth + 2;

    // Initialize Player
    if (!player.loadPlayerAssets())
    {
        std::cerr << "Error: Could not load player assets" << std::endl;
        exit(EXIT_FAILURE);
    }
    player.setPlayerPosition(50.0f, window.getSize().y - platformTileHeight - player.getPlayerDimensions().height + 20.0f);

    // Player's fireball count

    if (!fireBall.loadFireBallTexture())
    {
        std::cerr << "Error: Could not load fireball texture!" << std::endl;
        exit(EXIT_FAILURE);
    }
    fireBall.setFireBallPosition(2100 - fireBall.getFireBallDimensions().x / 2, 75);
    fireBall.setFireBallScale(0.125, 0.125);

    // Enemies
    // Bat
    std::vector<std::string> paths;

    paths.push_back("Fly\\0_Monster_Fly_000.png");
    paths.push_back("Fly\\0_Monster_Fly_004.png");
    paths.push_back("Fly\\0_Monster_Fly_008.png");
    paths.push_back("Fly\\0_Monster_Fly_012.png");

    if (!bat.loadEnemyAssets(paths))
    {
        std::cerr << "Error: Could not load bats assets" << std::endl;
        exit(EXIT_FAILURE);
    }

    bat.setPosition(window.getSize().x + bat.getGlobalBounds().width, player.getPlayerDimensions().top + 10.f);

    // Spider
    paths.clear();
    paths.push_back("enemy2\\character.jpg");
    paths.push_back("enemy2\\character.jpg");
    paths.push_back("enemy2\\character.jpg");
    paths.push_back("enemy2\\character.jpg");
    if (!spider.loadEnemyAssets(paths))
    {
        std::cerr << "Error: Could not load spider assets" << std::endl;
        exit(EXIT_FAILURE);
    }

    spider.setPosition(window.getSize().x + bat.getGlobalBounds().width, 960 - platformTileHeight);
}

void Game::run()
{
    while (window.isOpen())
    {

        handleEvents();

        if (gameStart)
        {
            updateGame();
        }

        renderGame();
    }

    std::cout << "Window closed." << std::endl;
}

void Game::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
        {
            gameStart = !gameStart;
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
        {
            player.jump();
        }
    }
}

void Game::updateGame()
{
    updateBackground();
    updatePlatform();
    updateScore();
    player.updatePlayer(platformSprite.getGlobalBounds().height, window.getSize().y, gameStart);
    bat.updateEnemy(backgroundVelocity, gameStart);
    spider.updateEnemy(backgroundVelocity, gameStart);
}

void Game::updateBackground()
{
    backgroundOffset += backgroundVelocity;
    if (backgroundOffset >= bgTexture.getSize().x * bgSprite1.getScale().x)
    {
        backgroundOffset = 0.0f;
    }

    bgSprite1.setPosition(-backgroundOffset, 0);
    bgSprite2.setPosition(bgTexture.getSize().x * bgSprite1.getScale().x - backgroundOffset, 0);
}

void Game::updatePlatform()
{
    platformOffset += platformVelocity;
    if (platformOffset >= platformTileWidth)
    {
        platformOffset = 0.0f;
    }
}

void Game::updateScore()
{
    if (scoreClock.getElapsedTime().asSeconds() >= 1.0f)
    {
        scoreCounter++;
        scoreClock.restart();
    }
    scoreText.setString("Score: " + std::to_string(scoreCounter));
}

void Game::renderGame()
{
    window.clear();

    window.draw(bgSprite1);
    window.draw(bgSprite2);

    for (int i = 0; i < numTiles; ++i)
    {
        platformSprite.setPosition(i * platformTileWidth - platformOffset, window.getSize().y - platformTileHeight);
        window.draw(platformSprite);
    }

    window.draw(scoreText);

    if (!gameStart)
    {
        window.draw(introText);
    }
    else
    {
        window.draw(fireBallCount);
        fireBall.drawFireBall(window);
        window.draw(player.getHealthBar());
    }
    window.draw(player.getPlayerSprite());
    bat.renderEnemy(window);
    spider.renderEnemy(window);
    window.display();
}
