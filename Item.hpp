#pragma once
class Item
{
public:
	int x;//x���W
	int y;//y���W
	int sizeX;
	int sizeY;
	int type;//�A�C�e���^�C�v 4���}���t�@�i�A5���N���R�_�C���B
	Item();//�R���X�g���N�^
	void itemSet(int& x, int& y, int& type);//�A�C�e���̍��W�ƃ^�C�v���i�[
	void update(int& cameraX);//�S�̂̃��\�b�h
	void get();//������
	bool flag;//�\������\����
private:
	int mari;//�A�C�e���摜�i�[
	int taima;//�A�C�e���摜�i�[
	int kuroko;//�A�C�e���摜�i�[
	
	void hyoji(int& cameraX);//�摜�\�����\�b�h
};

