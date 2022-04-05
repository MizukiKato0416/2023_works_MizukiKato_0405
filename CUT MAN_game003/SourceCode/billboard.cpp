//=======================================================================
//ビルボードに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#include "main.h"
#include "billboard.h"
#include "shadow.h"


//=======================================================================
//グローバル変数宣言
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureBillboard[BILLBOARD_TYPE] = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;			//頂点バッファへのポインタ
BILLBOARD g_aBillboard[MAX_BILLBOARD];									//壁構造体


//=======================================================================
//初期化処理
//=======================================================================
HRESULT InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//初期化
	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		g_aBillboard[nCntBillboard].fWidth = BILLBOARD_WIDTH;
		g_aBillboard[nCntBillboard].fHeight = BILLBOARD_HEIGHT;
		g_aBillboard[nCntBillboard].fDepth = BILLBOARD_DEPTH;
		g_aBillboard[nCntBillboard].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBillboard[nCntBillboard].scale = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		g_aBillboard[nCntBillboard].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBillboard[nCntBillboard].bUse = false;
		g_aBillboard[nCntBillboard].nShadow = 0;

	}
	

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/tree001.png",
		&g_pTextureBillboard[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 *MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	VERTEX_3D *pVtx;		//頂点情報へのポインタ

							//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		pVtx[0].pos = D3DXVECTOR3(-g_aBillboard[nCntBillboard].fWidth / 2.0f, g_aBillboard[nCntBillboard].fHeight / 2.0f, g_aBillboard[nCntBillboard].fDepth / 2.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBillboard[nCntBillboard].fWidth / 2.0f, g_aBillboard[nCntBillboard].fHeight / 2.0f, g_aBillboard[nCntBillboard].fDepth / 2.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aBillboard[nCntBillboard].fWidth / 2.0f, -g_aBillboard[nCntBillboard].fHeight / 2.0f, g_aBillboard[nCntBillboard].fDepth / 2.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBillboard[nCntBillboard].fWidth / 2.0f, -g_aBillboard[nCntBillboard].fHeight / 2.0f, g_aBillboard[nCntBillboard].fDepth / 2.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	
	//頂点バッファをアンロックする
	g_pVtxBuffBillboard->Unlock();

	/*for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		SetShadow(D3DXVECTOR3(g_aBillboard[nCntBillboard].pos.x,0.0f, g_aBillboard[nCntBillboard].pos.z), 50.0f, 50.0f);

	}

*/


	return S_OK;
}

//=======================================================================
//終了処理
//=======================================================================
void UninitBillboard(void)
{
	int nCntBillboard;
	for (nCntBillboard = 0; nCntBillboard < BILLBOARD_TYPE; nCntBillboard++)
	{
		//テクスチャの破棄
		if (g_pTextureBillboard[nCntBillboard] != NULL)
		{
			g_pTextureBillboard[nCntBillboard]->Release();
			g_pTextureBillboard[nCntBillboard] = NULL;
		}
	}


	//頂点バッファの破棄
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateBillboard(void)
{
	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_aBillboard[nCntBillboard].bUse == false)
		{
			
		}
	}

}

//=======================================================================
//描画処理
//=======================================================================
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する

	D3DXMATRIX mtxTrans;				//位置計算用マトリックス
	D3DXMATRIX mtxScale;				//スケール計算用マトリックス

	//Zテスト
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);


	//ライト無効
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);


	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_aBillboard[nCntBillboard].bUse == true)
		{
			//αテスト
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 190);

			D3DXMatrixIdentity(&g_aBillboard[nCntBillboard].mtxWorld);		//ワールドマトリックスの初期化


			pDevice->GetTransform(D3DTS_VIEW, &g_aBillboard[nCntBillboard].mtxView);	//ビューマトリックスを取得


			//ポリゴンをカメラに対して正面に向ける
			//逆行列を求める	
			g_aBillboard[nCntBillboard].mtxWorld._11 = g_aBillboard[nCntBillboard].mtxView._11 * g_aBillboard[nCntBillboard].scale.x;
			g_aBillboard[nCntBillboard].mtxWorld._12 = g_aBillboard[nCntBillboard].mtxView._21 * g_aBillboard[nCntBillboard].scale.x;
			g_aBillboard[nCntBillboard].mtxWorld._13 = g_aBillboard[nCntBillboard].mtxView._31 * g_aBillboard[nCntBillboard].scale.x;
			//g_aBillboard[nCntBillboard].mtxWorld._21 = g_aBillboard[nCntBillboard].mtxView._12 * g_aBillboard[nCntBillboard].scale.y;
			g_aBillboard[nCntBillboard].mtxWorld._22 = g_aBillboard[nCntBillboard].mtxView._22 * g_aBillboard[nCntBillboard].scale.y;
			//g_aBillboard[nCntBillboard].mtxWorld._23 = g_aBillboard[nCntBillboard].mtxView._32 * g_aBillboard[nCntBillboard].scale.y;
			g_aBillboard[nCntBillboard].mtxWorld._31 = g_aBillboard[nCntBillboard].mtxView._13;
			g_aBillboard[nCntBillboard].mtxWorld._32 = g_aBillboard[nCntBillboard].mtxView._23;
			g_aBillboard[nCntBillboard].mtxWorld._33 = g_aBillboard[nCntBillboard].mtxView._33;
			//g_aBillboard[nCntBillboard].mtxWorld._41 = 0.0f;
			//g_aBillboard[nCntBillboard].mtxWorld._42 = 0.0f;
			//g_aBillboard[nCntBillboard].mtxWorld._43 = 0.0f;

			//スケールを反映
			//D3DXMatrixScaling(&mtxScale, g_aBillboard[nCntBillboard].scale.x, g_aBillboard[nCntBillboard].scale.y, g_aBillboard[nCntBillboard].scale.z);		//スケール行列を作成
			//D3DXMatrixMultiply(&g_aBillboard[nCntBillboard].mtxWorld, &g_aBillboard[nCntBillboard].mtxWorld, &mtxScale);	//スケールを反映

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aBillboard[nCntBillboard].pos.x, g_aBillboard[nCntBillboard].pos.y, g_aBillboard[nCntBillboard].pos.z);		//移動行列を作成
			D3DXMatrixMultiply(&g_aBillboard[nCntBillboard].mtxWorld, &g_aBillboard[nCntBillboard].mtxWorld, &mtxTrans);	//移動を反映

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBillboard[nCntBillboard].mtxWorld);


			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);			//頂点フォーマットの設定

			pDevice->SetTexture(0, g_pTextureBillboard[0]);	//テクスチャの設定

															//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCntBillboard * 4,					//開始する頂点のインデックス
				2);					//描画するプリミティブ数

			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
		}
	}
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void SetBillboard(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_aBillboard[nCntBillboard].bUse == false)
		{
			g_aBillboard[nCntBillboard].pos = pos;
			g_aBillboard[nCntBillboard].scale.x = fWidth;
			g_aBillboard[nCntBillboard].scale.y = fHeight;

			g_aBillboard[nCntBillboard].bUse = true;

			break;
		}
	}
}

BILLBOARD *GetBillboard(void)
{
	return &g_aBillboard[0];
}