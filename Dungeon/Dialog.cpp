
#include "Menu.h"
#include <iostream>

void menu_main() {

}



/* Weapon Change
double d;
		int j, fl = 1;
		while (fl) {
			std::cout << "What do you want to change? \n 0. Exit\n 1. Damage\n" << std::endl;
			if (enchantmments != nullptr)
				std::cout << "2. Multiplier \n -->" << std::endl;
			std::cin >> j;
			switch (j)
			{
			case 0:
				fl = 0;
				break;
			case 1:
				double d;
				std::cout << "What damage do you want to set for " << getName() << "? (now is " << getDamage() << ")" << std::endl;
				std::cin >> d;
				if (std::cin.good() && d > 0) {
					setDamage(d);
					std::cout << "Successfully changed";
				}
				else {
					std::cout << "Zero or error";
					std::cin.clear();
					std::cin.ignore(10000, '\n');
				}
				break;
			case 2:
				if (enchantmments != nullptr) {
					enchantmments->changeFeatures();
				}
				else {
					std::cout << "ERROR" << std::endl;
				}
				break;
			default:
				std::cout << "Error";
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				break;
			}
		}
*/

/*Enchantment change
int i, fl = 1;

				std::cout << "Which multiplier do you want to change: 1.Humanoid\n 2.Insect \n 3.Animal \n 4.Demon \n 5.Icy \n 6. Undead \n -->" << std::endl;
				int j;
				std::cin >> j;
				if (!std::cin.good() && j>6 && j<0) {
					std::cout << "Error";
					std::cin.clear();
					std::cin.ignore(10000, '\n');
				}
				else {
					std::cout << "Enter the multiplier -->";
					double po;
					std::cin >> po;
					if (!std::cin.good() && po<=0) {
						std::cout << "Error";
						std::cin.clear();
						std::cin.ignore(10000, '\n');
					}
					else {
						multipler[AllEnemy[i]] = po;
					}
				}

		*/

/*Artefect

int fl = 1;
		while (fl) {
			std::cout << "What parameter do you want to change: \n 0. Cancel \n1.Agility\n 2. Stamina \n 3. Sterength \n 4.Max Health\n -->";
			int i = -1;
			std::cin >> i;
			switch (i)
			{
			case 0:
				fl = 0;
				break;
			case 1:
				std::cout << "Enter the agility --> ";
				int a;
				std::cin >> a;
				if (!std::cin.good()) {
					std::cout << "Error";
					std::cin.clear();
					std::cin.ignore(10000, '\n');
				}
				else {
					mod.agility = a;
				}
				break;
			case 2:
				std::cout << "Enter the stamina --> ";
				int s;
				std::cin >> s;
				if (!std::cin.good()) {
					std::cout << "Error";
					std::cin.clear();
					std::cin.ignore(10000, '\n');
				}
				else {
					mod.stamina = s;
				}
				break;
			case 3:
				std::cout << "Enter the strength --> ";
				int st;
				std::cin >> st;
				if (!std::cin.good()) {
					std::cout << "Error";
					std::cin.clear();
					std::cin.ignore(10000, '\n');
				}
				else {
					mod.strength = st;
				}
				break;
			case 4:
				std::cout << "Enter the max health --> ";
				int h;
				std::cin >> h;
				if (!std::cin.good()) {
					std::cout << "Error";
					std::cin.clear();
					std::cin.ignore(10000, '\n');
				}
				else {
					mod.MaxHealth = h;
				}
			default:
				std::cout << "Error";
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				break;
			}
		}*/


/*Hero


std::cout << "What do you want to change? \n 1. Agility (now " << Params.agility << ") \n 2. Strength (now " << Params.strength <<
			") \n 3. Stamina (now " << Params.stamina << ") \n 4. MaxHealth (now " << Params.MaxHealth << ") \n";
		int fl = 0, i, a;
		do {
			std::cin >> i;
			if (!std::cin.good()) {
				std::cout << "Error";
				std::cin.clear();
				std::cin.ignore(10000, '\n');
			}
		} while (!std::cin.good() || i < 0 || i >4);
		do{
			std::cout << "Enter the parametr -->" << std::endl;
			std::cin >> a;
			if (!std::cin.good()) {
				std::cout << "Error";
				std::cin.clear();
				std::cin.ignore(10000, '\n');
			}
		} while (!std::cin.good() || a < 0);
		switch (i)
		{
		case 1:
			Params.agility = a;
			break;
		case 2:
			Params.strength = a;
			break;
		case 3:
			Params.stamina=a;
			break;
		case 4:
			double p = CurHealth / Params.MaxHealth;
			Params.MaxHealth = a;
			CurHealth = Params.MaxHealth * p;
			break;
		}*/


/* ene,y
std::cout << "What do you want to change? \n0. Cancel \n 1. Attack (now " << params.attack << ") \n 2. Defence (now " << params.defence <<
") \n 3. MaxHealth (now " << MaxHealth << ") \n 4. Type (now ";
switch (params.type)
{
case EnemyType::ANIMAL:
	std::cout << "Animal) \n";
	break;
case EnemyType::DEMON:
	std::cout << "Demon) \n";
	break;
case EnemyType::HUMANOID:
	std::cout << "Humanoid) \n";
	break;
case EnemyType::ICY:
	std::cout << "Icy) \n";
	break;
case EnemyType::INSECT:
	std::cout << "Insect) \n";
	break;
case EnemyType::UNDEAD:
	std::cout << "Undead) \n";
	break;
}
int fl = 0, i, a;
do {
	std::cin >> i;
	if (!std::cin.good()) {
		std::cout << "Error";
		std::cin.clear();
		std::cin.ignore(10000, '\n');
	}
} while (!std::cin.good() || i < 0 || i >4);
switch (i)
{
case 0:
	break;
case 1:
	do {
		std::cout << "Enter the parametr -->" << std::endl;
		std::cin >> a;
		if (!std::cin.good()) {
			std::cout << "Error";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
	} while (!std::cin.good() || a < 0);
	params.attack = a;
	break;
case 2:
	do {
		std::cout << "Enter the parametr -->" << std::endl;
		std::cin >> a;
		if (!std::cin.good()) {
			std::cout << "Error";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
	} while (!std::cin.good() || a < 0);
	params.defence = a;
	break;
case 3:
	std::cout << " 0 - Humanoid \n 1 - Insect \n 2 - Animal \n 3 - Demon \n 4 - Icy \n 5 - Undead \n ";
	do {
		std::cout << "Enter the parametr -->" << std::endl;
		std::cin >> a;
		if (!std::cin.good()) {
			std::cout << "Error";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
	} while (!std::cin.good() || a < 0);
	switch (a)
	{
	case EnemyType::ANIMAL:
		params.type = EnemyType::ANIMAL;
		break;
	case EnemyType::DEMON:
		params.type = EnemyType::DEMON;
		break;
	case EnemyType::HUMANOID:
		params.type = EnemyType::HUMANOID;
		break;
	case EnemyType::ICY:
		params.type = EnemyType::ICY;
		break;
	case EnemyType::INSECT:
		params.type = EnemyType::INSECT;
		break;
	case EnemyType::UNDEAD:
		params.type = EnemyType::UNDEAD;
		break;
	}
	break;
case 4:
	do {
		std::cout << "Enter the parametr -->" << std::endl;
		std::cin >> a;
		if (!std::cin.good()) {
			std::cout << "Error";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
	} while (!std::cin.good() || a < 0);
	double p = CurHealth / MaxHealth;
	MaxHealth = a;
	CurHealth = MaxHealth * p;
	break;
}
*/