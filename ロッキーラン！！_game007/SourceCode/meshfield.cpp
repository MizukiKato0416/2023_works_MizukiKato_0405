//================================================
//メッシュフィールド処理
//Author:加藤瑞葵
//================================================
#include "renderer.h"
#include "meshfield.h"
#include "scene3D.h"
#include "manager.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CMeshField::CMeshField(int nPriority):CScene(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLine = 0;
	m_nVertical = 0;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CMeshField::~CMeshField()
{

}

//================================================
//初期化処理
//================================================
HRESULT CMeshField::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//変数初期化
	m_pos = pos;
	m_size = size;

	//位置・サイズ設定処理
	CScene::SetPos(m_pos);
	CScene::SetSize(m_size);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * ((m_nVertical + 1) * (m_nLine + 1)),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);


	VERTEX_3D *pVtx;
	//頂点バッファをロックし、頂点データのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	int nNum = 0;
	for (int nVertical = 0; nVertical < m_nVertical + 1; nVertical++)
	{
		for (int nLine = 0; nLine < m_nLine + 1; nLine++, nNum++)
		{
			pVtx[nNum].pos = D3DXVECTOR3(-m_size.x / 2.0f + (m_size.x / m_nLine) * nLine,
											m_pos.y,
											m_size.z / 2.0f - (m_size.z / m_nVertical) * nVertical);
			//カラー
			pVtx[nNum].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			//テクスチャ
			pVtx[nNum].tex = D3DXVECTOR2(0.0f + (1.0f * nLine), 0.0f + (1.0f * nVertical));
		}
	}

	//法線ベクトルを求める
	D3DXVECTOR3 vec[2];		//外積計算用ベクトル
	D3DXVECTOR3 vecNor;		//法線ベクトル

	//外積計算のためのベクトルを求める
	vec[0] = D3DXVECTOR3(pVtx[1].pos.x - pVtx[0].pos.x, pVtx[1].pos.y - pVtx[0].pos.y, pVtx[1].pos.z - pVtx[0].pos.z);
	vec[1] = D3DXVECTOR3(pVtx[m_nLine + 1].pos.x - pVtx[0].pos.x, pVtx[m_nLine + 1].pos.y - pVtx[0].pos.y, pVtx[m_nLine + 1].pos.z - pVtx[0].pos.z);

	//外積計算
	D3DXVec3Cross(&vecNor, &vec[0], &vec[1]);

	//ベクトルを正規化する(ベクトルの大きさを1にする)
	D3DXVec3Normalize(&vecNor, &vecNor);

	//法線
	nNum = 0;
	for (int nVertical = 0; nVertical < m_nVertical + 1; nVertical++)
	{
		for (int nLine = 0; nLine < m_nLine + 1; nLine++, nNum++)
		{
			pVtx[nNum].nor = D3DXVECTOR3(vecNor.x, vecNor.y, vecNor.z);
		}
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * ((m_nVertical - 1) * (m_nLine + 3) + (m_nLine + 1) * (m_nVertical + 1)),
								D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIdxBuff, NULL);

	WORD *pIdx;		//インデックス情報へのポインタ
					//インデックスバッファをロックし番号データへのポインタを取得
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt1 = 0; nCnt1 < m_nVertical; nCnt1++)
	{
		for (int nCnt2 = 0; nCnt2 < m_nLine + 1; nCnt2++)
		{
			//番号データの設定
			pIdx[(nCnt2 * 2) + 0 + (m_nLine + 2) * 2 * nCnt1] = (m_nLine + 1) + nCnt2 + (m_nLine + 1) * nCnt1;
			pIdx[(nCnt2 * 2) + 1 + (m_nLine + 2) * 2 * nCnt1] = 0			  + nCnt2 + (m_nLine + 1) * nCnt1;
		}
	}

	for (int nCnt3 = 0; nCnt3 < m_nVertical - 1; nCnt3++)
	{
		pIdx[((m_nLine + 1) * 2 + 0) * (nCnt3 + 1) + (2 * nCnt3)] = m_nLine			+ (m_nLine + 1) * nCnt3;
		pIdx[((m_nLine + 1) * 2 + 1) * (nCnt3 + 1) + (1 * nCnt3)] = m_nLine * 2 + 2 + (m_nLine + 1) * nCnt3;
	}

	//インデックスバッファをアンロックする
	m_pIdxBuff->Unlock();


	return S_OK;
}

//================================================
//終了処理
//================================================
void CMeshField::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//インデックスバッファの破棄
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CMeshField::Update(void)
{
	
}

//================================================
//描画処理
//================================================
void CMeshField::Draw(void)
{
	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;	//計算用マトリックス
	D3DXMatrixIdentity(&m_mtxWorld);		//ワールドマトリックスの初期化

	//スケールを反映
	//m_mtxWorld._11 = m_size.x;
	//m_mtxWorld._22 = m_size.y;
	//m_mtxWorld._33 = m_size.z;

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);


	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	pDevice->SetFVF(FVF_VERTEX_3D);					//頂点フォーマットの設定

	pDevice->SetTexture(0, m_pTexture);				//テクスチャの設定

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
									0,
									0,
									((m_nLine + 1) * (m_nVertical + 1)),				//頂点の数
									0,													//開始する頂点のインデックス
									2 * m_nLine * m_nVertical + (m_nVertical * 4) - 4);	//描画するプリミティブ数
}

//================================================
//生成処理
//================================================
CMeshField* CMeshField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nLine, int nVertical)
{
	//インスタンスの生成
	CMeshField *pMeshField = NULL;
	if (pMeshField == NULL)
	{
		pMeshField = new CMeshField;
		if (pMeshField != NULL)
		{
			//変数初期化
			pMeshField->m_rot = rot;
			pMeshField->m_nLine = nLine;
			pMeshField->m_nVertical = nVertical;
			//初期化処理
			pMeshField->Init(pos, size);
		}
	}
	return pMeshField;
}

//================================================
//テクスチャ割り当て処理
//================================================
void CMeshField::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
