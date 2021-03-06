//===========================================
//リザルト処理
//Author:KatoMizuki
//===========================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "object.h"

//================================================
//前方宣言
//================================================
class CRanking;

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
class CResult : public CObject
{
public:
	CResult();				//コンストラクタ
	~CResult();				//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	int m_nResultCounter;				//タイトルに行くまでのカウンター
};
//================================================
//プロトタイプ宣言
//================================================
#endif // !_RESULT_H_