// Nabeeha starts here
class Player{
    private:
    public:

};

class Road{
    private:

    public:


};

class Enemy{
    private:
        int DamageAmount;
    public:
    Enemy();
    Enemy(int damage);

};

class Spider: public Enemy{
    private:
    int acid_balls;
    public:
    Spider();
    Spider(int damage,int balls);

};

class Bats:public Enemy{
    private:
    public:
    Bats();
    Bats(int damage);

};

class HealingPotion{
    
};