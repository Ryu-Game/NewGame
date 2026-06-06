#pragma once

struct Menu {
	int BGM;
	int SE;

	int flg;
};

void Menu_Initialize();
void Menu_Finalize();
void Menu_Update();
void Menu_Draw();

extern Menu mm;