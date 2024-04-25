#pragma once
#include "Dxlib.h"
#include "Shoot.hpp"
#include "pushKey.hpp"
#include "LoadMap.hpp"
class Player
{
public:
	int x;
	int y;
	int sizeX;//キャラのxサイズ
	int sizeY;//キャラのyサイズ
	int laserX;//現時点レーザーのxサイズ
	int laserY;//現時点レーザーのyサイズ
	int weaponGun;//プレイヤーの所持(銃)武器
	Player(int x, int y, int weaponGun,int money);//コンストラクタ
	void update(int& cameraX, int SizeX, LoadMap& m,int& mapsizeX);//全体の動き
	void setMoney(int money);//現在を所持金を変更する
	

	void hitEnemy(int& flag);//敵に当たった場合
	void hitItem(int& type);//アイテムに当たった場合
	void hitEnemyAmmo();//敵の弾に当たった場合
	void hyoji(int& cameraX);//表示
	int getHP();//HPゲット
	int tamakazu;

	Shoot tama[100];//弾配列
private:
	int hp;//hp
	int fontHandle;//フォントサイズ
	int playerAnimeSituation;//アニメーション管理
	int player_chaka[6];//プレイヤーピストル状態の画像
	int player_AK[3];//プレイヤーAK状態の画像
	int player_minigun[19];//プレイヤー	ミニガン状態の画像
	int player_robot[4];//プレイヤー改造形態の画像
	int minigun_shot[4];//ミニガン発光の画像；
	int laser_charge[5]; //レーザーチャージ
	int laser;//レーザーの画像
	
	int shotx;//銃口のx座標設定
	int shoty;//銃口のy座標設定
	int money;//所持金

	bool now_reload = false;//リロード中かどうか
	bool changeReloadTime;//武器変更時のリロードタイム変更
	bool createWeapon;//武器(Shoot)のインスタンス生成をループしないように
	bool minigunShot;//ミニガン撃ったときのアニメーション判定
	bool laserChargenow;//レーザーチャージアニメーション
	bool laserShot;//ビーム撃ったときのアニメーション判定
	bool canMove;

	int jump;//ジャンプ音
	int shotSound;//発射音
	int reloadSound;//リロード音
	int kara;//空打ち音
	int shotImage;//弾画像
	int minigunStartSound;//ミニガン発射スタート音
	int minigunEndSound;//ミニガン発射終了音
	int minigunLoopSound;//ミニガン回転音
	int laserChargeSound;//レーザーチャージ音
	int laserShotSound;//レーザー発射音
	int laserStopSound;//レーザー停止音
	int laserLoopSound;//レーザー待機音
	int damageSound_1;//ダメージ1
	int damageSound_2;//ダメージ2
	int damageSound_3;//ダメージ3
	int ricochet_1;//跳弾1
	int ricochet_2;//跳弾2
	int getItemSound;//アイテムゲットサウンド
	int getMoneySound;//お金ゲットサウンド
	int payMoneySound;//お金払うサウンド
	int hitSound;

	void move(int& cameraX, LoadMap& m, int& mapsizeX);//動く
	void shot(int& cameraX, int& SizeX, LoadMap& m);//撃つ
	void reload(int& tamakazu);//リロード
	void changeWeapon();//武器変更
	int createWeapons();//Shootのインスタンス生成メソッド
	
};

