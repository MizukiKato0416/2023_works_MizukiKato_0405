//===========================================
//メニュー処理
//Authore:加藤瑞葵
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

//========================================================
//構造体の定義
//========================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CMenu : public CScene
{
public:
	//選択肢
	typedef enum
	{
		SELECT_MENU_TYPE_NONE = 0,
		SELECT_MENU_TYPE_TUTORIAL,		//Tutorial
		SELECT_MENU_TYPE_GAME_START,	//GameStart
		SELECT_MENU_TYPE_EXIT,			//Exit
		SELECT_MENU_TYPE_MAX			//選択肢最大値
	} SELECT_MENU_TYPE;

	CMenu();				//コンストラクタ
	~CMenu();				//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTexture *GetTexture(void);
	static int GetSelect(void);
	static int GetFrame(void);
	static void SetFrame(int nCntFrame);
	
private:
	static CTexture *m_pTexture;
	static CScene2D *m_pScene2D;
	static int m_nSelect;			//どの選択肢が選択されているか
	static int m_nCntFrame;			//uiを動かすためのフレームカウント
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_MENU_H_