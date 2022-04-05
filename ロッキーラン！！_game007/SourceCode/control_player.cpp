//=============================================================================
// コントロールプレイヤー処理 [control_player.cpp]
// Author : 加藤瑞葵
//=============================================================================
#include "control_player.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "player.h"
#include "camera.h"
#include "game01.h"
#include "2Danimation_jump.h"
#include "motion_player.h"
#include "sound.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CControlPlayer::CControlPlayer()
{
	m_speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_bRotate = false;
	m_nDiveTime = 0;
	m_bStop = false;
	m_bDive = false;
	m_bJump = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CControlPlayer::~CControlPlayer()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CControlPlayer::Init(void)
{
	m_speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_bRotate = false;
	m_nDiveTime = 0;
	m_bStop = false;
	m_bDive = false;
	m_bJump = false;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CControlPlayer::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CControlPlayer::Update(CScene *pScene)
{
	//引数のポインタをUiクラスのポインタにキャスト
	CPlayer *pPlayer = NULL;
	pPlayer = (CPlayer*)pScene;

	//ゲーム中の時
	if (CManager::GetGame01() != NULL)
	{
		//ゲームスタート状態でなかったら
		if (CManager::GetGame01()->GetGame() == false)
		{
			//動かない状態にする
			m_bStop = true;
		}
		else
		{
			//動けるようにする
			m_bStop = false;
		}
	}
	else if (CManager::GetResult() != NULL)
	{
		//動かない状態にする
		m_bStop = true;
	}

	//モーション取得処理
	CMotionPlayer *pMotionPlayer = NULL;
	pMotionPlayer = pPlayer->GetMotionPlayer();

	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//パッド取得処理
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	D3DXVECTOR3 rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//cameraのポインタ配列1番目のアドレス取得
	CCamera **pCameraAddress = CManager::GetCamera();

	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++, pCameraAddress++)
	{
		//cameraの取得
		CCamera *pCamera = &**pCameraAddress;
		if (pCamera != NULL)
		{
			if (pPlayer->GetNum() == pCamera->GetNum())
			{
				//cameraの向き取得
				rotCamera = pCamera->GetRotV();
			}
		}
	}
	m_move = pPlayer->GetMove();
	m_moveOld = m_move;

	//重力
	m_move.y -= PLAYER_GRAVITY;

	//カウントダウン中は動けなくする
	if (m_bStop == false)
	{
		//移動処理
		Move(pPlayer);
	}

	//移動の慣性についての処理
	MoveInteria(pPlayer);

	//今のフレーム止まっているとき且つ移動モーション且つモーションをつなげていなかったら
	if (m_move.x == 0.0f && m_move.z == 0.0f &&
		pPlayer->GetMotionPlayer()->GetMotion() == CMotionPlayer::MOTION_PLAYER_TYPE_MOVE &&
		pPlayer->GetMotionPlayer()->GetConnect() == false)
	{
		//ニュートラルモーションにする
		pPlayer->GetMotionPlayer()->SetMotion(CMotionPlayer::MOTION_PLAYER_TYPE_NEUTRAL);
	}

	//前のフレーム止まっていて今動いているとき且つジャンプモーションじゃない且つダイブモーションでないとき
	if (((m_moveOld.x == 0.0f && m_move.x != 0.0f) || (m_moveOld.z == 0.0f && m_move.z != 0.0f)) &&
		pPlayer->GetMotionPlayer()->GetMotion() != CMotionPlayer::MOTION_PLAYER_TYPE_JUMP &&
		pPlayer->GetMotionPlayer()->GetMotion() != CMotionPlayer::MOTION_PLAYER_TYPE_DIVE)
	{
		//移動モーションにする
		pPlayer->GetMotionPlayer()->SetMotion(CMotionPlayer::MOTION_PLAYER_TYPE_MOVE);
	}

	//ダイブの処理
	Dive(pPlayer);

	//回転の慣性
	Rotate(pPlayer);

	//ジャンプ処理
	Jump(pPlayer);
}

//================================================
//生成処理
//================================================
CControlPlayer *CControlPlayer::Create(void)
{
	//インスタンスの生成
	CControlPlayer *pControlPlayer = NULL;
	if (pControlPlayer == NULL)
	{
		pControlPlayer = new CControlPlayer;
		if (pControlPlayer != NULL)
		{

			pControlPlayer->Init();
		}
	}
	return pControlPlayer;
}

//================================================
//移動処理
//================================================
void CControlPlayer::Move(CPlayer *pPlayer)
{
	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//パッド取得処理
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	D3DXVECTOR3 rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//cameraのポインタ配列1番目のアドレス取得
	CCamera **pCameraAddress = CManager::GetCamera();

	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++, pCameraAddress++)
	{
		//cameraの取得
		CCamera *pCamera = &**pCameraAddress;
		if (pCamera != NULL)
		{
			if (pPlayer->GetNum() == pCamera->GetNum())
			{
				//cameraの向き取得
				rotCamera = pCamera->GetRotV();
			}
		}
	}

	//プレイヤーの個体識別番号取得処理
	int nNumPlayer = pPlayer->GetNum();

	//通常移動の加速度
	float fSpeed;

	//氷の上に乗ったら
	if (pPlayer->GetOnIce() == true)
	{
		fSpeed = PLAYER_MOVE_SPEED_ON_ICE;

		if (pPlayer->GetDive() == true)
		{
			//ダイブ中の加速度
			fSpeed = PLAYER_DIVE_SPEED_ON_ICE;
		}

	}
	//それ以外は通常のスピードや慣性に戻す
	else
	{
		fSpeed = PLAYER_MOVE_SPEED;

		if (pPlayer->GetDive() == true)
		{
			//ダイブ中の加速度
			fSpeed = PLAYER_DIVE_SPEED;
		}
	}

	//ダイブ着地モーション中じゃなかったら
	if (pPlayer->GetMotionPlayer()->GetMotion() != CMotionPlayer::MOTION_PLAYER_TYPE_DIVE_LAND)
	{
		//***********************************************************************
		// 移動
		//***********************************************************************
		if (pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_UP, nNumPlayer) == true ||
			(pInputKeyboard->GetPress(DIK_W) == true && nNumPlayer == 0))								
		{//左スティックを上に倒したときまたはwを押したときの処理
			if (pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_LEFT, nNumPlayer) == true ||
				(pInputKeyboard->GetPress(DIK_A) == true && nNumPlayer == 0))
			{//左スティックを左に倒したときまたはaを押したときの処理の処理
				//移動量加算
				m_move.x += +cosf(rotCamera.y + D3DX_PI / 4.0f) * fSpeed;
				m_move.z += -sinf(rotCamera.y + D3DX_PI / 4.0f) * fSpeed;

				//目的の向きを設定
				m_fObjectiveRot = rotCamera.y - D3DX_PI / 4.0f;
				//回転の慣性をオンにする
				m_bRotate = true;
			}
			else if (pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_RIGHT, nNumPlayer) == true ||
				(pInputKeyboard->GetPress(DIK_D) == true && nNumPlayer == 0))
			{//左スティックを右に倒したときまたはdを押したときの処理の処理
				//移動量加算
				m_move.x += -cosf(rotCamera.y - D3DX_PI / 4.0f) * fSpeed;
				m_move.z += +sinf(rotCamera.y - D3DX_PI / 4.0f) * fSpeed;

				//目的の向きを設定
				m_fObjectiveRot = rotCamera.y + D3DX_PI / 4.0f;
				//回転の慣性をオンにする
				m_bRotate = true;
			}
			else
			{
				//移動量加算
				m_move.z += -cosf(rotCamera.y) * fSpeed;
				m_move.x += -sinf(rotCamera.y) * fSpeed;

				//目的の向きを設定
				m_fObjectiveRot = rotCamera.y;
				//回転の慣性をオンにする
				m_bRotate = true;
			}

		}
		else if (pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_DOWN, nNumPlayer) == true ||
			(pInputKeyboard->GetPress(DIK_S) == true && nNumPlayer == 0))			
		{//左スティックを下に倒したときまたはsを押したときの処理の処理の処理
			if (pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_LEFT, nNumPlayer) == true ||
				(pInputKeyboard->GetPress(DIK_A) == true && nNumPlayer == 0))			
			{//左スティックを左に倒したときまたはaを押したときの処理の処理の処理
				//移動量加算
				m_move.x += +cosf(rotCamera.y - D3DX_PI / 4.0f) * fSpeed;
				m_move.z += -sinf(rotCamera.y - D3DX_PI / 4.0f) * fSpeed;

				//目的の向きを設定
				m_fObjectiveRot = rotCamera.y - (D3DX_PI / 4.0f) * 3.0f;
				//回転の慣性をオンにする
				m_bRotate = true;
			}
			else if (pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_RIGHT, nNumPlayer) == true ||
				(pInputKeyboard->GetPress(DIK_D) == true && nNumPlayer == 0))		
			{//左スティックを右に倒したときまたはdを押したときの処理の処理の処理
				//移動量加算
				m_move.x += -cosf(rotCamera.y + D3DX_PI / 4.0f) * fSpeed;
				m_move.z += +sinf(rotCamera.y + D3DX_PI / 4.0f) * fSpeed;

				//目的の向きを設定
				m_fObjectiveRot = rotCamera.y + D3DX_PI / 1.5f;
				//回転の慣性をオンにする
				m_bRotate = true;
			}
			else
			{
				//移動量加算
				m_move.z += +cosf(rotCamera.y) * fSpeed;
				m_move.x += +sinf(rotCamera.y) * fSpeed;

				//目的の向きを設定
				m_fObjectiveRot = rotCamera.y + D3DX_PI;
				//回転の慣性をオンにする
				m_bRotate = true;
			}
		}
		else if (pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_LEFT, nNumPlayer) == true ||
			(pInputKeyboard->GetPress(DIK_A) == true && nNumPlayer == 0))			
		{//左スティックを左に倒したときまたはaを押したときの処理の処理の処理
			//移動量加算
			m_move.x += +cosf(rotCamera.y) * fSpeed;
			m_move.z += -sinf(rotCamera.y) * fSpeed;

			//目的の向きを設定
			m_fObjectiveRot = rotCamera.y - D3DX_PI / 2.0f;
			//回転の慣性をオンにする
			m_bRotate = true;
		}
		else if (pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_RIGHT, nNumPlayer) == true ||
			(pInputKeyboard->GetPress(DIK_D) == true && nNumPlayer == 0))		
		{//左スティックを右に倒したときまたはdを押したときの処理の処理の処理
			//移動量加算
			m_move.x += -cosf(rotCamera.y) * fSpeed;
			m_move.z += +sinf(rotCamera.y) * fSpeed;

			//目的の向きを設定
			m_fObjectiveRot = rotCamera.y + D3DX_PI / 2.0f;
			//回転の慣性をオンにする
			m_bRotate = true;
		}
	}
}

