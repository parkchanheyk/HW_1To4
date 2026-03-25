#pragma once
#include "player.h"

class Monster; // 전방 선언

class Warrior : public Player {
public:
    Warrior(string nickname);
    void attack() override;
	void attack(Monster* monster) override;
};