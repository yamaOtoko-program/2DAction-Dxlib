#include "HitCheck.hpp"
HitCheck::HitCheck() {
	headShotSound = LoadSoundMem("./sound/headShot.mp3");
	laserhit = LoadSoundMem("./sound/enemy_hitlaser.mp3");
}

void HitCheck::checkHit(Player& p, std::vector<Enemy>& e, std::vector<Item>& item,int& cameraX,LoadMap& m) {
	//プレイヤーが受け
	for (int i = 0; i < e.size(); i++) {
		if (p.x + p.sizeX > e[i].x && p.x < e[i].x + 64 && p.y + p.sizeY > e[i].y && p.y < e[i].y + 128) {
			int flag = e[i].flag;
			p.hitEnemy(flag);
			e[i].playerHit();
		}

		for (int j = 0; j < 5; j++) {
			Shoot& s = e[i].tama[j];
			if (p.x + p.sizeX > s.x && p.x < s.x + s.sizeX && p.y + p.sizeY > s.y && p.y < s.y + s.sizeY) {
				if (s.flag == 1) {
					p.hitEnemyAmmo();
					s.flag = 2;
				}
			}
		}
	}
	//敵が受け
	for (int i = 0; i < e.size(); i++) {
		if (p.weaponGun == 3) {
			if (e[i].x + 64 > p.x + p.sizeX && e[i].x < p.laserX && e[i].y + 128 > p.y + 8 && e[i].y < p.laserY) {
				//レーザー
				if (e[i].flag != 0 && cameraX - 64 < e[i].x && e[i].x < cameraX + 1280) {
					p.setMoney(20000);
					e[i].hp -= 500;
					e[i].flag = 0;
					PlaySoundMem(laserhit, DX_PLAYTYPE_BACK);
				}
				
			}
		}
		else {
			for (int j = 0; j < p.tamakazu; j++) {
				//銃弾
				Shoot& s = p.tama[j];
				int type = p.weaponGun;
				int damage = 0;
				if (e[i].x + 64 > s.x && e[i].x < s.x + s.sizeX && e[i].y + 128 > s.y && e[i].y < s.y + s.sizeY) {
					if (e[i].flag == 1 && s.flag == 1) {
						if (e[i].y + 71 > s.y) {
							PlaySoundMem(headShotSound, DX_PLAYTYPE_BACK);
							if (type == 0) damage = 15;
							if (type == 1) damage = 20;
							if (type == 2) damage = 40;
							p.setMoney(5000);
						}
						else {
							if (type == 0) damage = 10;
							if (type == 1 ) damage = 15;
							if (type == 2) damage = 20;
						}
						e[i].ammoHit(damage);
						s.flag = 2;
					}
				}
			}
		}

	}
	for (int i = 0; i < item.size(); i++) {
		//アイテム
		if (p.x + p.sizeX > item[i].x+10 && p.x < item[i].x + item[i].sizeX-10 && p.y + p.sizeY > item[i].y && p.y < item[i].y + 10 + item[i].sizeY - 10) {
			int type = item[i].type;
			if(item[i].flag){
				item[i].get();
				p.hitItem(type);
			}
			
		}
	}
}