//================================================
//移動の慣性についての処理
//================================================
void CControlPlayer::MoveInteria(CPlayer *pPlayer)
{
	//プレイヤーが氷の上に乗っていたら
	if (pPlayer->GetOnIce() == true)
	{
		// 慣性を0になるまで戻す
		m_move.z *= PLAYER_INTERIA_SUBTRACTION_ON_ICE;
		m_move.x *= PLAYER_INTERIA_SUBTRACTION_ON_ICE;
	}
	else	//乗っていなかったら
	{
		// 慣性を0になるまで戻す
		m_move.z *= PLAYER_INTERIA_SUBTRACTION;
		m_move.x *= PLAYER_INTERIA_SUBTRACTION;
	}

	//移動量が既定の値になったら0にする
	if (m_move.x <= PLAYER_MOVE_STOP_COUNT && m_move.x >= -PLAYER_MOVE_STOP_COUNT)
	{
		m_move.x = 0.0f;
	}
	if (m_move.z <= PLAYER_MOVE_STOP_COUNT && m_move.z >= -PLAYER_MOVE_STOP_COUNT)
	{
		m_move.z = 0.0f;
	}
}

//================================================
//回転処理
//================================================
void CControlPlayer::Rotate(CPlayer *pPlayer)
{
	//プレイヤーの向き取得処理
	D3DXVECTOR3 rotPlayer = pPlayer->GetRot();

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
		if (rotPlayer.y < 0.0f && -rotPlayer.y + m_fObjectiveRot > D3DX_PI)
		{
			m_fNumRot = (-D3DX_PI - rotPlayer.y) + -(D3DX_PI - m_fObjectiveRot);
		}
		else if (rotPlayer.y >= D3DX_PI / 2.0f && rotPlayer.y - m_fObjectiveRot > D3DX_PI)
		{
			m_fNumRot = (D3DX_PI - rotPlayer.y) - (-D3DX_PI - m_fObjectiveRot);
		}
		else
		{
			m_fNumRot = (m_fObjectiveRot - rotPlayer.y);
		}

		//プレイヤーの向きに加算
		rotPlayer.y += m_fNumRot * 0.2f;

		//既定の値に達したら回転をやめる
		if (rotPlayer.y - m_fObjectiveRot < 0.001 && rotPlayer.y - m_fObjectiveRot > -0.001)
		{
			m_bRotate = false;
		}
	}

	//πより大きくなったら-2πする
	if (rotPlayer.y > D3DX_PI)
	{
		rotPlayer.y -= D3DX_PI * 2.0f;
	}
	else if (rotPlayer.y < -D3DX_PI)
	{	//-πより小さくなったら+2πする
		rotPlayer.y += D3DX_PI * 2.0f;
	}

	//向きを反映
	pPlayer->SetRot(rotPlayer);
}

