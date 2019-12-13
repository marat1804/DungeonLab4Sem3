#include "..//Dungeon/Cell.h"
#include "..//Dungeon/Menu.h"
#include <conio.h>
#include "windows.h"
#include <cstdlib>


using namespace CELL;
using namespace CHARACTERS;
using namespace ITEMS;
using namespace MENU;

int main() {
	int i;
	//std::cout << "Enter the name -> ";
	string buf = "17";
	//std::cin >> buf;
	Dialog menu;
	Dungeon *dungeon = nullptr;
	std::cout << "Do you want to start a new game(0) or load(1)?" << std::endl;
	std::cin >> i;
	switch (i) {
	case 0:
		std::cout << "Enter the name -> ";
		std::cin >> buf;
		dungeon = new Dungeon(buf);
		break;
	case 1:
		dungeon = new Dungeon(buf);
		dungeon->load();
		break;
	default:
		std::cout << "Error" << std::endl;
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		break;
	}
	int m;
	std::string move;
	std::cout << "Do you want to change the map(0) or play(1)? " << std::endl;
	std::cin >> m;
	int fl = 1;
	switch (m)
	{
	case 0:
		while (fl) {
			fl = menu.menu_main_print(*dungeon);
		}
		break;
	case 1:
		while (fl) {
			dungeon->printLevel(dungeon->getCurrLevel());
			move = _getch();
			dungeon->makeTurn(move);
			if (system("CLS")) system("clear");
		}
		break;
	default:
		std::cout << "Error" << std::endl;
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		break;
	}
	
	return 1;
}