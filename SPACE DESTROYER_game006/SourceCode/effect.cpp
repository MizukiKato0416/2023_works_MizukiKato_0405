//================================================
//弾処理
//Authore:加藤瑞葵
//================================================
#include "scene2D.h"
#include "scene.h"
#include "manager.h"
#include "renderer.h"
#include "effect.h"
#include "texture.h"
#include "boss.h"
#include "game01.h"

//================================================
//静的メンバ変数宣言
//================================================
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;

//================================================
//デフォルトコンストラクタ
//================================================
CEffect::CEffect(int nPriority) :CScene2D(nPriority)
{
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col.r = 0.0f;
	m_col.g = 0.0f;
	m_col.b = 0.0f;
	m_col.a = 0.0f;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CEffect::~CEffect()
{

}

//================================================
//初期化処理
//================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLORVALUE col)
{
	m_col = col;
	m_size = size;
	m_move = move;

	CScene2D::Init(pos, size);

	//カラー反映
	CScene2D::SetCol(m_col);
	return S_OK;
}

//================================================
//終了処理
//================================================
void CEffect::Uninit(void)
{
	CScene2D::Uninit();
}

//================================================
//更新処理
//================================================
void CEffect::Update(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//移動量反映
	pos += m_move;

	//動きの処理
	MoveType();

	//位置反映
	CScene2D::SetPos(pos, m_size);
	//カラー反映
	CScene2D::SetCol(m_col);

	if (m_size.x <= 0.0f || m_size.y <= 0.0f || m_col.a <= 0.0f)
	{
		Uninit();
		return;
	}
}

//================================================
//描画処理
//================================================
void CEffect::Draw(void)
{
	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//加算合成の設定
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	//元の設定に戻す
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//================================================
//生成処理
//================================================
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLORVALUE col, EFFECT_TYPE type)
{
	//インスタンスの生成
	CEffect *pEffect = NULL;
	if (pEffect == NULL)
	{
		pEffect = new CEffect;
		if (pEffect != NULL)
		{
			pEffect->m_type = type;
			pEffect->Init(pos, size, move, col);
			m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_EFFECT);
			pEffect->BindTexture(m_pTexture);
		}
	}
	return pEffect;
}

//================================================
////タイプによる動き
//================================================
void CEffect::MoveType(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();

	//ボスと弾の角度計算用
	float fTanR = 0.0f;
	//ボスのポインター
	CBoss *pBoss = CGame01::GetBoss();
	//ボスの位置保存用
	D3DXVECTOR3 posBoss = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//ボスとの距離
	float fDiffer = 0;

	switch (m_type)
	{
	case EFFECT_TYPE_NONE:
		break;
	case EFFECT_TYPE_NORMAL:
		//サイズを小さくする
		m_size.x -= 2.5f;
		m_size.y -= 2.5f;
		//カラーを薄くする
		m_col.a -= 20.0f;
		break;
	case EFFECT_TYPE_BOSS_LASER:
		//サイズを大きくする
		m_size.x += 0.1f;
		m_size.y += 0.1f;
		//ボスの位置を取得
		posBoss = pBoss->GetBodyPos();
		//y座標を調整
		posBoss.y += 150.0f;
		//ボスとの距離
		fDiffer = sqrtf(((posBoss.x - pos.x) * (posBoss.x - pos.x)) + ((posBoss.y - pos.y) * (posBoss.y - pos.y)));
		//ボスとエフェクトの角度を計算
		fTanR = atan2f(posBoss.y - pos.y, posBoss.x - pos.x);
		//ボスに向かって行くよう移動量を計算
		m_move = D3DXVECTOR3(cosf(fTanR) * 2.0f, sinf(fTanR) * 2.0f, 0.0f);
		if (fDiffer <= 20.0f)
		{
			m_col.a = 0.0f;
		}
		break;
	default:
		break;
	}
}