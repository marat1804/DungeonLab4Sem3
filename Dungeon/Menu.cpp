#include "Menu.h"


namespace MENU {

	void Dialog::menu_map_print(CELL::Floor *floor, CELL::Dungeon &d)
	{
		Weapon *w;
		Equipment *eq;
		Potion *p;
		Picklocks *pi;
		ItemType t;
		HeroParams mod;
		int fl = 1, i, x, y;
		int n;
		int tip;
		vector<Enemy *> enemy;
		vector<Chest *> chest;
		CELL::Size map(0,0);
		ITEMS::Chest *ch;
		CHARACTERS::Enemy *e;
		while (fl) {
			print(MapMenu);
			map = floor->getSize();
			std::cout << "Width - " << map.width << " Length - " << map.length << std::endl;
			floor->print(d.getHero().getPos());
			std::cin >> i;
			switch (i)
			{
			case 0:
				fl = 0;
				break;				
			case 1:
				std::cout << "Enter the length and width (0 if you don't want to change)" << std::endl;
				std::cin >> map.length >> map.width;
				floor->setSize(map);
				break;
			case 2:
				std::cout << "Enter the chords -> ";
				int x, y;
				std::cin >> x >> y;
				print(CellType);
				int type;
				std::cin >> type;
				if (type >= 0 && type <= 5) {
					floor->changeType(x, y, static_cast<CELL::CellType>(type));
				}
				else
					std::cout << "Error" << std::endl;
				break;
			case 3:
				std::cout << "Where do you want to put it -->";
				std::cin >> x >> y;
				ch = new Chest(new Weapon, x, y, 1);
				floor->addChest(ch, x, y);
				break;
			case 4:
				std::cout << "Where do you want to put it -->";
				std::cin >> x >> y;
				e = new Enemy("Enemy", EnemyType::ANIMAL, x, y);
				floor->putEnemy(e,x,y);
				break;
			case 5:
				d.addFloor();
				break;
			case 6:
				chest = floor->getChestList();
				if (chest.size() == 0) {
					std::cout << "There is no chests on the floor";
				}
				else {
					std::cout << "Which do you want to change?" << std::endl;
					for (int i = 0; i < chest.size(); ++i) {
						std::cout << i << " " << chest[i]->getParams() << std::endl;
					}
					std::cin >> x;
					if (x >= 0 && x < chest.size())
						menu_chest_change(chest[x], floor);
				}
				break;
			case 7:
				enemy = floor->getEnemylist();
				if (enemy.size() == 0) {
					std::cout << "There is no enemy on the floor";
				}
				else {
					std::cout << "Which do you want to change?" << std::endl;
					for (int i = 0; i < enemy.size(); ++i) {
						std::cout << i << " " << enemy[i]->getParams() << std::endl;
					}
					std::cin >> x;
					if (x >= 0 && x < enemy.size())
						menu_enemy_print(enemy[x]);
				}
				break;
			case 8:
				std::cout << "Where do you want to put it?";
				std::cin >> x >> y;
				std::cout << "What do you want to create?" << std::endl;
				print(TypeOfItem);
				std::cin >> tip;
				switch (tip)
				{
				case 0:
					w = new Weapon;
					floor->putItem(w, x, y,1);
					menu_weapon_print(w);
					break;
				case 1:
					eq = new Equipment;
					floor->putItem(eq, x, y,1);
					menu_equipment_change(eq);
					break;
				case 2:
					p = new Potion("Potion", 15, mod);
					floor->putItem(p, x, y,1);
					menu_potion_change(p);
					break;
				case 3:
					pi = new Picklocks("Picklocks");
					floor->putItem(pi, x, y,1);
					menu_picklock_change(pi);
					break;
				default:
					break;
				}
				break;
			default:
				std::cout << "Error" << std::endl;
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				break;
			}
		}
	}

	int Dialog::menu_main_print(CELL::Dungeon &d)
	{
		print(MainMenu);
		int n;
		int m;
		std::cin >> n;
		switch (n)
		{
		case 0:
			d.save();
			return 0;
			break;
		case 1:
			menu_hero_print(d);
			break;
		case 2:
			std::cout << "Choose the floor( from 0 to " << d.getLevelCount() - 1 << ") --> ";
			std::cin >> m;
			if (m < 0 || m >= d.getLevelCount()) {
				std::cout << "Error!" << std::endl;
				n = 6;
				return 1;
			}

			menu_map_print(d.getFloor(m), d);
			break;
		default:
			std::cout << "Error" << std::endl;
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			return 1;
			break;
		}
		return 1;
	}

