#include "GameMain.h"

//player
Player::Player():health_status(100),fireball_count(0),healingpotion_count(0),shield_status(false){}

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
Spider::Spider(int damage):Enemy(damage){}

//bats
Bats::Bats():Enemy(){}
Bats::Bats(int damage):Enemy(damage){}

//CollectableItem
CollectableItems::CollectableItems(){}
CollectableItems::CollectableItems(int x, int y) : xpos(x), ypos(y), collected(false) {}

// HealingPotion 
HealingPotion::HealingPotion(){}
HealingPotion::HealingPotion(int x, int y, int heal_amount) : CollectableItems(x, y), healing_amount(heal_amount) {}

//Bullets
Bullets::Bullets(){}
Bullets::Bullets(int x, int y, int count) : CollectableItems(x, y), fireball_count(count) {}

//