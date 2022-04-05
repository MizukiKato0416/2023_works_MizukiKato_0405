//=============================================================================
// ヒットエフェクトの動きの処理
// Author : KatoMizuki
//=============================================================================
#include "control_effect_hit.h"
#include "effect3D.h"

//================================================
//マクロ定義
//================================================
#define CONTROL_EFFECT_HIT_SUBTRACTION	(0.05f)						//α値減算値

//=============================================================================
// コンストラクタ
//=============================================================================
CControlEffectHit::CControlEffectHit()
{
	
}

//=============================================================================
// デストラクタ
//=============================================================================
CControlEffectHit::~CControlEffectHit()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CControlEffectHit::Init(CObject *pObject)
{
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CControlEffectHit::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CControlEffectHit::Update(CObject *pObject)
{
	//オブジェクトのポインタをエフェクトのポインタにキャスト
	CEffect3D *pEffect3D = nullptr;
	pEffect3D = (CEffect3D*)pObject;

	//カラーの取得
	D3DXCOLOR col = pEffect3D->GetCol();
	//薄くする
	col.a -= CONTROL_EFFECT_HIT_SUBTRACTION;
	//見えなくなったら
	if (col.a <= 0.0f)
	{
		//消す
		pEffect3D->Uninit();
		return;
	}
	pEffect3D->SetCol(col);
}

//=============================================================================
// 生成処理
//=============================================================================
CControlEffectHit *CControlEffectHit::Create(CObject *pObject)
{
	//インスタンスの生成
	CControlEffectHit *pControlEffectHit = nullptr;
	if (pControlEffectHit == nullptr)
	{
		pControlEffectHit = new CControlEffectHit;
		if (pControlEffectHit != nullptr)
		{
			pControlEffectHit->Init(pObject);
		}
	}
	return pControlEffectHit;
}