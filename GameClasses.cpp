#include <iostream>
#include "GameClasses.h"
#include <SFML/Graphics.hpp>

// player

Player::Player()
    : healthStatus(100), bulletCount(0), healingPotionCount(0), velocity(0.0),
      shieldStatus(false), isJumping(false), jumpVelocity(0.0f) {}

bool Player::loadPlayerAssets()
{
    // Load idle texture
    if (!idleTexture.loadFromFile("Gangsters_1\\Idle.png"))
    {
        std::cerr << "Could not load idle texture" << std::endl;
        return false;
    }

    // Load running textures
    for (int i = 0; i < 4; ++i)
    {
        if (!runningTextures[i].loadFromFile("Gangsters_1\\Run" + std::to_string(i + 1) + ".png"))
            std::cout << "Could not load running sprite " << i + 1 << std::endl;
    }

    // Set idle texture initially
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
        if (newY >= windowHeight - platformHeight - playerSprite.getGlobalBounds().height)
        {
            newY = windowHeight - platformHeight - playerSprite.getGlobalBounds().height;
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

// Placeholder methods for future functionality
void Player::reduceHealth(int damage)
{
    healthStatus -= damage;
    if (healthStatus < 0)
        healthStatus = 0;
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

// // spider
// Spider::Spider() : Enemy() {}
// Spider::Spider(int damage) : Enemy(damage) {}

// // bats
// Bats::Bats() : Enemy() {}
// Bats::Bats(int damage) : Enemy(damage) {}

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
