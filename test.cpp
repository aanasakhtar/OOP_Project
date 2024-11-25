#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Minimal Example");
    sf::Texture texture;
    if (!texture.loadFromFile("Background\\Bright\\Background.png"))
    {
        std::cerr << "Failed to load texture" << std::endl;
        return -1;
    }
    sf::Sprite sprite(texture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }
    return 0;
}

// int main()
// {
//     bool gameStart = false;
//     float platformVelocity = 1.5f;
//     float platformOffset = 0.0f;
//     float backgroundVelocity = 0.5f;
//     float backgroundOffset = 0.0f;
//     int scoreCounter = 0;
//     sf::Clock scoreClock;
//     sf::Text Score;

//     const float gravity = 0.2f;
//     const float jumpStrength = -10.0f;
//     float jumpVelocity = 0.0f;
//     bool isJumping = false;

//     sf::RenderWindow window(sf::VideoMode(1800, 960), "Basic SFML Window");

//     // Load Background
//     sf::Texture bgTexture;
//     if (!bgTexture.loadFromFile("Background\\Bright\\Background.png"))
//         std::cout << "Could not load the background" << std::endl;

//     sf::Sprite bgSprite1, bgSprite2;
//     bgSprite1.setTexture(bgTexture);
//     bgSprite2.setTexture(bgTexture);

//     sf::Vector2u windowSize = window.getSize();
//     sf::Vector2u textureSize = bgTexture.getSize();

//     float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
//     float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

//     bgSprite1.setScale(scaleX, scaleY);
//     bgSprite2.setScale(scaleX, scaleY);
//     bgSprite2.setPosition(static_cast<float>(textureSize.x) * scaleX, 0);

//     sf::Font font;
//     if (!font.loadFromFile("SFML-Progs\\fonts\\arial.ttf"))
//         std::cout << "Couldn't load the font" << std::endl;

//     sf::Text IntroText("Press Space to continue", font, 50);
//     IntroText.setFillColor(sf::Color(255, 255, 255, 100));
//     sf::FloatRect textBounds = IntroText.getLocalBounds();
//     float IntroTextX = (windowSize.x - textBounds.width) / 2;
//     float IntroTextY = (windowSize.y - textBounds.height) / 2;
//     IntroText.setPosition(IntroTextX, IntroTextY);

//     // Load Platform Texture and Sprite
//     sf::Texture platformTexture;
//     if (!platformTexture.loadFromFile("Tiles_rock\\tile2.png"))
//         std::cout << "Could not load the tile" << std::endl;

//     sf::Sprite platformSprite;
//     platformSprite.setTexture(platformTexture);
//     platformSprite.setScale(2.0f, 2.0f);

//     int platformTileWidth = platformTexture.getSize().x * platformSprite.getScale().x;
//     int platformTileHeight = platformTexture.getSize().y * platformSprite.getScale().y;
//     int numTiles = windowSize.x / platformTileWidth + 2;

//     // Load Player Texture and Sprite
//     sf::Texture idlePlayerTexture;
//     if (!idlePlayerTexture.loadFromFile("Gangsters_1\\Idle.png"))
//         std::cout << "Could not load the player" << std::endl;

//     sf::Sprite idlePlayerSprite;
//     idlePlayerSprite.setScale(1.25f, 1.25f);
//     float playerY = windowSize.y - platformTileHeight - (idlePlayerTexture.getSize().y);
//     float playerX = 50.0f;
//     idlePlayerSprite.setTexture(idlePlayerTexture);
//     idlePlayerSprite.setPosition(playerX, playerY);

//     // Load Running Animation Frames
//     std::vector<sf::Texture> runningTextures(4);
//     for (int i = 0; i < 4; ++i)
//     {
//         if (!runningTextures[i].loadFromFile("Gangsters_1\\Run" + std::to_string(i + 1) + ".png"))
//             std::cout << "Could not load running sprite " << i + 1 << std::endl;
//     }
//     sf::Sprite runningPlayerSprite;
//     runningPlayerSprite.setScale(1.25f, 1.25f);
//     runningPlayerSprite.setPosition(playerX, playerY);

//     // Animation variables
//     sf::Clock animationClock;
//     int runningFrame = 0;
//     float frameDuration = 0.1f;

//     sf::RectangleShape healthbar(sf::Vector2f(500.f, 50.f));
//     healthbar.setFillColor(sf::Color(119, 105, 78));
//     healthbar.setPosition(700, 100);
//     while (window.isOpen())
//     {
//         sf::Text Score("Score: " + std::to_string(scoreCounter), font, 40);
//         Score.setFillColor(sf::Color(119, 105, 78));
//         Score.setPosition(100, 100);
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
//             {
//                 window.close();
//             }
//             if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) // To start the game
//             {
//                 gameStart = !gameStart;
//             }
//             if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up && !isJumping) // To jump
//             {
//                 isJumping = true;
//                 jumpVelocity = jumpStrength;
//             }
//         }

//         // Update platform and background position if game has started
//         if (gameStart)
//         {
//             if (scoreClock.getElapsedTime().asSeconds() >= 1.0f)
//             {
//                 scoreCounter += 1; // Increment the score
//                 scoreClock.restart();
//             }

//             Score.setString("Score: " + std::to_string(scoreCounter));

//             // Move background
//             backgroundOffset += backgroundVelocity;
//             if (backgroundOffset >= textureSize.x * scaleX)
//             {
//                 backgroundOffset = 0.0f; // Reset the offset to loop background
//             }
//             bgSprite1.setPosition(-backgroundOffset, 0);
//             bgSprite2.setPosition(textureSize.x * scaleX - backgroundOffset, 0);

//             // Move platform
//             platformOffset += platformVelocity;
//             if (platformOffset >= platformTileWidth)
//             {
//                 platformOffset = 0.0f; // Reset
//             }

//             // Handle jumping logic
//             if (isJumping)
//             {
//                 playerY += jumpVelocity; // Move the player upwards
//                 jumpVelocity += gravity; // Apply gravity to slow the jump

//                 if (playerY >= windowSize.y - platformTileHeight - idlePlayerTexture.getSize().y)
//                 {
//                     playerY = windowSize.y - platformTileHeight - idlePlayerTexture.getSize().y;
//                     isJumping = false;
//                     jumpVelocity = 0.0f;
//                 }
//             }

//             runningPlayerSprite.setPosition(playerX, playerY);

//             // Running animation
//             if (animationClock.getElapsedTime().asSeconds() > frameDuration)
//             {
//                 runningFrame = (runningFrame + 1) % 4;
//                 runningPlayerSprite.setTexture(runningTextures[runningFrame]);
//                 animationClock.restart();
//             }
//         }

//         // Clear the window
//         window.clear();

//         // Draw Background
//         window.draw(bgSprite1);
//         window.draw(bgSprite2);

//         // Draw Platform
//         for (int i = 0; i < numTiles; ++i)
//         {
//             platformSprite.setPosition(i * platformTileWidth - platformOffset, windowSize.y - platformTileHeight);
//             window.draw(platformSprite);
//         }

//         // Draw Score and Intro Text
//         window.draw(Score);
//         if (!gameStart)
//         {
//             window.draw(IntroText);
//             window.draw(idlePlayerSprite);
//         }
//         else
//         {
//             window.draw(runningPlayerSprite);
//         }

//         // Draw healthbar
//         window.draw(healthbar);

//         // Display all drawn elements
//         window.display();
//     }

//     return 0;
// }