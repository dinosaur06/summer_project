#include "GameManager.h"
#include <iostream>
#include <random>
#include <limits>
#include <windows.h>
#include <algorithm> // for find()
#include <cstdlib>   // for rand()
// #include <ctime>     // srand()가 main으로 이동했으므로 여기서는 불필요
using namespace std;

// 콘솔 텍스트 색상 변경 함수
void SetConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// 색상 상수 정의
const int BLACK = 0;
const int BLUE = FOREGROUND_BLUE;
const int GREEN = FOREGROUND_GREEN;
const int CYAN = FOREGROUND_BLUE | FOREGROUND_GREEN;
const int RED = FOREGROUND_RED;
const int MAGENTA = FOREGROUND_RED | FOREGROUND_BLUE;
const int YELLOW = FOREGROUND_RED | FOREGROUND_GREEN;
const int WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
const int INTENSE_BLACK = FOREGROUND_INTENSITY; // 회색
const int INTENSE_BLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const int INTENSE_GREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int INTENSE_CYAN = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int INTENSE_RED = FOREGROUND_RED | FOREGROUND_INTENSITY;
const int INTENSE_MAGENTA = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const int INTENSE_YELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY; // 밝은 노랑
const int INTENSE_WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY; // 밝은 하양 (기본)


GameManager::GameManager(const string& playerName) {
    // srand(time(0)); // 난수 초기화는 main 함수에서 한 번만 하도록 수정됨
    monsterCount = 1;
    turn = 1;
    player = new Player(playerName, 100);
    monster = new Monster("Monster1", 50, 10, 25, 3);

    GenerateEarlyEventTurns(); // 초반 고정 이벤트 턴 생성
}

GameManager::~GameManager() {
    delete player;
    delete monster;
}

void GameManager::StartGame() {
    cout << "게임 시작!\n";
    while (true) {
        cout << "\n===== [Turn " << turn << "] =====\n";
        PrintStatus();

        CheckEventTurn(); // 이벤트 체크

        PlayerTurn();
        if (IsGameover()) break; // 플레이어 턴 후 게임 종료 여부 확인

        MonsterTurn();
        if (IsGameover()) break; // 몬스터 턴 후 게임 종료 여부 확인

        turn++;
    }
}

void GameManager::PlayerTurn() {
    int skill;
    bool skillUsedSuccessfully = false;

    while (true) {
        cout << "플레이어의 턴입니다. 스킬을 선택하세요:\n";
        cout << "1. 기본 공격\n";
        cout << "2. 스킬 (치명타 공격)\n";
        cout << "3. 궁극기 (" << player->getUltimateCooldown() << "턴 남음)\n"; // 쿨타임 표시
        cout << "4. 힐 (" << player->getHealCooldown() << "턴 남음)\n";         // 쿨타임 표시
        cout << ">> ";
        cin >> skill;

        if (cin.fail() || skill < 1 || skill > 4) { // 유효하지 않은 입력 처리
            cout << "잘못된 선택입니다. 다시 시도하세요.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (skill) {
        case 1:
            player->basicAttack(*monster);
            skillUsedSuccessfully = true;
            break;
        case 2:
            player->skill2(*monster);
            skillUsedSuccessfully = true;
            break;
        case 3:
            skillUsedSuccessfully = player->ultimateSkill(*monster);
            break;
        case 4:
            skillUsedSuccessfully = player->heal(); // 인자 없는 heal 호출
            break;
        }

        if (skillUsedSuccessfully) {
            player->reduceCooldowns(); // 스킬 사용에 성공했을 경우에만 쿨타임 감소 및 턴 종료
            break; // 플레이어 턴 종료
        }
    }
}

void GameManager::MonsterTurn() {
    cout << "몬스터의 턴입니다.\n";
    int damage = monster->performAction();
    player->takeDamage(damage);
    monster->decreaseCooldown();
}

void GameManager::PrintStatus() {
    cout << "[현재 상태]\n";
    player->printStatus();
    monster->printStatus();
}

