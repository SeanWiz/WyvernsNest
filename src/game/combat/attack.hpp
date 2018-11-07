#pragma once

#include <string>
#include <vector>

#include "../../engine/core.hpp"
#include "../../math/vec.hpp"

class Combat;
class Unit;

// Enumeration for all attack types
enum class AttackType {
	INVALID,	// THIS SHOULD NEVER BE A REAL ATTACK, ONLY USED IF SOMETHING FAILS
	SELF,
	MELEE,
	RANGED,
	PIERCE,
	SPIN,
	HEAL,
	BIG_AOE
};

// Use an integer to represent the range of the attack
using AttackRange = int;

// Use an integer to represent the AoE of the attack
using AttackAoE = int;

// TODO: Move attack effects to a different file location
// Base class to represent an attack effect
class AttackEffect {
public:
	virtual void attack(ScreenCoord pos, Combat& combat, int stat, double mult) = 0;
};

// Attack effect that damages units
class DamageEffect : public AttackEffect {
public:
	DamageEffect() : damage(1) {}
	DamageEffect(int damage) : damage(damage) {}
	void attack(ScreenCoord pos, Combat& combat, int stat, double mult);
	int damage;

private:
};

// TODO: Handle invalid attacks during gameplay
// TODO: Change affect self to be calculated in the effect, not in the attack
// TODO: Change attacks to be able to have multiple effects
// Generic attack class to hold all of the data for an attack
class Attack {

public:
	Attack();
	Attack(std::string name, 
		Unit * source, 
		AttackType type = AttackType::MELEE,
		AttackRange range = 0,
		AttackEffect * effect = new DamageEffect(), 
		AttackAoE aoe = 0,
		bool affect_self = false);
	// Constuctor that duplicates an attack but changes the source unit
	Attack(const Attack& other, Unit * source);

	/*
	void update();
	bool attackStart(ScreenCoord pos, Combat & combat);
	*/

	void attack(ScreenCoord pos, Combat& combat);
	void renderValidGrid();
	void renderValidTarget();
	bool isValid(ScreenCoord pos);

	// Getter functions for attack properties
	inline AttackType getType() const { return type; }
	inline const AttackEffect& getEffect() const { return *effect; }
	inline AttackAoE getAoE() const { return aoe; }
	inline std::string getName() const { return name; }

	// Other methods to make sure this class works properly
	void setTileSize(int width, int height);

	/*
	bool attackStarted;
	int attack_counter;
	ScreenCoord target;
	Combat * combat;
	*/

private:
	std::string name;
	Unit * source;

	AttackType type;
	AttackRange range;
	AttackEffect * effect;
	AttackAoE aoe;
	bool affect_self;

	Sprite validSprite;
	Sprite targetValidSprite;
	Sprite targetInvalidSprite;

	// Helper variables to make sure sprites render correctly
	int tile_width, tile_height;

	// Helper methods
	void attackAoE(ScreenCoord pos, Combat& combat);
};

/*
class Plus : public Attack {
public:
	Plus() : 
		Attack(AttackType::MELEE),
		sprite1("res/test6.png"),
		sprite2("res/test6.png"),
		sprite3("res/test6.png"),
		sprite4("res/test6.png"),
		sprite5("res/test6.png"),
		sprite1_wrong("res/test7.png"),
		sprite2_wrong("res/test7.png"),
		sprite3_wrong("res/test7.png"),
		sprite4_wrong("res/test7.png"),
		sprite5_wrong("res/test7.png")

	{
		sprite1.setSize(213, 180);
		sprite2.setSize(213, 180);
		sprite3.setSize(213, 180);
		sprite4.setSize(213, 180);
		sprite5.setSize(213, 180);
		sprite1_wrong.setSize(213, 180);
		sprite2_wrong.setSize(213, 180);
		sprite3_wrong.setSize(213, 180);
		sprite4_wrong.setSize(213, 180);
		sprite5_wrong.setSize(213, 180);

	}

	int damage = 1;
	Sprite sprite1;
	Sprite sprite2;
	Sprite sprite3;
	Sprite sprite4;
	Sprite sprite5;

	Sprite sprite1_wrong;
	Sprite sprite2_wrong;
	Sprite sprite3_wrong;
	Sprite sprite4_wrong;
	Sprite sprite5_wrong;


	std::vector<ScreenCoord> getAttackPos(ScreenCoord pos) {
		//TODO returns all the positions hit by the attack
		std::vector<ScreenCoord> hit;
		if (isValid(pos)) {
			hit.push_back(pos);
			hit.push_back(pos + ScreenCoord(1,0));
			hit.push_back(pos + ScreenCoord(0, 1));
			hit.push_back(pos + ScreenCoord(-1, 0));
			hit.push_back(pos + ScreenCoord(0, -1));
		}

		isRendered = false;

		return hit;
	}

	bool isValid(ScreenCoord pos) {
		//TODO
		int x_dist = abs(pos.x() - playerPos.x());
		int y_dist = abs(pos.y() - playerPos.y());

		if (y_dist + x_dist >= 2) {
			return true;
		}
		return false;
	}

	void showValidGrid() {
		return;
	}

	void render(ScreenCoord pos) {
		if (isRendered) {
			if (isValid(pos)) {
				sprite1.setPos(pos.x() * 213, pos.y() * 180);
				sprite1.render();
				sprite2.setPos(pos.x() * 213, (pos.y() - 1) * 180);
				sprite2.render();
				sprite3.setPos((pos.x() + 1) * 213, pos.y() * 180);
				sprite3.render();
				sprite4.setPos(pos.x() * 213, (pos.y() + 1) * 180);
				sprite4.render();
				sprite5.setPos((pos.x() - 1) * 213, pos.y() * 180);
				sprite5.render();
			}
			else {
				//TODO values here are temporary
				sprite1_wrong.setPos(pos.x() * 213, pos.y() * 180);
				sprite1_wrong.render();
				sprite2_wrong.setPos(pos.x() * 213, (pos.y() - 1) * 180);
				sprite2_wrong.render();
				sprite3_wrong.setPos((pos.x() + 1) * 213, pos.y() * 180);
				sprite3_wrong.render();
				sprite4_wrong.setPos(pos.x() * 213, (pos.y() + 1) * 180);
				sprite4_wrong.render();
				sprite5_wrong.setPos((pos.x() - 1) * 213, pos.y() * 180);
				sprite5_wrong.render();
			}

		}
	}
};
*/