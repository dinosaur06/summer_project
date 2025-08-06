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
        cerr << "��� ������ �� �� �����ϴ�." << endl;
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
        cerr << "��� ������ ���� �� �����ϴ�." << endl; 
        return;
    }

    sort(rankings.begin(), rankings.end(), [](const auto& a, const auto& b) {
        return get<1>(a) > get<1>(b); // �������� ���� (���� óġ ���� ū ����)
        });

    cout << endl << "[��� TOP 5]" << endl; 
    int rank = 1;
    for (const auto& entry : rankings) { 
        cout << rank++ << ". ";
        cout << get<0>(entry);
        cout << " - ���� ";
        cout << get<1>(entry);
        cout << "���� óġ";
        cout << " (";
        cout << get<2>(entry);
        cout << "��)" << endl;

        if (rank > 5) break; 
    }
    cout << endl;
}
