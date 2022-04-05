//===========================================
//チェックポイント魔法陣処理
//Author:KatoMizuki
//===========================================
#ifndef _CHECK_CIRCLE_H_
#define _CHECK_CIRCLE_H_

#include "magic_circle.h"

//前方宣言
class CObject2D;
class CGauge;

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CCheckCircle : public CMagicCircle
{
public:
	CCheckCircle(int nPriority = PRIORITY_CHECK_CIRCLE);		//コンストラクタ
	~CCheckCircle();											//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CCheckCircle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);
	bool CollisionPlayer(void);			//プレイヤーとの当たり判定

private:
	int m_nEffectCounter;			//エフェクトを出す頻度のカウンター
	CObject2D *m_pMask;				//オブジェクト2Dのポインタ(マスク用)
	CObject2D *m_pGaugeFrame;		//オブジェクト2Dのポインタ(ゲージのフレーム用)
	CGauge *m_pGauge;				//ゲージのポインタ
};

#endif // !_CHECK_CIRCLE_H_