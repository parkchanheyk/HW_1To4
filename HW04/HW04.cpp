#include <string>
#include <vector>
#include <map>
#include <iostream>

// PotionRecipe class 정의--------------------------------------------------------------
class PotionRecipe
{
public:
    // 멤버 변수들을 초기화하는 생성자
    PotionRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
		this->name_ = name;
		this->ingredients_ = ingredients;   
    }

    // 물약 이름을 반환
    const std::string& GetName() const {
		return name_;
    }
    // 물약을 만들기 위한 재료 목록을 반환
    const std::vector<std::string>& GetIngredients() const {
        return ingredients_;
    }

private:
    std::string name_;
    std::vector<std::string> ingredients_;
};

// RecipeManager class 정의--------------------------------------------------------------
class RecipeManager
{
public:
    // 레시피 추가 후, 내부에 저장된 레시피의 포인터를 반환(없으면 nullptr)
    // - 예외처리 : 이미 있는 Recipe을 추가할 때, 자유롭게 처리
    PotionRecipe* AddRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
		//중복 이름 처리 방식은 같은 이름 없게
		if (FindRecipeByName(name) != nullptr) return nullptr; // 이미 같은 이름의 레시피가 존재하면 nullptr 반환
        
        recipes_.push_back(PotionRecipe(name, ingredients)); // 레시피 추가

		return &recipes_.back(); // 추가된 레시피의 포인터 반환
    }

    // 이름으로 1개 찾기(없으면 nullptr)
    PotionRecipe* FindRecipeByName(const std::string& name) {
        for(auto& recipe : recipes_) {
            if (recipe.GetName() == name) {
                return &recipe; // 이름이 일치하는 레시피의 포인터 반환
            }
		}
		return nullptr; // 일치하는 레시피가 없으면 nullptr 반환
    }

    // 재료로 여러 개 찾기(결과 복사본 반환)
    std::vector<PotionRecipe> FindRecipesByIngredient(const std::string& ingredient) const {
		
        std::vector<PotionRecipe> foundRecipes; // 결과를 저장할 벡터 선언!
        
        for (const auto& recipe : recipes_) { // 레시피 벡터를 순회하면서 접근

            for(const auto& ingr : recipe.GetIngredients()) { // 각 레시피의 재료 목록을 순회하면서 접근
                if (ingr == ingredient) { // 재료가 일치하는 경우
                    foundRecipes.push_back(recipe); // 결과 벡터에 해당 레시피 추가
                    break; // 해당 레시피는 이미 추가했으므로 다음 레시피로 넘어감
                }
			}
        }
		return foundRecipes; // 결과 벡터 반환
    }

    // 전체 레시피(읽기 전용 참조)
    const std::vector<PotionRecipe>& GetAllRecipes() const {
		return recipes_; // 전체 레시피에 대한 읽기 전용 참조 반환(함수 내에서 변경 불가능)
    }

private:
	std::vector<PotionRecipe> recipes_; // 레시피들을 저장하는 벡터 변수 타입을 클래스 객체로 저장하는 벡터
};

// StockManager class 정의--------------------------------------------------------------
class StockManager
{
public:
    static constexpr int MAX_STOCK = 3;

    // 레시피 추가 시 자동으로 3개 재고 세팅
    void InitializeStock(const std::string& potionName) {
		potionStock_[potionName] = MAX_STOCK; // 레시피가 추가될 때 해당 물약의 재고를 MAX_STOCK으로 초기화
    }

    // 재고가 1개 이상이면 1개 지급(감소)하고 true, 아니면 false
    bool DispensePotion(const std::string& potionName) {
        if(potionStock_.count(potionName) && potionStock_[potionName] > 0) { // potionName이 맵에 존재하고 재고가 1개 이상인 경우
            --potionStock_[potionName]; // 재고 감소
            return true; // 지급 성공
		}
		return false; // 재고가 없거나 potionName이 맵에 존재하지 않는 경우 지급 실패
    }

    // 공병 반환(재고 +1).
    // - 예외처리 : 단, MAX_STOCK 초과 불가
    void ReturnPotion(const std::string& potionName) {
        if (potionStock_.count(potionName) && potionStock_[potionName] < MAX_STOCK) { // potionName이 맵에 존재하고 재고가 MAX_STOCK보다 작은 경우
            ++potionStock_[potionName]; // 재고 증가
        }
    }

    // 현재 재고 조회(없으면 0)
    int GetStock(const std::string& potionName) const {
		return potionStock_.count(potionName) ? potionStock_.at(potionName) : 0; // potionName이 맵에 존재하면 해당 재고 수 반환, 없으면 0 반환
    }

private:
	std::map<std::string, int> potionStock_; // 물약 이름을 키로, 재고 수를 값으로 저장하는 맵
};

// AlchemyWorkshop class 정의--------------------------------------------------------------
class AlchemyWorkshop
{
public:
    // 레시피 추가 + 자동 재고 3개 생성
    // (중복 이름 처리 방식은 구현 자유: 덮어쓰기/거부/중복허용 등)
    void AddRecipe(const std::string& potionName, const std::vector<std::string>& ingredients) { // 레시피가 추가되면 조합식과 재고가 자동으로 세팅되도록 구현해야함
		recipeManager_.AddRecipe(potionName, ingredients); // 레시피 매니저에 레시피 추가

		stockManager_.InitializeStock(potionName); // 레시피가 추가될 때 해당 물약의 재고를 MAX_STOCK으로 초기화
    }

