//================================================
//プレイヤー処理
//Authore:加藤瑞葵
//================================================
#include "scene2D.h"
#include "manager.h"
#include "game01.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "player.h"
#include "bullet_player.h"
#include "renderer.h"
#include "sound.h"
#include "life.h"
#include "texture.h"
#include "item.h"
#include "score.h"
#include "ui_rest.h"
#include "explosion.h"

//================================================
//静的メンバ変数宣言
//================================================
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;

//================================================
//デフォルトコンストラクタ
//================================================
CPlayer::CPlayer(int nPriority):CScene2D(nPriority)
{
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fAngle = 0.0f;
	m_nLife = 0;
	m_nCounterShoot = 0;
	m_nCounterNotShoot = 0;
	m_nNextShoot = 0;
	m_bulletPowerLevel = PLAYER_BULLET_POWER_LEVEL_NONE;
	m_bulletSpeedLevel = PLAYER_BULLET_SPEED_LEVEL_NONE;
	m_state = PLAYER_STATE_NONE;
	m_nDamageCounter = 0;
	m_nBlinkCounter = 0;
	m_bBlink = false;
	m_pUi = NULL;
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
	m_size = size;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fAngle = 0.0f;
	m_nLife = MAX_PLAYER_INIT_LIFE;
	m_nCounterShoot = PLAYER_BULLET_NEXT_SHOOT_LEVEL_1;
	m_nCounterNotShoot = 0;
	m_nNextShoot = PLAYER_BULLET_NEXT_SHOOT_LEVEL_1;
	m_bulletPowerLevel = PLAYER_BULLET_POWER_LEVEL_1;
	m_bulletSpeedLevel = PLAYER_BULLET_SPEED_LEVEL_1;
	m_state = PLAYER_STATE_NORMAL;
	m_nDamageCounter = 0;
	m_nBlinkCounter = 0;
	m_bBlink = false;


	CScene2D::Init(pos, size);

	//テクスチャ反映
	CScene2D::SetTex(TEXPATTERN_SENTER, TEXPATTERN_MAX);

	//オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_PLAYER);
	return S_OK;
}

//================================================
//終了処理
//================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//================================================
//更新処理
//================================================
void CPlayer::Update(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	pos += m_move;		//移動量反映

	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//パッド取得処理
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	if (CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		//移動処理
		Move(pInputKeyboard, pInputPadX);

		//射撃処理
		Shoot();
	}
	else if (CManager::GetMode() == CManager::MODE_GAME01)
	{
		//ゲームの状態取得
		if (CManager::GetGame01()->GetState() == CGame01::GAME_STATE_GAME)
		{
			//移動処理
			Move(pInputKeyboard, pInputPadX);

			//射撃処理
			Shoot();
		}
		else if (CManager::GetGame01()->GetState() == CGame01::GAME_STATE_CLEAR)
		{
			m_nDamageCounter = PLAYER_DAMAGE_COUNT;
			//移動量を0にする
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}

		if (CManager::GetGame01()->GetState() == CGame01::GAME_STATE_OVER)
		{
			//ゲームオーバー時の処理
			if (GameOver() == true)
			{
				return;
			}
		}
		//ライフが0になったらゲームオーバーにする
		if (m_nLife <= 0)
		{
			CManager::GetGame01()->SetState(CGame01::GAME_STATE_OVER);
		}
	}


	//移動制限
	pos = MoveLimit(pos);

	//状態による色の変化処理
	StateColor();

	//位置反映
	CScene2D::SetPos(pos, m_size);

	//チュートリアルでは当たり判定を行わない
	if (CManager::GetMode() != CManager::MODE_TUTORIAL)
	{
		//プレイヤーの状態がダメージを受けている状態でなければ当たり判定を行う
		if (m_state != PLAYER_STATE_DAMAGE)
		{
			//当たり判定
			if (Collision(pos, pSound) == true)
			{
				return;
			}
		}
	}
}

//================================================
//描画処理
//================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}

//================================================
//生成処理
//================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//インスタンスの生成
	CPlayer *pPlayer = NULL;
	if (pPlayer == NULL)
	{
		pPlayer = new CPlayer;
		if (pPlayer != NULL)
		{
			m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_PLAYER);
			pPlayer->Init(pos, size);
			pPlayer->BindTexture(m_pTexture);
		}
	}
	return pPlayer;
}

