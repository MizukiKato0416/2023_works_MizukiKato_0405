//=======================================================================
//モデルに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "main.h"
#include "modeltxt.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "bullet.h"

//=======================================================================
//グローバル変数宣言
//=======================================================================
MODELTXT g_aModelTxt[MAX_MODELTXT];						//モデルの構造体
int g_nCntModelTxt;
int g_MaxNumModel;			//モデルの最大量

//=======================================================================
//初期化処理
//=======================================================================
void InitModelTxt(void)
{

	//初期化
	for (int nCntModelTxt = 0; nCntModelTxt < MAX_MODELTXT; nCntModelTxt++)
	{
		g_aModelTxt[nCntModelTxt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aModelTxt[nCntModelTxt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aModelTxt[nCntModelTxt].nIdxModelTxtParent = 0;
		g_aModelTxt[nCntModelTxt].bUse = false;
		g_aModelTxt[nCntModelTxt].vtxMin = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
		g_aModelTxt[nCntModelTxt].vtxMax = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);
		g_aModelTxt[nCntModelTxt].nNum = 0;
		g_aModelTxt[nCntModelTxt].nType = 0;
		for (int nCntVtx = 0; nCntVtx < 8; nCntVtx++)
		{
			g_aModelTxt[nCntModelTxt].Vtx.pos[nCntVtx] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aModelTxt[nCntModelTxt].Vtx.rot[nCntVtx] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		for (int nCntVec = 0; nCntVec < 4; nCntVec++)
		{
			g_aModelTxt[nCntModelTxt].Vtx.fVecX[nCntVec] = 0.0f;
			g_aModelTxt[nCntModelTxt].Vtx.fVecX2[nCntVec] = 0.0f;
			g_aModelTxt[nCntModelTxt].Vtx.fVecZ[nCntVec] = 0.0f;
			g_aModelTxt[nCntModelTxt].Vtx.fVecZ2[nCntVec] = 0.0f;
		}
	}
	g_MaxNumModel = 0;
	g_nCntModelTxt = 0;
	//textファイル読み込み
	FILE *pfile = fopen("data/STAGE/stage2.txt", "r");

	//モデルの種類を取得
	char string[5][128];
	char cFileName[15][128];
	int nCntFileName = 0;
	int nCntModelTxt = 0;
	char NUM_MODEL[] = "NUM_MODEL";
	char MODEL_FILENAME[] = "MODEL_FILENAME";
	char MODELSET[] = "MODELSET";

	while (fgets(string[0], 255, pfile) != NULL)
	{
		fscanf(pfile, "%s", string[0]);
		if (strncmp(NUM_MODEL, string[0], 8) == 0)
		{
			fscanf(pfile, "%s%d", string[1], &g_MaxNumModel);
			break;
		}
	}
	while (fgets(string[0], 255, pfile) != NULL)
	{
		fscanf(pfile, "%s", string[0]);
		if (strncmp(MODEL_FILENAME, string[0], 13) == 0)
		{
			fscanf(pfile, "%s%s", string[1], cFileName[nCntFileName]);
			nCntFileName++;
			if (nCntFileName >= g_MaxNumModel)
			{
				break;
			}
		}
	}
	while (fgets(string[0], 255, pfile) != NULL)
	{
		if (strncmp(MODELSET, string[0], 7) == 0)
		{
			fscanf(pfile, "%s%s%d", string[1], string[2], &g_aModelTxt[g_nCntModelTxt].nType);
			fscanf(pfile, "%s%s%f%f%f", string[1], string[2], &g_aModelTxt[g_nCntModelTxt].pos.x, &g_aModelTxt[g_nCntModelTxt].pos.y, &g_aModelTxt[g_nCntModelTxt].pos.z);
			fscanf(pfile, "%s%s%f%f%f", string[1], string[2], &g_aModelTxt[g_nCntModelTxt].rot.x, &g_aModelTxt[g_nCntModelTxt].rot.y, &g_aModelTxt[g_nCntModelTxt].rot.z);
			fscanf(pfile, "%s", string[3]);
			g_aModelTxt[g_nCntModelTxt].rot.x *= D3DX_PI * 2.0f / 360.0f * g_aModelTxt[g_nCntModelTxt].rot.x;
			g_aModelTxt[g_nCntModelTxt].rot.y *= D3DX_PI * 2.0f / 360.0f * g_aModelTxt[g_nCntModelTxt].rot.y;
			g_aModelTxt[g_nCntModelTxt].rot.z *= D3DX_PI * 2.0f / 360.0f * g_aModelTxt[g_nCntModelTxt].rot.z;
			g_aModelTxt[g_nCntModelTxt].bUse = true;
			g_nCntModelTxt++;
		}
	}

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//Xファイル読み込み
	for (int nCntModel = 0; nCntModel < g_nCntModelTxt; nCntModel++)
	{
		D3DXLoadMeshFromX(cFileName[g_aModelTxt[nCntModel].nType], D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aModelTxt[nCntModel].pBuffMat, NULL, &g_aModelTxt[nCntModel].nNumMat, &g_aModelTxt[nCntModel].pMesh);

		//テクスチャデータの取得
		D3DXMATERIAL *pMat;		//マテリアルへのポインタ

		//マテリアル情報に対するポインタを取得
		pMat = (D3DXMATERIAL *)g_aModelTxt[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aModelTxt[nCntModel].nNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_aModelTxt[nCntModel].pTexture[nCntMat]);
			}
		}
		//頂点情報の取得
		int nNumVtx;		//頂点数
		DWORD sizeFVF;		//頂点フォーマットのサイズ
		BYTE *pVtxBuff;		//頂点バッファへのポインタ

		//頂点数を取得
		nNumVtx = g_aModelTxt[nCntModel].pMesh->GetNumVertices();
		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_aModelTxt[nCntModel].pMesh->GetFVF());

		//頂点バッファをロック
		g_aModelTxt[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		//頂点座標の代入

															//全ての頂点を比較して最大値と最小手を抜き出す
															//最大値
			if (vtx.x >= g_aModelTxt[nCntModel].vtxMax.x)
			{
				g_aModelTxt[nCntModel].vtxMax.x = vtx.x;
			}
			if (vtx.y >= g_aModelTxt[nCntModel].vtxMax.y)
			{
				g_aModelTxt[nCntModel].vtxMax.y = vtx.y;
			}
			if (vtx.z >= g_aModelTxt[nCntModel].vtxMax.z)
			{
				g_aModelTxt[nCntModel].vtxMax.z = vtx.z;
			}
			//最小値
			if (vtx.x <= g_aModelTxt[nCntModel].vtxMin.x)
			{
				g_aModelTxt[nCntModel].vtxMin.x = vtx.x;
			}
			if (vtx.y <= g_aModelTxt[nCntModel].vtxMin.y)
			{
				g_aModelTxt[nCntModel].vtxMin.y = vtx.y;
			}
			if (vtx.z <= g_aModelTxt[nCntModel].vtxMin.z)
			{
				g_aModelTxt[nCntModel].vtxMin.z = vtx.z;
			}

			g_aModelTxt[nCntModel].fWidth = g_aModelTxt[nCntModel].vtxMax.x - g_aModelTxt[nCntModel].vtxMin.x;
			g_aModelTxt[nCntModel].fHeight = g_aModelTxt[nCntModel].vtxMax.y - g_aModelTxt[nCntModel].vtxMin.y;
			g_aModelTxt[nCntModel].fDepth = g_aModelTxt[nCntModel].vtxMax.z - g_aModelTxt[nCntModel].vtxMin.z;
			pVtxBuff += sizeFVF;		//頂点フォーマットのサイズ分ポインタを進める
		}

		g_aModelTxt[nCntModel].Vtx.pos[0].x = g_aModelTxt[nCntModel].vtxMin.x;
		g_aModelTxt[nCntModel].Vtx.pos[0].z = g_aModelTxt[nCntModel].vtxMax.z;
		g_aModelTxt[nCntModel].Vtx.pos[0].y = g_aModelTxt[nCntModel].vtxMax.y;
		g_aModelTxt[nCntModel].Vtx.pos[1].x = g_aModelTxt[nCntModel].vtxMax.x;
		g_aModelTxt[nCntModel].Vtx.pos[1].z = g_aModelTxt[nCntModel].vtxMax.z;
		g_aModelTxt[nCntModel].Vtx.pos[1].y = g_aModelTxt[nCntModel].vtxMax.y;
		g_aModelTxt[nCntModel].Vtx.pos[2].x = g_aModelTxt[nCntModel].vtxMin.x;
		g_aModelTxt[nCntModel].Vtx.pos[2].z = g_aModelTxt[nCntModel].vtxMax.z;
		g_aModelTxt[nCntModel].Vtx.pos[2].y = g_aModelTxt[nCntModel].vtxMin.y;
		g_aModelTxt[nCntModel].Vtx.pos[3].x = g_aModelTxt[nCntModel].vtxMax.x;
		g_aModelTxt[nCntModel].Vtx.pos[3].z = g_aModelTxt[nCntModel].vtxMax.z;
		g_aModelTxt[nCntModel].Vtx.pos[3].y = g_aModelTxt[nCntModel].vtxMin.y;
		g_aModelTxt[nCntModel].Vtx.pos[4].x = g_aModelTxt[nCntModel].vtxMin.x;
		g_aModelTxt[nCntModel].Vtx.pos[4].z = g_aModelTxt[nCntModel].vtxMin.z;
		g_aModelTxt[nCntModel].Vtx.pos[4].y = g_aModelTxt[nCntModel].vtxMax.y;
		g_aModelTxt[nCntModel].Vtx.pos[5].x = g_aModelTxt[nCntModel].vtxMax.x;
		g_aModelTxt[nCntModel].Vtx.pos[5].z = g_aModelTxt[nCntModel].vtxMin.z;
		g_aModelTxt[nCntModel].Vtx.pos[5].y = g_aModelTxt[nCntModel].vtxMax.y;
		g_aModelTxt[nCntModel].Vtx.pos[6].x = g_aModelTxt[nCntModel].vtxMin.x;
		g_aModelTxt[nCntModel].Vtx.pos[6].z = g_aModelTxt[nCntModel].vtxMin.z;
		g_aModelTxt[nCntModel].Vtx.pos[6].y = g_aModelTxt[nCntModel].vtxMin.y;
		g_aModelTxt[nCntModel].Vtx.pos[7].x = g_aModelTxt[nCntModel].vtxMax.x;
		g_aModelTxt[nCntModel].Vtx.pos[7].z = g_aModelTxt[nCntModel].vtxMin.z;
		g_aModelTxt[nCntModel].Vtx.pos[7].y = g_aModelTxt[nCntModel].vtxMin.y;
		//頂点バッファをアンロック
		g_aModelTxt[nCntModel].pMesh->UnlockVertexBuffer();
	}
}

