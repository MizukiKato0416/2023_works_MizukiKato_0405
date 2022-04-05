//================================================
//モデル単体を出す処理
//Author:加藤瑞葵
//================================================
#include "scene2D.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "model_single.h"
#include "renderer.h"
#include "model.h"
#include "x_load.h"
#include "game01.h"
#include "tutorial.h"
#include "player.h"
#include "control.h"
#include "control_up_down_wall.h"
#include "shadow.h"
#include "scene3D.h"
#include "play_data.h"
//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CModelSingle::CModelSingle(int nPriority):CScene(nPriority)
{
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pParent = NULL;
	m_pModel = NULL;
	m_modelType = MODEL_SINGLE_TYPE_NONE;
	m_bDelete = false;
	m_nCntDelete = 0;
	m_pControl = NULL;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CModelSingle::~CModelSingle()
{

}

//================================================
//初期化処理
//================================================
HRESULT CModelSingle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_pos = pos;
	m_posOld = m_pos;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bDelete = false;
	m_nCntDelete = 0;

	//モデルの生成
	m_pModel = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_rot, m_type);

	//親の設定
	m_pModel->SetParent(m_pParent);


	//オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_MODEL);

	//サイズを取得
	m_size = m_pModel->GetSize();
	SetSize(m_size);
	SetPos(m_pos);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CModelSingle::Uninit(void)
{
	Release();
}

//================================================
//更新処理
//================================================
void CModelSingle::Update(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();

	//位置の反映
	m_pos = pos;
	m_posOld = pos;

	//モデルの移動処理
	if (m_pControl != NULL)
	{
		m_pControl->Update(this);
		m_move = m_pControl->GetMove();
	}

	m_pos += m_move;		//移動量反映

	//位置反映
	SetPos(m_pos);
	SetPosOld(m_posOld);

	//オブジェクト情報を入れるポインタ
	CScene *pObject = NULL;
	//オブジェクト情報を保存するポインタ変数
	CScene *pSaveObject = NULL;

	//先頭のポインタを代入
	pObject = pObject->GetTopObj(CScene::PRIORITY_MODEL);

	if (m_modelType == MODEL_SINGLE_TYPE_DOWN_WALL || m_modelType == MODEL_SINGLE_TYPE_UP_WALL)
	{
		while (pObject != NULL)
		{
			//現在のオブジェクトのポインタを保存
			pSaveObject = pObject;

			if (pObject->GetObjType() == CScene::OBJTYPE_PLAYER)
			{
				//プレイヤーにキャスト
				CPlayer *pPlayer = NULL;
				pPlayer = (CPlayer*)pObject;
				//オブジェクトとの当たり判定
				pPlayer->Collision(this);
			}
			pObject = pSaveObject->GetObjNext(pSaveObject);
		}
	}

	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//パッド取得処理
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	m_pModel->Update();

	if (m_bDelete == true)
	{
		//カウントを加算
		m_nCntDelete++;
		if (m_nCntDelete >= MODEL_SINGLE_DELETE_TIME)
		{
			m_bDelete = false;
			m_nCntDelete = 0;
		}
	}

	//位置反映
	SetPos(m_pos);
}

//================================================
//描画処理
//================================================
void CModelSingle::Draw(void)
{
	//消えていなかったら
	if (m_bDelete == false)
	{
		//デバイスのポインタ
		LPDIRECT3DDEVICE9 pDevice;
		//デバイスの取得
		pDevice = CManager::GetRenderer()->GetDevice();

		D3DXMATRIX mtxRot, mtxTrans;			//計算用マトリックス

		D3DXMatrixIdentity(&m_mtxWorld);		//モデルのワールドマトリックスの初期化

												//モデルの向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//モデルの位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//モデルの描画
		m_pModel->Draw();
	}
}

//================================================
//生成処理
//================================================
CModelSingle *CModelSingle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CXload::X_TYPE type, CModel *pParent, MODEL_SINGLE_TYPE modelType)
{
	//インスタンスの生成
	CModelSingle *pModelSingle = NULL;
	if (pModelSingle == NULL)
	{
		pModelSingle = new CModelSingle;
		if (pModelSingle != NULL)
		{
			switch (modelType)
			{
			case MODEL_SINGLE_TYPE_UP_WALL:
				pModelSingle->m_pControl = CControlUpDownWall::Create(CControlUpDownWall::UP_WALL, 110.0f);
				break;

			case MODEL_SINGLE_TYPE_DOWN_WALL:
				pModelSingle->m_pControl = CControlUpDownWall::Create(CControlUpDownWall::DOWN_WALL, 110.0f);
				break;
			default:
				pModelSingle->m_pControl = NULL;
				break;
			}
			pModelSingle->m_rot = rot;
			pModelSingle->m_type = type;
			pModelSingle->m_modelType = modelType;
			pModelSingle->m_pParent = pParent;
			pModelSingle->Init(pos, pModelSingle->m_size);
		}
	}
	return pModelSingle;
}

