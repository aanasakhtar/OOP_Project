#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
// Nabeeha starts here

class Player
{
private:
    int health;
    int fireballsCount;
    double velocity;
    bool healingPotion;
    bool shieldStatus;
    bool isJumping;
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

    int getFireBallCount();

    // Other functionality (placeholders for future work)
    void reduceHealth(int damage);
    void activateShield();
    void deactivateShield();
    bool isShieldActive() const;
};

class Enemy
{
protected:
    sf::Texture idleTexture;
    std::vector<sf::Texture> movingTextures;
    sf::Sprite EnemySprite;
    float velocity;
    int health;
    int damage;
    bool isDead;

public:
    Enemy(int damage);
    virtual ~Enemy();
    virtual void loadEnemyAssets(const std::string &texturePath);
    virtual void updateEnemy(float deltaTime, float platformHeight, float windowHeight, bool isGameRunning) = 0;

    void renderEnemy(sf::RenderWindow &window);
    void setPosition(float x, float y);
    sf::FloatRect getGlobalBounds() const;
    void reduceHealth(int damage);
    bool death_status() const;
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
    void drawFireBall(sf::RenderWindow &window) const;
    sf::Vector2u getFireBallDimensions() const;
    void updateCount(unsigned int newCount);
    void setFireBallScale(float scaleX, float scaleY);
};

class Enemy
{
private:
    int damage_amount;

    // public:
    //     Enemy();
    //     Enemy(int damage);
    //     int get_damage();
    //     void set_damage(int damage);
    // };

    // spider has acid balls
    // class AcidBall
    // {
    // private:
    //     int damage;

public:
    AcidBall(int dmg);
    void move_left();                   // Moves acid ball leftward
    void damage_player(Player &player); // Inflicts damage if it hits player
    bool is_hit(const Player &player);  // Checks collision with player
    void deactivate();                  // Deactivates after impact
};

class Spider : public Enemy
{
private:
    int countTillDeath;
    std::vector<sf::Texture> runningTextures;
    sf::Texture spiderTexture;
    sf::Sprite spiderSprite;

    sf::Clock animationClock;
    int runningFrame = 0;
    float frameDuration = 0.1f;

public:
    Spider() = default;
    Spider(int damage, int count);
    bool loadSpiderAssets();
    void updateEnemy(float platformHeight, float windowHeight, bool isGameRunning);
    sf::Sprite getSpiderSprite() const;
    void setSpiderPosition(float playerX, float playerY);
    sf::FloatRect getSpiderDimensions();
    void updateCTD();
    // AcidBall throw_Acidball();
};

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
