//============================================================================
// 通常のビルボード処理 [billboard_normal.h]
// Author : KUSAKARI KAKERU
//=============================================================================
#ifndef _BILLBOARD_NORMAL_H_
#define _BILLBOARD_NORMAL_H_

#include "billboard.h"

//================================================
//クラスの定義
//================================================
//クラスの定義
class CBillboardNormal : public CBillboard
{
public:
	CBillboardNormal();							//コンストラクタ
	~CBillboardNormal();						//デストラクタ

												//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBillboardNormal *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
};

#endif // _BILLBOARD_NORMAL_H_