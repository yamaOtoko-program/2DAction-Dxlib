#include "Player.hpp"

Player::Player(int x, int y, int weaponGun, int money) {
	this->x = x;
	this->y = y;
	this->weaponGun = weaponGun;
	this->money = 150000;
	hp = 200;
	tamakazu = 0;
	LoadDivGraph("./images/miffi_chaka.png", 6, 6, 1, 69, 128, player_chaka);
	LoadDivGraph("./images/miffi_ak.png", 3, 3, 1, 96, 128, player_AK);
	LoadDivGraph("./images/miffi_minigun.png", 19, 19, 1, 88, 128, player_minigun);
	LoadDivGraph("./images/minigun_shot.png", 4, 4, 1, 24, 20, minigun_shot);
	LoadDivGraph("./images/miffi_shinka.png", 4, 4, 1, 74, 128, player_robot);
	LoadDivGraph("./images/laser_charge.png", 5, 5, 1, 86, 86, laser_charge);
	damageSound_1 = LoadSoundMem("./sound/damage_1.mp3");
	damageSound_2 = LoadSoundMem("./sound/damage_2.mp3");
	damageSound_3 = LoadSoundMem("./sound/damage_3.mp3");
	ricochet_1 = LoadSoundMem("./sound/ricochet1.mp3");
	ricochet_2 = LoadSoundMem("./sound/ricochet2.mp3");
	getItemSound = LoadSoundMem("./sound/get_item.mp3");
	getMoneySound = LoadSoundMem("./sound/get_money.mp3");
	payMoneySound = LoadSoundMem("./sound/pay_money.mp3");
	hitSound = LoadSoundMem("./sound/hitBlock.mp3");
	jump = LoadSoundMem("./sound/jump.mp3");
	laser = LoadGraph("./images/laser.png");
	createWeapon = true;
	changeReloadTime = true;
	minigunShot = false;
	laserShot = false;
	canMove = true;
	laserChargenow = false;
	kara = 0;
	reloadSound = 0;
	sizeX = 64;
	sizeY = 128;
	laserX = 0;
	laserY = 0;
	fontHandle = CreateFontToHandle(NULL, 20, -1, DX_FONTTYPE_EDGE);
}

pushKey p(MOUSE_INPUT_LEFT);
pushKey p2(MOUSE_INPUT_LEFT);
pushKey r(KEY_INPUT_R);
int time = 0;
int wait = 0;

void Player::update(int& cameraX, int SizeX, LoadMap& m, int& mapSizeX) {
	changeWeapon();
	move(cameraX, m,mapSizeX);
	shot(cameraX, SizeX,m);
	hyoji(cameraX);
}

