//=======================================================================
//弾に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#include "main.h"
#include "bullet.h"
#include "shadow.h"
#include "camera.h"
#include "player.h"
#include "effect.h"
#include "modeltxt.h"

//=======================================================================
//グローバル変数宣言
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureBullet[BULLET_TYPE] = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;			//頂点バッファへのポインタ
BULLET g_aBullet[MAX_BULLET];								//壁構造体


//=======================================================================
//初期化処理
//=======================================================================
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//初期化
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].fWidth = BULLET_WIDTH;
		g_aBullet[nCntBullet].fHeight = BULLET_HEIGHT;
		g_aBullet[nCntBullet].fDepth = BULLET_DEPTH;
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].scale = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].bUse = false;
		g_aBullet[nCntBullet].nType = BULLET_MOVETYPE_NOMAL;
	}
	

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/effect000.jpg",
		&g_pTextureBullet[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 *MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_3D *pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		pVtx[0].pos = D3DXVECTOR3(-g_aBullet[nCntBullet].fWidth / 2.0f, g_aBullet[nCntBullet].fHeight / 2.0f, g_aBullet[nCntBullet].fDepth / 2.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].fWidth / 2.0f, g_aBullet[nCntBullet].fHeight / 2.0f, g_aBullet[nCntBullet].fDepth / 2.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aBullet[nCntBullet].fWidth / 2.0f, -g_aBullet[nCntBullet].fHeight / 2.0f, g_aBullet[nCntBullet].fDepth / 2.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].fWidth / 2.0f, -g_aBullet[nCntBullet].fHeight / 2.0f, g_aBullet[nCntBullet].fDepth / 2.0f);

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
	g_pVtxBuffBullet->Unlock();

	return S_OK;
}

//=======================================================================
//終了処理
//=======================================================================
void UninitBullet(void)
{
	int nCntBullet;
	for (nCntBullet = 0; nCntBullet < BULLET_TYPE; nCntBullet++)
	{
		//テクスチャの破棄
		if (g_pTextureBullet[nCntBullet] != NULL)
		{
			g_pTextureBullet[nCntBullet]->Release();
			g_pTextureBullet[nCntBullet] = NULL;
		}
	}


	//頂点バッファの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateBullet(void)
{
	PLAYER *pPlayer = GetPlayer();
	Camera * pCamera;
	pCamera = GetCamera();

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			if (g_aBullet[nCntBullet].pos.x >= 5000.0f || g_aBullet[nCntBullet].pos.x <= -5000.0f ||
				g_aBullet[nCntBullet].pos.z >= 5000.0f || g_aBullet[nCntBullet].pos.z <= -5000.0f)
			{
				g_aBullet[nCntBullet].bUse = false;
			}

			if (pPlayer->nType == PLAYERTYPE_NOMAL)
			{
				SetEffect(D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), 15.0f, 15.0f, D3DXCOLOR(255, 255, 255, 255), 6, EFFEFCT_MOVETYPE_BULLET);
				g_aBullet[nCntBullet].nType = BULLET_MOVETYPE_NOMAL;
			}
			else if (pPlayer->nType == PLAYERTYPE_SPEED)
			{
				SetEffect(D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, 10.0f, D3DXCOLOR(255, 255, 255, 255), 3, EFFEFCT_MOVETYPE_BULLET);
				g_aBullet[nCntBullet].nType = BULLET_MOVETYPE_SPEED;
			}
			else if (pPlayer->nType == PLAYERTYPE_POWER)
			{
				SetEffect(D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), 140.0f, 140.0f, D3DXCOLOR(255, 255, 255, 255), 40, EFFEFCT_MOVETYPE_BULLET);
				g_aBullet[nCntBullet].nType = BULLET_MOVETYPE_POWER;
			}
			//モデルとの当たり判定
			if (CollisionModelTxtBool(&g_aBullet[nCntBullet].pos) == true)
			{
				g_aBullet[nCntBullet].bUse = false;
			}
		}
	}
}

