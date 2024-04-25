#pragma once
#include <vector>
#include <cstdlib>
class LoadMap
{
public:
	LoadMap(int chipSize);
	void loadData(std::vector<std::vector<int>>& m, int x, int y, void (generateEnemy)(int, int, int), void (generateItem)(int, int, int));//�}�b�v�f�[�^��Main����ǂݍ���
	void hyoji(int& cameraX);//�}�b�v�\��
	void generateMap();//�`�b�v���W����S�̍��W�ɕϊ�
	std::vector<std::vector<int>> chipmap;//�`�b�v�p�}�b�v
	std::vector<std::vector<long>> map;//�S�̃}�b�v
private:
	int sizeX;//�}�b�v��x�T�C�Y
	int sizeY;//�}�b�v��y�T�C�Y
	int chipSize;//�}�b�v�̃`�b�v�T�C�Y
	int map_chip[2];//�}�b�v�摜
	
};

