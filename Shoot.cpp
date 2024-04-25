#include "Shoot.hpp"


Shoot::Shoot() {
	x = 0;
	y = 0;
	speed = 0;
}
Shoot::~Shoot() {
	
}
void Shoot::set(int& x, int& y, int sizeX, int sizeY, int& speed, int& tama, int& sound) {
	this->x = x;
	this->y = y;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->speed = speed;
	this->tama = tama;
	this->sound = sound;
	flag = 0;
}
void Shoot::shot(int x, int y, int& cameraX, int SizeX) {
	if (x >= SizeX - (sizeX + speed + 10) + cameraX) return;
	PlaySoundMem(sound, DX_PLAYTYPE_BACK);
	flag = 1;
	this->x = x;
	this->y = y;
}
void Shoot::reload() {
	flag = 0;
}
void Shoot::bulletsMove(int& cameraX, int SizeX,LoadMap& m) { 
	if (flag == 1) {
		DrawGraph(x - cameraX, y, tama, TRUE);	//弾を表示
		x += speed;
		if (x > SizeX + cameraX || cameraX > x) flag = 2;//リロード待ち状態。
		if (x + sizeX >= m.map.at(0).size() - speed) { flag = 2; return; }
		if (m.map[y][x + sizeX] == 1 || m.map[y + sizeY][x + sizeX] == 1) {
			flag = 2;//壁が右にある 
		}
	}
}