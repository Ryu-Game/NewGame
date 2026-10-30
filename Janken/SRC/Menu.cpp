#include "DxLib.h"
#include "Menu.h"
#include "SceneMgr.h"
#include "Input.h"

void Menu_Initialize() {

}

void Menu_Finalize() {

}

void Menu_Update(){
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		SceneMgr_ChangeScene(eScene_Game);
	}
}

void Menu_Draw() {
	SetFontSize(50);
	DrawString(mgr.SCREEN_WIDTH/2- 120, mgr.SCREEN_HEIGHT/2 - 50, " SPASEキー\nゲーム開始", 0xffffff);
}