	void Dialog::menu_hero_print(CELL::Dungeon &d)
	{
		int fl = 1, x, y;
		Hero & h = d.getHero();
		Weapon *w;
		Chords p(0,0);
		Equipment *newe;
		CELL::Floor * f = d.getFloor(d.getCurrLevel());
		map<EquipType, Equipment *> &e = h.getEquipMap();
		while (fl) {
			print(HeroChange);
			int n;
			std::cin >> n;
			switch (n)
			{
			case 0:
				fl = 0;
				break;
			case 1:
				menu_heroparams_print(d);
				break;
			case 2:
				w = menu_weapon_print(h.getWeapon());
				h.setItem(w);
				break;
			case 3:
				std::cout << "What do you want to change?" << std::endl;
				for (int i = 0; i < e.size(); ++i) {
					std::cout << i << " " << e[static_cast<EquipType>(i)]->getFeatures()<<std::endl;
				}
				std::cin >> x;
				newe = menu_equipment_change(e[static_cast<EquipType>(x)]);
				h.setItem(newe);
				break;
			case 4:
				std::cout << "x - " << h.getPos().x << " y - " << h.getPos().y << std::endl;
				std::cout << "Enter a new position --> ";
				std::cin >> x >> y;
				if (!std::cin.good()) {
					std::cout << "Error" << std::endl;
					std::cin.clear();
					std::cin.ignore(10000, '\n');
					continue;
				}
				else {
					p = h.getPos();
					if (f->getType(x, y) == CELL::CellType::FLOOR) {
						h.setPos(x, y);
					}
					else {
						std::cout << "There is something but not floor" << std::endl;
					}
				}

				break;
			default:
				std::cout << "Error" << std::endl;
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				break;
			}
		}
	}

	void Dialog::menu_enemy_print(Enemy *e)
	{
		Weapon *w;
		Equipment *eq;
		Potion *p;
		Picklocks *pi;
		HeroParams mod;
		int fl = 1, x;
		double d;
		while (fl) {
			print(EnemyChange);
			int n;
			std::cout << e->getParams();
			std::cin >> n;
			if (n == 1 || n == 2 || n == 3) {
				std::cout << "Enter the value -->";
				std::cin >> d;
			}
			switch (n)
			{
			case 0:
				fl = 0;
				break;
			case 1:
				e->changeParams(ENEMYPARAMETRS::ATTACK, d);
				break;
			case 2:
				e->changeParams(ENEMYPARAMETRS::DEFENCE, d);
				break;
			case 3:
				e->changeParams(ENEMYPARAMETRS::MAXHEALTH, d);
				break;
			case 4:
				std::cout << "Choose the type -->" << std::endl;
				print(TypeOfEnemy);
				std::cin >> x;
				if (x >= 0 && x < 6) {
					e->changeParams(ENEMYPARAMETRSCOUNT, 0, static_cast<EnemyType>(x));
				}
				break;
			case 5:
				if (e->getItem() == nullptr) {
					std::cout << "There is now item. What do you like to create?" << std::endl;
					print(TypeOfItem);
					std::cin >> x;
					if (x >= 0 && x < 4) {
						switch (x)
						{
						case 0:
							w = new Weapon;
							e->putItem(w);
							menu_weapon_print(w);
							break;
						case 1:
							eq = new Equipment;
							e->putItem(eq);
							menu_equipment_change(eq);
							break;
						case 2:
							p = new Potion("Potion",15,mod);
							e->putItem(p);
							menu_potion_change(p);
							break;
						case 3:
							pi = new Picklocks("Picklocks");
							e->putItem(pi);
							menu_picklock_change(pi);
							break;
						default:
							break;
						}
					}
				}
			default:
				std::cout << "Error" << std::endl;
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				break;
			}
		}
	}

