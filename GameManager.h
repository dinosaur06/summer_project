#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Player.h"
#include "Monster.h"
#include <vector>
#include <string>

using namespace std;

class GameManager {
private:
	Player* player;
	Monster* monster;
	int monsterCount;
	int turn;

	vector<int> eventTurns; // 랜덤 이벤트 턴 저장

	void GenerateEarlyEventTurns();
	void CheckEventTurn();
	bool ShouldTriggerRandomEvent();
	void TriggerRandomEvent();

public:
	GameManager(const string& playername);
	~GameManager();

	void startGame();
	void PlayerTurn();
	void MonsterTurn();
	void PrintStatus();
	bool IsGameover();
};

#endif 