int mCount = 0;//ミニガン残り弾数カウント
int chargeCount = 0;//レーザービームチャージカウント
int beemCount = 0;//ビーム発射時間カウント
void Player::hyoji(int& cameraX) {
	if(weaponGun == 3)DrawFormatStringToHandle(50, 150, GetColor(255, 255, 255), fontHandle, "HP:999999999999 谿ｺ縺励◆謨ｰ:%d",money);
	else DrawFormatStringToHandle(50, 150, GetColor(255, 255, 255), fontHandle, "HP:%d 上納金:%d円",hp,money);
	DrawFormatStringToHandle(50, 200, GetColor(255, 255, 255), fontHandle, "1.ピストル:20000円\n2.AK:40000円\n3.ミニガン:80000円\n4.???:150000円");
	if (hp <= 0) {
		int playerImage;
		if(weaponGun==0) playerImage = player_chaka[0];
		if (weaponGun == 1) playerImage = player_AK[0];
		if (weaponGun == 2) playerImage = player_minigun[0];
		DrawRotaGraph2(x - cameraX, y+64, 64, 128, 1.0, 4.71239, playerImage, TRUE, FALSE);
	}
	else {
		if (playerAnimeSituation == 0) {
			//ピストル通常時
			DrawGraph(x - cameraX, y, player_chaka[0], TRUE);
		}
		if (playerAnimeSituation == 1) {
			//ピストル発射アニメーション
			static int pistolShotAnimation = 1;
			DrawGraph(x - cameraX, y, player_chaka[pistolShotAnimation], TRUE);
			pistolShotAnimation++;
			if (pistolShotAnimation >= 6) pistolShotAnimation = 1;
			playerAnimeSituation = 0;
		}
		if (playerAnimeSituation == 2) {
			//ピストル弾切れ
			DrawGraph(x - cameraX, y, player_chaka[4], TRUE);
		}
		if (playerAnimeSituation == 4) {
			//AK47通常時
			DrawGraph(x - cameraX, y, player_AK[0], TRUE);
		}
		if (playerAnimeSituation == 5) {
			//AK47発射アニメーション
			static int pistolShotAnimation = 1;
			DrawGraph(x - cameraX, y, player_AK[pistolShotAnimation], TRUE);
			pistolShotAnimation++;
			if (pistolShotAnimation >= 3) pistolShotAnimation = 1;
			playerAnimeSituation = 4;
		}
		if (playerAnimeSituation == 6) {
			//ミニガン通常時
			if (minigunShot) mCount++;
			if (100 - mCount <= 17) {
				DrawGraph(x - cameraX, y, player_minigun[18 - (100 - mCount)], TRUE);
			}
			else {
				DrawGraph(x - cameraX, y, player_minigun[0], TRUE);
			}
		}
		if (minigunShot) {
			//ミニガン発射時
			static int minigunShotAnimation = 0;
			DrawGraph((x + 88) - cameraX, y + 92, minigun_shot[minigunShotAnimation], TRUE);
			minigunShotAnimation++;
			if (minigunShotAnimation >= 3) minigunShotAnimation = 0;
			minigunShot = false;
		}
		if (playerAnimeSituation == 7) {
			//ミッフィー改造形態通常時
			static int change = 0;
			if (mCount % 9 == 0) change = mCount / 9;
			else change = mCount / 9 + 1;
			DrawGraph(x - cameraX, y, player_robot[change], TRUE);
		}
		if (laserChargenow) {
			static int change = 0;
			if (chargeCount % 80 == 0) change = chargeCount / 80;
			else change = chargeCount / 80 + 1;
			if (laserShot) change = 0;
			DrawGraph(x + 74 - cameraX, y + 8, laser_charge[change], TRUE);
		}
		if (laserShot) {
			DrawRotaGraph3(x + 74 + 79 - cameraX, y + 8 + 20, 0, 0, beemCount, 1, 0, laser, TRUE, FALSE);
		}
	}
}
int Player::getHP() {
	return hp;
}
void Player::hitItem(int& type) {
	if (type == 4) { 
		PlaySoundMem(getItemSound,DX_PLAYTYPE_BACK);
		hp += 40; 
	}

	if (type == 5) {
		PlaySoundMem(damageSound_1, DX_PLAYTYPE_BACK);
		hp -= 60;
	}
}
void Player::move(int& cameraX, LoadMap& m, int& mapSizeX) {
	int jikispeed = 8;
	if (weaponGun == 3) jikispeed = 12;
	int tmpx = x, tmpy = y;
	int tmcx = cameraX;
	static int y_prev = y;
	static bool isJump = false;
	if (canMove) {
		if (isJump) {
			tmpy = y;
			y += (y - y_prev) + 1;
			y_prev = tmpy;
		}
		
		if (CheckHitKey(KEY_INPUT_A)) {
			if (x - cameraX <= jikispeed) x = jikispeed + cameraX;//これより後ろに行くとエラー
			x -= jikispeed;
		}
		if (CheckHitKey(KEY_INPUT_D)) {
			if (x - cameraX > 64 * 6 && cameraX < mapSizeX-1280-8) { cameraX += jikispeed; }
			if(mapSizeX > x+sizeX) x += jikispeed;
		}
		if (CheckHitKey(KEY_INPUT_SPACE) && !isJump) {
			if(!CheckSoundMem(jump))PlaySoundMem(jump, DX_PLAYTYPE_BACK);
			isJump = true;
			y_prev = y;
			y -= 20;
		}
	}
	if (y <= jikispeed) y = 8;
	if (m.map[y][x + 38] == 1 || m.map[y + sizeY - 1][x + 38] == 1 || m.map[y + sizeY / 2][x + 38] == 1) {
		//壁が右にある場合
		x = tmpx; 
		cameraX = tmcx;
	}
	if (m.map[y][x] == 1 || m.map[y + sizeY - 1][x] == 1|| m.map[y+sizeY/2][x] == 1) x = tmpx;//壁が左にある場合

	if (m.map[y + sizeY - 1][x + 5] == 1 || m.map[y + sizeY - 1][x + 38] == 1) {//壁が下にある場合
		isJump = false;
		y = tmpy;
	}
	if (m.map[y][x + 5] == 1 || m.map[y][x + 38] == 1) {//壁が上にある場合
		if (CheckHitKey(KEY_INPUT_SPACE) && !CheckSoundMem(hitSound)) PlaySoundMem(hitSound, DX_PLAYTYPE_BACK);
		isJump = false;
		y = tmpy;
	}

	int ycount = 0;
	for (int i = 0; i < m.map.size()*64; i++) {
		if (!isJump) {
			if (m.map[y + sizeY + i][x + 5] == 0 && m.map[y + sizeY + i][x + 38] == 0) ycount++;
			if (m.map[y + sizeY + i][x + 5] == 1 || m.map[y + sizeY + i][x + 38] == 1) break;
		}
	}

	if (ycount > 0 ) {
		isJump = true;
		y_prev = y;
	}


}

