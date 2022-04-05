//=======================================================================
//ゲージに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#include "main.h"
#include "enemylife.h"
#include "enemy.h"
#include "shadow.h"
#include "drone.h"


//=======================================================================
//グローバル変数宣言
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureEnemyLife[ENEMYLIFE_TYPE] = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemyLife = NULL;			//頂点バッファへのポインタ
EnemyLife g_aEnemyLife[MAX_ENEMYLIFE];									//ゲージ構造体


//=======================================================================
//初期化処理
//=======================================================================
HRESULT InitEnemyLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//初期化
	for (int nCntEnemyLife = 0; nCntEnemyLife < MAX_ENEMYLIFE; nCntEnemyLife++)
	{
		g_aEnemyLife[nCntEnemyLife].fWidth = ENEMYLIFE_WIDTH;
		g_aEnemyLife[nCntEnemyLife].fHeight = ENEMYLIFE_HEIGHT;
		g_aEnemyLife[nCntEnemyLife].fDepth = ENEMYLIFE_DEPTH;
		g_aEnemyLife[nCntEnemyLife].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemyLife[nCntEnemyLife].scale = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		g_aEnemyLife[nCntEnemyLife].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemyLife[nCntEnemyLife].bUse = false;
		g_aEnemyLife[nCntEnemyLife].nShadow = 0;

	}
	

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/EnemyLife.png",
		&g_pTextureEnemyLife[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 *MAX_ENEMYLIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemyLife,
		NULL);

	VERTEX_3D *pVtx;		//頂点情報へのポインタ

							//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffEnemyLife->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemyLife = 0; nCntEnemyLife < MAX_ENEMYLIFE; nCntEnemyLife++)
	{
		pVtx[0].pos = D3DXVECTOR3(-g_aEnemyLife[nCntEnemyLife].fWidth / 2.0f, g_aEnemyLife[nCntEnemyLife].fHeight / 2.0f, g_aEnemyLife[nCntEnemyLife].fDepth / 2.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemyLife[nCntEnemyLife].fWidth / 2.0f, g_aEnemyLife[nCntEnemyLife].fHeight / 2.0f, g_aEnemyLife[nCntEnemyLife].fDepth / 2.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aEnemyLife[nCntEnemyLife].fWidth / 2.0f, -g_aEnemyLife[nCntEnemyLife].fHeight / 2.0f, g_aEnemyLife[nCntEnemyLife].fDepth / 2.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemyLife[nCntEnemyLife].fWidth / 2.0f, -g_aEnemyLife[nCntEnemyLife].fHeight / 2.0f, g_aEnemyLife[nCntEnemyLife].fDepth / 2.0f);

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
	g_pVtxBuffEnemyLife->Unlock();
	return S_OK;
}

