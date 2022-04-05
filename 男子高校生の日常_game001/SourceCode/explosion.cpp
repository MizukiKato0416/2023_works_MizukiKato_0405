//=======================================================================
//爆発に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#include "main.h"
#include "explosion.h"

//マクロ定義
#define MAX_EXPLOSION (128)		//爆発の最大数
#define EXPLOSION_SIZE (30.0f)	//爆発の縦の大きさ
#define EXPLOSION_SIZE2 (30.0f)	//爆発の横の大きさ

//弾の構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXCOLOR  col;				//色
	int nCounterAnim;			//アニメーションカウンタ
	int nPatternAnim;			//アニメーションパターンNo
	bool bUse;					//使用しているかどうか
} Explosion;

//=======================================================================
//グローバル変数宣言
//=======================================================================

LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;		//頂点バッファへのポインタ
Explosion g_aExplosion[MAX_EXPLOSION];

//=======================================================================
//初期化処理
//=======================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//でアイスのポインタ
	int nCntExplosion;

	//デバイスの取得
	pDevice = GetDevice();

	//弾の初期化
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//explosion000.png",
		&g_pTextureExplosion);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);



	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

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
	g_pVtxBuffExplosion->Unlock();
}

//=======================================================================
//終了処理
//=======================================================================
void UninitExplosion(void)
{
	//テクスチャの破棄
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateExplosion(void)
{
	
	int nCntExplosion;
	VERTEX_2D *pVtx;		//頂点情報へのポインタ
							//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{

		if (g_aExplosion[nCntExplosion].bUse == true)
		{

			g_aExplosion[nCntExplosion].nCounterAnim++;
			if (g_aExplosion[nCntExplosion].nCounterAnim == 15)
			{
				g_aExplosion[nCntExplosion].nCounterAnim = 0;		//カウンターを初期地に戻す
				
				pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim *  0.125f + 0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim *  0.125f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f + 0.125f, 1.0f);

				if (g_aExplosion[nCntExplosion].nPatternAnim > 9)
				{
					g_aExplosion[nCntExplosion].nPatternAnim = 0;
					g_aExplosion[nCntExplosion].bUse = false;
				}

				g_aExplosion[nCntExplosion].nPatternAnim++;		//パターンNoを更新


				//頂点バッファをアンロックする
				g_pVtxBuffExplosion->Unlock();
			}

			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_SIZE2, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_SIZE2, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_SIZE2, g_aExplosion[nCntExplosion].pos.y + EXPLOSION_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_SIZE2, g_aExplosion[nCntExplosion].pos.y + EXPLOSION_SIZE, 0.0f);



			if (g_aExplosion[nCntExplosion].pos.x >SCREEN_WIDTH + 30)
			{
				g_aExplosion[nCntExplosion].bUse = false;		//使用していない状態にする
			}

		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}

//=======================================================================
//描画処理
//=======================================================================
void DrawExplosion(void)
{
	int nCntExplosion;

	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する
												//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//頂点フォーマットの設定
	pDevice->SetTexture(0, g_pTextureExplosion);	//テクスチャの設定

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCntExplosion * 4,					//描画を開始する頂点のインデックス
				2);					//描画するプリミティブ数
		}
	}
}

//=======================================================================
//設定処理
//=======================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{
			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].col = col;
			g_aExplosion[nCntExplosion].nCounterAnim = 0;
			g_aExplosion[nCntExplosion].nPatternAnim = 0;
			g_aExplosion[nCntExplosion].bUse = true;



			//頂点座標の設定

			VERTEX_2D *pVtx;		//頂点情報へのポインタ
									//頂点バッファをロックし、頂点データのポインタを取得
			g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += (nCntExplosion * 4);


			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_SIZE2, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_SIZE2, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_SIZE2, g_aExplosion[nCntExplosion].pos.y + EXPLOSION_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_SIZE2, g_aExplosion[nCntExplosion].pos.y + EXPLOSION_SIZE, 0.0f);

			//頂点バッファをアンロックする
			g_pVtxBuffExplosion->Unlock();
			
			break;
		}
	}
}
