/*!
\file
\brief Header file with items discription

This file has a discription of all main item-classes
*/
#ifndef _ITEMS_H_
#define _ITEMS_H_
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>

using std::string;
using std::vector;
using std::map;
namespace ITEMS 
{
/*!\mainpage Dungeon Hobo
*
* This is a game "Dungeon".  You are playing as a hobo. And your main goal is to reach the latest floor. And not to die of course...

* The hero is moving on the dungeoun and killing enemies, also use items, that lays in the chests, in the dungeon and after killing enemies.

* Hero can't wear more that one weapon, and one type of each equipment.

* Also hero has an experince and you can upgrade your characteristics. 
*
*-\subpage componentsPage "Is there any enemies?"
*
*-\subpage modulePage "Can I save my progress?"
*
* 
 \page componentsPage Is there any enemies?
*
* Yes! Of course.
*
*
 \page modulePage Can I save my progress?
*
* Coming soon.Now you can save, but can't load the information
*
*/

	/// All types of Item
	enum ItemType {
		ITEM, ///< Item
		WEAPON, ///< Weapon
		EQUIPMENT, ///< Equipment
		POTION,///< Potion
		PICKLOCK,///< Picklocks
		ENCHANTEDWEAPON, ///< Enchanted weapon
		ARTEFACTWEAPON, ///< ArtefactWeapon
		ARTEFACTEQUIPMENT, ///<ArtefactEquipment
		ARTEFACTENCHANTWEAPON ///< Artifact enchanted weapon
	};

	///All types of Enemies
	enum EnemyType {
		HUMANOID,///< Humanlike enemy
		INSECT, ///< From mosquitos to bugs
		ANIMAL,///< Different predatory animals
		DEMON, ///< Something magical..
		ICY, ///< Consist of water
		UNDEAD, ///< Something not alive
		ENEMYCOUNT ///< Just to count all types
	};

	/*!
	\brief Structure that keeps all hero parameters

	It consits of strength, agillity, stamina, maximum health, current health
*/
	struct HeroParams {
		int strength=0///< Keeps strength of hero
			, agility=0///< Keeps agillity of hero
			, stamina=0;///< Keeps stamina of hero
		double MaxHealth///< Keeps as much as possible health of hero
			, CurHealth; ///< Keeps current health of hero
		HeroParams(int sta = 0, int str = 0, int ag = 0, double mh = 0) : stamina(sta), strength(str), agility(ag), MaxHealth(mh) {};
		friend std::ostream & operator <<(std::ostream&, const HeroParams&);
	};

	///All types of equipment
	enum EquipType {
		HELMET, ///< Helmet
		CHESTPLATE, ///< Chestplate
		PANTS, ///< Pants
		SHOES,///<Shoes
		AMULET,///<Amulet
		EQUIPCOUNT ///< Just to count all equipment
	};

	/*!
	\brief Parent class

	He contains name of every item
	*/

	class Item {
	protected:
		string name;///< Keeps item's name
	public:
		virtual ItemType iAm(); 
		Item(string s = nullptr) : name(s) {};
		string getName();
		void setName(string &s);
		virtual void save(std::fstream&);
		virtual void load(std::fstream&);
		virtual ~Item() {};
	};

	/*! \brief This structure contains of weapon parameters

	It consists of multiplier(for enchnted weapons), damage, hero parametrs(for artifact weapons)
	*/
	struct WeaponParams {
		map<EnemyType, double>  multiplier; ///< For enchanted weapons
		double damage; ///< Damage of a weapon
		bool isArtifact; ///< Is it an Artifact?)
		HeroParams params; ///< For artifact weapons
		friend std::ostream & operator <<(std::ostream&, const WeaponParams&);
	};

	class Enchantments;

