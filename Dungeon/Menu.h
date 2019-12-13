/*!
\file
\brief Header file with all dialogs to change world, items, enemies, hero
*/

#ifndef _MENU_H_
#define _MENU_H_
#include <string>
#include <iostream>
#include "Cell.h"
#include "Characters.h"
#include "Items.h"
using std::string;
namespace MENU {
	class Dialog {
	private:
		vector<string> WeaponChange = { "What do you want to change ? ","0. Cancel", "1. Damage" , "2. Enchants", "3. Artefacts" }; ///<Menu to change the weapon

		vector< string> EnchantChange = { "Which multiplier do you want to change:","0. Cancel","1. Humanoid" ,"2. Insect","3. Animal","4. Demon ","5. Icy" ,"6. Undead" }; ///<Menu to change the enchant

		vector <string> ArtefactChange = { "What parameter do you want to change:","0. Cancel","1. Agility","2. Stamina","3. Sterength","4. Max Health" };///<Menu to change the artifact

		vector<string> EquipChange = { "What parameter do you want to change:","0. Cancel","1. Defence", "2. Type ", "3. Artefacts" };///<Menu to change the equipment

		vector<string>PotionChange = { "What parameter do you want to change:" ,"0. Cancel", "1.Agility","2. Stamina","3. Sterength","4. Max Health","5. Duration" };///<Menu to change the potion

		vector < string>ChestChange = { "What parameter do you want to change:" , "0. Cancel", "1. Item", "2. Locklevel", "3. Position" };///<Menu to change the chest

		vector < string> HeroChange = { "What do you want to change:", "0. Cancel", "1. Params", "2. Weapon", "3. Equipment", "4. Position" };///<Menu to change the hero

		vector < string> HeroParamsChange = { "What do you want to change", "0. Cancel", "1. Agility", "2. Strength", "3. Stamina", "4. MaxHealth" };///<Menu to change the hero parameters

		vector < string> EnemyChange = { "What do you want to change", "0. Cancel", "1. Attack", "2. Defence", "3. MaxHealth", "4. Type", "5. Item" };///<Menu to change the enemy

		vector < string > MainMenu = { "What do you want to do?", "0. Exit and save", "1. Hero Edit", "2. Map Edit" };///<Just main menu

		vector < string> MapMenu = { "What do you want to do?", "0. Cancel", "1. Change size", "2. Change cell type","3. Add chest", "4. Add Enemy", "5. Add Floor", "6. Edit chest", "7. Edit Enemy","8. Add Item" };///<Menu to change the map

		vector < string> CellType = { "0 - FLOOR","1 - OPENED_DOOR","2 - CLOSED_DOOR","3 - STAIRS_UP", "4 - STAIRS_DOWN","5 - WALL" };///<All the cell types

		vector<string> TypeOfEquipment = { " 0. HELMET", "1. CHESTPLATE","2. PANTS","3. SHOES","4. AMULET" };///<All types of equipment
		
		vector<string> TypeOfEnemy = { "0. HUMANOID","1. INSECT", "2. ANIMAL","3. DEMON", "4. ICY", "5. UNDEAD" };///<All types of enemies

		vector<string> TypeOfItem = { "0. WEAPON","1. EQUIPMENT","2. POTION","3. PICKLOCK" };///<All types of items

		vector<string> PicklockChange = { "0. Cancel", "1. Count" };///<Menu to change the picklocks
	public:
		Dialog() {};
		/*!\brief Prints the menu*/
		void print(vector<string> &);
		/*!\brief Map menu*/
		void menu_map_print(CELL::Floor * f, CELL::Dungeon &d);
		/*!\brief Main menu*/
		int menu_main_print(CELL::Dungeon &d);
		/*!\brief Hero menu*/
		void menu_hero_print(CELL::Dungeon &d);
		/*!\brief Enemy menu*/
		void menu_enemy_print(Enemy *e);
		/*!\brief HeroParams menu*/
		void menu_heroparams_print(CELL::Dungeon &d);
		/*!\brief Weapon menu*/
		Weapon * menu_weapon_print(Weapon *w);
		/*!\brief Enchants change menu*/
		void menu_enchant_print(Weapon *w);
		/*!\brief Artifact change menu*/
		void menu_artefact_change(Item *w);
		/*!\brief Equipment change*/
		Equipment * menu_equipment_change(Equipment *e);
		/*!\brief Chest menu*/
		void menu_chest_change(Chest *ch, CELL::Floor *);

		/*!\brief Picklock menu*/
		void menu_picklock_change(Picklocks *p);
		/*!\brief Potion change*/
		void menu_potion_change(Potion *p);
	};
}
#endif