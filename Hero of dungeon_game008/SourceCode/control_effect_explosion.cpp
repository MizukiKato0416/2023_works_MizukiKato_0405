//=============================================================================
// 爆発エフェクトの動きの処理
// Author : KatoMizuki
//=============================================================================
#include "control_effect_explosion.h"
#include "effect3D.h"

//================================================
//マクロ定義
//================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CControlEffectExplosion::CControlEffectExplosion()
{
	
}

//=============================================================================
// デストラクタ
//=============================================================================
CControlEffectExplosion::~CControlEffectExplosion()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CControlEffectExplosion::Init(CObject *pObject)
{
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CControlEffectExplosion::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CControlEffectExplosion::Update(CObject *pObject)
{
	//オブジェクトのポインタをエフェクトのポインタにキャスト
	CEffect3D *pEffect3D = nullptr;
	pEffect3D = (CEffect3D*)pObject;
	
}

//=============================================================================
// 生成処理
//=============================================================================
CControlEffectExplosion *CControlEffectExplosion::Create(CObject *pObject)
{
	//インスタンスの生成
	CControlEffectExplosion *pControlEffectExplosion = nullptr;
	if (pControlEffectExplosion == nullptr)
	{
		pControlEffectExplosion = new CControlEffectExplosion;
		if (pControlEffectExplosion != nullptr)
		{
			pControlEffectExplosion->Init(pObject);
		}
	}
	return pControlEffectExplosion;
}