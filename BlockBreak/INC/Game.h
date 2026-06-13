#pragma once

struct Game {
	int score;

	int select;
	bool gameflg;
	bool pouseflg;
	bool soundflg;
	int ChoiseSE;
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