//================================================
//当たり判定処理
//================================================
bool CModelSingle::SimpleCollision(CScene *pScene)
{
	bool bLand = false;	//着地しているかどうか

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

			//消えていなかったら
			if (pModelSingle->m_bDelete == false)
			{
				D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//対象の位置
				D3DXVECTOR3 posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//モデルの位置
				D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//対象のサイズ
				D3DXVECTOR3 sizeModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//モデルのサイズ
				D3DXVECTOR3 posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//対象の1フレーム前の位置

				//モデルの位置・サイズ取得
				posModel = pModelSingle->GetPos();
				sizeModel = pModelSingle->GetSize();

				//対象の位置・サイズ取得
				pos = pScene->GetPos();
				posOld = pScene->GetPosOld();
				size = pScene->GetSize();

				if (pos.x + size.x / 2.0f > posModel.x - sizeModel.x / 2.0f &&
					pos.x - size.x / 2.0f < posModel.x + sizeModel.x / 2.0f &&
					pos.z + size.x / 2.0f > posModel.z - sizeModel.z / 2.0f &&
					pos.z - size.x / 2.0f < posModel.z + sizeModel.z / 2.0f &&
					pos.y <= posModel.y + sizeModel.y &&
					posOld.y >= posModel.y + sizeModel.y)
				{
					pos.y = posModel.y + sizeModel.y;
					//位置を設定
					pScene->SetPos(pos);

					if (pModelSingle->m_modelType == MODEL_SINGLE_TYPE_UNINIT_FLOOR)
					{
						pModelSingle->m_bDelete = true;
						return false;
					}
					else if (pModelSingle->m_modelType == MODEL_SINGLE_TYPE_GOAL)
					{
						//フェーズをゴールにする
						if (CManager::GetGame01() != NULL)
						{
							//プレイヤーにキャスト
							CPlayer *pPlayer = NULL;
							pPlayer = (CPlayer*)pScene;

							CManager::GetGame01()->SetPhase(CGame01::GAME01_PHASE_CLEAR);

							CPlayData::SetWinNum(pPlayer->GetNum());
						}
						if (CManager::GetTutorial() != NULL)
						{
							CManager::GetTutorial()->SetGoal(true);
						}
					}
					else if (pModelSingle->m_modelType == MODEL_SINGLE_TYPE_MIDDLE1_FLOOR)
					{//中間の床に乗ったら
						if (CManager::GetGame01() != NULL)
						{
							//プレイヤーにキャスト
							CPlayer *pPlayer = NULL;
							pPlayer = (CPlayer*)pScene;

							//チェックポイントがひとつ前ならチェックポイントを設定
							if (pPlayer->GetCheckPoint() == CPlayer::PLAYER_CHECK_POINT_NONE)
							{
								pPlayer->SetCheckPoint(CPlayer::PLAYER_CHECK_POINT_GAME01_MIDDLE1);
							}
						}
					}
					else if (pModelSingle->m_modelType == MODEL_SINGLE_TYPE_MIDDLE2_FLOOR)
					{//中間の床に乗ったら
						if (CManager::GetGame01() != NULL)
						{
							//プレイヤーにキャスト
							CPlayer *pPlayer = NULL;
							pPlayer = (CPlayer*)pScene;

							//チェックポイントがひとつ前ならチェックポイントを設定
							if (pPlayer->GetCheckPoint() == CPlayer::PLAYER_CHECK_POINT_GAME01_MIDDLE1)
							{
								pPlayer->SetCheckPoint(CPlayer::PLAYER_CHECK_POINT_GAME01_MIDDLE2);
							}
						}
					}
					else if (pModelSingle->m_modelType == MODEL_SINGLE_TYPE_ICE_FLOOR)
					{//氷の床に乗ったら

						if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)
						{
							//プレイヤーにキャスト
							CPlayer *pPlayer = NULL;
							pPlayer = (CPlayer*)pScene;

							pPlayer->SetOnIce(true);
						}
					}
					else if (pModelSingle->m_modelType == MODEL_SINGLE_TYPE_SPRING)
					{//ばねの床に乗ったら
						if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)
						{
							//プレイヤーにキャスト
							CPlayer *pPlayer = NULL;
							pPlayer = (CPlayer*)pScene;

							pPlayer->SetOnSpring(true);
						}
					}

					if (pModelSingle->m_modelType != MODEL_SINGLE_TYPE_ICE_FLOOR)
					{
						if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)
						{
							//プレイヤーにキャスト
							CPlayer *pPlayer = NULL;
							pPlayer = (CPlayer*)pScene;

							pPlayer->SetOnIce(false);
						}
					}

					if (pModelSingle->m_modelType != MODEL_SINGLE_TYPE_SPRING)
					{
						if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)
						{
							//プレイヤーにキャスト
							CPlayer *pPlayer = NULL;
							pPlayer = (CPlayer*)pScene;

							pPlayer->SetOnSpring(false);
						}
					}

					bLand = true;
				}
				else if (pos.x + size.x / 2.0f > posModel.x - sizeModel.x / 2.0f &&
					pos.x - size.x / 2.0f < posModel.x + sizeModel.x / 2.0f &&
					pos.z + size.x / 2.0f > posModel.z - sizeModel.z / 2.0f &&
					pos.z - size.x / 2.0f < posModel.z + sizeModel.z / 2.0f &&
					pos.y + size.y >= posModel.y &&
					posOld.y + size.y <= posModel.y)
				{
					pos.y = posModel.y - size.y;
					//位置を設定
					pScene->SetPos(pos);
				}
				if (pos.y + size.y > posModel.y &&
					pos.y < posModel.y + sizeModel.y &&
					pos.z + size.x / 2.0f > posModel.z - sizeModel.z / 2.0f &&
					pos.z - size.x / 2.0f < posModel.z + sizeModel.z / 2.0f &&
					pos.x + size.x / 2.0f >= posModel.x - sizeModel.x / 2.0f &&
					posOld.x + size.x / 2.0f <= posModel.x - sizeModel.x / 2.0f)
				{
					pos.x = posModel.x - sizeModel.x / 2.0f - size.x / 2.0f;
					//位置を設定
					pScene->SetPos(pos);
				}
				else if (pos.y + size.y > posModel.y &&
					pos.y < posModel.y + sizeModel.y &&
					pos.z + size.x / 2.0f > posModel.z - sizeModel.z / 2.0f &&
					pos.z - size.x / 2.0f < posModel.z + sizeModel.z / 2.0f &&
					pos.x - size.x / 2.0f <= posModel.x + sizeModel.x / 2.0f &&
					posOld.x - size.x / 2.0f >= posModel.x + sizeModel.x / 2.0f)
				{
					pos.x = posModel.x + sizeModel.x / 2.0f + size.x / 2.0f;
					//位置を設定
					pScene->SetPos(pos);
				}
				if (pos.y + size.y > posModel.y &&
					pos.y < posModel.y + sizeModel.y &&
					pos.x + size.x / 2.0f > posModel.x - sizeModel.x / 2.0f &&
					pos.x - size.x / 2.0f < posModel.x + sizeModel.x / 2.0f &&
					pos.z + size.x / 2.0f >= posModel.z - sizeModel.z / 2.0f &&
					posOld.z + size.x / 2.0f <= posModel.z - sizeModel.z / 2.0f)
				{
					pos.z = posModel.z - sizeModel.z / 2.0f - size.x / 2.0f;
					//位置を設定
					pScene->SetPos(pos);
				}
				else if (pos.y + size.y > posModel.y &&
					pos.y < posModel.y + sizeModel.y &&
					pos.x + size.x / 2.0f > posModel.x - sizeModel.x / 2.0f &&
					pos.x - size.x / 2.0f < posModel.x + sizeModel.x / 2.0f &&
					pos.z - size.x / 2.0f <= posModel.z + sizeModel.z / 2.0f &&
					posOld.z - size.x / 2.0f >= posModel.z + sizeModel.z / 2.0f)
				{
					pos.z = posModel.z + sizeModel.z / 2.0f + size.x / 2.0f;
					//位置を設定
					pScene->SetPos(pos);
				}
			}
		}
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
	return bLand;
}

//================================================
//使用状況の取得処理
//================================================
bool CModelSingle::GetDeleteObject(void)
{
	return m_bDelete;
}