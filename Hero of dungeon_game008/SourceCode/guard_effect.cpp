//================================================
//魔法陣の処理
//Author:KatoMizuki
//================================================
#include "guard_effect.h"
#include "manager.h"
#include "texture.h"
#include "object3D.h"

//================================================
//マクロ定義
//================================================
#define GUARD_EFFECT_SUBTRACT_ALPHA		(0.05f)					//α値減算値
#define GUARD_EFFECT_ADD_SIZE			(4.5f)					//サイズ加算量

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CGuardEffect::CGuardEffect(int nPriority) :CObject(nPriority)
{
	m_pObject3D = nullptr;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CGuardEffect::~CGuardEffect()
{

}

//================================================
//初期化処理
//================================================
HRESULT CGuardEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//ガードエフェクトの生成
	m_pObject3D = CObject3D::Create(pos, size, m_rot);
	m_pObject3D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_EFFECT_RING"));
	m_pObject3D->SetCulling(false);
	m_pObject3D->SetAlphaTest(true);
	m_pObject3D->SetAlphaBlend(true);
	m_pObject3D->SetLighting(false);

	//オブジェクトの種類を設定
	SetObjType(CObject::OBJTYPE::GUARD);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CGuardEffect::Uninit(void)
{
	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CGuardEffect::Update(void)
{
	//位置とサイズとカラーの取得
	D3DXVECTOR3 pos = m_pObject3D->GetPos();
	D3DXVECTOR3 size = m_pObject3D->GetSize();
	D3DXCOLOR col = m_pObject3D->GetCol();

	//大きくする
	size.x += GUARD_EFFECT_ADD_SIZE;
	size.y += GUARD_EFFECT_ADD_SIZE;
	//薄くする
	col.a -= GUARD_EFFECT_SUBTRACT_ALPHA;
	//見えなくなったら
	if (col.a <= 0.0f)
	{
		//消す
		m_pObject3D->Uninit();
		m_pObject3D = nullptr;
		Uninit();
		return;
	}
	//カラーの設定
	m_pObject3D->SetCol(col);
	//サイズの設定
	m_pObject3D->SetPos(pos, size);
}

//================================================
//描画処理
//================================================
void CGuardEffect::Draw(void)
{
	
}

//================================================
//生成処理
//================================================
CGuardEffect* CGuardEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	//インスタンスの生成
	CGuardEffect *pGuardEffect = nullptr;
	if (pGuardEffect == nullptr)
	{
		pGuardEffect = new CGuardEffect();
		if (pGuardEffect != nullptr)
		{
			pGuardEffect->m_rot = rot;
			pGuardEffect->Init(pos, size);
		}
	}
	return pGuardEffect;
}
