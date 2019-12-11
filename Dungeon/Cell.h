/*!
\file
\brief Header file with cell discription

This file has a cell of all character classes
*/

#include "Items.h"
#include "Ñharacters.h"

#ifndef _CELL_H_
#define _CELL_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::vector;
using std::string;
using std::map;
using namespace ITEMS;
using namespace CHARACTERS;


namespace CELL {

	/*! All types of the cell*/
	enum CellType{
		FLOOR,///< Just a floor
		OPENED_DOOR,///< Opened door
		CLOSED_DOOR,///<Closed door
		STAIRS_UP,///< Stairs up
		STAIRS_DOWN,///<Stairs down
		WALL,///< Wall
		ENEMY,///<Enemy
		CHEST,///< Chest
		ITEM///<Item
	};

	/*!\brief This class describes one cell of the floor*/

	class Cell {
	private:
		CellType type; ///< Type of a cell
		Item *object; ///< Item that is in the cell
	public:
		Cell(CellType c = CellType::FLOOR, Item *i = nullptr) :type(c), object(i) {};
		void setType(CellType);
		void putItem(Item *i);
		CellType getType();
		void openDoor();
		void closeDoor();
		/*! \brief Returns Item in the cell*/
		Item * getItem() { return object; };
		Cell & operator = (Cell &); 
		~Cell() { delete object; };
	};
	/*! \brief Struct that helds a size of a floor*/
	struct Size {
		 int length,///<Length
			width; ///< Width
		Size( int len,  int wid) :length(len), width(wid) {};
	};

	/*! \brief This class describes a entire floor*/

	class Floor {
	private:
		Cell **cell;///< Array of cells
		Size size;///< Size of floor
		vector<Enemy *> enemies; ///< This vectors has all enemies on the floor
		int enemyCount;///< Amount anemie of on the floor
		vector<Chest *> chests;
	public:
		Floor();
		Floor(int len, int wid);
		void putItem(Item *i, int x, int y);
		Size getSize();
		void changeType(int, int, CellType);
		CellType getType(int, int);
		int getWidth();
		int getLength();
		vector<Enemy *> & getEnemylist();
		vector<Chest *> & getChestList();
		void addChest(Chest *e, int x, int y);
		void putEnemy(Enemy *e, int x, int y);
		void setSize(Size);
		void print();
		void save(int);
		void load(int);
		~Floor();
	};

	/*! \brief This class describes all Dungeon
	
	This manipuletes everything
	*/

	class Dungeon {
	private:
		vector<Floor *> floors; ///< All floors
		int numberOfFloors;	 ///< Number of floors
		int curLevel; ///< Current level
		Hero hero; ///< Hero
	public: 
		Dungeon(string s) :numberOfFloors(1) { hero.setName(s); Floor *f=new Floor(10,10); floors.push_back(f); };
		void createEnemy(string name, EnemyType type, int floor, int x, int y, Item *it = nullptr, double health = 200);
		void makeTurn();
		Size getSize(int);
		/*!\brief Returns amount of the levels*/
		int getLevelCount() { return numberOfFloors; }; 
		void changeMapSize(int, Size);
		void save();
		void load();
		Weapon * getWeapon();
		void changeCellType(int n, int, int, CellType);
		void changeHeroParams(HeroParamIndex, double);
		HeroParams getHeroParams();
		void tryToOpenChest();
		void printLevel(int n);
		Hero & getHero();
		Floor * getFloor(int);
		void addFloor();
	};

}
#endif 


