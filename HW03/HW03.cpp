// HW03.cpp

#include <iostream>
#include <algorithm>
#include <string>

// 인벤토리를 위한 아이템 클래스 부터 정의하자

class Item {
public:
	Item(const std::string& name = "None", int price = 0)
		: name(name), price(price) {
	}

	const std::string& getName() const { 
		return name; // 아이템 이름 반환(함수 내 변경 불가능)
	} 
	int GetPrice() const { 
		return price; // 아이템 가격 반환(함수 내 변경 불가능)
	}

private:
	std::string name;
	int price;
};

bool compareItemPrice(const Item& item1, const Item& item2) { // 아이템 가격을 기준으로 비교하는 함수
	return item1.GetPrice() > item2.GetPrice();
}

// Inventory 를 템플릿 클래스로 정의

template <typename T>
class Inventory 
{
public:
	Inventory(int capacity = 10 ) : capacity(capacity) {
		items = new T[capacity]; // 아이템을 저장할 배열 동적 할당
	}

	Inventory(const Inventory<T>& other) : capacity(other.capacity), size(other.size) {
		// 복사 생성자에서 다른 인벤토리의 용량과 크기를 복사하여 초기화 

		items = new T[capacity]; // 새로운 배열 할당(아마도 아이템 클래스를 저장할 배열)

		for (int i = 0; i < size; ++i) {
			items[i] = other.items[i]; // 아이템 복사
		}

		std::cout << "인벤토리 복사 완료" << std::endl;
	}

	~Inventory() { // 소멸자에서 동적 할당된 배열 해제 
		if (items != nullptr) {
			delete[] items;
		}
	}

	int GetSize() const {
		return size; // 현재 인벤토리에 저장된 아이템 수 반환(함수 내 변경 불가능)
	}
	int GetCapacity() const {
		return capacity; // 인벤토리의 최대 용량 반환(함수 내 변경 불가능)
	}

	void PrintAllItems() const {
		for (int i = 0; i < size; ++i) {
			std::cout << "아이템 이름: " << items[i].getName()
				<< ", 가격: " << items[i].GetPrice() << std::endl;
		}
	}

	void AddItem(const T& item) {
		if (size >= capacity) {
			std::cout << "인벤토리가 가득 찼습니다. 아이템을 추가할 수 없습니다." << std::endl;
			return;
		}
		items[size] = item; // 아이템 추가
		++size; // 아이템 수 증가
	}

	void RemoveLastItem() {
		if (size <= 0) {
			std::cout << "인벤토리가 비어 있습니다. 아이템을 제거할 수 없습니다." << std::endl;
			return;
		}
		--size; // 마지막 아이템 제거(메모리 접근을 안하게 만들어버림 실제로 제거는 아님)
		// 아이템이 추가될 때 덮어쓰여질 것이므로 실제로 메모리를 해제할 필요는 없음
	}

	// 1. 새로운 동적배열 만들기(기존 동적배열은 아직 그대로 가지고 있어야 함)
	// 2. 기존 동적배열의 정보를 새로운 동적배열로 이동시키기
	// 3. 기존 동적배열 제거
	void Resize(int newCapacity) {
		if (newCapacity <= capacity) {
			std::cout << "새 용량은 현재 용량보다 커야 합니다." << std::endl;
			return;
		}
		T* newItems = new T[newCapacity]; // 새로운 동적 배열 생성
		for (int i = 0; i < size; ++i) {
			newItems[i] = items[i]; // 기존 아이템을 새로운 배열로 복사
		}
		delete[] items; // 기존 동적 배열 해제
		items = newItems; // 기존 배열 포인터를 새로운 배열을 가르키도록
		capacity = newCapacity; // 용량 업데이트
	}

	// std::sort(pItems_, pItems_ + size_, compareItemsByPrice);
	void SortItems() {
		std::sort(items, items + size, compareItemPrice); // 아이템 가격을 기준으로 정렬
		std::cout << "아이템 정렬 완료" << std::endl;	
	}

private:
	T* items; // 아이템을 저장할 배열 포인터
	int capacity; // 인벤토리의 최대 용량
	int size=0; // 현재 인벤토리에 저장된 아이템 수
	
};

int main()
{
	Inventory<Item>* itemInventory = new Inventory<Item>(); // 아이템 인벤토리 생성
	for (int i = 0; i < 10; ++i) {
		itemInventory->AddItem(Item("Item" + std::to_string(i), i+1)); // 아이템 인벤토리에 추가
	}

	itemInventory->PrintAllItems(); // 아이템 인벤토리에 있는 모든 아이템 출력

	std::cout << "인벤토리 크기: " << itemInventory->GetSize() << std::endl; // 인벤토리 크기 출력

	// 인벤토리를 확장해보자!
	itemInventory->Resize(20); // 인벤토리 용량 확장
	for (int i = 10; i < 15; ++i) {
		itemInventory->AddItem(Item("NewItem" + std::to_string(i), (i+1))); // 새로운 아이템 추가 남은 공간은 (none,0)으로 채워짐
	}

	itemInventory->PrintAllItems(); // 아이템 인벤토리에 있는 모든 아이템 출력
	std::cout << "인벤토리 크기: " << itemInventory->GetSize() << std::endl; // 인벤토리 크기 출력

	itemInventory->SortItems(); // 아이템 정렬
	itemInventory->PrintAllItems(); // 아이템 인벤토리에 있는 모든 아이템 출력

	//인벤토리 복사
	Inventory<Item>* itemInventory2 = new Inventory<Item>(*itemInventory); // 복사 생성자 호출하여 새로운 인벤토리 생성	
	itemInventory2->PrintAllItems(); // 복사된 인벤토리에 있는 모든 아이템 출력

	delete itemInventory; // 동적 할당된 인벤토리1 해제
	delete itemInventory2; // 동적 할당된 인벤토리2 해제
	return 0;
}