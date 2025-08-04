#include "Monster.h"
#include <iostream>
#include <windows.h>
using namespace std;

Monster::Monster(const string& name, int hp, int baseDamage, int ultDamage, int ultCooldown)
	: Character(name,hp),
	baseAttackDamage(baseDamage),
	ultimateAttackDamage(ultDamage),
	ultimateCooldownMax(ultCooldown),
	ultimateCooldownCurrent(0) {}

int Monster::performAction() {
	if (ultimateCooldownCurrent == 0) {
		cout << name << "이/가 궁극기를 사용합니다!" << endl;
		Sleep(200);
		ultimateCooldownCurrent = ultimateCooldownMax;
		return ultimateAttackDamage;
	} 
	else {
		cout << name << "이/가 일반 공격을 합니다!" << endl;
		Sleep(200);
		return baseAttackDamage;
	}
}

void Monster::decreaseCooldown() {
	if (ultimateCooldownCurrent > 0) {
		ultimateCooldownCurrent--;
	}
}

int Monster::getUltimateCoddownCurrent() const {
	return ultimateCooldownCurrent;
}

void Monster::printStatus() const {
	cout << getName() << " HP: " << hp << "/" << maxHp << " ";

	if (ultimateCooldownCurrent == 0) {
		cout << "[몬스터 궁극기 사용 가능!]" << endl << endl;
	}
	else {
		cout << "[몬스터 궁극기 쿨타임: " << ultimateCooldownCurrent << "턴]" << endl << endl;
	}
}