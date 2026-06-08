#include "DxLib.h"
#include "Stage.h"
#include "SceneMgr.h"

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

}

void Stage_Update() {

}

void Stage_Draw() {

}

void Frame_Draw() {

}

void CheckBallBlock(int Pleft, int Ptop, int Pright, int Pbottom) {

}