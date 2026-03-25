#pragma once
#include "player.h"
class Monster; // 전방 선언
class Magician : public Player {
public:
    Magician(string nickname);
    void attack() override;
    void attack(Monster* monster) override;
};