//================================================
//メッシュ軌跡処理
//Author:KatoMizuki
//================================================
#include "renderer.h"
#include "mesh_trajectory.h"
#include "object3D.h"
#include "manager.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CMeshTrajectory::CMeshTrajectory(int nPriority):CObject(nPriority)
{
	m_aPosPoint.clear();
	m_aColPoint.clear();
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_aOffset[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_aCol[nCnt] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	m_nLine = 0;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CMeshTrajectory::~CMeshTrajectory()
{

}

//================================================
//初期化処理
//================================================
HRESULT CMeshTrajectory::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//オブジェクトの種類の設定
	SetObjType(CObject::OBJTYPE::TRAJECTORY);

	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	for (int nCntMtx = 0; nCntMtx < 2; nCntMtx++)
	{
		D3DXMATRIX mtxTrans, mtx;					//計算用マトリックス
		D3DXMatrixIdentity(&m_aMtxPoint[nCntMtx]);	//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtx);					//ワールドマトリックスの初期化

													//位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_aOffset[nCntMtx].x, m_aOffset[nCntMtx].y, m_aOffset[nCntMtx].z);
		D3DXMatrixMultiply(&m_aMtxPoint[nCntMtx], &m_aMtxPoint[nCntMtx], &mtxTrans);

		//算出した各パーツのワールドマトリックスと親のワールドマトリックスを掛け合わせる
		D3DXMatrixMultiply(&m_aMtxPoint[nCntMtx], &m_aMtxPoint[nCntMtx], m_pMtxParent);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &mtx);
	}

	//両端の頂点座標と頂点カラーを代入
	for (int nCntVtx = 0; nCntVtx < m_nLine + 1; nCntVtx++)
	{
		//動的確保
		m_aColPoint.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_aColPoint.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_aPosPoint.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_aPosPoint.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		m_aPosPoint[nCntVtx * 2] = D3DXVECTOR3(m_aMtxPoint[0]._41, m_aMtxPoint[0]._42, m_aMtxPoint[0]._43);
		m_aPosPoint[nCntVtx * 2 + 1] = D3DXVECTOR3(m_aMtxPoint[1]._41, m_aMtxPoint[1]._42, m_aMtxPoint[1]._43);
		m_aColPoint[nCntVtx * 2] = m_aCol[0];
		m_aColPoint[nCntVtx * 2 + 1] = m_aCol[1];
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2 * (m_nLine + 1),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);

	VERTEX_3D *pVtx;
	//頂点バッファをロックし、頂点データのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	int nNum = 0;
	for (int nVertical = 0; nVertical < 2; nVertical++)
	{
		for (int nLine = 0; nLine < m_nLine + 1; nLine++, nNum++)
		{
			//位置
			pVtx[nNum].pos = m_aPosPoint[nNum];
			//カラー
			pVtx[nNum].col = m_aColPoint[nNum];
			//法線
			pVtx[nNum].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}

	nNum = 0;
	for (int nLine = 0; nLine < m_nLine + 1; nLine++)
	{
		//テクスチャ
		pVtx[nNum].tex = D3DXVECTOR2(0.0f + (1.0f / m_nLine * nLine), 0.0f);
		pVtx[nNum + 1].tex = D3DXVECTOR2(0.0f + (1.0f / m_nLine * nLine), 1.0f);
		nNum += 2;
	}
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================
//終了処理
//================================================
void CMeshTrajectory::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CMeshTrajectory::Update(void)
{
	
}

//================================================
//描画処理
//================================================
void CMeshTrajectory::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	for (int nCntMtx = 0; nCntMtx < 2; nCntMtx++)
	{
		D3DXMATRIX mtxTrans, mtx;					//計算用マトリックス
		D3DXMatrixIdentity(&m_aMtxPoint[nCntMtx]);	//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtx);					//ワールドマトリックスの初期化

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_aOffset[nCntMtx].x, m_aOffset[nCntMtx].y, m_aOffset[nCntMtx].z);
		D3DXMatrixMultiply(&m_aMtxPoint[nCntMtx], &m_aMtxPoint[nCntMtx], &mtxTrans);

		//算出した各パーツのワールドマトリックスと親のワールドマトリックスを掛け合わせる
		D3DXMatrixMultiply(&m_aMtxPoint[nCntMtx], &m_aMtxPoint[nCntMtx], m_pMtxParent);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &mtx);
	}

	

	//頂点座標と頂点カラーをずらす
	for (int nCntVtx = m_nLine; nCntVtx > 0; nCntVtx--)
	{
		m_aPosPoint[nCntVtx * 2] = m_aPosPoint[(nCntVtx - 1) * 2];
		m_aPosPoint[nCntVtx * 2 + 1] = m_aPosPoint[(nCntVtx - 1) * 2 + 1];
		m_aColPoint[nCntVtx * 2].a = m_aCol[0].a / (m_nLine + 1) * (m_nLine - nCntVtx);
		m_aColPoint[nCntVtx * 2 + 1].a = m_aCol[1].a / (m_nLine + 1) * (m_nLine - nCntVtx);
	}

	//両端の頂点座標と頂点カラーを代入
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_aPosPoint[nCnt] = D3DXVECTOR3(m_aMtxPoint[nCnt]._41, m_aMtxPoint[nCnt]._42, m_aMtxPoint[nCnt]._43);
		m_aColPoint[nCnt] = m_aCol[nCnt];
	}

	VERTEX_3D *pVtx;	// 頂点情報
	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntVtx = 0; nCntVtx < (m_nLine + 1) * 2; nCntVtx++)
	{
		pVtx[nCntVtx].pos = m_aPosPoint[nCntVtx];
		pVtx[nCntVtx].col = m_aColPoint[nCntVtx];
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// カリングを行わない
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				

	//アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 50);


	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetFVF(FVF_VERTEX_3D);					//頂点フォーマットの設定
	
	pDevice->SetTexture(0, m_pTexture);				//テクスチャの設定
	
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
		0,											//開始する頂点のインデックス
		m_nLine);									//描画するプリミティブ数

	//アルファテスト元に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	//ライティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	// カリングを行う
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				
}

