#define _CRT_SECURE_NO_WARNINGS
#include "Cell.h"
#include "windows.h"
#include <conio.h>

namespace CELL {

	/*! \brief Allows you to set a new type of a cell*/

	void Cell::setType(CellType c)
	{
		if (object != nullptr) {
			type = ITEM;
		}
		else {
			type = c;
		}
	}

	/*! \brief Puts a new item in the cell*/

	void Cell::putItem(Item * i, int p)
	{
		if (p) {
			if (object != nullptr)
				delete object;
		}
		object = i;
		i = nullptr;
		if (object != nullptr) {
			type = CellType::ITEM;
		}
		else
			type = CellType::FLOOR;
	}

	/*! \brief Returns type of a cell*/

	CellType Cell::getType()
	{
		return type;
	}

	/*!\brief Opens a door*/

	void Cell::openDoor()
	{
		if(type==CellType::CLOSED_DOOR)
			type = CellType::OPENED_DOOR;
		else {
			if (type == CellType::OPENED_DOOR)
				throw std::exception("The door is already opened");
			else throw std::exception("There is no door");
		}
	}
	/*!\brief closes a door*/
	void Cell::closeDoor()
	{
		if (type == CellType::OPENED_DOOR)
			type = CellType::CLOSED_DOOR;
		else {
			if (type == CellType::CLOSED_DOOR)
				throw std::exception("The door is already closed");
			else throw std::exception("There is no door");
		}
	}

	/*! \brief Overload operator =*/

	Cell & Cell::operator= (Cell &c)
	{
		if (this != &c) {
			type = c.type;
			object = c.object;
			c.object = nullptr;
			if (c.type == CellType::ITEM)
				c.type = CellType::FLOOR;
		}
		return (*this);
	}

	/*! \brief Allows you to put the item in the cell
	
	\param i - item that we held
	\param x - x chord
	\param y - y chord
	*/

	Floor::Floor() :  size(1, 1), enemyCount(0)
	{
		cell = new Cell* [1];
		*cell = new Cell[1];

	}

	Floor::Floor(int len, int wid) :size(len, wid), enemyCount(0)
	{
		cell = new Cell *[size.width];
		for (int i = 0; i < size.width; ++i)
			cell[i] = new Cell[size.length];
	}

	/*!\brief Puts an item to the x, y chords*/

	void Floor::putItem(Item * i, int x, int y, int p)
	{
		int co;
		Chest *temp;
		Enemy * tempE;
		CellType type = cell[y][x].getType();
		cell[y][x].putItem(i, p);
		if (type == CHEST) {
			if (chests.size() == 1)
				chests.pop_back();
			else {
				for (int i = 0; i < chests.size(); ++i) {
					if (chests[i]->getParams().pos.x == x && chests[i]->getParams().pos.y == y) {
						co = i;
						break;
					}
				}
				temp = chests[chests.size()-1];
				chests[chests.size()-1] = chests[co];
				chests[co] = temp;
				chests.pop_back();
			}
		}
		if (type == ENEMY) {
			if (enemies.size() == 1)
				enemies.pop_back();
			else {
				for (int i = 0; i < enemies.size(); ++i) {
					if (enemies[i]->getParams().pos.x == x && enemies[i]->getParams().pos.y == y) {
						co = i;
						break;
					}
				}
				tempE = enemies[enemies.size() - 1];
				enemies[enemies.size() - 1] = enemies[co];
				enemies[co] = tempE;
				enemies.pop_back();
			}
		}
	}

	/*! \brief Returns size of the floor*/

	Size Floor::getSize()
	{
		return size;
	}

	/*! \brief Changes type of the floor
	
	\param x - x chord
	\param y - y chord
	\param t - new type of the cell
	*/

	void Floor::changeType(int x, int y, CellType t)
	{
		if (x > size.length || y > size.width) {
			std::cout << "Error" << std::endl;
		}
		else {
			cell[y][x].setType(t);
		}
	}

	/*!\brief Allows you to know the type of the cell
	
	\return Cell type with chords [a][b]*/

