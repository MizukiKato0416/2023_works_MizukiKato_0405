//================================================
//敵の処理
//Author:KatoMizuki
//================================================
#include "manager.h"
#include "enemy.h"
#include "renderer.h"
#include "object3D.h"
#include "model_single.h"
#include "player.h"
#include "map.h"
#include "shadow.h"

//================================================
//マクロ定義
//================================================

//================================================
//静的メンバ変数宣言
//================================================
int CEnemy::m_nNum = 0;

//================================================
//デフォルトコンストラクタ
//================================================
CEnemy::CEnemy(int nPriority):CObject(nPriority)
{
	//生成する度増やす
	m_nNum++;

	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_bRotate = false;
	m_bDraw = false;
	m_bNotice = false;
	m_movePattern = ENEMY_MOVE_PATTERN::NONE;
	m_nStopCounter = 0;
	m_nMoveCounter = 0;
	m_nAttackCounter = 0;
	m_nDamageCounter = 0;
	m_nLife = 0;
	m_pShadow = nullptr;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CEnemy::~CEnemy()
{
	//消す度減らす
	m_nNum--;
}

//================================================
//終了処理
//================================================
void CEnemy::Uninit(void)
{
	//影を消す
	m_pShadow->Uninit();
	m_pShadow = nullptr;

	//オブジェクト情報を入れるポインタ
	CObject *pObject = nullptr;
	//オブジェクト情報を保存するポインタ変数
	CObject *pSaveObject = nullptr;
	//先頭のポインタを代入
	pObject = pObject->GetTopObj(CObject::PRIORITY_PLAYER);

	while (pObject != nullptr)
	{
		//現在の次のオブジェクトのポインタを保存
		pSaveObject = pObject;

		//オブジェクトの種類がプレイヤーだったら
		if (pObject->GetObjType() == CObject::OBJTYPE::PLAYER)
		{
			//プレイヤーにキャスト
			CPlayer *pPlayerObj = nullptr;
			pPlayerObj = (CPlayer*)pObject;

			//ロックオンしているなら
			if (pPlayerObj->GetEnemyNear() == this)
			{
				//nullにする
				pPlayerObj->SetEnemyNear(nullptr);
			}
		}
		//次のオブジェクトに進める
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}

	//マップ上の敵の位置破棄
	CMap::Delete(this);

	Release();
}

//================================================
//描画処理
//================================================
void CEnemy::Draw(void)
{
	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;			//計算用マトリックス

	D3DXMatrixIdentity(&m_mtxWorld);		//プレイヤーのワールドマトリックスの初期化

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
}

//================================================
//回転処理
//================================================
void CEnemy::Rotate(void)
{
	//回転させる状態なら
	if (m_bRotate == true)
	{
		//目的の向きを計算
		if (m_fObjectiveRot > D3DX_PI)
		{
			m_fObjectiveRot = -D3DX_PI - (D3DX_PI - m_fObjectiveRot);
		}
		else if (m_fObjectiveRot < -D3DX_PI)
		{
			m_fObjectiveRot = D3DX_PI - (-D3DX_PI - m_fObjectiveRot);
		}

		//現在の向きごとにそれぞれ向きを変える量を計算
		if (m_rot.y < 0.0f && -m_rot.y + m_fObjectiveRot > D3DX_PI)
		{
			m_fNumRot = (-D3DX_PI - m_rot.y) + -(D3DX_PI - m_fObjectiveRot);
		}
		else if (m_rot.y >= D3DX_PI / 2.0f && m_rot.y - m_fObjectiveRot > D3DX_PI)
		{
			m_fNumRot = (D3DX_PI - m_rot.y) - (-D3DX_PI - m_fObjectiveRot);
		}
		else
		{
			m_fNumRot = (m_fObjectiveRot - m_rot.y);
		}

		//向きに加算
		m_rot.y += m_fNumRot * 0.2f;

		//既定の値に達したら回転をやめる
		if (m_rot.y - m_fObjectiveRot < 0.001f && m_rot.y - m_fObjectiveRot > -0.001f)
		{
			m_bRotate = false;
		}
	}

	//πより大きくなったら-2πする
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y < -D3DX_PI)
	{	//-πより小さくなったら+2πする
		m_rot.y += D3DX_PI * 2.0f;
	}
}

//================================================
//当たり判定
//================================================
void CEnemy::Collision(CObject *pSubjectObject, float fObjRadius)
{
	//オブジェクト情報を入れるポインタ
	CObject *pObject = nullptr;
	//オブジェクト情報を保存するポインタ変数
	CObject *pSaveObject = nullptr;

	//先頭のポインタを代入
	pObject = pObject->GetTopObj(CObject::PRIORITY_ENEMY);

	while (pObject != nullptr)
	{
		//現在のオブジェクトのポインタを保存
		pSaveObject = pObject;

		//オブジェクトの種類が敵だったら
		if ((pObject->GetObjType() == CObject::OBJTYPE::ENEMY ||
			pObject->GetObjType() == CObject::OBJTYPE::ENEMY_FAT ||
			pObject->GetObjType() == CObject::OBJTYPE::ENEMY_BEE ||
			pObject->GetObjType() == CObject::OBJTYPE::ENEMY_BOSS) &&
			pObject != pSubjectObject)
		{
			//敵にキャスト
			CEnemy *pEnemyObj = nullptr;
			pEnemyObj = (CEnemy*)pObject;

			//オブジェクトの位置を取得
			D3DXVECTOR3 posObj = pSubjectObject->GetPos();

			//自身から対象のオブジェクトまでの距離を求める
			float fRadius = sqrtf((posObj.x - pEnemyObj->m_pos.x) * (posObj.x - pEnemyObj->m_pos.x) +
				(posObj.z - pEnemyObj->m_pos.z) * (posObj.z - pEnemyObj->m_pos.z));
			//自身と対象のオブジェクトの角度を求める
			float fRot = atan2((posObj.x - pEnemyObj->m_pos.x), (posObj.z - pEnemyObj->m_pos.z)) - D3DX_PI;

			//求めた距離がプレイヤーの半径と対象のオブジェクトの半径を足した数値以下だったら
			if (fRadius <= pEnemyObj->m_size.x / 2.0f + fObjRadius)
			{
				//自身の位置を押し出す
				pEnemyObj->m_pos.x = posObj.x + (sinf(fRot) * (pEnemyObj->m_size.x / 2.0f + fObjRadius));
				pEnemyObj->m_pos.z = posObj.z + (cosf(fRot) * (pEnemyObj->m_size.x / 2.0f + fObjRadius));

				//位置設定
				pEnemyObj->SetPos(pEnemyObj->m_pos);

				//モデルとの当たり判定
				CModelSingle::Collision(pEnemyObj);
			}
		}
		//次のオブジェクトに進める
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}

//================================================
//衝突判定のみの処理
//================================================
bool CEnemy::CollisionOnly(CObject * pSubjectObject, float fObjRadius)
{
	//オブジェクトの位置を取得
	D3DXVECTOR3 posObj = pSubjectObject->GetPos();

	//プレイヤーから対象のオブジェクトまでの距離を求める
	float fRadius = sqrtf((posObj.x - m_pos.x) * (posObj.x - m_pos.x) +
		(posObj.z - m_pos.z) * (posObj.z - m_pos.z));

	//求めた距離がプレイヤーの半径と対象のオブジェクトの半径を足した数値以下だったら
	if (fRadius <= m_size.x / 2.0f + fObjRadius)
	{
		//当たっている
		return true;
	}

	return false;
}