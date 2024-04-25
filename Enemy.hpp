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
	int flag = 0;//0�����ŏ�� 1������ 2�����S 3���������

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

	int image;//�摜
	int shotImage;;//�e�ۉ摜
	int explosion[12];//�����摜
	int explocount;//�����A�j������
	int explosionSound;//��������
	int shotSound;//���ˉ�
	int damageSound;//�_���[�W
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