	CellType Floor::getType(int a, int b)
	{
		return cell[b][a].getType();
	}

	/*!\brief Returns width of the floor*/

	int Floor::getWidth()
	{
		return size.width;
	}

	/*!\brief Returns length of the floor*/

	int Floor::getLength()
	{
		return size.length;
	}

	/*!\brief Returns all enemies that are in the floor*/
	vector<Enemy*>& Floor::getEnemylist()
	{
		return enemies;
	}

	/*!\brief Returns all chests that are in the floor*/
	vector<Chest*>& Floor::getChestList()
	{
		return chests;
	}
	/*! \brief Adds a chest to the floor*/

	void Floor::addChest(Chest * e, int x, int y)
	{
		chests.push_back(e);
		cell[y][x].setType(CellType::CHEST);
	}

	/*!\brief Puts a new enemie on the floor
	\param e - e new Enemy
	\param x - x chord
	\param y - y chord
	*/

	void Floor::putEnemy(Enemy *e, int x, int y)
	{
		enemies.push_back(e);
		cell[y][x].setType(CellType::ENEMY);
	}
	/*!\brief Sets a new size of the floor and generates a new array of the cell
	\param p - new size of the floor
	*/

	void Floor::setSize(Size p)
	{
		int l=size.length, w=size.width;
		if (p.length != 0) {
			size.length = p.length;
		}
		if (p.width != 0) {
			size.width = p.width;
		}
		l = l > p.length ? p.length : l;
		w = w > p.width ? p.width : w;
		Cell **neww;
		neww = new Cell *[size.width];
		for (int i = 0; i < size.width; ++i)
			neww[i] = new Cell[size.length];
		if (cell != nullptr) {
			for (int i = 0; i < w; ++i) {
				for (int j = 0; j < l; ++j) {
					neww[i][j] = cell[i][j];
				}
			}
			for (int i = 0; i < w; ++i)
				delete[] cell[i];
			delete[] cell;
		}
		cell = neww;
	}
	/*!\brief Prints a level*/

	void Floor::print(Chords hero)
	{
		CellType p;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		std::cout << std::endl;
		for (int i = 0; i < size.width; ++i) {
			for (int j = 0; j < size.length; ++j) {
				p = cell[i][j].getType();
				if (i == hero.y && j == hero.x) {
					setColor(Colors::Green, Colors::White);
					std::cout << "@";
					setColor(Colors::White, Colors::Black);
					continue;
				}
				switch (p)
				{
				case CELL::FLOOR:
					setColor(Colors::Black, Colors::White);
					std::cout << " ";
					break;
				case CELL::OPENED_DOOR:
					setColor(Colors::Green, Colors::White);
					std::cout << "/";
					break;
				case CELL::CLOSED_DOOR:
					setColor(Colors::LightRed, Colors::White);
					std::cout << "+";
					break;
				case CELL::STAIRS_UP:
					setColor(Colors::DarkGray, Colors::White);
					std::cout << "<";
					break;
				case CELL::STAIRS_DOWN:
					setColor(Colors::Magenta, Colors::White);
					std::cout << ">";
					break;
				case CELL::ENEMY:
					setColor(Colors::Red, Colors::White);
					std::cout << "e";
					break;
				case CELL::CHEST:
					setColor(Colors::LightBlue, Colors::White);
					std::cout << "&";
					break;
				case CELL::ITEM:
					setColor(Colors::Blue, Colors::White);
					std::cout << "*";
					break;
				case CELL::WALL:
					setColor(Colors::Black, Colors::White);
					std::cout << "#";
					break;
				default:
					break;
				}
			}
			std::cout << std::endl;
			setColor(Colors::White, Colors::Black);
		}
	}

	/*!\brief Saves all information of the floor*/

