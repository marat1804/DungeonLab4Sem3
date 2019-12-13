#include "Characters.h"
namespace CHARACTERS {

	Effect::Effect()
	{
		duration = 0;
		boost.agility = 0;
		boost.stamina = 0;
		boost.strength = 0;
	}

	/*!\brief Saves all information about effect into file*/

	void Effect::save()
	{
		std::fstream s("Hero/effects.txt", std::ios_base::out);
		s << boost.agility << " " << boost.stamina << " " << boost.strength <<
			" " << boost.MaxHealth << " " << duration;
		s.close();
	}

	void Effect::load()
	{
		std::fstream s("Hero/effects.txt", std::ios_base::in);
		string buf;
		s >> buf;
		boost.agility = std::stoi(buf);
		s >> buf;
		boost.stamina = std::stoi(buf);
		s >> buf;
		boost.strength = std::stoi(buf);
		s >> buf;
		boost.MaxHealth = std::stoi(buf);
		s >> buf;
		duration = std::stoi(buf);
		s.close();
	}

	/*!\brief Decreases duration of an effect*/

	int Effect::timer()
	{
		duration--;
		if (duration == 0) {
			wipe();
			return 0;
		}
		else
			return 1;
	}

	/*!\brief Wipes out all effects by the end of duration*/
	void Effect::wipe()
	{
		duration = 0;
		boost.agility = 0;
		boost.stamina = 0;
		boost.strength = 0;
	}

	/*! \brief Adds effects from the potion
	
	\param p - HeroParams by the potion
	\param dur - duration of the effect
	*/

	void Effect::add_effect(HeroParams p, int dur) throw (std::exception)
	{
		if (duration == 0) {
			boost = p;
			duration = dur;
		}
		else
			throw std::exception("There's already an effect");
	}

	/*!\brief Returns all boost the effect has now*/

	HeroParams Effect::getBoost()
	{
		return boost;
	}

	Hero::Hero(int x_, int y_) : experience(0), name("Player"), MaxPotionNumber(5), picklocks(2), pos(x_, y_), level(0)
	{
		srand(static_cast<unsigned int>(time(0)));
		Params.agility = 5;
		Params.stamina = 5;
		Params.strength = 5;
		Params.MaxHealth = 200;
		Params.CurHealth = Params.MaxHealth;
		weapon = new Weapon;
		Equipment* o1 = new Equipment(static_cast<EquipType>(0), "Hat", 0);
		Equipment* o2 = new Equipment(static_cast<EquipType>(1), "T-Shirt", 0);
		Equipment* o3 = new Equipment(static_cast<EquipType>(2), "Usual_pants", 0);
		Equipment* o4 = new Equipment(static_cast<EquipType>(3), "Boots", 0);
		Equipment *eq = new Equipment(EquipType::AMULET, "Ring", 0);
		equip[EquipType::HELMET] = o1;
		equip[EquipType::CHESTPLATE] = o2;
		equip[EquipType::PANTS] = o3;
		equip[EquipType::SHOES] = o4;
		equip[EquipType::AMULET] = eq;
		heroTable.add(HeroParamIndex::AGILITY ,Params.agility);
		heroTable.add(HeroParamIndex::STAMINA, Params.stamina);
		heroTable.add(HeroParamIndex::STRENGTH, Params.strength);
		heroTable.add(HeroParamIndex::CURHEALTHHERO, Params.CurHealth);
		heroTable.add(HeroParamIndex::MAXHEALTHHERO, Params.MaxHealth);
	}

	/*!\brief Generates a probability of successfull attack

	1 point of agility gives 0.01 plus to probability 
	*/

	double Hero::getAttackProb()
	{
		int bonus = 0;
		for (int i = 0; i < equip.size(); ++i) {
			bonus += equip[static_cast<EquipType>(i)]->getAgility();
		}
		bonus += weapon->getAgility();
		double b = effects.getBoost().agility + Params.agility + bonus;
		double prob = rand() / static_cast<double>(RAND_MAX) + 0.01 * b;
		return prob;
	}

