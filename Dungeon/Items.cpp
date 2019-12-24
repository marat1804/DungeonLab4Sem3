
#include "Items.h"
namespace ITEMS {

	/*! This method returns type of every item to define it correctly
	\return Type of Item
	*/
	ItemType Item::iAm()
	{
		return ItemType::ITEM;
	}
	/*! This method returns the name of item
	\return Name of item in std::string
	*/
	string Item::getName()
	{
		return name;
	}
	/*!\brief Sets a new to the item*/
	void Item::setName(string & s)
	{
		name = s;
	}
	/*! This method is savig all necessary information of item in file
	*/
	void Item::save(std::fstream&)
	{
	}
	/*!\brief Loads all info from file*/
	void Item::load(std::fstream &)
	{
	}

	/*! Saves all info about weapon
	\param s - file stream where to save everything
	*/
	void Weapon::save(std::fstream & s)
	{
		s << iAm() << " ";
		s << getName() << " ";
		s << std::to_string(damage)<<" ";
		if (enchantments == nullptr)
			s << 0<<" ";
		else
			s << 1<<" ";
		s << 0 << std::endl;
		if (enchantments != nullptr)
			enchantments->save(s);
		s << std::endl;
	}

	void Weapon::load(std::fstream &s)
	{
		string buf;
		string type, mod;
		s >> buf;
		setName(name);
		s >> buf;
		damage = std::stod(buf);
		s >> buf;
		if (std::stoi(buf) == 0)
			enchantments = nullptr;
		else {
			enchantments = new Enchantments;
			s >> buf;
			for (int i = 0; i < EnemyType::ENEMYCOUNT; ++i) {
				s >> type >> mod;
				enchantments->changeFeatures(static_cast<EnemyType>(i), std::stod(mod));
			}
		}
	}
	/*!Show if the weapon is enchanted
	\return true if the weapon is enchanted
	\return false if the weapon is not enchanted
	*/
	bool Weapon::isEnchanted()
	{
		if (enchantments == nullptr) {
			return false;
		}
		else {
			return true;
		}
	}

	ItemType Weapon::iAm()
	{
		if (isEnchanted()) {
			return ItemType::ENCHANTEDWEAPON;
		}
		else
			return ItemType::WEAPON;
	}
	/*! This method returns pure damage 
	This class is to get damage in childcare classes
	\return damage in double
	*/
	double Weapon::getDamage()
	{
		return damage;
	}

	/*! This method sets damage
	This class is to set damage from childcare classes
	\param d damage that is going to be set
	*/
	void Weapon::setDamage(double d)
	{
		if (damage != 0) {
			damage = d;
		}
	}
	/*! Allows to get the enchantments
	\return multiplier as std::map 
	*/

	Enchantments * Weapon::getEnchants()
	{
		return enchantments;
	}

	/*! Returns stamina for artefact weapons*/

	int Weapon::getStamina()
	{
		return 0;
	}
	/*! Returns agility for artefact weapons*/

	int Weapon::getAgility()
	{
		return 0;
	}
	/*! Returns strength for artefact weapons*/
	int Weapon::getStrength()
	{
		return 0;
	}


	Weapon::Weapon(string name1, double damage1, map<EnemyType, double> map, double Enchanted) : Item(name1), damage(damage1)
	{
		if (Enchanted) {
			enchantments = new Enchantments;
			enchantments->setFeatures(map);
		}
	}
	/*! Generating damage of a weapon
	\return damage of a weapon
	*/
	double Weapon::generateDamage()
	{
		return damage;
	}
	/*! Return all parameters of weapons
	\return WeaponParams
	*/

	WeaponParams Weapon::getFeatures()
	{
		WeaponParams p;
		map<EnemyType, double> map;
		p.damage = damage;
		if (enchantments != nullptr) {
			map = (enchantments->getFeatures());
			p.multiplier = map;
		}
		p.isArtifact = false;
		return p;
	}

	/*! \brief Allows you to set a multiplier for enchanted weapon
	*/

	void Weapon::setMultiplier(EnemyType type, double multiplier)
	{
		if (type != EnemyType::ENEMYCOUNT) {
			if (enchantments == nullptr) {
				enchantments = new Enchantments;
			}
			enchantments->changeFeatures(type, multiplier);
		}
	}

