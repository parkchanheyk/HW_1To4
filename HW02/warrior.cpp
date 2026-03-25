#include "warrior.h"
#include "monster.h"
#include <iostream>
using namespace std;

Warrior::Warrior(string nickname) : Player(nickname) {
    job_name = "전사";
    cout << "* 전사로 전직하였습니다." << endl;
    level=1;
    HP=80;
    MP=80;
    power=100;
    defence=100;
    accuracy=10;
    speed=10;
}

void Warrior::attack() {
    cout << "* 장검을 휘두른다" << endl;
}

void Warrior::attack(Monster* monster) {
    if (monster == nullptr) return;
    // 1. 데미지 계산: 플레이어 공격력 - 몬스터 방어력
    int damage = this->power - monster->getDefence();
    // 2. 데미지가 0 이하라면 1로 정의
    if (damage <= 0) {
        damage = 1;
    }
    // 3. 몬스터에게 입힌 데미지 출력
    cout << nickname << "이(가) " << monster->getName() << "에게 "
        << damage << "의 데미지를 입혔습니다!" << endl;
    // 4. 몬스터 HP 업데이트
    int currentHP = monster->getHP();
    int updatedHP = currentHP - damage;
    // HP가 음수가 되지 않도록 처리 (필요에 따라 0으로 보정)
    if (updatedHP < 0) updatedHP = 0;
    monster->setHP(updatedHP);
    // 5. 몬스터가 생존했을 경우 남은 HP 출력
    if (updatedHP > 0) {
        cout << monster->getName() << "의 남은 HP: " << updatedHP << endl;
    }
    else {
        cout << monster->getName() << "이(가) 쓰러졌습니다." << endl;
    }
}