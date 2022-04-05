//=======================================================================
//ライトに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#include "main.h"
#include "light.h"

//=======================================================================
//グローバル変数宣言
//=======================================================================
D3DLIGHT9 g_alight[3];

//=======================================================================
//初期化処理
//=======================================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	D3DXVECTOR3 vecDir[MAX_LIGHT];				//設定用方向ベクトル

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//ライトをクリアする
		ZeroMemory(&g_alight[nCntLight], sizeof(D3DLIGHT9));

		//ライトの種類を設定
		g_alight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;		//平行光源

													//ライトの拡散光を設定
		g_alight[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//ライトの方向を設定
		vecDir[0] = D3DXVECTOR3(-0.4f, 0.8f, 0.4f);
		vecDir[1] = D3DXVECTOR3(0.4f, -0.2f, -0.4f);
		vecDir[2] = D3DXVECTOR3(0.0f, 0.4f, 0.4f);
		D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);			//正規化する(ベクトルの大きさを1にする)
		g_alight[nCntLight].Direction = vecDir[nCntLight];

		//ライトを設定する
		pDevice->SetLight(nCntLight, &g_alight[nCntLight]);

		//ライトを有効にする
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//=======================================================================
//終了処理
//=======================================================================
void UninitLight(void)
{
	
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateLight(void)
{
	
}