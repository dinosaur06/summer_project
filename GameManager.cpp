#include "GameManager.h"
#include <windows.h>
#include <algorithm>
#include <cstdlib>
#include <iostream>

using namespace std;

// 콘솔 텍스트 색상 변경 함수
void SetConsoleColor(int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

// 색상 상수 정의
const int INTENSE_BLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const int INTENSE_GREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int INTENSE_RED = FOREGROUND_RED | FOREGROUND_INTENSITY;
const int INTENSE_YELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY; // 밝은 노랑
const int INTENSE_WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY; // 밝은 하양 (기본)



GameManager::GameManager(const string& playerName) {
	monsterCount = 1;
	turn = 1;
	player = new Player(playerName, 100);
	monster = new Monster("Monster1", 50, 10, 25, 3);

	GenerateEarlyEventTurns();
}

GameManager::~GameManager() {
	delete player;
	delete monster;
}

void GameManager::startGame() {
	cout << endl << "게임 시작!" << endl << endl;
	Sleep(300);
	while (true) {
		cout << "===== [ Turn " << turn << " ] =====" << endl << endl;
		PrintStatus();

		CheckEventTurn();

		PlayerTurn();
		if (IsGameover()) break;

		if (monsterJustRespawned) {
			monsterJustRespawned = false;
		}
		else {
			MonsterTurn();
			if (IsGameover()) break;


		}

		turn++;
	}
}

void GameManager::PlayerTurn() {
	int skill;
	bool skillUsedSuccessfully = false;

	while (true) {
		cout << "플레이어의 턴입니다. 스킬을 선택하세요." << endl << endl;
		cout << "1. 일반 공격" << endl;
		cout << "2. 스킬 (치명타 공격)" << endl;
		cout << "3. 궁극기 (" << player->getUltimateCooldown() << "턴 남음)" << endl;
		cout << "4. 힐 (" << player->getHealCooldown() << "턴 남음)" << endl;
		cout << endl << ">>";
		cin >> skill;

		if (cin.fail() || skill < 1 || skill > 4) {
			cout << "잘못된 선택입니다. 다시 시도하세요." << endl << endl;
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
			skillUsedSuccessfully = player->heal();
			break;
		}

		if (skillUsedSuccessfully) {
			player->reduceCooldowns();
			break;
		}
	}
}
void GameManager::MonsterTurn() {

	Sleep(300);
	cout << "몬스터의 턴입니다." << endl << endl;
	Sleep(300);
	int damage = monster->performAction();
	player->takeDamage(damage);
	monster->decreaseCooldown();
}

void GameManager::PrintStatus() {
	cout << "[현재 상태]" << endl;
	player->printStatus();
	monster->printStatus();
}

bool GameManager::IsGameover() {
	if (player->isAlive() == false) {
		SetConsoleColor(INTENSE_RED); // 게임 종료 빨간색
		cout << "플레이어가 패배했습니다." << endl;
		SetConsoleColor(INTENSE_WHITE); // 기본색으로 돌아옴
		return true;
	}
	if (monster->isAlive() == false) {
		cout << "몬스터를 처치했습니다!" << endl;
		delete monster;
		monsterCount++;
		monster = new Monster("Monster" + to_string(monsterCount), 50 + monsterCount * 10, 10 + monsterCount * 2, 25 + monsterCount * 2, 3);
		cout << "." << endl;
		Sleep(200);
		cout << "." << endl;
		Sleep(200);
		cout << "." << endl;
		Sleep(200);
		cout << "당신은 " << monster->getName() << "을/를 조우했습니다." << endl << endl;
		monsterJustRespawned = true;

	}
	return false;
}

void GameManager::GenerateEarlyEventTurns() {
	int numEarlyEvents = 3;
	int earlyTurnLimit = 5;

	eventTurns.clear();
	while (eventTurns.size() < numEarlyEvents) { //랜덤이벤트
		int turn = rand() % earlyTurnLimit + 1;
		if (find(eventTurns.begin(), eventTurns.end(), turn) == eventTurns.end()) {
			eventTurns.push_back(turn);
		}
	}

	cout << "확정 랜덤 이벤트 턴: ";
	for (int t : eventTurns) cout << t << " "; //나중에 없애기
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
		cout << "[이벤트] 최대 체력이 10 증가합니다!" << endl << endl;
		SetConsoleColor(INTENSE_WHITE); // 기본색으로 돌아옴
		player->increaseMaxHP(10);
		Sleep(300);
		break;
	case 1:
		SetConsoleColor(INTENSE_BLUE); // 궁극기 초기화 파랑색
		cout << "[이벤트] 궁극기 쿨타임이 초기화됩니다!" << endl << endl;
		SetConsoleColor(INTENSE_WHITE); // 기본색으로 돌아옴
		player->resetUltimateCooldown();
		Sleep(300);
		break;
	case 2:
		SetConsoleColor(INTENSE_GREEN); // 체력 회복 초록색
		cout << "[이벤트] 체력을 20 회복합니다!" << endl << endl;
		SetConsoleColor(INTENSE_WHITE); // 기본색으로 돌아옴
		player->heal(20);
		Sleep(300);
		break;
	case 3:
		SetConsoleColor(INTENSE_GREEN); // 체력 회복 초록색
		cout << "[이벤트] 모험을 하던 중 열매를 먹었더니 체력이 완전히 회복되었습니다!" << endl << endl;
		SetConsoleColor(INTENSE_WHITE); // 기본색으로 돌아옴
		player->healToFull();
		Sleep(300);
		break;

	case 4:
		SetConsoleColor(INTENSE_GREEN); // 체력 회복 초록색
		cout << "[이벤트] 동굴에서 쉬던 중 분수를 보았다. 체력이 30 회복되었습니다! " << endl << endl;
		SetConsoleColor(INTENSE_WHITE); // 기본색으로 돌아옴
		player->heal(30);
		Sleep(300);
		break;

	case 5:
		SetConsoleColor(INTENSE_RED); // 데미지 증가 빨간색
		cout << "[이벤트] 땅에 박힌 검에 걸려 넘어졌더니 검의 힘이 흡수되었습니다. 한 턴 동안 일반 공격이 99999만큼 증가합니다!" << endl << endl;
		SetConsoleColor(INTENSE_WHITE); // 기본색으로 돌아옴

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
int GameManager::getMonsterKillCount() const {
	return monsterCount;
}

int GameManager::getTurnCount() const {
	return turn;
}