//=======================================================================
//モデルに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#include "main.h"
#include "model.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "bullet.h"

//=======================================================================
//グローバル変数宣言
//=======================================================================
MODEL g_aModel[MAX_MODEL];						//モデルの構造体
int g_nCntModel;

//=======================================================================
//初期化処理
//=======================================================================
void InitModel(void)
{

	//初期化
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		g_aModel[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aModel[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aModel[nCntModel].nIdxModelParent = 0;
		g_aModel[nCntModel].bUse = false;
		g_aModel[nCntModel].vtxMin = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
		g_aModel[nCntModel].vtxMax = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);
		g_aModel[nCntModel].nNum = 0;
	}

	
	

	//影の設定
}

//=======================================================================
//終了処理
//=======================================================================
void UninitModel(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		//メッシュの破棄
		if (g_aModel[nCntModel].pMesh != NULL)
		{
			g_aModel[nCntModel].pMesh->Release();
			g_aModel[nCntModel].pMesh = NULL;
		}

		//マテリアルの破棄
		if (g_aModel[nCntModel].pBuffMat != NULL)
		{
			g_aModel[nCntModel].pBuffMat->Release();
			g_aModel[nCntModel].pBuffMat = NULL;
		}

		//テクスチャの破棄
		for (int nCntTex = 0; nCntTex < MODEL_MAX_TEXTURE; nCntTex++)
		{
			if (g_aModel[nCntModel].pTexture[nCntTex] != NULL)
			{
				g_aModel[nCntModel].pTexture[nCntTex]->Release();
				g_aModel[nCntModel].pTexture[nCntTex] = NULL;
			}
		}
	}
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateModel(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == true)
		{

		}
	}
}

//=======================================================================
//描画処理
//=======================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == true)
		{
			D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
			D3DMATERIAL9 matDef;						//現在のマテリアル保存用
			D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

			D3DXMatrixIdentity(&g_aModel[nCntModel].mtxWorld);		//ワールドマトリックスの初期化

																	//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModel[nCntModel].rot.y, g_aModel[nCntModel].rot.x, g_aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld, &g_aModel[nCntModel].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aModel[nCntModel].pos.x, g_aModel[nCntModel].pos.y, g_aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld, &g_aModel[nCntModel].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aModel[nCntModel].mtxWorld);

			//現在のマテリアルを保存
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_aModel[nCntModel].pBuffMat->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)g_aModel[nCntModel].nNumMat; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_aModel[nCntModel].pTexture[nCntMat]);

				//モデル(パーツ)の描画
				g_aModel[nCntModel].pMesh->DrawSubset(nCntMat);
			}

			//保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=======================================================================