    // 레시피/재고 출력(형식은 자유)
    void DisplayAllRecipes() const{
		std::vector<PotionRecipe> recipes = recipeManager_.GetAllRecipes(); // 레시피 매니저에서 전체 레시피를 가져와서 출력

        for (const auto& recipe : recipes) {
            std::cout << "물약 이름: " << recipe.GetName() << "\n재료: ";
            for (const auto& ingredient : recipe.GetIngredients()) {
                std::cout << ingredient << " ";
            }
            std::cout << "\n재고: " << stockManager_.GetStock(recipe.GetName()) << "\n\n"; // 각 레시피의 재고도 함께 출력
		}
    }

    // 해당 재료를 포함하는 레시피들 중, 재고 있는 것들을 지급처리
    // 반환: 실제로 지급된 물약 이름 목록(없으면 빈 벡터)
    std::vector<std::string> DispensePotionsByIngredient(const std::string& ingredient) {
		std::vector<std::string> dispensedPotions; // 지급된 물약 이름을 저장할 벡터

		auto recipes = recipeManager_.FindRecipesByIngredient(ingredient); // 레시피 매니저에서 해당 재료를 포함하는 레시피들을 찾아서 반환

        for(const auto& recipe : recipes) { // 해당 재료를 포함하는 레시피들을 순회하면서 접근
            if (stockManager_.DispensePotion(recipe.GetName())) { // 각 레시피의 물약을 지급 처리하고 성공 여부 확인
                dispensedPotions.push_back(recipe.GetName()); // 지급이 성공하면 해당 물약 이름을 결과 벡터에 추가
            }
		}

		return dispensedPotions; // 지급된 물약 이름 목록 반환

    }

    // potionName으로 검색하여 재고 있으면 지급처리하고 true, 재고 없으면 false
    bool DispensePotionByName(const std::string& potionName) {
		return stockManager_.DispensePotion(potionName); // StockManager의 DispensePotion 함수를 호출하여 potionName에 해당하는 물약을 지급 처리하고 결과 반환
    }

    // 재고 조회 (이름)
    int GetStockByName(const std::string& potionName) const {
		return stockManager_.GetStock(potionName); // StockManager의 GetStock 함수를 호출하여 potionName에 해당하는 물약의 재고 수 반환
    }

    // potionName에 공병을 반환 처리(최대 3개 제한)
    void ReturnPotionByName(const std::string& potionName) {
		return stockManager_.ReturnPotion(potionName); // StockManager의 ReturnPotion 함수를 호출하여 potionName에 해당하는 물약의 재고를 증가 처리
    }

private:
    RecipeManager recipeManager_;
    StockManager stockManager_;
};

void main()
{
	AlchemyWorkshop workshop; // 연금술 작업장 객체 생성(바구니 역할)

    /* 레시피 추가는 하나의 클래스 객체안에서 이루어지지만 더욱 내부적으로는 하나의 레시피가 하나의 객체(PotionRecipe)가 되도록 설계해야 한다
    
      비주얼 스투디오 자동완성 기능은 신인가 GOAT 찬양합니다.     
    */

	// 레시피 추가 및 자동 재고 초기화
    workshop.AddRecipe("Healing Potion", { "Herb", "Water" });
    workshop.AddRecipe("Mana Potion", { "Magic Water", "Crystal" });
    workshop.AddRecipe("Stamina Potion", { "Herb", "Berry" });
    workshop.AddRecipe("Fire Resistance Potion", { "Fire Flower", "Ash" });

    std::cout << "=== 초기 상태 (레시피 추가 + 재고 자동 3개) ===\n";
    workshop.DisplayAllRecipes();

    std::cout << "\n[재고 확인] Healing Potion 재고: "
        << workshop.GetStockByName("Healing Potion") << "\n";

    std::cout << "\n=== 이름으로 지급 테스트 (Healing Potion 3회 지급) ===\n";
    std::cout << "1회 지급: " << (workshop.DispensePotionByName("Healing Potion") ? "성공" : "실패") << "\n";
    std::cout << "2회 지급: " << (workshop.DispensePotionByName("Healing Potion") ? "성공" : "실패") << "\n";
    std::cout << "3회 지급: " << (workshop.DispensePotionByName("Healing Potion") ? "성공" : "실패") << "\n";

    std::cout << "현재 재고: " << workshop.GetStockByName("Healing Potion") << "\n";

    std::cout << "4회 지급(재고 없으면 실패): "
        << (workshop.DispensePotionByName("Healing Potion") ? "성공" : "실패") << "\n";

    std::cout << "\n=== 재료로 지급 테스트 (ingredient = Herb) ===\n";
    std::vector<std::string> dispensed = workshop.DispensePotionsByIngredient("Herb");

    std::cout << "지급된 물약 수: " << dispensed.size() << "\n";
    for (const std::string& name : dispensed)
        std::cout << "- " << name << "\n";

    std::cout << "\n=== 공병 반환 테스트 (Healing Potion) ===\n";
    workshop.ReturnPotionByName("Healing Potion");
    workshop.ReturnPotionByName("Healing Potion");
    workshop.ReturnPotionByName("Healing Potion"); // 이미 3이면 더 올라가면 안 됨

    std::cout << "반환 후 재고(최대 3 유지): "
        << workshop.GetStockByName("Healing Potion") << "\n";

    std::cout << "\n=== 최종 상태 ===\n";
    workshop.DisplayAllRecipes();
}

