#include <iostream>
using namespace std;

// Nabeeha starts here
class Player{
    private:
        int health_status;
        int fireball_count;
        int healingpotion_count;
        double velocity;
        //will also have sprite visuals here

    public:
        void move(int x,int y);
        void reduce_health(int damage)


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
        void damage_player();

};
class Spider: public Enemy{
    private:
        Acidball acidballs;
    public:
        Spider();
        Spider(int damage,int balls);
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

class Fireballs : public CollectableItems {
private:
    int fireball_count;

public:
    Fireballs();
    Fireballs(int x, int y, int count);            // Constructor to initialize position and fireball count
    void collect_fireballs();                      // Adds fireballs to player’s inventory
    int get_fireball_count() const;                // Returns the fireball count
};
