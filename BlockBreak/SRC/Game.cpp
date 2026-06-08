#include "DxLib.h"
#include "Game.h"
#include "Input.h"
#include "SceneMgr.h"
#include "Player.h"
#include "Stage.h"

Game mg;

void Game_Initialize() {
	mg.gameflg = false;
	mg.score = 0;

	mg.ChoiseSE = LoadSoundMem("./Sounds/decision.mp3");
	mg.soundflg = false;

	mg.select = 0;
}

void Game_Finalize() {
	Player_Finalize();
	Stage_Finalize();
	DeleteSoundMem(mg.ChoiseSE);
}

void Game_Update() {
	mg.gameflg = CheckStage();
	if (mg.gameflg == true) {	//ゲーム中
		Player_Update();
		Stage_Update();
	}
	else {	//ゲーム終了

	}

}

void Game_Draw() {
	if (mg.gameflg == true) {	//ゲーム中
		Player_Draw();
		Stage_Draw();
	}
	else {	//ゲーム終了

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