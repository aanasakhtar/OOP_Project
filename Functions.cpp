#include "GameMain.h"

//player
Player::Player():health_status(100),bullet_count(0),healingpotion_count(0),shield_status(false){}
void Player::reduce_health(int d){
    health_status -=d;
}


void Player::activate_shield(){
    if (shield_status==false){
        shield_status=true;
    }
}
void Player::deactivate_shield(){
    if (shield_status==true){
        shield_status=false;
    }
}
bool Player::is_shield_active() const{
    return shield_status;
}
void Player::collect_item(HealingPotion& potion){
    healingpotion_count++;
}
void Player::collect_item(Health& health){
    health_status+=health.get_amount();
}
void Player::collect_item(Bullets & bullet){
    bullet_count+=bullet.get_bullet_count();
}
void Player::hit(Spike& spike){
    health_status-=ob.
}







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
HealingPotion::HealingPotion():healing_amount(0){}
HealingPotion::HealingPotion(int x, int y, int heal_amount) : CollectableItems(x, y), healing_amount(heal_amount) {}

//Bullets
Bullets::Bullets():bullet_count(0){}
Bullets::Bullets(int x, int y, int count,int bullet) : CollectableItems(x, y), bullet_count(bullet){}
int Bullets::get_bullet_count()const{
    return bullet_count;
}
//Health
Health::Health():health_amount(0){}
Health::Health(int d ):health_amount(d){}
int Health::get_amount(){
    return health_amount;
}

//Obstacle

