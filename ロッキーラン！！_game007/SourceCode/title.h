//===========================================
//タイトル処理
//Author:寺下琉生
//===========================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include "scene.h"
#include "scene2D.h"
#include "main.h"
#include "camera.h"
#include "light.h"

//================================================
//前方宣言
//================================================
class CUi;
class CScene2D;

//================================================
//マクロ定義
//================================================
#define MAX_TITLE_UI_NUM			(4)				//ポリゴンの管理番号
#define TITLE_LOGO_POSY				(0.0f)			//タイトルロゴのposY
#define TITLE_LOGO_SIZEX			(1000.0f)		//タイトルロゴのサイズX
#define TITLE_LOGO_SIZEY			(600.0f)		//タイトルロゴのサイズX
#define TITlE_PRESS_POSY			(600.0f)		//Press EnterのposY
#define TITlE_PRESS_SIZEX			(550.0f)		//Press EnterのサイズX
#define TITlE_PRESS_SIZEY			(250.0f)		//Press EnterのサイズY
#define TITlE_PLAYER_1P_POSY		(1580.0f)		//1P画像のposY
#define TITlE_PLAYER_1P_SIZEX		(350.0f)		//1P画像のサイズX
#define TITlE_PLAYER_1P_SIZEY		(350.0f)		//1P画像のサイズY
#define TITlE_PLAYER_2P_POSY		(1350.0f)		//2P画像のposY
#define TITlE_PLAYER_2P_SIZEX		(300.0f)		//2P画像のサイズX
#define TITlE_PLAYER_2P_SIZEY		(300.0f)		//2P画像のサイズY
#define TITLE_TO_RESULT_COUNT		(600)			//リザルトに行くまでの時間

//========================================================
//構造体の定義
//========================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CTitle : public CScene
{
public:
	CTitle(int nPriority = PRIORITY_NONE);		//コンストラクタ
	~CTitle();									//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	CUi *GetUi(void);			//UIの取得処理

private:
	CUi *m_apUi[MAX_TITLE_UI_NUM];		//UIのポインタ
	CScene2D *m_pScene2D;				//Scene2Dのポインタ
	int m_nTitleCounter;				//リザルトに行くまでのまでの時間
};

#endif // !_TITLE_H_