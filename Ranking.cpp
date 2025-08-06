#include "Ranking.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

void Ranking::updateRanking(const string& playerName, int monsterCount, int turn) {
    ofstream outFile("ranking.txt", ios::app);
    if (outFile.is_open()) {
        outFile << playerName << " " << monsterCount << " " << turn << endl;
        outFile.close();
    }
    else {
        cerr << "랭킹 파일을 열 수 없습니다." << endl;
    }
}

void Ranking::printRanking() {
    ifstream inFile("ranking.txt");
    vector<tuple<string, int, int>> rankings;

    if (inFile.is_open()) {
        string name;
        int kills, turns;
        while (inFile >> name >> kills >> turns) {
            rankings.emplace_back(name, kills, turns);
        }
        inFile.close();
    }
    else {
        cerr << "랭킹 파일을 읽을 수 없습니다." << endl; 
        return;
    }

    sort(rankings.begin(), rankings.end(), [](const auto& a, const auto& b) {
        return get<1>(a) > get<1>(b); // 내림차순 정렬 (몬스터 처치 수가 큰 순서)
        });

    cout << endl << "[랭킹 TOP 5]" << endl; 
    int rank = 1;
    for (const auto& entry : rankings) { 
        cout << rank++ << ". ";
        cout << get<0>(entry);
        cout << " - 몬스터 ";
        cout << get<1>(entry);
        cout << "마리 처치";
        cout << " (";
        cout << get<2>(entry);
        cout << "턴)" << endl;

        if (rank > 5) break; 
    }
    cout << endl;
}
