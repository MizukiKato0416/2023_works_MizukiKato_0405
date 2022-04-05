//=======================================================================
//メッシュフィールド(球体)に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#include "main.h"
#include "meshsphere.h"
//=======================================================================
//グローバル変数宣言
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureMeshSphere[MESHSPHERE_TYPE] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshSphere = NULL;				//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshSphere = NULL;				//インデックスバッファへのポインタ
MESHSPHERE g_MeshSphere[MAX_MESHSPHERE];							//メッシュフィールド構造体
//=======================================================================
//初期化処理
//=======================================================================
HRESULT InitMeshSphere(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//初期化
	for (int nCntMeshSphere = 0; nCntMeshSphere < MAX_MESHSPHERE; nCntMeshSphere++)
	{
		g_MeshSphere[nCntMeshSphere].fWidth = MESHSPHERE_WIDTH;
		g_MeshSphere[nCntMeshSphere].fHeight = MESHSPHERE_HEIGHT;
		g_MeshSphere[nCntMeshSphere].fDepth = MESHSPHERE_DEPTH;
		g_MeshSphere[nCntMeshSphere].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshSphere[nCntMeshSphere].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshSphere[nCntMeshSphere].pos = D3DXVECTOR3(0.0f , 0.0f, 0.0f);
	}



	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/sky001.jpg",
		&g_pTextureMeshSphere[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * ((MESHSPHERE_X + 1) * (MESHSPHERE_Y + 1)) * MAX_MESHSPHERE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshSphere,
		NULL);

	VERTEX_3D *pVtx;		//頂点情報へのポインタ

							//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffMeshSphere->Lock(0, 0, (void**)&pVtx, 0);
	
	for (int nCntMeshSphere = 0; nCntMeshSphere < MAX_MESHSPHERE; nCntMeshSphere++)
	{
		int nNum = 0;
		for (int nCntY = 0; nCntY < MESHSPHERE_Y + 1; nCntY++)
		{
			for (int nCntX = 0; nCntX < MESHSPHERE_X + 1; nCntX++, nNum++)
			{
				pVtx[nNum].pos = D3DXVECTOR3(cos((D3DX_PI * 2 / MESHSPHERE_X) * nCntX) * (sin(((D3DX_PI * 2 / MESHSPHERE_X) * nCntY) +((D3DX_PI * 2 / MESHSPHERE_X) * MESHSPHERE_Y)) * (g_MeshSphere[nCntMeshSphere].fWidth / 2.0f)) ,
											sin((D3DX_PI * 2 / MESHSPHERE_X) * nCntY) * (g_MeshSphere[nCntMeshSphere].fWidth / 2.0f),
											(sin((D3DX_PI * 2 / MESHSPHERE_X) * nCntX) * (sin(((D3DX_PI * 2 / MESHSPHERE_X) * nCntY) + ((D3DX_PI * 2 / MESHSPHERE_X) * MESHSPHERE_Y)) * (g_MeshSphere[nCntMeshSphere].fWidth / 2.0f))));


				pVtx[nNum].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
				pVtx[nNum].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				pVtx[nNum].tex = D3DXVECTOR2(0.0f + (1.0f / MESHSPHERE_X * nCntX), 0.0f + (1.0f / MESHSPHERE_Y * nCntY));
			}
		}
		nNum = 0;

		
		pVtx += (MESHSPHERE_X + 1) * (MESHSPHERE_Y + 1);
	}

	

	//頂点バッファをアンロックする
	g_pVtxBuffMeshSphere->Unlock();


	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * ((MESHSPHERE_Y - 1) * (MESHSPHERE_X + 3) + (MESHSPHERE_X + 1) * (MESHSPHERE_Y + 1)) * MAX_MESHSPHERE,
								D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,D3DPOOL_MANAGED, &g_pIdxBuffMeshSphere, NULL);

	WORD *pIdx;		//インデックス情報へのポインタ
	//インデックスバッファをロックし番号データへのポインタを取得
	g_pIdxBuffMeshSphere->Lock(0, 0, (void**)&pIdx, 0);


	for (int nCntMeshSphere = 0; nCntMeshSphere < MAX_MESHSPHERE; nCntMeshSphere++)
	{
		for (int nCnt1 = 0; nCnt1 < MESHSPHERE_Y; nCnt1++)
		{
			for (int nCnt2 = 0; nCnt2 < MESHSPHERE_X + 1; nCnt2++)
			{
				//番号データの設定
				pIdx[(nCnt2 * 2) + 0 + (MESHSPHERE_X + 2) * 2 * nCnt1] = (MESHSPHERE_X + 1) + nCnt2 + (MESHSPHERE_X + 1) * nCnt1;
				pIdx[(nCnt2 * 2) + 1 + (MESHSPHERE_X + 2) * 2 * nCnt1] = 0				  + nCnt2 + (MESHSPHERE_X + 1) * nCnt1;
			}
		}
		for (int nCnt3 = 0; nCnt3 < MESHSPHERE_Y - 1; nCnt3++)
		{
			pIdx[((MESHSPHERE_X + 1) * 2 + 0) * (nCnt3 + 1) + (2 * nCnt3 )] = MESHSPHERE_X		 + (MESHSPHERE_X + 1) * nCnt3;
			pIdx[((MESHSPHERE_X + 1) * 2 + 1) * (nCnt3 + 1) + (1 * nCnt3 )] = MESHSPHERE_X * 2 + 2 + (MESHSPHERE_X + 1) * nCnt3;
		}
		pIdx += ((MESHSPHERE_Y - 1) * (MESHSPHERE_X + 3) + (MESHSPHERE_X + 1) * (MESHSPHERE_Y + 1));
	}


	//インデックスバッファをアンロックする
	g_pIdxBuffMeshSphere->Unlock();

	return S_OK;
}