	void Dialog::menu_heroparams_print(CELL::Dungeon &d)
	{
		int fl = 1;
		double val;
		while (fl) {
			print(HeroParamsChange);
			HeroParams p = d.getHeroParams();
			std::cout << "Now - " << p << std::endl;
			int n;
			std::cin >> n;
			if (n) {
				std::cout << "Enter the value -->";
				std::cin >> val;
			}
			try {
				switch (n)
				{
				case 0:
					fl = 0;
					break;
				case 1:
					d.changeHeroParams(CHARACTERS::HeroParamIndex::AGILITY, val);
					break;
				case 2:
					d.changeHeroParams(CHARACTERS::HeroParamIndex::STRENGTH, val);
					break;
				case 3:
					d.changeHeroParams(CHARACTERS::HeroParamIndex::STAMINA, val);
					break;
				case 4:
					d.changeHeroParams(CHARACTERS::HeroParamIndex::MAXHEALTHHERO, val);
					break;
				default:
					std::cout << "Invalid index" << std::endl;
					std::cin.clear();
					std::cin.ignore(10000, '\n');
					break;
				}
			}
			catch (std::exception &ex) {
				std::cout << ex.what() << std::endl << std::endl;
			}
			
		}
	}

	Weapon * Dialog::menu_weapon_print(Weapon *w)
	{
		int fl = 1, en=0;
		double dam;
		ArtefactWeapon *aw;
		HeroParams params;
		map < EnemyType, double> mult;
		Enchantments *e;
		Weapon *ww;
		ItemType t;
		while (fl) {
			print(WeaponChange);
			WeaponParams p = w->getFeatures();
			std::cout << p;
			int n;
			std::cin >> n;
			switch (n)
			{
			case 0:
				fl = 0;
				break;
			case 1:
				std::cout << "Enter the value --> ";
				std::cin >> dam;
				w->changeFeatures(dam);
				break;
			case 2:
				menu_enchant_print(w);
				break;
			case 3:
				t = w->iAm();
				if (t != ARTEFACTWEAPON && t != ARTEFACTENCHANTWEAPON) {
					dam = w->generateDamage();
					e = w->getEnchants();
					if (e != nullptr) {
						mult = e->getFeatures();
						en = 1;
					}
					aw = new ArtefactWeapon("Artefact_Weapon", dam, params, mult, en);
					//ww = w;
					w = aw;
					//delete ww;
				}

				menu_artefact_change(w);

				break;
			default:
				std::cout << "Error" << std::endl;
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				break;
			}
		}
		return w;
	}

	void Dialog::menu_enchant_print(Weapon *w) {

		int fl = 1; int n;
		double d, dam;
		while (fl) {
			print(EnchantChange);
			std::cin >> n;
			if (n == 0) {
				fl = 0;
			}
			else {
				std::cout << "Enter the value --> ";
				std::cin >> d;
				EnemyType type = static_cast<EnemyType>(n - 1);
				dam = w->generateDamage();
				w->changeFeatures(dam, type, d);
			}
		}
	}

	void Dialog::menu_artefact_change(Item * w)
	{
		ItemType t = w->iAm();
		Artefact *a = dynamic_cast<Artefact*>(w);
		int fl = 1; int n;
		double d;
		while (fl) {
			print(ArtefactChange);
			std::cin >> n;
			if (n != 0) {
				std::cout << "Enter the value --> ";
				std::cin >> d;
			}
			switch (n)
			{
			case 0:
				fl = 0;
				break;
			case 1:
				a->changeParams( ArtefactParams::AGILITY, d);
				break;
			case 2:
				a->changeParams(ArtefactParams::STAMINA, d);
				break;
			case 3:
				a->changeParams(ArtefactParams::STRENGTH, d);
				break;
			case 4:
				a->changeParams(ArtefactParams::MAXHEALTH, d);
				break;
			default:
				std::cout << "Error" << std::endl;
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				break;
			}
		}
	}

	Equipment * Dialog::menu_equipment_change(Equipment * e)
	{
		int fl = 1, typ = 0;
		double def;
		Equipment *ee;
		ArtefactEquipment *ae;
		HeroParams params;
		ItemType t;
		while (fl) {
			print(EquipChange);
			EquipParams p = e->getFeatures();
			std::cout << p;
			int n;
			std::cin >> n;
			switch (n)
			{
			case 0:
				fl = 0;
				break;
			case 1:
				std::cout << "Enter the value --> ";
				std::cin >> def;
				e->changeFeatures(def);
				break;
			case 2:
				print(TypeOfEquipment);
				std::cout << "-->";
				std::cin >> typ;
				if (typ >= 0 && typ <= 4) {
					e->changeFeatures(0, static_cast<EquipType>(typ));
				}
				break;
			case 3:
				t = e->iAm();
				if (t != ARTEFACTEQUIPMENT) {
					def = e->generateDefence();
					
					ae = new ArtefactEquipment("Artefact_"+ e->getName(), e->getType(), def, params);
					//ee = e;
					e = ae;
				}

				menu_artefact_change(e);
				break;
			default:
				std::cout << "Error" << std::endl;
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				break;
			}
		}
		return e;
	}

