#include "Item.hpp"
#include "Dxlib.h"
Item::Item() {
	taima = LoadGraph("./images/taima.png");
	kuroko = LoadGraph("./images/kurokodairu.png");
};
void Item::itemSet(int& x,int& y,int& type){
	this->x = x;
	this->y = y;
	sizeX = 64;
	sizeY = 64;
	flag = true;
	this->type = type;
}
void Item::update(int& cameraX) {
	hyoji(cameraX);
}
void Item::hyoji(int& cameraX) {
	if (flag) {
		if (type == 4)
			DrawGraph(x - cameraX, y, taima, TRUE);
		if (type == 5)
			DrawGraph(x - cameraX, y, kuroko, TRUE);
	}
}
void Item::get() {
	flag = false;
}