#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "GameManager.h"
#include <Windows.h>
using namespace std;


int main()
{
	srand(static_cast<unsigned int>(time(nullptr))); // 랜덤 시드 초기화
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