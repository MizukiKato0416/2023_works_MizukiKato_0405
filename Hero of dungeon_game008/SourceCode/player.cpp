//================================================
//プレイヤー処理
//Author:KatoMizuki
//================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_d.h"
#include "input_mouse.h"
#include "player.h"
#include "motion_player.h"
#include "renderer.h"
#include "model.h"
#include "x_load.h"
#include "floor.h"
#include "model_single.h"
#include "mesh_trajectory.h"
#include "texture.h"
#include "enemy_fat.h"
#include "camera.h"
#include "magic_thunder.h"
#include "magic_fire.h"
#include "play_data.h"
#include "gauge.h"
#include "meshfield.h"
#include "billboard.h"
#include "enemy.h"
#include "ui.h"
#include "shadow.h"
#include "sound.h"

//================================================
//マクロ定義
//================================================
#define PLAYER_JUMP							(7.0f)		//ジャンプ力
#define PLAYER_GRAVITY						(0.2f)		//重力の大きさ
#define PLAYER_MOVE_SPEED					(9.0f)		//通常移動の移動量
#define PLAYER_SLASH_MOVE_SPEED				(4.0f)		//斬撃時の移動の移動量
#define PLAYER_INVINCIBLE_COUNT				(30)		//無敵時間
#define PLAYER_SP_COST_MP					(400)		//SPを使用するのに必要なMP
#define PLAYER_MAGIC_FIRE_COST_MP			(100)		//炎魔法を使用するのに必要なMP
#define PLAYER_LOCK_ON_UI_SIZE				(100.0f)	//ロックオンUIのサイズ
#define PLAYER_LOCK_ON_UI_POS				(50.0f)		//ロックオンUIの位置調整値
#define PLAYER_SIZE							(10.0f)		//プレイヤーのサイズ調整値

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CPlayer::CPlayer(int nPriority):CObject(nPriority)
{
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pParent = nullptr;
	memset(&m_apModel, NULL, sizeof(m_apModel));
	m_pMotionPlayer = nullptr;
	m_pLockOn = nullptr;
	m_pEnemyNear = nullptr;
	m_fObjectiveRot = 0.0f;
	m_fLockOnObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_bRotate = false;
	m_bJump = false;
	m_bBurst = false;
	m_bSpecial = false;
	m_bLockOn = false;
	m_nCntBurst = 0;
	m_bGuard = false;
	m_state = PLAYER_STATE::NONE;
	m_nInvincibleCounter = 0;
	for (int nCntMeshTrajectory = 0; nCntMeshTrajectory < 2; nCntMeshTrajectory++)
	{
		m_pMeshTrajectory[nCntMeshTrajectory] = nullptr;
	}
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
	m_pos = pos;
	m_posOld = pos;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fLockOnObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_bRotate = false;
	m_bJump = false;
	m_bBurst = false;
	m_bSpecial = false;
	m_bLockOn = false;
	m_bGuard = false;
	m_nCntBurst = 0;
	m_state = PLAYER_STATE::NORMAL;
	m_nInvincibleCounter = 0;
	m_pLockOn = nullptr;
	m_pEnemyNear = nullptr;

	for (int nCntMeshTrajectory = 0; nCntMeshTrajectory < 2; nCntMeshTrajectory++)
	{
		m_pMeshTrajectory[nCntMeshTrajectory] = nullptr;
	}

	//モデルの生成
	//textファイル読み込み
	FILE *pFile = fopen("data/MOTION/motion_player.txt", "r");
	if (pFile != nullptr)
	{
		char cString[128];
		//一行ずつ保存
		while (fgets(cString, 128, pFile) != NULL)
		{
			//文字列を保存
			fscanf(pFile, "%s", cString);
			//文字列の中にPARTSSETがあったら
			if (strncmp("PARTSSET", cString, 9) == 0)
			{
				fscanf(pFile, "%*s%*s");

				//インデックス読み込み
				int nIndex = 0;
				fscanf(pFile, "%*s%*s%d", &nIndex);

				//親読み込み
				int nParent = 0;
				fscanf(pFile, "%*s%*s%d", &nParent);
				fscanf(pFile, "%*s%*s");

				//位置読み込み
				D3DXVECTOR3 modelPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				fscanf(pFile, "%*s%*s%f%f%f", &modelPos.x, &modelPos.y, &modelPos.z);

				//向き読み込み
				D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				fscanf(pFile, "%*s%*s%f%f%f", &rot.x, &rot.y, &rot.z);

				//モデル生成
				int nModelType = 0;
				nModelType = CXload::X_TYPE_PLAYER_BODY;
				m_apModel[nIndex] = CModel::Create(modelPos, rot, CManager::GetInstance()->GetXload()->GetType(nModelType + nIndex));

				//親の設定
				if (nParent == -1)
				{
					m_apModel[nIndex]->SetParent(nullptr);
				}
				else
				{
					m_apModel[nIndex]->SetParent(m_apModel[nParent]);
				}

				if (nIndex == MAX_PLAYER_MODEL - 1)
				{
					break;
				}
			}
		}
	}
	else
	{
		printf("ファイルが開けませんでした\n");
	}
	fclose(pFile);

	//位置の設定
	SetPos(m_pos);
	SetPosOld(m_posOld);

	//オブジェクトの種類の設定
	SetObjType(CObject::OBJTYPE::PLAYER);

	//モーションの生成
	m_pMotionPlayer = CMotionPlayer::Create(this);
	m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_NEUTRAL, this);

	//サイズを取得
	D3DXVECTOR3 modelSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	modelSize = m_apModel[0]->GetSize();

	//サイズのXとZを比べて大きいほうをXとZそれぞれに割り当てる
	if (modelSize.x >= modelSize.z)
	{
		m_size = D3DXVECTOR3(modelSize.x + PLAYER_SIZE, modelSize.y, modelSize.x + PLAYER_SIZE);
	}
	else
	{
		m_size = D3DXVECTOR3(modelSize.z + PLAYER_SIZE, modelSize.y, modelSize.z + PLAYER_SIZE);
	}

	//サイズの設定
	SetSize(m_size);

	//影の設定
	CShadow::Create(D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z), D3DXVECTOR3(m_size.x, 0.0f, m_size.z), this);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CPlayer::Uninit(void)
{
	Release();
}

