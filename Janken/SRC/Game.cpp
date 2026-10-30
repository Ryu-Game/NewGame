#include "DxLib.h"
#include "Game.h"
#include "SceneMgr.h"

struct Game mg;
struct Player mp;

void Game_Initialize() {
	LoadDivGraph("images/janken.png", 3, 3, 1, mp.jw, mp.jh, mp.gh);
	mg.changeflg = true;
	mg.counttime = rand();
	mg.judgenum = 4;
}


void Game_Finalize() {
	
}


void Game_Update() {
	
	PlayerHands();
	Game_Judge();
}


void Game_Draw() {
	SetFontSize(60);
	DrawBox(0, 0, mgr.SCREEN_WIDTH, mgr.SCREEN_HEIGHT / 2, 0xff0000, 1);			//上半分赤を表示
	DrawBox(0, mgr.SCREEN_HEIGHT / 2, mgr.SCREEN_WIDTH, mgr.SCREEN_HEIGHT, 0x0000ff, 1);	//上半分青を表示

	//エネミー表示
	DrawRotaGraph(mgr.SCREEN_WIDTH / 2, mp.jh * mp.exRate - 50, mp.exRate, 0, mp.gh[mp.eHand], 1, 0);

	//Player表示
	DrawRotaGraph(mgr.SCREEN_WIDTH / 2, mp.jh+30, mp.exRate, 0, mp.gh[mp.pHand], 1, 0);

	//勝敗描画
	switch (mg.judgenum) {
	case 0:
		DrawString(mgr.SCREEN_WIDTH / 2, mgr.SCREEN_HEIGHT - 120, "あいこで・・・", 0xffffff);
		break;
	case 1:
		DrawString(30, mgr.SCREEN_HEIGHT - 120, "勝ち！", 0xffffff);
		break;
	case 2:
		DrawString(30, mgr.SCREEN_HEIGHT - 120, "負け…", 0xffffff);
		break;
	}
}

void PlayerHands() {
	//ランダム描画処理
	if (mg.changeflg) {
		mp.eHand = ++mg.counttime / 5 % 3;
		mp.pHand = ++mg.counttime / 5 % 3;
	}

	//PlayerHand処理
	if (mg.changeflg) {
		if (CheckHitKey(KEY_INPUT_1) != 0 ||
			CheckHitKey(KEY_INPUT_2) != 0 ||
			CheckHitKey(KEY_INPUT_3) != 0) {
			if (CheckHitKey(KEY_INPUT_1) != 0) {
				mp.pHand = 0;
			}
			else if (CheckHitKey(KEY_INPUT_2) != 0) {
				mp.pHand = 1;
			}
			else if (CheckHitKey(KEY_INPUT_3) != 0) {
				mp.pHand = 2;
			}
			mg.changeflg = false;
		}
	}
}

void Game_Judge() {
	if (!mg.changeflg) {
		if (mg.judgenum == 4) {

			int ehand_Judge = mp.eHand;
			if (ehand_Judge == 0) {
				ehand_Judge = 3;
			}
			//あいこ
			if (mp.pHand == mp.eHand) {
				mg.judgenum = 0;
			}
			//勝ち
			else if (mp.pHand == ehand_Judge - 1) {
				mg.judgenum = 1;
			}
			//負け
			else {
				mg.judgenum = 2;
			}

		}
		if (CheckHitKey(KEY_INPUT_SPACE) != 0) {
			mg.judgenum = 4;			
			mg.changeflg = true;
		}
	}
}