//=======================================================================
//終了処理
//=======================================================================
void UninitMeshSphere(void)
{
	int nCntMeshSphere;
	for (nCntMeshSphere = 0; nCntMeshSphere < MESHSPHERE_TYPE; nCntMeshSphere++)
	{
		//テクスチャの破棄
		if (g_pTextureMeshSphere[nCntMeshSphere] != NULL)
		{
			g_pTextureMeshSphere[nCntMeshSphere]->Release();
			g_pTextureMeshSphere[nCntMeshSphere] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffMeshSphere != NULL)
	{
		g_pVtxBuffMeshSphere->Release();
		g_pVtxBuffMeshSphere = NULL;
	}

	//インデックスバッファの破棄
	if (g_pIdxBuffMeshSphere != NULL)
	{
		g_pIdxBuffMeshSphere->Release();
		g_pIdxBuffMeshSphere = NULL;
	}
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateMeshSphere(void)
{
	for (int nCntMeshSphere = 0; nCntMeshSphere < MESHSPHERE_TYPE; nCntMeshSphere++)
	{
		g_MeshSphere[nCntMeshSphere].rot.y += 0.00005;
		if (g_MeshSphere[nCntMeshSphere].rot.y >= D3DX_PI)
		{
			g_MeshSphere[nCntMeshSphere].rot.y = -D3DX_PI;
		}
	}

}

//=======================================================================
//描画処理
//=======================================================================
void DrawMeshSphere(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	pDevice = GetDevice();						//デバイスを取得する

	for (int nCntMeshSphere = 0; nCntMeshSphere < MAX_MESHSPHERE; nCntMeshSphere++)
	{
		D3DXMatrixIdentity(&g_MeshSphere[nCntMeshSphere].mtxWorld);		//ワールドマトリックスの初期化

														//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshSphere[nCntMeshSphere].rot.y, g_MeshSphere[nCntMeshSphere].rot.x, g_MeshSphere[nCntMeshSphere].rot.z);
		D3DXMatrixMultiply(&g_MeshSphere[nCntMeshSphere].mtxWorld, &g_MeshSphere[nCntMeshSphere].mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_MeshSphere[nCntMeshSphere].pos.x, g_MeshSphere[nCntMeshSphere].pos.y, g_MeshSphere[nCntMeshSphere].pos.z);
		D3DXMatrixMultiply(&g_MeshSphere[nCntMeshSphere].mtxWorld, &g_MeshSphere[nCntMeshSphere].mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_MeshSphere[nCntMeshSphere].mtxWorld);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffMeshSphere, 0, sizeof(VERTEX_3D));
		//インデックスバッファをデータストリームに設定
		pDevice->SetIndices(g_pIdxBuffMeshSphere);

		pDevice->SetFVF(FVF_VERTEX_3D);			//頂点フォーマットの設定

		pDevice->SetTexture(0, g_pTextureMeshSphere[0]);	//テクスチャの設定

														//ポリゴンの描画
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
			0,
			0,
			((MESHSPHERE_X + 1) * (MESHSPHERE_Y + 1)),					//頂点の数
			nCntMeshSphere * 14,											//開始する頂点のインデックス
			2 * MESHSPHERE_X * MESHSPHERE_Y + (MESHSPHERE_Y * 4) - 4);		//描画するプリミティブ数
	}
}

//=======================================================================
//取得処理
//=======================================================================
MESHSPHERE *GetMeshSphere(void)
{
	return &g_MeshSphere[0];
}

