#include "LoadMap.hpp"
#include "Dxlib.h"
//#include <vector>
LoadMap::LoadMap(int chipSize){
	this->chipSize = chipSize;
	LoadDivGraph("./images/map.png", 2, 2, 1, 64, 64, map_chip); 
}

void LoadMap ::loadData(std::vector<std::vector<int>>& m, int x, int y,void (generateEnemy)(int, int, int), void (generateItem)(int, int,int)) {
	sizeX = x*chipSize;
	sizeY = y*chipSize;
	chipmap = std::vector<std::vector<int>>(sizeY / chipSize, std::vector<int>(sizeX / chipSize));
	for (int y = 0; y < sizeY/chipSize; y++) {
		for (int x = 0; x < sizeX / chipSize; x++) {
			chipmap[y][x] = m[y][x];
			if (2<= chipmap[y][x] && chipmap[y][x] <= 3) {
				generateEnemy(x * chipSize, y * chipSize, chipmap[y][x]);
			}
			if (4 <= chipmap[y][x] && chipmap[y][x] <= 6) {
				generateItem(x*chipSize,y*chipSize, chipmap[y][x]);
			}
		}
	}
}
void LoadMap::hyoji(int &cameraX) {
	for (int y = 0; y < sizeY / chipSize; y++) {
		for (int x = 0; x < sizeX / chipSize; x++) {
			int realmap = chipmap[y][x];
			if (realmap > 1) realmap = 0;
			DrawGraph(x * 64 - cameraX, y * 64, map_chip[realmap], FALSE);
		}
	}
}
void LoadMap:: generateMap() {
	map = std::vector<std::vector<long>>(sizeY, std::vector<long>(sizeX));
	for (int y = 0; y < sizeY / chipSize; y++) {
		for (int x = 0; x < sizeX / chipSize; x++) {
			for (int ye = 0; ye < chipSize; ye++) {
				for (int xe = 0; xe < chipSize; xe++) {
					int realmap = chipmap[y][x];
					if (realmap > 1) realmap = 0;
					map[ye + y*chipSize][xe + x*chipSize] = realmap;
				}
			}
		}
	}

}