	/*!Allows to change weapon features
	\param damage_ - what damage to set(0-if you don't want to change)
	\param type - for what enemy type to change multiplier
	\param multiplier - multiplier
	*/

	void Weapon::changeFeatures(double damage_, EnemyType type, double multiplier)
	{
		if (damage_ != 0) {
			damage = damage_;
		}
		if (type != EnemyType::ENEMYCOUNT) {
			if (enchantments == nullptr) {
				enchantments = new Enchantments;
			}
			enchantments->changeFeatures(type, multiplier);
		}
	}

	Weapon::~Weapon()
	{
		delete enchantments;
	}

	Enchantments::Enchantments( double h, double in, double an, double de, double icy, double un)
	{
		multiplier[EnemyType::HUMANOID] = h;
		multiplier[EnemyType::INSECT] = in;
		multiplier[EnemyType::ANIMAL] = an;
		multiplier[EnemyType::DEMON] = de;
		multiplier[EnemyType::ICY] = icy;
		multiplier[EnemyType::UNDEAD] = un;
	}

	/*!Save all information in weapon file
	\param s - weapon file stream
	*/

	void Enchantments::save(std::fstream &s)
	{
		/*string path;
		switch (i)
		{
		case 0:
			path = "Hero/weapon.txt";	
		default:
			break;
		}*/
		/*std::fstream s(path, std::ios_base::app);*/
		for (int i = 0; i < multiplier.size(); ++i) {
			s << i << " " << multiplier[static_cast<EnemyType>(i)]<<std::endl;
		}
		s << std::endl;
	}

	/*! Returns a multiplier for a chosen type
	\param type - Enemy type for whom we want to get a multiplier
	\return multiplier for a chosen type of enemy
	*/

	double Enchantments::getMultiplier(EnemyType type)
	{
		return multiplier[type];
	}

	/*! Returns all multipliers*/

	map<EnemyType, double> Enchantments::getFeatures()
	{
		return multiplier;
	}
	/*! Helps you to set features
	\param map - multiplier
	*/

	void Enchantments::setFeatures(map<EnemyType, double> map)
	{
		for (int i = 0; i < EnemyType::ENEMYCOUNT; ++i) {
			multiplier[static_cast<EnemyType>(i)] = map[static_cast<EnemyType>(i)];
		}
	}

	/*!Helps to change multiplier of a specific type of enemy
	\param type - Enemy type
	\param multiplier_ - what multiplier is gonna to be for such type of enemy*/

	void Enchantments::changeFeatures(EnemyType type, double multiplier_) {
		multiplier[type] = multiplier_;
	}

	/*! Saves all information in file
	\param s - weapon or equip file stream*/
	
	void Artefact::save(std::fstream &s)
	{

	}

	/*! Returns how much artefact modificates stamina*/

	int Artefact::getStamina()
	{
		return mod.stamina;
	}

	/*! Returns how much artefact modificates strength*/


	int Artefact::getStrength()
	{
		return mod.strength;
	}

	/*! Returns how much artefact modificates agility*/

	int Artefact::getAgility()
	{
		return mod.agility;
	}
	/*! Returns how much artefact modificates max health*/

	double Artefact::getMaxHealth()
	{
		return mod.MaxHealth;
	}

	/*! This method helps to changes params of artefact item
	\param type - what param to change
	\param value - how much this artefact will change this hero param
	*/

	void Artefact::changeParams(ArtefactParams type, double value)
	{
		switch (type)
		{
		case STAMINA:
			mod.stamina = value;
			break;
		case STRENGTH:
			mod.strength = value;
			break;
		case MAXHEALTH:
			mod.MaxHealth = value;
			break;
		case AGILITY:
			mod.agility = value;
			break;
		}
	}

	/*! Saves all information about Artifact Weapon
	*/

	void ArtefactWeapon::save(std::fstream & s)
	{
		s << iAm() << " ";
		s << getName() << " ";
		s << std::to_string(getDamage()) << " ";
		if (!isEnchanted())
			s << 0 << " ";
		else
			s << 1 << " ";
		s << 1 << std::endl;
		Enchantments *e = getEnchants();
		/*s.close();*/
		if (e != nullptr)
			e->save(s);
		s << STAMINA << " " << getStamina() << std::endl;
		s << STRENGTH << " " << getStrength() << std::endl;
		s << MAXHEALTH << " " << getMaxHealth() << std::endl;
		s << AGILITY << " " << getAgility() << std::endl;
	}

