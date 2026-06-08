#pragma once

struct Game {
	int score;

	int select;
	bool gameflg;
	bool soundflg;
	int ChoiseSE;
};

void Game_Initialize();
void Game_Finalize();
void Game_Update();
void Game_Draw();


extern Game mg;