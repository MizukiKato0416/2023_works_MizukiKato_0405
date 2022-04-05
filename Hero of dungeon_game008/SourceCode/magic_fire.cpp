//================================================
//炎魔法の処理
//Author:KatoMizuki
//================================================
#include "magic_fire.h"
#include "fire_ball.h"
#include "texture.h"
#include "magic_circle.h"
#include "manager.h"
#include "object3D.h"
#include "player.h"
#include "sound.h"

//================================================
//マクロ定義
//================================================
#define MAGIC_FIRE_CIRCLE_SIZE				(60.0f)		//魔法陣のサイズ
#define MAGIC_FIRE_CIRCLE_ADD_SIZE			(3.5f)		//魔法陣を大きくする値
#define MAGIC_FIRE_CIRCLE_SUBTRACTION_SIZE	(8.0f)		//魔法陣を小さくする値
#define MAGIC_FIRE_COUNTER					(50)		//魔法陣を出す時間
#define MAGIC_FIRE_SUBTRACTION_COUNTER		(60)		//魔法陣を小さくし始める時間
#define MAGIC_FIRE_BALL_CREATE_COUNTER_01	(20)		//火球を出す時間1
#define MAGIC_FIRE_BALL_CREATE_COUNTER_02	(35)		//火球を出す時間2
#define MAGIC_FIRE_BALL_CREATE_COUNTER_03	(50)		//火球を出す時間3
#define MAGIC_FIRE_BALL_ROT_PARTITION_NUM	(4)			//角度分割数
#define MAGIC_FIRE_BALL_LAYER				(3)			//層の数
#define MAGIC_FIRE_BALL_LIFE				(100)		//寿命
#define MAGIC_FIRE_BALL_POWRER				(3.8f)		//y=a(x*x)のaの部分
#define MAGIC_FIRE_BALL_SIZE				(60.0f)		//サイズ

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CMagicFire::CMagicFire(int nPriority) :CObject(nPriority)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pMagicCircle = nullptr;
	m_pFireBall = nullptr;
	m_nCounter = 0;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CMagicFire::~CMagicFire()
{

}

