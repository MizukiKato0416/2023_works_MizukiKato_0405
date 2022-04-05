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
#include <XInput.h>
#include "main.h"

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")			//描画に必要
#pragma comment(lib,"d3dx9.lib")		//[d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")		//DirectXコンポーネント(部品)使用に必要
#pragma comment(lib, "winmm.lib")		//fps表示に必要
#pragma comment(lib,"dinput8.lib")		//入力処理に必要
#pragma comment(lib,"xinput.lib")		//pad入力処理に必要

//========================================================
//マクロ定義
//========================================================
#define SCREEN_WIDTH (1280)		//ウィンドウの幅
#define SCREEN_HEIGHT (720)		//ウィンドウの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)				//頂点フォーマット2D
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)		//頂点フォーマット3D
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)										// ウインドウの中心Ｘ座標
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)										// ウインドウの中心Ｙ座標


//========================================================
//画面（モード）の種類
//========================================================
typedef enum
{
	MODE_TITLE = 0,
	MODE_DESCRIPTION,
	MODE_STAGE1,
	MODE_RESULT,
	MODE_MAX
} MODE;

//========================================================
//構造体の定義2D
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//頂点座標
	float rhw;				//1.0fで固定
	D3DCOLOR col;			//頂点カラー
	D3DXVECTOR2 tex;		//	テクスチャ座標
} VERTEX_2D;

//========================================================
//構造体の定義3D
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//頂点座標
	D3DXVECTOR3 nor;		//法線ベクトル
	D3DCOLOR col;			//頂点カラー
	D3DXVECTOR2 tex;		//テクスチャ座標
} VERTEX_3D;


//========================================================
//プロトタイプ宣言
//========================================================
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);
void DrawFPS(void);

#endif // !_MAIN_H_