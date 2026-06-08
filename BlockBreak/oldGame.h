#pragma once
#define STAGEX_MAX 6
#define STAGEY_MAX 6

struct Game {
	int score;

	int select;
	bool soundflg;
	int ChoiseSE;
};

struct Player {
	int bar_x, bar_y;
	int bullet_x, bullet_y;
	const int barSize = 32;
	int InitPositionX , InitPositionY;
	int Life;

	int ball_x, ball_y;
	const int ballSize = 8;
	bool ballflg;
	int ball_speedY = 3;
	int ball_speedX = 2;

	int breakSE;
};

struct Stage {
	int data[6][6];
	int flg;	//0:ゲーム中 1:ゲーム終了 2:探索中
	int InitX;
	int StageSizeX;
	int StageSizeY = 10;

	int frameRight, frameLeft, frameTop;
};

void Game_Initialize();
void Game_Finalize();
void Game_Update();
void Game_Draw();

void FrameDraw();
void StageDraw();

void Player_Update();
void Player_Draw();

bool CheckHitBox(int Pleft, int Ptop, int Pright, int Pbottom, int Eleft, int Etop, int Eright, int Ebottom);

void MoveBall();
void CheckBallBlock(int Pleft, int Ptop, int Pright, int Pbottom);

extern Player mp;
extern Stage ms;
extern Game mg;