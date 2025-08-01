#include "Monster.h"
#include <iostream>
using namespace std;

Monster::Monster(const string& name, int hp, int baseDamage, int ultDamage, int ultCooldown)
	: Character(name,hp),
	baseAttackDamage(baseDamage),
	ultimateAttackDamage(ultDamage),
	ultimateCooldownMax(ultCooldown),
	ultimateCooldownCurrent(0) {}

int Monster::performAction() {
	if (ultimateCooldownCurrent == 0) {
		cout << name << "��/�� �ñر⸦ ����մϴ�! (" << ultimateAttackDamage << "����)" << endl;
		ultimateCooldownCurrent = ultimateCooldownMax;
		return ultimateAttackDamage;
	} 
	else {
		cout << name << "��/�� �Ϲ� ������ �մϴ�! (" << baseAttackDamage << "����)" << endl;
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
	cout << getName() << " HP: " << hp << "/" << maxHp << endl;

	if (ultimateCooldownCurrent == 0) {
		cout << "[�ñر� ��� ����!]" << endl;
	}
	else {
		cout << "[�ñر� ��Ÿ��: " << ultimateCooldownCurrent << "��]" << endl;
	}
}