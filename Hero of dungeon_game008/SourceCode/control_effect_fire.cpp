//=============================================================================
// 炎エフェクトの動きの処理
// Author : KatoMizuki
//=============================================================================
#include "control_effect_fire.h"
#include "effect3D.h"

//================================================
//マクロ定義
//================================================
#define CONTROL_EFFECT_FIRE_MAX_TEX_ANIM	(8)			//テクスチャアニメーションの種類
#define CONTROL_EFFECT_FIRE_TEX_COUNTER		(rand() % 8 + 3)			//アニメーションのカウンタ

//=============================================================================
// コンストラクタ
//=============================================================================
CControlEffectFire::CControlEffectFire()
{
	m_nTexAnimCounter = 0;
	m_nTexAnimNum = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CControlEffectFire::~CControlEffectFire()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CControlEffectFire::Init(CObject *pObject)
{
	//オブジェクトのポインタをエフェクトのポインタにキャスト
	CEffect3D *pEffect3D = nullptr;
	pEffect3D = (CEffect3D*)pObject;

	m_nTexAnimCounter = 0;
	m_nTexAnimNum = rand() % (CONTROL_EFFECT_FIRE_MAX_TEX_ANIM - 1);

	//テクスチャの設定
	pEffect3D->SetTex(m_nTexAnimNum, CONTROL_EFFECT_FIRE_MAX_TEX_ANIM);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CControlEffectFire::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CControlEffectFire::Update(CObject *pObject)
{
	//オブジェクトのポインタをエフェクトのポインタにキャスト
	CEffect3D *pEffect3D = nullptr;
	pEffect3D = (CEffect3D*)pObject;

	//カウンターを加算
	m_nTexAnimCounter++;
	//規定値以上になったら
	if (m_nTexAnimCounter >= CONTROL_EFFECT_FIRE_TEX_COUNTER)
	{
		//0にする
		m_nTexAnimCounter = 0;

		//アニメーションの番号を加算
		m_nTexAnimNum++;
		//規定値以上になったら
		if (m_nTexAnimNum >= CONTROL_EFFECT_FIRE_MAX_TEX_ANIM)
		{
			//0にする
			m_nTexAnimNum = 0;
		}

		//テクスチャの設定
		pEffect3D->SetTex(m_nTexAnimNum, CONTROL_EFFECT_FIRE_MAX_TEX_ANIM);
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CControlEffectFire *CControlEffectFire::Create(CObject *pObject)
{
	//インスタンスの生成
	CControlEffectFire *pControlEffectFire = nullptr;
	if (pControlEffectFire == nullptr)
	{
		pControlEffectFire = new CControlEffectFire;
		if (pControlEffectFire != nullptr)
		{
			pControlEffectFire->Init(pObject);
		}
	}
	return pControlEffectFire;
}