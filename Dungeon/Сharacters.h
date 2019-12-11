/*!
\file
\brief Header file with characters discription

This file has a discription of all character classes
*/

#ifndef _CHARACTERS_H_
#define _CHARACTERS_H_
#include "Items.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime> 
#include "map_template.h"

using std::string;
using std::vector;
using namespace ITEMS;

namespace CHARACTERS {

	/*! \brief Describes all additional effect to the hero
	
	Effect is caused by drunk potion
	*/
	class Effect {
	private:
		HeroParams boost; ///< What potion modofies
		int duration; ///< Duration of an effect
	public:
		Effect(HeroParams p, int dur) :duration(dur), boost(p) {};
		Effect();
		void save();
		void load();
		int timer();
		void wipe();
		void add_effect(HeroParams p, int dur);
		HeroParams getBoost();
	};

	/*!\brief This structure describes every param about the enemy*/

	struct EnemyParams {
		EnemyType type;///< Type of an enemy
		double attack;///< Attack of an enemy
		double defence;///< Defence of an enemy
		double CurHealth;///< Current health
		double MaxHealth;///< Maximum health
		double exp; ///<Experience of an enemy
		Item *i; ///< Item which enemy holds
		EnemyParams(EnemyType type_, double attack_, double defence_, double mh) : type(type_), attack(attack_), defence(defence_), CurHealth(mh), MaxHealth(mh) {};
		friend std::ostream & operator <<(std::ostream&, const EnemyParams&);
	};
	/*!\brief Hero parametrs index to tell what parameter to change*/
	enum HeroParamIndex{
		AGILITY,///< Agility
		STAMINA,///< Stamina
		STRENGTH,///< Strength
		MAXHEALTHHERO, ///< Max health
		CURHEALTHHERO ///< Current health
	};



	/*!\brief This class describes everything about Hero
	
	It has all parameters, all wearing equipment, weapon, potions, effect from the potion, number of picklocks and of course position
	*/
	class Hero{
	private:
		int level; ///< Level of the hero
		double experience; ///< Experience
		string name; ///< Heroname
		HeroParams Params; ///Parameters of hero
		Weapon *weapon; ///< Weapon
		map<EquipType,Equipment*> equip; ///< All equipment
		unsigned int MaxPotionNumber; ///< Max number of potions that hero can held
		vector<Potion *> potions;///< Potions
		int picklocks; ///< Number fo picklocks
		Effect effects; ///< Effects from the potion
		Map<HeroParamIndex, double> heroTable; ///< Herotable, where you can see all information of the hero
		Chords pos;///< Hero position
	public:
		Hero( int x=-1, int y=-1); //Добавить HEROTABLE
		double getAttackProb();
		void getExp(double);
		double getAttackBonus();
		double getDefenceBonus();
		double generateDamage();
		double getHackProb();
		void LevelUp();
		void setName(string &);
		map<EquipType, Equipment *> & getEquipMap();
		HeroParams getParams();
		void changeParams(HeroParamIndex index, double value);
		Item * takeItem(Item * i);
		void setItem(Item *i);
		void drinkPotion(); 
		void setPos(int, int);
		/*! \brief Returns current position of a hero*/
		Chords getPos() { return pos; }; 
		void takeDamage( double);
		void save();
		void load();
		void move(int);
		/*! \brief Returns weapon of a hero to change it*/
		Weapon * getWeapon() { return weapon; }; 
		~Hero();
	};

	/*! \brief All eemy params to change*/
	enum ENEMYPARAMETRS {
		CURHEALTH,///< Current health
		MAXHEALTH,///< Max health
		ATTACK,///< Attack of a hero
		DEFENCE, ///< Defence
		ENEMYPARAMETRSCOUNT ///< Count
	};

	/*! \brief Class the describes enemies*/

	class Enemy {
	private:
		string name; ///< Name of an enemy
		double experience; ///< Experience that hero gain after killing enemy
		Item *item; ///< Item that enemy holds
		EnemyParams params; ///< EnemyParam
		Chords pos; ///< Current position of an enemy
	public:
		Enemy(string name, EnemyType type, int x, int y,Item *item=nullptr, double mh=200, double experience=145);
		void changeParams(ENEMYPARAMETRS index=ENEMYPARAMETRS::ENEMYPARAMETRSCOUNT, double p=0, EnemyType t = ENEMYCOUNT);
		EnemyParams getParams();
		double dealDamage();
		void getDamage(double);
		Item *dropItem();
		void putItem(Item *i);
		Item * getItem();
		void save(std::fstream &);
		void load(std::fstream &s);
		~Enemy() { if (item != nullptr) delete item; };
	};
}

#endif