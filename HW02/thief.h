#pragma once
#include "player.h"

class Monster; // 전방 선언
class Thief : public Player {
public:
    Thief(string nickname);
    void attack() override;
    void attack(Monster* monster) override;
};