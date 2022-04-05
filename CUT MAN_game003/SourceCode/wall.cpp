//=======================================================================
//壁に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#include "main.h"
#include "wall.h"
#include "shadow.h"

//=======================================================================
//グローバル変数宣言
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureWall[WALL_TYPE] = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;			//頂点バッファへのポインタ
WALL g_aWall[MAX_WALL];									//壁構造体


//=======================================================================
//初期化処理
//=======================================================================
HRESULT InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//初期化
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_aWall[nCntWall].fWidth = WALL_WIDTH;
		g_aWall[nCntWall].fHeight = WALL_HEIGHT;
		g_aWall[nCntWall].fDepth = WALL_DEPTH;
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].scale = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		g_aWall[nCntWall].bUse = false;
		g_aWall[nCntWall].nNum = 0;

	}
	

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/wall_building000.png",
		&g_pTextureWall[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 *MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	VERTEX_3D *pVtx;		//頂点情報へのポインタ

							//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		pVtx[0].pos = D3DXVECTOR3(-0.5f, 0.5f, g_aWall[nCntWall].fDepth / 2.0f);
		pVtx[1].pos = D3DXVECTOR3(0.5f, 0.5f, g_aWall[nCntWall].fDepth / 2.0f);
		pVtx[2].pos = D3DXVECTOR3(-0.5f, -0.5f, g_aWall[nCntWall].fDepth / 2.0f);
		pVtx[3].pos = D3DXVECTOR3(0.5f, -0.5f, g_aWall[nCntWall].fDepth / 2.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(3.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(3.0f, 1.0f);

		pVtx += 4;
	}
	
	
	//頂点バッファをアンロックする
	g_pVtxBuffWall->Unlock();
	return S_OK;
}

//=======================================================================
//終了処理
//=======================================================================
void UninitWall(void)
{
	int nCntWall;
	for (nCntWall = 0; nCntWall < WALL_TYPE; nCntWall++)
	{
		//テクスチャの破棄
		if (g_pTextureWall[nCntWall] != NULL)
		{
			g_pTextureWall[nCntWall]->Release();
			g_pTextureWall[nCntWall] = NULL;
		}
	}


	//頂点バッファの破棄
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateWall(void)
{
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//SetPositionShadow(g_aWall[nCntWall].nNum, g_aWall[nCntWall].pos);
	}
}

//=======================================================================
//描画処理
//=======================================================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
			D3DXMATRIX mtxRot, mtxTrans, mtxScale;				//計算用マトリックス
			D3DXMatrixIdentity(&g_aWall[nCntWall].mtxWorld);		//ワールドマトリックスの初期化

			//スケールを反映
			g_aWall[nCntWall].mtxWorld._11 = g_aWall[nCntWall].scale.x;
			g_aWall[nCntWall].mtxWorld._22 = g_aWall[nCntWall].scale.y;

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtxWorld);


			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);			//頂点フォーマットの設定

			pDevice->SetTexture(0, g_pTextureWall[0]);	//テクスチャの設定

														//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCntWall * 4,					//開始する頂点のインデックス
				2);					//描画するプリミティブ数
		}		
	}
}

//=======================================================================
//設定処理
//=======================================================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale)
{
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == false)
		{
			g_aWall[nCntWall].scale = scale;
			g_aWall[nCntWall].rot = rot;
			g_aWall[nCntWall].pos = pos;

			g_aWall[nCntWall].bUse = true;





			break;
		}
	}
}