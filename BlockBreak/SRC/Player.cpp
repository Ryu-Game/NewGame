#include "DxLib.h"
#include "Player.h"
#include "SceneMgr.h"
#include "Input.h"

Player mp;

void Player_Initialize() {
	//バー座標
	mp.barX = mgr.SCREEN_WIDTH / 2;
	mp.barY = mgr.SCREEN_HEIGHT - 50;

	//ボール座標
	mp.InitPositionX = mgr.SCREEN_WIDTH / 2 - 200;
	mp.InitPositionY = mgr.SCREEN_HEIGHT / 2;
	mp.ballX = mp.InitPositionX;
	mp.ballY = mp.InitPositionY;

	mp.Life = 3;
	mp.breakSE = LoadSoundMem("./Sounds/break.mp3");
}

void Player_Finalize() {

}

void Player_Update() {

}

void Player_Draw() {

}

void MoveBall() {

}

bool CheckHitBox(int Pleft, int Ptop, int Pright, int Pbottom, int Eleft, int Etop, int Eright, int Ebottom) {

}