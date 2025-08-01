#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Player.h"
#include "Monster.h"
#include <string>

using namespace std;

class GameManager {
private:
	Player* player;
	Monster* monster;
	int monsterCount;
	int turn;

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