//=======================================================================
//メッシュフィールドに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#include "main.h"
#include "meshfield.h"
//=======================================================================
//グローバル変数宣言
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureMeshField[MESHFIELD_TYPE] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;				//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;				//インデックスバッファへのポインタ
MESHFIELD g_MeshField[MAX_MESHFIELD];							//メッシュフィールド構造体
D3DXVECTOR3 g_rotMeshField;										//向き

//=======================================================================
//初期化処理
//=======================================================================
HRESULT InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//初期化
	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		g_MeshField[nCntMeshField].fWidth = MESHFIELD_WIDTH;
		g_MeshField[nCntMeshField].fHeight = MESHFIELD_HEIGHT;
		g_MeshField[nCntMeshField].fDepth = MESHFIELD_DEPTH;
		g_MeshField[nCntMeshField].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshField[nCntMeshField].pos = D3DXVECTOR3(800.0f * (nCntMeshField + 1), 0.0f, 0.0f);
	}

	g_rotMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/road000.jpg",
		&g_pTextureMeshField[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * ((MESHFIELD_X + 1) * (MESHFIELD_Z + 1)) * MAX_MESHFIELD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);

	VERTEX_3D *pVtx;		//頂点情報へのポインタ

							//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);
	
	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		int nNum = 0;
		for (int nCntZ = 0; nCntZ < MESHFIELD_Z + 1; nCntZ++)
		{
			for (int nCntX = 0; nCntX < MESHFIELD_X + 1; nCntX++, nNum++)
			{
				pVtx[nNum].pos = D3DXVECTOR3(-g_MeshField[nCntMeshField].fWidth / 2.0f + (g_MeshField[nCntMeshField].fWidth / MESHFIELD_X) * nCntX,
											g_MeshField[nCntMeshField].pos.y,
											g_MeshField[nCntMeshField].fDepth / 2.0f - (g_MeshField[nCntMeshField].fDepth / MESHFIELD_Z) * nCntZ);

				pVtx[nNum].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
				pVtx[nNum].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				pVtx[nNum].tex = D3DXVECTOR2(0.0f + (1.0f * nCntX), 0.0f + (1.0f * nCntZ));
				//pVtx[nNum].tex = D3DXVECTOR2(0.0f + (1.0f * nCntX), 0.0f + (0.0f * (1.0f * nCntZ)));
			}
		}
		nNum = 0;

		/*pVtx[0].pos = D3DXVECTOR3(g_MeshField[nCntMeshField].pos.x * (nCntMeshField + 1) - g_MeshField[nCntMeshField].fWidth / 2.0f, g_MeshField[nCntMeshField].pos.y + g_MeshField[nCntMeshField].fHeight / 2.0f, g_MeshField[nCntMeshField].pos.z + g_MeshField[nCntMeshField].fDepth / 2.0f);
		pVtx[1].pos = D3DXVECTOR3(g_MeshField[nCntMeshField].pos.x * (nCntMeshField + 1), g_MeshField[nCntMeshField].pos.y + g_MeshField[nCntMeshField].fHeight / 2.0f, g_MeshField[nCntMeshField].pos.z + g_MeshField[nCntMeshField].fDepth / 2.0f);
		pVtx[2].pos = D3DXVECTOR3(g_MeshField[nCntMeshField].pos.x * (nCntMeshField + 1) + g_MeshField[nCntMeshField].fWidth / 2.0f, g_MeshField[nCntMeshField].pos.y + g_MeshField[nCntMeshField].fHeight / 2.0f, g_MeshField[nCntMeshField].pos.z + g_MeshField[nCntMeshField].fDepth / 2.0f);
		pVtx[3].pos = D3DXVECTOR3(g_MeshField[nCntMeshField].pos.x * (nCntMeshField + 1) - g_MeshField[nCntMeshField].fWidth / 2.0f, g_MeshField[nCntMeshField].pos.y + g_MeshField[nCntMeshField].fHeight / 2.0f, g_MeshField[nCntMeshField].pos.z);
		pVtx[4].pos = D3DXVECTOR3(g_MeshField[nCntMeshField].pos.x * (nCntMeshField + 1), g_MeshField[nCntMeshField].pos.y + g_MeshField[nCntMeshField].fHeight / 2.0f, g_MeshField[nCntMeshField].pos.z);
		pVtx[5].pos = D3DXVECTOR3(g_MeshField[nCntMeshField].pos.x * (nCntMeshField + 1) + g_MeshField[nCntMeshField].fWidth / 2.0f, g_MeshField[nCntMeshField].pos.y + g_MeshField[nCntMeshField].fHeight / 2.0f, g_MeshField[nCntMeshField].pos.z);
		pVtx[6].pos = D3DXVECTOR3(g_MeshField[nCntMeshField].pos.x * (nCntMeshField + 1) - g_MeshField[nCntMeshField].fWidth / 2.0f, g_MeshField[nCntMeshField].pos.y + g_MeshField[nCntMeshField].fHeight / 2.0f, g_MeshField[nCntMeshField].pos.z - g_MeshField[nCntMeshField].fDepth / 2.0f);
		pVtx[7].pos = D3DXVECTOR3(g_MeshField[nCntMeshField].pos.x * (nCntMeshField + 1), g_MeshField[nCntMeshField].pos.y + g_MeshField[nCntMeshField].fHeight / 2.0f, g_MeshField[nCntMeshField].pos.z - g_MeshField[nCntMeshField].fDepth / 2.0f);
		pVtx[8].pos = D3DXVECTOR3(g_MeshField[nCntMeshField].pos.x * (nCntMeshField + 1) + g_MeshField[nCntMeshField].fWidth / 2.0f, g_MeshField[nCntMeshField].pos.y + g_MeshField[nCntMeshField].fHeight / 2.0f, g_MeshField[nCntMeshField].pos.z - g_MeshField[nCntMeshField].fDepth / 2.0f);



		pVtx[0].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[4].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[5].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[6].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[7].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[8].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);


		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);


		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(2.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[4].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[5].tex = D3DXVECTOR2(2.0f, 1.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 2.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 2.0f);
		pVtx[8].tex = D3DXVECTOR2(2.0f, 2.0f);

		pVtx += 9;*/
		pVtx += (MESHFIELD_X + 1) * (MESHFIELD_Z + 1);
	}

	

	//頂点バッファをアンロックする
	g_pVtxBuffMeshField->Unlock();


	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * ((MESHFIELD_Z - 1) * (MESHFIELD_X + 3) + (MESHFIELD_X + 1) * (MESHFIELD_Z + 1)) * MAX_MESHFIELD,
								D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,D3DPOOL_MANAGED, &g_pIdxBuffMeshField, NULL);

	WORD *pIdx;		//インデックス情報へのポインタ
	//インデックスバッファをロックし番号データへのポインタを取得
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);


	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		for (int nCnt1 = 0; nCnt1 < MESHFIELD_Z; nCnt1++)
		{
			for (int nCnt2 = 0; nCnt2 < MESHFIELD_X + 1; nCnt2++)
			{
				//番号データの設定
				pIdx[(nCnt2 * 2) + 0 + (MESHFIELD_X + 2) * 2 * nCnt1] = (MESHFIELD_X + 1) + nCnt2 + (MESHFIELD_X + 1) * nCnt1;
				pIdx[(nCnt2 * 2) + 1 + (MESHFIELD_X + 2) * 2 * nCnt1] = 0				  + nCnt2 + (MESHFIELD_X + 1) * nCnt1;
			}
		}
		for (int nCnt3 = 0; nCnt3 < MESHFIELD_Z - 1; nCnt3++)
		{
			pIdx[((MESHFIELD_X + 1) * 2 + 0) * (nCnt3 + 1) + (2 * nCnt3 )] = MESHFIELD_X		 + (MESHFIELD_X + 1) * nCnt3;
			pIdx[((MESHFIELD_X + 1) * 2 + 1) * (nCnt3 + 1) + (1 * nCnt3 )] = MESHFIELD_X * 2 + 2 + (MESHFIELD_X + 1) * nCnt3;
		}
		pIdx += ((MESHFIELD_Z - 1) * (MESHFIELD_X + 3) + (MESHFIELD_X + 1) * (MESHFIELD_Z + 1));
	}


	//インデックスバッファをアンロックする
	g_pIdxBuffMeshField->Unlock();

	return S_OK;
}

