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
    cout << name << "이/가 기본 공격을 사용했습니다!\n";
    Sleep(200);
    target.takeDamage(damage);
}

void Player::skill2(Character& target) {
    cout << name << "이/가 치명타 스킬을 사용했습니다!\n";
    Sleep(200);
    int critChance = rand() % 100;
    int damage = (critChance < 30) ? 30 : 15;

    if (critChance < 30)
        cout << "치명타 성공!! ";
    else
        cout << "치명타 실패. ";

    target.takeDamage(damage);
}

bool Player::ultimateSkill(Character& target) {
    if (canUseUltimate()) {
        cout << name << "이/가 궁극기를 사용했습니다!\n";
        Sleep(200);
        target.takeDamage(50);
        ultimateCooldown = 5;
        return true;
    }
    else {
        cout << "궁극기는 아직 쿨타임입니다. (" << ultimateCooldown << "턴 남음)\n";
        return false;
    }
}

bool Player::heal() {
    if (canUseHeal()) {
        int healAmount = static_cast<int>((maxHp - hp) * 0.5);
        if (healAmount <= 0) {
            cout << name << "의 체력이 이미 가득 찼습니다!\n";
            return false;
        }
        Character::heal(healAmount);
        healCooldown = 3;
        return true;
    }
    else {
        cout << "힐은 아직 쿨타임입니다. (" << healCooldown << "턴 남음)\n";
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
    cout << name << " (플레이어) HP: " << hp << "/" << maxHp << "\n";
}
