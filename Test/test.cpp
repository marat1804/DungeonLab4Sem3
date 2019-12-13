#include "pch.h"
#include <tchar.h>
#include "..//Dungeon/Cell.h"


TEST(TemplateTest, Init) {
	Map<std::string, int> map1;
	std::string s1 = "1", s2 = "s2";
	int i1 = 1, i2 = 2;
	map1.add(s1, i1);
	map1.add(s2, i2);
	Map<std::string, int> map2(map1);
	ASSERT_EQ(map2[s1], 1);
	ASSERT_EQ(map2[s2], 2);
}

TEST(TemplateTest, Add) {
	Map<std::string, int> map;
	std::string s3 = "Test3";
	std::string s1 = "Test1", s2 = "Test2";
	int i1 = 1, i2 = 2, i3 = 3;
	map.add(s1, i1);
	map.add(s2, i2);
	ASSERT_EQ(map[s1], 1);
	ASSERT_EQ(map[s2], 2);
}

TEST(TemplateTest, AddException) {
	Map<std::string, int> map;
	std::string s3 = "Test3";
	ASSERT_THROW(map[s3], std::exception);
}

TEST(TemplateTest, EqOperator) {
	Map<std::string, int> map1, map2;
	std::string s1 = "1", s2 = "s2";
	int i1 = 1, i2 = 2;
	map1.add(s1, i1);
	map2.add(s2, i2);
	ASSERT_EQ(map1[s1], 1);
	ASSERT_EQ(map2[s2], 2);
	map1 = map2;
	ASSERT_THROW(map1[s1], std::exception);
	ASSERT_EQ(map1[s2], 2);
}

TEST(TemplateTest, Iterator) {
	Map<int, int> map;
	Map<int, int>::Iterator it=map.begin();
	int i1 = 1, i2 = 2, i3 = 3;
	map.add(i1,i1);
	map.add(i2, i2);
	map.add(i3, i3);
	int i = 1;
	for (it = map.begin(); it != map.end(); ++it) {
		ASSERT_EQ((*it).second, i);
		++i;
	}

}


TEST(WeaponTest, Init) {
	ITEMS::Weapon w;
	WeaponParams p = w.getFeatures();
	ASSERT_EQ(p.damage, 125);
	ASSERT_EQ(p.multiplier.size(), 0);
}

TEST(WeaponTest, ChangeFeatures) {
	ITEMS::Weapon w;
	WeaponParams p = w.getFeatures();
	w.changeFeatures(0, EnemyType::ANIMAL, 2.5);
	p = w.getFeatures();
	ASSERT_EQ(p.damage, 125);
	ASSERT_EQ(p.multiplier.size(), 6);
	ASSERT_EQ(p.multiplier[EnemyType::ANIMAL], 2.5);
}

TEST(ArtifactWeaponTest, Init) {
	HeroParams mod;
	mod.agility = 1;
	mod.stamina = 2;
	mod.strength = 3;
	mod.MaxHealth = 15;
	std::string s = "Art";
	ITEMS::ArtefactWeapon w(s, 140.0, mod);
	WeaponParams p = w.getFeatures();
	ASSERT_EQ(p.damage, 140.0);
	ASSERT_EQ(p.params.agility, 1);
	ASSERT_EQ(p.params.stamina, 2);
}

TEST(ArtifactWeaponTest, ChangeFeatures) {
	HeroParams mod;
	mod.agility = 1;
	mod.stamina = 2;
	mod.strength = 3;
	mod.MaxHealth = 15;
	std::string s = "Art";
	ITEMS::ArtefactWeapon w(s, 140.0, mod);
	w.changeFeatures(160.0, ArtefactParams::AGILITY, 45);
	WeaponParams p = w.getFeatures();
	ASSERT_EQ(p.damage, 160.0);
	ASSERT_EQ(p.params.agility, 45);
	ASSERT_EQ(w.isEnchanted(), false);
	ASSERT_EQ(w.getStamina(), 2);
}

TEST(EquipmentTest, Init) {
	ITEMS::Equipment e;
	EquipParams p = e.getFeatures();
	ASSERT_EQ(p.def, 5);
	ASSERT_EQ(p.isArtifact, false);
	ASSERT_EQ(p.type, EquipType::CHESTPLATE);
}