	void Floor::save(int n)
	{
		string s = "Floors/floor";
		string s1 = "Floors/enemy";
		string s2 = "Floors/items";
		string s3 = "Floors/chests";
		CellType type;
		vector<Item *> itemlist;
		vector<Chords> itempos;
		Chords itemss(0,0);
		
		s.append(std::to_string(n));
		s.append(".txt");

		s1.append(std::to_string(n));
		s1.append(".txt");

		s2.append(std::to_string(n));
		s2.append(".txt");

		s3.append(std::to_string(n));
		s3.append(".txt");

		std::fstream floor(s, std::ios_base::out);
		std::fstream enemy(s1, std::ios_base::out);
		std::fstream items(s2, std::ios_base::out);
		std::fstream chest(s3, std::ios_base::out);
		
		floor << size.width << " " << size.length << std::endl;
		for (int i = 0; i < size.width; ++i) {
			for (int j = 0; j < size.length; ++j) {
				type = cell[i][j].getType();
				switch (type)
				{
				case CELL::FLOOR:
					floor << CELL::FLOOR<<" ";
					break;
				case CELL::OPENED_DOOR:
					floor <<CELL::OPENED_DOOR<< " ";
					break;
				case CELL::CLOSED_DOOR:
					floor <<CELL::CLOSED_DOOR << " ";
					break;
				case CELL::STAIRS_UP:
					floor <<CELL::STAIRS_UP << " ";
					break;
				case CELL::STAIRS_DOWN:
					floor <<CELL::STAIRS_DOWN << " ";
					break;
				case CELL::WALL:
					floor << CELL::WALL << " ";
					break;
				case CELL::ENEMY:
					floor << CELL::ENEMY << " ";
					break;
				case CELL::CHEST: //!!!!
					floor << CELL::CHEST << " ";
					break;
				case CELL::ITEM:
					floor << CELL::ITEM << " ";
					itemss.x = i;
					itemss.y = j;
					itemlist.push_back(cell[i][j].getItem());
					break;
				default:
					break;
				}
			}
			floor << std::endl;
		}
		floor.close();
		items << itemlist.size() << std::endl;
		for (int j = 0; j < itemlist.size(); ++j) {
			items << itemss.x <<" "<< itemss.y << std::endl;
			itemlist[j]->save(items);
		}
		items.close();
		enemy << enemies.size() << std::endl;
		for (int j = 0; j < enemies.size(); ++j) {
			enemies[j]->save(enemy);
		}
		enemy.close();
		chest << chests.size() << std::endl;
		for (int i = 0; i < chests.size(); ++i)
			chests[i]->save(chest);
		chest.close();
	}
	/*! \brief Loads information of the floor from the file*/
	void Floor::load(int n)
	{

		Weapon *w;
		HeroParams param;
		Equipment *e;
		Potion *po;
		Picklocks *pi;
		ArtefactWeapon *aw;
		ArtefactEquipment *ae;

		string s = "Floors/floor";
		string s1 = "Floors/enemy";
		string s2 = "Floors/items";
		string s3 = "Floors/chests";
		CellType type;
		vector<Item *> itemlist;

		s.append(std::to_string(n));
		s.append(".txt");

		s1.append(std::to_string(n));
		s1.append(".txt");

		s2.append(std::to_string(n));
		s2.append(".txt");

		s3.append(std::to_string(n));
		s3.append(".txt");

		std::fstream floor(s, std::ios_base::in);
		std::fstream enemy(s1, std::ios_base::in);
		std::fstream items(s2, std::ios_base::in);
		std::fstream chest(s3, std::ios_base::in);



		floor >> size.width >> size.length;
		cell = new Cell *[size.width];
		for (int i = 0; i < size.width; ++i)
			cell[i] = new Cell[size.length];
		int buf;
		int k = 0;
		for (int i = 0; i < size.width; ++i) {
			for (int j = 0; j < size.length; ++j) {
				floor >> buf;
				switch (static_cast<CELL::CellType>(buf))
				{
				case CELL::FLOOR:
					cell[i][j].setType(CELL::FLOOR); 
					break;
				case CELL::OPENED_DOOR:
					cell[i][j].setType(CELL::OPENED_DOOR);
					break;
				case CELL::CLOSED_DOOR:
					cell[i][j].setType(CELL::CLOSED_DOOR);
					break;
				case CELL::STAIRS_UP:
					StairsUp.x = j;
					StairsUp.y = i;
					cell[i][j].setType(CELL::STAIRS_UP);
					break;
				case CELL::STAIRS_DOWN:
					StairsDown.x = j;
					StairsDown.y = i;
					cell[i][j].setType(CELL::STAIRS_DOWN);
					break;
				case CELL::WALL:
					cell[i][j].setType(CELL::WALL);
					break;
				case CELL::ENEMY:
					cell[i][j].setType(CELL::ENEMY);
					break;
				case CELL::CHEST: 
					cell[i][j].setType(CELL::CHEST);
					break;
				case CELL::ITEM:
					cell[i][j].setType(CELL::ITEM);
					break;
				default:
					break;
				}
			}
		}
		int n1, x, y, tip;
		items >> n1;
		for (int i = 0; i < n1; ++i) {
			items >> x >> y;
			items >> tip;
			switch (static_cast<ItemType>(tip))
			{
			case ITEMS::WEAPON:
				w = new Weapon;
				w->load(items);
				cell[x][y].putItem(w, 1);
				break;
			case ITEMS::EQUIPMENT:
				e = new Equipment;
				e->load(items);
				cell[x][y].putItem(e, 1);
				break;
			case ITEMS::POTION:
				po = new Potion;
				po->load(items);
				cell[x][y].putItem(po, 1);
				break;
			case ITEMS::PICKLOCK:
				pi = new Picklocks;
				pi->load(items);
				cell[x][y].putItem(pi, 1);
				break;
			case ITEMS::ENCHANTEDWEAPON:
				w = new Weapon;
				w->load(items);
				cell[x][y].putItem(w, 1);
				break;
			case ITEMS::ARTEFACTWEAPON:
				aw = new ArtefactWeapon("A", 1, param);
				aw->load(items);
				cell[x][y].putItem(aw, 1);
				break;
			case ITEMS::ARTEFACTEQUIPMENT:
				ae = new ArtefactEquipment("A", EquipType::AMULET, 1, param);
				ae->load(items);
				cell[x][y].putItem(ae, 1);
				break;
			case ITEMS::ARTEFACTENCHANTWEAPON:
				aw = new ArtefactWeapon("A", 1, param);
				aw->load(items);
				cell[x][y].putItem(aw, 1);
				break;
			default:
				break;
			}
		}
		items.close();
		enemy >> n;
		Enemy *enem;
		for (int i = 0; i < n; ++i) {
			enem = new Enemy("d",EnemyType::ANIMAL,0,0);
			enem->load(enemy);
			enemies.push_back(enem);
		}
		enemy.close();
		chest >> n;
		Chest *ch;
		for (int i = 0; i < n; ++i) {
			ch = new Chest(nullptr, 0, 0);
			ch->load(chest);
			chests.push_back(ch);
		}
		chest.close();
	}

