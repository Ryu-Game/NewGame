#pragma once

struct Game {
	bool changeflg;
	int counttime;
	int judgenum;
	/****************
	* •Ï”–¼:judgenum
	* 0:ƒQ[ƒ€’†
	* 1:Ÿ—˜
	* 2:”s–k
	* 3:‚ ‚¢‚±
	****************/

	int soundgamestart;
	int soundsame;
};

struct Player {
	int gh[3];
	int jw = 300, jh = 360;
	double exRate = 0.5;
	int pHand, eHand;
};

extern struct Game mg;
extern struct Player mp;

void Game_Initialize();	//‰Šú‰»
void Game_Finalize();	//I—¹ˆ—
void Game_Update();		//XV
void Game_Draw();		//•`‰æ

void PlayerHands();		//è‚Ìó‘Ôˆ—
void Game_Judge();		//Ÿ”sˆ—