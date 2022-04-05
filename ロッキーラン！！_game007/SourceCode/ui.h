//===========================================
//UI処理
//Authore:寺下琉生
//===========================================
#ifndef _UI_H_
#define _UI_H_
#include "scene2D.h"

//================================================
//マクロ定義
//================================================

//================================================
//前方宣言
//================================================
class CControl;

//================================================
//クラスの定義
//================================================
//クラスの定義
class CUi : public CScene2D
{
public:
	typedef enum
	{
		UI_TYPE_TITLE_LOGO,					//タイトルロゴ
		UI_TYPE_TITLE_PRESS,				//タイトルUI:Press文字
		UI_TYPE_TITLE_PLAYER_1P,			//タイトルUI:1P
		UI_TYPE_TITLE_PLAYER_2P,			//タイトルUI:2P

		UI_TYPE_MENU_LOGO,					//メニューロゴ
		UI_TYPE_MENU_STAR,					//メニューUI:星
		UI_TYPE_MENU_SELECT_TUTORIAL,		//メニューUI:選択肢(チュートリアル)
		UI_TYPE_MENU_SELECT_GAME,			//メニューUI:選択肢(ゲームスタート)
		UI_TYPE_MENU_SELECT_BACKTITLE,		//メニューUI:選択肢(タイトルに戻る)
		UI_TYPE_MENU_EXPLANATION_TUTORIAL,	//メニューUI:選択肢の説明(チュートリアル)
		UI_TYPE_MENU_EXPLANATION_GAME,		//メニューUI:選択肢の説明(ゲームスタート)
		UI_TYPE_MENU_EXPLANATION_BACKTITLE,	//メニューUI:選択肢の説明(タイトルに戻る)

		UI_TYPE_TUTORIAL_EXPLANATION,		//チュートリアルUI:操作説明

		UI_TYPE_GAME_COUNTDOWN03,			//ゲームUI:カウントダウン3
		UI_TYPE_GAME_COUNTDOWN02,			//ゲームUI:カウントダウン2
		UI_TYPE_GAME_COUNTDOWN01,			//ゲームUI:カウントダウン1
		UI_TYPE_GAME_START,					//ゲームUI:スタート
		UI_TYPE_GAME_GOAL,					//ゲームUI:ゲームクリア
		UI_TYPE_GAME_TIME_UP,				//ゲームUI:タイムアップ
		UI_TYPE_GAME_TIME_COMMA,			//ゲームUI:タイム(カンマ)

		UI_TYPE_RESULT_WIN,					//リザルトUI:Win
		UI_TYPE_RESULT_RANKING01,			//リザルトUI:ランキング1位
		UI_TYPE_RESULT_RANKING02,			//リザルトUI:ランキング2位
		UI_TYPE_RESULT_RANKING03,			//リザルトUI:ランキング3位
		UI_TYPE_RESULT_RANKING04,			//リザルトUI:ランキング4位
		UI_TYPE_RESULT_RANKING05,			//リザルトUI:ランキング5位

		UI_TYPE_PAUSE_FRAME,				//ポーズUI:枠
		UI_TYPE_PAUSE_START,				//ポーズUI:再開
		UI_TYPE_PAUSE_EXIT,					//ポーズUI:終了
		UI_TYPE_PAUSE_RESTART,				//ポーズUI:やり直し

		UI_TYPE_PLAYER_1P,					//プレイヤーUI:1P
		UI_TYPE_PLAYER_2P,					//プレイヤーUI:2P
		UI_TYPE_MAX,
	}UI_TYPE;

	CUi(int nPriority = PRIORITY_UI);	//コンストラクタ
	~CUi();								//デストラクタ

										//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CUi *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriolty, UI_TYPE type);
	UI_TYPE GetUIType(void);

private:
	UI_TYPE m_type;						// UIの種類
	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャへのポインタ
	CControl *m_pControl;
	D3DXVECTOR3 m_size;
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_UI_H_