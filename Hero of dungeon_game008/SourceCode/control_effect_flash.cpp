//=============================================================================
// 閃光エフェクトの動きの処理
// Author : KatoMizuki
//=============================================================================
#include "control_effect_flash.h"
#include "effect3D.h"

//================================================
//マクロ定義
//================================================
#define CONTROL_EFFECT_FLASH_ADD_SIZE_SMALL				(1.0f)		//サイズ加算値(変化値小)
#define CONTROL_EFFECT_FLASH_ADD_SIZE_BIG				(30.0f)		//サイズ加算値(変化値大)
#define CONTROL_EFFECT_FLASH_SUBTRACTION_SIZE			(2.0f)		//サイズ減算値
#define CONTROL_EFFECT_FLASH_SIZE_SMALL					(40.0f)		//小さいサイズ
#define CONTROL_EFFECT_FLASH_SIZE_BIG					(4000.0f)	//大きいさいサイズ

//=============================================================================
// コンストラクタ
//=============================================================================
CControlEffectFlash::CControlEffectFlash()
{
	m_nCounter = 0;
	m_state = CONTROL_EFFECT_FLASH_STATE::NONE;
}

//=============================================================================
// デストラクタ
//=============================================================================
CControlEffectFlash::~CControlEffectFlash()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CControlEffectFlash::Init(CObject *pObject)
{
	m_nCounter = 0;
	m_state = CONTROL_EFFECT_FLASH_STATE::ADD_SIZE_SMALL;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CControlEffectFlash::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CControlEffectFlash::Update(CObject *pObject)
{
	//カウンターを加算
	m_nCounter++;

	//オブジェクトのポインタをエフェクトのポインタにキャスト
	CEffect3D *pEffect3D = nullptr;
	pEffect3D = (CEffect3D*)pObject;

	//位置とサイズ取得
	D3DXVECTOR3 pos = pEffect3D->GetPos();
	D3DXVECTOR3 size = pEffect3D->GetSize();

	switch (m_state)
	{
	case CONTROL_EFFECT_FLASH_STATE::ADD_SIZE_SMALL:
		//大きくする
		size.x += CONTROL_EFFECT_FLASH_ADD_SIZE_SMALL;
		size.y += CONTROL_EFFECT_FLASH_ADD_SIZE_SMALL;
		//既定の大きさ以上になったら
		if (size.x >= CONTROL_EFFECT_FLASH_SIZE_SMALL)
		{
			//既定の大きさにする
			size.x = CONTROL_EFFECT_FLASH_SIZE_SMALL;
		}
		if (size.y >= CONTROL_EFFECT_FLASH_SIZE_SMALL)
		{
			//既定の大きさにする
			size.y = CONTROL_EFFECT_FLASH_SIZE_SMALL;
		}

		//既定の値以上になったら
		if (m_nCounter >= 240)
		{
			//状態を変える
			m_state = CONTROL_EFFECT_FLASH_STATE::SUBTRACTION_SIZE;
			//0にする
			m_nCounter = 0;
		}

		break;
	case CONTROL_EFFECT_FLASH_STATE::SUBTRACTION_SIZE:
		//小さくする
		size.x -= CONTROL_EFFECT_FLASH_SUBTRACTION_SIZE;
		size.y -= CONTROL_EFFECT_FLASH_SUBTRACTION_SIZE;

		//既定の値以上になったら
		if (m_nCounter >= 30)
		{
			//状態を変える
			m_state = CONTROL_EFFECT_FLASH_STATE::ADD_SIZE_BIG;
			//0にする
			m_nCounter = 0;
		}
		break;
	case CControlEffectFlash::CONTROL_EFFECT_FLASH_STATE::ADD_SIZE_BIG:
		//大きくする
		size.x += CONTROL_EFFECT_FLASH_ADD_SIZE_BIG;
		size.y += CONTROL_EFFECT_FLASH_ADD_SIZE_BIG;
		//既定の大きさ以上になったら
		if (size.x >= CONTROL_EFFECT_FLASH_SIZE_BIG)
		{
			//既定の大きさにする
			size.x = CONTROL_EFFECT_FLASH_SIZE_BIG;
		}
		if (size.y >= CONTROL_EFFECT_FLASH_SIZE_BIG)
		{
			//既定の大きさにする
			size.y = CONTROL_EFFECT_FLASH_SIZE_BIG;
		}

		//既定の値以上になったら
		if (m_nCounter >= 120)
		{
			//カラーを取得
			D3DXCOLOR col = pEffect3D->GetCol();
			//薄くする
			col.a -= 0.01f;
			//見えなくなったら
			if (col.a <= 0.0f)
			{
				//消す
				pEffect3D->Uninit();
				return;
			}
			//色を設定
			pEffect3D->SetCol(col);
		}
		break;
	default:
		break;
	}

	//位置とサイズを反映
	pEffect3D->SetPos(pos, size);
}

//=============================================================================
// 生成処理
//=============================================================================
CControlEffectFlash *CControlEffectFlash::Create(CObject *pObject)
{
	//インスタンスの生成
	CControlEffectFlash *pControlEffectFlash = nullptr;
	if (pControlEffectFlash == nullptr)
	{
		pControlEffectFlash = new CControlEffectFlash;
		if (pControlEffectFlash != nullptr)
		{
			pControlEffectFlash->Init(pObject);
		}
	}
	return pControlEffectFlash;
}