	/*! \brief This class describes weapon

	This is need too deal more damage your enemies
	It has damage and enchantments(if a weapon is enchanted)
	*/
	class Weapon : virtual public Item {
	private:
		double damage; ///< Damage
		Enchantments *enchantments; ///< Enchantments
	protected:
		double getDamage();
		void setDamage(double d);
	public:
		Enchantments * getEnchants();
		virtual void save(std::fstream &);
		virtual void load(std::fstream&);
		bool isEnchanted();
		ItemType iAm();
		virtual int getStamina();
		virtual int getAgility();
		virtual int getStrength();
		Weapon(std::string name, double damage_) :Item(name), damage(damage_), enchantments(nullptr) {};
		Weapon() :Item("Standart_sword"), damage(125), enchantments(nullptr) {};
		Weapon(string name1, double damage1, map<EnemyType, double> map, double Enchanted=0);
		virtual double generateDamage();
		virtual WeaponParams getFeatures();
		void setMultiplier(EnemyType type = EnemyType::ENEMYCOUNT, double multiplier = 1.0);
		void changeFeatures(double damage_, EnemyType type=EnemyType::ENEMYCOUNT, double multiplier = 1.0);
		~Weapon();
	};

	/*!\brief Class that keeps all enchantments for weapon
	
	It keeps in map with EnemyType - double
	*/
	class Enchantments{
	private:
		map < EnemyType, double> multiplier;///< Multiplier
	public:
		Enchantments(double h = 1.0, double in = 1.0, double an = 1.0, double de = 1.0, double icy = 1.0, double un = 1.0);
		void save(std::fstream &);
		double getMultiplier(EnemyType type);
		map<EnemyType, double> getFeatures();
		void setFeatures(map<EnemyType, double>);
		void changeFeatures (EnemyType type, double multiplier_);
	};

	///All types of artefact params
	enum ArtefactParams {
		STAMINA, ///< Stamina
		STRENGTH, ///< Strength
		MAXHEALTH, ///< Max Health
		AGILITY, ///< Agility
		ARTEFACTCOUNT ///< Just to count params 
	};

	/*!\brief This class is kept information about artefact items
	
	It keeps only modificator of hero params
	*/

	class Artefact : virtual public Item {
	private:
		HeroParams mod;
	protected:
		virtual void save(std::fstream &);
		int getStamina();
		int getStrength();
		int getAgility();
		double getMaxHealth();
	public:
		Artefact(int sta = 0, int str = 0, int ag = 0, double mh = 0) :mod(sta, str, ag, mh) {};
		void changeParams(ArtefactParams type, double);
	};

	/*!\brief This class describes Artifact Weapon 

	And so on
	*/

	class ArtefactWeapon :public Weapon, public Artefact {
	public:
		void save(std::fstream &s);
		ItemType iAm();
		void load(std::fstream&s);
		int getStamina();
		int getAgility();
		int getStrength();
		ArtefactWeapon(string name, double damage, HeroParams mod_) :Item(name), Weapon(name, damage), Artefact(mod_.stamina, mod_.strength, mod_.agility, mod_.MaxHealth) {};
		ArtefactWeapon(string name, double damage, HeroParams mod_, map<EnemyType, double> map, int enchanted = 0) : Item(name), Weapon(name, damage,map, enchanted), Artefact(mod_.stamina,mod_.strength,mod_.agility, mod_.MaxHealth ) {};
		virtual double generateDamage();
		virtual WeaponParams getFeatures();
		void changeFeatures(double damage_, ArtefactParams type_a = ARTEFACTCOUNT, double value = 0, EnemyType type_e = EnemyType::ENEMYCOUNT, double multiplier = 1.0);
	};

	/*!\brief Structure that contain all equipment parameters
	*/
	struct EquipParams {
		double def; ///<Defence
		EquipType type; ///< Type of equipment
		bool isArtifact; ///< Is it an Artifact?)
		HeroParams params; ///< For artifact weapon
		friend std::ostream & operator <<(std::ostream&, const EquipParams&);
	};

	/*! \brief This class describes everything about equipment

	Equipment is needed for some defence 
	*/

