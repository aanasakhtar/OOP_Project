// Anas starts here
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
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
        }
        // Clear the window with a black color
        window.clear();
        // Drawing the background
        window.draw(bgSprite);
        // Drawing IntroText
        window.draw(IntroText);
        // Display what has been drawn so far
        window.display();
    }
    return 0;
}