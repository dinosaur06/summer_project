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
	cout << endl << "���� ����!" << endl << endl;
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
		cout << "�÷��̾��� ���Դϴ�. ��ų�� �����ϼ���." << endl << endl;
		cout << "1. �Ϲ� ����" << endl;
		cout << "2. ��ų (ġ��Ÿ ����)" << endl;
		cout << "3. �ñر�" << endl;
		cout << "4. ��" << endl;
		cout << endl << ">>";
		cin >> skill;

		if (skill < 1 || skill > 4) {
			cout << "�߸��� �����Դϴ�. �ٽ� �õ��ϼ���." << endl << endl;
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
		cout << "������ ���Դϴ�." << endl << endl;
		Sleep(300);
		int damage = monster->performAction();
		player->takeDamage(damage);
		monster->decreaseCooldown();
	}

	void GameManager::PrintStatus() {
		cout << "[���� ����]" << endl;
		player->printStatus();
		monster->printStatus();
	}

	bool GameManager::IsGameover() {
		if (player->isAlive() <= 0) {
			cout << "�÷��̾ �й��߽��ϴ�." << endl;
			return true;
		}
		if (monster->isAlive() <= 0) {
			cout << "���͸� óġ�߽��ϴ�!." << endl;
			delete monster;
			monsterCount ++;
			monster = new Monster("Monster" + to_string(monsterCount), 50 + monsterCount * 10, 10 + monsterCount * 2, 25 + monsterCount * 2, 3);
			cout << "." << endl;
			Sleep(200);
			cout << "." << endl;
			Sleep(200);
			cout << "." << endl;
			Sleep(200);
			cout << "����� " << monster->getName() << "��/�� �����߽��ϴ�." << endl << endl;
		}
		return false;
	}