//================================================
//初期化処理
//================================================
HRESULT CMagicFire::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//変数初期化
	m_nCounter = 0;

	//オブジェクトの種類を設定
	SetObjType(CObject::OBJTYPE::MAGIC_FIRE);
	
	//魔法陣を出す
	m_pMagicCircle = CMagicCircle::Create(pos, D3DXVECTOR3(1.0f, 1.0f, 0.0f), m_rot);
	//テクスチャを設定
	m_pMagicCircle->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_CHECK_POINT"));
	//カリングをオフ
	m_pMagicCircle->SetCulling(false);
	//αテストをオン
	m_pMagicCircle->SetAlphaTest(true);
	//カラーを設定
	m_pMagicCircle->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	//回転軸を設定
	m_pMagicCircle->SetRotateType(CMagicCircle::ROTATE_TYPE::Z);
	//プライオリティを設定
	m_pMagicCircle->SetPriority(CObject::PRIORITY_MAGIC);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CMagicFire::Uninit(void)
{
	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CMagicFire::Update(void)
{
	if (m_pMagicCircle != nullptr)
	{
		//位置とサイズを取得
		D3DXVECTOR3 pos = m_pMagicCircle->GetPos();
		D3DXVECTOR3 size = m_pMagicCircle->GetSize();

		//オブジェクト情報を入れるポインタ
		CObject *pThisObject = nullptr;
		//オブジェクト情報を保存するポインタ変数
		CObject *pSaveObject = nullptr;

		//先頭のポインタを代入
		pThisObject = pThisObject->GetTopObj(CObject::PRIORITY_PLAYER);

		while (pThisObject != nullptr)
		{
			//現在のオブジェクトのポインタを保存
			pSaveObject = pThisObject;
			if (pThisObject->GetObjType() == CObject::OBJTYPE::PLAYER)
			{
				//プレイヤーにキャスト
				CPlayer *pPlayer = nullptr;
				pPlayer = (CPlayer*)pThisObject;

				//プレイヤーの位置と向き取得
				D3DXVECTOR3 posPlayer = pPlayer->GetPos();
				D3DXVECTOR3 rotPlayer = pPlayer->GetRot();

				pos = D3DXVECTOR3(posPlayer.x + sinf(rotPlayer.y - D3DX_PI) * PLAYER_MAGIC_01_POS,
					              posPlayer.y + PLAYER_MAGIC_01_POS_Y,
					              posPlayer.z + cosf(rotPlayer.y - D3DX_PI) * PLAYER_MAGIC_01_POS);
			}
			pThisObject = pSaveObject->GetObjNext(pSaveObject);
		}



		//カウンターを加算
		m_nCounter++;

		//既定の値以下の時
		if (m_nCounter <= MAGIC_FIRE_COUNTER)
		{
			//既定の値より小さかったら
			if (size.x < MAGIC_FIRE_CIRCLE_SIZE)
			{
				//サイズを大きくする
				size.x += MAGIC_FIRE_CIRCLE_ADD_SIZE;
				size.y += MAGIC_FIRE_CIRCLE_ADD_SIZE;

				//既定のサイズを超えたら
				if (size.x >= MAGIC_FIRE_CIRCLE_SIZE)
				{
					//既定のサイズにする
					size.x = MAGIC_FIRE_CIRCLE_SIZE;
					size.y = MAGIC_FIRE_CIRCLE_SIZE;
				}

				//サイズを設定
				m_pMagicCircle->SetPos(pos, size);
			}

			//既定の値の時
			if (m_nCounter == MAGIC_FIRE_BALL_CREATE_COUNTER_01 ||
				m_nCounter == MAGIC_FIRE_BALL_CREATE_COUNTER_02 || 
				m_nCounter == MAGIC_FIRE_BALL_CREATE_COUNTER_03)
			{
				//サウンド取得処理
				CSound *pSound;
				pSound = CManager::GetInstance()->GetSound();

				//SE再生
				pSound->Play(CSound::SOUND_LABEL_MAGIC_SE);
				//サウンドの音量調整
				pSound->ControllVoice(CSound::SOUND_LABEL_MAGIC_SE, 1.8f);

				//火球の生成
				CFireBall::Create(pos, MAGIC_FIRE_BALL_ROT_PARTITION_NUM, MAGIC_FIRE_BALL_LAYER, MAGIC_FIRE_BALL_LIFE, MAGIC_FIRE_BALL_POWRER,
					              D3DXVECTOR3(sinf(m_rot.y + D3DX_PI) * MAGIC_FIRE_BALL_MOVE, 0.0f, cosf(m_rot.y + D3DX_PI) * MAGIC_FIRE_BALL_MOVE),
								  D3DXVECTOR3(MAGIC_FIRE_BALL_SIZE, MAGIC_FIRE_BALL_SIZE, MAGIC_FIRE_BALL_SIZE));
			}
		}
		else
		{//既定の値よりも大きいとき
			//既定の値よりも小さいとき
			if (m_nCounter < MAGIC_FIRE_SUBTRACTION_COUNTER)
			{
				//サイズを大きくする
				size.x += MAGIC_FIRE_CIRCLE_ADD_SIZE;
				size.y += MAGIC_FIRE_CIRCLE_ADD_SIZE;
			}
			else
			{//既定の値以上の時
				//サイズを小さくする
				size.x -= MAGIC_FIRE_CIRCLE_SUBTRACTION_SIZE;
				size.y -= MAGIC_FIRE_CIRCLE_SUBTRACTION_SIZE;

				//見えなくなったら
				if (size.x <= 0.0f || size.y <= 0.0f)
				{
					//消す
					m_pMagicCircle->Uninit();
					m_pMagicCircle = nullptr;

					Uninit();
					return;
				}
			}
		}

		if (m_pMagicCircle != nullptr)
		{
			//サイズを設定
			m_pMagicCircle->SetPos(pos, size);
		}
	}
}

//================================================
//描画処理
//================================================
void CMagicFire::Draw(void)
{
	
}

//================================================
//生成処理
//================================================
CMagicFire* CMagicFire::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//インスタンスの生成
	CMagicFire *pMagicFire = nullptr;
	if (pMagicFire == nullptr)
	{
		pMagicFire = new CMagicFire();
		if (pMagicFire != nullptr)
		{
			pMagicFire->m_rot = rot;
			pMagicFire->Init(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}
	return pMagicFire;
}
