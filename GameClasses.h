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
    bool isJumping;
    bool isDead;
    float jumpVelocity;

    const float gravity = 0.2f;
    const float jumpStrength = -10.0f;

    sf::Texture idleTexture;
    std::vector<sf::Texture> runningTextures;
    sf::Sprite playerSprite;

    sf::Clock animationClock;
    int runningFrame = 0;
    float frameDuration = 0.1f;

    sf::RectangleShape healthBar;

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
    // bool checkCollision(const collectables&);
    // bool checkCollision(const collectables&);

    void reset();
    void activateShield();
    void deactivateShield();
    bool isShieldActive() const;
};

class FireBall
{
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f position;

public:
    FireBall();
    bool loadFireBallTexture();
    bool loadFireBallFont();
    void setFireBallPosition(float x, float y);
    void drawFireBall(sf::RenderWindow &window, bool isGameRunning) const;
    sf::Vector2u getFireBallDimensions() const;
    void updateCount(unsigned int newCount);
    void setFireBallScale(float scaleX, float scaleY);
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

// class Spider : public Enemy
// {
// private:
//     int countTillDeath;
//     std::vector<sf::Texture> runningTextures;
//     sf::Texture spiderTexture;
//     sf::Sprite spiderSprite;

//     sf::Clock animationClock;
//     int runningFrame = 0;
//     float frameDuration = 0.1f;

// public:
//     Spider() = default;
//     Spider(int damage, int count);
//     bool loadSpiderAssets();
//     void updateEnemy(float platformHeight, float windowHeight, bool isGameRunning);
//     sf::Sprite getSpiderSprite() const;
//     void setSpiderPosition(float playerX, float playerY);
//     sf::FloatRect getSpiderDimensions();
//     void updateCTD();
//     // AcidBall throw_Acidball();
// };

// class Bats : public Enemy
// {
// private:
//     std::string name;

// public:
//     Bats();
//     Bats(int damage);
// };

// class CollectableItems
// {
// private:
//     int xpos;
//     int ypos;
//     bool collected;

// public:
//     CollectableItems();
//     CollectableItems(int x, int y); // Constructor to initialize position and collected status
//     virtual void collect();         // Marks item as collected
//     bool is_collected() const;      // Checks if the item has been collected
// };

// class HealingPotion : public CollectableItems
// {
// private:
//     int healing_amount;

// public:
//     HealingPotion();
//     HealingPotion(int x, int y, int heal_amount); // Constructor to initialize position and healing amount
//     void use();                                   // Uses the healing potion, applying its effects
//     int get_healing_amount() const;               // Returns the healing amount
// };

// class Bullets : public CollectableItems
// {
// private:
//     int bullet_count;

// public:
//     Bullets();
//     Bullets(int x, int y, int count, int bullet); // Constructor to initialize position and fireball count

//     int get_bullet_count() const; // Returns the fireball count
// };

// class Health : public CollectableItems
// {
// private:
//     int health_amount;

// public:
//     Health();
//     Health(int amount);
//     int get_amount();
// };

// class Shield : public CollectableItems
// {
// private:
// public:
// };

// class Obstacle
// {
// private:
//     int xpos;
//     int ypos;

// public:
//     Obstacle(int x, int y);
//     virtual void move_left();                    // Moves obstacle leftward
//     virtual void inflict_damage(Player &player); // Inflicts damage on collision
//     virtual int get_damage() = 0;
// };

// class Spikes : public Obstacle
// {
// public:
//     Spikes(int x, int y);
//     void inflict_damage(Player &player) override; // Damages player on contact
//     int get_damage();
// };

// class AcidBath : public Obstacle
// {
// public:
//     AcidBath(int x, int y);
//     void inflict_damage(Player &player) override; // Poisons player on contact
//     int get_damage();
// };
