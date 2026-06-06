#include "DxLib.h"
#include "Game.h"
#include "Input.h"
#include "SceneMgr.h"

#include <string.h>

Game mg;
Player mp;
Stage ms;

static int tempdata[6][6]{
	{ 1,2,3,1,2,3 },
	{ 2,3,1,2,3,1 },
	{ 3,1,2,3,1,2 },
	{ 1,2,3,1,2,3 },
	{ 2,3,1,2,3,1 },
	{ 3,1,2,3,1,3 }
};

void Game_Initialize() {
	memcpy(ms.data, tempdata, sizeof(tempdata));
	ms.flg = 0;

	ms.frameRight = mgr.SCREEN_WIDTH / 2 + mgr.SCREEN_WIDTH / 4;
	ms.frameLeft = mgr.SCREEN_WIDTH / 2 - mgr.SCREEN_WIDTH / 4;
	ms.frameTop = 0;

	ms.InitX = mgr.SCREEN_WIDTH / 2 - mgr.SCREEN_WIDTH / 4;
	ms.StageSizeX = (mgr.SCREEN_WIDTH / 2) / 6;

	mp.bar_x = mgr.SCREEN_WIDTH / 2;
	mp.bar_y = mgr.SCREEN_HEIGHT - 50;
	
	mp.InitPositionX = mgr.SCREEN_WIDTH / 2 - 200;
	mp.InitPositionY = mgr.SCREEN_HEIGHT / 2;
	mp.ball_x = mp.InitPositionX;
	mp.ball_y = mp.InitPositionY;

	mp.Life = 3;
	mg.score = 0;
	mp.breakSE = LoadSoundMem("./Sounds/break.mp3");
	mg.ChoiseSE = LoadSoundMem("./Sounds/decision.mp3");
}

void Game_Finalize() {

}

void Game_Update() {
	if (KeyFlg[KEY_INPUT_RETURN]) {
		SceneMgr_ChangeScene(eScene_Menu);
	}

	ms.flg = 2;
	for (int Sy = 0; Sy < STAGEY_MAX; Sy++) {
		for (int Sx = 0; Sx < STAGEX_MAX; Sx++) {
			if (ms.data[Sy][Sx] != 0) {
				ms.flg = 0;
				break;
			}
		}
		if (ms.flg == 0) {	//ゲーム中
			break;
		}
		//全部破壊していたら終了判定
		else if ((ms.flg == 2 && Sy == 5)
				|| mp.Life == 0) {
			ms.flg = 1;
		}
	}

	Player_Update();

	MoveBall();

	if (mp.ball_y >= mgr.SCREEN_HEIGHT) {
		mp.Life--;
		mp.ball_x = mp.InitPositionX;
		mp.ball_y = mp.InitPositionY;
		if (mp.ball_speedX < 0) {
			mp.ball_speedX *= -1;
		}
		WaitTimer(500);
	}

	if (ms.flg == 1) {
		WaitTimer(500);
		SceneMgr_ChangeScene(eScene_Menu);
	}
}

void Game_Draw() {
	FrameDraw();
	StageDraw();

	Player_Draw();

	SetFontSize(35);
	int fontX = mgr.SCREEN_WIDTH / 2 + mgr.SCREEN_WIDTH / 4 + 100;
	int fontY = mgr.SCREEN_HEIGHT / 2;
	DrawFormatString(fontX - 75,fontY - 50, 0xffffff, "Score: %d", mg.score);
	for (int life = 0; life < mp.Life; life++) {
		DrawString(fontX + 35 * life, fontY, "〇", 0xffffff);
	}
}

void FrameDraw() {
	int Fright, Fleft, Ftop, Fbuttom;
	int Ffour = mgr.SCREEN_WIDTH / 4;
	Fright = mgr.SCREEN_WIDTH / 2 + Ffour;
	Fleft = mgr.SCREEN_WIDTH / 2 - Ffour;
	Ftop = 0;
	Fbuttom = mgr.SCREEN_HEIGHT;

	DrawBox(Fleft, Ftop, Fright, Fbuttom, 0xffffff, false);
}

