#include <iostream>
#include "GameClasses.h"
#include <SFML/Graphics.hpp>

// player

Player::Player()
    : health(100), fireballsCount(5), healingPotion(false), velocity(0.0),
      shieldStatus(false), isJumping(false), isDead(false), jumpVelocity(0.0f), healthBar(sf::Vector2f(500.f, 50.f)), fireBallThrown(false)
{
    healthBar.setFillColor(sf::Color(119, 105, 78));
    healthBar.setPosition(700, 100);
}

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

// Healthbar

sf::RectangleShape Player::getHealthBar()
{
    return healthBar;
}

// void Player::reduceHealth(int damage)
// {
//     health -= damage;
//     if (damage == 5)
//     {
//         healthBar.setSize(sf::Vector2f(healthBar.getSize().x - 25, healthBar.getSize().y));
//     }
//     else if (damage == 10)
//     {
//         healthBar.setSize(sf::Vector2f(healthBar.getSize().x - 50, healthBar.getSize().y));
//     }
//     else if (damage == 20)
//     {
//         healthBar.setSize(sf::Vector2f(healthBar.getSize().x - 100, healthBar.getSize().y));
//     }
//     else if (damage == 30)
//     {
//         healthBar.setSize(sf::Vector2f(healthBar.getSize().x - 150, healthBar.getSize().y));
//     }
//     if (health < 0)
//     {
//         health = 0;
//         isDead = true;
//     }
// }

// qasim's reduce health function
void Player::reduceHealth(int damage)
{
    if (shieldStatus && currentShieldPower > 0)
    {
        // Shield absorbs damage first
        if (damage <= currentShieldPower)
        {
            currentShieldPower -= damage; // Shield absorbs the full damage
            damage = 0;                   // No damage left for health
        }
        else
        {
            damage -= currentShieldPower; // If shield can't absorb all, reduce health
            currentShieldPower = 0;       // Shield is now depleted
            deactivateShield();           // Shield is turned off after depletion
        }
    }

    // Apply remaining damage to health
    health -= damage;
    if (health < 0)
        health = 0; // Make sure health doesn't go negative
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
    // Define the offset for the player sprite (adjust this based on your offset values)
    sf::Vector2f offset(playerSprite.getGlobalBounds().width / 2 - 25, playerSprite.getGlobalBounds().height / 2 + 25); // Modify these values as needed

    // Create a copy of the player sprite
    sf::Sprite adjustedPlayerSprite = playerSprite;

    // Adjust the player's sprite position by the offset
    adjustedPlayerSprite.setPosition(playerSprite.getPosition() + offset);

    // Perform the collision check with the adjusted player sprite
    return adjustedPlayerSprite.getGlobalBounds().intersects(enemy.getSprite().getGlobalBounds());
}

int Player::getFireBallCount()
{
    return fireballsCount;
}

void Player::reset()
{
    health = 100; // Reset health
    isDead = false;

    healthBar.setSize(sf::Vector2f(500.f, 50.f)); // Reset health bar size
    playerSprite.setPosition(50.0f, 500.0f);      // Reset player position
    playerSprite.setTexture(idleTexture);
}

// Placeholder methods for future functionality

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
void Player::throwFireball()
{
    if (this->fireballsCount != 0)
    {
        FireBall ball;
        ball.setFireBallPosition(playerSprite.getPosition().x, playerSprite.getPosition().y);
        updateFireBallThrown();
    }
}

void Player::updateFireBallThrown()
{
    fireBallThrown = true;
}

bool Player::getFireBallStatus()
{
    return fireBallThrown;
}

// Display
FireBall::FireBall() : position(0, 0) {}

FireBall::FireBall(sf::Vector2f position)
{
    sprite.setPosition(position);
}

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

void FireBall::updateFireBallOnScreen(float velocity, bool thrown)
{
    if (thrown)
    {
        sprite.setPosition(sprite.getPosition().x + velocity, sprite.getPosition().y);
    }
}

void FireBall::renderFireBallForPlayer(sf::RenderWindow &window, bool thrown)
{
    if (thrown)
        window.draw(sprite);
}

sf::Sprite FireBall::getSprite()
{
    return sprite;
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
    if (sprite.getGlobalBounds().intersects(player.getPlayerSprite().getGlobalBounds()))
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

void Collectible::updateCollectible()
{
    sprite.setPosition(sprite.getPosition().x - velocity, sprite.getPosition().y);
}

void Collectible::renderCollectible(sf::RenderWindow &window)
{
    if (!collected)
    {
        window.draw(sprite); // Draw sprite if not collected
    }
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

Shield::Shield(int protectionAmount, float velocity)
    : Collectible(velocity), protectionAmount(protectionAmount)
{
    if (!loadTexture("3.png")) // Load the shield texture (path may need adjusting)
    {
        std::cerr << "Error: Could not load shield texture." << std::endl;
    }
}

void Shield::interactWithPlayer(Player &player)
{
    if (!isCollected())
    {
        Collectible::interactWithPlayer(player); // Check for collision with player
        if (isCollected())
        {
            player.activateShield(); // Activate shield for player
            std::cout << "Shield activated! Protection: " << std::endl;
        }
    }
}

Obstacle::Obstacle(float velocity, int damage)
    : velocity(velocity), damage(damage) {}

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

void Obstacle::update(float backgroundVelocity)
{
    sprite.move(-backgroundVelocity, 0); // Move left with the background velocity
}

void Obstacle::inflictDamage(Player &player)
{
    // Default behavior: obstacles inflict damage when the player hits them
    std::cout << "Obstacle inflicts " << damage << " damage!" << std::endl;
}

void Obstacle::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

sf::FloatRect Obstacle::getGlobalBounds() const
{
    return sprite.getGlobalBounds();
}

void Obstacle::draw(sf::RenderWindow &window)
{
    window.draw(sprite); // Draw sprite on screen
}

Spikes::Spikes(float velocity, int damage)
    : Obstacle(velocity, damage)
{
    if (!loadTexture("spikes.png")) // Load spikes texture (path may need adjusting)
    {
        std::cerr << "Error: Could not load spikes texture." << std::endl;
    }
}

void Spikes::inflictDamage(Player &player)
{
    // Spikes inflict damage instantly
    player.reduceHealth(damage);
    std::cout << "Player hit by spikes! " << damage << " damage taken!" << std::endl;
}

AcidBath::AcidBath(float velocity, int damage)
    : Obstacle(velocity, damage)
{
    if (!loadTexture("acid_bath.png")) // Load acid bath texture (path may need adjusting)
    {
        std::cerr << "Error: Could not load acid bath texture." << std::endl;
    }
}

void AcidBath::inflictDamage(Player &player)
{
    // Acid bath inflicts damage over time
    player.reduceHealth(damage);
    std::cout << "Player touched the acid bath! " << damage << " damage taken!" << std::endl;
}