int Player::createWeapons() {
	if (weaponGun == 0) {
		//ピストル
		playerAnimeSituation = 0;
		reloadSound = LoadSoundMem("./sound/chaka_reload.mp3");
		kara = LoadSoundMem("./sound/chaka_kara.mp3");
		shotSound = LoadSoundMem("./sound/chaka_shot.mp3");
		shotImage = LoadGraph("./images/chaka_ammo.png");
		sizeX = 64;
		sizeY = 128;
		time = 100;
		wait = time;
		return 7;
	}
	if (weaponGun == 1) {
		//AK47
		playerAnimeSituation = 4;
		reloadSound = LoadSoundMem("./sound/ak_reload.mp3");
		kara = LoadSoundMem("./sound/chaka_kara.mp3");
		shotSound = LoadSoundMem("./sound/ak_shot.mp3");
		shotImage = LoadGraph("./images/ak_ammo.png");
		sizeX = 91;
		sizeY = 128;
		time = 120;
		wait = time;
		return 30;
	}
	if (weaponGun == 2) {
		//ミニガン
		playerAnimeSituation = 6;
		reloadSound = LoadSoundMem("./sound/minigun_reload.mp3");
		kara = LoadSoundMem("./sound/chaka_kara.mp3");
		shotSound = LoadSoundMem("./sound/minigun_shot.mp3");
		shotImage = LoadGraph("./images/ak_ammo.png");
		minigunStartSound = LoadSoundMem("./sound/minigun_start.mp3");
		minigunEndSound = LoadSoundMem("./sound/minigun_end.mp3");
		minigunLoopSound = LoadSoundMem("./sound/minigun_loop.mp3");
		sizeX = 88;
		sizeY = 128;
		time = 450;
		wait = time;
		return 100;
	}
	if (weaponGun == 3) {
		//改造形態
		playerAnimeSituation = 7;
		laserChargeSound= LoadSoundMem("./sound/laser_charge.mp3");
		laserStopSound = LoadSoundMem("./sound/laser_stop.mp3");
		laserShotSound = LoadSoundMem("./sound/laser_shot.mp3");
		laserLoopSound = LoadSoundMem("./sound/laser_loop.mp3");
		sizeX = 74;
		sizeY = 128;
		mCount = 0;
		time = 300;
		wait = time;
		return 5;
	}
}

void Player::changeWeapon() {
	if (CheckHitKey(KEY_INPUT_1)) {
		if (weaponGun == 0 || weaponGun == 3 || money < 20000) return;
		PlaySoundMem(payMoneySound, DX_PLAYTYPE_BACK);
		changeReloadTime = true;
		weaponGun = 0;
		money -= 500;
		createWeapon = true;
	}
	if (CheckHitKey(KEY_INPUT_2)) {
		if (weaponGun == 1 || weaponGun == 3 || money < 40000) return;
		PlaySoundMem(payMoneySound, DX_PLAYTYPE_BACK);
		changeReloadTime = true;
		weaponGun = 1;
		money -= 40000;
		createWeapon = true;
	}
	if (CheckHitKey(KEY_INPUT_3)) {
		if (weaponGun >= 2 || money < 80000) return;
		PlaySoundMem(payMoneySound, DX_PLAYTYPE_BACK);
		mCount = 0;
		changeReloadTime = true;
		weaponGun = 2;
		money -= 80000;
		createWeapon = true;
	}
	if (CheckHitKey(KEY_INPUT_4)) {
		if (weaponGun == 3 || money < 150000) return;
		PlaySoundMem(payMoneySound, DX_PLAYTYPE_BACK);
		changeReloadTime = true;
		weaponGun = 3;
		money -= 150000;
		createWeapon = true;
	}

}

