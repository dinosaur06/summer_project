#include <iostream>
#include <cstdlib>
#include <windows.h>
#include "Player.h"
using namespace std;

Player::Player(const string& name, int hp)
    : Character(name, hp), ultimateCooldown(0), healCooldown(0) {}

void Player::basicAttack(Character& target) {
    int damage = 20 + getBuffAmount() + permanentBuffDamage;
    cout << name << "이/가 기본 공격을 사용했습니다!\n";
    if (getBuffAmount() > 0)
        cout << "[버프 적용] 공격력 +" << getBuffAmount() << "!\n";
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
    decreaseBuffTurn(); // 버프도 턴마다 줄어듬
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

void Player::increaseMaxHP(int amount) {
    maxHp += amount;
    hp += amount; // 최대 체력 증가 시 현재 체력도 증가 (넘지 않도록)
    if (hp > maxHp) hp = maxHp;
    cout << name << "의 최대 체력이 " << amount << " 증가했습니다! (현재: " << maxHp << ")\n";
}

void Player::healToFull() {
    hp = maxHp;
    cout << "체력이 전부 회복됨! (" << hp << "/" << maxHp << ")\n";
}

void Player::resetUltimateCooldown() {
    ultimateCooldown = 0;
}

void Player::heal(int amount) {
    Character::heal(amount);
}

void Player::applyBuff(int amount, int turns) {
    buffAmount = amount;
    buffTurn = turns;
    cout << name << "에게 공격력 +" << amount << " 버프가 " << turns << "턴 동안 적용됩니다!\n";
}

bool Player::hasBuff() const {
    return buffTurn > 0;
}

int Player::getBuffAmount() const {
    return hasBuff() ? buffAmount : 0;
}

void Player::decreaseBuffTurn() {
    if (buffTurn > 0) buffTurn--;
}

void Player::applyPermanentBuff(int amount) {
    permanentBuffDamage += amount;
    cout << "[버프] 영구적으로 일반 공격력이 " << amount << " 증가했습니다!" << endl << endl;
}