//設定処理
//=======================================================================
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODELTYPE Type)
{
	if (g_aModel[g_nCntModel].bUse == false)
	{
		g_aModel[g_nCntModel].rot = rot;
		g_aModel[g_nCntModel].pos = pos;

		g_aModel[g_nCntModel].Type = Type;

		g_aModel[g_nCntModel].bUse = true;

		//デバイスの取得
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = GetDevice();

		//Xファイル読み込み
		if (g_aModel[g_nCntModel].Type == BUILDING_HIGH)
		{
			D3DXLoadMeshFromX("data/MODEL/building002.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
				&g_aModel[g_nCntModel].pBuffMat, NULL, &g_aModel[g_nCntModel].nNumMat, &g_aModel[g_nCntModel].pMesh);
		}
		else if (g_aModel[g_nCntModel].Type == BUILDING_HIGH_02)
		{
			D3DXLoadMeshFromX("data/MODEL/building003.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
				&g_aModel[g_nCntModel].pBuffMat, NULL, &g_aModel[g_nCntModel].nNumMat, &g_aModel[g_nCntModel].pMesh);
		}
		else if (g_aModel[g_nCntModel].Type == BUILDING_LOW)
		{
			D3DXLoadMeshFromX("data/MODEL/building001.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
				&g_aModel[g_nCntModel].pBuffMat, NULL, &g_aModel[g_nCntModel].nNumMat, &g_aModel[g_nCntModel].pMesh);
		}
		else if (g_aModel[g_nCntModel].Type == BUILDING_LOW_02)
		{
			D3DXLoadMeshFromX("data/MODEL/building004.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
				&g_aModel[g_nCntModel].pBuffMat, NULL, &g_aModel[g_nCntModel].nNumMat, &g_aModel[g_nCntModel].pMesh);
		}
		else if (g_aModel[g_nCntModel].Type == CAR)
		{
			D3DXLoadMeshFromX("data/MODEL/car000.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
				&g_aModel[g_nCntModel].pBuffMat, NULL, &g_aModel[g_nCntModel].nNumMat, &g_aModel[g_nCntModel].pMesh);
		}

		//テクスチャデータの取得
		D3DXMATERIAL *pMat;		//マテリアルへのポインタ

								//マテリアル情報に対するポインタを取得
		pMat = (D3DXMATERIAL *)g_aModel[g_nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aModel[g_nCntModel].nNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_aModel[g_nCntModel].pTexture[nCntMat]);
			}
		}
		//頂点情報の取得
		int nNumVtx;		//頂点数
		DWORD sizeFVF;		//頂点フォーマットのサイズ
		BYTE *pVtxBuff;		//頂点バッファへのポインタ

							//頂点数を取得
		nNumVtx = g_aModel[g_nCntModel].pMesh->GetNumVertices();
		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_aModel[g_nCntModel].pMesh->GetFVF());

		//頂点バッファをロック
		g_aModel[g_nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		//頂点座標の代入

			//全ての頂点を比較して最大値と最小手を抜き出す
			//最大値
			if (vtx.x >= g_aModel[g_nCntModel].vtxMax.x)
			{
				g_aModel[g_nCntModel].vtxMax.x = vtx.x;
			}
			if (vtx.y >= g_aModel[g_nCntModel].vtxMax.y)
			{
				g_aModel[g_nCntModel].vtxMax.y = vtx.y;
			}
			if (vtx.z >= g_aModel[g_nCntModel].vtxMax.z)
			{
				g_aModel[g_nCntModel].vtxMax.z = vtx.z;
			}
			//最小値
			if (vtx.x <= g_aModel[g_nCntModel].vtxMin.x)
			{
				g_aModel[g_nCntModel].vtxMin.x = vtx.x;
			}
			if (vtx.y <= g_aModel[g_nCntModel].vtxMin.y)
			{
				g_aModel[g_nCntModel].vtxMin.y = vtx.y;
			}
			if (vtx.z <= g_aModel[g_nCntModel].vtxMin.z)
			{
				g_aModel[g_nCntModel].vtxMin.z = vtx.z;
			}

			g_aModel[g_nCntModel].fWidth = g_aModel[g_nCntModel].vtxMax.x - g_aModel[g_nCntModel].vtxMin.x;
			g_aModel[g_nCntModel].fHeight = g_aModel[g_nCntModel].vtxMax.y - g_aModel[g_nCntModel].vtxMin.y;
			g_aModel[g_nCntModel].fDepth = g_aModel[g_nCntModel].vtxMax.z - g_aModel[g_nCntModel].vtxMin.z;


			pVtxBuff += sizeFVF;		//頂点フォーマットのサイズ分ポインタを進める
		}
		//頂点バッファをアンロック
		g_aModel[g_nCntModel].pMesh->UnlockVertexBuffer();
	}
	g_nCntModel++;
	if (g_nCntModel >= MAX_MODEL)
	{
		g_nCntModel = 0;
	}
}

