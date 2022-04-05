//===========================================
//メニュー処理
//Authore:寺下琉生
//===========================================
#ifndef _MENU_H_
#define _MENU_H_
#include "scene.h"
#include "scene2D.h"
#include "main.h"

//前方宣言
class CTexture;
class CScene2D;

//================================================
//マクロ定義
//================================================
#define MENU_SELECT_COL						(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))		//選択中の色(白い方)
#define MENU_DEFAULT_COL					(D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f))		//デフォの色(グレーの方)
#define MENU_HIDE							(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f))		//非表示

#define MENU_MAX_STAR						(3)										//星の最大数
#define MENU_STAR_CREATE_SPAN				(480)									//星の生成間隔
#define MENU_LOGO_POSX						(290.0f)								//タイトルロゴのposX
#define MENU_LOGO_POSY						(58.0f)									//タイトルロゴのposY
#define MENU_LOGO_SIXEX						(650.0f)								//タイトルロゴのsizeX
#define MENU_LOGO_SIXEY						(150.0f)								//タイトルロゴのsizeY
#define MENU_CHOICES_SPACE					(150.0f)								//選択肢の間隔	
#define MENU_UI_SIZEX						(400.0f)								//選択肢とその説明のsizeX
#define MENU_UI_SIZEY						(100.0f)								//選択肢とその説明のsizeY
#define MENU_TUTORIAL_BUTTON_POSY			(80.0f)									//選択肢:チュートリアルのposY
#define MENU_GAME_BUTTON_POSY				(220.0f)								//選択肢:ゲームのposY
#define MENU_EXIT_BUTTON_POSY				(360.0f)								//選択肢:終了のposY
#define MENU_EXPLANATION_POSY				(650.0f)								//選択肢の説明のposY
//========================================================
//構造体の定義
//========================================================

//========================================================
//前方宣言
//========================================================
class CUi;
class CScene2D;

//================================================
//クラスの定義
//================================================
//クラスの定義
class CMenu : public CScene
{
public:
	CMenu();				//コンストラクタ
	~CMenu();				//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	//画面遷移の選択肢ボタン
	typedef enum
	{
		SELECT_TUTORIAL,		//チュートリアルボタン
		SELECT_GAME,			//ゲームボタン
		SELECT_BACKTITLE,		//タイトルに戻るボタン
		SELECT_MAX
	}SELECT;

	//選択肢の説明
	typedef enum
	{
		EXPLANATION_TUTORIAL,	//チュートリアル説明
		EXPLANATION_GAME,		//ゲーム説明
		EXPLANATION_EXIT,		//終了説明
		EXPLANATION_MAX
	}EXPLANATION;

	//星生成のパターン
	typedef enum
	{
		STARPATTERN_01,
		STARPATTERN_02,
		STARPATTERN_03,
		STARPATTERN_MAX
	}STARPATTERN;

	CUi *m_pMenu;						   //メニューロゴ
	CUi *m_apSelect[SELECT_MAX];		   //各選択肢
	CUi *m_apExplanation[EXPLANATION_MAX]; //各選択肢の説明
	CUi *m_apStar[MENU_MAX_STAR];		   //星
	CScene2D *m_pScene2D;				   //Scene2Dのポインタ
	int m_nSelect;						   //今の選択肢
	int m_nExplanation;					   //今の選択肢の説明
	int m_nSpan;						   //星の生成間隔
	int m_nPattern;						   //星生成パターン
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_MENU_H_