//================================================
//プレイヤー移動制限処理
//================================================
D3DXVECTOR3 CPlayer::MoveLimit(D3DXVECTOR3 pos)
{
	if (pos.x - m_size.x / 2.0f <= 0.0f)
	{
		pos.x = 0.0f + m_size.x / 2.0f;
	}
	else if (pos.x + m_size.x / 2.0f >= SCREEN_WIDTH)
	{
		pos.x = SCREEN_WIDTH - m_size.x / 2.0f;
	}
	if (pos.y - m_size.y / 2.0f <= 0.0f)
	{
		pos.y = 0.0f + m_size.y / 2.0f;
	}
	else if (pos.y + m_size.y / 2.0f >= SCREEN_HEIGHT)
	{
		pos.y = SCREEN_HEIGHT - m_size.y / 2.0f;
	}

	return pos;
}

//================================================
//当たり判定処理
//================================================
bool CPlayer::Collision(D3DXVECTOR3 pos, CSound *pSound)
{
	//ライフのポインタ取得
	CLife *pLife;
	pLife = CGame01::GetLife();

	//判定のフラグ
	bool bCol = false;

	//オブジェクト分回す
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{ 
			//シーンのnCnt番目のポインタ取得
			CScene *pScene;
			pScene = CScene::GetScene(nCntScene, nCntPriority);

			if (pScene != NULL)
			{
				//オブジェクトのタイプを取得
				CScene::OBJTYPE objType;
				objType = pScene->GetObjType();

				if (objType == CScene::OBJTYPE_ENEMY)		//オブジェクトのタイプがENEMYの時
				{
					//取得したオブジェクトの位置とサイズを取得
					D3DXVECTOR3 EnemyPos = pScene->GetPos();
					D3DXVECTOR3 Enemysize = pScene->GetSize();

					//当たり判定
					if (pos.x + m_size.x / 2.0f - PLAYER_COLLISION_ADJUST >= EnemyPos.x - Enemysize.x / 2.0f &&
						pos.x - m_size.x / 2.0f + PLAYER_COLLISION_ADJUST <= EnemyPos.x + Enemysize.x / 2.0f &&
						pos.y + m_size.y / 2.0f - PLAYER_COLLISION_ADJUST >= EnemyPos.y - Enemysize.y / 2.0f &&
						pos.y - m_size.y / 2.0f + PLAYER_COLLISION_ADJUST <= EnemyPos.y + Enemysize.y / 2.0f)
					{
						//当たった判定
						bCol = true;
						//サウンドの再生
						pSound->Play(CSound::SOUND_LABEL_EXPLOSION_SE);
						//敵の破棄
						pScene->Uninit();
						//ライフを減らす
						m_nLife--;
						//ライフを設定
						pLife->SubtractLife(1);
						//プレイヤーの状態をダメージにする
						m_state = PLAYER_STATE_DAMAGE;

						break;
					}
				}
			}
		}
	}
	return bCol;
}