//================================================
//ダイブ処理
//================================================
void CControlPlayer::Dive(CPlayer *pPlayer)
{
	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//パッド取得処理
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	//モーション取得処理
	CMotionPlayer *pMotionPlayer = NULL;
	pMotionPlayer = pPlayer->GetMotionPlayer();

	//プレイヤーの個体識別番号取得処理
	int nNumPlayer = pPlayer->GetNum();

	//プレイヤーが止まってる状態ではないとき
	if (m_bStop == false)
	{
		//ジャンプしていたら
		if (pPlayer->GetJump() == true)
		{
			if (pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_B, nNumPlayer) == true ||
				(pInputKeyboard->GetTrigger(DIK_SPACE) == true && nNumPlayer == 0))
			{	//Bボタンを押したときまたはSPACEを押したときの処理の処理の処理
				//ジャンプ状態の時
				if (m_bJump == true)
				{
					//ダイブしていなかったら
					if (m_bDive == false)
					{
						//サウンド取得処理
						CSound *pSound;
						pSound = CManager::GetSound();

						//ダイブSE
						pSound->Play(CSound::SOUND_LABEL_DIVE_SE);

						//ダイブモーションにする
						pMotionPlayer->SetMotion(CMotionPlayer::MOTION_PLAYER_TYPE_DIVE);
						//ダイブ状態にする
						pPlayer->SetDive(true);
						pPlayer->SetJump(false);
						m_bDive = true;
					}
				}
			}
		}
	}
	//ダイブ状態の時
	if (pPlayer->GetDive() == true)
	{
		//カウントを増やす
		m_nDiveTime++;

		//既定の時間になったら
		if (m_nDiveTime >= PLAYER_DIVE_COUNT)
		{
			m_nDiveTime = 0;
			//ダイブをしていない状態にする
			pPlayer->SetDive(false);
		}
	}
}

