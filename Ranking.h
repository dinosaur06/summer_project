#ifndef RANKING_H
#define RANKING_H
#include <string>
using namespace std;   

class Ranking {
public:
	static void updateRanking(const string& playerName, int monsterCount, int turn);
	static void printRanking();
};

#endif