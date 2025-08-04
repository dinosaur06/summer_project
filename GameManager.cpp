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
	cout << endl << "���� ����!" << endl << endl;
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
		cout << "�÷��̾��� ���Դϴ�. ��ų�� �����ϼ���." << endl << endl;
		cout << "1. �Ϲ� ����" << endl;
		cout << "2. ��ų (ġ��Ÿ ����)" << endl;
		cout << "3. �ñر� (" << player->getUltimateCooldown() << "�� ����)" << endl;
		cout << "4. �� (" << player->getHealCooldown() << "�� ����)" << endl;
		cout << endl << ">>";
		cin >> skill;

		if (cin.fail() || skill < 1 || skill > 4) {
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

	void GameManager::GenerateEarlyEventTurns() {
		int numEarlyEvents = 3;
		int earlyTurnLimit = 5;

		eventTurns.clear();
		while (eventTurns.size() < numEarlyEvents) { //�����̺�Ʈ
			int turn = rand() % earlyTurnLimit + 1;
			if (find(eventTurns.begin(), eventTurns.end(), turn) == eventTurns.end()) {
				eventTurns.push_back(turn);
			}
		}

		cout << "���� �̺�Ʈ ��: ";
		for (int t : eventTurns) cout << t << " " << endl;
	}

	bool GameManager::ShouldTriggerRandomEvent() {
		if (turn <= 5) return false; // �ʹ� ���� �̺�Ʈ ���� ������ �Ϲ� ���� �̺�Ʈ Ȱ��ȭ
		return (rand() % 100) < 20; // 20% Ȯ���� �̺�Ʈ �߻�
	}

	void GameManager::TriggerRandomEvent() {
		int effectType = rand() % 4; // 0, 1, 2, 3 �� �ϳ�

		switch (effectType) {
		case 0:
			cout << "[�̺�Ʈ] �ִ� ü���� 10 �����մϴ�!\n";
			player->increaseMaxHP(10); // Player Ŭ������ increaseMaxHP ȣ��
			break;
		case 1:
			cout << "[�̺�Ʈ] �ñر� ��Ÿ���� �ʱ�ȭ�˴ϴ�!\n";
			player->resetUltimateCooldown(); // Player Ŭ������ resetUltimateCooldown ȣ��
			break;
		case 2:
			cout << "[�̺�Ʈ] ü���� 20 ȸ���մϴ�!\n";
			player->heal(20); // Character Ŭ������ heal �Լ� ȣ��
			break;
		case 3:
			cout << "[�̺�Ʈ] ������ �ϴ��� ���Ÿ� �Ծ����� ü���� ������ ȸ���Ǿ����ϴ�!!\n";
			player->healToFull();
			break;
		}
	}

	void GameManager::CheckEventTurn() {
		// �ʹ� ���� �̺�Ʈ ������ Ȯ��
		if (find(eventTurns.begin(), eventTurns.end(), turn) != eventTurns.end()) {
			TriggerRandomEvent(); // ���� �̺�Ʈ �߻�
		}
		// ���� �̺�Ʈ ���� �ƴϸ鼭, Ȯ�������� ���� �̺�Ʈ �߻� ���� ���� ��
		else if (ShouldTriggerRandomEvent()) {
			TriggerRandomEvent(); // Ȯ�� �̺�Ʈ �߻�
		}
		}