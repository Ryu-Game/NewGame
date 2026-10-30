#include "DxLib.h"
#include "SceneMgr.h"
#include "Game.h"
#include "Menu.h"

static eScene mScene = eScene_Menu;		//シーン管理変数(デバッグでゲーム開始)
static eScene mNextScene = eScene_None; //次のシーン管理変数

static void SceneMgr_InitializeModule(eScene scene);//指定モジュールを初期化する
static void SceneMgr_FinalizeModule(eScene scene);	//指定モジュールの終了処理を行う

struct SceneMgr mgr;

/******************************
* 初期化処理
*******************************/
void SceneMgr_Initialize() {
	SceneMgr_InitializeModule(mScene);
}

/******************************
* 終了処理
*******************************/
void SceneMgr_Finalize() {
	SceneMgr_FinalizeModule(mScene);
}

/******************************
* 更新処理
*******************************/
void SceneMgr_Update() {
	if (mNextScene != eScene_None) {		//次のシーンがセットされていたら
		SceneMgr_FinalizeModule(mScene);	//現在のシーンの終了処理を実行
		mScene = mNextScene;				//次のシーンを現在のシーンセット
		mNextScene = eScene_None;			//次のシーン情報をクリア
		SceneMgr_InitializeModule(mScene);	//現在のシーンを初期化
	}

	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		DxLib_End();
	}

	switch (mScene) {
		case eScene_Menu:		//メニュー画面
			Menu_Update();
			break;
	case eScene_Game:		//ゲーム画面
		Game_Update();
		break;
	}
}

/******************************
* 描画処理
*******************************/
void SceneMgr_Draw() {
	DrawGraph(0, 0, mgr.BackImg, false);

	switch (mScene) {
	case eScene_Menu: //現在の画面がメニュー画面なら
		Menu_Draw(); 
		break;
	case eScene_Game:
		Game_Draw();
		break;
	}
}

/******************************
* 関数
*******************************/
// 引数 nextScene にシーンを変更する
void SceneMgr_ChangeScene(eScene NextScene) {
	mNextScene = NextScene;	//次のシーンをセットする
}

// 引数sceneモジュールを初期化する
static void SceneMgr_InitializeModule(eScene scene) {
	switch (scene) { //シーンによって処理を分岐
	case eScene_Menu: //指定画面がメニュー画面なら
		Menu_Initialize(); 
		mgr.BackImg = LoadGraph("images/MenuBack.png");
		break;
	case eScene_Game:
		Game_Initialize();
		break;	
	}
}
// 引数sceneモジュールの終了処理を行う
static void SceneMgr_FinalizeModule(eScene scene) {
	switch
		(scene) { //シーンによって処理を分岐
	case eScene_Menu: //指定画面がメニュー画面なら
		Menu_Finalize(); 
		break;

	case eScene_Game:
		Game_Finalize();
		break;
	}
	mgr.BackImg = 0;
}