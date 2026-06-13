#include "DxLib.h"
#include "Player.h"
#include "SceneMgr.h"
#include "Input.h"
#include "Stage.h"

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
	DeleteSoundMem(mp.breakSE);
}

void Player_Update() {
	MoveBar();
	MoveBall();
}

void Player_Draw() {
	//バー描画
	DrawBox(mp.barX - mp.barSize, mp.barY, mp.barX + mp.barSize, mp.barY + 10, 0xffffff, false);

	//ボール描画
	DrawCircle(mp.ballX, mp.ballY, mp.ballSize, 0xffffff, false);
}

void MoveBar() {
	int embed = mp.barSpeed + 1;
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		mp.barX += mp.barSpeed;
		if (mp.barX + mp.barSize > ms.frameRight) {
			mp.barX -= embed;
		}
	}
	else if (CheckHitKey(KEY_INPUT_LEFT)) {
		mp.barX -= mp.barSpeed;
		if (mp.barX - mp.barSize < ms.frameLeft) {
			mp.barX += embed;
		}
	}
}

void MoveBall() {
	mp.ballX += mp.ballSpeedX;
	mp.ballY += mp.ballSpeedY;

	int Pleft, Ptop, Pright, Pbottom;
	Pleft = mp.ballX - mp.ballSize;
	Ptop = mp.ballY - mp.ballSize;
	Pright = mp.ballX + mp.ballSize;
	Pbottom = mp.ballY + mp.ballSize;

	//壁との当たり判定
	if ((mp.ballX + mp.ballSize > ms.frameRight) ||
		(mp.ballX - mp.ballSize < ms.frameLeft)) {
		PlaySoundMem(mp.breakSE, DX_PLAYTYPE_BACK);
		mp.ballSpeedX *= -1;
		mp.ballX += mp.ballSpeedX;
	}
	else if (mp.ballY - mp.ballSize < 0) {
		PlaySoundMem(mp.breakSE, DX_PLAYTYPE_BACK);
		mp.ballSpeedY *= -1;
		mp.ballY = mp.ballSize * 2 + 1;
	}

	//プレイヤーとの当たり判定
	if (CheckHitBox(Pleft, Ptop, Pright, Pbottom, mp.barX - mp.barSize, mp.barY, mp.barX + mp.barSize, mp.barY + 10)) {
		PlaySoundMem(mp.breakSE, DX_PLAYTYPE_BACK);
		mp.ballSpeedY *= -1;
		mp.ballY = mp.barY - mp.ballSize;
	}
}

bool CheckHitBox(int Pleft, int Ptop, int Pright, int Pbottom, int Eleft, int Etop, int Eright, int Ebottom) {
	if (Pright > Eleft &&
		Pleft < Eright &&
		Pbottom > Etop &&
		Ptop < Ebottom) {
		return true;
	}
	else {
		return false;
	}
}