//================================================
//更新処理
//================================================
void CPlayer::Update(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();

	m_pos = pos;
	m_posOld = pos;

	//1フレーム前の位置設定
	SetPosOld(m_posOld);

	//重力
	m_move.y -= PLAYER_GRAVITY;

	//ロックオン処理
	LockOn();

	//状態による処理分け
	State();

	m_pos += m_move;		//移動量反映

	//回転の慣性
	Rotate();

	//モーション
	m_pMotionPlayer->Update(this);

	//位置反映
	SetPos(m_pos);

	//床との当たり判定
	if (CFloor::Collision(this) == true)
	{
		m_bJump = false;
		m_move.y = 0.0f;
		//ジャンプ処理
		Jump();

		if (m_bJump == false)
		{
			m_move.y -= 40.0f;
		}
	}

	//モデルとの当たり判定
	if (CModelSingle::Collision(this) == true)
	{
		m_bJump = false;
		m_move.y = 0.0f;
		//ジャンプ処理
		Jump();

		if (m_bJump == false)
		{
			m_move.y -= 40.0f;
		}
	}

	//メッシュフィールドとの当たり判定
	//if (CMeshField::Collision(this, 100.0f) == true)
	//{
	//	m_bJump = false;
	//	m_move.y = 0.0f;
	//	//ジャンプ処理
	//	Jump();

	//	if (m_bJump == false)
	//	{
	//		m_move.y -= 40.0f;
	//	}
	//}

	//位置取得
	pos = GetPos();
	m_pos = pos;
}

//================================================
//描画処理
//================================================
void CPlayer::Draw(void)
{
	//位置取得処理
	D3DXVECTOR3 pos = GetPos();

	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

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
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//インスタンスの生成
	CPlayer *pPlayer = nullptr;
	if (pPlayer == nullptr)
	{
		pPlayer = new CPlayer;
		if (pPlayer != nullptr)
		{
			pPlayer->m_rot = rot;
			pPlayer->Init(pos, pPlayer->m_size);
		}
	}
	return pPlayer;
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
//モデルの動き処理
//================================================
void CPlayer::Move(void)
{
	//パッドD取得処理
	CInputPadD *pInputPadD = CManager::GetInstance()->GetInputPadD();
	DIJOYSTATE2 JoyStick = pInputPadD->GetGamepad();

	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//パッドX取得処理
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInstance()->GetInputPadX();

	D3DXVECTOR3 rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//cameraのポインタ配列1番目のアドレス取得
	CCamera **pCameraAddress = CManager::GetInstance()->GetCamera();

	for (int nCntCamera = 0; nCntCamera < MAX_MAIN_CAMERA; nCntCamera++, pCameraAddress++)
	{
		//cameraの取得
		CCamera *pCamera = &**pCameraAddress;
		if (pCamera != nullptr)
		{
			//cameraの向き取得
			rotCamera = pCamera->GetRotV();
		}
	}

	//移動量設定用変数
	float fSpeed = 0.0f;

	//連撃中じゃなかったら
	if (m_bBurst == false)
	{
		//通常の移動量にする
		fSpeed = PLAYER_MOVE_SPEED;
	}
	else
	{//連撃中なら
		//斬撃時の移動量にする
		fSpeed = PLAYER_SLASH_MOVE_SPEED;
	}

	//スティックの傾きがあったらまたはWASDを押したら
	if ((float)JoyStick.lX != 0.0f || (float)JoyStick.lY != 0.0f || 
		pInputKeyboard->GetPress(DIK_W) == true || pInputKeyboard->GetPress(DIK_A) == true ||
		pInputKeyboard->GetPress(DIK_S) == true || pInputKeyboard->GetPress(DIK_D) == true)
	{
		//目的の向きを設定
		if ((float)JoyStick.lX != 0.0f || (float)JoyStick.lY != 0.0f)
		{
			m_fObjectiveRot = rotCamera.y + atan2f((float)JoyStick.lY, (float)JoyStick.lX) + D3DX_PI / 2.0f;
		}
		else if (pInputKeyboard->GetPress(DIK_W) == true)
		{
			if (pInputKeyboard->GetPress(DIK_A) == true)
			{
				//目的の向きを設定
				m_fObjectiveRot = rotCamera.y - D3DX_PI / 4.0f;
			}
			else if (pInputKeyboard->GetPress(DIK_D) == true)
			{
				//目的の向きを設定
				m_fObjectiveRot = rotCamera.y + D3DX_PI / 4.0f;
			}
			else
			{
				//目的の向きを設定
				m_fObjectiveRot = rotCamera.y;
			}
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{
			if (pInputKeyboard->GetPress(DIK_A) == true)
			{
				//目的の向きを設定
				m_fObjectiveRot = rotCamera.y - D3DX_PI / 4.0f * 3.0f;
			}
			else if (pInputKeyboard->GetPress(DIK_D) == true)
			{
				//目的の向きを設定
				m_fObjectiveRot = rotCamera.y + D3DX_PI / 4.0f * 3.0f;
			}
			else
			{
				//目的の向きを設定
				m_fObjectiveRot = rotCamera.y + D3DX_PI;
			}
		}
		else if (pInputKeyboard->GetPress(DIK_A) == true)
		{
			//目的の向きを設定
			m_fObjectiveRot = rotCamera.y - D3DX_PI / 2.0f;
		}
		else if (pInputKeyboard->GetPress(DIK_D) == true)
		{
			//目的の向きを設定
			m_fObjectiveRot = rotCamera.y + D3DX_PI / 2.0f;
		}

		//移動量加算
		m_move.x = sinf(m_fObjectiveRot + D3DX_PI) * fSpeed;
		m_move.z = cosf(m_fObjectiveRot + D3DX_PI) * fSpeed;
		//回転をさせる
		m_bRotate = true;

		if (m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_SLASH_01 &&	//斬撃1モーションでない
			m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_SLASH_02 &&	//斬撃2モーションでない
			m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_SLASH_03 &&	//斬撃3モーションでない
			m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_SLASH_04 &&	//斬撃4モーションでない
			m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_SPECIAL &&	//必殺技モーションでない
			m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_MOVE)		//移動モーションでない
		{
			//移動モーションにする
			m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_MOVE, this);
		}
	}
	else
	{//スティックに傾きがなかったら

		//移動量をゼロにする
		m_move.x = 0.0f;
		m_move.z = 0.0f;

		//移動モーションだったら
		if (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_MOVE)
		{
			//ニュートラルモーションにする
			m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_NEUTRAL, this);
		}
	}
}

