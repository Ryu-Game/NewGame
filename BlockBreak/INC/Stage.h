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

	int frameRight, frameLeft, frameTop;
};

struct Color {
	const int red = 0xff0000;
	const int blue = 0x0000ff;
	const int green = 0x00ff00;
};


void Stage_Initialize();
void Stage_Finalize();
void Stage_Update();
void Stage_Draw();


void Frame_Draw();
void CheckBallBlock(int Pleft, int Ptop, int Pright, int Pbottom);

extern Stage ms;
extern Color cl;