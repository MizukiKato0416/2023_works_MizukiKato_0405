//================================================
//魔法陣の処理
//Author:KatoMizuki
//================================================
#include "check_circle.h"
#include "effect3D.h"
#include "texture.h"
#include "object2D.h"
#include "manager.h"
#include "play_data.h"
#include "gauge.h"
#include "map.h"
#include "sound.h"

//================================================
//マクロ定義
//================================================
#define CHECK_CIRCLE_EFFECT_NUM		(rand() % 16 + 8)						//エフェクトの数
#define CHECK_CIRCLE_EFFECT_ROT		(float (rand() % 629 + -314) / 100)		//エフェクトを出す場所を決めるための角度
#define CHECK_CIRCLE_EFFECT_COUNTER	(rand() % 120 + 30)						//エフェクトを出す頻度
#define CHECK_CIRCLE_MAX_GAUGE		(300)									//ゲージ最大値

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CCheckCircle::CCheckCircle(int nPriority) :CMagicCircle(nPriority)
{
	m_nEffectCounter = 0;
	m_pMask = nullptr;
	m_pGauge = nullptr;
	m_pGaugeFrame = nullptr;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CCheckCircle::~CCheckCircle()
{

}

//================================================
//初期化処理
//================================================
HRESULT CCheckCircle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CMagicCircle::Init(pos,size);

	//オブジェクトの種類を設定
	SetObjType(CObject::OBJTYPE::CHECK_CIRCLE);

	//変数初期化
	m_nEffectCounter = 0;
	m_pMask = nullptr;
	m_pGauge = nullptr;
	m_pGaugeFrame = nullptr;

	
	

	return S_OK;
}

//================================================
//終了処理
//================================================
void CCheckCircle::Uninit(void)
{
	//マップ上の敵の位置破棄
	CMap::Delete(this);

	if (m_pMask != nullptr)
	{
		//マスクを削除
		m_pMask->Uninit();
		m_pMask = nullptr;
	}
	if (m_pGaugeFrame != nullptr)
	{
		//ゲージのフレームを削除
		m_pGaugeFrame->Uninit();
		m_pGaugeFrame = nullptr;
	}
	if (m_pGauge != nullptr)
	{
		//ゲージを削除
		m_pGauge->Uninit();
		m_pGauge = nullptr;
	}

	CMagicCircle::Uninit();
}

//================================================
//更新処理
//================================================
void CCheckCircle::Update(void)
{
	CMagicCircle::Update();

	//プレイヤーとの当たり判定
	if (CollisionPlayer() == true)
	{
		if (m_pGauge != nullptr)
		{
			//ゲージの量が既定の以上になったら
			if (m_pGauge->GetGauge() >= m_pGauge->GetMaxNum())
			{
				//サウンド取得処理
				CSound *pSound;
				pSound = CManager::GetInstance()->GetSound();

				//SE再生
				pSound->Play(CSound::SOUND_LABEL_CURE_SE);
				//サウンドの音量調整
				pSound->ControllVoice(CSound::SOUND_LABEL_CURE_SE, 1.3f);

				//HPとMPを回復させる
				CManager::GetInstance()->GetPlayData()->GetHpGauge()->AddGauge(200);
				CManager::GetInstance()->GetPlayData()->GetMpGauge()->AddGauge(200);

				//チェックポイントを消す
				Uninit();
				return;
			}
		}

		if (m_pMask == nullptr)
		{
			//マスクを作成
			m_pMask = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
										D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CObject::PRIORITY_MASK);
			m_pMask->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_CHECK_MASK"));
		}
		if (m_pGaugeFrame == nullptr)
		{
			//ゲージのフレームを作成
			m_pGaugeFrame = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
												D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CObject::PRIORITY_UI);
			m_pGaugeFrame->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_CHECK_GAUGE_FRAME"));
		}
		if (m_pGauge == nullptr)
		{
			//ゲージを作成
			m_pGauge = CGauge::Create(D3DXVECTOR3(480.84f, 352.0f + 15.01f / 2.0f, 0.0f), D3DXVECTOR3(317.36f, 15.01f, 0.0f), CHECK_CIRCLE_MAX_GAUGE, 0);
			m_pGauge->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_CHECK_GAUGE"));
		}
		//チェックポイントのゲージを増やす
		m_pGauge->AddGauge(1);
	}
	else
	{
		if (m_pMask != nullptr)
		{
			//マスクを削除
			m_pMask->Uninit();
			m_pMask = nullptr;
		}
		if (m_pGaugeFrame != nullptr)
		{
			//ゲージのフレームを削除
			m_pGaugeFrame->Uninit();
			m_pGaugeFrame = nullptr;
		}
		if (m_pGauge != nullptr)
		{
			//ゲージを削除
			m_pGauge->Uninit();
			m_pGauge = nullptr;
		}
	}

	//カウンターを加算
	m_nEffectCounter++;
	//規定値よりも大きくなったら
	if (m_nEffectCounter >= CHECK_CIRCLE_EFFECT_COUNTER)
	{
		//エフェクトの生成
		for (int nCnteffect = 0; nCnteffect < CHECK_CIRCLE_EFFECT_NUM; nCnteffect++)
		{
			float fRot = CHECK_CIRCLE_EFFECT_ROT;
			CEffect3D::Create(D3DXVECTOR3(m_pos.x + cosf(fRot) * m_size.x / 2.0f,
													m_pos.y,
													m_pos.z + sinf(fRot) * m_size.z / 2.0f),
							  D3DXVECTOR3(5.0f, 5.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.3f, 1.0f), CEffect3D::EFFECT3D_TYPE::CHECK);
		}
		//0にする
		m_nEffectCounter = 0;
	}
}

//================================================
//描画処理
//================================================
void CCheckCircle::Draw(void)
{
	CMagicCircle::Draw();
}

//================================================
//生成処理
//================================================
CCheckCircle* CCheckCircle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	//インスタンスの生成
	CCheckCircle *pCheckCircle = nullptr;
	if (pCheckCircle == nullptr)
	{
		pCheckCircle = new CCheckCircle();
		if (pCheckCircle != nullptr)
		{
			pCheckCircle->m_rot = rot;
			pCheckCircle->Init(pos, size);
		}
	}
	return pCheckCircle;
}


//================================================
//プレイヤーとの当たり判定
//================================================
bool CCheckCircle::CollisionPlayer(void)
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
			//オブジェクトの位置とサイズを取得
			D3DXVECTOR3 posObj = pObject->GetPos();
			D3DXVECTOR3 sizeObj = pObject->GetSize();

			//中心点からプレイヤーまでの距離を求める
			float fRadius = sqrtf((posObj.x - m_pos.x) * (posObj.x - m_pos.x) +
				(posObj.z - m_pos.z) * (posObj.z - m_pos.z));

			//魔法陣の半径以下だったら
			if (fRadius <= m_size.x / 2.0f)
			{
				return true;
			}
		}
		//次のオブジェクトに進める
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}

	return false;
}