//=======================================================================
//終了処理
//=======================================================================
void UninitEnemyLife(void)
{
	int nCntEnemyLife;
	for (nCntEnemyLife = 0; nCntEnemyLife < ENEMYLIFE_TYPE; nCntEnemyLife++)
	{
		//テクスチャの破棄
		if (g_pTextureEnemyLife[nCntEnemyLife] != NULL)
		{
			g_pTextureEnemyLife[nCntEnemyLife]->Release();
			g_pTextureEnemyLife[nCntEnemyLife] = NULL;
		}
	}


	//頂点バッファの破棄
	if (g_pVtxBuffEnemyLife != NULL)
	{
		g_pVtxBuffEnemyLife->Release();
		g_pVtxBuffEnemyLife = NULL;
	}
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateEnemyLife(void)
{
	DRONE *pDrone = GetDrone();
	ENEMY *pEnemy = GetEnemy();
	int nEnemy = GetUseEnemy();

	for (int nCntEnemyLife = 0; nCntEnemyLife < MAX_ENEMYLIFE; nCntEnemyLife++)
	{
		if (g_aEnemyLife[nCntEnemyLife].bUse == true)
		{
			
		}
		
	}

}

//=======================================================================
//描画処理
//=======================================================================
void DrawEnemyLife(void)
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


	for (int nCntEnemyLife = 0; nCntEnemyLife < MAX_ENEMYLIFE; nCntEnemyLife++)
	{
		if (g_aEnemyLife[nCntEnemyLife].bUse == true)
		{
			//αテスト
			//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			//pDevice->SetRenderState(D3DRS_ALPHAREF, 190);

			D3DXMatrixIdentity(&g_aEnemyLife[nCntEnemyLife].mtxWorld);		//ワールドマトリックスの初期化


			pDevice->GetTransform(D3DTS_VIEW, &g_aEnemyLife[nCntEnemyLife].mtxView);	//ビューマトリックスを取得


			//ポリゴンをカメラに対して正面に向ける
			//逆行列を求める	
			g_aEnemyLife[nCntEnemyLife].mtxWorld._11 = g_aEnemyLife[nCntEnemyLife].mtxView._11 * g_aEnemyLife[nCntEnemyLife].scale.x;
			g_aEnemyLife[nCntEnemyLife].mtxWorld._12 = g_aEnemyLife[nCntEnemyLife].mtxView._21 * g_aEnemyLife[nCntEnemyLife].scale.x;
			g_aEnemyLife[nCntEnemyLife].mtxWorld._13 = g_aEnemyLife[nCntEnemyLife].mtxView._31 * g_aEnemyLife[nCntEnemyLife].scale.x;
			//g_aEnemyLife[nCntEnemyLife].mtxWorld._21 = g_aEnemyLife[nCntEnemyLife].mtxView._12 * g_aEnemyLife[nCntEnemyLife].scale.y;
			g_aEnemyLife[nCntEnemyLife].mtxWorld._22 = g_aEnemyLife[nCntEnemyLife].mtxView._22 * g_aEnemyLife[nCntEnemyLife].scale.y;
			//g_aEnemyLife[nCntEnemyLife].mtxWorld._23 = g_aEnemyLife[nCntEnemyLife].mtxView._32 * g_aEnemyLife[nCntEnemyLife].scale.y;
			g_aEnemyLife[nCntEnemyLife].mtxWorld._31 = g_aEnemyLife[nCntEnemyLife].mtxView._13;
			g_aEnemyLife[nCntEnemyLife].mtxWorld._32 = g_aEnemyLife[nCntEnemyLife].mtxView._23;
			g_aEnemyLife[nCntEnemyLife].mtxWorld._33 = g_aEnemyLife[nCntEnemyLife].mtxView._33;
			//g_aEnemyLife[nCntEnemyLife].mtxWorld._41 = 0.0f;
			//g_aEnemyLife[nCntEnemyLife].mtxWorld._42 = 0.0f;
			//g_aEnemyLife[nCntEnemyLife].mtxWorld._43 = 0.0f;

			//スケールを反映
			//D3DXMatrixScaling(&mtxScale, g_aEnemyLife[nCntEnemyLife].scale.x, g_aEnemyLife[nCntEnemyLife].scale.y, g_aEnemyLife[nCntEnemyLife].scale.z);		//スケール行列を作成
			//D3DXMatrixMultiply(&g_aEnemyLife[nCntEnemyLife].mtxWorld, &g_aEnemyLife[nCntEnemyLife].mtxWorld, &mtxScale);	//スケールを反映

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aEnemyLife[nCntEnemyLife].pos.x, g_aEnemyLife[nCntEnemyLife].pos.y, g_aEnemyLife[nCntEnemyLife].pos.z);		//移動行列を作成
			D3DXMatrixMultiply(&g_aEnemyLife[nCntEnemyLife].mtxWorld, &g_aEnemyLife[nCntEnemyLife].mtxWorld, &mtxTrans);	//移動を反映

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemyLife[nCntEnemyLife].mtxWorld);


			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffEnemyLife, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);			//頂点フォーマットの設定

			pDevice->SetTexture(0, g_pTextureEnemyLife[0]);	//テクスチャの設定

															//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCntEnemyLife * 4,					//開始する頂点のインデックス
				2);					//描画するプリミティブ数

			//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
			//pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
		}
	}
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}


//===========================================
//設定処理
//===========================================
int SetEnemyLife(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	int nIdx = -1;
	for (int nCntEnemyLife = 0; nCntEnemyLife < MAX_ENEMYLIFE; nCntEnemyLife++)
	{
		if (g_aEnemyLife[nCntEnemyLife].bUse == false)
		{
			g_aEnemyLife[nCntEnemyLife].pos = pos;
			g_aEnemyLife[nCntEnemyLife].scale.x = fWidth;
			g_aEnemyLife[nCntEnemyLife].scale.y = fHeight;

			g_aEnemyLife[nCntEnemyLife].bUse = true;
			nIdx = nCntEnemyLife;
			break;
		}
	}
	return nIdx;
}

//===========================================
//位置更新処理
//===========================================
void SetPositionEnemyLife(int nIdx, D3DXVECTOR3 pos, bool bUse, int nMaxlife, int nLife, float fWidth)
{
	if (g_aEnemyLife[nIdx].bUse == true)
	{
		g_aEnemyLife[nIdx].pos.x = pos.x;
		g_aEnemyLife[nIdx].pos.y = pos.y;
		g_aEnemyLife[nIdx].pos.z = pos.z;

		g_aEnemyLife[nIdx].scale.x = fWidth / nMaxlife * nLife;

		if (bUse == false)
		{
			g_aEnemyLife[nIdx].bUse = false;
		}
	}
}

EnemyLife *GetEnemyLife(void)
{
	return &g_aEnemyLife[0];
}