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
	bool monsterJustRespawned = false;

	vector<int> eventTurns; //랜덤이벤트 턴 지정
	void GenerateEarlyEventTurns();
	void TriggerRockPaperScissorsEvent();
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
	int getMonsterKillCount() const;
	int getTurnCount() const;
};

#endif 