TEST(EquipmentTest, ChangeFeatures) {
	std::string d = "WOW HElmeT";
	ITEMS::Equipment e(EquipType::HELMET, d, 15);
	EquipParams p = e.getFeatures();
	ASSERT_EQ(p.type, EquipType::HELMET);
	ASSERT_EQ(p.def, 15);
}

TEST(ArtefactEquipmentTest, Init) {
	HeroParams mod;
	mod.agility = 1;
	mod.stamina = 2;
	mod.strength = 3;
	mod.MaxHealth = 15;
	std::string s = "Art";
	ITEMS::ArtefactEquipment e(s,EquipType::AMULET, 45,mod);
	EquipParams p = e.getFeatures();
	ASSERT_EQ(p.type, EquipType::AMULET);
	ASSERT_EQ(p.def, 45);
	ASSERT_EQ(p.params.agility, e.getAgility());
}

TEST(ArtefactEquipmentTest, ChangeFeatures) {
	HeroParams mod;
	mod.agility = 1;
	mod.stamina = 2;
	mod.strength = 3;
	mod.MaxHealth = 15;
	std::string s = "Art";
	ITEMS::ArtefactEquipment e(s, EquipType::AMULET, 45, mod);
	e.changeFeatures(14, EquipType::PANTS, ArtefactParams::MAXHEALTH, 400);
	EquipParams p = e.getFeatures();
	ASSERT_EQ(p.def, 14);
	ASSERT_EQ(p.isArtifact, true);
	ASSERT_EQ(p.type, EquipType::PANTS);
	ASSERT_EQ(p.params.MaxHealth, 400);
	Equipment * pe = &e;

	ASSERT_EQ(pe->iAm(), ItemType::ARTEFACTEQUIPMENT);
}

TEST(PicklocksTest, Init) {
	std::string s = "SuperPicklocks";
	Picklocks p(s, 15);
	ASSERT_EQ(p.getCount(), 15);
	ASSERT_EQ(p.getName(), s);
}

TEST(PotionTest, Init) {
	HeroParams mod;
	mod.agility = 1;
	mod.stamina = 2;
	mod.strength = 3;
	mod.MaxHealth = 15;
	std::string s = "Potion";
	Potion p(s, 45, mod);
	PotionParams param = p.getFeatures();
	ASSERT_EQ(param.duration,  45);
	ASSERT_EQ(param.params.agility, 1);
}

TEST(PotionTest, ChangeParams) {
	HeroParams mod;
	mod.agility = 1;
	mod.stamina = 2;
	mod.strength = 3;
	mod.MaxHealth = 15;
	std::string s = "Potion";
	Potion p(s, 45, mod);
	p.changeFeatures(75);
	p.changeFeatures(0, ArtefactParams::STAMINA, 44);
	PotionParams param = p.getFeatures();
	ASSERT_EQ(param.duration, 75);
	ASSERT_EQ(param.params.stamina, 44);
}

TEST(ChestTest, Init) {
	HeroParams mod;
	mod.agility = 1;
	mod.stamina = 2;
	mod.strength = 3;
	mod.MaxHealth = 15;
	std::string s = "Art";
	ITEMS::ArtefactWeapon *w=new ArtefactWeapon(s, 140.0, mod);
	Chest ch(w,1,1 ,5);
	ChestParams p = ch.getParams();
	ASSERT_EQ(p.locklevel, 5);
	ASSERT_EQ(p.item->iAm(), ItemType::ARTEFACTWEAPON);
}

TEST(ChestTest, PutItem) {
	HeroParams mod;
	mod.agility = 1;
	mod.stamina = 2;
	mod.strength = 3;
	mod.MaxHealth = 15;
	std::string s = "Art";
	ITEMS::ArtefactWeapon *w = new ArtefactWeapon(s, 140.0, mod);
	Chest ch(w,1,1, 5);
	ITEMS::Equipment *e = new Equipment;
	ch.putItem(e);
	ChestParams p = ch.getParams();
	ASSERT_EQ(p.locklevel, 5);
	ASSERT_EQ(p.item->iAm(), ItemType::EQUIPMENT);
}

TEST(EffectTest, Init) {
	CHARACTERS::Effect ef;
	HeroParams p = ef.getBoost();
	ASSERT_EQ(p.agility, 0);

	HeroParams p1(2, 2, 2, 2);
	CHARACTERS::Effect ef1(p1, 15);
	ASSERT_EQ(ef1.getBoost().agility, 2);
}