	Item * Floor::getItem(int x, int y)
	{
		return cell[y][x].getItem();
	}

	Chest * Floor::findChest(Chords pos)
	{
		for (int i = 0; i < chests.size(); ++i) {
			if (chests[i]->getParams().pos.x == pos.x && chests[i]->getParams().pos.y == pos.y) {
				return chests[i];
			}
		}
		return nullptr;
	}

	Enemy * Floor::findEnemy(Chords pos)
	{
		for (int i = 0; i < enemies.size(); ++i) {
			if (enemies[i]->getParams().pos.x == pos.x && enemies[i]->getParams().pos.y == pos.y) {
				return enemies[i];
			}
		}
		return nullptr;
	}

	void Floor::EnemyMove( Chords heropos, Hero & hero)
	{
		if (enemies.size() != 0) {
			for (int i = 0; i < enemies.size(); ++i) {
				CELL::CellType type;
				int** floor;
				floor = new int *[size.width];
				for (int i = 0; i < size.width; ++i) {
					floor[i] = new int[size.length];
				}
				for (int i = 0; i < size.width; ++i) {
					for (int j = 0; j < size.length; ++j) {
						type = cell[i][j].getType();
						switch (type)
						{
						case CELL::CLOSED_DOOR:
							floor[i][j] = -1;
							break;
						case CELL::STAIRS_UP:
							floor[i][j] = -1;
							break;
						case CELL::STAIRS_DOWN:
							floor[i][j] = -1;
							break;
						case CELL::WALL:
							floor[i][j] = -1;
							break;
						case CELL::ENEMY:
							floor[i][j] = -1;
							break;
						case CELL::CHEST:
							floor[i][j] = -1;
							break;
						default:
							floor[i][j] = 0;
							break;
						}
					}
				}

				Chords newpos;
				CHARACTERS::Enemy * e = enemies[i];
				EnemyParams ep = e->getParams();
				double damage;
				newpos = e->move(floor, size, heropos);
				if (newpos.x != -1) {
					if (newpos.x == heropos.x && newpos.y == heropos.y) {
						damage = enemies[i]->dealDamage();
						hero.takeDamage(damage);
					}
					else {
						enemies[i]->setPos(newpos);
						cell[newpos.y][newpos.x].setType(CellType::ENEMY);
						cell[ep.pos.y][ep.pos.x].setType(CellType::FLOOR);
					}
				}

			}
		}
	}

