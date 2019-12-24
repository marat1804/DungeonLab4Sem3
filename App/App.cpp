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
	//CELL::setFontSize(18);
	int i, flTable=0;
	int endGame = 0;
	//std::string fof;
	//std::fstream params("Floors/banner.txt", std::ios_base::in);
	//for (int i = 0; i < 12; ++i) {
	//	for (int j = 0; j < 80; ++j) {
	//		params >> fof;
	//		std::cout << fof;
	//	}
	//	//std::cout << "\n";
	//}

	std::ifstream input("Floors/banner.txt");
	std::string str;

	while (std::getline(input, str))
	{
		std::cout << str << std::endl;
	}
	//CELL::setFontSize(18);
	string buf = "17";
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
			if (flTable) {
				dungeon->printHeroTable();
				std::cout << std::endl;
			}
			move = _getch();
			if (move == "h") {
				flTable = !flTable;
			}
			if (move == "0") {
				fl = 0;
				std::cout << "Thanks for the game";
				break;
			}
			dungeon->makeTurn(move, endGame);
			if (endGame) {
				fl = 0;
				break;
			}
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