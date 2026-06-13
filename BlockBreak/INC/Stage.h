#pragma once

#define STAGEX_MAX 6
#define STAGEY_MAX 6
#define none 0

struct Stage {
	int data[6][6];
	bool flg;
	int InitX;
	int StageSizeX;
	int StageSizeY = 10;
	
	int Color;

	int frameRight, frameLeft, frameTop, frameBottom;
};

void Stage_Initialize();
void Stage_Finalize();
void Stage_Update();
void Stage_Draw();

void CheckBallBlock(int Pleft, int Ptop, int Pright, int Pbottom);

extern Stage ms;