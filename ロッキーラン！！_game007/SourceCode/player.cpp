//================================================
//プレイヤー処理
//Author:加藤瑞葵
//================================================
#include "scene2D.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "player.h"
#include "renderer.h"
#include "model.h"
#include "x_load.h"
#include "control.h"
#include "control_player.h"
#include "shadow.h"
#include "model_single.h"
#include "camera.h"
#include "motion_player.h"
#include "2DAnimation_jump.h"
#include "sound.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CPlayer::CPlayer(int nPriority):CScene(nPriority)
{
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pParent = NULL;
	m_pControl = NULL;
	m_bLand = false;
	m_bJump = false;
	m_bDive = false;
	m_bOnIce = false;
	m_bOnIce = false;
	m_bOnSpring = false;
	for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
	{
		m_apModel[nCntModel] = NULL;
	}
	m_pMotionPlayer = NULL;
	m_pShadow = NULL;
	m_bLandMoment = false;
	m_bJumpOld = false;
	m_nNum = 0;
	m_checkPoint = PLAYER_CHECK_POINT_NONE;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CPlayer::~CPlayer()
{

}

//================================================
//初期化処理
//================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	//クリアSE再生
	pSound->Play(CSound::SOUND_LABEL_RESPAWN_SE);

	m_pos = pos;
	m_posOld = pos;
	m_move = m_pControl->GetMove();
	m_bLand = false;
	m_bJump = true;
	m_bDive = false;
	m_bLandMoment = false;
	m_bJumpOld = false;
	m_bOnIce = false;
	m_bOnSpring = false;
	m_checkPoint = PLAYER_CHECK_POINT_NONE;

	//モデルの生成
	switch (m_nNum)
	{
	case 0:
		m_apModel[0] = CModel::Create(D3DXVECTOR3(0.0f, 8.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_PLAYER_BODY);
		m_apModel[1] = CModel::Create(D3DXVECTOR3(-10.0f, 12.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_PLAYER_ARM_R);
		m_apModel[2] = CModel::Create(D3DXVECTOR3(10.0f, 12.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_PLAYER_ARM_L);
		m_apModel[3] = CModel::Create(D3DXVECTOR3(-5.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_PLAYER_LEG_R);
		m_apModel[4] = CModel::Create(D3DXVECTOR3(5.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_PLAYER_LEG_L);
		break;
	case 1:
		m_apModel[0] = CModel::Create(D3DXVECTOR3(0.0f, 8.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_PLAYER_GIRL_BODY);
		m_apModel[1] = CModel::Create(D3DXVECTOR3(-10.0f, 12.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_PLAYER_GIRL_ARM_R);
		m_apModel[2] = CModel::Create(D3DXVECTOR3(10.0f, 12.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_PLAYER_GIRL_ARM_L);
		m_apModel[3] = CModel::Create(D3DXVECTOR3(-5.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_PLAYER_GIRL_LEG_R);
		m_apModel[4] = CModel::Create(D3DXVECTOR3(5.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_PLAYER_GIRL_LEG_L);
	default:
		break;
	}

	//親の設定
	m_apModel[0]->SetParent(NULL);
	m_apModel[1]->SetParent(m_apModel[0]);
	m_apModel[2]->SetParent(m_apModel[0]);
	m_apModel[3]->SetParent(m_apModel[0]);
	m_apModel[4]->SetParent(m_apModel[0]);

	//位置の設定
	SetPos(m_pos);
	SetPosOld(m_posOld);

	//オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_PLAYER);

	//サイズを取得
	m_size = m_apModel[0]->GetSize();

	//サイズの設定
	SetSize(m_size);

	//モーションの生成
	m_pMotionPlayer = CMotionPlayer::Create(this);

	//cameraのポインタ配列1番目のアドレス取得
	CCamera **pCameraAddress = CManager::GetCamera();

	for (int nCntCamera = 0; nCntCamera <MAX_CAMERA; nCntCamera++, pCameraAddress++)
	{
		//cameraの取得
		CCamera *pCamera = &**pCameraAddress;
		if (pCamera != NULL)
		{
			if (m_nNum == pCamera->GetNum())
			{
				if (CManager::GetResult() != NULL)
				{
					//cameraの向き設定
					pCamera->SetRotV(D3DXVECTOR3(m_rot.x, m_rot.y - D3DX_PI, m_rot.z));
					//cameraの注視点設定処理
					pCamera->SetPosR(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z));
					//cameraの視点設定処理
					pCamera->SetPosV(D3DXVECTOR3(m_pos.x + sinf(m_rot.y - D3DX_PI) * CAMERA_RESULT_DISTANCE,
													100.0f,
													m_pos.z + cosf(m_rot.y - D3DX_PI) * CAMERA_RESULT_DISTANCE));
				}
				else
				{
					//cameraの向き設定
					pCamera->SetRotV(m_rot);
					//cameraの注視点設定処理
					pCamera->SetPosR(m_pos);
					//cameraの視点設定処理
					pCamera->SetPosV(D3DXVECTOR3(m_pos.x + sinf(m_rot.y) * CAMERA_DISTANCE, 150.0f, m_pos.z + cosf(m_rot.y) * CAMERA_DISTANCE));
				}
			}
		}
	}
	return S_OK;
}

//================================================
//終了処理
//================================================
void CPlayer::Uninit(void)
{
	//影を消す
	m_pShadow->Uninit();
	delete m_pShadow;
	m_pShadow = NULL;

	Release();
}

//================================================
//更新処理
//================================================
void CPlayer::Update(void)
{
	if (this != NULL)
	{
		//位置取得
		D3DXVECTOR3 pos = GetPos();
		m_pos = pos;
		m_posOld = pos;
		//1フレーム前の位置設定
		SetPosOld(m_posOld);

		//前のフレームのジャンプしているかどうかの情報を代入
		m_bJumpOld = m_bJump;

		//キーボード取得処理
		CInputKeyboard *pInputKeyboard;
		pInputKeyboard = CManager::GetInputKeyboard();

		//パッド取得処理
		CInputPadX *pInputPadX;
		pInputPadX = CManager::GetInputPadX();

		//移動処理
		Move();

		m_pos += m_move;		//移動量反映

		//プレイヤーとの当たり判定
		CollisionPlayer(this);

		//位置反映
		SetPos(m_pos);

		//着地しているときは移動量を0にする
		m_bLand = CModelSingle::SimpleCollision(this);
		if (m_bLand == true)
		{
			if (m_bJumpOld == true)
			{
				//ジャンプモーション時
				if (m_pMotionPlayer->GetMotion() == CMotionPlayer::MOTION_PLAYER_TYPE_JUMP)
				{
					//着地モーションにする
					m_pMotionPlayer->SetMotion(CMotionPlayer::MOTION_PLAYER_TYPE_LAND);

					//着地アニメーション
					C2DAnimationJump::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 10.0f, m_pos.z),
											D3DXVECTOR3(25.0f, 25.0f, 0.0f), 
											D3DXVECTOR3(m_rot.x, m_rot.y + 3.14f, m_rot.z), 0.1f);
					m_bJump = false;
					m_move.y = 0.0f;
				}
			}
		}
		else
		{
			m_bLandMoment = false;
		}
		
		//モーション
		m_pMotionPlayer->Update(this);

		//影の追従
		ShadowCollision();

		//位置取得
		m_pos = GetPos();
	}
}

//================================================
//描画処理
//================================================
void CPlayer::Draw(void)
{
	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;			//計算用マトリックス

	D3DXMatrixIdentity(&m_mtxWorld);		//プレイヤーのワールドマトリックスの初期化

	//プレイヤーの向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//プレイヤーの位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//モデルの描画
	for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
	{
		m_apModel[nCntModel]->Draw();
	}

}

//================================================
//生成処理
//================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNum)
{
	//インスタンスの生成
	CPlayer *pPlayer = NULL;
	if (pPlayer == NULL)
	{
		pPlayer = new CPlayer;
		if (pPlayer != NULL)
		{
			pPlayer->m_pShadow = CShadow::Create(D3DXVECTOR3(pos.x, 0.0f, pos.z), D3DXVECTOR3(40.0f, 0.0f, 40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			pPlayer->m_pControl = CControlPlayer::Create();
			pPlayer->m_rot = rot;
			pPlayer->m_nNum = nNum;
			pPlayer->Init(pos, pPlayer->m_size);
		}
	}
	return pPlayer;
}

//================================================
//1フレーム前の位置取得
//================================================
D3DXVECTOR3 CPlayer::GetPosOld(void)
{
	return m_posOld;
}

//================================================
//当たり判定処理
//================================================
bool CPlayer::Collision(void)
{
	return false;
}

//================================================
//移動処理
//================================================
void CPlayer::Move(void)
{
	if (m_pControl != NULL)
	{
		m_pControl->Update(this);
		m_move = m_pControl->GetMove();
	}
}

//================================================
//着地設定処理
//================================================
void CPlayer::SetLand(bool bLand)
{
	m_bLand = bLand;
}

//================================================
//着地取得処理
//================================================
bool CPlayer::GetLand(void)
{
	return m_bLand;
}

//================================================
//向き取得処理
//================================================
D3DXVECTOR3 CPlayer::GetRot(void)
{
	return m_rot;
}

//================================================
//向き設定処理
//================================================
void CPlayer::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//================================================
//移動量取得処理
//================================================
void CPlayer::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//================================================
//移動量取得処理
//================================================
D3DXVECTOR3 CPlayer::GetMove(void)
{
	return m_move;
}

//================================================
//ジャンプ取得処理
//================================================
void CPlayer::SetJump(bool bJump)
{
	m_bJump = bJump;
}

//================================================
//ジャンプ取得処理
//================================================
bool CPlayer::GetJump(void)
{
	return m_bJump;
}

//================================================
//ダイブ取得処理
//================================================
void CPlayer::SetDive(bool bDive)
{
	m_bDive = bDive;
}

//================================================
//ダイブ取得処理
//================================================
bool CPlayer::GetDive(void)
{
	return m_bDive;
}

//================================================
//モデルの位置設定処理
//================================================
void CPlayer::SetModelPos(int nCntModel, D3DXVECTOR3 pos)
{
	m_apModel[nCntModel]->SetPos(pos);
}

//================================================
//モデルの位置取得処理
//================================================
D3DXVECTOR3 CPlayer::GetModelPos(int nCntModel)
{
	return m_apModel[nCntModel]->GetPos();
}

//================================================
//モデルの向き設定処理
//================================================
void CPlayer::SetModelRot(int nCntModel, D3DXVECTOR3 rot)
{
	m_apModel[nCntModel]->SetRot(rot);
}

//================================================
//モデルの向き取得処理
//================================================
D3DXVECTOR3 CPlayer::GetModelRot(int nCntModel)
{
	return m_apModel[nCntModel]->GetRot();
}

//================================================
//モーションプレイヤー取得処理
//================================================
CMotionPlayer *CPlayer::GetMotionPlayer(void)
{
	return m_pMotionPlayer;
}

//================================================
//氷の上かどうか設定処理
//================================================
void CPlayer::SetOnIce(bool bOnIce)
{
	m_bOnIce = bOnIce;
}

//================================================
//氷の上かどうか取得処理
//================================================
bool CPlayer::GetOnIce(void)
{
	return m_bOnIce;
}

//================================================
//バネかどうか設定処理
//================================================
void CPlayer::SetOnSpring(bool bOnSpring)
{
	m_bOnSpring = bOnSpring;
}

//================================================
//バネかどうか取得処理
//================================================
bool CPlayer::GetOnSpring(void)
{
	return m_bOnSpring;
}

//================================================
//オブジェクトとの当たり判定
//================================================
void CPlayer::Collision(CScene *pScene)
{
	//オブジェクトの位置を取得
	D3DXVECTOR3 posObj = pScene->GetPos();
	//オブジェクトの1フレーム前の位置を取得
	D3DXVECTOR3 posObjOld = pScene->GetPosOld();
	//オブジェクトのサイズを取得
	D3DXVECTOR3 sizeObj = pScene->GetSize();

	if (posObj.x + sizeObj.x / 2.0f > m_pos.x - m_size.x / 2.0f &&
		posObj.x - sizeObj.x / 2.0f < m_pos.x + m_size.x / 2.0f &&
		posObj.z + sizeObj.z / 2.0f > m_pos.z - m_size.x / 2.0f &&
		posObj.z - sizeObj.z / 2.0f < m_pos.z + m_size.x / 2.0f &&
		posObj.y + sizeObj.y >= m_pos.y&&
		posObjOld.y + sizeObj.y <= m_pos.y)
	{
		m_pos.y = posObj.y + sizeObj.y;
		//位置を設定
		SetPos(m_pos);
		//1フレーム前の位置を設定
		SetPosOld(m_pos);
		if (pScene->GetObjType() == OBJTYPE_MODEL)
		{
			m_move.z -= 2.0f;
		}
	}
	else if (posObj.x + sizeObj.x / 2.0f > m_pos.x - m_size.x / 2.0f &&
			 posObj.x - sizeObj.x / 2.0f < m_pos.x + m_size.x / 2.0f &&
			 posObj.z + sizeObj.z / 2.0f > m_pos.z - m_size.x / 2.0f &&
			 posObj.z - sizeObj.z / 2.0f < m_pos.z + m_size.x / 2.0f &&
			 posObj.y <= m_pos.y + m_size.y &&
			 posObjOld.y >= m_pos.y + m_size.y)
	{
		m_pos.y = posObj.y - m_size.y;
		//位置を設定
		SetPos(m_pos);
		//1フレーム前の位置を設定
		SetPosOld(m_pos);
	}
	if (posObj.y + sizeObj.y < m_pos.y &&
		posObj.y > m_pos.y + m_size.y &&
		posObj.z + sizeObj.z / 2.0f > m_pos.z - m_size.x / 2.0f &&
		posObj.z - sizeObj.z / 2.0f < m_pos.z + m_size.x / 2.0f &&
		posObj.x + sizeObj.x / 2.0f <= m_pos.x - m_size.x / 2.0f &&
		posObjOld.x + sizeObj.x / 2.0f >= m_pos.x - m_size.x / 2.0f)
	{
		m_pos.x = posObj.x + sizeObj.x / 2.0f - m_size.x / 2.0f;
		//位置を設定
		SetPos(m_pos);
		//1フレーム前の位置を設定
		SetPosOld(m_pos);
	}
	else if (posObj.y + sizeObj.y < m_pos.y &&
			 posObj.y > m_pos.y + m_size.y &&
			 posObj.z + sizeObj.z / 2.0f > m_pos.z - m_size.x / 2.0f &&
			 posObj.z - sizeObj.z / 2.0f < m_pos.z + m_size.x / 2.0f &&
			 posObj.x - sizeObj.x / 2.0f >= m_pos.x + m_size.x / 2.0f &&
			 posObjOld.x - sizeObj.x / 2.0f <= m_pos.x + m_size.x / 2.0f)
	{
		m_pos.x = posObj.x - sizeObj.x / 2.0f + m_size.x / 2.0f;
		//位置を設定
		SetPos(m_pos);
		//1フレーム前の位置を設定
		SetPosOld(m_pos);
	}
	if (posObj.y + sizeObj.y < m_pos.y &&
		posObj.y > m_pos.y + m_size.y &&
		posObj.x + sizeObj.x / 2.0f > m_pos.x - m_size.x / 2.0f &&
		posObj.x - sizeObj.x / 2.0f < m_pos.x + m_size.x / 2.0f &&
		posObj.z + sizeObj.z / 2.0f <= m_pos.z - m_size.x / 2.0f &&
		posObjOld.z + sizeObj.z / 2.0f >= m_pos.z - m_size.x / 2.0f)
	{
		m_pos.z = posObj.z - sizeObj.z / 2.0f + m_size.x / 2.0f;
		//位置を設定
		SetPos(m_pos);
		//1フレーム前の位置を設定
		SetPosOld(m_pos);
	}
	else if (posObj.y + sizeObj.y < m_pos.y &&
			 posObj.y > m_pos.y + m_size.y &&
			 posObj.x + sizeObj.x / 2.0f > m_pos.x - m_size.x / 2.0f &&
			 posObj.x - sizeObj.x / 2.0f < m_pos.x + m_size.x / 2.0f &&
			 posObj.z - sizeObj.z / 2.0f >= m_pos.z + m_size.x / 2.0f &&
			 posObjOld.z - sizeObj.z / 2.0f <= m_pos.z + m_size.x / 2.0f)
	{
		m_pos.z = posObj.z + sizeObj.z / 2.0f - m_size.x / 2.0f;
		//位置を設定
		SetPos(m_pos);
		//1フレーム前の位置を設定
		SetPosOld(m_pos);
	}
}

//================================================
//プレイヤーとの当たり判定
//================================================
void CPlayer::CollisionPlayer(CPlayer *pPlayer)
{
	//オブジェクト情報を入れるポインタ
	CScene *pObject = NULL;
	//オブジェクト情報を保存するポインタ変数
	CScene *pSaveObject = NULL;

	//先頭のポインタを代入
	pObject = pObject->GetTopObj(CScene::PRIORITY_MODEL);

	while (pObject != NULL)
	{
		//現在のオブジェクトのポインタを保存
		pSaveObject = pObject;

		if (pObject->GetObjType() == CScene::OBJTYPE_PLAYER)
		{
			//プレイヤーにキャスト
			CPlayer *pPlayerObj = NULL;
			pPlayerObj = (CPlayer*)pObject;

			if (pPlayerObj->GetNum() != pPlayer->GetNum())
			{
				//オブジェクトの位置を取得
				D3DXVECTOR3 posObj = pPlayerObj->GetPos();
				//オブジェクトの1フレーム前の位置を取得
				D3DXVECTOR3 posObjOld = pPlayerObj->GetPosOld();
				//オブジェクトのサイズを取得
				D3DXVECTOR3 sizeObj = pPlayerObj->GetSize();

				float fRadius = sqrtf((posObj.x - pPlayer->m_pos.x) * (posObj.x - pPlayer->m_pos.x) + (posObj.z - pPlayer->m_pos.z) * (posObj.z - pPlayer->m_pos.z));
				float fRot = atan2((posObj.x - pPlayer->m_pos.x), (posObj.z - pPlayer->m_pos.z)) - D3DX_PI;
				pPlayer->m_rot;

				if (fRadius <= pPlayer->m_size.x * 2.0f)
				{
					pPlayer->m_pos.x = posObj.x + (sinf(fRot) * pPlayer->m_size.x * 2.0f);
					pPlayer->m_pos.z = posObj.z + (cosf(fRot) * pPlayer->m_size.x * 2.0f);
				}
			}
		}
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}


//================================================
//個体識別番号設定処理
//================================================
void CPlayer::SetNum(int nNum)
{
	m_nNum = nNum;
}

//================================================
//バネかどうか取得処理
//================================================
int CPlayer::GetNum(void)
{
	return m_nNum;
}

//================================================
//チェックポイント設定処理
//================================================
void CPlayer::SetCheckPoint(PLAYER_CHECK_POINT checkPoint)
{
	m_checkPoint = checkPoint;
}

//================================================
//チェックポイント取得処理
//================================================
CPlayer::PLAYER_CHECK_POINT CPlayer::GetCheckPoint(void)
{
	return m_checkPoint;
}

//================================================
//影の表示のためのオブジェクトとの当たり判定
//================================================
void CPlayer::ShadowCollision(void)
{
	//オブジェクト情報を入れるポインタ
	CScene *pObject = NULL;
	//オブジェクト情報を保存するポインタ変数
	CScene *pSaveObject = NULL;

	//先頭のポインタを代入
	pObject = pObject->GetTopObj(CScene::PRIORITY_MODEL);

	while (pObject != NULL)
	{
		//現在のオブジェクトのポインタを保存
		pSaveObject = pObject;

		if (pObject->GetObjType() == CScene::OBJTYPE_MODEL)
		{
			//モデルシングルにキャスト
			CModelSingle *pModelSingle = NULL;
			pModelSingle = (CModelSingle*)pObject;

			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			//オブジェクトの位置を取得
			D3DXVECTOR3 posObj = pModelSingle->GetPos();
			//オブジェクトの1フレーム前の位置を取得
			D3DXVECTOR3 posObjOld = pModelSingle->GetPosOld();
			//オブジェクトのサイズを取得
			D3DXVECTOR3 sizeObj = pModelSingle->GetSize();

			if (posObj.x + sizeObj.x / 2.0f > m_pos.x - m_size.x / 2.0f &&
				posObj.x - sizeObj.x / 2.0f < m_pos.x + m_size.x / 2.0f &&
				posObj.z + sizeObj.z / 2.0f > m_pos.z - m_size.x / 2.0f &&
				posObj.z - sizeObj.z / 2.0f < m_pos.z + m_size.x / 2.0f &&
				posObj.y + sizeObj.y >= m_pos.y - 50.0f &&
				posObj.y + sizeObj.y <= m_pos.y)
			{
				//オブジェクトが消えてない場合のみ
				if (pModelSingle->GetDeleteObject() == false)
				{
					//位置をモデルの上に
					pos.y = posObj.y + sizeObj.y;

					//影の追従
					m_pShadow->SetShadow(D3DXVECTOR3(m_pos.x, pos.y, m_pos.z), (m_pos.y - pos.y));


					//影を使っている状態にする
					m_pShadow->SetUseShadow(true);

					return;
				}
			}
			else
			{
				//影を使っていない状態にする
				m_pShadow->SetUseShadow(false);
			}
		}
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}