#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

// Forward declaration to avoid circular dependencies
class Enemy;
class Obstacle;
class Collectible;
class Player
{
private:
    int health;
    double velocity;
    bool healingPotion;
    bool shieldStatus;
    int currentShieldPower;
    bool isJumping;
    bool isDead;
    float jumpVelocity;

    const float gravity = 0.05f;
    const float jumpStrength = -8.0f;

    sf::Texture idleTexture;
    std::vector<sf::Texture> runningTextures;
    sf::Sprite playerSprite;

    sf::Clock animationClock;
    int runningFrame = 0;
    float frameDuration = 0.1f;

    sf::RectangleShape healthBar;

public:
    Player();

    bool loadPlayerAssets();
    void updatePlayer(float platformHeight, float windowHeight, bool isGameRunning);
    void jump();

    // Getters
    sf::Sprite getPlayerSprite() const;
    void setPlayerPosition(float playerX, float playerY);
    sf::FloatRect getPlayerDimensions();
    sf::RectangleShape getHealthBar();
    void drawHealthBar(sf::RenderWindow &window, bool isGameRunning) const;

    void reduceHealth(int damage);
    bool isPlayerDead();
    bool checkCollision(Enemy &enemy);
    bool checkCollision(Obstacle &obstacle);
    bool checkCollision(Collectible &Obstacle);

    void reset(float x, float y);
    void activateShield();
    void deactivateShield();
    bool isShieldActive() const;
};

class Enemy
{
protected:
    std::vector<sf::Texture> movingTextures;
    sf::Sprite sprite;
    float velocity;
    int health;
    int damage;
    bool isDead;

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
    int countTillDeath;

public:
    Bat() = default;
    Bat(int damage, int health, float velocity, int count);
    bool loadBatAssets(const std::vector<std::string> &movingTexturePaths);
    void updateEnemy(float backgroundVelocity, bool isGameRunning) override;
    void updateCTD();
    void renderEnemy(sf::RenderWindow &window);
};

class Spider : public Enemy
{
private:
    int countTillDeath;

public:
    Spider() = default;
    Spider(int damage, int health, float velocity, int count);
    bool loadSpiderAssets(const std::vector<std::string> &movingTexturePaths);
    void updateEnemy(float backgroundVelocity, bool isGameRunning) override;
    void updateCTD();
    void renderEnemy(sf::RenderWindow &window);
};

// Collectibles
class Collectible
{
protected:
    sf::Sprite sprite;
    sf::Texture texture;
    bool collected;
    float velocity;

public:
    Collectible(float velocity = 0.f);
    virtual ~Collectible() {}
    sf::Sprite getSprite() const;
    virtual bool loadTexture(const std::string &texturePath);
    virtual void update(float backgroundVelocity);
    virtual void interactWithPlayer(Player &player);

    bool isCollected() const;
    void setPosition(float x, float y);
    sf::FloatRect getGlobalBounds() const;
    virtual void render(sf::RenderWindow &window);
};

// HealingPotion class
class HealingPotion : public Collectible
{
private:
    int healingAmount;

public:
    HealingPotion(int healingAmount = 10, float velocity = 0.f);
    void interactWithPlayer(Player &player) override;
};

// Obstacles
class Obstacle : public sf::Sprite
{
public:
    Obstacle(float velocity, int damage);

    virtual bool loadTexture(const std::string &texturePath);
    virtual void update(float backgroundVelocity);
    virtual void inflictDamage(Player &player);
    virtual void setPosition(float x, float y);
    sf::Sprite getSprite() const;
    sf::FloatRect getGlobalBounds() const;
    void draw(sf::RenderWindow &window);
    bool shouldDelete() const { return deleteFlag; }
    void markForDeletion() { deleteFlag = true; }

protected:
    sf::Texture texture;
    sf::Sprite sprite;
    float velocity; // Speed of the obstacle
    int damage;     // Damage caused by the obstacle
    bool deleteFlag = false;
    bool inflicted = false;
};
class Spikes : public Obstacle
{
public:
    Spikes(float velocity, int damage, float position);
    void inflictDamage(Player &player) override;
};

class AcidBath : public Obstacle
{
public:
    AcidBath(float velocity, int damage, float position);
    void update(float backgroundVelocity) override;
    void inflictDamage(Player &player) override;

private:
    sf::Clock timer;
};
