#pragma once
#include "Dxlib.h"
#include "LoadMap.hpp"
class Shoot
{
public: 
	int x;
	int y;
	int sizeX;
	int sizeY;
	int flag;//2がリロード待ち状態1が表示状態0が非表示状態
	Shoot();
	~Shoot();
	void shot(int x, int y, int& cameraX, int SizeX);//発射ボタンを押したときの処理
	void bulletsMove(int& cameraX, int SizeX, LoadMap& m);//発射されたあとの動き
	void set(int& x, int& y, int sizeX, int sizeY, int& speed, int& tama, int& sound);//座標と速度のセット
	void reload();//リロード
private:
	int sound;//銃撃音
	int tama;//弾の画像
	int speed;//発射スピードを格納
};

