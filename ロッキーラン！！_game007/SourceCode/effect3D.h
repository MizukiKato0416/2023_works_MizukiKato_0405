//============================================================================
// 3Dエフェクト処理 [3Deffect.h]
// Author : KUSAKARI KAKERU
//=============================================================================
#ifndef _3D_EFFECT_H_
#define _3D_EFFECT_H_

#include "billboard.h"

//================================================
// マクロ定義
//================================================
#define EFFECT_SHRINK_SIZE	(0.2f)	// 縮小させるサイズ

//================================================
//クラスの定義
//================================================
//クラスの定義
class CEffect3D : public CBillboard
{
public:
	CEffect3D(int nPriority = PRIORITY_PLAYER);	//コンストラクタ
	~CEffect3D();								//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEffect3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nPriolty);

private:
	int m_nLife;							// 寿命
};

#endif // _3D_EFFECT_H_