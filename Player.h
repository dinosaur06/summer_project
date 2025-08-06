#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <string>
using namespace std;

class Player : public Character {
private:
    int ultimateCooldown;
    int healCooldown;
    int buffTurn = 0;
    int buffAmount = 0;
    int permanentBuffDamage = 0;

public:
    Player(const string& name, int hp);

    void basicAttack(Character& target);
    void skill2(Character& target);         // 치명타 공격

    bool ultimateSkill(Character& target);  // 궁극기
    bool heal();    // 회복
    void heal(int amount);

    void reduceCooldowns();  // 턴마다 쿨타임 감소
     

    bool canUseUltimate() const;
    bool canUseHeal() const;

    // 추가: 현재 쿨타임 값을 가져오는 함수
    int getUltimateCooldown() const;
    int getHealCooldown() const;

    void printStatus() const override;

    void increaseMaxHP(int amount);
    void healToFull();
    void resetUltimateCooldown();

    void applyBuff(int amount, int turns);
    bool hasBuff() const;
    int getBuffAmount() const;
    void decreaseBuffTurn();

    void applyPermanentBuff(int amount);

};

#endif