	Floor::~Floor()
	{
		for (int i = 0; i < size.width; ++i)
			delete[] cell[i];
		delete[] cell;
		for (int i = 0; i < enemies.size(); ++i)
			delete enemies[i];

	}

	/*!\brief Allows you to create an enemy
	
	\param type - type of an emeny
	\param name - name of the enemy
	\param floor - where if will be
	\param x - x chord
	\param y - y chord
	\param it - item to the enemy
	\param health - health of the enemy
	*/

	void Dungeon::createEnemy(string name, EnemyType type, int floor, int x, int y, Item * it, double health)
	{
		Enemy *e = new Enemy (name, type, x, y, it, health);
		if (floor >= floors.size()) {
			floor = floors.size() - 1;
		}
		floors[floor]->putEnemy(e, x, y);
	}


	/*!\brief Makes turn */
	void Dungeon::makeTurn(std::string s, int & endGame)
	{
		int n, isAliveH, isAliveE;
		double damageH, damageE;
		int choice;
		CHARACTERS ::Enemy *enemy;
		EquipParams eqparam;
		WeaponParams weparam;
		PotionParams potparam;
		Item *item1, *item2;
		ItemType itemtype;
		CELL::Floor *f = getFloor(curLevel);;
		Chords first = hero.getPos(), second = hero.getPos();
		Size size = f->getSize();
		CELL::CellType type;
		if (s == "4" || s == "6" || s == "8" || s == "2") {
			n = std::stoi(s);
			switch (n)
			{
			case 4:
				second.x = second.x - 1;
				break;
			case 6:
				second.x = second.x + 1;
				break;
			case 8:
				second.y = second.y - 1;
				break;
			case 2:
				second.y = second.y + 1;
				break;
			default:
				break;
			}
			if (second.x >= 0 && second.x < size.length&&second.y >= 0 && second.y < size.width) {
				type = f->getType(second.x, second.y);
				switch (type)
				{
				case CELL::FLOOR:
					hero.setPos(second.x, second.y);
					break;
				case CELL::OPENED_DOOR:
					hero.setPos(second.x, second.y);
					break;
				case CELL::CLOSED_DOOR:
					break;
				case CELL::STAIRS_UP:
					if (curLevel != 0) {
						curLevel--;
						f = getFloor(curLevel);
						hero.setPos(f->getStairsDown().x, f->getStairsDown().y);
					}
					else {
						hero.setPos(second.x, second.y);
						std::cout << "It's the first floor";
						Sleep(1500);
					}
					break;
				case CELL::STAIRS_DOWN:
					if (curLevel != numberOfFloors - 1) {
						curLevel++;
						f = getFloor(curLevel);
						hero.setPos(f->getStairsUp().x, f->getStairsUp().y);
						if (curLevel == numberOfFloors - 1) {
							std::cout << "You win!!!";
							Sleep(3000);
						}
					}
					else{
					hero.setPos(second.x, second.y);
					std::cout << "It's the last floor";
					Sleep(1500);
					}
					break;
				case CELL::WALL:
					break;
				case CELL::ENEMY:
					enemy = f->findEnemy(second);
					std::cout << "Before: " << std::endl;
					std::cout << enemy->getParams() << std::endl;
					std::cout << hero.getParams() << std::endl;
					damageE = enemy->dealDamage();
					damageH = hero.generateDamage();
					isAliveE = enemy->getDamage(damageH, hero.getWeapon()->getEnchants());
					if (isAliveE) {
						isAliveH = hero.takeDamage(damageE);
						if (isAliveH) {
							endGame = 0;
						}
						else {
							endGame = 1;
						}
					}
					else {
						item1 = enemy->dropItem();
						f->putItem(item1, second.x, second.y, 0);
					}
					Sleep(2000);
					std::cout << std::endl;
					std::cout << "After: " << std::endl;
					if (isAliveE) {
						std::cout << enemy->getParams() << std::endl;
					}
					if (!isAliveE)
						hero.getExp(enemy->getParams().exp);
					std::cout << hero.getParams() << std::endl;
					Sleep(2000);
					break;
				case CELL::CHEST:
					break;
				case CELL::ITEM:
					hero.setPos(second.x, second.y);
				}
			}
		}

		//taking item
		if (s == "e") {
			item1 = f->getItem(first.x, first.y);
			if (item1 != nullptr) {
				itemtype = item1->iAm();

				std::cout << "Do you want to take it? yes(1)/no(0)" << std::endl;
				if (itemtype == ItemType::WEAPON || itemtype == ItemType::ENCHANTEDWEAPON || itemtype == ItemType::ARTEFACTENCHANTWEAPON || itemtype == ItemType::ARTEFACTWEAPON) {
					weparam = dynamic_cast<Weapon*>(item1)->getFeatures();
					std::cout << "New - " << weparam << std::endl;
					std::cout << "Your - " << hero.getWeaponP() << std::endl;
				}
				if (itemtype == ItemType::ARTEFACTEQUIPMENT || itemtype == ItemType::EQUIPMENT) {
					eqparam = dynamic_cast<Equipment*>(item1)->getFeatures();
					std::cout << "New - " << eqparam << std::endl;
					std::cout << "Your - " << hero.getEquipP(eqparam.type) << std::endl;
				}
				if (itemtype == ItemType::PICKLOCK)
					std::cout << dynamic_cast<Picklocks*>(item1)->getCount() << " picklocks" << std::endl;
				if (itemtype == ItemType::POTION) {
					potparam = dynamic_cast<Potion *>(item1)->getFeatures();
					std::cout << "Do you want to take it? yes(1)/no(0)" << std::endl;
					std::cout << "New - " << potparam << std::endl;
				}
				std::cin >> choice;
				switch (choice)
				{
				case 1:
					item2 = hero.takeItem(item1);
					//hero.setItem(item1);
					f->putItem(item2, first.x, first.y, 0);
					break;
				case 0:
					break;
				default:
					std::cout << "Error" << std::endl;
					std::cin.clear();
					std::cin.ignore(10000, '\n');
					break;
				}
			}
			else {
				std::cout << "There is no item under you";
				Sleep(1300);
			}
		}

		//open doors
		if (s == "o") {
			if (first.x + 1 >= 0 && first.x + 1 < size.length) {
				type = f->getType(first.x+1, first.y);
				if (type == CellType::CLOSED_DOOR) {
					f->changeType(first.x + 1, first.y, CellType::OPENED_DOOR);
					return;
				}
			}
			if (first.x - 1 >= 0 && first.x - 1 < size.length) {
				type = f->getType(first.x - 1, first.y);
				if (type == CellType::CLOSED_DOOR) {
					f->changeType(first.x - 1, first.y, CellType::OPENED_DOOR);
					return;
				}
			}
			if (first.y + 1 >= 0 && first.y + 1 < size.width) {
				type = f->getType(first.x, first.y+1);
				if (type == CellType::CLOSED_DOOR) {
					f->changeType(first.x, first.y + 1, CellType::OPENED_DOOR);
					return;
				}
			}
			if (first.y - 1 >= 0 && first.y - 1 < size.width) {
				type = f->getType(first.x, first.y - 1);
				if (type == CellType::CLOSED_DOOR) {
					f->changeType(first.x, first.y - 1, CellType::OPENED_DOOR);
					return;
				}
				else {
					std::cout << "There is no closed doors nearby" << std::endl;
					Sleep(1000);
				}
			}
		}
		
		//close doors
		if (s == "c") {
			if (first.x + 1 >= 0 && first.x + 1 < size.length) {
				type = f->getType(first.x + 1, first.y);
				if (type == CellType::OPENED_DOOR) {
					f->changeType(first.x + 1, first.y, CellType::CLOSED_DOOR);
					return;
				}
			}
			if (first.x - 1 >= 0 && first.x - 1 < size.length) {
				type = f->getType(first.x - 1, first.y);
				if (type == CellType::OPENED_DOOR) {
					f->changeType(first.x - 1, first.y, CellType::CLOSED_DOOR);
					return;
				}
			}
			if (first.y + 1 >= 0 && first.y + 1 < size.width) {
				type = f->getType(first.x, first.y + 1);
				if (type == CellType::OPENED_DOOR) {
					f->changeType(first.x, first.y + 1, CellType::CLOSED_DOOR);
					return;
				}
			}
			if (first.y - 1 >= 0 && first.y - 1 < size.width) {
				type = f->getType(first.x, first.y - 1);
				if (type == CellType::OPENED_DOOR) {
					f->changeType(first.x, first.y - 1, CellType::CLOSED_DOOR);
					return;
				}
				else {
					std::cout << "There is no opened doors nearby" << std::endl;
					Sleep(1000);
				}
			}

		}

		//open chest
		Item * itemchest;
		Chest * chest;
		int chestflag = 0, pick;
		if (s == "g") {
			if (first.x + 1 >= 0 && first.x + 1 < size.length) {
				type = f->getType(first.x + 1, first.y);
				if (type == CellType::CHEST) {
					second.x = first.x + 1;
					chestflag = 1;
				}
			}
			if (first.x - 1 >= 0 && first.x - 1 < size.length) {
				type = f->getType(first.x - 1, first.y);
				if (type == CellType::CHEST) {
					second.x = first.x - 1;
					chestflag = 1;
				}
			}
			if (first.y + 1 >= 0 && first.y + 1 < size.width) {
				type = f->getType(first.x, first.y + 1);
				if (type == CellType::CHEST) {
					second.y = first.y + 1;
					chestflag = 1;
				}
			}
			if (first.y - 1 >= 0 && first.y - 1 < size.width) {
				type = f->getType(first.x, first.y - 1);
				if (type == CellType::CHEST) {
					second.y = first.y - 1;
					chestflag = 1;
				}
				else {
					if (chestflag == 0) {
						std::cout << "There is no chests nearby" << std::endl;
						Sleep(1000);
						return;
					}
				}
			}
			chest = f->findChest(second);
			std::cout << chest->getParams();
			std::cout << "Do you want to open? (1 or 0) ";
			std::cin >> chestflag;
			if (chestflag == 1) {
				pick = hero.openChest();
				if (pick > 0) {
					itemchest = chest->open(hero.getHackProb());
					if (itemchest) {
						f->putItem(itemchest, second.x, second.y, 1);
						std::cout << "Opened";
					}
					else {
						std::cout << "Better luck next time";
					}
				}
				else {
					std::cout << "You don't have picklocks.";
				}
			}
			else {
				std::cout << "Error" << std::endl;
				std::cin.clear();
				std::cin.ignore(10000, '\n');
			}
			Sleep(1400);
		}

		//Drink potion
		if (s == "z") {
			try {
				hero.drinkPotion();
			}
			catch (std::exception &ex) {
				std::cout << "Invalid index";
				Sleep(1500);
			}
			catch (std::runtime_error &ex) {
				std::cout << ex.what();
				Sleep(1500);
			}
		}
		f->EnemyMove(hero.getPos(), hero);
		timer();
	}