	ItemType ArtefactWeapon::iAm()
	{
		if (isEnchanted()) {
			return ItemType::ARTEFACTENCHANTWEAPON;
		}
		else {
			return ItemType::ARTEFACTWEAPON;
		}
	}

	void ArtefactWeapon::load(std::fstream &s)
	{
		string buf;
		string type, mod;
		int ench, art;
		s >> buf;
		setName(name);
		s >> buf;
		setDamage(std::stod(buf));
		s >> buf;
		ench = std::stoi(buf);
		s >> buf;
		if (ench) {
			for (int i = 0; i < EnemyType::ENEMYCOUNT; ++i) {
				s >> type >> mod;
				setMultiplier(static_cast<EnemyType>(i), std::stod(mod));
			}
		}
		for (int i = 0; i < ArtefactParams::ARTEFACTCOUNT; ++i) {
			s >> type >> mod;
			changeParams(static_cast<ArtefactParams>(i), std::stoi(mod));
		}
	}

	/*!Returns boost for stamina of weapon
	\return boost for stamina
	*/

	int ArtefactWeapon::getStamina()
	{
		return Artefact::getStamina();
	}

	/*!Returns boost for agility of weapon
		\return boost for agility
	*/

	int ArtefactWeapon::getAgility()
	{
		return Artefact::getAgility();
	}

	/*!Returns boost for strength of weapon
	\return boost for strength
	*/

	int ArtefactWeapon::getStrength()
	{
		return Artefact::getStrength();
	}

	/*! Generetes damage of weapon
	\return Damage for weapon (additional 5 damage for each strength point)
	*/

	double ArtefactWeapon::generateDamage()
	{
		return getDamage() + getStrength() * 5;
	}

	/*! Allows you to know all the characteristics of the weapon
	\return Everything in WeaponParams
	*/

	WeaponParams ArtefactWeapon::getFeatures()
	{
		WeaponParams p;
		p.damage = getDamage();
		if (isEnchanted()) {
			p.multiplier = getEnchants()->getFeatures();
		}
		p.isArtifact = true;
		p.params.agility = getAgility();
		p.params.stamina = getStamina();
		p.params.strength = getStrength();
		p.params.MaxHealth = getMaxHealth();
		return p;
	}

	/*! Allows you to change params of artifact weapon
	\param damage_ - what damage to set (0 - if you don't want to change)
	\param type_e - Enemy type for enchanted weapon
	\param multiplier - Multiplier for enchanted weapon
	\param type_a - What booster of artifact weapon to change 
	\param value - value for booster
	*/

	void ArtefactWeapon::changeFeatures(double damage_, ArtefactParams type_a , double value , EnemyType type_e , double multiplier)
	{
		setDamage(damage_);
		setMultiplier(type_e, multiplier);
		if (type_a != ARTEFACTCOUNT) {
			Artefact::changeParams(type_a, value);
		}
	}

	/*! \brief Allow to get defence in Artifact Equipment

	\return defence of an equipment
	*/

	double Equipment::getDefence()
	{
		return defence;
	}

	/*! \brief Allows you to set a type to an equipment

	\param e - type of equipment
	*/

	void Equipment::setType(EquipType e) 
	{
		if (e != EquipType::EQUIPCOUNT) {
			type = e;
		}
	}

	/*! \brief Allow to set defence in Artifact Equipment

	\param d - defence of an equipment
	*/

	void Equipment::setDefence(double d)
	{
		if (d != 0) {
			defence = d;
		}
	}

	/*! \brief Saves all information about equipment in file
	
	\param s - file stream
	*/

	void Equipment::save(std::fstream &s)
	{
		s << iAm()<<" ";
		s << getName() << " ";
		s << type << " " << std::to_string(defence) << " " << 0<<std::endl;

	}

	void Equipment::load(std::fstream &s)
	{
		string buf;
		s >> buf;
		setName(name);
		s >> buf;
		type = static_cast<EquipType>(std::stoi(buf));
		s >> buf;
		defence = std::stod(buf);
		s >> buf;
	}

	ItemType Equipment::iAm()
	{
		return ItemType::EQUIPMENT;
	}

	/*! \brief Returns additional stamina for artifact equipment

	\return Additional stamina of artifact equipment
	*/

