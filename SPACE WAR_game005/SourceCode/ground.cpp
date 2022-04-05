//=======================================================================
//メッシュフィールドに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#include "main.h"
#include "ground.h"
//=======================================================================
//グローバル変数宣言
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureGround[GROUND_TYPE] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGround = NULL;		//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffGround = NULL;			//インデックスバッファへのポインタ
GROUND g_Ground[MAX_GROUND];							//プレイヤー構造体

//=======================================================================
//初期化処理
//=======================================================================
HRESULT InitGround(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//初期化
	for (int nCntGround = 0; nCntGround < MAX_GROUND; nCntGround++)
	{
		g_Ground[nCntGround].fWidth = 1.0f;
		g_Ground[nCntGround].fHeight = 1.0f;
		g_Ground[nCntGround].fDepth = 1.0f;
		g_Ground[nCntGround].nTileX = GROUND_X;	//問題あり
		g_Ground[nCntGround].nTileZ = GROUND_Z;
		g_Ground[nCntGround].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Ground[nCntGround].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Ground[nCntGround].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Ground[nCntGround].bUse = false;
	}


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ground000.png",
		&g_pTextureGround[0]);

	for (int nCntGround = 0; nCntGround < MAX_GROUND; nCntGround++)
	{
		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * ((g_Ground[nCntGround].nTileX + 1) * (g_Ground[nCntGround].nTileZ + 1)) * MAX_GROUND,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffGround,
			NULL);

		VERTEX_3D *pVtx;		//頂点情報へのポインタ

								//頂点バッファをロックし、頂点データのポインタを取得
		g_pVtxBuffGround->Lock(0, 0, (void**)&pVtx, 0);

		int nNum = 0;
		for (int nCntZ = 0; nCntZ < g_Ground[nCntGround].nTileZ + 1; nCntZ++)
		{
			for (int nCntX = 0; nCntX < g_Ground[nCntGround].nTileX + 1; nCntX++, nNum++)
			{
				pVtx[nNum].pos = D3DXVECTOR3(-g_Ground[nCntGround].fWidth / 2.0f + (g_Ground[nCntGround].fWidth / g_Ground[nCntGround].nTileX) * nCntX,
											g_Ground[nCntGround].pos.y,
											g_Ground[nCntGround].fDepth / 2.0f - (g_Ground[nCntGround].fDepth / g_Ground[nCntGround].nTileZ) * nCntZ);

				pVtx[nNum].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
				pVtx[nNum].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				pVtx[nNum].tex = D3DXVECTOR2(0.0f + (1.0f * nCntX), 0.0f + (1.0f * nCntZ));
			}
		}
		nNum = 0;
		pVtx += (g_Ground[nCntGround].nTileX + 1) * (g_Ground[nCntGround].nTileZ + 1);

		//頂点バッファをアンロックする
		g_pVtxBuffGround->Unlock();
	}



	for (int nCntGround = 0; nCntGround < MAX_GROUND; nCntGround++)
	{
		//インデックスバッファの生成
		pDevice->CreateIndexBuffer(sizeof(WORD) * ((g_Ground[nCntGround].nTileZ - 1) * (g_Ground[nCntGround].nTileX + 3) + (g_Ground[nCntGround].nTileX + 1) * (g_Ground[nCntGround].nTileZ + 1)) * MAX_GROUND,
			D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIdxBuffGround, NULL);

		WORD *pIdx;		//インデックス情報へのポインタ
						//インデックスバッファをロックし番号データへのポインタを取得
		g_pIdxBuffGround->Lock(0, 0, (void**)&pIdx, 0);

		for (int nCnt1 = 0; nCnt1 < g_Ground[nCntGround].nTileZ; nCnt1++)
		{
			for (int nCnt2 = 0; nCnt2 < g_Ground[nCntGround].nTileX + 1; nCnt2++)
			{
				//番号データの設定
				pIdx[(nCnt2 * 2) + 0 + (g_Ground[nCntGround].nTileX + 2) * 2 * nCnt1] = (g_Ground[nCntGround].nTileX + 1) + nCnt2 + (g_Ground[nCntGround].nTileX + 1) * nCnt1;
				pIdx[(nCnt2 * 2) + 1 + (g_Ground[nCntGround].nTileX + 2) * 2 * nCnt1] = 0				  + nCnt2 + (g_Ground[nCntGround].nTileX + 1) * nCnt1;
			}
		}
		for (int nCnt3 = 0; nCnt3 < g_Ground[nCntGround].nTileZ - 1; nCnt3++)
		{
			pIdx[((g_Ground[nCntGround].nTileX + 1) * 2 + 0) * (nCnt3 + 1) + (2 * nCnt3 )] = g_Ground[nCntGround].nTileX		 + (g_Ground[nCntGround].nTileX + 1) * nCnt3;
			pIdx[((g_Ground[nCntGround].nTileX + 1) * 2 + 1) * (nCnt3 + 1) + (1 * nCnt3 )] = g_Ground[nCntGround].nTileX * 2 + 2 + (g_Ground[nCntGround].nTileX + 1) * nCnt3;
		}
		pIdx += ((g_Ground[nCntGround].nTileZ - 1) * (g_Ground[nCntGround].nTileX + 3) + (g_Ground[nCntGround].nTileX + 1) * (g_Ground[nCntGround].nTileZ + 1));

		//インデックスバッファをアンロックする
		g_pIdxBuffGround->Unlock();
	}

	return S_OK;
}

