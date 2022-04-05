//============================================================================
// ビルボードのエフェクト処理 [billboard_effect.h]
// Author : KUSAKARI KAKERU
//=============================================================================
#ifndef _BILLBOARD_EFFECT_H_
#define _BILLBOARD_EFFECT_H_

#include "billboard.h"

//================================================
//クラスの定義
//================================================
class CBillboardEffect : public CBillboard
{
public:
	CBillboardEffect();							//コンストラクタ
	~CBillboardEffect();						//デストラクタ

												//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBillboardEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
};

#endif // _BILLBOARD_EFFECT_H_