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

class Spider: public Enemy{
    private:
        Acidball acidballs;
    public:
        Spider();
        Spider(int damage,int balls);
        AcidBall throw_Acidball();

};

//spider has acid balls
class AcidBall{
    private:
        int damage;
    public:
        void damage_player();

};

class Bats:public Enemy{
    private:
        std::string name;
    public:
    Bats();
    Bats(int damage);

};

class CollectableItems{
    public:


};

class HealingPotion{
    private:

    public:

};

class Fireballs{
    private:

};