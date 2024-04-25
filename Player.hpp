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
	int sizeX;//�L������x�T�C�Y
	int sizeY;//�L������y�T�C�Y
	int laserX;//�����_���[�U�[��x�T�C�Y
	int laserY;//�����_���[�U�[��y�T�C�Y
	int weaponGun;//�v���C���[�̏���(�e)����
	Player(int x, int y, int weaponGun,int money);//�R���X�g���N�^
	void update(int& cameraX, int SizeX, LoadMap& m,int& mapsizeX);//�S�̂̓���
	void setMoney(int money);//���݂���������ύX����
	

	void hitEnemy(int& flag);//�G�ɓ��������ꍇ
	void hitItem(int& type);//�A�C�e���ɓ��������ꍇ
	void hitEnemyAmmo();//�G�̒e�ɓ��������ꍇ
	void hyoji(int& cameraX);//�\��
	int getHP();//HP�Q�b�g
	int tamakazu;

	Shoot tama[100];//�e�z��
private:
	int hp;//hp
	int fontHandle;//�t�H���g�T�C�Y
	int playerAnimeSituation;//�A�j���[�V�����Ǘ�
	int player_chaka[6];//�v���C���[�s�X�g����Ԃ̉摜
	int player_AK[3];//�v���C���[AK��Ԃ̉摜
	int player_minigun[19];//�v���C���[	�~�j�K����Ԃ̉摜
	int player_robot[4];//�v���C���[�����`�Ԃ̉摜
	int minigun_shot[4];//�~�j�K�������̉摜�G
	int laser_charge[5]; //���[�U�[�`���[�W
	int laser;//���[�U�[�̉摜
	
	int shotx;//�e����x���W�ݒ�
	int shoty;//�e����y���W�ݒ�
	int money;//������

	bool now_reload = false;//�����[�h�����ǂ���
	bool changeReloadTime;//����ύX���̃����[�h�^�C���ύX
	bool createWeapon;//����(Shoot)�̃C���X�^���X���������[�v���Ȃ��悤��
	bool minigunShot;//�~�j�K���������Ƃ��̃A�j���[�V��������
	bool laserChargenow;//���[�U�[�`���[�W�A�j���[�V����
	bool laserShot;//�r�[���������Ƃ��̃A�j���[�V��������
	bool canMove;

	int jump;//�W�����v��
	int shotSound;//���ˉ�
	int reloadSound;//�����[�h��
	int kara;//��ł���
	int shotImage;//�e�摜
	int minigunStartSound;//�~�j�K�����˃X�^�[�g��
	int minigunEndSound;//�~�j�K�����ˏI����
	int minigunLoopSound;//�~�j�K����]��
	int laserChargeSound;//���[�U�[�`���[�W��
	int laserShotSound;//���[�U�[���ˉ�
	int laserStopSound;//���[�U�[��~��
	int laserLoopSound;//���[�U�[�ҋ@��
	int damageSound_1;//�_���[�W1
	int damageSound_2;//�_���[�W2
	int damageSound_3;//�_���[�W3
	int ricochet_1;//���e1
	int ricochet_2;//���e2
	int getItemSound;//�A�C�e���Q�b�g�T�E���h
	int getMoneySound;//�����Q�b�g�T�E���h
	int payMoneySound;//���������T�E���h
	int hitSound;

	void move(int& cameraX, LoadMap& m, int& mapsizeX);//����
	void shot(int& cameraX, int& SizeX, LoadMap& m);//����
	void reload(int& tamakazu);//�����[�h
	void changeWeapon();//����ύX
	int createWeapons();//Shoot�̃C���X�^���X�������\�b�h
	
};

