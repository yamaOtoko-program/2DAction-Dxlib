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
	int flag;//2�������[�h�҂����1���\�����0����\�����
	Shoot();
	~Shoot();
	void shot(int x, int y, int& cameraX, int SizeX);//���˃{�^�����������Ƃ��̏���
	void bulletsMove(int& cameraX, int SizeX, LoadMap& m);//���˂��ꂽ���Ƃ̓���
	void set(int& x, int& y, int sizeX, int sizeY, int& speed, int& tama, int& sound);//���W�Ƒ��x�̃Z�b�g
	void reload();//�����[�h
private:
	int sound;//�e����
	int tama;//�e�̉摜
	int speed;//���˃X�s�[�h���i�[
};

