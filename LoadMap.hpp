#pragma once
#include <vector>
#include <cstdlib>
class LoadMap
{
public:
	LoadMap(int chipSize);
	void loadData(std::vector<std::vector<int>>& m, int x, int y, void (generateEnemy)(int, int, int), void (generateItem)(int, int, int));//マップデータをMainから読み込む
	void hyoji(int& cameraX);//マップ表示
	void generateMap();//チップ座標から全体座標に変換
	std::vector<std::vector<int>> chipmap;//チップ用マップ
	std::vector<std::vector<long>> map;//全体マップ
private:
	int sizeX;//マップのxサイズ
	int sizeY;//マップのyサイズ
	int chipSize;//マップのチップサイズ
	int map_chip[2];//マップ画像
	
};

