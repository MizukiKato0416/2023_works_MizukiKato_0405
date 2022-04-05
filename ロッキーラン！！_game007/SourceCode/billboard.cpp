//============================================================================
// ビルボード処理 [billboard.cpp]
// Author : KUSAKARI KAKERU
//=============================================================================
#include "renderer.h"
#include "billboard.h"
#include "scene3D.h"
#include "manager.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CBillboard::CBillboard(int nPriority) :CScene(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CBillboard::~CBillboard()
{

}

//================================================
//初期化処理
//================================================
HRESULT CBillboard::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//変数初期化
	m_pos = pos;
	m_size = size;

	//位置・サイズ設定処理
	CScene::SetPos(m_pos);
	CScene::SetSize(m_size);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;
	//頂点バッファをロックし、頂点データのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(- m_size.x / 2.0f, + m_size.y / 2.0f, + m_size.z / 2.0f);
	pVtx[1].pos = D3DXVECTOR3(+ m_size.x / 2.0f, + m_size.y / 2.0f, + m_size.z / 2.0f);
	pVtx[2].pos = D3DXVECTOR3(- m_size.x / 2.0f, - m_size.y / 2.0f, - m_size.z / 2.0f);
	pVtx[3].pos = D3DXVECTOR3(+ m_size.x / 2.0f, - m_size.y / 2.0f, - m_size.z / 2.0f);

	//法線ベクトルを求める
	D3DXVECTOR3 vec[2];		//外積計算用ベクトル
	D3DXVECTOR3 vecNor;		//法線ベクトル

							//外積計算のためのベクトルを求める
	vec[0] = D3DXVECTOR3(pVtx[1].pos.x - pVtx[0].pos.x, pVtx[1].pos.y - pVtx[0].pos.y, pVtx[1].pos.z - pVtx[0].pos.z);
	vec[1] = D3DXVECTOR3(pVtx[2].pos.x - pVtx[0].pos.x, pVtx[2].pos.y - pVtx[0].pos.y, pVtx[2].pos.z - pVtx[0].pos.z);

	//外積計算
	D3DXVec3Cross(&vecNor, &vec[0], &vec[1]);

	//ベクトルを正規化する(ベクトルの大きさを1にする)
	D3DXVec3Normalize(&vecNor, &vecNor);

	//法線
	pVtx[0].nor = D3DXVECTOR3(vecNor.x, vecNor.y, vecNor.z);
	pVtx[1].nor = D3DXVECTOR3(vecNor.x, vecNor.y, vecNor.z);
	pVtx[2].nor = D3DXVECTOR3(vecNor.x, vecNor.y, vecNor.z);
	pVtx[3].nor = D3DXVECTOR3(vecNor.x, vecNor.y, vecNor.z);

	//カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================
//終了処理
//================================================
void CBillboard::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CBillboard::Update(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	m_pos = pos;

	//移動量反映
	m_pos += m_move;

	//位置反映
	CScene::SetPos(m_pos);
}

//================================================
//描画処理
//================================================
void CBillboard::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

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
}

//================================================
//生成処理
//================================================
CBillboard* CBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nPriolity)
{
	//インスタンスの生成
	CBillboard *pBillboard = NULL;
	if (pBillboard == NULL)
	{
		pBillboard = new CBillboard(nPriolity);
		if (pBillboard != NULL)
		{
			pBillboard->m_rot = rot;
			pBillboard->Init(pos, size);
		}
	}
	return pBillboard;
}

//================================================
//位置取得処理
//================================================
D3DXVECTOR3 CBillboard::GetPos(void)
{
	return m_pos;
}

//================================================
//位置設定処理
//================================================
void CBillboard::SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_pos = pos;
	m_size = size;

	//位置・サイズ設定処理
	CScene::SetPos(m_pos);
	CScene::SetSize(m_size);

	VERTEX_3D *pVtx;	// 頂点情報
						//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(-m_size.x / 2.0f, +m_size.y / 2.0f, +m_size.z / 2.0f);
	pVtx[1].pos = D3DXVECTOR3(+m_size.x / 2.0f, +m_size.y / 2.0f, +m_size.z / 2.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x / 2.0f, -m_size.y / 2.0f, -m_size.z / 2.0f);
	pVtx[3].pos = D3DXVECTOR3(+m_size.x / 2.0f, -m_size.y / 2.0f, -m_size.z / 2.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================
//テクスチャ設定処理
//================================================
void CBillboard::SetTex(int nPattern, int nMaxPattern)
{
	VERTEX_3D *pVtx;	// 頂点情報
						//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2((1.0f / nMaxPattern) * nPattern, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((1.0f / nMaxPattern) + (1.0f / nMaxPattern) * nPattern, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((1.0f / nMaxPattern) * nPattern, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((1.0f / nMaxPattern) + (1.0f / nMaxPattern) * nPattern, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================
//テクスチャ設定処理
//================================================
void CBillboard::SetTex(float fMoveTexU, float fMoveTexV)
{
	VERTEX_3D *pVtx;	// 頂点情報
						//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f + fMoveTexU, 0.0f + fMoveTexV);
	pVtx[1].tex = D3DXVECTOR2(1.0f + fMoveTexU, 0.0f + fMoveTexV);
	pVtx[2].tex = D3DXVECTOR2(0.0f + fMoveTexU, 1.0f + fMoveTexV);
	pVtx[3].tex = D3DXVECTOR2(1.0f + fMoveTexU, 1.0f + fMoveTexV);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================
//カラー設定処理
//================================================
void CBillboard::SetCol(D3DCOLORVALUE col)
{
	VERTEX_3D *pVtx;	// 頂点情報
						//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = D3DCOLOR_RGBA((int)col.r, (int)col.g, (int)col.b, (int)col.a);
	pVtx[1].col = D3DCOLOR_RGBA((int)col.r, (int)col.g, (int)col.b, (int)col.a);
	pVtx[2].col = D3DCOLOR_RGBA((int)col.r, (int)col.g, (int)col.b, (int)col.a);
	pVtx[3].col = D3DCOLOR_RGBA((int)col.r, (int)col.g, (int)col.b, (int)col.a);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================
//カラー設定処理
//================================================
void CBillboard::SetCol(D3DXCOLOR col)
{
	VERTEX_3D *pVtx;	// 頂点情報
						//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================
//テクスチャ割り当て処理
//================================================
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