//=======================================================================
//描画処理
//=======================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する

	D3DXMATRIX mtxTrans;				//位置計算用マトリックス
	D3DXMATRIX mtxScale;				//スケール計算用マトリックス

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//αブレンディングを加算合成に設定
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			//αテスト
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 190);


			D3DXMatrixIdentity(&g_aBullet[nCntBullet].mtxWorld);		//ワールドマトリックスの初期化


			pDevice->GetTransform(D3DTS_VIEW, &g_aBullet[nCntBullet].mtxView);	//ビューマトリックスを取得


			//ポリゴンをカメラに対して正面に向ける
			//逆行列を求める	
			g_aBullet[nCntBullet].mtxWorld._11 = g_aBullet[nCntBullet].mtxView._11 * g_aBullet[nCntBullet].scale.x;
			g_aBullet[nCntBullet].mtxWorld._12 = g_aBullet[nCntBullet].mtxView._21 * g_aBullet[nCntBullet].scale.x;
			g_aBullet[nCntBullet].mtxWorld._13 = g_aBullet[nCntBullet].mtxView._31 * g_aBullet[nCntBullet].scale.x;
			g_aBullet[nCntBullet].mtxWorld._21 = g_aBullet[nCntBullet].mtxView._12 * g_aBullet[nCntBullet].scale.y;
			g_aBullet[nCntBullet].mtxWorld._22 = g_aBullet[nCntBullet].mtxView._22 * g_aBullet[nCntBullet].scale.y;
			g_aBullet[nCntBullet].mtxWorld._23 = g_aBullet[nCntBullet].mtxView._32 * g_aBullet[nCntBullet].scale.y;
			g_aBullet[nCntBullet].mtxWorld._31 = g_aBullet[nCntBullet].mtxView._13;
			g_aBullet[nCntBullet].mtxWorld._32 = g_aBullet[nCntBullet].mtxView._23;
			g_aBullet[nCntBullet].mtxWorld._33 = g_aBullet[nCntBullet].mtxView._33;
			//g_aBullet[nCntBullet].mtxWorld._41 = 0.0f;
			//g_aBullet[nCntBullet].mtxWorld._42 = 0.0f;
			//g_aBullet[nCntBullet].mtxWorld._43 = 0.0f;

			//スケールを反映
			//D3DXMatrixScaling(&mtxScale, g_aBullet[nCntBullet].scale.x, g_aBullet[nCntBullet].scale.y, g_aBullet[nCntBullet].scale.z);		//スケール行列を作成
			//D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorld, &g_aBullet[nCntBullet].mtxWorld, &mtxScale);	//スケールを反映

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);		//移動行列を作成
			D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorld, &g_aBullet[nCntBullet].mtxWorld, &mtxTrans);	//移動を反映

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].mtxWorld);

			//Zテスト
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);			//頂点フォーマットの設定

			pDevice->SetTexture(0, g_pTextureBullet[0]);	//テクスチャの設定

															//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCntBullet * 4,					//開始する頂点のインデックス
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
}

//=======================================================================
//弾との当たり判定
//=======================================================================
int CollisionBullet(D3DXVECTOR3 *pPos, float fWidth)
{
	BULLET *pBullet = GetBullet();
	int nDamageType = 0;			//あったているかどうか、何の種類の弾に当たっているか

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == true)
		{
			if (pBullet->pos.x >= pPos->x - fWidth / 2.0f && pBullet->pos.x <= pPos->x + fWidth / 2.0f &&
				pBullet->pos.z >= pPos->z - fWidth / 2.0f && pBullet->pos.z <= pPos->z + fWidth / 2.0f)
			{
				if (g_aBullet[nCntBullet].nType == BULLET_MOVETYPE_NOMAL)
				{
					nDamageType = 1;
					pBullet->bUse = false;
				}
				else if (g_aBullet[nCntBullet].nType == BULLET_MOVETYPE_SPEED)
				{
					nDamageType = 2;
					pBullet->bUse = false;
				}
				else if (g_aBullet[nCntBullet].nType == BULLET_MOVETYPE_POWER)
				{
					nDamageType = 3;
				}
			}
		}
	}

	return nDamageType;
}

//=======================================================================
//設定処理
//=======================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight ,D3DXCOLOR col)
{
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].scale.x = fWidth;
			g_aBullet[nCntBullet].scale.y = fHeight;
			g_aBullet[nCntBullet].col = col;
			g_aBullet[nCntBullet].bUse = true;

			VERTEX_3D *pVtx;		//頂点情報へのポインタ

			//頂点バッファをロックし、頂点データのポインタを取得
			g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

			pVtx[0].col = g_aBullet[nCntBullet].col;
			pVtx[1].col = g_aBullet[nCntBullet].col;
			pVtx[2].col = g_aBullet[nCntBullet].col;
			pVtx[3].col = g_aBullet[nCntBullet].col;

			//頂点バッファをアンロックする
			g_pVtxBuffBullet->Unlock();
			break;
		}
	}
}

BULLET *GetBullet(void)
{
	return &g_aBullet[0];
}