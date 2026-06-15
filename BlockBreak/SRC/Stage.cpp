#include "DxLib.h"
#include "Stage.h"
#include "Common.h"
#include "SceneMgr.h"
#include "Player.h"
#include "Game.h"

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
	ms.frameRight = (int)(mgr.SCREEN_WIDTH / 2) + (int)(mgr.SCREEN_WIDTH / 4);
	ms.frameLeft = (int)(mgr.SCREEN_WIDTH / 2) - (int)(mgr.SCREEN_WIDTH / 4);
	ms.frameTop = 0;
	ms.frameBottom = mgr.SCREEN_HEIGHT;
	ms.InitX = (int)(mgr.SCREEN_WIDTH / 2) - (int)(mgr.SCREEN_WIDTH / 4);

	//ステージ描画サイズ
	ms.StageSizeX = (int)((mgr.SCREEN_WIDTH / 2) / 6);

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
	//プレイヤー座標格納
	int Pleft, Ptop, Pright, Pbottom;
	Pleft = mp.ballX - mp.ballSize;
	Ptop = mp.ballY - mp.ballSize;
	Pright = mp.ballX + mp.ballSize;
	Pbottom = mp.ballY + mp.ballSize;
	CheckBallBlock(Pleft, Ptop, Pright, Pbottom);
}

void Stage_Draw() {
	//ブロック描画処理
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
				else if (ms.data[Sy][Sx] == 0) {
					ms.Color = color.green;
				}
				BlockX = ms.InitX + ms.StageSizeX * Sx;
				BlockY = ms.StageSizeY * Sy;
				DrawBox(BlockX, BlockY, BlockX + ms.StageSizeX, BlockY + ms.StageSizeY, ms.Color, true);
			}
		}
	}
	DrawBox(ms.frameLeft, ms.frameTop, ms.frameRight, ms.frameBottom, color.white, false);

	//得点・ライフ描画
	int fontsize = 35;
	SetFontSize(fontsize);
	int fontX = (int)(mgr.SCREEN_WIDTH / 2) + (int)(mgr.SCREEN_WIDTH / 4);
	int fontY = (int)(mgr.SCREEN_HEIGHT / 2);
	DrawString(fontX + 10, fontY - 50, "Score:", color.white);
	DrawFormatString(fontX + 10 + (int)(fontsize * 1.5) + fontsize * 2, fontY - 50, color.white, "%d", mg.score);
	for (int life = 0; life < mp.Life; life++) {
		DrawString(fontX + 10 + fontsize * life, fontY, "〇", color.white);
	}

	DrawString(fontX + 10, fontY + 50, "PUSH [SPACE]", color.white);
	DrawString(fontX + 10, fontY + 85, "POUSE", color.white);
}

//ボールとブロックの当たり判定処理
void CheckBallBlock(int Pleft, int Ptop, int Pright, int Pbottom) {
	int Bleft, Btop, Bright, Bbottom;
	
	//ブロック探索
	int startX = (int)((Pleft - ms.InitX) / ms.StageSizeX);
	int endX = (int)((Pright - ms.InitX) / ms.StageSizeX);
	int startY = (int)(Ptop / ms.StageSizeY);
	int endY = (int)(Pbottom / ms.StageSizeY);

	//範囲補正
	if (startX < 0)startX = 0;
	if (startY < 0)startY = 0;
	if (endX >= STAGEX_MAX)endX = STAGEX_MAX - 1;
	if (endY >= STAGEY_MAX)endY = STAGEY_MAX - 1;

	for (int Sy = startY; Sy <= endY; Sy++) {
		for (int Sx = startX; Sx <= endX; Sx++) {
			//ブロックが無ければスキップ
			if (ms.data[Sy][Sx] == 0) {
				continue;
			}

			//座標計算
			Bleft = ms.InitX + (Sx * ms.StageSizeX);
			Btop = Sy * ms.StageSizeY;
			Bright = Bleft + ms.StageSizeX;
			Bbottom = Btop + ms.StageSizeY;

			//当たり判定
			if (CheckHitBox(Pleft, Ptop, Pright, Pbottom,
				Bleft, Btop, Bright, Bbottom)) {
				PlaySoundMem(mp.breakSE, DX_PLAYTYPE_BACK);
				mg.score += ms.data[Sy][Sx] * 10;
				ms.data[Sy][Sx] = 0;
				mp.ballSpeedY *= -1;

				return;
			}

		}
	}
}