TEST(EffectTest, Wipe) {
	HeroParams p(15, 15, 15, 15);
	CHARACTERS::Effect ef(p, 10);
	ASSERT_EQ(ef.getBoost().agility, 15);
	ef.wipe();
	ASSERT_EQ(ef.getBoost().agility, 0);
}

TEST(EffectTest, AddBoostAndTimeOut) {
	HeroParams p(15, 15, 15, 15);
	CHARACTERS::Effect ef(p, 10);
	ASSERT_EQ(ef.getBoost().agility, 15);
	for (int i = 0; i < 11; ++i) {
		ef.timer();
	}
	ASSERT_EQ(ef.getBoost().agility, 0);
}

TEST(HeroTest, Init) {
	CHARACTERS::Hero h;
	HeroParams p = h.getParams();
	ASSERT_EQ(p.agility, 5);
}

TEST(HeroTest, ChangePos) {
	CHARACTERS::Hero h;
	h.setPos(1, 5);
	ASSERT_EQ(h.getPos().x, 1);
	ASSERT_EQ(h.getPos().y, 5);
}

TEST(HeroTest, AttackBonus) {
	Hero h;
	double d = h.getAttackBonus();
	ASSERT_EQ(d, 25);
}

TEST(HeroTest,DefencekBonus) {
	Hero h;
	double d = h.getDefenceBonus();
	ASSERT_EQ(d, 12.5);
}

TEST(HeroTest, GenerateDamage) {
	Hero h;
	double d = h.generateDamage();
	ASSERT_EQ(150, d);
}

TEST(HeroTest, ChangeParams) {
	Hero h;
	h.changeParams(HeroParamIndex::STAMINA, 15);
	HeroParams p = h.getParams();
	ASSERT_EQ(p.stamina, 15);
}

TEST(HeroTest, TakeItem) {
	Weapon *w = new Weapon("Super", 500);
	Hero h;
	Item *i;
	i = h.takeItem(w);
	ASSERT_EQ(i->iAm(), ItemType::WEAPON);
	ASSERT_EQ(h.generateDamage(), 525);
	delete i;
}


TEST(HeroTest, Move) {
	Hero h;
	h.setPos(1, 2);
	h.move(8);
	ASSERT_EQ(h.getPos().y, 3);
	h.move(6);
	ASSERT_EQ(h.getPos().x, 2);
}

TEST(EnemyTest, Init) {
	std::string s1 = "Eminem";
	Enemy e(s1,EnemyType::HUMANOID, 15,15, nullptr, 260,180);
	EnemyParams p = e.getParams();
	ASSERT_EQ(p.attack,55 );
	ASSERT_EQ(p.exp, 180);
	ASSERT_EQ(p.type, EnemyType::HUMANOID);
}

TEST(EnemyTest, ChangeParams) {
	std::string s1 = "Eminem";
	Enemy e(s1, EnemyType::HUMANOID, 15, 15, nullptr, 260, 180);
	e.changeParams(ENEMYPARAMETRS::ATTACK, 800, EnemyType::DEMON);
	EnemyParams p = e.getParams();
	ASSERT_EQ(p.attack, 800);
	ASSERT_EQ(p.type, EnemyType::DEMON);

}

TEST(EnemyTest, DealDamage) {
	std::string s1 = "Eminem";
	Enemy e(s1, EnemyType::HUMANOID, 15, 15, nullptr, 260, 180);
	e.changeParams(ENEMYPARAMETRS::ATTACK, 800);
	ASSERT_EQ(e.dealDamage(), 800);
}

TEST(EnemyTest, ItemDamage) {
	Weapon *w = new Weapon;
	std::string s1 = "Eminem";
	Enemy e(s1, EnemyType::HUMANOID, 15, 15, w, 260, 180);
	ASSERT_EQ(e.dealDamage(), 180);
}

TEST(EnemyTest, DropItem) {
	Weapon *w = new Weapon;
	std::string s1 = "Eminem";
	Enemy e(s1, EnemyType::HUMANOID, 15, 15, w, 260, 180);
	EnemyParams p = e.getParams();
	Item *i = e.dropItem();
	ASSERT_TRUE(p.i);
	p = e.getParams();
	ASSERT_EQ(p.i, nullptr);
	ASSERT_EQ(i->iAm(), ItemType::WEAPON);
	delete(i);
}