	int Equipment::getStamina()
	{
		return 0;
	}

	/*! \brief Returns additional agility for artifact equipment

	\return Additional agility of artifact equipment
	*/

	int Equipment::getAgility()
	{
		return 0;
	}

	/*! \brief Returns additional strength for artifact equipment

	\return Additional strength of artifact equipment
	*/

	int Equipment::getStrength()
	{
		return 0;
	}

	/*! Gives you a type of an equipment

	\return Type of an equipment
	*/

	EquipType Equipment::getType()
	{
		return type;
	}

	/*! \brief Returns all features of equipment

	\return EquipParams of equipment
	*/

	EquipParams Equipment::getFeatures()
	{
		EquipParams p;
		p.def = defence;
		p.type = type;
		p.isArtifact = false;
		return p;
	}

	/*!\brief Changes the params of an equipment
	
	\param defence_ - new defence of equipment (0 - if don't want to change)
	\param t - new type of equipment (EQUIPCOUNT - if don't want to change)
	*/

	void Equipment::changeFeatures(double defence_, EquipType t)
	{
		if (defence_ != 0)
			defence = defence_;
		if (t != EQUIPCOUNT)
			type = t;
	}

	/*! \brief Generates the defence of equipment
	
	\return defence of equipment
	*/

	double Equipment::generateDefence()
	{
		return defence;
	}

	/*! \brief Saves all information about Artefact Equipment in file
	
	\param s - file stream
	*/

	void ArtefactEquipment::save(std::fstream & s)
	{
		s << iAm() << " ";
		s << Item::getName() << " ";
		s << getType() << " " << std::to_string(getDefence()) << " " << 1 << std::endl;
		s << STAMINA << " " << getStamina() << std::endl;
		s << STRENGTH << " " << getStrength() << std::endl;
		s << MAXHEALTH << " " << getMaxHealth() << std::endl;
		s << AGILITY << " " << getAgility() << std::endl;
	}

	void ArtefactEquipment::load(std::fstream & s)
	{
		string buf;
		string type, mod;
		s >> buf;
		setName(buf);
		s >> buf;
		setType( static_cast<EquipType>(std::stoi(buf)));
		s >> buf;
		setDefence( std::stod(buf));
		s >> buf;
		for (int i = 0; i < ArtefactParams::ARTEFACTCOUNT; ++i) {
			s >> type >> mod;
			changeParams(static_cast<ArtefactParams>(i), std::stoi(mod));
		}
	}

	ItemType ArtefactEquipment::iAm()
	{
		return ItemType::ARTEFACTEQUIPMENT;
	}

	/*! \brief Returns additional stamina for artifact equipment

	\return Additional stamina of artifact equipment
	*/

	int ArtefactEquipment::getStamina()
	{
		return Artefact::getStamina();
	}

	/*! \brief Returns additional strength for artifact equipment

	\return Additional strength of artifact equipment
	*/

	int ArtefactEquipment::getStrength()
	{
		return Artefact::getStrength();
	}

	/*! \brief Returns additional agility for artifact equipment

	\return Additional agility of artifact equipment
	*/

	int ArtefactEquipment::getAgility()
	{
		return Artefact::getAgility();
	}

	/*! \brief Generate the defence of equipment

	\return Defence of equipment (Additional 2 defence for each stamina point)
	*/

	double ArtefactEquipment::generateDefence()
	{
		return (getDefence()  + getStamina() * 2) ;
	}

	/*! \brief Returns all params of Artifact Equipment*/

	EquipParams ArtefactEquipment::getFeatures()
	{
		EquipParams p;
		p.def = getDefence();
		p.type = getType();
		p.isArtifact = true;
		p.params.agility = getAgility();
		p.params.stamina = getStamina();
		p.params.strength = getStrength();
		p.params.MaxHealth = getMaxHealth();
		return p;
	}

	/*! \brief Allows you to change all features
	\param def - new defence of equipment (0 - if don't want to change)
	\param type_ - new type of equipment(EQUIPCOUNT - if don't want to change)
	\param type_a - what HeroParam to change(ARTEFACTCOUNT - if don't want to change)
	\param value - new value for HeroParam in type_a (0 - if don't want to change)
	*/

