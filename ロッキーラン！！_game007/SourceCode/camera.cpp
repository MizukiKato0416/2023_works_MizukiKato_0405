//=======================================================================
//カメラに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#include "main.h"
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "player.h"
#include "play_data.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CCamera::CCamera()
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//カメラの向き
	m_rotAsk = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//目的のカメラの向き
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//現在の視点
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//目的の視点
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//現在の注視点
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//目的の注視点
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//法線
	m_rotDiffer = 0.0f;								//目的と向きの差
	m_viewport.X = (DWORD)0.0f;						//描画する画面の左上X座標
	m_viewport.Y = (DWORD)0.0f;						//描画する画面の左上Y座標
	m_viewport.MinZ = 0.0f;							//描画するz座標の範囲の最小値
	m_viewport.MaxZ = 0.0f;							//描画するz座標の範囲の最大値
	m_viewport.Width = (DWORD)0.0f;					//描画する画面の幅
	m_viewport.Height = (DWORD)0.0f;				//描画する画面の高さ
	m_bTurn = false;								//カメラが回転しているかどうか
	m_nNum = 0;										//cameraの個体識別番号
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CCamera::~CCamera()
{

}

//================================================
//初期化処理
//================================================
HRESULT CCamera::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float viewportX, float viewportY, float viewportWidth, float viewporHeight)
{
	m_rot = rot;																	//カメラの向き
	m_rotAsk = D3DXVECTOR3(0.0f, 0.0f, 0.0f);										//目的のカメラの向き
	m_posV = pos;																	//現在の視点
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);										//目的の視点
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);											//現在の注視点
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);										//目的の注視点
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);											//法線
	m_rotDiffer = 0.0f;																//目的と向きの差
	m_viewport.X = (DWORD)viewportX;												//描画する画面の左上X座標
	m_viewport.Y = (DWORD)viewportY;												//描画する画面の左上Y座標
	m_viewport.MinZ = 0.0f;															//描画するz座標の範囲の最小値
	m_viewport.MaxZ = 1.0f;															//描画するz座標の範囲の最大値
	m_viewport.Width = (DWORD)viewportWidth;										//描画する画面の幅
	m_viewport.Height = (DWORD)viewporHeight;										//描画する画面の高さ
	m_bTurn = false;																//カメラが回転しているかどうか


	return S_OK;
}

//================================================
//終了処理
//================================================
void CCamera::Uninit(void)
{
	
}

