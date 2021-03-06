//================================================
//メッシュフィールド処理
//Author:KatoMizuki
//================================================
#include "renderer.h"
#include "meshfield.h"
#include "object3D.h"
#include "manager.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CMeshField::CMeshField(int nPriority):CObject(nPriority)
{
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
	m_pIdxBuff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_indexPos.clear();
	m_indexSavePos.clear();
	m_bufferPos.clear();
	m_indexRot.clear();
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLine = 0;
	m_nVertical = 0;
	m_indexMtxWorld.clear();
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
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//変数初期化
	m_pos = pos;
	m_size = size;

	//位置・サイズ設定処理
	CObject::SetPos(m_pos);
	CObject::SetSize(m_size);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * ((m_nVertical + 1) * (m_nLine + 1)),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);


	VERTEX_3D *pVtx;
	//頂点バッファをロックし、頂点データのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nNum = 0;
	for (int nVertical = 0; nVertical < m_nVertical + 1; nVertical++)
	{
		for (int nLine = 0; nLine < m_nLine + 1; nLine++, nNum++)
		{
			//要素を追加
			m_bufferPos.push_back(D3DXVECTOR3(-m_size.x / 2.0f + (m_size.x / m_nLine) * nLine,
			                                  0.0f,
			                                  m_size.z / 2.0f - (m_size.z / m_nVertical) * nVertical));

			//頂点座標
			pVtx[nNum].pos = m_bufferPos[nNum];
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
								D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIdxBuff, nullptr);

	WORD *pIdx;		//インデックス情報へのポインタ
	//インデックスバッファをロックし番号データへのポインタを取得
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt1 = 0; nCnt1 < m_nVertical; nCnt1++)
	{
		for (int nCnt2 = 0; nCnt2 < m_nLine + 1; nCnt2++)
		{
			//番号データの設定
			pIdx[(nCnt2 * 2) + 0 + (m_nLine + 2) * 2 * nCnt1] = static_cast<WORD>((m_nLine + 1) + nCnt2 + (m_nLine + 1) * nCnt1);
			pIdx[(nCnt2 * 2) + 1 + (m_nLine + 2) * 2 * nCnt1] = static_cast<WORD>(0 + nCnt2 + (m_nLine + 1) * nCnt1);
			//要素を追加
			m_indexPos.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_indexPos.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_indexSavePos.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_indexSavePos.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			D3DXMATRIX temp;
			m_indexMtxWorld.push_back(temp);
			m_indexMtxWorld.push_back(temp);
			m_indexRot.push_back(m_rot);
			m_indexRot.push_back(m_rot);
		}
	}

	for (int nCnt3 = 0; nCnt3 < m_nVertical - 1; nCnt3++)
	{
		pIdx[((m_nLine + 1) * 2 + 0) * (nCnt3 + 1) + (2 * nCnt3)] = static_cast<WORD>(m_nLine + (m_nLine + 1) * nCnt3);
		pIdx[((m_nLine + 1) * 2 + 1) * (nCnt3 + 1) + (1 * nCnt3)] = static_cast<WORD>(m_nLine * 2 + 2 + (m_nLine + 1) * nCnt3);
		//要素を追加
		m_indexPos.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_indexPos.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_indexSavePos.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_indexSavePos.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		D3DXMATRIX temp;
		m_indexMtxWorld.push_back(temp);
		m_indexMtxWorld.push_back(temp);
		m_indexRot.push_back(m_rot);
		m_indexRot.push_back(m_rot);
	}

	//インデックスバッファをアンロックする
	m_pIdxBuff->Unlock();

	//頂点座標を保存
	for (int nIndexCnt1 = 0; nIndexCnt1 < m_nVertical; nIndexCnt1++)
	{
		for (int nIndexCnt2 = 0; nIndexCnt2 < m_nLine + 1; nIndexCnt2++)
		{
			//位置を設定
			m_indexSavePos[(nIndexCnt2 * 2) + 0 + (m_nLine + 2) * 2 * nIndexCnt1] = m_bufferPos[(m_nLine + 1) + nIndexCnt2 + (m_nLine + 1) * nIndexCnt1];
			m_indexSavePos[(nIndexCnt2 * 2) + 1 + (m_nLine + 2) * 2 * nIndexCnt1] = m_bufferPos[0 + nIndexCnt2 + (m_nLine + 1) * nIndexCnt1];
		}
	}

	for (int nIndexCnt3 = 0; nIndexCnt3 < m_nVertical - 1; nIndexCnt3++)
	{
		//位置を設定
		m_indexSavePos[((m_nLine + 1) * 2 + 0) * (nIndexCnt3 + 1) + (2 * nIndexCnt3)] = m_bufferPos[m_nLine + (m_nLine + 1) * nIndexCnt3];
		m_indexSavePos[((m_nLine + 1) * 2 + 1) * (nIndexCnt3 + 1) + (1 * nIndexCnt3)] = m_bufferPos[(m_nLine * 2 + 2 + (m_nLine + 1) * nIndexCnt3)];
	}


	//オブジェクトの種類の設定
	SetObjType(CObject::OBJTYPE::FLOOR);

	//最初だけ描画する
	Draw();
	//頂点の取得、設定
	GetIndexPos();

	return S_OK;
}