//================================================
//移動処理
//================================================
void CPlayer::Move(CInputKeyboard *pInputKeyboard, CInputPadX *pInputPadX)
{
	//位置の取得
	D3DXVECTOR3 pos = GetPos();
	
	//テクスチャ反映
	CScene2D::SetTex(TEXPATTERN_SENTER, TEXPATTERN_MAX);

	//-----------------------------------------
	//ボタンを押し続けているときの処理
	//-----------------------------------------
	if (pInputKeyboard->GetPress(DIK_A) == true ||							//Aキーを押したときの処理
		pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_LEFT) == true)		//左スティックを左に倒したときの処理
	{
		m_move.x = -PLAYER_MOVE;
		//テクスチャ反映
		CScene2D::SetTex(TEXPATTERN_LEFT, TEXPATTERN_MAX);

		if (pInputKeyboard->GetPress(DIK_W) == true ||						//Wキーを押したときの処理
			pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_UP) == true)		//左スティックを上に倒したときの処理
		{
			if (pos.y - m_size.y / 2.0f != 0.0f)
			{
				m_move.x = cosf(D3DX_PI / 4.0f) * -PLAYER_MOVE;
				m_move.y = sinf(D3DX_PI / 4.0f) * -PLAYER_MOVE;
			}
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true ||						//Sキーを押したときの処理
				pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_DOWN) == true)	//左スティックを下に倒したときの処理
		{
			if (pos.y + m_size.y / 2.0f != SCREEN_HEIGHT)
			{
				m_move.x = cosf(D3DX_PI / 4.0f) * -PLAYER_MOVE;
				m_move.y = sinf(D3DX_PI / 4.0f) * PLAYER_MOVE;
			}
		}
	}
	else if (pInputKeyboard->GetPress(DIK_D) == true ||							//Dキーを押したときの処理
			pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_RIGHT) == true)		//左スティックを右に倒したときの処理
	{
		m_move.x = PLAYER_MOVE;
		//テクスチャ反映
		CScene2D::SetTex(TEXPATTERN_RIGHT, TEXPATTERN_MAX);

		if (pInputKeyboard->GetPress(DIK_W) == true ||						//Wキーを押したときの処理
			pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_UP) == true)		//左スティックを上に倒したときの処理
		{
			if (pos.y - m_size.y / 2.0f != 0.0f)
			{
				m_move.x = cosf(D3DX_PI / 4.0f) * PLAYER_MOVE;
				m_move.y = sinf(D3DX_PI / 4.0f) * -PLAYER_MOVE;
			}
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true ||						//Sキーを押したときの処理
				pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_DOWN) == true)	//左スティックを下に倒したときの処理
		{
			if (pos.y + m_size.y / 2.0f != SCREEN_HEIGHT)
			{
				m_move.x = cosf(D3DX_PI / 4.0f) * PLAYER_MOVE;
				m_move.y = sinf(D3DX_PI / 4.0f) * PLAYER_MOVE;
			}
		}
	}
	else if (pInputKeyboard->GetPress(DIK_W) == true ||						//Wキーを押したときの処理
			pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_UP) == true)		//左スティックを上に倒したときの処理
	{
		m_move.y = -PLAYER_MOVE;
	}
	else if (pInputKeyboard->GetPress(DIK_S) == true ||						//Sキーを押したときの処理
			pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_DOWN) == true)	//左スティックを下に倒したときの処理
	{
		m_move.y = PLAYER_MOVE;
	}

	//-----------------------------------------
	////ボタンを離した瞬間の処理
	//-----------------------------------------
	if (pInputKeyboard->GetRelease(DIK_A) == true ||							//Aキーを離したときの処理
		pInputPadX->GetLeftStickRelease(CInputPadX::STICKTYPE_LEFT) == true)	//左に倒した左スティックを戻したときの処理
	{
		m_move.x = 0.0f;

		if (pInputKeyboard->GetPress(DIK_D) == true ||								//Dキーを離したときの処理
			pInputPadX->GetLeftStickRelease(CInputPadX::STICKTYPE_RIGHT) == true)	//右に倒した左スティックを戻したときの処理
		{
			m_move.y = 0.0f;
		}
		else if (pInputKeyboard->GetPress(DIK_A) == true ||							//Aキーを離したときの処理
			pInputPadX->GetLeftStickRelease(CInputPadX::STICKTYPE_LEFT) == true)	//左に倒した左スティックを戻したときの処理
		{
			m_move.y = 0.0f;
		}
	}
	else if (pInputKeyboard->GetRelease(DIK_D) == true ||							//Dキーを離したときの処理
			pInputPadX->GetLeftStickRelease(CInputPadX::STICKTYPE_RIGHT) == true)	//右に倒した左スティックを戻したときの処理
	{
		m_move.x = 0.0f;

		if (pInputKeyboard->GetPress(DIK_D) == true ||								//Dキーを離したときの処理
			pInputPadX->GetLeftStickRelease(CInputPadX::STICKTYPE_RIGHT) == true)	//右に倒した左スティックを戻したときの処理
		{
			m_move.y = 0.0f;
		}
		else if (pInputKeyboard->GetPress(DIK_A) == true ||							//Aキーを離したときの処理
			pInputPadX->GetLeftStickRelease(CInputPadX::STICKTYPE_LEFT) == true)	//左に倒した左スティックを戻したときの処理
		{
			m_move.y = 0.0f;
		}
	}
	if (pInputKeyboard->GetRelease(DIK_W) == true ||							//Wキーを離したときの処理
		pInputPadX->GetLeftStickRelease(CInputPadX::STICKTYPE_UP) == true)		//上に倒した左スティックを戻したときの処理
	{
		m_move.y = 0.0f;

		if (pInputKeyboard->GetPress(DIK_D) == true ||								//Dキーを離したときの処理
			pInputPadX->GetLeftStickRelease(CInputPadX::STICKTYPE_RIGHT) == true)	//右に倒した左スティックを戻したときの処理
		{
			m_move.x = 0.0f;
		}
		else if (pInputKeyboard->GetPress(DIK_A) == true ||							//Aキーを離したときの処理
			pInputPadX->GetLeftStickRelease(CInputPadX::STICKTYPE_LEFT) == true)	//左に倒した左スティックを戻したときの処理
		{
			m_move.x = 0.0f;
		}
	}
	else if (pInputKeyboard->GetRelease(DIK_S) == true ||							//Sキーを離したときの処理
			pInputPadX->GetLeftStickRelease(CInputPadX::STICKTYPE_DOWN) == true)	//下に倒した左スティックを戻したときの処理
	{
		m_move.y = 0.0f;

		if (pInputKeyboard->GetPress(DIK_D) == true ||								//Dキーを離したときの処理
			pInputPadX->GetLeftStickRelease(CInputPadX::STICKTYPE_RIGHT) == true)	//右に倒した左スティックを戻したときの処理
		{
			m_move.x = 0.0f;
		}
		else if (pInputKeyboard->GetPress(DIK_A) == true ||							//Aキーを離したときの処理
			pInputPadX->GetLeftStickRelease(CInputPadX::STICKTYPE_LEFT) == true)	//左に倒した左スティックを戻したときの処理
		{
			m_move.x = 0.0f;
		}
	}
}

