#pragma once

struct Player {
	int ballX, ballY;
	const int ballSize = 8;
	bool ballflg;
	int ballSpeedX = 2;
	int ballSpeedY = 3;
	int InitPositionX, InitPositionY;

	int barX, barY;
	const int barSpeed = 2;
	const int barSize = 32;

	int Life;
	int breakSE;
};

void Player_Initialize();
void Player_Finalize();
void Player_Update();
void Player_Draw();

void MoveBall();
bool CheckHitBox(int Pleft, int Ptop, int Pright, int Pbottom, int Eleft, int Etop, int Eright, int Ebottom);

extern Player mp;