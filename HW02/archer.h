#pragma once
#include "player.h"
class Monster; // 전방 선언
class Archer : public Player {
public:
    Archer(string nickname);
    void attack() override;
    void attack(Monster* monster) override;
};