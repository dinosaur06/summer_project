#include "Character.h"
#include <iostream>
#include <windows.h>
using namespace std;

Character::Character(const string& name, int hp)
	: name(name), hp(hp), maxHp(hp) {
}

void Character::takeDamage(int damage) {
	hp -= damage;
	if (hp < 0) hp = 0;
	cout << name << "��/�� " << damage << "�� ���ظ� �Ծ����ϴ�! (���� ü��: " << hp << "/" << maxHp << ")" << endl << endl;
	Sleep(500);
}

void Character::heal(int amount) {
	hp += amount;
	if (hp > maxHp) hp = maxHp;
	cout << name << "��/�� " << amount << "��ŭ ü���� ȸ���߽��ϴ�! (���� ü��: " << hp << "/" << maxHp << ")" << endl << endl;
	Sleep(300);
}

bool Character::isAlive() const {
	return hp > 0;
}

string Character::getName() const {
	return name;
}

int Character::getHp() const {
	return hp;
}

int Character::getMaxHp() const {
	return maxHp;
}