	/*!\brief Hero gaining the experience 

	\param a - experience from died enemy
	*/

	void Hero::getExp(double a)
	{
		experience += a;
		if (experience >= level * 150) {
			experience -= level * 150;
			LevelUp();
		}
	}

	/*!\brief Generates a probability of successfull attack

	1 point of strength gives 0.01 plus to probability
	*/

	double Hero::getAttackBonus()
	{
		int bonus = 0;
		for (int i = 0; i < equip.size(); ++i) {
			bonus += equip[static_cast<EquipType>(i)]->getStrength();
		}
		return (effects.getBoost().strength + Params.strength + bonus) * 5;
	}

	/*! \brief Returns additional defence of hero

	Bonus defence generates from stamina. Every point of stamina gives 2.5 points of defence
	*/

	double Hero::getDefenceBonus()
	{
		int bonus = 0;
		for (int i = 0; i < equip.size(); ++i) {
			bonus += equip[static_cast<EquipType>(i)]->getStamina();
		}
		bonus += weapon->getStamina();
		return (effects.getBoost().stamina + Params.stamina + bonus)*2.5;
	}

	/*!\brief Generates damage 
	
	From weapon + bonus attack
	*/

	double Hero::generateDamage()
	{
		return weapon->generateDamage() + getAttackBonus();
	}

	/*!\brief Returns hack probability
	
	1 point of agility gives 0.01 plus to probability
	*/

	double Hero::getHackProb()
	{
		int bonus = 0;
		for (int i = 0; i < equip.size(); ++i) {
			bonus += equip[static_cast<EquipType>(i)]->getAgility();
		}
		bonus += weapon->getAgility();
		double b = effects.getBoost().agility + Params.agility + bonus;
		double prob = rand() / static_cast<double>(RAND_MAX) + 0.01 * b;
		return prob;
	}

	/*! \brief Levels up your hero*/

