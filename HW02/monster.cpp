#include "monster.h"
#include <iostream>
#include <algorithm> // max 함수 사용을 위함

using namespace std;

// Monster 생성자
Monster::Monster(string name) {
    this->name = name;
    this->HP = 1000;
    this->power = 30;
    this->defence = 10;
    this->speed = 10;
}

// 몬스터의 공격 함수
void Monster::attack(Player* player) {
    if (player == nullptr) return;

    // 1. 데미지 계산: 몬스터 공격력 - 플레이어 방어력
    int damage = this->power - player->getDefence();

    // 2. 데미지가 0 이하라면 1로 정의
    if (damage <= 0) {
        damage = 1;
    }

    // 3. 플레이어에게 입힌 데미지 출력
    cout << name << "이(가) " << player->getNickname() << "에게 "
        << damage << "의 데미지를 입혔습니다!" << endl;

    // 4. 플레이어 HP 업데이트
    int currentHP = player->getHP();
    int updatedHP = currentHP - damage;

    // HP가 음수가 되지 않도록 처리 (필요에 따라 0으로 보정)
    if (updatedHP < 0) updatedHP = 0;

    player->setHP(updatedHP);

    // 5. 플레이어가 생존했을 경우 남은 HP 출력
    if (updatedHP > 0) {
        cout << player->getNickname() << "의 남은 HP: " << updatedHP << endl;
    }
    else {
        cout << player->getNickname() << "이(가) 쓰러졌습니다." << endl;
    }
}

// --- Getter 함수 정의 ---

string Monster::getName() {
    return name;
}

int Monster::getHP() {
    return HP;
}

int Monster::getPower() {
    return power;
}

int Monster::getDefence() {
    return defence;
}

int Monster::getSpeed() {
    return speed;
}

// --- Setter 함수 정의 ---

void Monster::setName(string name) {
    this->name = name;
}

void Monster::setHP(int HP) {
    this->HP = HP;
}

void Monster::setPower(int power) {
    this->power = power;
}

void Monster::setDefence(int defence) {
    this->defence = defence;
}

void Monster::setSpeed(int speed) {
    this->speed = speed;
}