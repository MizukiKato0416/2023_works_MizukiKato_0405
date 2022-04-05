//============================================================================
// ビルボードのエフェクト処理 [billboard_effect.cpp]
// Author : KUSAKARI KAKERU
//=============================================================================
#include "renderer.h"
#include "billboard_effect.h"
#include "manager.h"
#include "texture.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CBillboardEffect::CBillboardEffect()
{

}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CBillboardEffect::~CBillboardEffect()
{

}

//================================================
//初期化処理
//================================================
HRESULT CBillboardEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 継承元クラスの初期化処理
	CBillboard::Init(pos, size);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CBillboardEffect::Uninit(void)
{
	// 継承元クラスの終了処理
	CBillboard::Uninit();
}

//================================================
//更新処理
//================================================
void CBillboardEffect::Update(void)
{
	
}

//================================================
//描画処理
//================================================
void CBillboardEffect::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// 継承元クラスの終了処理
	CBillboard::Draw();

	//アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	//減算合成から通常の合成に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//ライティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//================================================
//生成処理
//================================================
CBillboardEffect *CBillboardEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//インスタンスの生成
	CBillboardEffect *pBillboardEffect = NULL;
	if (pBillboardEffect == NULL)
	{
		pBillboardEffect = new CBillboardEffect;
		if (pBillboardEffect != NULL)
		{
			pBillboardEffect->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_EFFECT);
			pBillboardEffect->BindTexture(pBillboardEffect->m_pTexture);
			pBillboardEffect->Init(pos, size);
		}
	}
	return pBillboardEffect;
}