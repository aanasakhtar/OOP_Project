#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
// Nabeeha starts here
class Enemy;
class Player
{
private:
    int health;
    int fireballsCount;
    double velocity;
    bool healingPotion;
    bool shieldStatus;
    int currentShieldPower;
    bool isJumping;
    bool isDead;
    float jumpVelocity;

    const float gravity = 0.15f;
    const float jumpStrength = -10.0f;

    sf::Texture idleTexture;
    std::vector<sf::Texture> runningTextures;
    sf::Sprite playerSprite;

    sf::Clock animationClock;
    int runningFrame = 0;
    float frameDuration = 0.1f;

    sf::RectangleShape healthBar;
    bool fireBallThrown;

public:
    Player();

    // Load player assets (textures, etc.)
    bool loadPlayerAssets();

    // Update player state (position, animation, etc.)
    void updatePlayer(float platformHeight, float windowHeight, bool isGameRunning);

    // Handle jumping
    void jump();

    // Getters
    sf::Sprite getPlayerSprite() const;

    // Player Position
    void setPlayerPosition(float playerX, float playerY);

    // Player's dimensions

    sf::FloatRect getPlayerDimensions();

    sf::RectangleShape getHealthBar();

    void drawHealthBar(sf::RenderWindow &window, bool isGameRunning) const;

    int getFireBallCount();

    void reduceHealth(int damage);
    bool isPlayerDead();
    bool checkCollision(Enemy &enemy);

    void updateFireBallThrown();
    bool getFireBallStatus();
    // bool checkCollision(const collectables&);
    // bool checkCollision(const collectables&);

    void reset();
    void activateShield();
    void deactivateShield();
    bool isShieldActive() const;
    void throwFireball();
    bool getFireBall();
};

class FireBall
{
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f position;

public:
    FireBall();
    FireBall(sf::Vector2f);
    sf::Sprite getSprite();
    bool loadFireBallTexture();
    bool loadFireBallFont();
    void setFireBallPosition(float x, float y);
    void drawFireBall(sf::RenderWindow &window, bool isGameRunning) const;
    sf::Vector2u getFireBallDimensions() const;
    void updateCount(unsigned int newCount);
    void setFireBallScale(float scaleX, float scaleY);
    void renderFireBallForPlayer(sf::RenderWindow &window, bool thrown);
    void updateFireBallOnScreen(float velocity, bool thrown);
};

class Enemy
{
protected:
    std::vector<sf::Texture> movingTextures; // Shared across all enemies
    sf::Sprite sprite;                       // Shared sprite
    float velocity;                          // Movement velocity
    int health;                              // Enemy health
    int damage;                              // Damage dealt by the enemy
    bool isDead;                             // Death status flag

    sf::Clock animationClock;
    int runningFrame = 0;
    float frameDuration = 0.1f;

public:
    Enemy() = default;
    Enemy(int damage, int health, float velocity);
    virtual ~Enemy() = default;

    void markForDeletion();
    bool shouldDelete() const;

    virtual void updateEnemy(float backgroundVelocity, bool isGameRunning) = 0;
    virtual void renderEnemy(sf::RenderWindow &window) = 0;
    virtual bool loadEnemyAssets(const std::vector<std::string> &movingTexturePaths);

    void setPosition(float x, float y);
    sf::FloatRect getGlobalBounds() const;
    int getDamage() const;
    sf::Sprite getSprite() const;
    void reduceHealth(int damage);
    bool deathStatus() const;
};

class Bat : public Enemy
{
private:
    int countTillDeath; // Specific to Bat

public:
    Bat() = default;
    Bat(int damage, int health, float velocity, int count);

    // Load bat-specific assets
    bool loadBatAssets(const std::vector<std::string> &movingTexturePaths);

    // Override update logic
    void updateEnemy(float backgroundVelocity, bool isGameRunning) override;

    // Getters and setters
    void updateCTD();

    // Render on screen
    void renderEnemy(sf::RenderWindow &window);
};

class Spider : public Enemy
{
private:
    int countTillDeath; // Specific to Bat

public:
    Spider() = default;
    Spider(int damage, int health, float velocity, int count);

    // Load bat-specific assets
    bool loadSpiderAssets(const std::vector<std::string> &movingTexturePaths);

    // Override update logic
    void updateEnemy(float backgroundVelocity, bool isGameRunning) override;

    // Getters and setters
    void updateCTD();

    // Render on the screen
    void renderEnemy(sf::RenderWindow &window);
};

// collectibles
class Collectible
{
protected:
    sf::Sprite sprite;   // Sprite that will hold the texture
    sf::Texture texture; // Texture to load and assign to the sprite
    bool collected = false;
    float velocity;

public:
    Collectible(float velocity = 0.f);
    virtual ~Collectible() {}

    virtual bool loadTexture(const std::string &texturePath); // Load texture
    virtual void update(float backgroundVelocity);            // Update collectible position
    virtual void interactWithPlayer(Player &player);          // Handle interaction with player

    bool isCollected() const;
    virtual void setPosition(float x, float y); // Set position of the sprite
    sf::FloatRect getGlobalBounds() const;      // Get global bounds for collision detection
    virtual void updateCollectible();
    void renderCollectible(sf::RenderWindow &window); // Render the collectible sprite
};

class HealingPotion : public Collectible
{
private:
    int healingAmount;

public:
    HealingPotion(int healingAmount = 10, float velocity = 0.f);
    void interactWithPlayer(Player &player) override;
};

class Shield : public Collectible
{
private:
    int protectionAmount; // Amount of protection the shield provides

public:
    Shield() = default;
    Shield(int protectionAmount, float velocity = 0.f);
    void interactWithPlayer(Player &player) override; // Interaction with the player
};

class Obstacle
{
protected:
    sf::Sprite sprite;   // Sprite for obstacle
    sf::Texture texture; // Texture for obstacle
    float velocity;
    int damage;

public:
    Obstacle(float velocity = 0.f, int damage = 10);
    virtual ~Obstacle() {}

    virtual bool loadTexture(const std::string &texturePath); // Load texture
    virtual void update(float backgroundVelocity);            // Update obstacle position
    virtual void inflictDamage(Player &player);               // Damage the player on collision

    void setPosition(float x, float y);    // Set position of the sprite
    sf::FloatRect getGlobalBounds() const; // Get global bounds for collision detection
    void draw(sf::RenderWindow &window);   // Render the obstacle sprite
};

class Spikes : public Obstacle
{
public:
    Spikes(float velocity = 0.f, int damage = 10);
    void inflictDamage(Player &player) override; // Damages player on collision
};

class AcidBath : public Obstacle
{
public:
    AcidBath(float velocity = 0.f, int damage = 10);
    void inflictDamage(Player &player) override; // Damages player over time
};