//================================================
//射撃処理
//================================================
void CPlayer::Shoot(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();

	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//パッド取得処理
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	//プレイヤーの弾のレベルに応じて次の弾が出るまでの間隔を変更
	switch (m_bulletSpeedLevel)
	{
	case PLAYER_BULLET_SPEED_LEVEL_1:
		m_nNextShoot = PLAYER_BULLET_NEXT_SHOOT_LEVEL_1;
		break;
	case PLAYER_BULLET_SPEED_LEVEL_2:
		m_nNextShoot = PLAYER_BULLET_NEXT_SHOOT_LEVEL_2;
		break;
	case PLAYER_BULLET_SPEED_LEVEL_3:
		m_nNextShoot = PLAYER_BULLET_NEXT_SHOOT_LEVEL_3;
		break;
	case PLAYER_BULLET_SPEED_LEVEL_4:
		m_nNextShoot = PLAYER_BULLET_NEXT_SHOOT_LEVEL_4;
		break;
	default:
		break;
	}

	//撃っていないときカウンターを増やす
	m_nCounterNotShoot++;

	if (pInputKeyboard->GetPress(DIK_SPACE) == true ||			//スペースキーが押されたら
		pInputPadX->GetButtonPress(XINPUT_GAMEPAD_A) == true)		//Aボタンが押されたら
	{
		//撃ってるときカウンターを増やす
		m_nCounterShoot++;

		switch (m_bulletPowerLevel)
		{
		case PLAYER_BULLET_POWER_LEVEL_1:
			if (m_nCounterShoot >= m_nNextShoot || m_nCounterNotShoot >= m_nNextShoot)
			{
				//撃っていないカウンターをリセット
				m_nCounterNotShoot = 0;
				//撃ってる時のカウンターをリセット
				m_nCounterShoot = 0;
				//弾の生成
				CBulletPlayer::Create(pos, D3DXVECTOR3(BULLET_PLAYER_WIDTH, BULLET_PLAYER_HEIGHT, 0.0f),
										D3DXVECTOR3(0.0f, BULLET_PLAYER_SPEED, 0.0f), CBulletPlayer::BULLET_TYPE_STRAIGHT, 0.0f);

				//サウンドの再生
				pSound->Play(CSound::SOUND_LABEL_BULLET_SE);
				//サウンドの音量調整
				pSound->ControllVoice(CSound::SOUND_LABEL_BULLET_SE, 0.2f);
			}
			break;
		case PLAYER_BULLET_POWER_LEVEL_2:
			if (m_nCounterShoot >= m_nNextShoot || m_nCounterNotShoot >= m_nNextShoot)
			{
				//撃っていないカウンターをリセット
				m_nCounterNotShoot = 0;
				//撃ってる時のカウンターをリセット
				m_nCounterShoot = 0;
				//弾の生成
				CBulletPlayer::Create(D3DXVECTOR3(pos.x + PLAYER_BULLET_POWER_LEVEL_2_POS_X, pos.y, pos.z), 
										D3DXVECTOR3(BULLET_PLAYER_WIDTH, BULLET_PLAYER_HEIGHT, 0.0f),
										D3DXVECTOR3(0.0f, BULLET_PLAYER_SPEED, 0.0f), CBulletPlayer::BULLET_TYPE_STRAIGHT, 0.0f);
				//弾の生成
				CBulletPlayer::Create(D3DXVECTOR3(pos.x - PLAYER_BULLET_POWER_LEVEL_2_POS_X, pos.y, pos.z),
										D3DXVECTOR3(BULLET_PLAYER_WIDTH, BULLET_PLAYER_HEIGHT, 0.0f),
										D3DXVECTOR3(0.0f, BULLET_PLAYER_SPEED, 0.0f), CBulletPlayer::BULLET_TYPE_STRAIGHT, 0.0f);
				//サウンドの再生
				pSound->Play(CSound::SOUND_LABEL_BULLET_SE);
				//サウンドの音量調整
				pSound->ControllVoice(CSound::SOUND_LABEL_BULLET_SE, 0.2f);
			}
			break;
		case PLAYER_BULLET_POWER_LEVEL_3:
			if (m_nCounterShoot >= m_nNextShoot || m_nCounterNotShoot >= m_nNextShoot)
			{
				//撃っていないカウンターをリセット
				m_nCounterNotShoot = 0;
				//撃ってる時のカウンターをリセット
				m_nCounterShoot = 0;
				//弾の生成
				CBulletPlayer::Create(D3DXVECTOR3(pos.x + PLAYER_BULLET_POWER_LEVEL_2_POS_X, pos.y, pos.z), 
										D3DXVECTOR3(BULLET_PLAYER_WIDTH, BULLET_PLAYER_HEIGHT, 0.0f),
										D3DXVECTOR3(0.0f, BULLET_PLAYER_SPEED, 0.0f), CBulletPlayer::BULLET_TYPE_STRAIGHT, 0.0f);
				//弾の生成
				CBulletPlayer::Create(D3DXVECTOR3(pos.x - PLAYER_BULLET_POWER_LEVEL_2_POS_X, pos.y, pos.z),
										D3DXVECTOR3(BULLET_PLAYER_WIDTH, BULLET_PLAYER_HEIGHT, 0.0f),
										D3DXVECTOR3(0.0f, BULLET_PLAYER_SPEED, 0.0f), CBulletPlayer::BULLET_TYPE_STRAIGHT, 0.0f);
				//弾の生成
				CBulletPlayer::Create(pos, D3DXVECTOR3(BULLET_PLAYER_WIDTH, BULLET_PLAYER_HEIGHT, 0.0f),
										D3DXVECTOR3(20.0f, 0.0f, 0.0f), CBulletPlayer::BULLET_TYPE_STRAIGHT, -D3DX_PI / 2.0f);
				//弾の生成
				CBulletPlayer::Create(pos, D3DXVECTOR3(BULLET_PLAYER_WIDTH, BULLET_PLAYER_HEIGHT, 0.0f),
										D3DXVECTOR3(-20.0f, 0.0f, 0.0f), CBulletPlayer::BULLET_TYPE_STRAIGHT, D3DX_PI / 2.0f);
				//サウンドの再生
				pSound->Play(CSound::SOUND_LABEL_BULLET_SE);
				//サウンドの音量調整
				pSound->ControllVoice(CSound::SOUND_LABEL_BULLET_SE, 0.2f);
			}
			break;
		case PLAYER_BULLET_POWER_LEVEL_4:

			break;
		default:
			break;
		}
	}
}

