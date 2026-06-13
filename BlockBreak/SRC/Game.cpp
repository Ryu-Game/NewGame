#include "DxLib.h"
#include "Game.h"
#include "Input.h"
#include "SceneMgr.h"
#include "Player.h"
#include "Stage.h"

Game mg;

void Game_Initialize() {
	mg.gameflg = true;
	mg.score = 0;

	mg.ChoiseSE = LoadSoundMem("./Sounds/decision.mp3");
	mg.soundflg = false;

	mg.select = 0;
	mg.pouseflg = false;

	Player_Initialize();
	Stage_Initialize();
}

void Game_Finalize() {
	Player_Finalize();
	Stage_Finalize();
	DeleteSoundMem(mg.ChoiseSE);
}

void Game_Update() {
	mg.gameflg = CheckStage();
	if (mg.gameflg == true) {	//ゲーム中
		if (mg.pouseflg != true) {	//ゲーム画面
			Player_Update();
			Stage_Update();

			//ポーズ画面設定
			if (KeyFlg[KEY_INPUT_SPACE]) {
				PlaySoundMem(mg.ChoiseSE, DX_PLAYTYPE_BACK);
				mg.soundflg = true;
			}
			else if (CheckSoundMem(mg.ChoiseSE) == 0 && mg.soundflg == true) {
				mg.pouseflg = true;
				mg.soundflg = false;
			}
		}
		else {	//ポーズ画面
			Pouse_Update();
		}
		
	}
	else {	//ゲーム終了
		Result_Update();
	}

}

void Game_Draw() {
	if (mg.gameflg == true) {	//ゲーム中
		if (mg.pouseflg != true) {	//ゲーム画面
			Player_Draw();
			Stage_Draw();
		}
		else {	//ポーズ画面
			Pouse_Draw();
		}
	}
	else {	//ゲーム終了
		Result_Draw();
	}
}

bool CheckStage() {
	for (int StageY = 0; StageY < STAGEY_MAX; StageY++) {
		for (int StageX = 0; StageX < STAGEX_MAX; StageX++) {
			//ブロックがあるかどうか
			if (ms.data[StageY][StageX] != none) {
				return true;
			}
		}
	}

	//ブロック全破壊
	return false;
}

void Result_Update() {
	if (KeyFlg[KEY_INPUT_ESCAPE]) {
		PlaySoundMem(mg.ChoiseSE, DX_PLAYTYPE_BACK);
		mg.soundflg = true;
		mg.select = 1;
	}
	else if (KeyFlg[KEY_INPUT_SPACE]) {
		PlaySoundMem(mg.ChoiseSE, DX_PLAYTYPE_BACK);
		mg.soundflg = true;
		mg.select = 2;
	}

	if (CheckSoundMem(mg.ChoiseSE) == 0 && mg.soundflg == true) {
		switch (mg.select) {
		case 1:
			SceneMgr_ChangeScene(eScene_Game);
			break;
		case 2:
			SceneMgr_ChangeScene(eScene_Menu);
			break;
		}
	}
}

void Result_Draw() {
	SetFontSize(50);
	int fontX = mgr.SCREEN_WIDTH / 2;
	int fontY = mgr.SCREEN_HEIGHT / 2;
	DrawString(fontX - 75, fontY - 75, "RESULT", 0xffffff);
	DrawFormatString(fontX - 100, fontY, 0xffffff, "Score: %d", mg.score);
	DrawString(fontX - 225, fontY + 75, "- PUSH[ESC] GAME -", 0xffffff);
	DrawString(fontX - 250, fontY + 150, "- PUSH[SPACE] MENU -", 0xffffff);
}

void Pouse_Update() {
	if (KeyFlg[KEY_INPUT_ESCAPE]) {
		PlaySoundMem(mg.ChoiseSE, DX_PLAYTYPE_BACK);
		mg.soundflg = true;
		mg.select = 1;
	}
	else if (KeyFlg[KEY_INPUT_SPACE]) {
		PlaySoundMem(mg.ChoiseSE, DX_PLAYTYPE_BACK);
		mg.soundflg = true;
		mg.select = 2;
	}

	if (CheckSoundMem(mg.ChoiseSE) == 0 && mg.soundflg ==true) {
		switch (mg.select) {
		case 1:
			mg.pouseflg = false;
			mg.soundflg = false;
			break;
		case 2:
			SceneMgr_ChangeScene(eScene_Menu);
			break;
		}
	}
}

void Pouse_Draw() {
	SetFontSize(50);
	int fontX = mgr.SCREEN_WIDTH / 2;
	int fontY = mgr.SCREEN_HEIGHT / 2;
	DrawString(fontX - 75, fontY - 150, "POUSE", 0xffffff);
	DrawString(fontX - 225, fontY - 50, "- PUSH[ESC] GAME -", 0xffffff);
	DrawString(fontX - 250, fontY + 50, "- PUSH[SPACE] MENU -", 0xffffff);
}