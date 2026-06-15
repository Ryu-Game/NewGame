#pragma once

struct Game {
	int score;		//得点

	int select;		//画面選択(0:Game, 1:Pouse, 2: Menu)
	bool gameflg;	//ゲームクリア判定
	bool pouseflg;	//ポーズ画面判定
	bool soundflg;	//サウンド流れているか判定
	int ChoiseSE;	//SE
};

void Game_Initialize();
void Game_Finalize();
void Game_Update();
void Game_Draw();

void Result_Update();
void Result_Draw();
void Pouse_Update();
void Pouse_Draw();

bool CheckStage();

extern Game mg;