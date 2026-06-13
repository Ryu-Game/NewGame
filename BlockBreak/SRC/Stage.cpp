#include "DxLib.h"
#include "Stage.h"
#include "Common.h"
#include "SceneMgr.h"
#include "Player.h"

Stage ms;

static int tempdata[STAGEY_MAX][STAGEX_MAX]{
	{ 1,2,3,1,2,3 },
	{ 2,3,1,2,3,1 },
	{ 3,1,2,3,1,2 },
	{ 1,2,3,1,2,3 },
	{ 2,3,1,2,3,1 },
	{ 3,1,2,3,1,3 }
};

void Stage_Initialize() {
	//ステージ情報読み込み
	memcpy(ms.data, tempdata, sizeof(tempdata));
	ms.flg = false;

	//ステージ描画座標
	ms.frameRight = mgr.SCREEN_WIDTH / 2 + mgr.SCREEN_WIDTH / 4;
	ms.frameLeft = mgr.SCREEN_WIDTH / 2 - mgr.SCREEN_WIDTH / 4;
	ms.frameTop = 0;
	ms.InitX = mgr.SCREEN_WIDTH / 2 - mgr.SCREEN_WIDTH / 4;

	//ステージ描画サイズ
	ms.StageSizeX = (mgr.SCREEN_WIDTH / 2) / 6;

}

void Stage_Finalize() {
	//データ削除
	for (int Sy = 0; Sy < STAGEY_MAX; Sy++) {
		for (int Sx = 0; Sx < STAGEX_MAX; Sx++) {
			ms.data[Sy][Sx] = 0;
		}
	}
}

void Stage_Update() {

}

void Stage_Draw() {
	int BlockX, BlockY;

	for (int Sy = 0; Sy < STAGEY_MAX; Sy++) {
		for (int Sx = 0; Sx < STAGEX_MAX; Sx++) {
			if (ms.data[Sy][Sx] != 0) {
				if (ms.data[Sy][Sx] == 1) {
					ms.Color = color.red;
				}
				else if (ms.data[Sy][Sx] == 2) {
					ms.Color = color.blue;
				}
				else if (ms.data[Sy][Sx] == 3) {
					ms.Color = color.green;
				}
				BlockX = ms.InitX + ms.StageSizeX * Sx;
				BlockY = ms.StageSizeY * Sy;
				DrawBox(BlockX, BlockY, BlockX + ms.StageSizeX, BlockY + ms.StageSizeY, ms.Color, true);
			}
		}
	}
}

void Frame_Draw() {
	int Fright, Fleft, Ftop, Fbuttom;
	int Ffour = mgr.SCREEN_WIDTH / 4;
	Fright = mgr.SCREEN_WIDTH / 2 + Ffour;
	Fleft = mgr.SCREEN_WIDTH / 2 - Ffour;
	Ftop = 0;
	Fbuttom = mgr.SCREEN_HEIGHT;

	DrawBox(Fleft, Ftop, Fright, Fbuttom, 0xffffff, false);
}

void CheckBallBlock(int Pleft, int Ptop, int Pright, int Pbottom) {
	int Bleft, Btop, Bright, Bbottom;
	int StageChipX = (int)(mp.ballX / ms.StageSizeX);
	int StageChipY = (int)(mp.ballY / ms.StageSizeY);

	if (ms.data[StageChipY][StageChipX] != 0) {

	}
	
	Bleft = ms.InitX + ms.StageSizeX * StageChipX;
	
}