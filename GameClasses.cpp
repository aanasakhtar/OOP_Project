#include <iostream>
#include "GameClasses.h"
#include <SFML/Graphics.hpp>

// player

Player::Player()
    : health(100), healingPotion(false), velocity(0.0),
      shieldStatus(false), isJumping(false), isDead(false), jumpVelocity(0.0f), healthBar(sf::Vector2f(500.f, 25.f))
{
    healthBar.setFillColor(sf::Color::Green);
    healthBar.setPosition(700, 100);
}

bool Player::loadPlayerAssets()
{
    std::cout << "Loading player assets..." << std::endl;

    if (!idleTexture.loadFromFile("Gangsters_1\\Idle.png"))
    {
        std::cerr << "Error: Could not load idle texture." << std::endl;
        return false;
    }

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
        if (animationClock.getElapsedTime().asSeconds() > frameDuration)
        {
            runningFrame = (runningFrame + 1) % runningTextures.size();
            playerSprite.setTexture(runningTextures[runningFrame]);
            animationClock.restart();
        }
    }
    else
    {
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
    return healthBar;
}

void Player::reduceHealth(int damage)
{
    if (shieldStatus && currentShieldPower > 0)
    {
        if (damage <= currentShieldPower)
        {
            currentShieldPower -= damage;
            damage = 0;
        }
        else
        {
            damage -= currentShieldPower;
            currentShieldPower = 0;
            deactivateShield();
        }
    }

    health -= damage;
    if (health <= 0)
    {
        isDead = true;
        health = 0;
    }

    // Update health bar size
    healthBar.setSize(sf::Vector2f(500.f * (health / 100.f), healthBar.getSize().y));
}

void Player::drawHealthBar(sf::RenderWindow &window, bool isGameRunning) const
{
    if (isGameRunning)
    {
        window.draw(healthBar);
    }
}

bool Player::isPlayerDead()
{
    return isDead;
}

bool Player::checkCollision(Enemy &enemy)
{
    sf::Vector2f offset(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2, playerSprite.getPosition().y + playerSprite.getGlobalBounds().height / 2 + 25);
    sf::FloatRect offsetRect(offset.x - 25, offset.y - 25, 50, 50);
    return offsetRect.intersects(enemy.getSprite().getGlobalBounds());
}
bool Player::checkCollision(Collectible &collectible)
{
    sf::Vector2f offset(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2, playerSprite.getPosition().y + playerSprite.getGlobalBounds().height / 2 + 25);
    sf::FloatRect offsetRect(offset.x - 25, offset.y - 25, 50, 50);
    return offsetRect.intersects(collectible.getSprite().getGlobalBounds());
}

bool Player::checkCollision(Obstacle &Obstacle)
{
    sf::Vector2f offset(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2, playerSprite.getPosition().y + playerSprite.getGlobalBounds().height / 2 + 25);
    sf::FloatRect offsetRect(offset.x - 25, offset.y - 25, 50, 50);
    return offsetRect.intersects(Obstacle.getSprite().getGlobalBounds());
}

void Player::reset(float x, float y)
{
    health = 100;
    isDead = false;
    healthBar.setSize(sf::Vector2f(500.f, 25.f));
    playerSprite.setPosition(x, y);
    playerSprite.setTexture(idleTexture);
}

void Player::activateShield()
{
    shieldStatus = true;
    currentShieldPower = 100;
}

void Player::deactivateShield()
{
    shieldStatus = false;
}