	/*!\brief Returns current level*/
	int Dungeon::getCurrLevel()
	{
		return curLevel;
	}
	/*!\brief Returns a size of chosen floor*/

	Size Dungeon::getSize(int i)
	{
		if(floors.size()==0){
			return Size(0, 0);
		}
		return floors[i]->getSize();
	}
	/*!\brief Allows you to change a size of the floor
	\param i - which floor
	\param p - new size of the floor
	*/

	void Dungeon::changeMapSize(int i , Size p)
	{
		floors[i]->setSize(p);
	}

	/*! \brief Saves all the information of the Dungeon*/

	void Dungeon::save()
	{
		std::fstream params("Floors/dungeon.txt", std::ios_base::out);
		params << numberOfFloors << " " << curLevel << std::endl;
		hero.save();
		for (int i = 0; i < floors.size(); ++i) {
			floors[i]->save(i);
		}
	}
	/*!\brief Loads all the information from the file*/

	void Dungeon::load()
	{
		floors.pop_back();
		std::fstream params("Floors/dungeon.txt", std::ios_base::in);
		params >> numberOfFloors >> curLevel;
		hero.load();
		Floor *f;
		for (int i = 0; i < numberOfFloors; ++i) {
			f = new Floor;
			f->load(i);
			floors.push_back(f);
		}
	}
	/*!\brief Returns HeroWeapon*/

