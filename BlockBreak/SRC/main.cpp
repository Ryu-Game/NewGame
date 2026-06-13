#include "DxLib.h"
#include "SceneMgr.h"
#include "Common.h"
#include "Input.h"

Color color;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE);	//ウィンドウモード変更
	DxLib_Init();	//Dxライブラリ初期化
	SetGraphMode(mgr.SCREEN_WIDTH, mgr.SCREEN_HEIGHT, 32);	//画面サイズ
	SetDrawScreen(DX_SCREEN_BACK);	//裏画面設定
	SetUseCharCodeFormat(DX_CHARCODEFORMAT_SHIFTJIS);
	SceneMgr_Initialize();	//初期シーン
	while (ProcessMessage() == 0) {
		ClearDrawScreen();		//画面初期化

		InputKey();				//入力情報
		SceneMgr_Update();		//更新
		SceneMgr_Draw();		//描画

		

		ScreenFlip();			//画面更新
	}
	SceneMgr_Finalize();		//終了画面

	DxLib_End();
	return 0;
}