#include "DxLib.h"
#include "Menu.h"
#include "Input.h"
#include "SceneMgr.h"

Menu mm;

void Menu_Initialize() {
	mm.SE = LoadSoundMem("./Sounds/decision.mp3");

	mm.flg = 0;
}

void Menu_Finalize() {
	DeleteSoundMem(mm.SE);
}

void Menu_Update() {
	if (KeyFlg[KEY_INPUT_SPACE]) {
		PlaySoundMem(mm.SE, DX_PLAYTYPE_BACK);
		mm.flg = 1;
	}
	else if (KeyFlg[KEY_INPUT_ESCAPE]) {
		PlaySoundMem(mm.SE, DX_PLAYTYPE_BACK);
		mm.flg = 2;
	}

	if (CheckSoundMem(mm.SE) == 0 && mm.flg != 0) {
		switch (mm.flg) {
		case 1:
			SceneMgr_ChangeScene(eScene_Game);
			break;
		case 2:
			DxLib_End();
			break;
		}
	}
}

void Menu_Draw() {
	SetFontSize(50);
	DrawString((mgr.SCREEN_WIDTH / 2) - (50 * 3), mgr.SCREEN_HEIGHT / 2 - 150, "-BlockBreak-", 0xffffff);
	DrawString((mgr.SCREEN_WIDTH / 2) - (50 * 4), mgr.SCREEN_HEIGHT / 2, "- PUSH [SPACE] -", 0xffffff);
	DrawString((mgr.SCREEN_WIDTH / 2) - (50 * 4.5), mgr.SCREEN_HEIGHT / 2 + 150, "- PUSH [ESC] END -", 0xffffff);

	
}