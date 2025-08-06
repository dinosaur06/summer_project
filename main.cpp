#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include "GameManager.h"
#include "Ranking.h"
using namespace std;


int main()
{
	srand(static_cast<unsigned int>(time(nullptr))); // 랜덤 시드 초기화

    char playAgain; // 게임 재시작 여부를 저장할 변수

    do {
        Ranking::printRanking();

        string playerName;
        cout << endl << "======================================" << endl;
        cout << "      새로운 게임을 시작합니다!       " << endl;
        cout << "======================================" << endl;
        Sleep(200);
        cout << "플레이어 이름을 입력하세요: ";
        getline(cin, playerName);

        GameManager game(playerName);
        game.startGame(); 

        cout << endl << "======================================" << endl;
        cout << "        게임이 종료되었습니다!        " << endl;
        cout << "======================================" << endl << endl;

        Ranking::updateRanking(playerName, game.getMonsterKillCount(), game.getTurnCount());

        cout << endl << endl << "다시 플레이하시겠습니까? (Y/N): ";
        cin >> playAgain;

        cin.ignore(1000, '\n');

        if (toupper(playAgain) == 'Y') {
            cout << endl;
        }
    } while (toupper(playAgain) == 'Y');

    cout << "게임을 종료합니다. 플레이해주셔서 감사합니다!" << endl;

	return 0;
}