	void ArtefactEquipment::changeFeatures(double def, EquipType type_, ArtefactParams type_a, double value)
	{
		setDefence(def);
		setType(type_);
		if (type_a != ARTEFACTCOUNT) {
			Artefact::changeParams(type_a, value);
		}
	}

	ItemType Picklocks::iAm()
	{
		return PICKLOCK;
	}

	void Picklocks::save(std::fstream & s)
	{
		s<<iAm() << " " << getName() << " " << std::to_string(amount) << std::endl;
	}

	void Picklocks::load(std::fstream & s)
	{
		string buf;
		s >> buf;
		setName(name);
		s >> buf;
		amount = std::stoi(buf);
	}

	/*!\brief Returns amount of picklocks in lock pin bundle
	\return Amount of picklocks
	*/

	int Picklocks::getCount()
	{
		return amount;
	}

	/*!\brief Changes the amount of picklocks*/
	void Picklocks::changeParam(int i)
	{
		if (i > 0)
			amount = i;
	}

	/*! \brief Saves everything about potion in the file
	\param s - filestream
	*/

	void Potion::save(std::fstream &s)
	{
		s<<iAm() << " " << getName() << " " << features.agility<< " "<<features.stamina<<
			" "<< features.strength<<" "<<features.MaxHealth<<" "<<duration<<std::endl;
	}

	void Potion::load(std::fstream & s)
	{
		string buf;
		s >> buf;
		setName(name);
		s >> buf;
		features.agility = std::stoi(buf);
		s >> buf;
		features.stamina = std::stoi(buf);
		s >> buf;
		features.strength = std::stoi(buf);
		s >> buf;
		features.MaxHealth = std::stoi(buf);
		s >> buf;
		duration = std::stoi(buf);
	}

	ItemType Potion::iAm()
	{
		return ItemType::POTION;
	}

	Potion::Potion():Item ("Potion")
	{
		duration = 0;

	}

	/*! \brief Return duration of an potion

	\return Duration of potion
	*/

	int Potion::getDuration()
	{
		return duration;
	}

	/*!\brief Returns modificators of potion
	\return Modeficators of potion
	*/

	HeroParams Potion::getParams()
	{
		return features;
	}

	/*!\breif Returns all features of potion*/

	PotionParams Potion::getFeatures()
	{
		PotionParams p;
		p.params = features;
		p.duration = duration;
		return p;
	}

	/*!\brief Sets a new duration of a potion
	\param dur - new duration of potion
	*/

	void Potion::setDuration(int dur)
	{
		duration = dur;
	}

	/*!\brief Allows you to change the potion params
	\param duration_ - new duration of potion(0 - if you don't want to change)
	\param a - what do you want to change (ARTEFACTCOUNT - if don't want to change)
	\param value - value for changing parameter
	*/

	void Potion::changeFeatures(int duration_, ArtefactParams a, double value)
	{
		if (duration_ != 0)
			duration = duration_;
		if (a != ARTEFACTCOUNT) {
			switch (a)
			{
			case STAMINA:
				features.stamina = value;
				break;
			case STRENGTH:
				features.strength = value;
				break;
			case MAXHEALTH:
				features.MaxHealth = value;
				break;
			case AGILITY:
				features.agility = value;
				break;
			}
		}
	}

	/*!\brief Return everything of a Chest 
	\return Chest Params
	*/

	ChestParams Chest::getParams()
	{
		ChestParams ch(lockLevel, pos, item);
		return ch;
	}

	/*!\brief Allows to change the params of chest
	\param lock - new level of lock (0 - if don't want to change)
	\param i - new item to the chest (nullptr - if don't want to change)
	*/

	void Chest::changeParams(int lock, Item *i, int x, int y)
	{
		if (lock != 0) {
			lockLevel = lock;
		}
		if (i != nullptr) {
			item = i;
		}
		if (x != -1 && y != -1) {
			pos.x = x;
			pos.y = y;
		}
	}

	/*! \brief Puts a new item in the chest
	\param i - new Item
	*/

	void Chest::putItem(Item *i)
	{
		if (item != nullptr)
			delete item;
		item = i;
	}