//================================================
//回転処理
//================================================
void CPlayer::Rotate(void)
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

		//プレイヤーの現在の向きごとにそれぞれ向きを変える量を計算
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

		//プレイヤーの向きに加算
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
//ジャンプ処理
//================================================
void CPlayer::Jump(void)
{
	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//パッドD取得処理
	CInputPadD *pInputPadD;
	pInputPadD = CManager::GetInstance()->GetInputPadD();

	if (pInputPadD->GetTrigger(CInputPadD::A) == true)	//Aボタンを押したときの処理
	{
		//移動量をジャンプ分加算
		m_move.y = PLAYER_JUMP;
		m_bJump = true;
	}
}

//================================================
//剣攻撃処理
//================================================
void CPlayer::Slash(void)
{
	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//パッドD取得処理
	CInputPadD *pInputPadD;
	pInputPadD = CManager::GetInstance()->GetInputPadD();

	//マウス取得処理
	CInputMouse *pInputMouse;
	pInputMouse = CManager::GetInstance()->GetInputMouse();

	//攻撃ボタンを押したときの処理
	if (pInputPadD->GetTrigger(CInputPadD::B) == true || pInputMouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
	{
		if (m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_GUARD &&	//ガードモーションではないとき
			m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_MAGIC_01 &&	//魔法モーションではないとき
			m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_SPECIAL)	//必殺技モーションではないとき
		{
			//攻撃モーション最大値よりも小さいとき
			if (m_nCntBurst <= CMotionRoad::MOTION_PLAYER_TYPE_SLASH_04 - CMotionRoad::MOTION_PLAYER_TYPE_SLASH_01)
			{
				//連撃中ではないとき
				if (m_bBurst == false)
				{
					//連撃数が0の時
					if (m_nCntBurst == 0)
					{
						//連撃数を加算
						m_nCntBurst++;
						//連撃状態にする
						m_bBurst = true;
						//斬撃モーションにする
						m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_SLASH_01 + m_nCntBurst - 1, this);

						if (m_nCntBurst == 1 || m_nCntBurst == 3)
						{
							//SE再生
							pSound->Play(CSound::SOUND_LABEL_SLASH_01_SE);
							//サウンドの音量調整
							pSound->ControllVoice(CSound::SOUND_LABEL_SLASH_01_SE, 1.5f);
						}
						else if (m_nCntBurst == 2 || m_nCntBurst == 4)
						{
							//SE再生
							pSound->Play(CSound::SOUND_LABEL_SLASH_02_SE);
							//サウンドの音量調整
							pSound->ControllVoice(CSound::SOUND_LABEL_SLASH_02_SE, 1.5f);
						}
						
					}
				}
				else
				{//連撃中の時
					//現在のモーションが次の攻撃モーションのひとつ前だったら
					if (m_pMotionPlayer->GetMotion() == m_nCntBurst + CMotionRoad::MOTION_PLAYER_TYPE_SLASH_01 - 1)
					{
						//連撃数を加算
						m_nCntBurst++;
					}
				}
			}
		}
	}

	//モーションが繋がっている状態でないとき
	if (m_pMotionPlayer->GetConnect() == false)
	{
		//斬撃モーションが終わったとき
		if ((m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_01 ||
			 m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_02 ||
			 m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_03 ||
			 m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_04) &&
			 m_pMotionPlayer->GetKey() == m_pMotionPlayer->GetKeyMax() - 2 &&
			 m_pMotionPlayer->GetFrame() == m_pMotionPlayer->GetFrameMax())
		{
			for (int nCntMeshTrajectory = 0; nCntMeshTrajectory < 2; nCntMeshTrajectory++)
			{
				if (m_pMeshTrajectory[nCntMeshTrajectory] != nullptr)
				{
					//剣の軌跡を破棄
					m_pMeshTrajectory[nCntMeshTrajectory]->Uninit();
					m_pMeshTrajectory[nCntMeshTrajectory] = nullptr;
				}
			}

			//連撃数が現在の斬撃モーションの次のモーションだったら
			if (m_nCntBurst + CMotionRoad::MOTION_PLAYER_TYPE_SLASH_01 - 1 == m_pMotionPlayer->GetMotion() + 1)
			{
				if (m_nCntBurst == 1 || m_nCntBurst == 3)
				{
					//SE再生
					pSound->Play(CSound::SOUND_LABEL_SLASH_01_SE);
					//サウンドの音量調整
					pSound->ControllVoice(CSound::SOUND_LABEL_SLASH_01_SE, 1.5f);
				}
				else if (m_nCntBurst == 2 || m_nCntBurst == 4)
				{
					//SE再生
					pSound->Play(CSound::SOUND_LABEL_SLASH_02_SE);
					//サウンドの音量調整
					pSound->ControllVoice(CSound::SOUND_LABEL_SLASH_02_SE, 1.5f);
				}

				//次の斬撃モーションに設定
				m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_SLASH_01 + m_nCntBurst - 1, this);
				//モーションをつなぐときのフレーム数を設定
				m_pMotionPlayer->SetFrameMax(1);
			}
			else
			{//連撃数が現在の斬撃モーションの次のモーションじゃなかったら
				if(m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_SLASH_04)
				{
					//連撃状態でなくする
					m_bBurst = false;
					//連撃数を0にする
					m_nCntBurst = 0;
					m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_NEUTRAL, this);
					//モーションをつなぐときのフレーム数を設定
					m_pMotionPlayer->SetFrameMax(20);
				}
			}
		}
	}

	//モーションが繋がっている状態じゃなくてモーションが移動かニュートラルの時
	if (m_pMotionPlayer->GetConnect() == false &&
		(m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_NEUTRAL ||
		 m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_MOVE))
	{
		//連撃状態でなくする
		m_bBurst = false;
		//連撃数を0にする
		m_nCntBurst = 0;
	}
	

	if (((m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_01 && m_pMotionPlayer->GetKey() == 1) ||
		 (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_02 && m_pMotionPlayer->GetKey() == 1) ||
		 (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_03 && m_pMotionPlayer->GetKey() == 1) ||
		 (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_04 && m_pMotionPlayer->GetKey() == 1)) &&
		  m_pMotionPlayer->GetFrame() == 0)
	{
		//剣の軌跡が生成されていなかったら
		if (m_pMeshTrajectory[0] == nullptr)
		{
			//剣の軌跡を生成
			m_pMeshTrajectory[0] = CMeshTrajectory::Create(14, m_apModel[15]->GetMtxPoint(), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, -44.0f),
														D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			m_pMeshTrajectory[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_MESH_TRAJECTORY_01"));
		}
		if (m_pMeshTrajectory[1] == nullptr)
		{
			//剣の軌跡を生成
			m_pMeshTrajectory[1] = CMeshTrajectory::Create(18, m_apModel[15]->GetMtxPoint(), D3DXVECTOR3(-2.0f, 0.0f, -20.0f), D3DXVECTOR3(-2.0f, 0.0f, -94.0f),
														D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			m_pMeshTrajectory[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_MESH_TRAJECTORY_02"));
		}
	}

	//攻撃1、2、3は攻撃モーションが始まった瞬間、攻撃4はキーが4になったとき
	if (((m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_01 ||
		  m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_02 ||
		  m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_03) &&
		  m_pMotionPlayer->GetKey() == 0 && m_pMotionPlayer->GetFrame() == 0) || 
		 (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_04 &&
		  m_pMotionPlayer->GetKey() == 4 && m_pMotionPlayer->GetFrame() == 0))
	{
		//移動できるようにする
		Move();
	}


	//攻撃1の時はキーが3以降は移動できないようにする
	//攻撃2の時はキーが2以降は移動できないようにする
	//攻撃3の時は移動できないようにする
	//攻撃4の時はキーが7以降は移動できないようにする
	if ((m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_01 &&
		m_pMotionPlayer->GetKey() == 3 && m_pMotionPlayer->GetFrame() == 0) ||
		(m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_02 &&
		m_pMotionPlayer->GetKey() == 2 && m_pMotionPlayer->GetFrame() == 0) ||
		(m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_03 &&
		m_pMotionPlayer->GetKey() == 0 && m_pMotionPlayer->GetFrame() == 0 ||
		(m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SLASH_04 &&
		m_pMotionPlayer->GetKey() == 7 && m_pMotionPlayer->GetFrame() == 0)))
	{
		//移動量を0にする
		m_move.x = 0.0f;
		m_move.z = 0.0f;
	}
}

//================================================
//必殺技処理
//================================================
void CPlayer::Special(void)
{
	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	//パッドD取得処理
	CInputPadD *pInputPadD;
	pInputPadD = CManager::GetInstance()->GetInputPadD();

	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//カメラのポインタ配列1番目のアドレス取得
	CCamera** pCameraAddress = CManager::GetInstance()->GetCamera();
	//cameraの取得
	CCamera* pCamera = &**pCameraAddress;

	//R2L2同時にボタンを押したときまたはSPACEキーを押したときの処理
	if (((pInputPadD->GetPress(CInputPadD::R2) == true && pInputPadD->GetTrigger(CInputPadD::L2) == true) ||
		(pInputPadD->GetTrigger(CInputPadD::R2) == true && pInputPadD->GetPress(CInputPadD::L2) == true)) ||
		 pInputKeyboard->GetTrigger(DIK_SPACE) == true)
	{
		//SPゲージがMAXの時且つMPゲージが既定の値以上あるとき
		if (CManager::GetInstance()->GetPlayData()->GetSpGauge()->GetGauge() == CManager::GetInstance()->GetPlayData()->GetSpGauge()->GetMaxNum() &&
			CManager::GetInstance()->GetPlayData()->GetMpGauge()->GetGauge() >= PLAYER_SP_COST_MP)
		{
			if (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_NEUTRAL ||	//ニュートラルモーションの時
				m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_MOVE)		//移動モーションの時
			{
				//必殺技モーションにする
				m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_SPECIAL, this);
				//カメラの状態を小さい揺れにする
				pCamera->SetState(CCamera::CAMERA_STATE::SWAY_SMALL);
				//無敵状態にする
				m_state = PLAYER_STATE::INVINCIBLE;
				//移動量を0にする
				m_move.x = 0.0f;
				m_move.z = 0.0f;
				//SPゲージを0にする
				CManager::GetInstance()->GetPlayData()->GetSpGauge()->SetGauge(0);
				//MPゲージを減らす
				CManager::GetInstance()->GetPlayData()->GetMpGauge()->AddGauge(-PLAYER_SP_COST_MP);
				//必殺技をしている状態にする
				m_bSpecial = true;

				//SE再生
				pSound->Play(CSound::SOUND_LABEL_MAGIC_CIRCLE_SE);
				//サウンドの音量調整
				pSound->ControllVoice(CSound::SOUND_LABEL_MAGIC_CIRCLE_SE, 1.8f);

				//SE再生
				pSound->Play(CSound::SOUND_LABEL_EARTH_QUAKE_01_SE);
				//サウンドの音量調整
				pSound->ControllVoice(CSound::SOUND_LABEL_EARTH_QUAKE_01_SE, 2.8f);
			}
		}

		//SPが足りないとき
		if (CManager::GetInstance()->GetPlayData()->GetSpGauge()->GetGauge() != CManager::GetInstance()->GetPlayData()->GetSpGauge()->GetMaxNum())
		{
			//UIを出す
			CUi::Create(D3DXVECTOR3(GAUGE_SP_POS_X, GAUGE_SP_POS_Y, 0.0f), D3DXVECTOR3(UI_CROSS_SIZE, UI_CROSS_SIZE, 0.0f),
				        PRIORITY_UI, CUi::TYPE::CROSS);
			//SE再生
			pSound->Play(CSound::SOUND_LABEL_POOR_SE);
			//サウンドの音量調整
			pSound->ControllVoice(CSound::SOUND_LABEL_POOR_SE, 1.4f);
		}
		//MPが足りないとき
		if (CManager::GetInstance()->GetPlayData()->GetMpGauge()->GetGauge() < PLAYER_SP_COST_MP)
		{
			//UIを出す
			CUi::Create(D3DXVECTOR3(GAUGE_MP_POS_X, GAUGE_MP_POS_Y, 0.0f), D3DXVECTOR3(UI_CROSS_SIZE, UI_CROSS_SIZE, 0.0f),
				        PRIORITY_UI, CUi::TYPE::CROSS);
			//SE再生
			pSound->Play(CSound::SOUND_LABEL_POOR_SE);
			//サウンドの音量調整
			pSound->ControllVoice(CSound::SOUND_LABEL_POOR_SE, 1.4f);
		}
	}

	//必殺技モーションの時
	if (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_SPECIAL && m_pMotionPlayer->GetConnect() == false)
	{
		//キーが0の時
		if (m_pMotionPlayer->GetKey() == 0)
		{
			//空を飛ばせる
			m_move.y = 3.0f;
			//既定の値以上になったら
			if (pCamera->GetDiffer() > CAMERA_DISTANCE_SPECIAL)
			{
				pCamera->SetDiffer(CAMERA_DISTANCE_SPECIAL);
			}
			else
			{//既定の値よりも小さいとき
				//カメラを引いていく
				pCamera->AddDiffer(4.0f);
			}
		}
		else if (m_pMotionPlayer->GetKey() < 5)
		{//キーが5より小さいとき
			//止める
			m_move.y = 0.0f;
		}
		else if (m_pMotionPlayer->GetKey() >= 5)
		{//キーが5以上の時
			//既定の値以下になったら
			if (pCamera->GetDiffer() <= CAMERA_DISTANCE)
			{
				pCamera->SetDiffer(CAMERA_DISTANCE);
			}
			else
			{//既定の値よりも大きいとき
			 //カメラを寄せる
				pCamera->AddDiffer(-6.0f);
			}
		}

		//キーが1になった瞬間
		if (m_pMotionPlayer->GetKey() == 1 && m_pMotionPlayer->GetFrame() == 0 && m_pMotionPlayer->GetConnect() == false)
		{
			//雷魔法を出す
			CMagicThunder::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 150.0f, m_pos.z));

			//SE再生
			pSound->Play(CSound::SOUND_LABEL_THUNDER_01_SE);
			//サウンドの音量調整
			pSound->ControllVoice(CSound::SOUND_LABEL_THUNDER_01_SE, 1.5f);
		}
		else if (m_pMotionPlayer->GetKey() == 2 && m_pMotionPlayer->GetFrame() == 0)
		{//キーが2になった瞬間
			//カメラの状態を大きい揺れにする
			pCamera->SetState(CCamera::CAMERA_STATE::SWAY_LARGE);

			//SE再生
			pSound->Play(CSound::SOUND_LABEL_EARTH_QUAKE_02_SE);
			//サウンドの音量調整
			pSound->ControllVoice(CSound::SOUND_LABEL_EARTH_QUAKE_02_SE, 1.5f);
		}
		else if (m_pMotionPlayer->GetKey() == 3 && m_pMotionPlayer->GetFrame() == 0)
		{//キーが2になった瞬間
		 //カメラの状態を大きい揺れにする
			pCamera->SetState(CCamera::CAMERA_STATE::SWAY_LARGE);

			//SE再生
			pSound->Play(CSound::SOUND_LABEL_THUNDER_02_SE);
			//サウンドの音量調整
			pSound->ControllVoice(CSound::SOUND_LABEL_THUNDER_02_SE, 1.5f);
		}
		else if(m_pMotionPlayer->GetKey() == 5 && m_pMotionPlayer->GetFrame() == 0)
		{//キーが5になった瞬間
			//カメラの状態を通常にする
			pCamera->SetState(CCamera::CAMERA_STATE::NORMAL);
			//通常状態にする
			m_state = PLAYER_STATE::NORMAL;
			//必殺技をしていない状態にする
			m_bSpecial = false;
		}
	}
}

