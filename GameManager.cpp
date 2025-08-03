#include "GameManager.h"
#include <windows.h>
#include <iostream>

using namespace std;

GameManager::GameManager(const string& playerName) {
	monsterCount = 1;
	turn = 1;
	player = new Player(playerName, 100);
	monster = new Monster("Monster1", 50, 10, 25, 3);
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
		cout << "3. 궁극기" << endl;
		cout << "4. 힐" << endl;
		cout << endl << ">>";
		cin >> skill;

		if (skill < 1 || skill > 4) {
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