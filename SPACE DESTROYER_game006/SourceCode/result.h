//===========================================
//リザルト処理
//Authore:加藤瑞葵
//===========================================
#ifndef _RESULT_H_
#define _RESULT_H_
#include "scene.h"
#include "scene2D.h"
#include "main.h"

//前方宣言
class CTexture;
class CBg;
class CRanking;

//================================================
//マクロ定義
//================================================
#define RESULT_TO_TITLE_COUNT	(600)			//タイトルに行くまでの間隔

//========================================================
//構造体の定義
//========================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CResult : public CScene
{
public:
	CResult();				//コンストラクタ
	~CResult();				//デストラクタ

							//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTexture *GetTexture(void);
	static CBg *GetBg(void);
	static CRanking *GetRanking(void);

private:
	CScene2D *m_pScene2D;

	static CTexture *m_pTexture;
	static CBg *m_pBg;
	static CRanking *m_pRanking;
	int m_nTitleCounter;			//タイトルに行くまでのカウンター
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_RESULT_H_