	void Hero::LevelUp()
	{
		level++;
		std::cout << "What do you want to upgrade? \n 1. +1 agility (now " << Params.agility << ") \n 2. +1 strength (now " << Params.strength <<
			") \n 3. +1 stamina (now " << Params.stamina << ") \n 4. +100 maxhealth (now " << Params.MaxHealth << ") \n";
		int fl = 0, i;
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
		case 1:
			Params.agility++;
			break;
		case 2:
			Params.strength++;
			break;
		case 3:
			Params.stamina++;
			break;
		case 4:
			double p = Params.CurHealth / Params.MaxHealth;
			Params.MaxHealth += 100;
			Params.CurHealth = Params.MaxHealth * p;
			break;
		}
	}

	/*! \brief Sets a new name to a hero*/

	void Hero::setName(string &s)
	{
		name = s;
	}
	/*!\brief Returns all equipment that has the hero*/
	map<EquipType, Equipment*>& Hero::getEquipMap()
	{
		return equip;
	}

	/*! \brief Returns all params of a hero*/

	HeroParams Hero::getParams()
	{
		return Params;
	}

	/*!\brief allows you to change the params of hero
	\param index - which hero param to change
	\param value - new value for hero param*/

	void Hero::changeParams(HeroParamIndex index, double value) throw(std::exception)
	{
		if (value <= 0)
			throw std::exception("Invalid value");
		switch (index)
		{
		case HeroParamIndex::AGILITY:
			Params.agility = value;
			break;
		case HeroParamIndex::STRENGTH:
			Params.strength = value;
			break;
		case HeroParamIndex::STAMINA:
			Params.stamina = value;
			break;
		case HeroParamIndex::MAXHEALTHHERO:
			Params.MaxHealth = value;
			Params.CurHealth = value;
			break;
		}
	}

	/*!\brief Taking a new item 

	Functions understand the type of an item
	\param i - new Item
	\return Item that was held in the backpack
	*/

	Item * Hero::takeItem(Item * i)
	{
		ItemType type = i->iAm();
		Item *p = nullptr;
		Equipment * e;
		Picklocks * pick;
		Weapon *w;
		Potion *pot;
		switch (type)
		{
		case ItemType::WEAPON:
			p = weapon;
			w = dynamic_cast<Weapon *>(i);
			weapon = w;
			break;
		case ItemType::EQUIPMENT:
			e = dynamic_cast<Equipment *>(i);
			p = equip[e->getType()];
			equip[e->getType()] = e;
			break;
		case ItemType::PICKLOCK:
			pick = dynamic_cast<Picklocks *> (i);
			picklocks += pick->getCount();
			break;
		case ItemType::POTION:
			if (potions.size() == MaxPotionNumber)
				throw std::exception("Max Number of potions get reached");
			else {
				pot = dynamic_cast<Potion*>(i);
				potions.push_back(pot);
			}
			break;
		case ItemType::ARTEFACTWEAPON:
			p = weapon;
			w = dynamic_cast<Weapon *>(i);
			weapon = w;
			break;
		case ItemType::ARTEFACTENCHANTWEAPON:
			p = weapon;
			w = dynamic_cast<Weapon *>(i);
			weapon = w;
			break;
		case ItemType::ARTEFACTEQUIPMENT:
			e = dynamic_cast<Equipment *>(i);
			p = equip[e->getType()];
			equip[e->getType()] = e;
			break;
		case ItemType::ENCHANTEDWEAPON:
			p = weapon;
			w = dynamic_cast<Weapon *>(i);
			weapon = w;
			break;
		}
		return p;
	}
	/*! \brief Sets a new Item after changing it*/
	void Hero::setItem(Item * i)
	{
		ItemType type = i->iAm();
		Item *p = nullptr;
		Equipment * e;
		Picklocks * pick;
		Weapon *w;
		Potion *pot;
		switch (type)
		{
		case ItemType::WEAPON:
			w = dynamic_cast<Weapon *>(i);
			weapon = w;
			break;
		case ItemType::EQUIPMENT:
			e = dynamic_cast<Equipment *>(i);
			equip[e->getType()] = e;
			break;
		case ItemType::PICKLOCK:
			pick = dynamic_cast<Picklocks *> (i);
			picklocks += pick->getCount();
			break;
		case ItemType::POTION:
			if (potions.size() == MaxPotionNumber)
				throw std::exception("Max Number of potions get reached");
			else {
				pot = dynamic_cast<Potion*>(i);
				potions.push_back(pot);
			}
			break;
		case ItemType::ARTEFACTWEAPON:
			w = dynamic_cast<Weapon *>(i);
			weapon = w;
			break;
		case ItemType::ARTEFACTENCHANTWEAPON:
			w = dynamic_cast<Weapon *>(i);
			weapon = w;
			break;
		case ItemType::ARTEFACTEQUIPMENT:
			e = dynamic_cast<Equipment *>(i);
			equip[e->getType()] = e;
			break;
		}
	}
	


	/*! \brief Hero drinks a potion 
	
	And it gives you an additional params
	*/

	void Hero::drinkPotion() throw (std::exception)
	{
		if (potions.empty())
			throw std::exception( "You don't have any potions");
		else {
			std::cout << "You have: \n";
			for (int i = 0; i < potions.size(); ++i) {
				std::cout <<i<<" "<< potions[i]->getFeatures() << std::endl;
			}
			std::cout << "Which one do you want to drink ? -->";
		}
		int index;
		std::cin >> index;
		Potion *p = potions.at(index);
		effects.add_effect(p->getParams(), p->getDuration());
	}

	/*! \brief Sets a new posotion of a hero*/

	void Hero::setPos(int x_, int y_) {
		pos.x = x_;
		pos.y = y_;
	};

	/*! \brief Hero takes a damage
	
	Each point of defence reduces damage by 20%
	\param damage - damage
	*/

	void Hero::takeDamage(double damage)
	{
		double def = getDefenceBonus();
		double prob = rand() / static_cast<double>(RAND_MAX);
		if (prob < 0.10) {
			std::cout << "Damage was dodged"<<std::endl;
		}
 		else {
			damage -= def * 0.8;
			Params.CurHealth -= damage;
			if (Params.CurHealth <= 0) {
				std::cout << "You're dead";
			}
		}
	}

	/*! \brief Saves all information about hero into file*/

	void Hero::save()
	{
		std::fstream params("Hero/params.txt", std::ios_base::out);
		params << name<<std::endl;
		params << Params.agility << " " << Params.stamina << " " << Params.strength << " " << Params.CurHealth << " "
			<< Params.MaxHealth<<std::endl;
		params << experience << " " << level << " " << MaxPotionNumber << " " << picklocks << std::endl;
		params << pos.x << " " << pos.y;
		params.close();
		std::fstream wep("Hero/weapon.txt", std::ios_base::out);
		weapon->save(wep);
		wep.close();
		std::fstream eq("Hero/equipment.txt", std::ios_base::out);
		eq << equip.size() << std::endl;
		for (int i = 0; i < equip.size(); ++i) {
			equip[static_cast<EquipType>(i)]->save(eq);
		}
		eq.close();
		std::fstream s1("Hero/potion.txt", std::ios_base::out);
		s1 << potions.size() << std::endl;
		for (int i = 0; i < potions.size(); ++i) {
			potions[i]->save(s1);
		}
		s1.close();
		effects.save();
	}

	/*! \brief Loads information of hero from the file*/

	void Hero::load()
	{
		std::fstream params("Hero/params.txt", std::ios_base::in);
		params >> name;
		string buf;
		params >> buf;
		Params.agility=std::stoi(buf);
		params >> buf;
		Params.stamina = std::stoi(buf);
		params >> buf;
		Params.strength = std::stoi(buf);
		params >> buf;
		Params.CurHealth = std::stod(buf);
		params >> buf;
		Params.MaxHealth = std::stod(buf);
		params >> buf;
		experience = std::stod(buf);
		params >> buf;
		level = std::stoi(buf);
		params >> buf;
		MaxPotionNumber = std::stoi(buf);
		params >> buf;
		picklocks = std::stoi(buf);
		params >> buf;
		pos.x = std::stoi(buf);
		params >> buf;
		pos.y = std::stoi(buf);
		params.close();
		std::fstream wep("Hero/weapon.txt", std::ios_base::in);
		int i;
		wep >> i;
		if (static_cast<ItemType>(i) == ItemType::ARTEFACTWEAPON|| static_cast<ItemType>(i) == ItemType::ARTEFACTENCHANTWEAPON) {
			delete weapon;
			weapon = new ArtefactWeapon("lol", 11, Params);
		}
		weapon->load(wep);
		wep.close();
		effects.load();
		std::fstream eq("Hero/equipment.txt", std::ios_base::in);
		eq >> buf;
		int count = std::stoi(buf);
		Equipment* o1 = new Equipment(static_cast<EquipType>(4), "Hat", 0);
		if(equip.size()<count)
			equip[EquipType::AMULET] = o1;
		int tpp;
		for (int i = 0; i < equip.size(); ++i) {
			eq >> tpp;
			if (static_cast<ItemType>(tpp) == ItemType::ARTEFACTEQUIPMENT) {
				delete equip[static_cast<EquipType>(i)];
				equip[static_cast<EquipType>(i)] = new ArtefactEquipment("lol", static_cast<EquipType>(i),5,Params);
			}
			equip[static_cast<EquipType>(i)]->load(eq);
		}
		eq.close();
		std::fstream s1("Hero/potion.txt", std::ios_base::in);
		s1 >> buf;
		count = std::stoi(buf);
		Potion *pot;
		for (int i = 0; i < count; ++i) {
			pot = new Potion;
			pot->load(s1);
			potions.push_back(pot);
		}
		s1.close();
	}

	/*! \brief Move of a hero
	
	4 - one cell right
	8 - one cell up
	2 - one cell down
	6 - one cell left
	*/

	void Hero::move(int i)
	{
		switch (i)
		{
		case 4:
			--pos.x;
			break;
		case 8:
			++pos.y;
			break;
		case 2:
			--pos.y;
			break;
		case 6:
			++pos.x;
			break;
		}
	}

	WeaponParams Hero::getWeaponP()
	{
		return weapon->getFeatures();
	}

	Equipment * Hero::getEquip(EquipType type)
	{
		return equip[type];
	}

	EquipParams Hero::getEquipP(EquipType type)
	{
		return equip[type]->getFeatures();
	}

	Hero::~Hero()
	{
		delete weapon;
		for (int i = 0; i < equip.size(); ++i)
			delete equip[static_cast<EquipType>(i)];
	}

	Enemy::Enemy(string name_, EnemyType type, int x_, int y_,Item *item_, double mh, double exp_): name(name_), experience(exp_),
		params(type,55,7, mh), pos(x_,y_), item(item_)
	{
	}

	/*! \brief Allows you to change enemy params
	\param index - what param do you want to change
	\param p - new value of a param
	\param t - new type of an enemy (ENEMYCOUNT - if you don't want to change)
	*/

	void Enemy::changeParams(ENEMYPARAMETRS index, double p, EnemyType t)
	{
		if (t != ENEMYCOUNT) {
			params.type = t;
		}
		switch (index)
		{
		case ENEMYPARAMETRS::ATTACK:
			params.attack = p;
			break;
		case ENEMYPARAMETRS::CURHEALTH:
			params.CurHealth = p;
			break;
		case ENEMYPARAMETRS::DEFENCE:
			params.defence = p;
			break;
		case ENEMYPARAMETRS::MAXHEALTH:
			params.MaxHealth = p;
			break;
		}
	}

	/*!\brief Returns enemy params
	\return EnemyParams
	*/

	EnemyParams Enemy::getParams()
	{
		params.i = item;
		params.exp = experience;
		return params;
	}

	/*! \brief Generates the damage of an enemy
	
	\return Damage*/

	double Enemy::dealDamage()
	{
		double d=0;
		d += params.attack;
		if (item != nullptr) {
			ItemType type_ = item->iAm();
			if (type_ == ItemType::WEAPON || type_== ItemType::ARTEFACTENCHANTWEAPON || type_ == ItemType::ENCHANTEDWEAPON || type_==ItemType::ARTEFACTWEAPON) {
				Weapon *w = dynamic_cast<Weapon *>(item);
				d += w->generateDamage();
			}
		}
		return d;
	}

	/*!\brief Enemy gets a damage
	
	\param damage - damage that hero gets*/

	void Enemy::getDamage(double damage)
	{
		double d=0;
		Equipment *e;
		if (item != nullptr) {
			if (item->iAm() == ItemType::EQUIPMENT || item->iAm() == ItemType::ARTEFACTEQUIPMENT) {
				e = dynamic_cast<Equipment *>(item);
				d = e->generateDefence();
			}
		}
		damage -= (params.defence+d) *0.8;
		params.CurHealth -= damage;
		if (params.CurHealth == 0) {
			std::cout << name << " is dead!";
		}
	}

	/*!\brief When enemy dies it drops an item
	
	\return Item that enemy held*/

	Item * Enemy::dropItem()
	{
		Item *i = item;
		item = nullptr;
		return i;
	}

	/*!\brief Put the item to the enemy*/

	void Enemy::putItem(Item * i)
	{
		if (item == nullptr)
			delete item;
		item = i;
	}

	/*!\brief Gets item of the enemy*/

	Item * Enemy::getItem()
	{
		return item;
	}
	/*!\brief Saves all information about enemy in the file*/

	void Enemy::save(std::fstream &s)
	{
		s << name << " " << params.attack << " " << params.defence << " " << params.type <<
			" " << params.CurHealth << " " << params.MaxHealth <<" "<<experience<< std::endl;
		s << pos.x << " " << pos.y << std::endl;
		if (item == nullptr)
			s << 0 << std::endl;
		else
			s << 1 << std::endl;
		if (item != nullptr) {
			s << item->iAm() << std::endl;
			item->save(s);
		}
	}

	void Enemy::load(std::fstream & s)
	{

		Weapon *w;
		HeroParams param;
		Equipment *e;
		Potion *po;
		Picklocks *pi;
		ArtefactWeapon *aw;
		ArtefactEquipment *ae;
		string buf;
		s >> buf;
		name = buf;
		s >> buf;
		params.attack = std::stod(buf);
		s >> buf;
		params.defence = std::stod(buf);
		s >> buf;
		params.type = static_cast<EnemyType>(std::stoi(buf));
		s >> buf;
		params.CurHealth = std::stod(buf);
		s >> buf;
		params.MaxHealth = std::stod(buf);
		s >> buf;
		experience = std::stod(buf);
		s >> buf;
		pos.x = std::stoi(buf);
		s >> buf;
		pos.y = std::stoi(buf);
		s >> buf;
		if (std::stoi(buf)) {
			s >> buf;
			ItemType type = static_cast<ItemType>(std::stoi(buf));
			switch (type)
			{
			case ITEMS::WEAPON:
				w = new Weapon;
				w->load(s);
				item = w;
				break;
			case ITEMS::EQUIPMENT:
				e = new Equipment;
				e->load(s);
				item = e;
				break;
			case ITEMS::POTION:
				po = new Potion;
				po->load(s);
				item = po;
				break;
			case ITEMS::PICKLOCK:
				pi = new Picklocks;
				pi->load(s);
				item = pi;
				break;
			case ITEMS::ENCHANTEDWEAPON:
				w = new Weapon;
				w->load(s);
				item = w;
				break;
			case ITEMS::ARTEFACTWEAPON:
				aw = new ArtefactWeapon("A", 1, param);
				aw->load(s);
				item = aw;
				break;
			case ITEMS::ARTEFACTEQUIPMENT:
				ae = new ArtefactEquipment("A", EquipType::AMULET, 1, param);
				ae->load(s);
				item = ae;
				break;
			case ITEMS::ARTEFACTENCHANTWEAPON:
				aw = new ArtefactWeapon("A", 1, param);
				aw->load(s);
				item = aw;
				break;
			default:
				break;
			}
		}
	}

	std::ostream & operator<<(std::ostream &s, const EnemyParams &p)
	{
		EnemyType t = p.type;
		s << "Attack - " << p.attack << ", defence - " << p.defence << ", MaxHealth - " << p.MaxHealth <<
			", exp - " << p.exp << " ";
		switch (t)
		{
		case ITEMS::HUMANOID:
			s << "Humanoid ";
			break;
		case ITEMS::INSECT:
			s << "Insect ";
			break;
		case ITEMS::ANIMAL:
			s << "Animal ";
			break;
		case ITEMS::DEMON:
			s << "Demon ";
			break;
		case ITEMS::ICY:
			s << "Icy ";
			break;
		case ITEMS::UNDEAD:
			s << "Undead ";
			break;
		}
		s << std::endl;
		ItemType it;
		if (p.i != nullptr) {
			it = p.i->iAm();
			switch (it)
			{
			case ITEMS::WEAPON:
				s << "Weapon" << std::endl;
				break;
			case ITEMS::EQUIPMENT:
				s << "Equipment" << std::endl;
				break;
			case ITEMS::POTION:
				s << "Potion" << std::endl;
				break;
			case ITEMS::PICKLOCK:
				s << "Picklocks" << std::endl;
				break;
			case ITEMS::ENCHANTEDWEAPON:
				s << "Enchanted weapon" << std::endl;
				break;
			case ITEMS::ARTEFACTWEAPON:
				s << "Artefact weapon" << std::endl;
				break;
			case ITEMS::ARTEFACTEQUIPMENT:
				s << "Artefact equipment" << std::endl;
				break;
			case ITEMS::ARTEFACTENCHANTWEAPON:
				s << "Artefact enchanted weapon" << std::endl;
				break;
			default:
				break;
			}
		}
		s << std::endl;
		return s;
	}

}