//================================================
//更新処理
//================================================
void CCamera::Update(void)
{
	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//パッド取得処理
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

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
			//プレイヤーのクラスにキャスト
			CPlayer *pPlayer = NULL;
			pPlayer = (CPlayer*)pObject;

			if (CManager::GetResult() != NULL)
			{
				if (pPlayer->GetNum() == CManager::GetPlayData()->GetWinNum())
				{
					//プレイヤーの位置取得
					D3DXVECTOR3 pos = pPlayer->GetPos();
					m_posR = D3DXVECTOR3(pos.x, pos.y + 50.0f, pos.z);
				}
			}
			else
			{
				//プレイヤーに追従させる
				D3DXVECTOR3 pos = pPlayer->GetPos();
				//個体識別番号が一致していたら
				if (m_nNum == pPlayer->GetNum())
				{
					m_posR = pos;
					//プレイヤーの移動量を加算
					D3DXVECTOR3 move = pPlayer->GetMove();
					m_posV.y += move.y;

					//================================================
					//右スティック処理
					//================================================
					if (pInputPadX->GetRightStick(CInputPadX::STICKTYPE_LEFT, m_nNum) == true && m_bTurn == false ||
						(pInputKeyboard->GetPress(DIK_LEFT) == true && m_nNum == 0))
					{
						m_rot.y -= CAMERA_R_SPEED;
						m_posV.x = m_posR.x + sinf(m_rot.y) * CAMERA_DISTANCE;
						m_posV.z = m_posR.z + cosf(m_rot.y) * CAMERA_DISTANCE;

					}
					else if (pInputPadX->GetRightStick(CInputPadX::STICKTYPE_RIGHT, m_nNum) == true && m_bTurn == false ||
						(pInputKeyboard->GetPress(DIK_RIGHT) == true && m_nNum == 0))
					{
						m_rot.y += CAMERA_R_SPEED;
						m_posV.x = m_posR.x + sinf(m_rot.y) * CAMERA_DISTANCE;
						m_posV.z = m_posR.z + cosf(m_rot.y) * CAMERA_DISTANCE;
					}
					if (pInputPadX->GetRightStick(CInputPadX::STICKTYPE_UP, m_nNum) == true && m_bTurn == false ||
						(pInputKeyboard->GetPress(DIK_UP) == true && m_nNum == 0))
					{
						m_posV.y += CAMERA_VR_SPEED;
						if (m_posV.y >= CAMERA_V_MAX_POS_Y)
						{
							m_posV.y = CAMERA_V_MAX_POS_Y;
						}
					}
					else if (pInputPadX->GetRightStick(CInputPadX::STICKTYPE_DOWN, m_nNum) == true && m_bTurn == false ||
						(pInputKeyboard->GetPress(DIK_DOWN) == true && m_nNum == 0))
					{
						m_posV.y -= CAMERA_VR_SPEED;
						if (m_posV.y <= CAMERA_V_MIN_POS_Y)
						{
							m_posV.y = CAMERA_V_MIN_POS_Y;
						}
					}
				}
			}
		}
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}

	//視点の場所を注視点を元に移動
	float fDistance = CAMERA_DISTANCE;

	if (CManager::GetResult() != NULL)
	{
		fDistance = CAMERA_RESULT_DISTANCE;
	}
	m_posV.x = m_posR.x + sinf(m_rot.y) * fDistance;
	m_posV.z = m_posR.z + cosf(m_rot.y) * fDistance;

	if (m_bTurn == true)
	{
		if (m_rotAsk.y > D3DX_PI)
		{
			m_rotAsk.y = -D3DX_PI - (D3DX_PI - m_rotAsk.y);
		}
		else if (m_rotAsk.y < -D3DX_PI)
		{
			m_rotAsk.y = D3DX_PI - (-D3DX_PI - m_rotAsk.y);
		}

		if (m_rot.y < 0.0f && -m_rot.y + m_rotAsk.y > D3DX_PI)
		{
			m_rotDiffer = (-D3DX_PI - m_rot.y) + -(D3DX_PI - m_rotAsk.y);
		}
		else if (m_rot.y >= D3DX_PI / 2.0f && m_rot.y - m_rotAsk.y > D3DX_PI)
		{
			m_rotDiffer = (D3DX_PI - m_rot.y) - (-D3DX_PI - m_rotAsk.y);
		}
		else
		{
			m_rotDiffer = (m_rotAsk.y - m_rot.y);
		}

		m_rot.y += m_rotDiffer * 0.1f;
	}

	if (m_rot.y >= D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
}

//================================================
//生成処理
//================================================
CCamera *CCamera::Create(D3DXVECTOR3 m_pos, D3DXVECTOR3 rot, float viewportX, float viewportY, float viewportWidth, float viewporHeight)
{
	//インスタンスの生成
	CCamera *pCamera = NULL;
	if (pCamera == NULL)
	{
		pCamera = new CCamera;
		if (pCamera != NULL)
		{
			pCamera->Init(m_pos, rot, viewportX, viewportY,viewportWidth, viewporHeight);
		}
	}
	return pCamera;
}


//=======================================================================
//設定処理
//=======================================================================
void CCamera::Set(void)
{
	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
								D3DXToRadian(50.0f),									//画角
								(float)m_viewport.Width / (float)m_viewport.Height,		//比率
								CAMERA_MIN_RENDERER,									//Z方向の描画範囲
								CAMERA_MAX_RENDERER);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//=======================================================================
//視点取得処理
//=======================================================================
D3DXVECTOR3 CCamera::GetPosV(void)
{
	return m_posV;
}

//=======================================================================
//注視点取得処理
//=======================================================================
D3DXVECTOR3 CCamera::GetPosR(void)
{
	return m_posR;
}

//=======================================================================
//視点設定処理
//=======================================================================
void CCamera::SetPosV(D3DXVECTOR3 pos)
{
	m_posV = pos;
}

//=======================================================================
//注視点設定処理
//=======================================================================
void CCamera::SetPosR(D3DXVECTOR3 pos)
{
	m_posR = pos;
}


//=======================================================================
//視点の向き取得処理
//=======================================================================
D3DXVECTOR3 CCamera::GetRotV(void)
{
	return m_rot;
}

//=======================================================================
//視点の向き設定処理
//=======================================================================
void CCamera::SetRotV(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=======================================================================
//cameraの個体識別番号設定処理
//=======================================================================
void CCamera::SetNum(int nNum)
{
	m_nNum = nNum;
}

//=======================================================================
//cameraの個体識別番号取得処理
//=======================================================================
int CCamera::GetNum(void)
{
	return m_nNum;
}