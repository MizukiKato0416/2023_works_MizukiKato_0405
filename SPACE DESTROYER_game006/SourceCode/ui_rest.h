//===========================================
//動きのないUIの処理
//Authore:加藤瑞葵
//===========================================
#ifndef _UI_REST_H_
#define _UI_REST_H_
#include "ui.h"

//================================================
//マクロ定義
//================================================
#define UI_REST_MENU_BAND_WIDTH					(SCREEN_WIDTH)			//メニュー画面の帯のポリゴンの幅
#define UI_REST_MENU_BAND_HEIGHT				(SCREEN_HEIGHT)			//メニュー画面の帯のポリゴンの高さ
#define UI_REST_PAUSE_WIDTH						(SCREEN_WIDTH)			//ポーズ画面の枠のポリゴンの幅
#define UI_REST_PAUSE_HEIGHT					(SCREEN_HEIGHT)			//ポーズ画面の枠のポリゴンの高さ
#define UI_REST_GAME_CLEAR_WIDTH				(1112.0f)				//GAMECLEARのポリゴンの幅
#define UI_REST_GAME_CLEAR_HEIGHT				(124.0f)				//GAMECLEARのポリゴンの高さ
#define UI_REST_GAME_OVER_WIDTH					(1112.0f)				//GAMEOVERのポリゴンの幅
#define UI_REST_GAME_OVER_HEIGHT				(124.0f)				//GAMEOVERのポリゴンの高さ
#define UI_REST_TUTORIAL_EXPLANATION_WIDTH		(1230.0f)				//チュートリアルの説明欄のポリゴンの幅
#define UI_REST_TUTORIAL_EXPLANATION_HEIGHT		(184.0f)				//チュートリアルの説明欄のポリゴンの高さ
#define UI_REST_TUTORIAL_EXPLANATION_POS_X		(SCREEN_WIDTH / 2.0f)	//チュートリアルの説明欄のポリゴンのX座標
#define UI_REST_TUTORIAL_EXPLANATION_POS_Y		(628.0f)				//チュートリアルの説明欄のポリゴンのY座標


//================================================
//クラスの定義
//================================================
//クラスの定義
class CUiRest : public CUi
{
public:
	//弾の種類
	typedef enum
	{
		UI_REST_TYPE_NONE = 0,
		UI_REST_TYPE_MENU_BAND,					//メニュー画面の上下にある帯
		UI_REST_TYPE_PAUSE,						//ポーズ画面の枠
		UI_REST_TYPE_DAMAGE_MASK,				//ダメージを受けたときのマスク
		UI_REST_TYPE_TUTORIAL_EXPLANATION_000,	//チュートリアルの説明欄
		UI_REST_TYPE_TUTORIAL_EXPLANATION_001,	//チュートリアルの説明欄
		UI_REST_TYPE_TUTORIAL_EXPLANATION_002,	//チュートリアルの説明欄
		UI_REST_TYPE_TUTORIAL_EXPLANATION_003,	//チュートリアルの説明欄
		UI_REST_TYPE_TUTORIAL_EXPLANATION_004,	//チュートリアルの説明欄
		UI_REST_TYPE_TUTORIAL_EXPLANATION_005,	//チュートリアルの説明欄
		UI_REST_TYPE_GAME_CLEAR,				//ゲームクリア
		UI_REST_TYPE_GAME_OVER,					//ゲームオーバー
		UI_REST_TYPE_MAX
	} UI_REST_TYPE;

	CUiRest();					//コンストラクタ
	~CUiRest();					//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CUiRest *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CUiRest::UI_REST_TYPE);

private:
	//メンバ関数
	D3DXVECTOR3 m_pos;									//ポリゴンの位置
	D3DXVECTOR3	m_size;									//サイズ
	static LPDIRECT3DTEXTURE9 m_pTexture;				//共有テクスチャのポインタ
	UI_REST_TYPE m_nType;								//UIの種類
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_UI_REST_H_