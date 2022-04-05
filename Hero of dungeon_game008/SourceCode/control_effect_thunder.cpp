//=============================================================================
// 雷エフェクトの動きの処理
// Author : KatoMizuki
//=============================================================================
#include "control_effect_thunder.h"
#include "effect3D.h"

//================================================
//マクロ定義
//================================================
#define CONTROL_EFFECT_THUNDER_ADD_SIZE				(5.0f)		//サイズ加算値
#define CONTROL_EFFECT_THUNDER_SUBTRACTION_SIZE		(8.0f)		//サイズ減算値
#define CONTROL_EFFECT_THUNDER_SIZE					(400.0f)	//サイズ
#define CONTROL_EFFECT_THUNDER_DESTROY_COUNT		(280)		//消えるまでの時間

//=============================================================================
// コンストラクタ
//=============================================================================
CControlEffectThunder::CControlEffectThunder()
{
	m_nDestroyCounter = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CControlEffectThunder::~CControlEffectThunder()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CControlEffectThunder::Init(CObject *pObject)
{
	m_nDestroyCounter = 0;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CControlEffectThunder::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CControlEffectThunder::Update(CObject *pObject)
{
	//カウンターを加算
	m_nDestroyCounter++;

	//オブジェクトのポインタをエフェクトのポインタにキャスト
	CEffect3D *pEffect3D = nullptr;
	pEffect3D = (CEffect3D*)pObject;

	//位置とサイズ取得
	D3DXVECTOR3 pos = pEffect3D->GetPos();
	D3DXVECTOR3 size = pEffect3D->GetSize();

	//既定の値より小さいとき
	if (m_nDestroyCounter < CONTROL_EFFECT_THUNDER_DESTROY_COUNT)
	{
		//太くする
		size.x += CONTROL_EFFECT_THUNDER_ADD_SIZE;
		//既定の値より太くなったら
		if (size.x >= CONTROL_EFFECT_THUNDER_SIZE)
		{
			//既定の値にする
			size.x = CONTROL_EFFECT_THUNDER_SIZE;
		}
	}
	else
	{//既定の値以上の時
		//細くする
		size.x -= CONTROL_EFFECT_THUNDER_SUBTRACTION_SIZE;
		//見えなくなったら
		if (size.x <= 0.0f)
		{
			//消す
			pEffect3D->Uninit();
			return;
		}
	}

	//位置とサイズを反映
	pEffect3D->SetPos(pos, size);
}

//=============================================================================
// 生成処理
//=============================================================================
CControlEffectThunder *CControlEffectThunder::Create(CObject *pObject)
{
	//インスタンスの生成
	CControlEffectThunder *pControlEffectThunder = nullptr;
	if (pControlEffectThunder == nullptr)
	{
		pControlEffectThunder = new CControlEffectThunder;
		if (pControlEffectThunder != nullptr)
		{
			pControlEffectThunder->Init(pObject);
		}
	}
	return pControlEffectThunder;
}