#include "DxLib.h"
#include "Menu.h"
#include "Input.h"
#include "SceneMgr.h"

void Menu_Initialize() {

}

void Menu_Finalize() {

}

void Menu_Update() {
	if (KeyFlg[KEY_INPUT_SPACE]) {
		SceneMgr_ChangeScene(eScene_Game);
	}
	if (KeyFlg[KEY_INPUT_ESCAPE]) {
		DxLib_End();
	}
}

void Menu_Draw() {
	SetFontSize(50);
	DrawString((mgr.SCREEN_WIDTH / 2) - (50 * 3), mgr.SCREEN_HEIGHT / 2 - 150, "-BlockBreak-", 0xffffff);
	DrawString((mgr.SCREEN_WIDTH / 2) - (50 * 4), mgr.SCREEN_HEIGHT / 2, "- PUSH [SPACE] -", 0xffffff);
	DrawString((mgr.SCREEN_WIDTH / 2) - (50 * 4.5), mgr.SCREEN_HEIGHT / 2 + 150, "- PUSH [ESC] END -", 0xffffff);

	
}