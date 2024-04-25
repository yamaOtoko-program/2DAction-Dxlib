#pragma once
#include "Dxlib.h"
#include "Player.hpp"
#include "Shoot.hpp"
#include "Enemy.hpp"
#include "Item.hpp"
class HitCheck
{
public:
	HitCheck();
	void checkHit(Player& p, std::vector<Enemy>& e, std::vector<Item>& item,int& cameraX, LoadMap& m);
private:
	int headShotSound;
	int laserhit;
};