//=======================================================================
//終了処理
//=======================================================================
void UninitModelTxt(void)
{
	for (int nCntModelTxt = 0; nCntModelTxt < g_nCntModelTxt; nCntModelTxt++)
	{
		//メッシュの破棄
		if (g_aModelTxt[nCntModelTxt].pMesh != NULL)
		{
			g_aModelTxt[nCntModelTxt].pMesh->Release();
			g_aModelTxt[nCntModelTxt].pMesh = NULL;
		}

		//マテリアルの破棄
		if (g_aModelTxt[nCntModelTxt].pBuffMat != NULL)
		{
			g_aModelTxt[nCntModelTxt].pBuffMat->Release();
			g_aModelTxt[nCntModelTxt].pBuffMat = NULL;
		}

		//テクスチャの破棄
		for (int nCntTex = 0; nCntTex < MODELTXT_MAX_TEXTURE; nCntTex++)
		{
			if (g_aModelTxt[nCntModelTxt].pTexture[nCntTex] != NULL)
			{
				g_aModelTxt[nCntModelTxt].pTexture[nCntTex]->Release();
				g_aModelTxt[nCntModelTxt].pTexture[nCntTex] = NULL;
			}
		}
	}
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateModelTxt(void)
{
	for (int nCntModelTxt = 0; nCntModelTxt < g_nCntModelTxt; nCntModelTxt++)
	{
		if (g_aModelTxt[nCntModelTxt].bUse == true)
		{

		}
	}
}

//=======================================================================
//描画処理
//=======================================================================
void DrawModelTxt(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する

	for (int nCntModelTxt = 0; nCntModelTxt < g_nCntModelTxt; nCntModelTxt++)
	{
		if (g_aModelTxt[nCntModelTxt].bUse == true)
		{
			D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
			D3DMATERIAL9 matDef;						//現在のマテリアル保存用
			D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

			D3DXMatrixIdentity(&g_aModelTxt[nCntModelTxt].mtxWorld);		//ワールドマトリックスの初期化

																	//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModelTxt[nCntModelTxt].rot.y, g_aModelTxt[nCntModelTxt].rot.x, g_aModelTxt[nCntModelTxt].rot.z);
			D3DXMatrixMultiply(&g_aModelTxt[nCntModelTxt].mtxWorld, &g_aModelTxt[nCntModelTxt].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aModelTxt[nCntModelTxt].pos.x, g_aModelTxt[nCntModelTxt].pos.y, g_aModelTxt[nCntModelTxt].pos.z);
			D3DXMatrixMultiply(&g_aModelTxt[nCntModelTxt].mtxWorld, &g_aModelTxt[nCntModelTxt].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aModelTxt[nCntModelTxt].mtxWorld);

			//現在のマテリアルを保存
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_aModelTxt[nCntModelTxt].pBuffMat->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)g_aModelTxt[nCntModelTxt].nNumMat; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_aModelTxt[nCntModelTxt].pTexture[nCntMat]);

				//モデル(パーツ)の描画
				g_aModelTxt[nCntModelTxt].pMesh->DrawSubset(nCntMat);
			}

			//保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);

			//8頂点の設定
			for (int nCntVtx = 0; nCntVtx < 8; nCntVtx++)
			{
				D3DXMatrixIdentity(&g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx]);		//ワールドマトリックスの初期化

				//向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModelTxt[nCntModelTxt].Vtx.rot[nCntVtx].y, g_aModelTxt[nCntModelTxt].Vtx.rot[nCntVtx].x, g_aModelTxt[nCntModelTxt].Vtx.rot[nCntVtx].z);
				D3DXMatrixMultiply(&g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx], &g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx], &mtxRot);

				//位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_aModelTxt[nCntModelTxt].Vtx.pos[nCntVtx].x, g_aModelTxt[nCntModelTxt].Vtx.pos[nCntVtx].y, g_aModelTxt[nCntModelTxt].Vtx.pos[nCntVtx].z);
				D3DXMatrixMultiply(&g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx], &g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx], &mtxTrans);

				D3DXMATRIX mtxParent;						//親のマトリックス
				mtxParent = g_aModelTxt[nCntModelTxt].mtxWorld;

				//算出した各パーツのワールドマトリックスと親のワールドマトリックスを掛け合わせる
				D3DXMatrixMultiply(&g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx], &g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx], &mtxParent);

				//ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx]);
			}
		}
	}
}