void Player::setMoney(int money) {
	this->money += money;
}
void Player::shot(int& cameraX, int& SizeX,LoadMap& m) {
	shotx = x + sizeX;
	
	if (createWeapon) {
		int speed = 40;
		if (weaponGun == 1) speed = 50;
		if (weaponGun == 2) speed = 64;
		tamakazu = createWeapons();
		if (weaponGun < 3) {
			for (int i = 0; i < tamakazu; i++) {
				tama[i].set(shotx, shoty, 18, 18, speed, shotImage, shotSound);
			}
		}
		else {

		}
		createWeapon = false;
	}
	if (weaponGun == 0) {
		shoty = y + 78;
		int bullet_time = 5;
		static int  bullet_wait = bullet_time;
		int count = 0;
		if (bullet_wait == 0) {
			if (p.push() && !now_reload) {
				for (int i = 0; i < tamakazu; i++) {
					if (tama[i].flag == 0) {
						playerAnimeSituation = 1;
						tama[i].shot(shotx, shoty, cameraX, SizeX);
						bullet_wait = bullet_time;
						break;
					}
				}
			}
			for (int i = 0; i < tamakazu; i++) {
				if (tama[i].flag == 2) {
					count++;
				}
			}
			if (count >= tamakazu) playerAnimeSituation = 2;
			if (p2.push() && !now_reload) {
				if (count >= tamakazu) {
					PlaySoundMem(kara, DX_PLAYTYPE_BACK);
				}
			}
		}
		else {
			bullet_wait--;
		}
		for (int i = 0; i < tamakazu; i++) {
			tama[i].bulletsMove(cameraX, SizeX,m);
		}
		reload(tamakazu);
	}

	if (weaponGun == 1 || weaponGun == 2) {
		if (weaponGun == 1) shoty = y + 74;
		else shoty = y + 98;
		int bullet_time = 5;
		static int  bullet_wait = bullet_time;
		int count = 0;
		static bool hitkey = false;
		static int shotCount = 0;//ミニガン発射までのカウント
		if (bullet_wait == 0) {
			if (GetMouseInput() && MOUSE_INPUT_LEFT && !now_reload) {
				if (weaponGun == 2) {
					if (!hitkey) PlaySoundMem(minigunStartSound, DX_PLAYTYPE_BACK);
					shotCount++;
					if (shotCount > 45) {

						if(!CheckSoundMem(minigunLoopSound)) PlaySoundMem(minigunLoopSound, DX_PLAYTYPE_BACK);
					}
				}
				if (weaponGun == 1 || (weaponGun == 2 && shotCount > 45)) {
					for (int i = 0; i < tamakazu; i++) {
						if (tama[i].flag == 0) {
							if (weaponGun == 1) playerAnimeSituation = 5;
							else {
								minigunShot = true;
							}
							tama[i].shot(shotx, shoty, cameraX, SizeX);
							bullet_wait = bullet_time;
							break;
						}
					}
				}

			}

			for (int i = 0; i < tamakazu; i++) {
				if (tama[i].flag == 2) {
					count++;
				}
			}
			if (p2.push() && !now_reload) {
				if (count >= tamakazu) {
					if (weaponGun == 1) PlaySoundMem(kara, DX_PLAYTYPE_BACK);
				}
			}
		}
		else {
			bullet_wait--;
		}
		for (int i = 0; i < tamakazu; i++) {
			tama[i].bulletsMove(cameraX, SizeX,m);
		}
		if (weaponGun == 2 && hitkey && (!(GetMouseInput() && MOUSE_INPUT_LEFT)) && !now_reload) {
			StopSoundMem(minigunLoopSound);
			PlaySoundMem(minigunEndSound, DX_PLAYTYPE_BACK);
			shotCount = 0;
		}
		reload(tamakazu);
		hitkey = GetMouseInput() & MOUSE_INPUT_LEFT;
	}

	if (weaponGun == 3) {
		static bool hitkey = false;
		static bool chargeS = true;
		if (GetMouseInput() && MOUSE_INPUT_LEFT && !now_reload) {
			canMove = false;
			if (mCount < 27) { mCount++; }
			else {
				
				if (chargeS) {
					PlaySoundMem(laserChargeSound, DX_PLAYTYPE_BACK);
					chargeS = false;
				}
				laserChargenow = true;
				if (chargeCount < 240 + 1) { 
					laserX = x + 64 + 128;
					laserY = y + 128;
					chargeCount++; 
				}
				else {
					chargeCount = 240 + 1;
					if (!CheckSoundMem(laserLoopSound)) PlaySoundMem(laserLoopSound, DX_PLAYTYPE_BACK);
				}
			}
		}
		if (hitkey && (!(GetMouseInput() && MOUSE_INPUT_LEFT)) && !now_reload) {
			StopSoundMem(laserChargeSound);
			StopSoundMem(laserLoopSound);
			if (chargeCount >= 240 + 1) laserShot = true;
			else { 
				laserX = 0;
				laserY = 0;
				PlaySoundMem(laserStopSound, DX_PLAYTYPE_BACK);
				chargeS = true;
				canMove = true; 
				mCount = 0; 
				chargeCount = 0;
				laserChargenow = false;
			}
		}
		if (laserShot) {
			laserX = (x + 74 + 79) * beemCount;
			laserY = y + 75;
			beemCount++;
			if (x - cameraX > 1 && !(m.map[y][x] == 1 || m.map[y + sizeY - 1][x] == 1 || m.map[y + sizeY / 2][x] == 1))x--;
			if(!CheckSoundMem(laserShotSound)) PlaySoundMem(laserShotSound, DX_PLAYTYPE_BACK);
			if (beemCount >= 200) {
				StopSoundMem(laserShotSound);
				PlaySoundMem(laserStopSound, DX_PLAYTYPE_BACK);
				laserX = 0;
				laserY = 0;
				chargeCount = 0;
				laserShot = false;
				laserChargenow = false;
				beemCount = 0;
				canMove = true;
				chargeS = true;
				mCount = 0;
			}
		}
		hitkey = GetMouseInput() & MOUSE_INPUT_LEFT;
	}
}