//================================================
//魔法攻撃処理
//================================================
void CPlayer::Magic(void)
{
	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	//パッドD取得処理
	CInputPadD *pInputPadD;
	pInputPadD = CManager::GetInstance()->GetInputPadD();

	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//Yボタンを押したときまたはQキーを押したときの処理
	if (pInputPadD->GetTrigger(CInputPadD::Y) == true || pInputKeyboard->GetTrigger(DIK_Q) == true)
	{
		//MPゲージが既定の値以上あるとき
		if (CManager::GetInstance()->GetPlayData()->GetMpGauge()->GetGauge() >= PLAYER_MAGIC_FIRE_COST_MP)
		{

			if (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_NEUTRAL ||	//ニュートラルモーションの時
				m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_MOVE)		//移動モーションの時
			{
				//魔法攻撃1モーションにする
				m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_MAGIC_01, this);
				//移動量を0にする
				m_move.x = 0.0f;
				m_move.z = 0.0f;
				//MPゲージを減らす
				CManager::GetInstance()->GetPlayData()->GetMpGauge()->AddGauge(-PLAYER_MAGIC_FIRE_COST_MP);
			}
		}
		else
		{//MPが足りないとき
			//SE再生
			pSound->Play(CSound::SOUND_LABEL_POOR_SE);
			//サウンドの音量調整
			pSound->ControllVoice(CSound::SOUND_LABEL_POOR_SE, 1.4f);

			//UIを出す
			CUi::Create(D3DXVECTOR3(GAUGE_MP_POS_X, GAUGE_MP_POS_Y, 0.0f), D3DXVECTOR3(UI_CROSS_SIZE, UI_CROSS_SIZE, 0.0f),
				        PRIORITY_UI, CUi::TYPE::CROSS);
		}
	}

	//魔法攻撃1モーションの時
	if (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_MAGIC_01 && m_pMotionPlayer->GetConnect() == false)
	{
		//キーが1になった瞬間
		if (m_pMotionPlayer->GetKey() == 1 && m_pMotionPlayer->GetFrame() == 0 && m_pMotionPlayer->GetConnect() == false)
		{
			//炎魔法を出す
			CMagicFire::Create(D3DXVECTOR3(m_pos.x + sinf(m_rot.y - D3DX_PI) * PLAYER_MAGIC_01_POS,
				                           m_pos.y + PLAYER_MAGIC_01_POS_Y,
				                           m_pos.z + cosf(m_rot.y - D3DX_PI) * PLAYER_MAGIC_01_POS), m_rot);
		}
	}
}