//================================================
//終了処理
//================================================
void CMeshField::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//インデックスバッファの破棄
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
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
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DXMatrixIdentity(&m_mtxWorld);		//ワールドマトリックスの初期化

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
	CMeshField *pMeshField = nullptr;
	if (pMeshField == nullptr)
	{
		pMeshField = new CMeshField;
		if (pMeshField != nullptr)
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

//================================================
//当たり判定
//================================================
bool CMeshField::Collision(CObject * pSubjectObject, float fRadius)
{
	//着地しているかどうか
	bool bLand = false;

	//オブジェクト情報を入れるポインタ
	CObject *pThisObject = nullptr;
	//オブジェクト情報を保存するポインタ変数
	CObject *pSaveObject = nullptr;

	//先頭のポインタを代入
	pThisObject = pThisObject->GetTopObj(CObject::PRIORITY_MESH_FIELD);

	while (pThisObject != nullptr)
	{
		//現在のオブジェクトのポインタを保存
		pSaveObject = pThisObject;

		if (pThisObject->GetObjType() == CObject::OBJTYPE::FLOOR)
		{
			//ポインタをCMeshFieldにキャスト
			CMeshField *pMeshField = nullptr;
			pMeshField = (CMeshField*)pThisObject;

			for (int nCnt1 = 0; nCnt1 < 2 * pMeshField->m_nLine * pMeshField->m_nVertical + (pMeshField->m_nVertical * 4) - 4; nCnt1++)
			{
				//対象の現在位置取得
				D3DXVECTOR3 pos = pSubjectObject->GetPos();
				D3DXVECTOR3 diff = pos - pMeshField->m_indexPos[nCnt1];
				if (D3DXVec3LengthSq(&diff) > fRadius*fRadius)
				{
					continue;
				}

				

				////自身から対象のオブジェクトまでの距離を求める
				//float fSubjectRadius = sqrtf((pos.x - pMeshField->m_indexPos[nCnt1].x) * (pos.x - pMeshField->m_indexPos[nCnt1].x) +
				//                             (pos.z - pMeshField->m_indexPos[nCnt1].z) * (pos.z - pMeshField->m_indexPos[nCnt1].z));

				////指定された範囲内にあるポリゴンだけ当たり判定を行う
				//if (fSubjectRadius > fRadius)
				//{
				//	continue;
				//}

				//各頂点から各頂点のベクトルを算出
				D3DXVECTOR3 vecVtx[VERTEX_3D_NUM - 1];
				
				//偶数
				if (nCnt1 % 2 == 0)
				{
					vecVtx[0] = pMeshField->m_indexPos[nCnt1 + 1] - pMeshField->m_indexPos[nCnt1];
					vecVtx[1] = pMeshField->m_indexPos[nCnt1 + 2] - pMeshField->m_indexPos[nCnt1 + 1];
					vecVtx[2] = pMeshField->m_indexPos[nCnt1] - pMeshField->m_indexPos[nCnt1 + 2];
				}
				else
				{//奇数
					vecVtx[0] = pMeshField->m_indexPos[nCnt1] - pMeshField->m_indexPos[nCnt1 + 2];
					vecVtx[1] = pMeshField->m_indexPos[nCnt1 + 1] - pMeshField->m_indexPos[nCnt1];
					vecVtx[2] = pMeshField->m_indexPos[nCnt1 + 2] - pMeshField->m_indexPos[nCnt1 + 1];
				}

				//法線保存用
				D3DXVECTOR3 vecNor;

				D3DXVECTOR3 vecVtxInv = -vecVtx[2];

				//ポリゴンの法線を求める
				D3DXVec3Cross(&vecNor, &vecVtx[0], &vecVtxInv);

				//nCntが奇数の時
				if (nCnt1 % 2 == 1)
				{
					vecNor *= -1.0f;
				}

				//ベクトルを正規化する(ベクトルの大きさを1にする)
				D3DXVec3Normalize(&vecNor, &vecNor);

				//各頂点から対象の現在位置までのベクトルを算出
				D3DXVECTOR3 vecObj[VERTEX_3D_NUM - 1];
				vecObj[0] = pos - pMeshField->m_indexPos[nCnt1];
				vecObj[1] = pos - pMeshField->m_indexPos[nCnt1 + 1];
				vecObj[2] = pos - pMeshField->m_indexPos[nCnt1 + 2];

				//対象の1フレーム前の位置取得
				D3DXVECTOR3 posOld = pSubjectObject->GetPosOld();

				//各頂点から対象の1フレーム前の位置までのベクトルを算出
				D3DXVECTOR3 vecObjOld[VERTEX_3D_NUM - 1];
				vecObjOld[0] = posOld - pMeshField->m_indexPos[nCnt1];
				vecObjOld[1] = posOld - pMeshField->m_indexPos[nCnt1 + 1];
				vecObjOld[2] = posOld - pMeshField->m_indexPos[nCnt1 + 2];

				//各頂点から対象の現在位置までのベクトルと各頂点から各頂点のベクトルの外積(2D)を求める
				float fvecCross[VERTEX_3D_NUM - 1];
				//各頂点から対象の1フレーム前の位置までのベクトルと各頂点から各頂点のベクトルの外積(2D)を求める
				float fvecCrossOld[VERTEX_3D_NUM - 1];

				for (int nCntVec = 0; nCntVec < VERTEX_3D_NUM - 1; nCntVec++)
				{
					//外積の計算
					fvecCross[nCntVec] = (vecVtx[nCntVec].x * vecObj[nCntVec].z) - (vecObj[nCntVec].x * vecVtx[nCntVec].z);
					fvecCrossOld[nCntVec] = (vecVtx[nCntVec].x * vecObjOld[nCntVec].z) - (vecObjOld[nCntVec].x * vecVtx[nCntVec].z);

					//nCntが奇数の時
					if (nCnt1 % 2 == 1)
					{
						fvecCross[nCntVec] *= -1.0f;
						fvecCrossOld[nCntVec] *= -1.0f;
					}
				}
				
				//ポリゴンの範囲内にいるかどうか
				if ((fvecCross[0] <= 0.0f && fvecCross[1] <= 0.0f && fvecCross[2] <= 0.0f) ||
					(fvecCrossOld[0] <= 0.0f && fvecCrossOld[1] <= 0.0f && fvecCrossOld[2] <= 0.0f))
				{
					//ポリゴンの位置から対象の現在の位置のベクトルを算出
					D3DXVECTOR3 vecPos;
					vecPos = pos - pMeshField->m_indexPos[nCnt1];

					//算出したベクトルと法線のベクトルの内積を求める
					float fVecDot;
					fVecDot = D3DXVec3Dot(&vecNor, &vecPos);

					//ポリゴンの頂点から対象の1フレーム前の位置のベクトルを算出
					D3DXVECTOR3 vecPosOld;
					vecPosOld = posOld - pMeshField->m_indexPos[nCnt1];

					//算出したベクトルと法線のベクトルの内積を求める
					float fVecDotOld;
					fVecDotOld = D3DXVec3Dot(&vecNor, &vecPosOld);

					//内積の計算結果がマイナスの時
					if (fVecDot < 0.0f && fVecDotOld >= -FLT_EPSILON * 10000)
					{
						//押し出す位置を求める
						D3DXVECTOR3 objectPos = pos;

						objectPos.y = pMeshField->m_indexPos[nCnt1].y - 1.0f / vecNor.y *
							          (vecNor.x * (objectPos.x - pMeshField->m_indexPos[nCnt1].x) +
								       vecNor.z * (objectPos.z - pMeshField->m_indexPos[nCnt1].z));

						pSubjectObject->SetPos(objectPos);
						bLand = true;
					}
				}
			}
		}
		pThisObject = pSaveObject->GetObjNext(pSaveObject);
	}
	return bLand;
}

//================================================
//頂点座標設定処理
//================================================
void CMeshField::SetVtxPos(int nNumVtx, D3DXVECTOR3 pos)
{
	VERTEX_3D *pVtx;
	//頂点バッファをロックし、頂点データのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_bufferPos[nNumVtx] = pos;
	//頂点座標
	pVtx[nNumVtx].pos = m_bufferPos[nNumVtx];

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//WORD *pIdx;		//インデックス情報へのポインタ
	////インデックスバッファをロックし番号データへのポインタを取得
	//m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//for (int nCnt1 = 0; nCnt1 < m_nVertical; nCnt1++)
	//{
	//	for (int nCnt2 = 0; nCnt2 < m_nLine + 1; nCnt2++)
	//	{
	//		//番号データの設定
	//		pIdx[(nCnt2 * 2) + 0 + (m_nLine + 2) * 2 * nCnt1] = static_cast<WORD>((m_nLine + 1) + nCnt2 + (m_nLine + 1) * nCnt1);
	//		pIdx[(nCnt2 * 2) + 1 + (m_nLine + 2) * 2 * nCnt1] = static_cast<WORD>(0 + nCnt2 + (m_nLine + 1) * nCnt1);
	//	}
	//}

	//for (int nCnt3 = 0; nCnt3 < m_nVertical - 1; nCnt3++)
	//{
	//	pIdx[((m_nLine + 1) * 2 + 0) * (nCnt3 + 1) + (2 * nCnt3)] = static_cast<WORD>(m_nLine + (m_nLine + 1) * nCnt3);
	//	pIdx[((m_nLine + 1) * 2 + 1) * (nCnt3 + 1) + (1 * nCnt3)] = static_cast<WORD>(m_nLine * 2 + 2 + (m_nLine + 1) * nCnt3);
	//}

	////インデックスバッファをアンロックする
	//m_pIdxBuff->Unlock();

	//頂点座標を保存
	for (int nIndexCnt1 = 0; nIndexCnt1 < m_nVertical; nIndexCnt1++)
	{
		for (int nIndexCnt2 = 0; nIndexCnt2 < m_nLine + 1; nIndexCnt2++)
		{
			//位置を設定
			m_indexSavePos[(nIndexCnt2 * 2) + 0 + (m_nLine + 2) * 2 * nIndexCnt1] = m_bufferPos[(m_nLine + 1) + nIndexCnt2 + (m_nLine + 1) * nIndexCnt1];
			m_indexSavePos[(nIndexCnt2 * 2) + 1 + (m_nLine + 2) * 2 * nIndexCnt1] = m_bufferPos[0 + nIndexCnt2 + (m_nLine + 1) * nIndexCnt1];
		}
	}

	for (int nIndexCnt3 = 0; nIndexCnt3 < m_nVertical - 1; nIndexCnt3++)
	{
		//位置を設定
		m_indexSavePos[((m_nLine + 1) * 2 + 0) * (nIndexCnt3 + 1) + (2 * nIndexCnt3)] = m_bufferPos[m_nLine + (m_nLine + 1) * nIndexCnt3];
		m_indexSavePos[((m_nLine + 1) * 2 + 1) * (nIndexCnt3 + 1) + (1 * nIndexCnt3)] = m_bufferPos[(m_nLine * 2 + 2 + (m_nLine + 1) * nIndexCnt3)];
	}
}

//================================================
//インデックスバッファーの頂点位置取得処理
//================================================
void CMeshField::GetIndexPos(void)
{
	D3DXMATRIX mtxRot, mtxTrans;			//計算用マトリックス

	//親のワールドマトリックス
	D3DXMATRIX mtxParent;

	for (int nCntVtx = 0; nCntVtx < (int)m_indexMtxWorld.size(); nCntVtx++)
	{
		D3DXMatrixIdentity(&m_indexMtxWorld[nCntVtx]);		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxParent);						//ワールドマトリックスの初期化

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_indexMtxWorld[nCntVtx], &m_indexMtxWorld[nCntVtx], &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_indexSavePos[nCntVtx].x, m_indexSavePos[nCntVtx].y, m_indexSavePos[nCntVtx].z);
		D3DXMatrixMultiply(&m_indexMtxWorld[nCntVtx], &m_indexMtxWorld[nCntVtx], &mtxTrans);

		//親のマトリックス
		mtxParent = m_mtxWorld;

		//算出した各パーツのワールドマトリックスと親のワールドマトリックスを掛け合わせる
		D3DXMatrixMultiply(&m_indexMtxWorld[nCntVtx], &m_indexMtxWorld[nCntVtx], &mtxParent);
	}

	//頂点の設定
	for (int nCntVtxPos = 0; nCntVtxPos < (int)m_indexMtxWorld.size(); nCntVtxPos++)
	{
		m_indexPos[nCntVtxPos] = D3DXVECTOR3(m_indexMtxWorld[nCntVtxPos]._41, m_indexMtxWorld[nCntVtxPos]._42, m_indexMtxWorld[nCntVtxPos]._43);
	}
}
