#pragma once
#include "Shoot.hpp"
#include "LoadMap.hpp"
class Enemy
{
public: 
	int x;
	int y;
	int type;
	int hp;
	Enemy();
	void update(int& cameraX, LoadMap& m);
	void set(int& x, int& y, int& SizeX, int type);
	int flag = 0;//0が消滅状態 1が生存 2が死亡 3が爆発状態

	int getFlag();
	void playerHit();
	void ammoHit(int& damage);
	void hyoji(int& cameraX);
	int getKillCount();
	Shoot tama[5];
	
private:
	
	int SizeX;
	int y_prev;
	int bullet_wait;
	int wait;
	int change;

	int image;//画像
	int shotImage;;//弾丸画像
	int explosion[12];//爆発画像
	int explocount;//爆発アニメ時間
	int explosionSound;//爆発おと
	int shotSound;//発射音
	int damageSound;//ダメージ
	bool canCreate;
	bool isExploSound;
	bool isJump;
	bool startCount;
	bool isKillCount;
	void shot(int& cameraX, LoadMap& m);
	void move();
	void jump(LoadMap& m);
	void hpControl();
	void reload(int tamakazu);
	void ammo(int& cameraX, LoadMap& m);
};

