//===========================================
//タイトル処理
//Author:KatoMizuki
//===========================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include "object.h"

//前方宣言
class CObject2D;

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
class CTitle : public CObject
{
public:
	CTitle(int nPriority = PRIORITY_NONE);		//コンストラクタ
	~CTitle();									//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	int m_nTitleCounter;				//リザルトに行くまでのまでの時間
};

#endif // !_TITLE_H_