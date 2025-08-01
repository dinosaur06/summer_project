#include <iostream>
#include <string>
#include "GameManager.h"
using namespace std;


int main()
{
	string name;
	cout << "플레이어 이름을 입력하세요: ";
	getline(cin, name);

	GameManager game(name);
	game.startGame();
	
	cout << "게임이 종료되었습니다." << endl;

	return 0;
}