//=======================================================================
//モデルとの当たり判定
//=======================================================================
void CollisionModelTxt(D3DXVECTOR3 *pMove, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, float fWidth)
{
	MODELTXT *pModelTxt;
	pModelTxt = GetModelTxt();

	float fVecX[4];					//当たり判定の対象のベクトル保存変数
	float fVecZ[4];					//当たり判定の対象のベクトル保存変数
	float fVecX2[4];				//当たり判定の対象のベクトル保存変数
	float fVecZ2[4];				//当たり判定の対象のベクトル保存変数
	float fVecXOld[4];				//当たり判定の対象のベクトル保存変数
	float fVecZOld[4];				//当たり判定の対象のベクトル保存変数
	float fVecXOld2[4];				//当たり判定の対象のベクトル保存変数
	float fVecZOld2[4];				//当たり判定の対象のベクトル保存変数
	float fVecAsk[4];				//外積計算結果保存用変数
	float fVecAsk2[4];				//外積計算結果保存用変数
	float fVecAskOld[4];			//外積計算結果保存用変数
	float fVecAskOld2[4];			//外積計算結果保存用変数
	float fRadius[4];				//対象との距離計算結果保存用変数

	D3DXVECTOR3 nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//法線ベクトル
	D3DXVECTOR3 norR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//角丸の法線ベクトル
	D3DXVECTOR3 norRNomal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//角丸の法線ベクトルを正規化したベクトル
	D3DXVECTOR3 norAsk = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//法線ベクトルを求めるためのベクトル
	D3DXVECTOR3 norAsk2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//法線ベクトルを求めるためのベクトル
	D3DXVECTOR3 moveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//対象のムーブベクトル
	D3DXVECTOR3 posVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//対象の押し出し先を求めるベクトル
	D3DXVECTOR3 norVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//法線を対象の前の位置まで伸ばしたベクトル
	D3DXVECTOR3 norVecR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//角丸法線を対象の前の位置まで伸ばしたベクトル
	D3DXVECTOR3 posnorVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//法線の方向に対象を押し戻す位置を求めるベクトル
	D3DXVECTOR3 posnorVecR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//法線の方向に対象を押し戻す位置を求めるベクトル
	float VecNor = 0.0f;									//対象のムーブベクトルと法線の内積
	float VecNorR = 0.0f;									//対象のムーブベクトルと角丸法線の内積

	//初期化
	for (int nCntVec = 0; nCntVec < 4; nCntVec++)
	{
		fVecX[nCntVec] = 0.0f;
		fVecZ[nCntVec] = 0.0f;
		fVecX2[nCntVec] = 0.0f;
		fVecZ2[nCntVec] = 0.0f;
		fVecXOld[nCntVec] = 0.0f;
		fVecZOld[nCntVec] = 0.0f;
		fVecXOld2[nCntVec] = 0.0f;
		fVecZOld2[nCntVec] = 0.0f;
		fRadius[nCntVec] = 0.0f;
		fVecAsk[nCntVec] = 0.0f;
		fVecAsk2[nCntVec] = 0.0f;
		fVecAskOld[nCntVec] = 0.0f;
		fVecAskOld2[nCntVec] = 0.0f;
	}

	for (int nCntModelTxt = 0; nCntModelTxt < g_nCntModelTxt; nCntModelTxt++, pModelTxt++)
	{
		if (pModelTxt->bUse == true)
		{
			//角丸の当たり判定
			fRadius[0] = sqrt((pModelTxt->Vtx.mtxWorld[2]._41 - pPos->x) * (pModelTxt->Vtx.mtxWorld[2]._41 - pPos->x) +
				(pModelTxt->Vtx.mtxWorld[2]._43 - pPos->z) * (pModelTxt->Vtx.mtxWorld[2]._43 - pPos->z));
			fRadius[1] = sqrt((pModelTxt->Vtx.mtxWorld[3]._41 - pPos->x) * (pModelTxt->Vtx.mtxWorld[3]._41 - pPos->x) +
				(pModelTxt->Vtx.mtxWorld[3]._43 - pPos->z) * (pModelTxt->Vtx.mtxWorld[3]._43 - pPos->z));
			fRadius[2] = sqrt((pModelTxt->Vtx.mtxWorld[7]._41 - pPos->x) * (pModelTxt->Vtx.mtxWorld[7]._41 - pPos->x) +
				(pModelTxt->Vtx.mtxWorld[7]._43 - pPos->z) * (pModelTxt->Vtx.mtxWorld[7]._43 - pPos->z));
			fRadius[3] = sqrt((pModelTxt->Vtx.mtxWorld[6]._41 - pPos->x) * (pModelTxt->Vtx.mtxWorld[6]._41 - pPos->x) +
				(pModelTxt->Vtx.mtxWorld[6]._43 - pPos->z) * (pModelTxt->Vtx.mtxWorld[6]._43 - pPos->z));

			//角丸の法線を求める
			if (fRadius[0] <= fWidth / 2.0f)
			{
				norR = D3DXVECTOR3(pPosOld->x - pModelTxt->Vtx.mtxWorld[2]._41,
									pPosOld->y - pModelTxt->Vtx.mtxWorld[2]._42,
									pPosOld->z - pModelTxt->Vtx.mtxWorld[2]._43);
			}
			else if (fRadius[1] <= fWidth / 2.0f)
			{
				norR = D3DXVECTOR3(pPosOld->x - pModelTxt->Vtx.mtxWorld[3]._41,
									pPosOld->y - pModelTxt->Vtx.mtxWorld[3]._42,
									pPosOld->z - pModelTxt->Vtx.mtxWorld[3]._43);
			}
			else if (fRadius[2] <= fWidth / 2.0f)
			{
				norR = D3DXVECTOR3(pPosOld->x - pModelTxt->Vtx.mtxWorld[7]._41,
									pPosOld->y - pModelTxt->Vtx.mtxWorld[7]._42,
									pPosOld->z - pModelTxt->Vtx.mtxWorld[7]._43);
			}
			else if (fRadius[3] <= fWidth / 2.0f)
			{
				norR = D3DXVECTOR3(pPosOld->x - pModelTxt->Vtx.mtxWorld[6]._41,
									pPosOld->y - pModelTxt->Vtx.mtxWorld[6]._42,
									pPosOld->z - pModelTxt->Vtx.mtxWorld[6]._43);
			}
			D3DXVec3Normalize(&norRNomal, &norR);			//正規化する(ベクトルの大きさを1にする)

			//対象の幅の分大きくする
			g_aModelTxt[nCntModelTxt].Vtx.pos[0].x -= fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[1].x += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[2].x -= fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[3].x += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[4].x -= fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[5].x += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[6].x -= fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[7].x += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[0].z += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[1].z += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[2].z += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[3].z += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[4].z -= fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[5].z -= fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[6].z -= fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[7].z -= fWidth / 2.0f;

			//マトリックスに反映させる
			LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
			pDevice = GetDevice();						//デバイスを取得する
			D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
														//8頂点の設定
			for (int nCntVtx = 0; nCntVtx < 8; nCntVtx++)
			{
				D3DXMatrixIdentity(&g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx]);		//ワールドマトリックスの初期化

																							//向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModelTxt[nCntModelTxt].Vtx.rot[nCntVtx].y, g_aModelTxt[nCntModelTxt].Vtx.rot[nCntVtx].x, g_aModelTxt[nCntModelTxt].Vtx.rot[nCntVtx].z);
				D3DXMatrixMultiply(&g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx], &g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx], &mtxRot);

				//位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_aModelTxt[nCntModelTxt].Vtx.pos[nCntVtx].x, g_aModelTxt[nCntModelTxt].Vtx.pos[nCntVtx].y, g_aModelTxt[nCntModelTxt].Vtx.pos[nCntVtx].z);
				D3DXMatrixMultiply(&g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx], &g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx], &mtxTrans);

				D3DXMATRIX mtxParent;						//親のマトリックス
				mtxParent = g_aModelTxt[nCntModelTxt].mtxWorld;

				//算出した各パーツのワールドマトリックスと親のワールドマトリックスを掛け合わせる
				D3DXMatrixMultiply(&g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx], &g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx], &mtxParent);

				//ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx]);
			}

			//ベクトルを出す
			pModelTxt->Vtx.fVecX[0] = pModelTxt->Vtx.mtxWorld[3]._41 - pModelTxt->Vtx.mtxWorld[2]._41;
			pModelTxt->Vtx.fVecZ[0] = pModelTxt->Vtx.mtxWorld[3]._43 - pModelTxt->Vtx.mtxWorld[2]._43;
			pModelTxt->Vtx.fVecX[1] = pModelTxt->Vtx.mtxWorld[7]._41 - pModelTxt->Vtx.mtxWorld[3]._41;
			pModelTxt->Vtx.fVecZ[1] = pModelTxt->Vtx.mtxWorld[7]._43 - pModelTxt->Vtx.mtxWorld[3]._43;
			pModelTxt->Vtx.fVecX[2] = pModelTxt->Vtx.mtxWorld[6]._41 - pModelTxt->Vtx.mtxWorld[7]._41;
			pModelTxt->Vtx.fVecZ[2] = pModelTxt->Vtx.mtxWorld[6]._43 - pModelTxt->Vtx.mtxWorld[7]._43;
			pModelTxt->Vtx.fVecX[3] = pModelTxt->Vtx.mtxWorld[2]._41 - pModelTxt->Vtx.mtxWorld[6]._41;
			pModelTxt->Vtx.fVecZ[3] = pModelTxt->Vtx.mtxWorld[2]._43 - pModelTxt->Vtx.mtxWorld[6]._43;

			//対象のベクトルを出す
			fVecX[0] = pPos->x - pModelTxt->Vtx.mtxWorld[2]._41;
			fVecZ[0] = pPos->z - pModelTxt->Vtx.mtxWorld[2]._43;
			fVecX[1] = pPos->x - pModelTxt->Vtx.mtxWorld[3]._41;
			fVecZ[1] = pPos->z - pModelTxt->Vtx.mtxWorld[3]._43;
			fVecX[2] = pPos->x - pModelTxt->Vtx.mtxWorld[7]._41;
			fVecZ[2] = pPos->z - pModelTxt->Vtx.mtxWorld[7]._43;
			fVecX[3] = pPos->x - pModelTxt->Vtx.mtxWorld[6]._41;
			fVecZ[3] = pPos->z - pModelTxt->Vtx.mtxWorld[6]._43;

			//対象の1フレーム前のベクトルを出す
			fVecXOld[0] = pPosOld->x - pModelTxt->Vtx.mtxWorld[2]._41;
			fVecZOld[0] = pPosOld->z - pModelTxt->Vtx.mtxWorld[2]._43;
			fVecXOld[1] = pPosOld->x - pModelTxt->Vtx.mtxWorld[3]._41;
			fVecZOld[1] = pPosOld->z - pModelTxt->Vtx.mtxWorld[3]._43;
			fVecXOld[2] = pPosOld->x - pModelTxt->Vtx.mtxWorld[7]._41;
			fVecZOld[2] = pPosOld->z - pModelTxt->Vtx.mtxWorld[7]._43;
			fVecXOld[3] = pPosOld->x - pModelTxt->Vtx.mtxWorld[6]._41;
			fVecZOld[3] = pPosOld->z - pModelTxt->Vtx.mtxWorld[6]._43;

			//外積の計算
			fVecAsk[0] = (pModelTxt->Vtx.fVecX[0] * fVecZ[0]) - (fVecX[0] * pModelTxt->Vtx.fVecZ[0]);
			fVecAsk[1] = (pModelTxt->Vtx.fVecX[1] * fVecZ[1]) - (fVecX[1] * pModelTxt->Vtx.fVecZ[1]);
			fVecAsk[2] = (pModelTxt->Vtx.fVecX[2] * fVecZ[2]) - (fVecX[2] * pModelTxt->Vtx.fVecZ[2]);
			fVecAsk[3] = (pModelTxt->Vtx.fVecX[3] * fVecZ[3]) - (fVecX[3] * pModelTxt->Vtx.fVecZ[3]);

			//1フレーム前の外積の計算
			fVecAskOld[0] = (pModelTxt->Vtx.fVecX[0] * fVecZOld[0]) - (fVecXOld[0] * pModelTxt->Vtx.fVecZ[0]);
			fVecAskOld[1] = (pModelTxt->Vtx.fVecX[1] * fVecZOld[1]) - (fVecXOld[1] * pModelTxt->Vtx.fVecZ[1]);
			fVecAskOld[2] = (pModelTxt->Vtx.fVecX[2] * fVecZOld[2]) - (fVecXOld[2] * pModelTxt->Vtx.fVecZ[2]);
			fVecAskOld[3] = (pModelTxt->Vtx.fVecX[3] * fVecZOld[3]) - (fVecXOld[3] * pModelTxt->Vtx.fVecZ[3]);

			//どの壁にぶつかっているか
			if (fVecAskOld[1] >= 0.0f && fVecAsk[1] < 0.0f)
			{
				norAsk = D3DXVECTOR3(pModelTxt->Vtx.mtxWorld[5]._41 - pModelTxt->Vtx.mtxWorld[7]._41,
					pModelTxt->Vtx.mtxWorld[5]._42 - pModelTxt->Vtx.mtxWorld[7]._42,
					pModelTxt->Vtx.mtxWorld[5]._43 - pModelTxt->Vtx.mtxWorld[7]._43);
				norAsk2 = D3DXVECTOR3(pModelTxt->Vtx.mtxWorld[3]._41 - pModelTxt->Vtx.mtxWorld[7]._41,
					pModelTxt->Vtx.mtxWorld[3]._42 - pModelTxt->Vtx.mtxWorld[7]._42,
					pModelTxt->Vtx.mtxWorld[3]._43 - pModelTxt->Vtx.mtxWorld[7]._43);
			}
			else if (fVecAskOld[3] >= 0.0f && fVecAsk[3] < 0.0f)
			{
				norAsk = D3DXVECTOR3(pModelTxt->Vtx.mtxWorld[0]._41 - pModelTxt->Vtx.mtxWorld[2]._41,
					pModelTxt->Vtx.mtxWorld[0]._42 - pModelTxt->Vtx.mtxWorld[2]._42,
					pModelTxt->Vtx.mtxWorld[0]._43 - pModelTxt->Vtx.mtxWorld[2]._43);
				norAsk2 = D3DXVECTOR3(pModelTxt->Vtx.mtxWorld[6]._41 - pModelTxt->Vtx.mtxWorld[2]._41,
					pModelTxt->Vtx.mtxWorld[6]._42 - pModelTxt->Vtx.mtxWorld[2]._42,
					pModelTxt->Vtx.mtxWorld[6]._43 - pModelTxt->Vtx.mtxWorld[2]._43);
			}
			else if (fVecAskOld[2] >= 0.0f && fVecAsk[2] < 0.0f)
			{
				norAsk = D3DXVECTOR3(pModelTxt->Vtx.mtxWorld[4]._41 - pModelTxt->Vtx.mtxWorld[6]._41,
					pModelTxt->Vtx.mtxWorld[4]._42 - pModelTxt->Vtx.mtxWorld[6]._42,
					pModelTxt->Vtx.mtxWorld[4]._43 - pModelTxt->Vtx.mtxWorld[6]._43);
				norAsk2 = D3DXVECTOR3(pModelTxt->Vtx.mtxWorld[7]._41 - pModelTxt->Vtx.mtxWorld[6]._41,
					pModelTxt->Vtx.mtxWorld[7]._42 - pModelTxt->Vtx.mtxWorld[6]._42,
					pModelTxt->Vtx.mtxWorld[7]._43 - pModelTxt->Vtx.mtxWorld[6]._43);
			}
			else if (fVecAskOld[0] >= 0.0f && fVecAsk[0] < 0.0f)
			{
				norAsk = D3DXVECTOR3(pModelTxt->Vtx.mtxWorld[1]._41 - pModelTxt->Vtx.mtxWorld[3]._41,
					pModelTxt->Vtx.mtxWorld[1]._42 - pModelTxt->Vtx.mtxWorld[3]._42,
					pModelTxt->Vtx.mtxWorld[1]._43 - pModelTxt->Vtx.mtxWorld[3]._43);
				norAsk2 = D3DXVECTOR3(pModelTxt->Vtx.mtxWorld[2]._41 - pModelTxt->Vtx.mtxWorld[3]._41,
					pModelTxt->Vtx.mtxWorld[2]._42 - pModelTxt->Vtx.mtxWorld[3]._42,
					pModelTxt->Vtx.mtxWorld[2]._43 - pModelTxt->Vtx.mtxWorld[3]._43);
			}
			
			
			

			//元の大きさに戻す
			g_aModelTxt[nCntModelTxt].Vtx.pos[0].z -= fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[1].z -= fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[2].z -= fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[3].z -= fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[4].z += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[5].z += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[6].z += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[7].z += fWidth / 2.0f;

			//元の大きさに戻す
			g_aModelTxt[nCntModelTxt].Vtx.pos[0].x += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[1].x -= fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[2].x += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[3].x -= fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[4].x += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[5].x -= fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[6].x += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[7].x -= fWidth / 2.0f;

			
			//法線ベクトルを求める
			D3DXVec3Cross(&nor, &norAsk, &norAsk2);
			D3DXVec3Normalize(&nor, &nor);			//正規化する(ベクトルの大きさを1にする)

			//ムーブベクトルを求める
			moveVec = D3DXVECTOR3(pPos->x - pPosOld->x, pPos->y - pPosOld->y, pPos->z - pPosOld->z);

			//ムーブベクトルと法線の内積を求める
			VecNor = (-moveVec.x * nor.x) + (-moveVec.y * nor.y) + (-moveVec.z * nor.z);
			//VecNorR = (-moveVec.x * norR.x) + (-moveVec.y * norR.y) + (-moveVec.z * norR.z);

			//法線の方向に内積分伸ばしたベクトルを求める
			norVec = D3DXVECTOR3(nor.x * VecNor, nor.y * VecNor, nor.z * VecNor);
			//norVecR = D3DXVECTOR3(norR.x * VecNorR, norR.y * VecNorR, norR.z * VecNorR);

			//対象を押し戻す位置のベクトルを求める
			posnorVec = D3DXVECTOR3(nor.x * fWidth / 2.0f, nor.y * fWidth / 2.0f, nor.z * fWidth / 2.0f);


			posnorVecR = D3DXVECTOR3(norRNomal.x * fWidth / 2.0f, norRNomal.y * fWidth / 2.0f, norRNomal.z * fWidth / 2.0f);

			//当たり判定
			if (((fVecAsk[0] < 0.0f && fVecAsk[1] < 0.0f && fVecAsk[2] < 0.0f && fVecAsk[3] < 0.0f) &&
				(fVecAskOld[0] >= 0.0f || fVecAskOld[1] >= 0.0f || fVecAskOld[2] >= 0.0f || fVecAskOld[3] >= 0.0f)))
			{
				//対象の押出先を求める
				posVec.x = (moveVec.x + norVec.x);
				posVec.y = (moveVec.y + norVec.y);
				posVec.z = (moveVec.z + norVec.z);

				//当たってる
				pPos->x = pPosOld->x;
				pPos->z = pPosOld->z;
				pPos->x += posVec.x;
				pPos->z += posVec.z;
			}
		}
	}
}

