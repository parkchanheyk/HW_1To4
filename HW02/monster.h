#pragma once
#include "player.h"
#include <string>
class Monster {
public:
    // Monster 생성자
    // - 몬스터의 이름을 매개변수로 입력 받습니다.
    // - 모든 몬스터는 HP 10, 공격력 30, 방어력 10, 스피드 10의 능력치를 가집니다.
    Monster(string name);

    // 몬스터의 공격 함수
    // - 플레이어 객체 포인터를 매개변수로 입력 받습니다.
    // - 몬스터의 공격력-플레이어의 방어력을 데미지로 정의합니다.
    // - 만약 위에서 계산한 데미지가 0 이하라면, 데미지를 1로 정의합니다.
    // - 플레이어에게 얼마나 데미지를 입혔는지 출력합니다.
    // - 플레이어 객체의 getHP 함수를 실행하여 플레이어HP-데미지 계산 결과를
    // - 플레이어 객체의 setHP 매개변수로 전달합니다.
    // - 플레이어가 생존했을 경우, 플레이어의 남은 HP를 출력합니다.
    void attack(Player* player);

    // 몬스터의 속성값을 리턴하는 get 함수
    string getName();
    int getHP();
    int getPower();
    int getDefence();
    int getSpeed();

    // 몬스터의 속성값을 정의하는 set 함수
    void setName(string name);
    void setHP(int HP);
    void setPower(int power);
    void setDefence(int defence);
    void setSpeed(int speed);

protected:
    string name; // 몬스터의 이름
    int HP; // 몬스터의 HP
    int power; // 몬스터의 공격력
    int defence; // 몬스터의 방어력
    int speed; // 몬스터의 스피드
};

