//================================================
//3Dポリゴンの床処理
//Author:KatoMizuki
//================================================
#include <math.h>
#include "floor.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CFloor::CFloor(int nPriority) :CObject3D(nPriority)
{
	
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CFloor::~CFloor()
{

}

//================================================
//初期化処理
//================================================
HRESULT CFloor::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CObject3D::Init(pos,size);

	//オブジェクトの種類を設定
	SetObjType(CObject::OBJTYPE::FLOOR);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CFloor::Uninit(void)
{
	CObject3D::Uninit();
}

//================================================
//更新処理
//================================================
void CFloor::Update(void)
{
	
}

//================================================
//描画処理
//================================================
void CFloor::Draw(void)
{
	CObject3D::Draw();
}

//================================================
//生成処理
//================================================
CFloor* CFloor::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	//インスタンスの生成
	CFloor *pFloor = nullptr;
	if (pFloor == nullptr)
	{
		pFloor = new CFloor();
		if (pFloor != nullptr)
		{
			pFloor->m_rot = rot;
			pFloor->Init(pos, size);
		}
	}
	return pFloor;
}

//================================================
//当たり判定
//================================================
bool CFloor::Collision(CObject *pObject)
{
	bool bLand = false;	//着地しているかどうか

	//オブジェクト情報を入れるポインタ
	CObject *pThisObject = nullptr;
	//オブジェクト情報を保存するポインタ変数
	CObject *pSaveObject = nullptr;

	//先頭のポインタを代入
	pThisObject = pThisObject->GetTopObj(CObject::PRIORITY_POLYGON_3D);

	while (pThisObject != nullptr)
	{
		//現在のオブジェクトのポインタを保存
		pSaveObject = pThisObject;

		if (pThisObject->GetObjType() == CObject::OBJTYPE::FLOOR)
		{
			//ポインタをCFloorにキャスト
			CFloor *pFloor = nullptr;
			pFloor = (CFloor*)pThisObject;

			//各頂点から各頂点のベクトルを算出
			D3DXVECTOR3 vtxPos[VERTEX_3D_NUM];
			for (int nCntVtx = 0; nCntVtx < VERTEX_3D_NUM; nCntVtx++)
			{
				vtxPos[nCntVtx] = D3DXVECTOR3(pFloor->m_vtxMtxWorld[nCntVtx]._41,
												pFloor->m_vtxMtxWorld[nCntVtx]._42,
												pFloor->m_vtxMtxWorld[nCntVtx]._43);
			}
			D3DXVECTOR3 vecVtx[VERTEX_3D_NUM];
			vecVtx[0] = vtxPos[1] - vtxPos[0];
			vecVtx[1] = vtxPos[3] - vtxPos[1];
			vecVtx[2] = vtxPos[2] - vtxPos[3];
			vecVtx[3] = vtxPos[0] - vtxPos[2];

			//法線保存用
			D3DXVECTOR3 vecNor;

			//頂点から頂点までのベクトル算出用
			D3DXVECTOR3 vtxVec[2];
			//頂点から頂点までのベクトル算出
			vtxVec[0] = vtxPos[1] - vtxPos[0];
			vtxVec[1] = vtxPos[2] - vtxPos[0];

			//ポリゴンの法線を求める
			D3DXVec3Cross(&vecNor, &vtxVec[0], &vtxVec[1]);

			//ベクトルを正規化する(ベクトルの大きさを1にする)
			D3DXVec3Normalize(&vecNor, &vecNor);

			//対象の現在位置取得
			D3DXVECTOR3 pos = pObject->GetPos();

			//各頂点から対象の現在位置までのベクトルを算出
			D3DXVECTOR3 vecObj[VERTEX_3D_NUM];
			vecObj[0] = pos - vtxPos[0];
			vecObj[1] = pos - vtxPos[1];
			vecObj[2] = pos - vtxPos[3];
			vecObj[3] = pos - vtxPos[2];

			//対象の1フレーム前の位置取得
			D3DXVECTOR3 posOld = pObject->GetPosOld();

			//各頂点から対象の1フレーム前の位置までのベクトルを算出
			D3DXVECTOR3 vecObjOld[VERTEX_3D_NUM];
			vecObjOld[0] = posOld - vtxPos[0];
			vecObjOld[1] = posOld - vtxPos[1];
			vecObjOld[2] = posOld - vtxPos[3];
			vecObjOld[3] = posOld - vtxPos[2];

			//各頂点から対象の現在位置までのベクトルと各頂点から各頂点のベクトルの外積(2D)を求める
			float fvecCross[VERTEX_3D_NUM];
			//各頂点から対象の1フレーム前の位置までのベクトルと各頂点から各頂点のベクトルの外積(2D)を求める
			float fvecCrossOld[VERTEX_3D_NUM];

			for (int nCntVec = 0; nCntVec < VERTEX_3D_NUM; nCntVec++)
			{
				//外積の計算
				fvecCross[nCntVec] = (vecVtx[nCntVec].x * vecObj[nCntVec].z) - (vecObj[nCntVec].x * vecVtx[nCntVec].z);
				fvecCrossOld[nCntVec] = (vecVtx[nCntVec].x * vecObjOld[nCntVec].z) - (vecObjOld[nCntVec].x * vecVtx[nCntVec].z);
			}

			//ポリゴンの範囲内にいるかどうか
			if ((fvecCross[0] <= 0.0f && fvecCross[1] <= 0.0f && fvecCross[2] <= 0.0f && fvecCross[3] <= 0.0f) ||
				(fvecCrossOld[0] <= 0.0f && fvecCrossOld[1] <= 0.0f && fvecCrossOld[2] <= 0.0f && fvecCrossOld[3] <= 0.0f))
			{
				//ポリゴンの位置から対象の現在の位置のベクトルを算出
				D3DXVECTOR3 vecPos;
				vecPos = pos - pFloor->m_pos;

				//算出したベクトルと法線のベクトルの内積を求める
				float fVecDot;
				fVecDot = D3DXVec3Dot(&vecNor, &vecPos);

				//ポリゴンの頂点から対象の1フレーム前の位置のベクトルを算出
				D3DXVECTOR3 vecPosOld;
				vecPosOld = posOld - pFloor->m_pos;

				//算出したベクトルと法線のベクトルの内積を求める
				float fVecDotOld;
				fVecDotOld = D3DXVec3Dot(&vecNor, &vecPosOld);

				//内積の計算結果がマイナスの時
				if (fVecDot < 0.0f && fVecDotOld >= -FLT_EPSILON * 10000)
				{
					//押し出す位置を求める
					D3DXVECTOR3 objectPos = pos;
					objectPos.y = ((vecNor.x * vecPos.x) - (vecNor.z * vecPos.z)) / vecNor.y;

					objectPos.y += pFloor->m_pos.y;

					pObject->SetPos(objectPos);
					bLand = true;
				}
			}
		}
		pThisObject = pSaveObject->GetObjNext(pSaveObject);
	}
	return bLand;
}