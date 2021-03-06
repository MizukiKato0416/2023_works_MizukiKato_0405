//=======================================================================
//メイン(システム系)処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#ifndef _MAIN_H_
#define _MAIN_H_

//インクルードファイル
#include <windows.h>
#include "d3dx9.h"			//描画に必要
#define DIRECTINPUT_VERSION (0x0800)	//ビルド時の警告対応処理用マクロ
#include "dinput.h"						//入力処理に必要
#include "xaudio2.h"					//サウンド処理に必要
#include <time.h>

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")			//描画に必要
#pragma comment(lib,"d3dx9.lib")		//[d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")		//DirectXコンポーネント(部品)使用に必要
#pragma comment(lib,"dinput8.lib")		//入力処理に必要

//========================================================
//マクロ定義
//========================================================
#define SCREEN_WIDTH (1280)		//ウィンドウの幅
#define SCREEN_HEIGHT (720)		//ウィンドウの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)


//========================================================
//画面（モード）の種類
//========================================================
typedef enum
{
	MODE_TITLE = 0,
	MODE_RULE,
	MODE_TUTORIAL,
	MODE_STAGE1,
	MODE_GAME,
	MODE_STAGE3,
	MODE_RESULT,
	MODE_GAMEOVER,
	MODE_MAX
} MODE;

//========================================================
//プロトタイプ宣言
//========================================================
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);

//========================================================
//構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//頂点座標
	float rhw;				//1.0fで固定
	D3DCOLOR col;			//頂点カラー
	D3DXVECTOR2 tex;		//	テクスチャ座標
} VERTEX_2D;


#endif // !_MAIN_H_