bool GameManager::IsGameover() {
    if (!player->isAlive()) {
        SetConsoleColor(INTENSE_RED); // 게임 종료 빨간색
        cout << "플레이어가 패배했습니다. 게임 종료.\n";
        SetConsoleColor(INTENSE_WHITE); // 기본색으로 돌아옴
        return true;
    }

    if (!monster->isAlive()) {
        cout << "몬스터를 처치했습니다!\n";
        delete monster; // 기존 몬스터 객체 삭제
        monsterCount++;
        // 새로운 몬스터 생성 (스탯 증가)
        monster = new Monster("Monster" + to_string(monsterCount), 50 + monsterCount * 10, 10 + monsterCount * 2, 25 + monsterCount * 2, 3);
        cout << monster->getName() << "이/가 새로 등장했습니다!\n";
    }

    return false; // 게임이 아직 끝나지 않았음
}

void GameManager::GenerateEarlyEventTurns() {
    int numEarlyEvents = 3;
    int earlyTurnLimit = 5; // 1턴부터 5턴까지 중 이벤트 발생

    eventTurns.clear();
    while (eventTurns.size() < numEarlyEvents) {
        int turn = rand() % earlyTurnLimit + 1; // 1~5 사이의 난수
        // 중복된 턴이 아니라면 추가
        if (find(eventTurns.begin(), eventTurns.end(), turn) == eventTurns.end()) {
            eventTurns.push_back(turn);
        }
    }
     cout << "랜덤 이벤트 턴: ";
    for (int t : eventTurns) cout << t << " ";
    cout << endl;
}

bool GameManager::ShouldTriggerRandomEvent() {
    if (turn <= 5) return false; // 초반 고정 이벤트 턴이 지나면 일반 랜덤 이벤트 활성화
    return (rand() % 100) < 20; // 20% 확률로 이벤트 발생
}

void GameManager::TriggerRandomEvent() {
    int effectType = rand() % 4; // 0, 1, 2, 3 중 하나

    switch (effectType) {
    case 0:
        SetConsoleColor(INTENSE_YELLOW);
        cout << "[이벤트] 최대 체력이 10 증가합니다!\n";
        SetConsoleColor(INTENSE_WHITE); // 기본색으로 돌아옴
        player->increaseMaxHP(10); // Player 클래스의 increaseMaxHP 호출
        break;
    case 1:
        SetConsoleColor(INTENSE_BLUE); // 궁극기 초기화 파랑색
        cout << "[이벤트] 궁극기 쿨타임이 초기화됩니다!\n";
        SetConsoleColor(INTENSE_WHITE); // 기본색으로 돌아옴
        player->resetUltimateCooldown(); // Player 클래스의 resetUltimateCooldown 호출
        break;
    case 2:
        SetConsoleColor(INTENSE_GREEN); // 체력 회복 초록색
        cout << "[이벤트] 체력을 20 회복합니다!\n";
        SetConsoleColor(INTENSE_WHITE); // 기본색으로 돌아옴
        player->heal(20); // Character 클래스의 heal 함수 호출
        break;
    case 3:
        SetConsoleColor(INTENSE_GREEN); // 체력 회복 초록색
        cout << "[이벤트] 모험을 하던중 열매를 먹었더니 체력이 완전히 회복되었습니다!!\n";
        SetConsoleColor(INTENSE_WHITE); // 기본색으로 돌아옴
        player->healToFull();
        break;
    }
}

void GameManager::CheckEventTurn() {
    // 초반 고정 이벤트 턴인지 확인
    if (find(eventTurns.begin(), eventTurns.end(), turn) != eventTurns.end()) {
        TriggerRandomEvent(); // 고정 이벤트 발생
    }
    // 고정 이벤트 턴이 아니면서, 확률적으로 랜덤 이벤트 발생 조건 충족 시
    else if (ShouldTriggerRandomEvent()) {
        TriggerRandomEvent(); // 확률 이벤트 발생
    }
}