//================================================
//生成処理
//================================================
CMeshTrajectory* CMeshTrajectory::Create(int nLine, D3DXMATRIX *pMtx, D3DXVECTOR3 offset1, D3DXVECTOR3 offset2, D3DXCOLOR col1, D3DXCOLOR col2)
{
	//インスタンスの生成
	CMeshTrajectory *pMeshTrajectory = nullptr;
	if (pMeshTrajectory == nullptr)
	{
		pMeshTrajectory = new CMeshTrajectory;
		if (pMeshTrajectory != nullptr)
		{
			//変数初期化
			pMeshTrajectory->m_nLine = nLine;
			pMeshTrajectory->m_pMtxParent = pMtx;
			pMeshTrajectory->m_aOffset[0] = offset1;
			pMeshTrajectory->m_aOffset[1] = offset2;
			pMeshTrajectory->m_aCol[0] = col1;
			pMeshTrajectory->m_aCol[1] = col2;
			//初期化処理
			pMeshTrajectory->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}
	return pMeshTrajectory;
}

//================================================
//テクスチャ割り当て処理
//================================================
void CMeshTrajectory::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//================================================
//球と各頂点との衝突判定
//================================================
bool CMeshTrajectory::CollisionSphere(CObject *pSubjectObject, float fObjectRadius)
{
	//衝突しているかどうか
	bool bColl = false;
	//オブジェクト情報を入れるポインタ
	CObject *pObject = nullptr;
	//オブジェクト情報を保存するポインタ変数
	CObject *pSaveObject = nullptr;

	//先頭のポインタを代入
	pObject = pObject->GetTopObj(CObject::PRIORITY_TRAJECTORY);

	while (pObject != nullptr)
	{
		//現在のオブジェクトのポインタを保存
		pSaveObject = pObject;

		//オブジェクトの種類が敵だったら
		if (pObject->GetObjType() == CObject::OBJTYPE::TRAJECTORY)
		{
			//メッシュ軌跡にキャスト
			CMeshTrajectory *pMeshTrajectory = nullptr;
			pMeshTrajectory = (CMeshTrajectory*)pObject;

			//オブジェクトの位置を取得
			D3DXVECTOR3 posObj = pSubjectObject->GetPos();

			for (int nCntVtx = 0; nCntVtx < 2; nCntVtx++)
			{
				//自身から対象のオブジェクトまでの距離を求める
				float fRadius = sqrtf((posObj.x - pMeshTrajectory->m_aPosPoint[nCntVtx].x) * (posObj.x - pMeshTrajectory->m_aPosPoint[nCntVtx].x) +
										(posObj.z - pMeshTrajectory->m_aPosPoint[nCntVtx].z) * (posObj.z - pMeshTrajectory->m_aPosPoint[nCntVtx].z));

				//求めた距離が引数の数値以下だったら
				if (fRadius <= fObjectRadius)
				{
					//衝突している
					bColl = true;
					return bColl;
				}
			}
		}
		//次のオブジェクトに進める
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
	return bColl;
}

