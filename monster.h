#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include "Character.h"
using namespace std;

class Monster : public Character {
public:
	Monster(const string& name, int hp, int baseDamage, int ultDamage, int ultCooldown);

	int performAction();
	void decreaseCooldown();

	void printStatus() const;

	int getUltimateCoddownCurrent() const;

protected:
	int baseAttackDamage;
	int ultimateAttackDamage;
	int ultimateCooldownCurrent;
	int ultimateCooldownMax;
};

#endif