//=======================================================================
//モデルとの当たり判定falseにする系
//=======================================================================
bool CollisionModelTxtBool(D3DXVECTOR3 *pPos)
{
	bool bColl = false;

	MODELTXT *pModelTxt;
	pModelTxt = GetModelTxt();

	float fVecX[4];					//当たり判定の対象のベクトル保存変数
	float fVecZ[4];					//当たり判定の対象のベクトル保存変数
	float fVecAsk[4];				//外積計算結果保存用変数

									//初期化
	for (int nCntVec = 0; nCntVec < 4; nCntVec++)
	{
		fVecX[nCntVec] = 0.0f;
		fVecZ[nCntVec] = 0.0f;
		fVecAsk[nCntVec] = 0.0f;
	}

	for (int nCntModelTxt = 0; nCntModelTxt < g_nCntModelTxt; nCntModelTxt++, pModelTxt++)
	{
		if (pModelTxt->bUse == true)
		{
			//ベクトルを出す
			pModelTxt->Vtx.fVecX[0] = pModelTxt->Vtx.mtxWorld[3]._41 - pModelTxt->Vtx.mtxWorld[2]._41;
			pModelTxt->Vtx.fVecZ[0] = pModelTxt->Vtx.mtxWorld[3]._43 - pModelTxt->Vtx.mtxWorld[2]._43;
			pModelTxt->Vtx.fVecX[1] = pModelTxt->Vtx.mtxWorld[7]._41 - pModelTxt->Vtx.mtxWorld[3]._41;
			pModelTxt->Vtx.fVecZ[1] = pModelTxt->Vtx.mtxWorld[7]._43 - pModelTxt->Vtx.mtxWorld[3]._43;
			pModelTxt->Vtx.fVecX[2] = pModelTxt->Vtx.mtxWorld[6]._41 - pModelTxt->Vtx.mtxWorld[7]._41;
			pModelTxt->Vtx.fVecZ[2] = pModelTxt->Vtx.mtxWorld[6]._43 - pModelTxt->Vtx.mtxWorld[7]._43;
			pModelTxt->Vtx.fVecX[3] = pModelTxt->Vtx.mtxWorld[2]._41 - pModelTxt->Vtx.mtxWorld[6]._41;
			pModelTxt->Vtx.fVecZ[3] = pModelTxt->Vtx.mtxWorld[2]._43 - pModelTxt->Vtx.mtxWorld[6]._43;

			//対象のベクトルを出す
			fVecX[0] = pPos->x - pModelTxt->Vtx.mtxWorld[2]._41;
			fVecZ[0] = pPos->z - pModelTxt->Vtx.mtxWorld[2]._43;
			fVecX[1] = pPos->x - pModelTxt->Vtx.mtxWorld[3]._41;
			fVecZ[1] = pPos->z - pModelTxt->Vtx.mtxWorld[3]._43;
			fVecX[2] = pPos->x - pModelTxt->Vtx.mtxWorld[7]._41;
			fVecZ[2] = pPos->z - pModelTxt->Vtx.mtxWorld[7]._43;
			fVecX[3] = pPos->x - pModelTxt->Vtx.mtxWorld[6]._41;
			fVecZ[3] = pPos->z - pModelTxt->Vtx.mtxWorld[6]._43;

			//外積の計算
			fVecAsk[0] = (pModelTxt->Vtx.fVecX[0] * fVecZ[0]) - (fVecX[0] * pModelTxt->Vtx.fVecZ[0]);
			fVecAsk[1] = (pModelTxt->Vtx.fVecX[1] * fVecZ[1]) - (fVecX[1] * pModelTxt->Vtx.fVecZ[1]);
			fVecAsk[2] = (pModelTxt->Vtx.fVecX[2] * fVecZ[2]) - (fVecX[2] * pModelTxt->Vtx.fVecZ[2]);
			fVecAsk[3] = (pModelTxt->Vtx.fVecX[3] * fVecZ[3]) - (fVecX[3] * pModelTxt->Vtx.fVecZ[3]);

			//当たり判定
			if (fVecAsk[0] < 0.0f && fVecAsk[1] < 0.0f && fVecAsk[2] < 0.0f && fVecAsk[3] < 0.0f)
			{
				//当たってる
				bColl = true;
			}
		}
	}
	return bColl;
}


