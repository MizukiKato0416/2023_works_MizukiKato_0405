//============================================================================
// ビルボード処理 [billboard.cpp]
// Author : KUSAKARI KAKERU
//=============================================================================
#include "renderer.h"
#include "billboard_normal.h"
#include "manager.h"
#include "texture.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CBillboardNormal::CBillboardNormal()
{
	
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CBillboardNormal::~CBillboardNormal()
{

}

//================================================
//初期化処理
//================================================
HRESULT CBillboardNormal::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 継承元クラスの初期化処理
	CBillboard::Init(pos, size);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CBillboardNormal::Uninit(void)
{
	// 継承元クラスの終了処理
	CBillboard::Uninit();
}

//================================================
//更新処理
//================================================
void CBillboardNormal::Update(void)
{

}

//================================================
//描画処理
//================================================
void CBillboardNormal::Draw(void)
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
CBillboardNormal *CBillboardNormal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//インスタンスの生成
	CBillboardNormal *pBillboardNormal = NULL;
	if (pBillboardNormal == NULL)
	{
		pBillboardNormal = new CBillboardNormal;
		if (pBillboardNormal != NULL)
		{
			pBillboardNormal->Init(pos, size); 
		}
	}
	return pBillboardNormal;
}