//================================================
//弾のレベル設定処理
//================================================
void CPlayer::SetBulletPowerLevel(PLAYER_BULLET_POWER_LEVEL bulletPowerLevel)
{
	m_bulletPowerLevel = bulletPowerLevel;
}

//================================================
//弾のレベル取得処理
//================================================
CPlayer::PLAYER_BULLET_POWER_LEVEL CPlayer::GetBulletPowerLevel(void)
{
	return m_bulletPowerLevel;
}

//================================================
//次の弾を撃つまでの速さのレベル設定処理
//================================================
void CPlayer::SetBulletSpeedLevel(PLAYER_BULLET_SPEED_LEVEL bulletSpeedLevel)
{
	m_bulletSpeedLevel = bulletSpeedLevel;
}

//================================================
//次の弾を撃つまでの速さのレベル取得処理
//================================================
CPlayer::PLAYER_BULLET_SPEED_LEVEL CPlayer::GetBulletSpeedLevel(void)
{
	return m_bulletSpeedLevel;
}

//================================================
//状態に応じた色に変化させる処理
//================================================
void CPlayer::StateColor(void)
{
	//パッド取得処理
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	switch (m_state)
	{
	case PLAYER_STATE_NORMAL:
		break;
	case PLAYER_STATE_DAMAGE:
		//カウンターを加算
		m_nDamageCounter++;
		m_nBlinkCounter++;
		//ダメージを受けた瞬間マスクを生成
		if (m_nDamageCounter == 1)
		{
			//バイブレーション設定
			pInputPadX->SetVibration(60000, 60000, 30);

			m_pUi = CUiRest::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
									D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
									CUiRest::UI_REST_TYPE_DAMAGE_MASK);
		}

		if (m_nBlinkCounter >= PLAYER_BLINK_COUNT)
		{
			m_nBlinkCounter = 0;
			if (m_bBlink == false)
			{
				//薄くする
				SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
				m_bBlink = true;
			}
			else
			{
				//元に戻す
				SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_bBlink = false;
			}
		}

		if (m_nDamageCounter >= PLAYER_DAMAGE_COUNT)
		{
			//マスクを破棄
			m_pUi->Uninit();
			m_pUi = NULL;
			//カウンターを0にする
			m_nDamageCounter = 0;
			//状態をNORMALに戻す
			m_state = PLAYER_STATE_NORMAL;
			//元に戻す
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_bBlink = false;
		}
		break;
	default:
		break;
	}
}

