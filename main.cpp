#include <iostream>
#include <string>
#include "GameManager.h"
#include <Windows.h>
using namespace std;


int main()
{
	string name;
	cout << "플레이어 이름을 입력하세요: ";
	getline(cin, name);

	GameManager game(name);
	game.startGame();
	cout << "." << endl;
	Sleep(200);
	cout << "." << endl;
	Sleep(200);
	cout << "." << endl;
	Sleep(200);
	cout << "게임이 종료됩니다." << endl;

	return 0;
}