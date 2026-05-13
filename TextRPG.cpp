#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

struct Item {
    string name = "";
    int price = 0;
    void PrintInfo() const {
        cout << name << " (" << price << "G)" << endl;

    }
};

bool compareByPrice(const Item& a, const Item& b) {
    return a.price < b.price;
}

template<typename T>
class Inventory {
private:
    T* pItems_;
    int capacity_;
    int size_;
public:
    Inventory(int capacity) : capacity_(capacity), size_(0) {
        pItems_ = new T[capacity_];
    }
    ~Inventory() {
        delete[] pItems_;
    }
    Inventory(const Inventory& other) : capacity_(other.capacity_), size_(other.size_) {
        pItems_ = new T[capacity_];
        for (int i = 0; i < size_; i++) {
            pItems_[i] = other.pItems_[i];
        }
    }
    T& operator[](int index) {
        return pItems_[index];
    }
    void Additem(T item) {
        if (size_ == capacity_) {
            cout << "아이템 추가 시도... (현재 " << size_ << "/" << capacity_ << ")" << endl;
            cout << "-> 인벤토리 자동 확장! (" << capacity_ << " -> " << capacity_ * 2 << ")" << endl;
            Resize(capacity_ * 2);
            cout << "-> 아이템 추가 완료" << endl;
        }
        pItems_[size_++] = item;

    }
    void RemoveLastItem() {
        size_--;
    }
    void PrintAllItems() {
        for (int i = 0; i < size_; i++) {
            pItems_[i].PrintInfo();
        }
    }
    int GetSize() {
        return size_;
    }
    int GetCapacity() {
        return capacity_;
    }
    void SortItems() {
        sort(pItems_, pItems_ + size_, compareByPrice);
    }
    void RemoveItem(int index) {
        for (int i = index; i < size_ - 1; i++) {
            pItems_[i] = pItems_[i + 1];
        }
        size_--;
    }

    void Resize(int newCapacity) {
        T* newArray = new T[newCapacity];
        for (int i = 0; i < size_; i++) {
            newArray[i] = pItems_[i];
        }
        delete[] pItems_;
        pItems_ = newArray;
        capacity_ = newCapacity;
    }
};

struct PotionRecipe {
    string PotionName;
    string PotionI1;
    int PotionIN1;
    string PotionI2;
    int PotionIN2;
};

class AlchemyWorkshop {
private:
    vector<PotionRecipe> PR;
    map<string, int> potionStock_;
    int emptybottle = 0;
    const int MAX_STOCK = 5;
public:
    AlchemyWorkshop() {
        PR = {
            {"HP포션","허브",1,"맑은물",1},
            {"MP포션","별조각",1,"맑은물",2},
        };
        potionStock_["HP포션"] = 3;
        potionStock_["MP포션"] = 3;
    }

