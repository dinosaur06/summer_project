#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include "Player.h"
using namespace std;

Player::Player(const string& name, int hp)
    : Character(name, hp), ultimateCooldown(0), healCooldown(0) {
    srand(static_cast<unsigned int>(time(nullptr)));
}

void Player::basicAttack(Character& target) {
    int damage = 10;
    cout << name << "��/�� �⺻ ������ ����߽��ϴ�!\n";
    Sleep(200);
    target.takeDamage(damage);
}

void Player::skill2(Character& target) {
    cout << name << "��/�� ġ��Ÿ ��ų�� ����߽��ϴ�!\n";
    Sleep(200);
    int critChance = rand() % 100;
    int damage = (critChance < 30) ? 30 : 15;

    if (critChance < 30)
        cout << "ġ��Ÿ ����!! ";
    else
        cout << "ġ��Ÿ ����. ";

    target.takeDamage(damage);
}

bool Player::ultimateSkill(Character& target) {
    if (canUseUltimate()) {
        cout << name << "��/�� �ñر⸦ ����߽��ϴ�!\n";
        Sleep(200);
        target.takeDamage(50);
        ultimateCooldown = 5;
        return true;
    }
    else {
        cout << "�ñر�� ���� ��Ÿ���Դϴ�. (" << ultimateCooldown << "�� ����)\n";
        return false;
    }
}

bool Player::heal() {
    if (canUseHeal()) {
        int healAmount = static_cast<int>((maxHp - hp) * 0.5);
        if (healAmount <= 0) {
            cout << name << "�� ü���� �̹� ���� á���ϴ�!\n";
            return false;
        }
        Character::heal(healAmount);
        healCooldown = 3;
        return true;
    }
    else {
        cout << "���� ���� ��Ÿ���Դϴ�. (" << healCooldown << "�� ����)\n";
        return false;
    }
}

int Player::getUltimateCooldown() const {
    return ultimateCooldown;
}

int Player::getHealCooldown() const {
    return healCooldown;
}


void Player::reduceCooldowns() {
    if (ultimateCooldown > 0) ultimateCooldown--;
    if (healCooldown > 0) healCooldown--;
}

bool Player::canUseUltimate() const {
    return ultimateCooldown == 0;
}

bool Player::canUseHeal() const {
    return healCooldown == 0;
}

void Player::printStatus() const {
    cout << name << " (�÷��̾�) HP: " << hp << "/" << maxHp << "\n";
}
