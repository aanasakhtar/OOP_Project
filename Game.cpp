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
    // Load Background
    if (!bgTexture.loadFromFile("Background\\Bright\\Background.png"))
        std::cout << "Could not load background" << std::endl;

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
        std::cout << "Could not load font" << std::endl;

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

    // Load Platform
    if (!platformTexture.loadFromFile("Tiles_rock\\tile2.png"))
        std::cout << "Could not load platform" << std::endl;

    platformSprite.setTexture(platformTexture);
    platformSprite.setScale(2.0f, 2.0f);

    platformTileWidth = platformTexture.getSize().x * platformSprite.getScale().x;
    platformTileHeight = platformTexture.getSize().y * platformSprite.getScale().y;
    numTiles = window.getSize().x / platformTileWidth + 2;

    // Initialize Player
    player.loadPlayerAssets();
    player.setPlayerPosition(50.0f, window.getSize().y - platformTileHeight - player.getPlayerDimensions().height);
}

void Game::run()
{
    while (window.isOpen())
    {
        std::cout << "Handling events..." << std::endl;
        handleEvents();

        if (gameStart)
        {
            std::cout << "Updating game..." << std::endl;
            updateGame();
        }

        std::cout << "Rendering game..." << std::endl;
        renderGame();
    }
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

    window.draw(player.getPlayerSprite());
    window.display();
}