    void ShowAllRecipes() {
        for (const auto& AR : PR) {
            cout << AR.PotionName << ": " << AR.PotionI1 << " x" << AR.PotionIN1 << ", " << AR.PotionI2 << " x" << AR.PotionIN2 << endl;
        }
    }
    void SearchByName(string name) {
        bool found = false;
        for (const auto& AR : PR) {
            if (name == AR.PotionName) {
                cout << AR.PotionName << ": " << AR.PotionI1 << " x" << AR.PotionIN1 << ", " << AR.PotionI2 << " x" << AR.PotionIN2 << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "찾을 수 없습니다." << endl;
        }
    }
    void SearchByIngredient(string ingredient) {
        int count = 0;
        for (const auto& AR : PR) {
            if (ingredient == AR.PotionI1 || ingredient == AR.PotionI2) {
                cout << AR.PotionName << ": " << AR.PotionI1 << " x" << AR.PotionIN1 << ", " << AR.PotionI2 << " x" << AR.PotionIN2 << endl;
                ++count;
            }
        }
        if (count == 0) {
            cout << "찾을 수 없습니다." << endl;
        }
        else {
            cout << "총 " << count << "개의 레시피를 찾았습니다." << endl;
        }
    }
    void DispensePotion(string name) {
        if (potionStock_[name] > 0) {
            potionStock_[name]--;
            cout << "-> " << name << " 지급  (재고: " << potionStock_[name] << ")" << endl;
            emptybottle++;
        }
        else {
            cout << name << " 지급 실패: 재고 없음!" << endl;
        }
    }
    void ReturnPotion(string name) {
        if (emptybottle > 0) {
            if (potionStock_[name] < MAX_STOCK) {
                potionStock_[name]++;
                cout << "공병 반환  " << name << "재고: " << potionStock_[name] << endl;
                emptybottle--;
                cout << "남은 공병 수: " << emptybottle << "개" << endl;
            }
            else {
                cout << "개수 초과! 반환이 취소됩니다." << endl;
            }

        }
        else if (emptybottle <= 0) {
            cout << name << " 반환 실패: 공병 없음!" << endl;
        }
    }
    int GetStock(string name) {
        return potionStock_[name];
    }
};

class Monster;

class Player {
protected:
    string name, job;
    int level, hp, MaxHP, mp, MaxMP, power, defence, exp, maxExp;
public:
    Player(string name, int stat[]) :name(name), job(""), level(1), hp(stat[0]), MaxHP(stat[0]), mp(stat[1]), MaxMP(stat[1]), power(stat[2]), defence(stat[3]), exp(0), maxExp(100) {}
    virtual void attack(Monster* monster) = 0;
    virtual ~Player() {};
    void printPlayerStatus() {
        cout << "================================" << endl;
        cout << name << " 의 현재 능력치" << endl;
        cout << "================================" << endl;
        cout << "HP: " << hp << "    MP: " << mp << endl;
        cout << "공격력: " << power << "    방어력: " << defence << endl;
        cout << "레벨: " << level << "   경험치:" << exp << "/" << maxExp << endl;
        cout << "================================" << endl;
    }
    void setName(string n) {
        name = n;
    }
    void setJob(string j) {
        job = j;
    }
    void setLevel(int l) {
        level = l;
    }
    void setHP(int h) {
        hp = h < 0 ? 0 : h;
    }
    void setMP(int m) {
        mp = m;
    }
    void setPower(int p) {
        power = p;
    }
    void setDefence(int d) {
        defence = d;
    }
    string getName() {
        return name;
    }
    string getJob() {
        return job;
    }
    int getLevel() {
        return level;
    }
    int getHP() {
        return hp;
    }
    int getMP() {
        return mp;
    }
    int getPower() {
        return power;
    }
    int getDefence() {
        return defence;
    }
    int getMaxHP() {
        return MaxHP;
    }
    int getMaxMP() {
        return MaxMP;
    }
    int getExp() {
        return exp;
    }
    int getmaxExp() {
        return maxExp;
    }

    void gainExp(int amount) {
        exp += amount;
        while (exp >= maxExp) {
            levelUp();
        }
    }

