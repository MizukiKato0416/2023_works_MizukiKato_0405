//=======================================================================
//プレイヤーに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#include "main.h"
#include "shadow.h"
#include "model.h"
#include "enemy.h"


//=======================================================================
//グローバル変数宣言
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureShadow[SHADOW_TYPE] = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;			//頂点バッファへのポインタ
SHADOW g_aShadow[MAX_SHADOW];											//プレイヤー構造体

//=======================================================================
//初期化処理
//=======================================================================
HRESULT InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//初期化
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_aShadow[nCntShadow].fWidth = 50.0f;
		g_aShadow[nCntShadow].fHeight = 0.0f;
		g_aShadow[nCntShadow].fDepth = 50.0f;
		g_aShadow[nCntShadow].nType = 0;
		g_aShadow[nCntShadow].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].bUse = false;
	}


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/shadow000.jpg",
		&g_pTextureShadow[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 *MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	VERTEX_3D *pVtx;		//頂点情報へのポインタ

							//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		pVtx[0].pos = D3DXVECTOR3(-g_aShadow[nCntShadow].fWidth / 2.0f, g_aShadow[nCntShadow].pos.y ,  g_aShadow[nCntShadow].fDepth / 2.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aShadow[nCntShadow].fWidth / 2.0f, g_aShadow[nCntShadow].pos.y ,  g_aShadow[nCntShadow].fDepth / 2.0f);
		pVtx[2].pos = D3DXVECTOR3(- g_aShadow[nCntShadow].fWidth / 2.0f, g_aShadow[nCntShadow].pos.y ,  - g_aShadow[nCntShadow].fDepth / 2.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aShadow[nCntShadow].fWidth / 2.0f, g_aShadow[nCntShadow].pos.y ,  - g_aShadow[nCntShadow].fDepth / 2.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 40);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 40);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 40);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 40);


		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	

	//頂点バッファをアンロックする
	g_pVtxBuffShadow->Unlock();

	return S_OK;
}

//=======================================================================
//終了処理
//=======================================================================
void UninitShadow(void)
{
	int nCntShadow;
	for (nCntShadow = 0; nCntShadow < SHADOW_TYPE; nCntShadow++)
	{
		//テクスチャの破棄
		if (g_pTextureShadow[nCntShadow] != NULL)
		{
			g_pTextureShadow[nCntShadow]->Release();
			g_pTextureShadow[nCntShadow] = NULL;
		}
	}


	//頂点バッファの破棄
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateShadow(void)
{

}

//=======================================================================
//描画処理
//=======================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	


	//αテスト
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 180);

	//zテスト
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//ライト無効
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == true)
		{
			//減算合成の設定
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorld);		//ワールドマトリックスの初期化

			//スケールを反映
//			g_aShadow[nCntShadow].mtxWorld._11 = g_aShadow[nCntShadow].fWidth;
//			g_aShadow[nCntShadow].mtxWorld._22 = g_aShadow[nCntShadow].fHeight;
//			g_aShadow[nCntShadow].mtxWorld._33 = g_aShadow[nCntShadow].fDepth;

																		//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);			//頂点フォーマットの設定

			pDevice->SetTexture(0, g_pTextureShadow[g_aShadow[nCntShadow].nType]);	//テクスチャの設定

																					//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCntShadow * 4,					//開始する頂点のインデックス
				2);					//描画するプリミティブ数
			//通常の合成に戻す
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		}
	}


	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);


	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
}

int SetShadow(D3DXVECTOR3 pos, float fWidth, float fDepth)
{
	int nIdx = -1;
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == false)
		{
			g_aShadow[nCntShadow].pos = pos;
			g_aShadow[nCntShadow].fWidth = fWidth;
			g_aShadow[nCntShadow].fDepth = fDepth;

			g_aShadow[nCntShadow].bUse = true;
			nIdx = nCntShadow;
			break;
		}
	}
	return nIdx;
}

void SetPositionShadow(int nIdx, D3DXVECTOR3 pos , bool bUse)
{
	if (g_aShadow[nIdx].bUse == true)
	{
		g_aShadow[nIdx].pos.x = pos.x;
		//g_aShadow[nIdx].pos.y = pos.y;
		g_aShadow[nIdx].pos.z = pos.z;

		if (bUse == false)
		{
			g_aShadow[nIdx].bUse = false;
		}
	}
}

//=======================================================================
//取得処理
//=======================================================================
SHADOW *GetShadow(void)
{
	return &g_aShadow[0];
}