//=======================================================================
//モデルとの当たり判定
//=======================================================================
bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pBeforePos, D3DXVECTOR3 *pMove, float fWidth, float fHeight, float fDepth)
{
	
	bool bLand = false;			//着地しているかどうか
	MODEL *pModel;
	pModel = GetModel();

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++, pModel++)
	{
		if (pModel->bUse == true)
		{
			if (pPos->x > pModel->pos.x - pModel->fWidth / 2.0f - fWidth / 2.0f &&
				pPos->x < pModel->pos.x + pModel->fWidth / 2.0f + fWidth / 2.0f &&
				pPos->z > pModel->pos.z - pModel->fDepth / 2.0f - fDepth / 2.0f &&
				pPos->z < pModel->pos.z + pModel->fDepth / 2.0f + fDepth / 2.0f &&
				pPos->y <= pModel->pos.y + pModel->fHeight &&
				pBeforePos->y >= pModel->pos.y + pModel->fHeight)
			{
				pPos->y = pModel->pos.y + pModel->fHeight;
				pMove->y = 0.0f;
				bLand = true;
			}
			else if (pPos->x > pModel->pos.x - pModel->fWidth / 2.0f - fWidth / 2.0f &&
					pPos->x < pModel->pos.x + pModel->fWidth / 2.0f + fWidth / 2.0f &&
					pPos->z > pModel->pos.z - pModel->fDepth / 2.0f - fDepth / 2.0f &&
					pPos->z < pModel->pos.z + pModel->fDepth / 2.0f + fDepth / 2.0f &&
					pPos->y >= pModel->pos.y - fHeight &&
					pBeforePos->y <= pModel->pos.y - fHeight)
			{
				pPos->y = pModel->pos.y - fHeight;
			}

			if (pPos->y < pModel->pos.y + pModel->fHeight &&
				pPos->y > pModel->pos.y - fHeight &&
				pPos->z > pModel->pos.z - pModel->fDepth / 2.0f - fDepth / 2.0f &&
				pPos->z < pModel->pos.z + pModel->fDepth / 2.0f + fDepth / 2.0f &&
				pPos->x >= pModel->pos.x - pModel->fWidth / 2.0f - fWidth / 2.0f &&
				pBeforePos->x <= pModel->pos.x - pModel->fWidth / 2.0f - fWidth / 2.0f)
			{
				pPos->x = pModel->pos.x - pModel->fWidth / 2.0f - fWidth / 2.0f;
			}
			else if (pPos->y < pModel->pos.y + pModel->fHeight &&
					pPos->y > pModel->pos.y - fHeight &&
					pPos->z > pModel->pos.z - pModel->fDepth / 2.0f - fDepth / 2.0f &&
					pPos->z < pModel->pos.z + pModel->fDepth / 2.0f + fDepth / 2.0f &&
					pPos->x <= pModel->pos.x + pModel->fWidth / 2.0f + fWidth / 2.0f &&
					pBeforePos->x >= pModel->pos.x + pModel->fWidth / 2.0f + fWidth / 2.0f)
			{
				pPos->x = pModel->pos.x + pModel->fWidth / 2.0f + fWidth / 2.0f;
			}

			if (pPos->y < pModel->pos.y + pModel->fHeight &&
				pPos->y > pModel->pos.y - fHeight &&
				pPos->x > pModel->pos.x - pModel->fWidth / 2.0f - fWidth / 2.0f &&
				pPos->x < pModel->pos.x + pModel->fWidth / 2.0f + fWidth / 2.0f &&
				pPos->z >= pModel->pos.z - pModel->fDepth / 2.0f - fDepth / 2.0f &&
				pBeforePos->z <= pModel->pos.z - pModel->fDepth / 2.0f - fDepth / 2.0f)
			{
				pPos->z = pModel->pos.z - pModel->fDepth / 2.0f - fDepth / 2.0f;
			}
			else if (pPos->y < pModel->pos.y + pModel->fHeight &&
					pPos->y > pModel->pos.y - fHeight &&
					pPos->x > pModel->pos.x - pModel->fWidth / 2.0f - fWidth / 2.0f &&
					pPos->x < pModel->pos.x + pModel->fWidth / 2.0f + fWidth / 2.0f &&
					pPos->z <= pModel->pos.z + pModel->fDepth / 2.0f + fDepth / 2.0f &&
					pBeforePos->z >= pModel->pos.z + pModel->fDepth / 2.0f + fDepth / 2.0f)
			{
				pPos->z = pModel->pos.z + pModel->fDepth / 2.0f + fDepth / 2.0f;
			}

		}
	}
	return bLand;
}

//=======================================================================
//取得処理
//=======================================================================
MODEL *GetModel(void)
{
	return &g_aModel[0];
}
