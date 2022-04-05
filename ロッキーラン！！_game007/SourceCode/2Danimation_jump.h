//=============================================================================
// ジャンプの2Dアニメーション処理 [2Danimation_jump.h]
// Author : KUSAKARI KAKERU
//=============================================================================
#ifndef _2DANIMATION_JUMP_H_
#define _2DANIMATION_JUMP_H_

#include "billboard.h"

//================================================
// マクロ定義
//================================================
#define MAX_SMOKE_SPEED	(0.8f)	//移動速度の最大値

//*****************************************************************************
// ジャンプの2Dアニメーションクラス
//*****************************************************************************
class C2DAnimationJump : public CBillboard
{
public:
	C2DAnimationJump();		// コンストラクタ
	~C2DAnimationJump();	// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	static C2DAnimationJump *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, float fMaxSpeed);		//生成処理

private:
	int m_nCounterAnim;		// アニメーションカウンター
	int m_nPatternAnim;		// アニメーションパターン
	int m_nLife;			// 寿命
	float m_fMaxSpeed;		// 最大移動量
};

#endif	//_2DANIMATION_JUMP_H_