//================================================
//プレイヤーの状態取得処理
//================================================
CPlayer::PLAYER_STATE CPlayer::GetPlayerState(void)
{
	return m_state;
}

//================================================
//プレイヤーの状態設定処理
//================================================
void CPlayer::SetPlayerState(CPlayer::PLAYER_STATE state)
{
	m_state = state;
}

//================================================
//プレイヤーのライフ取得処理
//================================================
int CPlayer::GetLife(void)
{
	return m_nLife;
}

//================================================
//プレイヤーのライフ設定処理
//================================================
void CPlayer::SetLife(int nLife)
{
	m_nLife += nLife;
}

//================================================
//ゲームオーバー時の処理
//================================================
bool CPlayer::GameOver(void)
{
	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	//位置取得
	D3DXVECTOR3 pos = GetPos();

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//フレーム数取得
	int nClearCounter = CGame01::GetFinishCounter();

	if (nClearCounter == PLAYER_OVER_UNINIT_COUNT)
	{
		//ボスを破棄
		Uninit();
		return true;
	}
	else
	{
		if (nClearCounter % PLAYER_OVER_EXPLOSION_COUNT == 0)
		{
			//サウンドの再生
			pSound->Play(CSound::SOUND_LABEL_DIE_EXPLOSION_SE);
			//サウンドの音量調整
			pSound->ControllVoice(CSound::SOUND_LABEL_BOSS_BULLET_SE, 1.6f);

			//爆発の生成
			CExplosion::Create(pos, D3DXVECTOR3(EXPLOSION_WIDTH, EXPLOSION_HEIGHT, 0.0f));
		}
	}
	return false;
}