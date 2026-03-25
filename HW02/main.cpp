//HW02.cpp

#include <iostream>
#include "player.h"
#include "warrior.h"
#include "magician.h"
#include "thief.h"
#include "archer.h"
#include "monster.h"   
using namespace std;

// 메인 함수
int main() {
    string jobs[] = { "전사", "마법사", "도적", "궁수" };
    int job_choice = 0;
    string nickname;

    Player* player = nullptr;

    cout << "* 닉네임을 입력해주세요: ";
    cin >> nickname;

    cout << "<전직 시스템>" << endl;
    cout << nickname << "님, 환영합니다!" << endl;
    cout << "* 원하시는 직업을 선택해주세요." << endl;

    for (int i = 0; i < 4; i++) {
        cout << (i + 1) << ". " << jobs[i] << endl;
    }

    cout << "선택: ";
    cin >> job_choice;

    switch (job_choice) {
    case 1:
        player = new Warrior(nickname);
        break;
    case 2:
        player = new Magician(nickname);
        break;
    case 3:
        player = new Thief(nickname);
        break;
    case 4:
        player = new Archer(nickname);
        break;
    default:
        cout << "잘못된 입력입니다." << endl;
        return 1;
    }

    player->printPlayerStatus();

    Monster* monster = new Monster("슬라임"); //몬스터 생성
    cout << "\n야생의 " << monster->getName() << "이(가) 나타났다!" << endl;

    cout << "\n[전투 시작]" << endl;
    while (true)
    {
        player->attack(monster);

        // 몬스터의 반격
        if (monster->getHP() > 0) {
            monster->attack(player);
        }
        else {
            cout << monster->getName() << "이(가) 완전히 쓰러져 반격할 수 없습니다." << endl;
            break;
        }
    }
    cout << "\n[전투 종료]" << endl;
    player->printPlayerStatus(); // 전투 후 플레이어 상태 확인

    //메모리 해제
    if (monster != nullptr) {
        delete monster;
        monster = nullptr;
    }
    if (player != nullptr) {
        delete player;
		player = nullptr;
    }
    return 0;
}