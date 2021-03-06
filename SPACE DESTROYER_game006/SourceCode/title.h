//===========================================
//タイトル処理
//Authore:加藤瑞葵
//===========================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include "scene.h"
#include "scene2D.h"
#include "main.h"

//前方宣言

//================================================
//マクロ定義
//================================================
#define TITLE_TO_RESULT_COUNT	(600)			//リザルトに行くまでの間隔

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
	CTitle();				//コンストラクタ
	~CTitle();				//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	
private:
	CScene2D *m_pScene2D;
	int m_nResultCounter;		//リザルトに行くまでのカウンター
	
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_TITLE_H_