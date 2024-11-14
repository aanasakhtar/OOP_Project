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
    Enemy():DamageAmount(0){}
    Enemy(int damage):DamageAmount(damage){}

};

class Spider: public Enemy{
    private:
    int acid_balls;
    public:
    Spider():Enemy(0),acid_balls(0){}
    Spider(int damage,int balls):Enemy(d),acid_balls(balls){}

};

class Bats:public Enemy{
    private:
    public:
    Bats():Enemy(0){}
    Bats(int damage):Enemy(damage){}

};

class HealingPotion{
    
};