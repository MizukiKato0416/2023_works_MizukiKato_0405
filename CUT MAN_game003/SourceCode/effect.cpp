//=======================================================================
//壁に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#include "main.h"
#include "effect.h"
#include "shadow.h"


//=======================================================================
//グローバル変数宣言
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureEffect[EFFECT_TYPE] = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;			//頂点バッファへのポインタ
EFFECT g_aEffect[MAX_EFFECT];									//壁構造体


//=======================================================================
//初期化処理
//=======================================================================
HRESULT InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//初期化
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].fWidth = EFFECT_WIDTH;
		g_aEffect[nCntEffect].fHeight = EFFECT_HEIGHT;
		g_aEffect[nCntEffect].fDepth = EFFECT_DEPTH;
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].scale = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].bUse = false;

	}
	

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/effect000.jpg",
		&g_pTextureEffect[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 *MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	VERTEX_3D *pVtx;		//頂点情報へのポインタ

							//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fWidth / 2.0f, g_aEffect[nCntEffect].fHeight / 2.0f, g_aEffect[nCntEffect].fDepth / 2.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fWidth / 2.0f, g_aEffect[nCntEffect].fHeight / 2.0f, g_aEffect[nCntEffect].fDepth / 2.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fWidth / 2.0f, -g_aEffect[nCntEffect].fHeight / 2.0f, g_aEffect[nCntEffect].fDepth / 2.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fWidth / 2.0f, -g_aEffect[nCntEffect].fHeight / 2.0f, g_aEffect[nCntEffect].fDepth / 2.0f);

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
	g_pVtxBuffEffect->Unlock();

	return S_OK;
}

//=======================================================================
//終了処理
//=======================================================================
void UninitEffect(void)
{
	int nCntEffect;
	for (nCntEffect = 0; nCntEffect < EFFECT_TYPE; nCntEffect++)
	{
		//テクスチャの破棄
		if (g_pTextureEffect[nCntEffect] != NULL)
		{
			g_pTextureEffect[nCntEffect]->Release();
			g_pTextureEffect[nCntEffect] = NULL;
		}
	}


	//頂点バッファの破棄
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateEffect(void)
{
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			g_aEffect[nCntEffect].pos += g_aEffect[nCntEffect].move;
			g_aEffect[nCntEffect].nLife--;
			if (g_aEffect[nCntEffect].nLife <= 0)
			{
				g_aEffect[nCntEffect].nLife = 0;
				g_aEffect[nCntEffect].bUse = false;
			}
			
			if (g_aEffect[nCntEffect].nType == EFFEFCT_MOVETYPE_ENEMY_DEATH)
			{
				g_aEffect[nCntEffect].move.y -= 0.1f;
				if (g_aEffect[nCntEffect].pos.y <= 0.0f)
				{
					g_aEffect[nCntEffect].move.y = 0.5f;
				}
			}
		}
	}

}

//=======================================================================
//描画処理
//=======================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する

	D3DXMATRIX mtxTrans;				//位置計算用マトリックス
	D3DXMATRIX mtxScale;				//スケール計算用マトリックス


	//ライト無効
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);


	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{

			//αブレンディングを加算合成に設定
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			//αテスト
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 190);

			D3DXMatrixIdentity(&g_aEffect[nCntEffect].mtxWorld);		//ワールドマトリックスの初期化


			pDevice->GetTransform(D3DTS_VIEW, &g_aEffect[nCntEffect].mtxView);	//ビューマトリックスを取得


			//ポリゴンをカメラに対して正面に向ける
			//逆行列を求める	
			g_aEffect[nCntEffect].mtxWorld._11 = g_aEffect[nCntEffect].mtxView._11 * g_aEffect[nCntEffect].scale.x;
			g_aEffect[nCntEffect].mtxWorld._12 = g_aEffect[nCntEffect].mtxView._21 * g_aEffect[nCntEffect].scale.x;
			g_aEffect[nCntEffect].mtxWorld._13 = g_aEffect[nCntEffect].mtxView._31 * g_aEffect[nCntEffect].scale.x;
			g_aEffect[nCntEffect].mtxWorld._21 = g_aEffect[nCntEffect].mtxView._12 * g_aEffect[nCntEffect].scale.y;
			g_aEffect[nCntEffect].mtxWorld._22 = g_aEffect[nCntEffect].mtxView._22 * g_aEffect[nCntEffect].scale.y;
			g_aEffect[nCntEffect].mtxWorld._23 = g_aEffect[nCntEffect].mtxView._32 * g_aEffect[nCntEffect].scale.y;
			g_aEffect[nCntEffect].mtxWorld._31 = g_aEffect[nCntEffect].mtxView._13;
			g_aEffect[nCntEffect].mtxWorld._32 = g_aEffect[nCntEffect].mtxView._23;
			g_aEffect[nCntEffect].mtxWorld._33 = g_aEffect[nCntEffect].mtxView._33;
			//g_aEffect[nCntEffect].mtxWorld._41 = 0.0f;
			//g_aEffect[nCntEffect].mtxWorld._42 = 0.0f;
			//g_aEffect[nCntEffect].mtxWorld._43 = 0.0f;

			//スケールを反映
			//D3DXMatrixScaling(&mtxScale, g_aEffect[nCntEffect].scale.x, g_aEffect[nCntEffect].scale.y, g_aEffect[nCntEffect].scale.z);		//スケール行列を作成
			//D3DXMatrixMultiply(&g_aEffect[nCntEffect].mtxWorld, &g_aEffect[nCntEffect].mtxWorld, &mtxScale);	//スケールを反映

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCntEffect].pos.x, g_aEffect[nCntEffect].pos.y, g_aEffect[nCntEffect].pos.z);		//移動行列を作成
			D3DXMatrixMultiply(&g_aEffect[nCntEffect].mtxWorld, &g_aEffect[nCntEffect].mtxWorld, &mtxTrans);	//移動を反映

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCntEffect].mtxWorld);

			//Zテスト
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);			//頂点フォーマットの設定

			pDevice->SetTexture(0, g_pTextureEffect[0]);	//テクスチャの設定

															//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCntEffect * 4,					//開始する頂点のインデックス
				2);					//描画するプリミティブ数

			
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

			//aブレンディングを通常に戻す
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
	}

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, D3DXCOLOR col, int nLife, EFFECT_MOVETYPE nType)
{
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].move = move;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].nType = nType;
			g_aEffect[nCntEffect].scale.x = fWidth;
			g_aEffect[nCntEffect].scale.y = fHeight;

			g_aEffect[nCntEffect].bUse = true;

			VERTEX_3D *pVtx;		//頂点情報へのポインタ
			//頂点バッファをロックし、頂点データのポインタを取得
			g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += nCntEffect * 4;

			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;

			//頂点バッファをアンロックする
			g_pVtxBuffEffect->Unlock();
			break;
		}
	}
}

EFFECT *GetEffect(void)
{
	return &g_aEffect[0];
}