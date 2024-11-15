#include "GameMain.h"


//enemy class function
Enemy::Enemy():damage_amount(0){}
Enemy::Enemy(int damage):damage_amount(damage){}
int Enemy::get_damage(){
    return damage_amount;
}
void Enemy::set_damage(int d){
    damage_amount=d;
}

//spider
Spider::Spider():Enemy(){}
Spider::Spider(int damage,int acid_balls):Enemy(damage),acid_balls(acid_balls){}

//bats
Bats::Bats():Enemy(){}
Bats::Bats(int damage):Enemy(damage){}

//CollectableItem
CollectableItems::CollectableItems(){}
CollectableItems::CollectableItems(int x, int y) : xpos(x), ypos(y), collected(false) {}

// HealingPotion 
HealingPotion::HealingPotion(){}
HealingPotion::HealingPotion(int x, int y, int heal_amount) : CollectableItems(x, y), healing_amount(heal_amount) {}

//FireBalls
Fireballs::Fireballs(){}
Fireballs::Fireballs(int x, int y, int count) : CollectableItems(x, y), fireball_count(count) {}