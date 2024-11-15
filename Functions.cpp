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

//