	/*!\brief Saves all information about chest + item in the file*/
	void Chest::save(std::fstream &s)
	{
		s << lockLevel << " " << pos.x << " " << pos.y << std::endl;
		item->save(s);
	}
	/*!\brief Loads all information about chest from the file*/
	void Chest::load(std::fstream & s)
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
		lockLevel = std::stoi(buf);
		s >> buf;
		pos.x = std::stoi(buf);
		s >> buf;
		pos.y = std::stoi(buf);
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
	Item * Chest::open(double hackProb)
	{
		Item *i;
		if ((hackProb - lockLevel * 0.1) > 0.3) {
			i= item;
			item = nullptr;
			return i;
		}
		return nullptr;
	}
	/*!
	Overload operator << to print all the parametrs easily
	*/
	std::ostream & operator<<(std::ostream &s, const HeroParams &p)
	{
		s << "Agility - " << p.agility << ", stamina - " << p.stamina << ", strength - " << p.strength <<
			", maxHealth - " << p.MaxHealth <<", CurHealth - "<<p.CurHealth<< std::endl;
		return s;
	}

	/*!
	Overload operator << to print all the parametrs easily
	*/

	std::ostream & operator<<(std::ostream &s, const WeaponParams &p)
	{
		s << "Damage - " << p.damage << "\n";
		if (p.multiplier.size() != 0) {
			s << "Multiplier: \n";
			for (int i = 0; i < p.multiplier.size(); ++i) {
				switch (i)
				{
				case EnemyType::ANIMAL:
					s << "Animal - ";
					break;
				case EnemyType::DEMON:
					s << "Demon - ";
					break;
				case EnemyType::HUMANOID:
					s << "Humanoid - ";
					break;
				case EnemyType::ICY:
					s << "Icy - ";
					break;
				case EnemyType::INSECT:
					s << "Insect - ";
					break;
				case EnemyType::UNDEAD:
					s << "Undead - ";
					break;
				}
				s << p.multiplier.at(static_cast<EnemyType>(i))<<" ";
			}
		}
		s << "\n";
		if (p.isArtifact) {
			s << "Additional parameters: ";
			s << "Agility - " << p.params.agility;
			s << " Stamina - " << p.params.stamina;
			s << " Strength - " << p.params.strength;
			s << " MaxHealth - " << p.params.MaxHealth;
		}
		s << std::endl;
		return s;
	}

	/*!
	Overload operator << to print all the parametrs easily
	*/


	std::ostream & operator<<(std::ostream &s, const EquipParams &p)
	{
		s << "Type - " << p.type << "\n";
		s << "Defence - "<< p.def<<"\n";
		if (p.isArtifact) {
			s << "Additional parameters: ";
			s << "Agility - " << p.params.agility;
			s << " Stamina - " << p.params.stamina;
			s << " Strength - " << p.params.strength;
			s << " MaxHealth - " << p.params.MaxHealth;
		}
		s << std::endl;
		return s;
	}

	/*!
		Overload operator << to print all the parametrs easily
		*/

	std::ostream & operator<<(std::ostream &s, const PotionParams &p)
	{
		s << "Duration - " << p.duration << ", Additional: "
			<< "agility - " << p.params.agility <<
			" stamina - " << p.params.stamina <<
			" strength - " << p.params.strength <<
			" maxhealth - " << p.params.MaxHealth;
		return s;
	}

	/*!
	Overload operator << to print all the parametrs easily
	*/
	std::ostream & operator<<(std::ostream &s, const ChestParams &p)
	{
		Weapon *w;
		Equipment *e;
		Potion *po;
		Picklocks *pi;
		s << "Locklevel - " << p.locklevel << std::endl;
		s << "Position - " << p.pos.x << " " << p.pos.y << std::endl;
		if (p.item != nullptr) {
			ItemType i = p.item->iAm();
			switch (i)
			{
			case ITEMS::WEAPON:
				s << "Weapon - ";
				w = dynamic_cast<Weapon *>(p.item);
				s << w->getFeatures()<<std::endl;
				break;
			case ITEMS::EQUIPMENT:
				s << "Equipment - ";
				e = dynamic_cast<Equipment *>(p.item);
				s << e->getFeatures()<<std::endl;
				break;
			case ITEMS::POTION:
				s << "Potion - ";
				po = dynamic_cast<Potion *>(p.item);
				s << po->getFeatures()<<std::endl;
				break;
			case ITEMS::PICKLOCK:
				s << "Pickloks - ";
				pi = dynamic_cast<Picklocks*>(p.item);
				s << "count - " << pi->getCount()<<std::endl;
				break;
			}
		}
		return s;
	}

}