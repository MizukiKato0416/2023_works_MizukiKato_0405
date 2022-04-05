//=======================================================================
//タイトルに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "word.h"
#include "block.h"
#include "enemy.h"
#include "item.h"

//=======================================================================
//グローバル変数宣言
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureTitle = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//頂点バッファへのポインタ
int g_nCnt2;
int g_nEnemyCnt;
int g_nEnemyCnt2;

//=======================================================================
//初期化処理
//=======================================================================
void InitTitle(void)
{
	StopSound(SOUND_LABEL_RESULT_BGM);

	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();


	//変数の初期化
	g_nCnt2 = 0;
	g_nEnemyCnt = 0;
	g_nEnemyCnt2 = 1;


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//menu000.jpg",
		&g_pTextureTitle);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D *pVtx;		//頂点情報へのポインタ

							//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);


	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);


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

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	PlaySound(SOUND_LABEL_TITLE_BGM);
	InitWord();
	InitBlock();
	InitEnemy();
	InitItem();

	SetWord(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, -170.0f, 0.0f), 2, D3DXVECTOR3(0.0f, 0.4f, 0.0f), 1000.0f, 300.0f);
	SetWord(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 500.0f, 0.0f), 4, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 100.0f);
	SetMoveBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 80.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, 1, SCREEN_WIDTH, 80.0f, 32.0f ,2.0f);
}

//=======================================================================
//終了処理
//=======================================================================
void UninitTitle(void)
{
	StopSound(SOUND_LABEL_TITLE_BGM);

	//テクスチャの破棄
	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
	UninitWord();
	UninitBlock();
	UninitEnemy();
	UninitItem();

}

//=======================================================================
//更新処理
//=======================================================================
void UpdateTitle(void)
{
	g_nCnt2++;
	//エンターを押したときの処理
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		PlaySound(SOUND_LABEL_DECIDE);
		SetFade(MODE_RULE);
	}
	else if (g_nCnt2 >= 5000)
	{
		g_nCnt2 = 0;
		SetFade(MODE_RESULT);
	}
	UpdateWord();
	UpdateBlock();
	UpdateEnemy();
	UpdateItem();

	g_nEnemyCnt++;

	//エンターを押したときの処理
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		g_nEnemyCnt2 ++;
		if (g_nEnemyCnt2 >= 5)
		{
			g_nEnemyCnt2 = 1;
		}
	}

	if (g_nEnemyCnt >= 300)
	{
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH - 100.0f, -170.0f, 0.0f), 0, D3DXVECTOR3(-0.5f, 0.0f, 0.0f), 1, 100.0f * g_nEnemyCnt2, 100.0f* g_nEnemyCnt2);
		g_nEnemyCnt = 0;
	}

}

//=======================================================================
//描画処理
//=======================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する
												//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//頂点フォーマットの設定
	pDevice->SetTexture(0, g_pTextureTitle);	//テクスチャの設定
											//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,					//開始する頂点のインデックス
		2);					//描画するプリミティブ数

	DrawWord();
	DrawBlock();
	DrawEnemy();
	DrawItem();
}