//================================================
//ガード処理
//================================================
void CPlayer::Guard(void)
{
	//パッドD取得処理
	CInputPadD *pInputPadD;
	pInputPadD = CManager::GetInstance()->GetInputPadD();

	//マウス取得処理
	CInputMouse *pInputMouse;
	pInputMouse = CManager::GetInstance()->GetInputMouse();

	//Lボタンを押したときまたは左クリックをしたときの処理
	if (pInputPadD->GetPress(CInputPadD::L) == true || pInputMouse->GetPress(CInputMouse::MOUSE_TYPE_RIGHT) == true)
	{
		if (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_NEUTRAL ||	//ニュートラルモーションの時
			m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_MOVE)		//移動モーションの時
		{
			//ガードモーションじゃなかったら
			if (m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_GUARD)
			{
				//ガードモーションにする
				m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_GUARD, this);

				//ガードしていない状態なら
				if (m_bGuard == false)
				{
					//ガードしている状態にする
					m_bGuard = true;
				}
			}
			//移動量を0にする
			m_move.x = 0.0f;
			m_move.z = 0.0f;
		}
	}
	else
	{
		//ガードモーションだったら
		if (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_GUARD)
		{
			//ニュートラルモーションにする
			m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_NEUTRAL, this);
			//通常状態にする
			m_state = PLAYER_STATE::NORMAL;
			//ガードしていない状態にする
			m_bGuard = false;
		}
	}
}

