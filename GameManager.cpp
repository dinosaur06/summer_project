#include "GameManager.h"
#include <windows.h>
#include <algorithm>
#include <cstdlib>
#include <iostream>

using namespace std;

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

		MonsterTurn();
		if (IsGameover()) break;

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
		if (player->isAlive() <= 0) {
			cout << "플레이어가 패배했습니다." << endl;
			return true;
		}
		if (monster->isAlive() <= 0) {
			cout << "몬스터를 처치했습니다!." << endl;
			delete monster;
			monsterCount ++;
			monster = new Monster("Monster" + to_string(monsterCount), 50 + monsterCount * 10, 10 + monsterCount * 2, 25 + monsterCount * 2, 3);
			cout << "." << endl;
			Sleep(200);
			cout << "." << endl;
			Sleep(200);
			cout << "." << endl;
			Sleep(200);
			cout << "당신은 " << monster->getName() << "을/를 조우했습니다." << endl << endl;
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

		cout << "랜덤 이벤트 턴: ";
		for (int t : eventTurns) cout << t << " " << endl;
	}

	bool GameManager::ShouldTriggerRandomEvent() {
		if (turn <= 5) return false; // 초반 고정 이벤트 턴이 지나면 일반 랜덤 이벤트 활성화
		return (rand() % 100) < 20; // 20% 확률로 이벤트 발생
	}

	void GameManager::TriggerRandomEvent() {
		int effectType = rand() % 4; // 0, 1, 2, 3 중 하나

		switch (effectType) {
		case 0:
			cout << "[이벤트] 최대 체력이 10 증가합니다!\n";
			player->increaseMaxHP(10); // Player 클래스의 increaseMaxHP 호출
			break;
		case 1:
			cout << "[이벤트] 궁극기 쿨타임이 초기화됩니다!\n";
			player->resetUltimateCooldown(); // Player 클래스의 resetUltimateCooldown 호출
			break;
		case 2:
			cout << "[이벤트] 체력을 20 회복합니다!\n";
			player->heal(20); // Character 클래스의 heal 함수 호출
			break;
		case 3:
			cout << "[이벤트] 모험을 하던중 열매를 먹었더니 체력이 완전히 회복되었습니다!!\n";
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