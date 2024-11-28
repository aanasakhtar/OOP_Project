#include <iostream>
#include "GameClasses.h"
#include <SFML/Graphics.hpp>

// player

Player::Player()
    : health(100), fireballsCount(0), healingPotion(false), velocity(0.0),
      shieldStatus(false), isJumping(false), jumpVelocity(0.0f), healthBar(sf::Vector2f(500.f, 50.f)) {}

bool Player::loadPlayerAssets()
{
    std::cout << "Loading player assets..." << std::endl;

    // Load idle texture
    if (!idleTexture.loadFromFile("Gangsters_1\\Idle.png"))
    {
        std::cerr << "Error: Could not load idle texture." << std::endl;
        return false;
    }

    // Load running textures

    runningTextures.resize(4);

    for (int i = 0; i < 4; ++i)
    {
        std::string texturePath = "Gangsters_1\\Run" + std::to_string(i + 1) + ".png";
        std::cout << "Loading: " << texturePath << std::endl;

        if (!runningTextures[i].loadFromFile(texturePath))
        {
            std::cerr << "Error: Could not load " << texturePath << std::endl;
            return false;
        }

        std::cout << "Successfully loaded: " << texturePath << std::endl;
    }

    std::cout << "Player assets loaded successfully." << std::endl;
    playerSprite.setTexture(idleTexture);
    playerSprite.setScale(1.25f, 1.25f);

    return true;
}

void Player::setPlayerPosition(float x, float y)
{
    playerSprite.setPosition(x, y);
}

void Player::updatePlayer(float platformHeight, float windowHeight, bool isGameRunning)
{
    if (isJumping)
    {
        // Apply jump physics
        float newY = playerSprite.getPosition().y + jumpVelocity;
        jumpVelocity += gravity;

        // Check if landed on platform
        if (newY >= windowHeight - platformHeight - playerSprite.getGlobalBounds().height + 20.0f)
        {
            newY = windowHeight - platformHeight - playerSprite.getGlobalBounds().height + 20.0f;
            isJumping = false;
            jumpVelocity = 0.0f;
        }

        playerSprite.setPosition(playerSprite.getPosition().x, newY);
    }

    if (isGameRunning)
    {
        // Handle running animation
        if (animationClock.getElapsedTime().asSeconds() > frameDuration)
        {
            runningFrame = (runningFrame + 1) % runningTextures.size();
            playerSprite.setTexture(runningTextures[runningFrame]);
            animationClock.restart();
        }
    }
    else
    {
        // Show idle texture when game isn't running
        playerSprite.setTexture(idleTexture);
    }
}

void Player::jump()
{
    if (!isJumping)
    {
        isJumping = true;
        jumpVelocity = jumpStrength;
    }
}

sf::Sprite Player::getPlayerSprite() const
{
    return playerSprite;
}

sf::FloatRect Player::getPlayerDimensions()
{
    return playerSprite.getGlobalBounds();
}

sf::RectangleShape Player::getHealthBar()
{
    healthBar.setFillColor(sf::Color(119, 105, 78));
    healthBar.setPosition(700, 100);
    return healthBar;
}

int Player::getFireBallCount()
{
    return fireballsCount;
}

// Placeholder methods for future functionality
void Player::reduceHealth(int damage)
{
    health -= damage;
    if (health < 0)
        health = 0;
}

void Player::activateShield()
{
    shieldStatus = true;
}

void Player::deactivateShield()
{
    shieldStatus = false;
}

bool Player::isShieldActive() const
{
    return shieldStatus;
}

// Display
FireBall::FireBall() : position(0, 0) {}

bool FireBall::loadFireBallTexture()
{
    if (!texture.loadFromFile("fireball\\file.png"))
    {
        std::cerr << "Error: Could not load fireball texture" << std::endl;
        return false;
    }
    sprite.setTexture(texture);
    return true;
}

void FireBall::setFireBallPosition(float x, float y)
{
    position = {x, y};
    sprite.setPosition(position);
}

void FireBall::drawFireBall(sf::RenderWindow &window, bool isGameRunning) const
{
    if (isGameRunning)
        window.draw(sprite);
}

sf::Vector2u FireBall::getFireBallDimensions() const
{
    return texture.getSize();
}

void FireBall::setFireBallScale(float scaleX, float scaleY)
{
    sprite.setScale(scaleX, scaleY);
}

// enemy class functions
Enemy::Enemy(int damage, int health, float velocity)
    : damage(damage), health(health), velocity(velocity), isDead(false) {}

void Enemy::markForDeletion()
{
    isDead = true;
}

bool Enemy::shouldDelete() const
{
    return isDead;
}

