//=============================================================================
// ジャンプの2Dアニメーション処理 [2Danimation_jump.cpp]
// Author : KUSAKARI KAKERU
//=============================================================================
#include "2Danimation_jump.h"
#include "billboard.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "player.h"

//=============================================================================
// コンストラクタ
//=============================================================================
C2DAnimationJump::C2DAnimationJump()
{
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_nLife = 0;
	m_fMaxSpeed = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
C2DAnimationJump::~C2DAnimationJump()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT C2DAnimationJump::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_nLife = 24;

	CBillboard::Init(pos, size);

	SetTex(m_nPatternAnim, 4);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void C2DAnimationJump::Uninit(void)
{
	CBillboard::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void C2DAnimationJump::Update(void)
{
	// 向きに合わせて前進
	m_move.z += -cosf(m_rot.y) * 0.2f;
	m_move.x += -sinf(m_rot.y) * 0.2f;

	// 移動量が最大移動量を超えないようにする
	if (m_move.x <= -sinf(m_rot.y) *  m_fMaxSpeed)
	{
		m_move.x = -sinf(m_rot.y) *  m_fMaxSpeed;
	}

	if (m_move.x >= -sinf(m_rot.y) *  m_fMaxSpeed)
	{
		m_move.x = -sinf(m_rot.y) *  m_fMaxSpeed;
	}

	if (m_move.z <= -cosf(m_rot.y) * m_fMaxSpeed)
	{
		m_move.z = -cosf(m_rot.y) * m_fMaxSpeed;
	}

	if (m_move.z >= -cosf(m_rot.y) * m_fMaxSpeed)
	{
		m_move.z = -cosf(m_rot.y) * m_fMaxSpeed;
	}

	// 継承元クラスの更新処理
	CBillboard::Update();

	// アニメーションカウンターの更新
	m_nCounterAnim++;

	if (m_nCounterAnim % 6 == 0)
	{
		// アニメーションパターンの更新
		m_nPatternAnim++;

		if (m_nPatternAnim >= 4)
		{
			m_nPatternAnim = 3;
		}

		// テクスチャ座標の更新
		SetTex(m_nPatternAnim, 4);
	}

	// 寿命を減らす
	m_nLife--;

	// 寿命を減らしたら消す
	if (m_nLife <= 0)
	{
		Uninit();
	}
}

//================================================
//描画処理
//================================================
void C2DAnimationJump::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		//アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	//アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHAREF, 240);				//アルファ値の参照値

	D3DXMATRIX mtxView;						//ビューマトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;	//計算用マトリックス
	D3DXMatrixIdentity(&m_mtxWorld);		//ワールドマトリックスの初期化

											//ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);


	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetFVF(FVF_VERTEX_3D);					//頂点フォーマットの設定

	pDevice->SetTexture(0, m_pTexture);				//テクスチャの設定

													//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
		0,											//開始する頂点のインデックス
		2);											//描画するプリミティブ数

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		//アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);	//アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);				//アルファ値の参照値

																//ライティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//================================================
//生成処理
//================================================
C2DAnimationJump *C2DAnimationJump::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, float fMaxSpeed)
{
	//インスタンスの生成
	C2DAnimationJump *p2DAnimationJump = NULL;
	if (p2DAnimationJump == NULL)
	{
		p2DAnimationJump = new C2DAnimationJump;
		if (p2DAnimationJump != NULL)
		{
			p2DAnimationJump->Init(pos, size);
			p2DAnimationJump->m_rot = rot;
			p2DAnimationJump->m_fMaxSpeed = fMaxSpeed;
			p2DAnimationJump->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_JUMP_SMOKE);
		}
	}
	return p2DAnimationJump;
}