#include "Enemy.hpp"
#include "dxlib.h"
Enemy::Enemy() {
	flag = 1;
	hp = 0;
	canCreate = true;
	
	shotImage = LoadGraph("./images/enemy_ammo.png");
	LoadDivGraph("./images/explosion.png",12,12,1,197,128,explosion);

	explosionSound = LoadSoundMem("./sound/explosion.mp3");
	shotSound = LoadSoundMem("./sound/enemy_shot.mp3");
	damageSound = LoadSoundMem("./sound/enemy_damage.mp3");
	explocount=0;
	isExploSound = true;
	isJump = false;
	startCount = false;
	wait = 200;
	bullet_wait = 5;
	y_prev = y;
	change = 0;
	isKillCount = true;
}
void Enemy::set(int& x, int& y, int& SizeX, int type) {
	this->x = x;
	this->y = y;
	this->SizeX = SizeX;
	this->type = type;
	if (type == 2) {
		image = LoadGraph("./images/enemy_chaka.png"); 
		hp = 80;
	}
	if (type == 3) {
		image = LoadGraph("./images/enemy_dosu.png");
		hp = 40;
	}

}
int Enemy::getKillCount() {
	if (isKillCount && flag == 0) {
		isKillCount = false;
		return 1;
	}
	return 0;
}
void Enemy::update(int& cameraX, LoadMap& m) {
	if (cameraX - 64 < x && x < cameraX + SizeX) {
		if (flag == 1) {
			hpControl();
			if (type == 3) {
				move();
			}
			if (type == 2) {
				shot(cameraX, m);
			}
		}
		ammo(cameraX,m);
	}
	jump(m);
	if (cameraX+8 > x) { 
		if (flag == 1)flag = 3;
		if(flag == 2) flag = 0;
	}
	hyoji(cameraX);
}

int Enemy::getFlag() {
	return flag;
}
void Enemy::hpControl() {
	if (hp <= 0) {
		if (flag == 1)
		flag = 2; 
	}

}

void Enemy::move() {
	int speed_x = 6;
	x -= speed_x;

}

void Enemy::hyoji(int& cameraX) {
	if(flag ==1) DrawGraph(x - cameraX, y, image, TRUE);
	if (flag == 2) {DrawRotaGraph2(x - cameraX, y+64, 0, 128, 1.0, 1.5708, image, TRUE, FALSE); }
	if (flag == 3) {
		if (isExploSound) {
			PlaySoundMem(explosionSound, DX_PLAYTYPE_BACK);
			isExploSound = false;
		}
		
		if (explocount % 3 == 0) change = explocount / 3;
		else change = explocount / 3 + 1;
		DrawGraph(x -45 - cameraX, y, explosion[change], TRUE);
		explocount++;
		if (explocount > 39) flag = 0;
	}
}

void Enemy::playerHit() {
	if (flag == 1) flag = 3;
	if (flag == 2) flag = 0;
}
void Enemy::ammoHit(int& damage) {
	hp -= damage;
	PlaySoundMem(damageSound, DX_PLAYTYPE_BACK);
}
void Enemy::shot(int& cameraX,LoadMap& m) {
	int shotx = x;
	int shoty = y + 86;
	int shotspeed = -10;

	if (canCreate) {
		for (int i = 0; i < 5; i++) {
			tama[i].set(shotx, shoty, 8, 8, shotspeed, shotImage, shotSound);
		}
		canCreate = false;
	}

	int bullet_time = 5;
	int count = 0;
	int shot = 0 + (int)(rand() * (10 - 0  + 1.0) / (1.0 + RAND_MAX));
	if (bullet_wait == 0) {
		if (shot == 0) {
			for (int i = 0; i < 5; i++) {
				if (tama[i].flag == 0) {
					tama[i].shot(shotx, shoty, cameraX, SizeX);
					bullet_wait = bullet_time;
					break;
				}
			}
		}
		for (int i = 0; i < 5; i++) {
			if (tama[i].flag == 2) {
				count++;
			}
		}
	}
	else {
		bullet_wait--;
	}
	if (count >= 5) {
		reload(5);
	}
}
void Enemy::ammo(int& cameraX,LoadMap& m) {
	for (int i = 0; i < 5; i++) {
		tama[i].bulletsMove(cameraX, SizeX, m);
	}
}
void Enemy::jump(LoadMap& m) {
	int tmpy = y;
	int jump = 0 + (int)(rand() * (10 - 0 + 1.0) / (1.0 + RAND_MAX));
	if (isJump) {
		tmpy = y;
		y += (y - y_prev) + 1;
		y_prev = tmpy;
	}
	if (jump == 0 && !isJump && flag == 1 && type == 2) {
		isJump = true;
		y_prev = y;
		y -= 10;
	}
	if (m.map[y + 128 - 1][x] == 1 || m.map[y + 128 - 1][x + 64] == 1) {//•Ç‚ª‰º‚É‚ ‚éê‡
		isJump = false;
		y = tmpy;
	}
	if (m.map[y - 1][x] == 1 || m.map[y - 1][x + 64] == 1) {//•Ç‚ªã‚É‚ ‚éê‡
		isJump = false;
		y = tmpy;
	}
	if (flag==1 && (m.map[y][x] == 1 || m.map[y + 128 - 1][x] == 1 || m.map[y + 128 / 2][x] == 1)) flag = 3;//•Ç‚ª¶‚É‚ ‚éê‡
	int ycount = 0;
	for (int i = 0; i < m.map.size() * 64; i++) {
		if (!isJump) {
			if (m.map[y + 128 + i][x + 5] == 0 && m.map[y + 128 + i][x + 38] == 0) ycount++;
			if (m.map[y + 128 + i][x + 5] == 1 || m.map[y + 128 + i][x + 38] == 1) break;
		}
	}
	if (ycount > 0) {
		isJump = true;
		y_prev = y;
	}
}
void Enemy::reload(int tamakazu) {
	int time = 200;
	startCount = true;

	if (startCount) {
		wait--;
	}
	if (wait == 0) {
		for (int i = 0; i < tamakazu; i++) {
			if (tama[i].flag == 2) tama[i].reload();
		}
		startCount = false;
		wait = time;
	}
}