//================================================
//状態による処理分け
//================================================
void CPlayer::State(void)
{
	//現在の状態によって処理を分ける
	switch (m_state)
	{
	case PLAYER_STATE::NORMAL:			//通常
		//剣攻撃処理
		Slash();

		//必殺技処理
		Special();

		//魔法攻撃処理
		Magic();

		//ガード処理
		Guard();

		if (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_NEUTRAL ||	//ニュートラルモーションの時
			m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_MOVE)		//移動モーションの時
		{
			//移動処理
			Move();
		}

		break;
	case PLAYER_STATE::DAMAGE:			//ダメージ
		//カウンターを加算
		m_nInvincibleCounter++;
		//規定値以上になったら
		if (m_nInvincibleCounter >= PLAYER_INVINCIBLE_COUNT)
		{
			//0にする
			m_nInvincibleCounter = 0;
			//通常状態にする
			m_state = PLAYER_STATE::NORMAL;
		}

		//剣攻撃処理
		Slash();

		//必殺技処理
		Special();

		//魔法攻撃処理
		Magic();

		//ガード処理
		Guard();

		if (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_NEUTRAL ||	//ニュートラルモーションの時
			m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_MOVE)		//移動モーションの時
		{
			//移動処理
			Move();
		}
		break;
	case PLAYER_STATE::INVINCIBLE:		//無敵
		//剣攻撃処理
		Slash();

		//必殺技処理
		Special();

		//魔法攻撃処理
		Magic();

		//ガード処理
		Guard();

		if (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_NEUTRAL ||	//ニュートラルモーションの時
			m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_MOVE)		//移動モーションの時
		{
			//移動処理
			Move();
		}
		break;
	default:
		break;
	}
}