void StageDraw() {
	int BlockX, BlockY;

	int Color = 0xffffff;
	int red = 0xff0000;
	int blue = 0x0000ff;
	int green = 0x00ff00;
	for (int Sy = 0; Sy < STAGEY_MAX; Sy++) {
		for (int Sx = 0; Sx < STAGEX_MAX; Sx++) {
			if (ms.data[Sy][Sx] != 0) {
				if (ms.data[Sy][Sx] == 1) {
					Color = red;
				}
				else if (ms.data[Sy][Sx] == 2) {
					Color = blue;
				}
				else if (ms.data[Sy][Sx] == 3) {
					Color = green;
				}
				BlockX = ms.InitX + ms.StageSizeX * Sx;
				BlockY = ms.StageSizeY * Sy;
				DrawBox(BlockX, BlockY, BlockX + ms.StageSizeX, BlockY + ms.StageSizeY, Color, true);
			}
		}
	}
}

void Player_Update() {
	
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		mp.bar_x += 3;
		if (mp.bar_x + mp.barSize > ms.frameRight) {
			mp.bar_x -= 3;
		}
	}
	else if (CheckHitKey(KEY_INPUT_LEFT)) {
		mp.bar_x -= 3;
		if (mp.bar_x - mp.barSize < ms.frameLeft) {
			mp.bar_x += 3;
		}
	}
}

void Player_Draw() {
	DrawBox(mp.bar_x - mp.barSize, mp.bar_y, mp.bar_x + mp.barSize, mp.bar_y + 10, 0xffffff, false);

	DrawCircle(mp.ball_x, mp.ball_y, mp.ballSize, 0xffffff, false);


	SetFontSize(20);
	DrawFormatString(0, 20, 0xffffff, "%d", mp.ball_y);
}


void MoveBall() {
	mp.ball_x += mp.ball_speedX;
	mp.ball_y += mp.ball_speedY;

	int Pleft, Ptop, Pright, Pbottom;
	Pleft = mp.ball_x - mp.ballSize;
	Ptop = mp.ball_y - mp.ballSize;
	Pright = mp.ball_x + mp.ballSize;
	Pbottom = mp.ball_y + mp.ballSize;
	CheckBallBlock(Pleft, Ptop, Pright, Pbottom);
	
	//壁との当たり判定
	if ((mp.ball_x + mp.ballSize > ms.frameRight) ||
		(mp.ball_x - mp.ballSize < ms.frameLeft)) {
		PlaySoundMem(mp.breakSE, DX_PLAYTYPE_BACK);
		mp.ball_speedX *= -1;
		mp.ball_x += mp.ball_speedX;
	}
	else if (mp.ball_y - mp.ballSize < 0) {
		PlaySoundMem(mp.breakSE, DX_PLAYTYPE_BACK);
		mp.ball_speedY *= -1;
		mp.ball_y = mp.ballSize * 2 + 1;
	}

	//プレイヤーとの当たり判定
	mp.ballflg = CheckHitBox(Pleft, Ptop, Pright, Pbottom, mp.bar_x - mp.barSize, mp.bar_y, mp.bar_x + mp.barSize, mp.bar_y + 10);
	if (mp.ballflg == true) {
		PlaySoundMem(mp.breakSE, DX_PLAYTYPE_BACK);
		mp.ball_speedY *= -1;
		mp.ball_y = mp.bar_y - mp.ballSize;
		mp.ballflg = false;
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

void CheckBallBlock(int Pleft, int Ptop, int Pright, int Pbottom) {
	int Bleft, Btop, Bright, Bbottom;
	//ブロックとの当たり判定
	for (int Sy = 0; Sy < STAGEY_MAX; Sy++) {
		for (int Sx = 0; Sx < STAGEX_MAX; Sx++) {
			if (ms.data[Sy][Sx] != 0) {
				Bleft = ms.InitX + ms.StageSizeX * Sx;
				Btop = ms.StageSizeY * Sy;
				Bright = Bleft + ms.StageSizeX;
				Bbottom = Btop + ms.StageSizeY;

				mp.ballflg = CheckHitBox
				(Pleft, Ptop, Pright, Pbottom,
					Bleft, Btop, Bright, Bbottom);

				if (mp.ballflg == true) {
					mg.score += ms.data[Sy][Sx] * 100;
					ms.data[Sy][Sx] = 0;
					mp.ball_speedY *= -1;
					mp.ball_y += mp.ball_speedY;
					PlaySoundMem(mp.breakSE, DX_PLAYTYPE_BACK);
					break;
				}
			}
		}
		if (mp.ballflg == true) {
			break;
		}
	}

	//判定終了後もとにもどす
	mp.ballflg = false;
}
