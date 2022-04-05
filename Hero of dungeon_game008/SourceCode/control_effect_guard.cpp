//=============================================================================
// ガードエフェクトの動きの処理
// Author : KatoMizuki
//=============================================================================
#include "control_effect_guard.h"
#include "effect3D.h"

//================================================
//マクロ定義
//================================================
#define CONTROL_EFFECT_GUARD_SUBTRACT_ALPHA		(0.05f)					//α値減算値
#define CONTROL_EFFECT_GUARD_ADD_SIZE			(1.0f)					//サイズ加算量

//=============================================================================
// コンストラクタ
//=============================================================================
CControlEffectGuard::CControlEffectGuard()
{
	
}

//=============================================================================
// デストラクタ
//=============================================================================
CControlEffectGuard::~CControlEffectGuard()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CControlEffectGuard::Init(CObject *pObject)
{
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CControlEffectGuard::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CControlEffectGuard::Update(CObject *pObject)
{
	//オブジェクトのポインタをエフェクトのポインタにキャスト
	CEffect3D *pEffect3D = nullptr;
	pEffect3D = (CEffect3D*)pObject;

	//位置とサイズとカラーの取得
	D3DXVECTOR3 pos = pEffect3D->GetPos();
	D3DXVECTOR3 size = pEffect3D->GetSize();
	D3DXCOLOR col = pEffect3D->GetCol();

	//大きくする
	size.x += CONTROL_EFFECT_GUARD_ADD_SIZE;
	size.y += CONTROL_EFFECT_GUARD_ADD_SIZE;
	//薄くする
	col.a -= CONTROL_EFFECT_GUARD_SUBTRACT_ALPHA;
	//見えなくなったら
	if (col.a <= 0.0f)
	{
		//消す
		pEffect3D->Uninit();
		return;
	}
	//カラーの設定
	pEffect3D->SetCol(col);
	//サイズの設定
	pEffect3D->SetPos(pos,size);
}

//=============================================================================
// 生成処理
//=============================================================================
CControlEffectGuard *CControlEffectGuard::Create(CObject *pObject)
{
	//インスタンスの生成
	CControlEffectGuard *pControlEffectGuard = nullptr;
	if (pControlEffectGuard == nullptr)
	{
		pControlEffectGuard = new CControlEffectGuard;
		if (pControlEffectGuard != nullptr)
		{
			pControlEffectGuard->Init(pObject);
		}
	}
	return pControlEffectGuard;
}