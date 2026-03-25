// HW01.cpp

#include <iostream> //기본 입출력 라이브러리

// 포션을 지급하는 함수 변수에 직접 접근해야함
void setPotion(int count, int* HPPotion, int* MPPotion) {
	*HPPotion = count; // HP,MP 포션 count개 지급
	*MPPotion = count;
}

void getPotion(int* HPPotion, int* MPPotion) {
	*HPPotion += 1; // 레벨 업 시 HP,MP 포션 1개씩 지급
	*MPPotion += 1;
}

int main()
{
	// 스탯을 담을 배열을 선언(hp,mp, atk, def)
	int stats[4] = { 0 };

	//hp, mp, atk, def 순서로 스탯을 입력받는다
	while(true)
	{
		std::cout << "HP , MP, ATK, DEF 순서로 스탯을 입력하세요(숫자만, 스페이스로 구분): ";
		if (!(std::cin >> stats[0] >> stats[1] >> stats[2] >> stats[3]))
		{
			// 입력이 숫자가 아닌 경우
			std::cout << "잘못된 입력입니다. 다시 입력해주세요." << std::endl;

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 입력 버퍼 비우기

			continue; // 다시 입력 받기
		}

		if (stats[0] > 50 && stats[1] > 50 && stats[2] > 0 && stats[3] > 0) {
			break;
		}
		else {
			std::cout << "잘못된 입력입니다. HP와 MP는 50보다 커야하고, ATK와 DEF는 0보다 커야합니다. 다시 입력해주세요." << std::endl;
		}
	}

	int menu=0;
	int HPPotion = 0;
	int MPPotion = 0;
	int potionCount = 5;
	int level = 1;

	setPotion(potionCount, &HPPotion, &MPPotion); // 주소에 직접 접근해 포션 갯수 설정

	std::cout << "포션이 지급되었습니다. HP 포션: " << HPPotion << ", MP 포션: " << MPPotion << std::endl;

	while (true) {
		std::cout << "-----------------------------------------------------" << std::endl;
		std::cout << "-----------------<스탯 관리 시스템>------------------" << std::endl;
		std::cout << "[0]종료 \n[1] HP 포션 사용\n[2]MP 포션 사용\n[3]공격력 2배\n[4]방어력 2배\n[5]스탯 출력\n[6]레벨 업!(포션 지급)\n메뉴를 선택해주세요:";
		std::cin >> menu;

		if (menu == 0) {
			std::cout << "프로그램을 종료합니다." << std::endl;
			break;
		}

		switch (menu) {
			case 1:
				if (HPPotion > 0) {
					stats[0] += 20; // HP 포션 사용 시 HP 20 증가
					HPPotion--;
					std::cout << "HP 포션을 사용했습니다. 현재 HP: " << stats[0] << ", 남은 HP 포션: " << HPPotion << std::endl;
				}
				else {
					std::cout << "HP 포션이 없습니다." << std::endl;
				}
				break;

			case 2:
				if (MPPotion > 0) {
					stats[0] += 20; // MP 포션 사용 시 MP 20 증가
					MPPotion--;
					std::cout << "MP 포션을 사용했습니다. 현재 HP: " << stats[1] << ", 남은 MP 포션: " << MPPotion << std::endl;
				}
				else {
					std::cout << "MP 포션이 없습니다." << std::endl;
				}
				break;

			case 3:
				if (stats[2] > 0) {
					stats[2]*=2; // 공격력 2배
					std::cout << "공격력이 2배가 되었습니다 현재 공격력: " << stats[2] << std::endl;
				}
				else {
					std::cout << "공격력은 0이나 음수가 될 수 없습니다!" << std::endl;
				}
				break;

			case 4:
				if (stats[3] > 0) {
					stats[3] *= 2; // 방어력 2배
					std::cout << "방어력이 2배가 되었습니다 현재 방어력: " << stats[3] << std::endl;
				}
				else {
					std::cout << "방어력은 0이나 음수가 될 수 없습니다!" << std::endl;
				}
				break;

			case 5:
				std::cout << "현재 스탯: HP: " << stats[0] << ", MP: " << stats[1] << ", ATK: " << stats[2] 
					<< ", DEF: " << stats[3] <<"\n현재 레벨: "<< level <<" HP, MP 포션 갯수: "<< HPPotion<<","<< MPPotion << std::endl;
				break;

			case 6:
				std::cout << "레벨 업! 포션이 지급됩니다." << std::endl;
				getPotion(&HPPotion, &MPPotion); // 레벨 업 시 포션 지급
				level++;
				break;

			default:
				std::cout << "다시 입력해주세요. " << std::endl;
				break;
		}
	}
	return 0;
}