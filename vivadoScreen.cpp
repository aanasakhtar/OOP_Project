#include <SFML/Graphics.hpp>

int main()
{
    // Create the window with a black background
    sf::RenderWindow window(sf::VideoMode(800, 600), "Circular Holes");

    // Set up a white circle shape
    sf::CircleShape hole(50);               // radius of 50 for each hole
    hole.setFillColor(sf::Color::Black);    // Set the hole color to black (background)
    hole.setOutlineThickness(5);            // Set stroke thickness to 5
    hole.setOutlineColor(sf::Color::White); // Set stroke color to white

    // Set up the positions of the circles in the given pattern
    sf::Vector2f positions[] = {
        sf::Vector2f(375, 100), // Top center circle
        sf::Vector2f(275, 200), // Left middle circle
        sf::Vector2f(375, 200), // Center middle circle
        sf::Vector2f(475, 200), // Right middle circle
        sf::Vector2f(375, 300)  // Bottom center circle
    };

    // Main game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the screen with black color
        window.clear(sf::Color::Black);

        // Draw the circles at the specified positions
        for (const auto &position : positions)
        {
            hole.setPosition(position.x - hole.getRadius(), position.y - hole.getRadius());
            window.draw(hole);
        }

        // Display everything
        window.display();
    }

    return 0;
}