//=======================================================================
//終了処理
//=======================================================================
void UninitMeshField(void)
{
	int nCntMeshField;
	for (nCntMeshField = 0; nCntMeshField < MESHFIELD_TYPE; nCntMeshField++)
	{
		//テクスチャの破棄
		if (g_pTextureMeshField[nCntMeshField] != NULL)
		{
			g_pTextureMeshField[nCntMeshField]->Release();
			g_pTextureMeshField[nCntMeshField] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	//インデックスバッファの破棄
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateMeshField(void)
{
	
}

//=======================================================================
//描画処理
//=======================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	pDevice = GetDevice();						//デバイスを取得する

	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		D3DXMatrixIdentity(&g_MeshField[nCntMeshField].mtxWorld);		//ワールドマトリックスの初期化

														//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);
		D3DXMatrixMultiply(&g_MeshField[nCntMeshField].mtxWorld, &g_MeshField[nCntMeshField].mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_MeshField[nCntMeshField].pos.x, g_MeshField[nCntMeshField].pos.y, g_MeshField[nCntMeshField].pos.z);
		D3DXMatrixMultiply(&g_MeshField[nCntMeshField].mtxWorld, &g_MeshField[nCntMeshField].mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_MeshField[nCntMeshField].mtxWorld);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));
		//インデックスバッファをデータストリームに設定
		pDevice->SetIndices(g_pIdxBuffMeshField);

		pDevice->SetFVF(FVF_VERTEX_3D);			//頂点フォーマットの設定

		pDevice->SetTexture(0, g_pTextureMeshField[0]);	//テクスチャの設定

														//ポリゴンの描画
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
			0,
			0,
			((MESHFIELD_X + 1) * (MESHFIELD_Z + 1)),					//頂点の数
			nCntMeshField * 14,											//開始する頂点のインデックス
			2 * MESHFIELD_X * MESHFIELD_Z + (MESHFIELD_Z * 4) - 4);		//描画するプリミティブ数
	}
}

//=======================================================================
//取得処理
//=======================================================================
MESHFIELD *GetMeshField(void)
{
	return &g_MeshField[0];
}