//=======================================================================
//モデルとの当たり判定
//=======================================================================
bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pBeforePos, D3DXVECTOR3 *pMove, float fWidth, float fHeight, float fDepth)
{

	bool bLand = false;				//着地しているかどうか
	MODELTXT *pModelTxt;
	pModelTxt = GetModelTxt();

	for (int nCntModelTxt = 0; nCntModelTxt < g_nCntModelTxt; nCntModelTxt++, pModelTxt++)
	{
		if (pModelTxt->bUse == true)
		{
			if (pPos->x > pModelTxt->pos.x - pModelTxt->fWidth / 2.0f - fWidth / 2.0f &&
				pPos->x < pModelTxt->pos.x + pModelTxt->fWidth / 2.0f + fWidth / 2.0f &&
				pPos->z > pModelTxt->pos.z - pModelTxt->fDepth / 2.0f - fDepth / 2.0f &&
				pPos->z < pModelTxt->pos.z + pModelTxt->fDepth / 2.0f + fDepth / 2.0f &&
				pPos->y <= pModelTxt->pos.y + pModelTxt->fHeight &&
				pBeforePos->y >= pModelTxt->pos.y + pModelTxt->fHeight)
			{
				pPos->y = pModelTxt->pos.y + pModelTxt->fHeight;
				pMove->y = 0.0f;
				bLand = true;
			}
			else if (pPos->x > pModelTxt->pos.x - pModelTxt->fWidth / 2.0f - fWidth / 2.0f &&
				pPos->x < pModelTxt->pos.x + pModelTxt->fWidth / 2.0f + fWidth / 2.0f &&
				pPos->z > pModelTxt->pos.z - pModelTxt->fDepth / 2.0f - fDepth / 2.0f &&
				pPos->z < pModelTxt->pos.z + pModelTxt->fDepth / 2.0f + fDepth / 2.0f &&
				pPos->y >= pModelTxt->pos.y - fHeight &&
				pBeforePos->y <= pModelTxt->pos.y - fHeight)
			{
				pPos->y = pModelTxt->pos.y - fHeight;
			}

			if (pPos->y < pModelTxt->pos.y + pModelTxt->fHeight &&
				pPos->y > pModelTxt->pos.y - fHeight &&
				pPos->z > pModelTxt->pos.z - pModelTxt->fDepth / 2.0f - fDepth / 2.0f &&
				pPos->z < pModelTxt->pos.z + pModelTxt->fDepth / 2.0f + fDepth / 2.0f &&
				pPos->x >= pModelTxt->pos.x - pModelTxt->fWidth / 2.0f - fWidth / 2.0f &&
				pBeforePos->x <= pModelTxt->pos.x - pModelTxt->fWidth / 2.0f - fWidth / 2.0f)
			{
				pPos->x = pModelTxt->pos.x - pModelTxt->fWidth / 2.0f - fWidth / 2.0f;
			}
			else if (pPos->y < pModelTxt->pos.y + pModelTxt->fHeight &&
				pPos->y > pModelTxt->pos.y - fHeight &&
				pPos->z > pModelTxt->pos.z - pModelTxt->fDepth / 2.0f - fDepth / 2.0f &&
				pPos->z < pModelTxt->pos.z + pModelTxt->fDepth / 2.0f + fDepth / 2.0f &&
				pPos->x <= pModelTxt->pos.x + pModelTxt->fWidth / 2.0f + fWidth / 2.0f &&
				pBeforePos->x >= pModelTxt->pos.x + pModelTxt->fWidth / 2.0f + fWidth / 2.0f)
			{
				pPos->x = pModelTxt->pos.x + pModelTxt->fWidth / 2.0f + fWidth / 2.0f;
			}

			if (pPos->y < pModelTxt->pos.y + pModelTxt->fHeight &&
				pPos->y > pModelTxt->pos.y - fHeight &&
				pPos->x > pModelTxt->pos.x - pModelTxt->fWidth / 2.0f - fWidth / 2.0f &&
				pPos->x < pModelTxt->pos.x + pModelTxt->fWidth / 2.0f + fWidth / 2.0f &&
				pPos->z >= pModelTxt->pos.z - pModelTxt->fDepth / 2.0f - fDepth / 2.0f &&
				pBeforePos->z <= pModelTxt->pos.z - pModelTxt->fDepth / 2.0f - fDepth / 2.0f)
			{
				pPos->z = pModelTxt->pos.z - pModelTxt->fDepth / 2.0f - fDepth / 2.0f;
			}
			else if (pPos->y < pModelTxt->pos.y + pModelTxt->fHeight &&
				pPos->y > pModelTxt->pos.y - fHeight &&
				pPos->x > pModelTxt->pos.x - pModelTxt->fWidth / 2.0f - fWidth / 2.0f &&
				pPos->x < pModelTxt->pos.x + pModelTxt->fWidth / 2.0f + fWidth / 2.0f &&
				pPos->z <= pModelTxt->pos.z + pModelTxt->fDepth / 2.0f + fDepth / 2.0f &&
				pBeforePos->z >= pModelTxt->pos.z + pModelTxt->fDepth / 2.0f + fDepth / 2.0f)
			{
				pPos->z = pModelTxt->pos.z + pModelTxt->fDepth / 2.0f + fDepth / 2.0f;
			}

		}
	}
	return bLand;
}


//=======================================================================
//取得処理
//=======================================================================
MODELTXT *GetModelTxt(void)
{
	return &g_aModelTxt[0];
}