bool Enemy::loadEnemyAssets(const std::vector<std::string> &movingTexturePaths)
{
    // Load moving textures
    movingTextures.resize(movingTexturePaths.size());
    for (int i = 0; i < movingTexturePaths.size(); ++i)
    {
        if (!movingTextures[i].loadFromFile(movingTexturePaths[i]))
        {
            std::cerr << "Error: Could not load moving texture: " << movingTexturePaths[i] << std::endl;
            return false;
        }
    }

    std::cout << "Enemies assets loaded" << std::endl;

    return true;
}

void Enemy::renderEnemy(sf::RenderWindow &window)
{
    window.draw(sprite);
}

void Enemy::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

sf::FloatRect Enemy::getGlobalBounds() const
{
    return sprite.getGlobalBounds();
}

void Enemy::reduceHealth(int damage)
{
    health -= damage;
    if (health <= 0)
        isDead = true;
}

bool Enemy::deathStatus() const
{
    return isDead;
}

//

// bat

Bat::Bat(int damage, int health, float velocity, int count)
    : Enemy(damage, health, velocity), countTillDeath(count) {}

bool Bat::loadBatAssets(const std::vector<std::string> &movingTexturePaths)
{
    return loadEnemyAssets(movingTexturePaths); // Reuse base class method
}

void Bat::updateEnemy(float backgroundVelocity, bool isGameRunning)
{
    if (isGameRunning && !isDead)
    {
        // Update the enemy position relative to the background velocity
        float newX = sprite.getPosition().x - backgroundVelocity * 2.5; // Move left
        float newY = sprite.getPosition().y;                            // Maintain vertical position
        sprite.setScale(-0.25f, 0.25f);
        // Update the position or mark for deletion if off-screen
        if (newX > -200)
        {
            setPosition(newX, newY);
        }
        else
        {
            markForDeletion(); // Mark this enemy for removal instead of deleting it
        }

        // Handle animation
        if (animationClock.getElapsedTime().asSeconds() > frameDuration)
        {
            runningFrame = (runningFrame + 1) % movingTextures.size();
            sprite.setTexture(movingTextures[runningFrame]);
            animationClock.restart();
        }
    }
}

void Bat::updateCTD()
{
    if (isDead && countTillDeath > 0)
        countTillDeath--;
}

void Bat::renderEnemy(sf::RenderWindow &window)
{
    window.draw(sprite); // Render the Spider's sprite
}

// spider
Spider::Spider(int damage, int health, float velocity, int count)
    : Enemy(damage, health, velocity), countTillDeath(count) {}

bool Spider::loadSpiderAssets(const std::vector<std::string> &movingTexturePaths)
{
    return loadEnemyAssets(movingTexturePaths); // Reuse base class method
}

void Spider::updateEnemy(float backgroundVelocity, bool isGameRunning)
{
    if (isGameRunning && !isDead)
    {
        // Update the enemy position relative to the background velocity
        float newX = sprite.getPosition().x - backgroundVelocity * 2.5; // Move left
        float newY = sprite.getPosition().y;                            // Maintain vertical position

        sprite.setScale(-0.25f, 0.25f);

        // Update the position or mark for deletion if off-screen
        if (newX > -200)
        {
            setPosition(newX, newY);
        }
        else
        {
            markForDeletion(); // Mark this enemy for removal instead of deleting it
        }

        // Handle animation
        if (animationClock.getElapsedTime().asSeconds() > frameDuration)
        {
            runningFrame = (runningFrame + 1) % movingTextures.size();
            sprite.setTexture(movingTextures[runningFrame]);
            animationClock.restart();
        }
    }
}

void Spider::updateCTD()
{
    if (isDead && countTillDeath > 0)
        countTillDeath--;
}

void Spider::renderEnemy(sf::RenderWindow &window)
{
    window.draw(sprite); // Render the Spider's sprite
}

// // CollectableItem
// CollectableItems::CollectableItems() {}
// CollectableItems::CollectableItems(int x, int y) : xpos(x), ypos(y), collected(false) {}

// // HealingPotion
// HealingPotion::HealingPotion() : healing_amount(0) {}
// HealingPotion::HealingPotion(int x, int y, int heal_amount) : CollectableItems(x, y), healing_amount(heal_amount) {}

// // Bullets
// Bullets::Bullets() : bullet_count(0) {}
// Bullets::Bullets(int x, int y, int count, int bullet) : CollectableItems(x, y), bullet_count(bullet) {}
// int Bullets::get_bullet_count() const
// {
//     return bullet_count;
// }
// // Health
// Health::Health() : health_amount(0) {}
// Health::Health(int d) : health_amount(d) {}
// int Health::get_amount()
// {
//     return health_amount;
// }

// // Obstacle
