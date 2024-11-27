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
    std::cout << "in" << std::endl;
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

//enemy class functions
Enemy::Enemy(int d):damage(d),health(0),isDead(false),velocity(0.0f){}
void Enemy::loadEnemyAssets(const std::string& texturePath){
    std::cout << "Loading enemy assets..." << std::endl;

    // Load idle texture
    if (!idleTexture.loadFromFile(texturePath))
    {
        std::cerr << "Error: Could not load idle texture." << std::endl;
        
    }
    EnemySprite.setTexture(idleTexture);
    EnemySprite.setScale(1.25f, 1.25f);
}

void Enemy::renderEnemy(sf::RenderWindow& window){
    window.draw(EnemySprite);
}
void Enemy::setPosition(float x, float y){
    EnemySprite.setPosition(x, y);
}
sf::FloatRect Enemy::getGlobalBounds() const{
    return EnemySprite.getGlobalBounds();
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

void FireBall::drawFireBall(sf::RenderWindow &window) const
{
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

// enemy class function
// Enemy::Enemy() : damage_amount(0) {}
// Enemy::Enemy(int damage) : damage_amount(damage) {}
// int Enemy::get_damage()
// {
//     return damage_amount;
// }
// void Enemy::set_damage(int d)
// {
//     damage_amount = d;
// }



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