void Player::reload(int& tamakazu) {
	if (weaponGun == 3) return;
	int afterReloadAnimaiton = 0;
	if (weaponGun == 0) afterReloadAnimaiton = 0;
	if (weaponGun == 1) afterReloadAnimaiton = 4;
	if (weaponGun == 2) afterReloadAnimaiton = 6;
	static bool startcount = false;
	static bool soundR = true;
	if (r.push()) {
		if (soundR) {
			PlaySoundMem(reloadSound, DX_PLAYTYPE_BACK);
			soundR = false;
		}
		now_reload = true;
		startcount = true;
	}
	if (startcount) {

		wait--;
	}
	if (wait == 0) {
		for (int i = 0; i < tamakazu; i++) {
			if (tama[i].flag == 2) tama[i].reload();
		}
		startcount = false;
		wait = time;
		soundR = true;
		now_reload = false;
		playerAnimeSituation = afterReloadAnimaiton;
		mCount = 0;
	}
}
void Player::hitEnemy(int& flag) {
	if (flag == 2) {
		if(!CheckSoundMem(getMoneySound)) PlaySoundMem(getMoneySound, DX_PLAYTYPE_BACK);
		money += 10000;
	}
	if (flag == 1) {
		if (weaponGun < 3) {
			PlaySoundMem(damageSound_1, DX_PLAYTYPE_BACK);
			hp -= 40;
		}
	}
}
void Player::hitEnemyAmmo() {
	int shot = 0 + (int)(rand() * (1 - 0 + 1.0) / (1.0 + RAND_MAX));
	if (weaponGun < 3) {
		static int damage = 1;
		if(damage < 0)PlaySoundMem(damageSound_2, DX_PLAYTYPE_BACK);
		else PlaySoundMem(damageSound_3, DX_PLAYTYPE_BACK);
		hp -= 20;
		damage *= -1;
	}
	else {
		if(shot == 0) PlaySoundMem(ricochet_1, DX_PLAYTYPE_BACK);
		else PlaySoundMem(ricochet_2, DX_PLAYTYPE_BACK);
	}
}