//================================================
//敵の弾処理
//Author:KatoMizuki
//================================================
#include "bullet_enemy.h"
#include "manager.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "floor.h"
#include "model_single.h"
#include "player.h"
#include "play_data.h"
#include "gauge.h"
#include "guard_effect.h"
#include "sound.h"

//================================================
//マクロ定義
//================================================
#define BULLET_ENEMY_MOVE_SPEED		(15.0f)		//弾の移動速度
#define BULLET_ENEMY_LIFE			(300)		//寿命
#define BULLET_ENEMY_DAMAGE			(30)		//ダメージ量
#define BULLET_ENEMY_GUARD_ADD_SP	(2)			//ガード時のSP増加量

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CBulletEnemy::CBulletEnemy(int nPriority) :CBillboard(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CBulletEnemy::~CBulletEnemy()
{

}

//================================================
//初期化処理
//================================================
HRESULT CBulletEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_nLife = 0;

	CBillboard::Init(pos,size);

	//オブジェクトの種類を設定
	SetObjType(CObject::OBJTYPE::BULLET_ENEMY);

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
			//オブジェクトの位置とサイズを取得
			D3DXVECTOR3 posObj = pObject->GetPos();
			D3DXVECTOR3 sizeObj = pObject->GetSize();

			//位置をサイズ分調整
			posObj.y += sizeObj.y;

			//移動量を決めるためのベクトル
			D3DXVECTOR3 moveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//プレイヤーの位置から自身の位置のベクトルを求める
			moveVec = D3DXVECTOR3(m_pos.x - posObj.x, m_pos.y - posObj.y, m_pos.z - posObj.z);

			//算出したベクトルを正規化
			D3DXVec3Normalize(&moveVec, &moveVec);

			//移動量をベクトルをもとに算出
			m_move = D3DXVECTOR3(-moveVec.x * BULLET_ENEMY_MOVE_SPEED, -moveVec.y * BULLET_ENEMY_MOVE_SPEED, -moveVec.z * BULLET_ENEMY_MOVE_SPEED);
		}
		//次のオブジェクトに進める
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}

	//ビルボードのモード設定
	SetMode(BILLBOARD_MODE::NORMAL);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CBulletEnemy::Uninit(void)
{
	CBillboard::Uninit();
}

//================================================
//更新処理
//================================================
void CBulletEnemy::Update(void)
{
	//カウンターを加算
	m_nLife++;

	//規定値以上になったら
	if (m_nLife >= BULLET_ENEMY_LIFE)
	{
		//0にする
		m_nLife = 0;
		//消す
		Uninit();
		return;
	}

	//移動量を位置に加算
	m_pos += m_move;

	//位置の設定
	SetPos(m_pos, m_size);

	//3Dポリゴンとの当たり判定
	if (CFloor::Collision(this) == true)
	{
		Uninit();
		return;
	}

	//モデルとの当たり判定
	if (CModelSingle::CollisionAny(this) == true)
	{
		Uninit();
		return;
	}

	//プレイヤーとの当たり判定
	CollisionPlayer();
}

//================================================
//描画処理
//================================================
void CBulletEnemy::Draw(void)
{
	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 50);

	CBillboard::Draw();

	//ライティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//アルファテスト元に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
}

//================================================
//生成処理
//================================================
CBulletEnemy* CBulletEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//インスタンスの生成
	CBulletEnemy *pBulletEnemy = nullptr;
	if (pBulletEnemy == nullptr)
	{
		pBulletEnemy = new CBulletEnemy();
		if (pBulletEnemy != nullptr)
		{
			pBulletEnemy->m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pBulletEnemy->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_BULLET_ENEMY");
			pBulletEnemy->Init(pos, size);
		}
	}
	return pBulletEnemy;
}

//================================================
//プレイヤーとの当たり判定
//================================================
void CBulletEnemy::CollisionPlayer(void)
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

			//プレイヤーとの当たり判定
			if (pPlayerObj->CollisionOnly(this, m_size.x / 2.0f) == true)
			{
				//当たったときの処理
				if (pPlayerObj->GetState() == CPlayer::PLAYER_STATE::NORMAL)
				{//通常状態なら
					//ガードしていなかったら
					if (pPlayerObj->GetGuard() == false)
					{
						//ダメージ状態にする
						pPlayerObj->SetState(CPlayer::PLAYER_STATE::DAMAGE);
						//HPを減らす
						CManager::GetInstance()->GetPlayData()->GetHpGauge()->AddGauge(-BULLET_ENEMY_DAMAGE);
						//ライフが0になったら
						if (CManager::GetInstance()->GetPlayData()->GetHpGauge()->GetGauge() <= 0)
						{
							//ゲームオーバーにする
							CManager::GetInstance()->GetPlayData()->SetGameOver(true);
						}
					}
					else
					{//ガードしていたら
						//プレイヤーの位置と向き取得
						D3DXVECTOR3 posPlayer = pPlayerObj->GetPos();
						D3DXVECTOR3 rotPlayer = pPlayerObj->GetRot();
						float fRotPlayerY = rotPlayer.y;

						//プレイヤーとの角度を求める
						float fRot = atan2((posPlayer.x - m_pos.x), (posPlayer.z - m_pos.z));

						//プレイヤーの向きだけがマイナスの時D3DXPI*2を足す
						if (fRotPlayerY < 0.0f && fRot > 0.0f)
						{
							fRotPlayerY += D3DX_PI * 2.0f;
						}
						else if (rotPlayer.y > 0.0f && fRot < 0.0f)
						{//プレイヤーとの角度だけがマイナスの時D3DXPI*2を足す
							fRot += D3DX_PI * 2.0f;
						}

						float fDiffer = abs(fRotPlayerY - fRot);
						//向きの差が90度以上あったら
						if (fDiffer> D3DX_PI / 2.0f)
						{
							//ダメージ状態にする
							pPlayerObj->SetState(CPlayer::PLAYER_STATE::DAMAGE);
							//HPを減らす
							CManager::GetInstance()->GetPlayData()->GetHpGauge()->AddGauge(-BULLET_ENEMY_DAMAGE);
							//ライフが0になったら
							if (CManager::GetInstance()->GetPlayData()->GetHpGauge()->GetGauge() <= 0)
							{
								//ゲームオーバーにする
								CManager::GetInstance()->GetPlayData()->SetGameOver(true);
							}
						}
						else
						{
							//サウンド取得処理
							CSound *pSound;
							pSound = CManager::GetInstance()->GetSound();

							//SE再生
							pSound->Play(CSound::SOUND_LABEL_GUARD_SE);
							//サウンドの音量調整
							pSound->ControllVoice(CSound::SOUND_LABEL_GUARD_SE, 1.3f);

							//ガードエフェクトの生成
							CGuardEffect::Create(D3DXVECTOR3(posPlayer.x + sinf(rotPlayer.y - D3DX_PI) * GUARD_EFFECT_POS,
								                             posPlayer.y + GUARD_EFFECT_POS_Y,
								                             posPlayer.z + cosf(rotPlayer.y - D3DX_PI) * GUARD_EFFECT_POS),
								                 D3DXVECTOR3(GUARD_EFFECT_SIZE, GUARD_EFFECT_SIZE, 0.0f), rotPlayer);

							//SPゲージを増やす
							CManager::GetInstance()->GetPlayData()->GetSpGauge()->AddGauge(BULLET_ENEMY_GUARD_ADD_SP);
						}
					}
				}

				//消す
				Uninit();
			}
		}
		//次のオブジェクトに進める
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}

