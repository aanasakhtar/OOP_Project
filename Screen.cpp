// Anas starts here
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    bool gameStart = false;
    float platformVelocity = 5.0f;
    float platformOffset = 0.0f;
    sf::RenderWindow window(sf::VideoMode(1800, 960), "Basic SFML Window");

    sf::Texture bgTexture;

    if (!bgTexture.loadFromFile("Background\\Bright\\Background.png"))
        std::cout << "Could not load the background" << std::endl;

    sf::Sprite bgSprite;
    bgSprite.setTexture(bgTexture);

    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = bgTexture.getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    bgSprite.setScale(scaleX, scaleY);

    sf::Font font;
    if (!font.loadFromFile("SFML-Progs\\fonts\\arial.ttf"))
        std::cout << "Couldn't load the font" << std::endl;

    sf::Text IntroText("Press Space to begin", font, 50);
    IntroText.setFillColor(sf::Color(255, 255, 255, 100));

    sf::FloatRect textBounds = IntroText.getLocalBounds();

    float IntroTextX = (windowSize.x - textBounds.width) / 2;
    float IntroTextY = (windowSize.y - textBounds.height) / 2;

    IntroText.setPosition(IntroTextX, IntroTextY);

    sf::Text Score("Score: ", font, 40);
    Score.setFillColor(sf::Color(119, 105, 78));

    Score.setPosition(100, 100);

    sf::Texture platformTexture;
    if (!platformTexture.loadFromFile("Tiles_rock\\tile2.png"))
    {
        std::cout << "could not load the tile" << std::endl;
    }
    sf::Sprite platformSprite;
    platformSprite.setTexture(platformTexture);

    platformSprite.setScale(2.0f, 2.0f);

    int platformTileWidth = platformTexture.getSize().x;
    int platformTileHeight = platformTexture.getSize().y;

    int numTiles = windowSize.x / platformTileWidth + 1;

    sf::Texture idlePlayerTexture;

    if (!idlePlayerTexture.loadFromFile("Gangsters_1\\Idle.png"))
        std::cout << "Could not load the player" << std::endl;

    sf::Sprite idlePlayerSprite;
    idlePlayerSprite.setTexture(idlePlayerTexture);

    idlePlayerSprite.setPosition(50, platformSprite.getPosition().y + platformTexture.getSize().y);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close the window when close button or escape key is pressed
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                std::cout << "Closed the window";
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                gameStart = true;
            }
        }
        // Update platform position if game has started
        if (gameStart)
        {
            platformOffset += platformVelocity; // Move the platform horizontally
        }

        // Clear the window with a black color
        window.clear();
        // Drawing the background
        window.draw(bgSprite);
        // Drawing Platform
        if (!gameStart)
        {
            // Drawing IntroText
            window.draw(IntroText);
            // Draw idleplayer
            window.draw(idlePlayerSprite);

            for (int i = 0; i < numTiles; ++i)
            {
                platformSprite.setPosition(i * platformTileWidth, windowSize.y - platformTileHeight);

                window.draw(platformSprite);
            }
        }
        else
        {
            for (int i = 0; i < numTiles; ++i)
            {
                // Position each tile based on its index and the current offset
                platformSprite.setPosition(i * platformTileWidth - platformOffset, windowSize.y - platformTileHeight);
                window.draw(platformSprite);
            }
        }
        // Drawing Score
        window.draw(Score);
        // Display what has been drawn so far
        window.display();
    }
    return 0;
}