	Weapon * Dungeon::getWeapon()
	{
		return hero.getWeapon();
	}
	/*! \brief  Allows you to change the cell type
	\param n - which floor
	\param x - x chord
	\param y - y chord
	\param t - new type of the cell*/
	void Dungeon::changeCellType(int n, int x, int y, CellType t)
	{
		floors[n]->changeType(x, y, t);
	}

	/*!\brief Allows you to change the hero params
	\param index - What to change
	\value - new value of the hero param*/

	void Dungeon::changeHeroParams(HeroParamIndex index, double value)
	{
		hero.changeParams(index, value);
	}
	/*!\brief Returns hero params*/
	HeroParams Dungeon::getHeroParams()
	{
		return hero.getParams();
	}
	/*! \brief Prints the chosen level*/
	void Dungeon::printLevel(int n)
	{
		floors[n]->print(hero.getPos());
	}

	/*!\brief Returns hero to change it*/

	Hero & Dungeon::getHero()
	{
		return hero;
	}

	/*!\brief Returns floor to change
	\param i - what floor to change
	*/

	Floor * Dungeon::getFloor(int i)
	{
		return floors[i];
	}

	/*!\brief Adds a new floor*/

	void Dungeon::addFloor()
	{
		Floor *f = new Floor(10, 10);
		++numberOfFloors;
		floors.push_back(f);
	}

	void Dungeon::printHeroTable()
	{
		Map<HeroParamIndex, double> table = hero.getTable();
		Map<HeroParamIndex, double>::Iterator it;
		for (it = table.begin(); it != table.end(); ++it) {
			switch ((*it).first)
			{
			case HeroParamIndex::AGILITY:
				std::cout << "Agility - ";
				break;
			case HeroParamIndex::STAMINA:
				std::cout << "Stamina - ";
				break;
			case HeroParamIndex::STRENGTH:
				std::cout << "Strength - ";
				break;
			case HeroParamIndex::CURHEALTHHERO:
				std::cout << "CurHealth - ";
				break;
			case HeroParamIndex::MAXHEALTHHERO:
				std::cout << "MaxHealth - ";
				break;
			}
			std::cout << (*it).second << " ";
		}
	}

	void Dungeon::timer()
	{
		hero.timer();
	}

	void setColor(int txt, int bg)
	{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | txt));
	}

	void setFontSize(int size) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_FONT_INFOEX fontInfo;

		fontInfo.cbSize = sizeof(fontInfo);

		GetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);


		wcscpy(fontInfo.FaceName, L"Lucida Console");

		fontInfo.dwFontSize.Y = size;
		SetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
	}

}