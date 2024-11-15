#include <iostream>
using namespace std;

// Nabeeha starts here
class Player{
    private:
        int health_status;
        int fireball_count;
        int healingpotion_count;
        double velocity;
        bool shield_status;
        //will also have sprite visuals here

    public:
        Player();
        void move(int x,int y);
        void reduce_health(int damage);
        void duck(); 
        void jump(); 
        void activate_shield();  
        void deactivate_shield();  
        void deactivate_shield();  
        bool is_shield_active() const;
        void collect_item(CollectableItems item);
        void throw_fireball();




};

class Road{
    private:

    public:


};

class Enemy{
    private:
        int damage_amount;
    public:
        Enemy();
        Enemy(int damage);
        int get_damage(); 
        void set_damage(int damage);

};



//spider has acid balls
class AcidBall{
    private:
        int damage;
    public:
        AcidBall(int dmg);
        void move_left();                         // Moves acid ball leftward
        void damage_player(Player& player);       // Inflicts damage if it hits player
        bool is_hit(const Player& player);        // Checks collision with player
        void deactivate();                        // Deactivates after impact
};


class Spider: public Enemy{
    private:
        int health;
    public:
        Spider();
        Spider(int damage);
        AcidBall throw_Acidball();

};

class Bats:public Enemy{
    private:
        std::string name;
    public:
    Bats();
    Bats(int damage);

};

class CollectableItems {
private:
    int xpos;
    int ypos;
    bool collected;

public:
    CollectableItems();
    CollectableItems(int x, int y);         // Constructor to initialize position and collected status
    virtual void collect();                 // Marks item as collected
    bool is_collected() const;              // Checks if the item has been collected
};

class HealingPotion : public CollectableItems {
private:
    int healing_amount;

public:
    HealingPotion();
    HealingPotion(int x, int y, int heal_amount);  // Constructor to initialize position and healing amount
    void use();                                    // Uses the healing potion, applying its effects
    int get_healing_amount() const;                // Returns the healing amount
};

class Bullets : public CollectableItems {
private:
    int fireball_count;

public:
    Bullets();
    Bullets(int x, int y, int count);            // Constructor to initialize position and fireball count
    void collect_fireballs();                      // Adds fireballs to player’s inventory
    int get_fireball_count() const;                // Returns the fireball count
};


class Obstacle {
private:
    int xpos;
    int ypos;

public:
    Obstacle(int x, int y);
    virtual void move_left();                 // Moves obstacle leftward
    virtual void inflict_damage(Player& player); // Inflicts damage on collision
};

class Spikes : public Obstacle {
public:
    Spikes(int x, int y);
    void inflict_damage(Player& player) override; // Damages player on contact
};

class AcidBath : public Obstacle {
public:
    AcidBath(int x, int y);
    void inflict_damage(Player& player) override; // Poisons player on contact
};