//=======================================================================
//終了処理
//=======================================================================
void UninitGround(void)
{
	int nCntGround;
	for (nCntGround = 0; nCntGround < GROUND_TYPE; nCntGround++)
	{
		//テクスチャの破棄
		if (g_pTextureGround[nCntGround] != NULL)
		{
			g_pTextureGround[nCntGround]->Release();
			g_pTextureGround[nCntGround] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffGround != NULL)
	{
		g_pVtxBuffGround->Release();
		g_pVtxBuffGround = NULL;
	}

	//インデックスバッファの破棄
	if (g_pIdxBuffGround != NULL)
	{
		g_pIdxBuffGround->Release();
		g_pIdxBuffGround = NULL;
	}
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateGround(void)
{
	
}

//=======================================================================
//描画処理
//=======================================================================
void DrawGround(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	pDevice = GetDevice();						//デバイスを取得する

	//αテスト
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 180);

	//ライト無効
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntGround = 0; nCntGround < MAX_GROUND; nCntGround++)
	{
		if (g_Ground[nCntGround].bUse == true)
		{
			D3DXMatrixIdentity(&g_Ground[nCntGround].mtxWorld);		//ワールドマトリックスの初期化

			//スケールを反映
			g_Ground[nCntGround].mtxWorld._11 = g_Ground[nCntGround].fWidth;
			g_Ground[nCntGround].mtxWorld._22 = g_Ground[nCntGround].fHeight;
			g_Ground[nCntGround].mtxWorld._33 = g_Ground[nCntGround].fDepth;

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Ground[nCntGround].rot.y, g_Ground[nCntGround].rot.x, g_Ground[nCntGround].rot.z);
			D3DXMatrixMultiply(&g_Ground[nCntGround].mtxWorld, &g_Ground[nCntGround].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Ground[nCntGround].pos.x, g_Ground[nCntGround].pos.y, g_Ground[nCntGround].pos.z);
			D3DXMatrixMultiply(&g_Ground[nCntGround].mtxWorld, &g_Ground[nCntGround].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Ground[nCntGround].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffGround, 0, sizeof(VERTEX_3D));
			//インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_pIdxBuffGround);

			pDevice->SetFVF(FVF_VERTEX_3D);			//頂点フォーマットの設定

			pDevice->SetTexture(0, g_pTextureGround[0]);	//テクスチャの設定

															//ポリゴンの描画
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				0,
				0,
				((g_Ground[nCntGround].nTileX + 1) * (g_Ground[nCntGround].nTileZ + 1)),					//頂点の数
				nCntGround * ((g_Ground[nCntGround].nTileZ - 1) * (g_Ground[nCntGround].nTileX + 3) + (g_Ground[nCntGround].nTileX + 1) * (g_Ground[nCntGround].nTileZ + 1)),	//開始する頂点のインデックス
				2 * g_Ground[nCntGround].nTileX * g_Ground[nCntGround].nTileZ + (g_Ground[nCntGround].nTileZ * 4) - 4);		//描画するプリミティブ数
		}
	}
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=======================================================================
//設定処理
//=======================================================================
void SetGround(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, float fDepth, int nTileX, int nTileZ)
{
	for (int nCntGround = 0; nCntGround < MAX_GROUND; nCntGround++)
	{
		if (g_Ground[nCntGround].bUse == false)
		{
			g_Ground[nCntGround].pos = pos;
			g_Ground[nCntGround].rot = rot;
			g_Ground[nCntGround].fWidth = fWidth;
			g_Ground[nCntGround].fHeight = fHeight;
			g_Ground[nCntGround].fDepth = fDepth;
			g_Ground[nCntGround].nTileX = nTileX;
			g_Ground[nCntGround].nTileZ = nTileZ;
			g_Ground[nCntGround].bUse = true;
			break;
		}
	}
}

//=======================================================================
//取得処理
//=======================================================================
GROUND *GetGround(void)
{
	return &g_Ground[0];
}