    void levelUp() {
        level++;
        exp = exp - maxExp;
        maxExp += 100;
        power += 5;
        defence += 3;
        MaxHP += 30;
        hp = MaxHP;
        MaxMP += 15;
        mp = MaxMP;
        cout << "================================" << endl;
        cout << "레벨업! 현재 레벨: " << level << endl;
        cout << "공격력 +" << 5 << " → " << power << endl;
        cout << "방어력 +" << 3 << " → " << defence << endl;
        cout << "최대HP +" << 30 << " → " << MaxHP << endl;
        cout << "최대MP +" << 15 << " → " << MaxMP << endl;
        cout << "HP와 MP를 모두 회복합니다." << endl;
        cout << "================================" << endl;

    }
};

class Monster {
protected:
    string name, dropItemName;
    int hp, power, defence, dropItemPrice, expReward;
public:
    Monster(string name, int hp, int power, int defence, int expReward) : name(name), hp(hp), power(power), defence(defence), dropItemName(""), dropItemPrice(0), expReward(expReward) {

    }
    string getName() const { return name; }
    int getHP() const { return hp; }
    int getPower() const { return power; }
    int getDefence() const { return defence; }
    string getDropItemName() const {
        return dropItemName;
    }
    int getDropItemPrice() const {
        return dropItemPrice;
    }
    int getExpReward() const {
        return expReward;
    }
    void setHP(int h) { hp = h < 0 ? 0 : h; }
    void setDropItemName(string n) { dropItemName = n; }
    void setDropItemPrice(int p) { dropItemPrice = p; }
    void attack(Player* player) {
        int damage = power - player->getDefence();
        if (damage <= 0) {
            damage = 1;
        }
        player->setHP(player->getHP() - damage);
        cout << name << "이(가) 공격! " << damage << " 데미지!" << endl;
        cout << player->getName() << "의 남은 체력: " << player->getHP() << endl;
    }
};
class Slime : public Monster {
public:
    Slime() : Monster("슬라임", 30, 10, 5, 30) {
        dropItemName = "슬라임의 끈적한 젤리";
        dropItemPrice = 30;
    }
};
class Goblin : public Monster {
public:
    Goblin() : Monster("고블린", 100, 20, 15, 90) {
        dropItemName = "고블린의 한쪽 귀";
        dropItemPrice = 70;
    }
};
class Orc : public Monster {
public:
    Orc() : Monster("오크", 200, 40, 40, 200) {
        dropItemName = "오크의 나무 몽둥이";
        dropItemPrice = 200;
    }
};
class Dragon : public Monster {
public:
    Dragon() : Monster("드래곤", 600, 100, 80, 1000) {
        dropItemName = "드래곤의 깨끗한 비늘";
        dropItemPrice = 1000;
    }
};


class Warrior : public Player {
public:
    Warrior(string name, int stat[]) : Player(name, stat) {
        defence += 30;
        job = "전사";
        cout << "*전사로 전직하였습니다. (방어력 + 30)" << endl;
        cout << "*검으로 공격한다!" << endl;
        cout << "--------------------------------" << endl;
        cout << "닉네임: " << name << " | 직업: " << job << " | Lv." << level << endl;
        cout << "HP: " << hp << " | MP: " << mp << " | 공격력: " << power << " | 방어력: " << defence << endl;
    }
    void attack(Monster* monster) override {
        int monsterStartHP = monster->getHP();
        int damage = power - monster->getDefence();
        if (damage <= 0) damage = 1;
        monster->setHP(monster->getHP() - damage);
        cout << "검으로 강하게 내려칩니다." << endl;
        cout << monster->getName() << "에게 " << damage << "데미지!" << endl;
        cout << monster->getName() << " HP: " << monsterStartHP << " -> " << monster->getHP() << endl;
    }
};
class Magician : public Player {
public:
    Magician(string name, int stat[]) : Player(name, stat) {
        MaxMP += 30;
        mp += 30;
        job = "마법사";
        cout << "*마법사로 전직하였습니다. (mp + 30)" << endl;
        cout << "*파이어볼을 발사한다!" << endl;
        cout << "--------------------------------" << endl;
        cout << "닉네임: " << name << " | 직업: " << job << " | Lv." << level << endl;
        cout << "HP: " << hp << " | MP: " << mp << " | 공격력: " << power << " | 방어력: " << defence << endl;
    }
    void attack(Monster* monster) override {
        int monsterStartHP = monster->getHP();
        int damage = power - monster->getDefence();
        if (damage <= 0) damage = 1;
        monster->setHP(monster->getHP() - damage);
        cout << "파이어볼을 발사합니다." << endl;
        cout << monster->getName() << "에게 " << damage << "데미지!" << endl;
        cout << monster->getName() << " HP: " << monsterStartHP << " -> " << monster->getHP() << endl;
    }
};
class Rogue : public Player {
public:
    Rogue(string name, int stat[]) : Player(name, stat) {
        power += 30;
        job = "도적";
        cout << "*도적으로 전직하였습니다. (공격력 + 30)" << endl;
        cout << "*단검으로 공격한다!" << endl;
        cout << "--------------------------------" << endl;
        cout << "닉네임: " << name << " | 직업: " << job << " | Lv." << level << endl;
        cout << "HP: " << hp << " | MP: " << mp << " | 공격력: " << power << " | 방어력: " << defence << endl;
    }
    void attack(Monster* monster) override {
        int monsterStartHP = monster->getHP();
        int damage = (power - monster->getDefence()) / 5;
        if (damage <= 0) damage = 1;
        int totalDamage = damage * 5;
        monster->setHP(monster->getHP() - totalDamage);
        cout << "은밀하게 적의 뒤를 5회 공격합니다." << endl;
        cout << monster->getName() << "에게 " << damage << " x5 = " << totalDamage << "데미지!" << endl;
        cout << monster->getName() << " HP: " << monsterStartHP << " -> " << monster->getHP() << endl;
    }
};
class Archer : public Player {
public:
    Archer(string name, int stat[]) : Player(name, stat) {
        hp += 30;
        MaxHP += 30;
        job = "궁수";
        cout << "*궁수로 전직하였습니다. (HP + 30)" << endl;
        cout << "*화살로 공격한다!" << endl;
        cout << "--------------------------------" << endl;
        cout << "닉네임: " << name << " | 직업: " << job << " | Lv." << level << endl;
        cout << "HP: " << hp << " | MP: " << mp << " | 공격력: " << power << " | 방어력: " << defence << endl;
    }
    void attack(Monster* monster) override {
        int monsterStartHP = monster->getHP();
        int damage = (power - monster->getDefence()) / 3;
        if (damage <= 0) damage = 1;
        int totalDamage = damage * 3;
        monster->setHP(monster->getHP() - totalDamage);
        cout << "화살을 3발 발사합니다." << endl;
        cout << monster->getName() << "에게 " << damage << " x3 = " << totalDamage << "데미지!" << endl;
        cout << monster->getName() << " HP: " << monsterStartHP << " -> " << monster->getHP() << endl;
    }
};


void printStatus(string name, int stat[]) {
    cout << "================================" << endl;
    cout << name << " 의 현재 능력치" << endl;
    cout << "================================" << endl;
    cout << "HP: " << stat[0] << "    MP: " << stat[1] << endl;
    cout << "공격력: " << stat[2] << "    방어력: " << stat[3] << endl;
    cout << "================================" << endl;
}

void setPotion(int count, Inventory<Item>& inventory) {
    for (int i = 0; i < count; i++) {
        inventory.Additem({ "HP포션", 50 });
        inventory.Additem({ "MP포션", 50 });
    }
}

void usePotion(Inventory<Item>& inventory, Player* player) {
    int hpCount = 0, mpCount = 0;
    for (int i = 0; i < inventory.GetSize(); i++) {
        if (inventory[i].name == "HP포션") hpCount++;
        if (inventory[i].name == "MP포션") mpCount++;
    }
    cout << "[ 인벤토리 ]" << endl;
    cout << "1. HP포션 (남은: " << hpCount << "개)" << endl;
    cout << "2. MP포션 (남은: " << mpCount << "개)" << endl;
    cout << "사용할 아이템 번호: ";
    int itemNumber;
    cin >> itemNumber;
    switch (itemNumber) {
    case 1:
        for (int i = 0; i < inventory.GetSize(); i++) {
            if (inventory[i].name == "HP포션") {
                int beforeHP = player->getHP();
                player->setHP(min(player->getHP() + 20, player->getMaxHP()));
                inventory.RemoveItem(i);
                cout << "* HP포션 사용! (" << beforeHP << " -> " << player->getHP() << ")" << endl;
                break;
            }
        }
        break;

    case 2:
        for (int i = 0; i < inventory.GetSize(); i++) {
            if (inventory[i].name == "MP포션") {
                int beforeMP = player->getMP();
                player->setMP(min(player->getMP() + 20, player->getMaxMP()));
                inventory.RemoveItem(i);
                cout << "* MP포션 사용! (" << beforeMP << " -> " << player->getMP() << ")" << endl;
                break;
            }
        }
        break;
    }
}



int main() {
    string name;
    const int SIZE = 4;
    int stat[SIZE] = { 0 };//stat[0] = HP, stat[1] = MP, stat[2] = 공격력, stat[3] = 방어력
    int PotionCount = 5;
    AlchemyWorkshop alchemy;
    bool isGameStart = false;
    Inventory<Item> inventory(10);
    int currentRoom = 0;
    bool roomCleared[3] = { false, false, false };
    vector<Monster*> rooms = { new Slime(), new Goblin(), new Orc(), new Dragon() };
    cout << "================================" << endl;
    cout << "[던전 탈출 텍스트 RPG]" << endl;
    cout << "================================" << endl;
    cout << "용사의 이름을 입력해주세요: ";
    cin >> name;
    cout << endl;
    while (1) {
        cout << "HP와 MP를 입력해주세요: ";
        cin >> stat[0] >> stat[1];
        cout << endl;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "숫자를 입력해주세요." << endl;
            continue;
        }
        if (stat[0] >= 50 && stat[1] >= 50) {
            break;
        }
        cout << "HP나 MP의 값이 너무 작습니다. 다시 입력해주세요.(50이상)" << endl;
    }
    while (1) {
        cout << "공격력과 방어력을 입력해주세요: ";
        cin >> stat[2] >> stat[3];
        cout << endl;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "숫자를 입력해주세요." << endl;
            continue;
        }
        if (stat[2] >= 50 && stat[3] >= 30) {
            break;
        }
        cout << "공격력이나 방어력이 너무 작습니다. 다시 입력해주세요.(50,30이상)" << endl;
    }

    printStatus(name, stat);


    setPotion(PotionCount, inventory); // 포인터 없이 넘기면 함수가 받은건 복사본이기 때문에 원본이 바뀌지않음
    cout << "*HP 포션 5개, MP 포션 " << PotionCount << "개가 기본 지급되었습니다." << endl;
    cout << "================================" << endl;
    cout << "< 캐릭터 강화 >" << endl;
    cout << "1. HP UP   2. MP UP   3. 공격력 2배" << endl;
    cout << "4. 방어력 2배  5. 현재 능력치  0. 게임 시작" << endl;
    cout << "================================" << endl;
    int choice;
    while (!isGameStart) {
        cout << "번호를 선택해주세요: ";
        cin >> choice;
        switch (choice) {
        case 1: {
            bool found = false;
            for (int i = 0; i < inventory.GetSize(); i++) {
                if (inventory[i].name == "HP포션") {
                    stat[0] += 20;
                    inventory.RemoveItem(i);
                    int hpCount = 0;
                    for (int j = 0; j < inventory.GetSize(); j++) {
                        if (inventory[j].name == "HP포션") hpCount++;
                    }
                    cout << "*HP가 20 증가했습니다. (HP 포션 차감: 남은 포션 " << hpCount << "개)" << endl;
                    found = true;
                    break;
                }
            }
            if (!found) cout << "HP포션이 부족합니다." << endl;
            break;
        }
        case 2: {
            bool found = false;
            for (int i = 0; i < inventory.GetSize(); i++) {
                if (inventory[i].name == "MP포션") {
                    stat[1] += 20;
                    inventory.RemoveItem(i);
                    int mpCount = 0;
                    for (int j = 0; j < inventory.GetSize(); j++) {
                        if (inventory[j].name == "MP포션") mpCount++;
                    }
                    cout << "*MP가 20 증가했습니다. (MP 포션 차감: 남은 포션 " << mpCount << "개)" << endl;
                    found = true;
                    break;
                }
            }
            if (!found) cout << "MP포션이 부족합니다." << endl;
            break;
        }
        case 3:
            stat[2] *= 2;
            break;
        case 4:
            stat[3] *= 2;
            break;
        case 5:
            printStatus(name, stat);
            break;
        case 0:
            isGameStart = true;
            break;
        }

    }
    cout << "게임을 시작합니다!" << endl;
    Player* player = nullptr;

    int JobChoise;
    cout << "<전직 시스템>" << endl;
    cout << name << "님, 직업을 선택해주세요." << endl;
    cout << "1. 전사   2. 마법사   3. 도적   4. 궁수" << endl;
    while (true) {
        cout << "선택: ";
        cin >> JobChoise;
        if (JobChoise <= 4 && JobChoise >= 1) {
            switch (JobChoise) {
            case 1:
                player = new Warrior(name, stat);
                break;
            case 2:
                player = new Magician(name, stat);
                break;
            case 3:
                player = new Rogue(name, stat);
                break;
            case 4:
                player = new Archer(name, stat);
                break;
            }
            break;
        }
        else {
            cout << "옳지 않은 입력입니다. 다시 입력해주세요." << endl;
        }
    }

    while (true) {
        int MenuChoise;
        cout << "=== 메인 메뉴 ===" << endl;
        cout << " 1. 던전 입장" << endl;
        cout << " 2. 인벤토리 확인" << endl;
        cout << " 3. 포션 제작소" << endl;
        cout << " 0. 게임 종료" << endl;
        cout << "선택: ";
        cin >> MenuChoise;

        switch (MenuChoise) {
        case 1: {
            if (roomCleared[0] && roomCleared[1] && roomCleared[2]) {
                cout << "★ 보스방 개방!" << endl;
                cout << "보스 드래곤 등장!" << endl;
                Monster* boss = rooms[3];
                bool bossOver = false;
                while (player->getHP() > 0 && boss->getHP() > 0 && !bossOver) {
                    cout << "--- 플레이어 턴 ---" << endl;
                    cout << "1. 공격" << endl;
                    cout << "2. 아이템 사용" << endl;
                    int turnChoice;
                    cout << "선택: ";
                    cin >> turnChoice;
                    switch (turnChoice) {
                    case 1:
                        player->attack(boss);
                        if (boss->getHP() <= 0) {
                            cout << "드래곤을 처치했습니다!" << endl;
                            cout << "=== 게임 클리어! ===" << endl;
                            bossOver = true;
                            for (auto r : rooms) delete r;
                            delete player;
                            return 0;
                            break;
                        }
                        boss->attack(player);
                        if (player->getHP() <= 0) {
                            cout << "게임 오버..." << endl;
                            for (auto r : rooms) delete r;
                            return 0;
                        }
                        break;
                    case 2: 
                        usePotion(inventory, player);
                        break;
                    }
                }
            }
            else {
                cout << currentRoom + 1 << "번 방: " << rooms[currentRoom]->getName() << "등장!" << endl;
                Monster* monster = rooms[currentRoom];
                cout << "[ 전투 시작! ]" << endl;
                bool battleOver = false;
                while (player->getHP() > 0 && monster->getHP() > 0 && !battleOver) {
                    cout << "--- 플레이어 턴 ---" << endl;
                    cout << "1. 공격" << endl;
                    cout << "2. 아이템 사용" << endl;
                    int turnChoice;
                    cout << "선택: ";
                    cin >> turnChoice;
                    switch (turnChoice) {
                    case 1:
                        player->attack(monster);
                        if (monster->getHP() <= 0) {
                            cout << currentRoom + 1 << "번 방 클리어!" << endl;
                            roomCleared[currentRoom] = true;
                            currentRoom++;
                            cout << "-> " << monster->getDropItemName() << " 획득!" << endl;
                            cout << "-> 인벤토리에 저장되었습니다." << endl;
                            Item droppedItem = { monster->getDropItemName(), monster->getDropItemPrice() };
                            inventory.Additem(droppedItem);
                            player->gainExp(monster->getExpReward());
                            cout << "현재 경험치: " << player->getExp() << "/" << player->getmaxExp() << endl;
                            battleOver = true;
                            break;
                        }
                        monster->attack(player);
                        if (player->getHP() <= 0) {
                            cout << "게임 오버..." << endl;
                            for (auto r : rooms) delete r;
                            return 0;
                        }
                        break;
                    case 2: 
                        usePotion(inventory, player);
                        break;
                    }


                }

            }
            break;
        }//case 1 끝



        case 2:
        {
            inventory.SortItems();
            cout << "[ 가격순 정렬 후 인벤토리 (" << inventory.GetSize() << "/" << inventory.GetCapacity() << ") ]" << endl;
            for (int i = 0; i < inventory.GetSize(); i++) {
                cout << i + 1 << ". ";
                inventory[i].PrintInfo();
            }
            break;
        }


        case 3:
        {
            int PC;          
            cout << "=== 포션 제작소 ===" << endl;
            cout << "1. 전체 레시피 보기" << endl;
            cout << "2. 포션 이름으로 검색" << endl;
            cout << "3. 재료로 검색" << endl;
            cout << "4. 포션 지급/반환" << endl;
            cout << "0. 돌아가기" << endl;
            bool workshop = true;
            while (workshop) {
                cout << "선택: ";
                cin >> PC;
                switch (PC) {
                case 1:
                    cout << "전체 레시피 목록" << endl;
                    alchemy.ShowAllRecipes();
                    break;
                case 2: {
                    string name;
                    cout << "검색할 포션 이름(HP포션, MP포션): ";
                    cin >> name;
                    alchemy.SearchByName(name);
                    break;
                }
                case 3:
                {
                    string name1;
                    cout << "검색할 재료 이름(허브, 맑은물, 별조각): ";
                    cin >> name1;
                    alchemy.SearchByIngredient(name1);
                    break;
                }
                case 4:
                {
                    cout << "=== 포션 지급/반환 ===" << endl;
                    cout << "HP포션 재고: " << alchemy.GetStock("HP포션") << endl;
                    cout << "MP포션 재고: " << alchemy.GetStock("MP포션") << endl;
                    cout << "1. 포션 지급" << endl;
                    cout << "2. 포션 반환" << endl;
                    cout << "0. 돌아가기" << endl;
                    int pChoise;
                    cout << "선택: ";
                    cin >> pChoise;
                    switch (pChoise) {
                    case 1: {
                        string pName;
                        cout << "어떤 포션을 지급받으시겠습니까? (HP포션/MP포션): ";
                        cin >> pName;
                        alchemy.DispensePotion(pName);
                        break;
                    }
                    case 2: {
                        string pName;
                        cout << "어떤 포션을 반환하시겠습니까? (HP포션/MP포션): ";
                        cin >> pName;
                        alchemy.ReturnPotion(pName);
                        break;
                    }
                    case 0:
                        break;
                    }
                    break;
                }
                case 0:
                    workshop = false;
                    break;

                }

            }
            break;
        }


        case 0:
            cout << "게임 종료" << endl;
            for (auto r : rooms) {
                delete r;
            }
            delete player;
            return 0;
        }

    }
    for (auto r : rooms) {
        delete r;
    }
    delete player;
    return 0;
}