TEST(EnemyTest, GetDamage) {
	std::string s1 = "Eminem";
	Enemy e(s1, EnemyType::HUMANOID, 15, 15, nullptr, 260, 180);
	e.getDamage(200);
	EnemyParams p = e.getParams();
	ASSERT_TRUE(p.CurHealth < p.MaxHealth);
}

TEST(CellTest, Init) {
	CELL::Cell c;
	ASSERT_EQ(c.getType(), CELL::CellType::FLOOR);
	ASSERT_FALSE(c.getItem());
}

TEST(CellTest, SetType) {
	CELL::Cell c;
	c.setType(CELL::CellType::ENEMY);
	ASSERT_EQ(c.getType(), CELL::CellType::ENEMY);
}

TEST(CellTest, PutItem) {
	CELL::Cell c;
	Weapon *w = new Weapon;
	c.putItem(w);
	ASSERT_EQ(c.getItem()->iAm(), ITEMS::ItemType::WEAPON);
}

TEST(CellTest, OpenDoor) {
	CELL::Cell c;
	c.setType(CELL::CellType::CLOSED_DOOR);
	ASSERT_NO_THROW(c.openDoor());
	ASSERT_EQ(c.getType(), CELL::CellType::OPENED_DOOR);
}

TEST(CellTest, CloseDoor) {
	CELL::Cell c;
	c.setType(CELL::CellType::OPENED_DOOR);
	ASSERT_NO_THROW(c.closeDoor());
	ASSERT_EQ(c.getType(), CELL::CellType::CLOSED_DOOR);
}

TEST(CellTest, OperatorEq) {
	CELL::Cell c1, c2;
	Weapon *w = new Weapon;
	c2.putItem(w);
	c2.setType(CELL::CellType::ITEM);
	c1 = c2;
	ASSERT_EQ(c1.getType(), CELL::CellType::ITEM);
	ASSERT_EQ(c1.getItem()->iAm(), ITEMS::ItemType::WEAPON);
	ASSERT_EQ(c2.getType(), CELL::CellType::FLOOR);
	ASSERT_FALSE(c2.getItem());
}

TEST(FloorTest, Init) {
	CELL::Floor fl;
	ASSERT_EQ(fl.getLength(), 1);
}

TEST(FloorTest, ChangeType) {
	CELL::Floor fl;
	fl.changeType(0, 0, CELL::CellType::WALL);
	ASSERT_EQ(fl.getType(0, 0), CELL::CellType::WALL);
}

TEST(FloorTest, SetSize) {
	CELL::Floor fl;
	ASSERT_EQ(fl.getSize().length, 1);
	CELL::Size s(15, 10);
	fl.setSize(s);
	ASSERT_EQ(fl.getSize().length, 15);
	ASSERT_EQ(fl.getSize().width, 10);
}

TEST(FloorTest, PutEnemy) {
	CELL::Floor fl;
	std::string s1 = "PUP";
	CHARACTERS::Enemy *e = new Enemy(s1, EnemyType::ANIMAL, 0, 0, nullptr, 200, 400);
	fl.putEnemy(e, 0, 0);
	ASSERT_EQ(fl.getType(0, 0), CELL::CellType::ENEMY);
}

TEST(FloorTest, PutItem) {
	CELL::Floor fl;
	ITEMS::Weapon *w = new Weapon;
	fl.putItem(w, 0, 0,1);
	ASSERT_EQ(fl.getType(0, 0), CELL::CellType::ITEM);
}

TEST(DungeonTest, Init) {
	std::string s1 = "Player";
	CELL::Dungeon d(s1);
	ASSERT_EQ(d.getLevelCount(), 1);
}

TEST(DungeonTest, ChangeSize) {
	std::string s1 = "Player";
	CELL::Dungeon d(s1);
	CELL::Size s(10, 10);
	d.changeMapSize(0, s);
	ASSERT_EQ(d.getSize(0).length, 10);
}

TEST(DungeonTest, ChangeHeroParams) {
	std::string s1 = "Player";
	CELL::Dungeon d(s1);
	d.changeHeroParams(CHARACTERS::HeroParamIndex::AGILITY, 10);
	ASSERT_EQ(d.getHeroParams().agility,10);
}

TEST(DungeonTest, GetWeapon) {
	std::string s1 = "Player";
	CELL::Dungeon d(s1);
	Weapon *w = d.getWeapon();
	ASSERT_EQ(w->iAm(), ITEMS::ItemType::WEAPON);
}

int _tmain(int argc, _TCHAR *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}