//================================================
//ロックオン処理
//================================================
void CPlayer::LockOn(void)
{
	//パッドD取得処理
	CInputPadD *pInputPadD;
	pInputPadD = CManager::GetInstance()->GetInputPadD();

	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//RボタンまたはRキーを押したときの処理
	if (pInputPadD->GetTrigger(CInputPadD::R) == true || pInputKeyboard->GetTrigger(DIK_R) == true)
	{
		//ロックオン状態でないとき
		if (m_bLockOn == false)
		{
			//オブジェクト情報を入れるポインタ
			CObject *pObject = nullptr;
			//オブジェクト情報を保存するポインタ変数
			CObject *pSaveObject = nullptr;

			//先頭のポインタを代入
			pObject = pObject->GetTopObj(CObject::PRIORITY_ENEMY);

			//プレイヤーとの距離保存用
			float fDiffer = 100000.0f;

			while (pObject != nullptr)
			{
				//現在のオブジェクトのポインタを保存
				pSaveObject = pObject;

				//オブジェクトの種類が敵だったら
				if (pObject->GetObjType() == CObject::OBJTYPE::ENEMY_FAT ||
					pObject->GetObjType() == CObject::OBJTYPE::ENEMY_BEE ||
					pObject->GetObjType() == CObject::OBJTYPE::ENEMY_BOSS)
				{
					//敵にキャスト
					CEnemy *pEnemyObj = nullptr;
					pEnemyObj = (CEnemy*)pObject;

					//敵が描画されている状態だったら
					if (pEnemyObj->GetDraw() == true)
					{
						//オブジェクトの位置を取得
						D3DXVECTOR3 posObj = pEnemyObj->GetPos();

						//自身から対象のオブジェクトまでの距離を求める
						float fRadius = sqrtf((m_pos.x - posObj.x) * (m_pos.x - posObj.x) +
							                  (m_pos.z - posObj.z) * (m_pos.z - posObj.z));

						//距離を比較して保存してあるものより小さかったら
						if (fRadius < fDiffer)
						{
							//上書きする
							fDiffer = fRadius;
							//ポインタを保存
							m_pEnemyNear = pEnemyObj;
						}
					}
				}
				//次のオブジェクトに進める
				pObject = pSaveObject->GetObjNext(pSaveObject);
			}

			if (m_pEnemyNear != nullptr)
			{
				//ロックオン状態にする
				m_bLockOn = true;

				//一番近くの敵の位置取得
				D3DXVECTOR3 posEnemy = m_pEnemyNear->GetPos();
				//プレイヤーとの角度を求める
				m_fLockOnObjectiveRot = atan2((posEnemy.x - m_pos.x), (posEnemy.z - m_pos.z)) - D3DX_PI;
				if (m_pLockOn == nullptr)
				{
					//ロックオンUIを出す
					m_pLockOn = CBillboard::Create(D3DXVECTOR3(posEnemy.x + sinf(m_fLockOnObjectiveRot) * PLAYER_LOCK_ON_UI_POS,
						                                       posEnemy.y + PLAYER_LOCK_ON_UI_POS,
						                                       posEnemy.z + cosf(m_fLockOnObjectiveRot) * PLAYER_LOCK_ON_UI_POS),
						                           D3DXVECTOR3(PLAYER_LOCK_ON_UI_SIZE, PLAYER_LOCK_ON_UI_SIZE, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					//テクスチャを設定
					m_pLockOn->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_LOCK_ON"));
					//プライオリティを設定
					m_pLockOn->SetPriority(CObject::PRIORITY_LOCK_ON);
					//αテストを行う設定
					m_pLockOn->SetAlphaTest(true);
					//ライティングを無効にする
					m_pLockOn->SetLighting(false);
				}
			}
		}
		else
		{//ロックオン状態の時
			//カメラのポインタ配列1番目のアドレス取得
			CCamera** pCameraAddress = CManager::GetInstance()->GetCamera();
			//cameraの取得
			CCamera* pCamera = &**pCameraAddress;

			//ロックオン解除する
			m_bLockOn = false;

			//UIを消す
			if (m_pLockOn != nullptr)
			{
				m_pLockOn->Uninit();
				m_pLockOn = nullptr;
			}

			//回転を止める
			m_bRotate = false;
			//カメラの回転を止める
			pCamera->SetRotateX(false);
			pCamera->SetRotateY(false);

			//nullptrにする
			m_pEnemyNear = nullptr;
		}
	}

	//ロックオン状態のとき
	if (m_bLockOn == true)
	{
		if (m_pEnemyNear != nullptr)
		{
			//カメラのポインタ配列1番目のアドレス取得
			CCamera** pCameraAddress = CManager::GetInstance()->GetCamera();
			//cameraの取得
			CCamera* pCamera = &**pCameraAddress;

			//一番近くの敵の位置取得
			D3DXVECTOR3 posEnemy = m_pEnemyNear->GetPos();
			//プレイヤーとの角度を求める
			m_fLockOnObjectiveRot = atan2((posEnemy.x - m_pos.x), (posEnemy.z - m_pos.z)) - D3DX_PI;
			//プレイヤーの目的の向きを設定
			m_fObjectiveRot = m_fLockOnObjectiveRot;
			//回転をさせる
			m_bRotate = true;
			//カメラの目的の向きを設定
			pCamera->SetRotAsk(D3DXVECTOR3(CAMERA_ROCK_ON_ROT_X, m_fLockOnObjectiveRot, 0.0f));
			//回転させる
			pCamera->SetRotateX(true);
			pCamera->SetRotateY(true);

			//ロックオンUIの位置とサイズ取得
			D3DXVECTOR3 posLockOn = m_pLockOn->GetPos();
			D3DXVECTOR3 sizeLockOn = m_pLockOn->GetSize();
			posLockOn = D3DXVECTOR3(posEnemy.x + sinf(m_fLockOnObjectiveRot) * PLAYER_LOCK_ON_UI_POS,
				                    posEnemy.y + PLAYER_LOCK_ON_UI_POS,
				                    posEnemy.z + cosf(m_fLockOnObjectiveRot) * PLAYER_LOCK_ON_UI_POS);
			//位置設定
			m_pLockOn->SetPos(posLockOn, sizeLockOn);
		}
		else
		{
			//カメラのポインタ配列1番目のアドレス取得
			CCamera** pCameraAddress = CManager::GetInstance()->GetCamera();
			//cameraの取得
			CCamera* pCamera = &**pCameraAddress;

			//ロックオン解除する
			m_bLockOn = false;

			//UIを消す
			if (m_pLockOn != nullptr)
			{
				m_pLockOn->Uninit();
				m_pLockOn = nullptr;
			}

			//回転を止める
			m_bRotate = false;
			//カメラの回転を止める
			pCamera->SetRotateX(false);
			pCamera->SetRotateY(false);
		}
	}
}

//================================================
//プレイヤーとの当たり判定
//================================================
void CPlayer::Collision(CObject *pSubjectObject, float fObjRadius)
{
	//オブジェクト情報を入れるポインタ
	CObject *pObject = nullptr;
	//オブジェクト情報を保存するポインタ変数
	CObject *pSaveObject = nullptr;

	//先頭のポインタを代入
	pObject = pObject->GetTopObj(CObject::PRIORITY_PLAYER);

	while (pObject != nullptr)
	{
		//現在のオブジェクトのポインタを保存
		pSaveObject = pObject;

		//オブジェクトの種類がプレイヤーだったら
		if (pObject->GetObjType() == CObject::OBJTYPE::PLAYER)
		{
			//プレイヤーにキャスト
			CPlayer *pPlayerObj = nullptr;
			pPlayerObj = (CPlayer*)pObject;

			//必殺技をしていないとき
			if (pPlayerObj->m_bSpecial == false)
			{
				//オブジェクトの位置を取得
				D3DXVECTOR3 posObj = pSubjectObject->GetPos();

				//プレイヤーから対象のオブジェクトまでの距離を求める
				float fRadius = sqrtf((posObj.x - pPlayerObj->m_pos.x) * (posObj.x - pPlayerObj->m_pos.x) +
					                  (posObj.z - pPlayerObj->m_pos.z) * (posObj.z - pPlayerObj->m_pos.z));
				//プレイヤーと対象のオブジェクトの角度を求める
				float fRot = atan2((posObj.x - pPlayerObj->m_pos.x), (posObj.z - pPlayerObj->m_pos.z)) - D3DX_PI;

				//求めた距離がプレイヤーの半径と対象のオブジェクトの半径を足した数値以下だったら
				if (fRadius <= pPlayerObj->m_size.x / 2.0f + fObjRadius)
				{
					//プレイヤーの位置を押し出す
					pPlayerObj->m_pos.x = posObj.x + (sinf(fRot) * (pPlayerObj->m_size.x / 2.0f + fObjRadius));
					pPlayerObj->m_pos.z = posObj.z + (cosf(fRot) * (pPlayerObj->m_size.x / 2.0f + fObjRadius));

					//位置設定
					pPlayerObj->SetPos(pPlayerObj->m_pos);

					//モデルとの当たり判定
					CModelSingle::Collision(pPlayerObj);
				}
			}
		}
		//次のオブジェクトに進める
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}

//================================================
//プレイヤーとの衝突判定のみの処理
//================================================
bool CPlayer::CollisionOnly(CObject * pSubjectObject, float fObjRadius)
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