	class Equipment :virtual public Item {
	private:
		EquipType type; ///< Type of equipment
		double defence;///< Defence of an equipment
	protected:
		double getDefence();
		void setDefence(double);
		void setType(EquipType e);
	public:
		virtual void save(std::fstream &s);
		virtual void load(std::fstream&);
		ItemType iAm();
		virtual int getStamina();
		virtual int getAgility();
		virtual int getStrength();
		Equipment() :Item("Standart"), defence(5), type(EquipType::CHESTPLATE) {};
		EquipType getType();
		virtual EquipParams getFeatures();
		Equipment(EquipType type0, string name = "Standart",  double def=5) :Item(name), type(type0), defence(def) {};
		void changeFeatures(double defence_, EquipType t = EQUIPCOUNT);
		virtual double generateDefence();
	};

	/*! \brief This class describes Artefact Equipment

	It has additional Stamina, Strength, Agility
	*/

	class ArtefactEquipment : public Equipment, public Artefact {
	public:
		void save(std::fstream &s);
		virtual void load(std::fstream&s);
		ItemType iAm();
		int getStamina();
		int getStrength();
		int getAgility();
		ArtefactEquipment(string name, EquipType type0, double def, HeroParams mod_):Item(name),Equipment(type0, name, def), Artefact(mod_.stamina, mod_.stamina,  mod_.agility, mod_.MaxHealth){};
		double generateDefence();
		EquipParams getFeatures();
		void changeFeatures(double def, EquipType type_ =EQUIPCOUNT, ArtefactParams type_a = ARTEFACTCOUNT, double value = 0);
	};

	/*! \brief This class describes everything about picklocks
	
	They are needed to hack the chests
	*/

	class Picklocks : public Item {
	private:
		int amount; ///< Amount of picklocks in the lock pin bundle
	public:
		ItemType iAm();
		virtual void save(std::fstream&s);
		virtual void load(std::fstream&s);
		Picklocks(string name, int c = 1) : Item(name), amount(c) {};
		Picklocks() :amount(0) {};
		int getCount();
		void changeParam(int i);
	};

	/*! \brief This has everything about potion
	*/

	struct PotionParams
	{
		HeroParams params;///< What potion modifies
		double duration;///< Duration of an effect
		friend std::ostream & operator <<(std::ostream&, const PotionParams&);
	};

	/*! \brief This class describes everything about potions

	From features to duration
	*/

	class Potion : public Item {
	private:
		HeroParams features; ///<What potions improves
		int duration;///< Duration of an potion
	public:
		void save(std::fstream &s);
		virtual void load(std::fstream&s);
		ItemType iAm();
		Potion();
		Potion(string name, int duration1, HeroParams p) : Item(name), duration(duration1), features(p) {};
		int getDuration();
		HeroParams getParams();
		PotionParams getFeatures();
		void setDuration(int dur);
		void changeFeatures(int duration = 0, ArtefactParams a=ARTEFACTCOUNT, double value = 0);
	};

	/*!\brief Describes chords of an object*/

	struct Chords {
		int x,///<x
			y; ///<y
		Chords(int a, int b) :x(a), y(b) {};
	};

	/*!\brief This structure has everything about Chest*/

	struct ChestParams {
		int locklevel; ///< Level of a lock
		Item *item; ///< Item in the chest
		Chords pos; ///< Position of the chest on the map
		ChestParams(int lock, Chords p, Item * it) :locklevel(lock), item(it), pos(p) {};
		friend std::ostream & operator <<(std::ostream&, const ChestParams&);
	};

	/*! \brief This class describes everything about chest*/

	class Chest {
	private:
		int lockLevel; ///< Level of the lock
		Item *item; ///< Item in the chest
		Chords pos;///< Position of the chest on the map
	public:
		Chest(Item *i,int x, int y, int l = 1) :item(i), lockLevel(l), pos(x,y) {};
		ChestParams getParams();
		void changeParams(int lock=0, Item *i=nullptr, int x=-1, int y = -1); 
		void putItem(Item *i);
		void save(std::fstream&);
		virtual void load(std::fstream&s);
		~Chest() { if(item!=nullptr) delete item; };
	};

}
#endif