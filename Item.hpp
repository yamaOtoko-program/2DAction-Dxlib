#pragma once
class Item
{
public:
	int x;//x座標
	int y;//y座標
	int sizeX;
	int sizeY;
	int type;//アイテムタイプ 4がマリファナ、5がクロコダイル。
	Item();//コンストラクタ
	void itemSet(int& x, int& y, int& type);//アイテムの座標とタイプを格納
	void update(int& cameraX);//全体のメソッド
	void get();//消える
	bool flag;//表示か非表示か
private:
	int mari;//アイテム画像格納
	int taima;//アイテム画像格納
	int kuroko;//アイテム画像格納
	
	void hyoji(int& cameraX);//画像表示メソッド
};