	void Dialog::menu_chest_change(Chest * ch, CELL::Floor *f)
	{
		Weapon *w;
		Equipment *eq;
		Potion *p;
		Picklocks *pi;
		ItemType t;
		HeroParams mod;
		int fl = 1, typ = 0, n;
		int x,y;
		while (fl) {
			print(ChestChange);
			ChestParams param = ch->getParams();
			std::cout << "Now - " << param << std::endl;
			int n;
			x = 6;
			std::cin >> n;
			switch (n)
			{
			case 0:
				fl = 0;
				break;
			case 1:
				std::cout << "Do you want to create new Item(0) or change(1)?";
				std::cin >> x;
				switch (x)
				{
				case 0:
					std::cout << "What do you want to create?" << std::endl;
					print(TypeOfItem);
					std::cin >> y;
					switch (y)
					{
					case 0:
						w = new Weapon;
						ch->putItem(w);
						menu_weapon_print(w);
						break;
					case 1:
						eq = new Equipment;
						ch->putItem(eq);
						menu_equipment_change(eq);
						break;
					case 2:
						p = new Potion("Potion", 15, mod);
						ch->putItem(p);
						menu_potion_change(p);
						break;
					case 3:
						pi = new Picklocks("Picklocks");
						ch->putItem(pi);
						menu_picklock_change(pi);
						break;
					default:
						break;
					}
					break;
				case 1:
					t = param.item->iAm();
					if (t == ItemType::WEAPON || t == ItemType::ENCHANTEDWEAPON || t == ItemType::ARTEFACTENCHANTWEAPON || t == ItemType::ARTEFACTWEAPON)
						menu_weapon_print(dynamic_cast<Weapon *>(param.item));
					if (t == ItemType::ARTEFACTEQUIPMENT || t == ItemType::EQUIPMENT)
						menu_equipment_change(dynamic_cast<Equipment *>(param.item));
					if (t == ItemType::PICKLOCK)
						menu_picklock_change(dynamic_cast<Picklocks*>(param.item));
					if (t==ItemType::POTION)
						menu_potion_change(dynamic_cast<Potion *>(param.item));
					break;
				default:
					break;
				}
				break;
			case 2:
				std::cout << "Enter the value --> ";
				std::cin >> x;
				ch->changeParams(x);
				break;
			case 3:
				std::cout << "Enter the new pos -->";
				std::cin >> x >> y;
				ch->changeParams(0,nullptr, x, y);
				f->changeType(x, y, CELL::CellType::CHEST);
				break;
			default:
				std::cout << "Error" << std::endl;
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				break;
			}
		}
	}

	void Dialog::menu_picklock_change(Picklocks * p)
	{
		int fl = 1, x, y;
		while (fl) {
			print(PicklockChange);
			int n;
			std::cin >> n;
			switch (n)
			{
			case 0:
				fl = 0;
				break;
			case 1:
				std::cout << "Enter the amount";
				std::cin >> x;
				p->changeParam(x);
				break;
			default:
				std::cout << "Error" << std::endl;
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				break;
			}
		}

	}

	void Dialog::menu_potion_change(Potion * p)
	{
		int fl = 1, x, y;
		PotionParams param;
		while (fl) {
			print(PotionChange);
			param = p->getFeatures();
			std::cout << "Now - " << param;
			int n;
			std::cin >> n;
			if (n != 0) {
				std::cout << "Enter the value";
				std::cin >> x;
			}
			switch (n)
			{
			case 0:
				fl = 0;
				break;
			case 1:
				p->changeFeatures(0, ArtefactParams::AGILITY, x);
				break;
			case 2:
				p->changeFeatures(0, ArtefactParams::STAMINA, x);
				break;
			case 3:
				p->changeFeatures(0, ArtefactParams::STRENGTH, x);
				break;
			case 4:
				p->changeFeatures(0, ArtefactParams::MAXHEALTH, x);
				break;
			case 5:
				p->changeFeatures(x);
				break;
			default:
				std::cout << "Error" << std::endl;
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				break;
			}
		}
	}


	void Dialog::print(vector<string> &s)
	{
		for (int i = 0; i < s.size(); ++i)
			std::cout << s[i] << std::endl;
	}

}
