//=============================================================================
// チェックポイントのエフェクトの動きの処理
// Author : KatoMizuki
//=============================================================================
#include "control_effect_check.h"
#include "effect3D.h"

//================================================
//マクロ定義
//================================================
#define CONTROL_EFFECT_CHECK_MOVE			(float (rand() % 3 + 1) / 10)	//移動量
#define CONTROL_EFFECT_CHECK_SUBTRACTION	(0.005f)						//α値減算値

//=============================================================================
// コンストラクタ
//=============================================================================
CControlEffectCheck::CControlEffectCheck()
{
	
}

//=============================================================================
// デストラクタ
//=============================================================================
CControlEffectCheck::~CControlEffectCheck()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CControlEffectCheck::Init(CObject *pObject)
{
	m_move = D3DXVECTOR3(0.0f, CONTROL_EFFECT_CHECK_MOVE, 0.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CControlEffectCheck::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CControlEffectCheck::Update(CObject *pObject)
{
	//オブジェクトのポインタをエフェクトのポインタにキャスト
	CEffect3D *pEffect3D = nullptr;
	pEffect3D = (CEffect3D*)pObject;

	//カラーの取得
	D3DXCOLOR col = pEffect3D->GetCol();
	//薄くする
	col.a -= CONTROL_EFFECT_CHECK_SUBTRACTION;
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
CControlEffectCheck *CControlEffectCheck::Create(CObject *pObject)
{
	//インスタンスの生成
	CControlEffectCheck *pControlEffectCheck = nullptr;
	if (pControlEffectCheck == nullptr)
	{
		pControlEffectCheck = new CControlEffectCheck;
		if (pControlEffectCheck != nullptr)
		{
			pControlEffectCheck->Init(pObject);
		}
	}
	return pControlEffectCheck;
}