//================================================
//ジャンプ処理
//================================================
void CControlPlayer::Jump(CPlayer *pPlayer)
{
	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//パッド取得処理
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	//モーション取得処理
	CMotionPlayer *pMotionPlayer = NULL;
	pMotionPlayer = pPlayer->GetMotionPlayer();

	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	//プレイヤーの向き取得処理
	D3DXVECTOR3 rotPlayer = pPlayer->GetRot();

	//プレイヤーの個体識別番号取得処理
	int nNumPlayer = pPlayer->GetNum();

	if (pPlayer->GetLand() == true)
	{
		m_move.y = 0.0f;

		if (CManager::GetResult() != NULL)
		{

		}
		else
		{
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			// ジャンプ
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			if (pInputPadX->GetButtonTrigger(XINPUT_GAMEPAD_A, nNumPlayer) == true ||
				(pInputKeyboard->GetTrigger(DIK_SPACE) == true && nNumPlayer == 0))
			{	//Aボタンを押したときまたはSPACEを押したときの処理の処理の処理
				if (pPlayer->GetMotionPlayer()->GetMotion() != CMotionPlayer::MOTION_PLAYER_TYPE_DIVE_LAND &&
					pPlayer->GetMotionPlayer()->GetMotion() != CMotionPlayer::MOTION_PLAYER_TYPE_DIVE)
				{
					//ジャンプSE
					pSound->Play(CSound::SOUND_LABEL_JUMP_SE);
					pSound->ControllVoice(CSound::SOUND_LABEL_JUMP_SE, 0.6f);

					//ジャンプモーションにする
					pMotionPlayer->SetMotion(CMotionPlayer::MOTION_PLAYER_TYPE_JUMP);

					//移動量をジャンプ分加算
					m_move.y = PLAYER_JUMP;

					pPlayer->SetJump(true);
					pPlayer->SetLand(false);

					D3DXVECTOR3 pos = pPlayer->GetPos();

					C2DAnimationJump::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR3(m_rot.x, m_rot.y, m_rot.z), 0.8f);
					C2DAnimationJump::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR3(m_rot.x, m_rot.y + 3.14f, m_rot.z), 0.8f);
					C2DAnimationJump::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR3(m_rot.x, m_rot.y + 1.04f, m_rot.z), 0.8f);
					C2DAnimationJump::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR3(m_rot.x, m_rot.y - 1.04f, m_rot.z), 0.8f);
					C2DAnimationJump::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR3(m_rot.x, m_rot.y + 2.1f, m_rot.z), 0.8f);
					C2DAnimationJump::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR3(m_rot.x, m_rot.y - 2.1f, m_rot.z), 0.8f);

					m_bJump = true;
					m_bDive = false;
				}
			}
			//バネに乗ったら
			else if (pPlayer->GetOnSpring() == true)
			{
				//ジャンプSE
				pSound->Play(CSound::SOUND_LABEL_SPRING_SE);
				pSound->ControllVoice(CSound::SOUND_LABEL_SPRING_SE, 1.5f);

				//ジャンプモーションにする
				pMotionPlayer->SetMotion(CMotionPlayer::MOTION_PLAYER_TYPE_JUMP);

				//プレイヤーが向いている方向に移動量を加算
				m_move.z += -cosf(rotPlayer.y) * PLAYER_MOVE_FORWARD_SPRING;
				m_move.x += -sinf(rotPlayer.y) * PLAYER_MOVE_FORWARD_SPRING;

				//移動量をジャンプ分加算
				m_move.y = PLAYER_JUMP_SPRING;

				pPlayer->SetJump(true);
				pPlayer->SetLand(false);

				D3DXVECTOR3 pos = pPlayer->GetPos();

				C2DAnimationJump::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR3(m_rot.x, m_rot.y, m_rot.z), 0.8f);
				C2DAnimationJump::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR3(m_rot.x, m_rot.y + 3.14f, m_rot.z), 0.8f);
				C2DAnimationJump::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR3(m_rot.x, m_rot.y + 1.04f, m_rot.z), 0.8f);
				C2DAnimationJump::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR3(m_rot.x, m_rot.y - 1.04f, m_rot.z), 0.8f);
				C2DAnimationJump::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR3(m_rot.x, m_rot.y + 2.1f, m_rot.z), 0.8f);
				C2DAnimationJump::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR3(m_rot.x, m_rot.y - 2.1f, m_rot.z), 0.8f);

				m_bJump = true;
				m_bDive = false;
			}
			else
			{
				m_bJump = false;
			}
		}
	}
}