bool Player::isShieldActive() const
{
    return shieldStatus;
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

sf::Sprite Enemy::getSprite() const
{
    return sprite;
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

int Enemy::getDamage() const
{
    return damage;
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

Collectible::Collectible(float velocity) : velocity(velocity) {}

bool Collectible::loadTexture(const std::string &texturePath)
{
    if (!texture.loadFromFile(texturePath)) // Load texture into the texture member
    {
        std::cerr << "Error: Could not load texture: " << texturePath << std::endl;
        return false;
    }
    sprite.setTexture(texture); // Set the texture to the sprite after loading it
    return true;
}

void Collectible::update(float backgroundVelocity)
{
    sprite.move(-backgroundVelocity, 0); // Move left with the background velocity
}

void Collectible::interactWithPlayer(Player &player)
{
    sf::Vector2f offset(player.getPlayerSprite().getPosition().x + player.getPlayerSprite().getGlobalBounds().width / 2, player.getPlayerSprite().getPosition().y + player.getPlayerSprite().getGlobalBounds().height / 2 + 25);
    sf::FloatRect offsetRect(offset.x - 25, offset.y - 25, 50, 50);

    if (sprite.getGlobalBounds().intersects(offsetRect))
    {
        if (!collected)
        {
            collected = true;
            std::cout << "Collectible acquired!" << std::endl;
        }
    }
}

bool Collectible::isCollected() const
{
    return collected;
}

void Collectible::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

sf::FloatRect Collectible::getGlobalBounds() const
{
    return sprite.getGlobalBounds();
}

void Collectible::render(sf::RenderWindow &window)
{
    if (!collected)
    {
        window.draw(sprite); // Draw the collectible if not collected
    }
}

sf::Sprite Collectible::getSprite() const
{
    return sprite;
}

HealingPotion::HealingPotion(int healingAmount, float velocity)
    : Collectible(velocity), healingAmount(healingAmount)
{
    if (!loadTexture("Items/000_0065_heart.png")) // Load texture (path may need adjusting)
    {
        std::cerr << "Error: Could not load healing potion texture." << std::endl;
    }
}

void HealingPotion::interactWithPlayer(Player &player)
{
    if (!isCollected())
    {
        Collectible::interactWithPlayer(player); // Check for collision with player
        if (isCollected())
        {
            player.reduceHealth(-healingAmount); // Heal the player
            std::cout << "Player healed by " << healingAmount << std::endl;
        }
    }
}

Obstacle::Obstacle(float velocity, int damage)
    : velocity(velocity), damage(damage) {}

// Load texture for the obstacle
bool Obstacle::loadTexture(const std::string &texturePath)
{
    if (!texture.loadFromFile(texturePath)) // Load texture into the texture member
    {
        std::cerr << "Error: Could not load texture: " << texturePath << std::endl;
        return false;
    }
    sprite.setTexture(texture); // Set the texture to the sprite
    return true;
}

// Update the obstacle (move it left based on background velocity)
void Obstacle::update(float backgroundVelocity)
{
    sprite.move(-backgroundVelocity, 0); // Move left with the background velocity
}

// Default behavior: obstacles inflict damage when the player hits them
void Obstacle::inflictDamage(Player &player)
{
    std::cout << "Obstacle inflicts " << damage << " damage!" << std::endl;
}

// Set position for the obstacle
void Obstacle::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

sf::Sprite Obstacle::getSprite() const
{
    return sprite;
}

// Get the global bounds of the obstacle (used for collision detection)
sf::FloatRect Obstacle::getGlobalBounds() const
{
    return sprite.getGlobalBounds();
}

// Draw the obstacle on the screen
void Obstacle::draw(sf::RenderWindow &window)
{
    window.draw(sprite); // Draw sprite on screen
}

Spikes::Spikes(float velocity, int damage, float position)
    : Obstacle(velocity, damage)
{
    sprite.setPosition(position, sprite.getPosition().y);
    if (!loadTexture("Items\\tile36.png"))
    {
        std::cerr << "Error: Could not load spikes texture." << std::endl;
    }
}

void Spikes::inflictDamage(Player &player)
{
    if (inflicted == false)
    {
        player.reduceHealth(damage);
        std::cout << "Player hit by spikes! " << damage << " damage taken!" << std::endl;
        inflicted = true;
    }
}
AcidBath::AcidBath(float velocity, int damage, float position)
    : Obstacle(velocity, damage)
{
    sprite.setPosition(position, sprite.getPosition().y);
    if (!loadTexture("Details\\lava_drop1_1.png")) // Load acid bath texture (path may need adjusting)
    {
        std::cerr << "Error: Could not load acid bath texture." << std::endl;
    }
}

// Override the update method (if needed, for special behavior)
void AcidBath::update(float backgroundVelocity)
{
    // Custom behavior can be added here (e.g., falling, growing, etc.)
    Obstacle::update(backgroundVelocity); // Call the base update function for movement
}

// Acid bath inflicts damage over time (every second)
void AcidBath::inflictDamage(Player &player)
{
    if (inflicted == false)
    {
        player.reduceHealth(damage);
        std::cout << "Player hit by spikes! " << damage << " damage taken!" << std::endl;
        inflicted = true;
    }
}