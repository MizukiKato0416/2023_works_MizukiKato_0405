//================================================
//雷魔法の処理
//Author:KatoMizuki
//================================================
#include "magic_thunder.h"
#include "effect3D.h"
#include "texture.h"
#include "magic_circle.h"
#include "manager.h"
#include "texture.h"
#include "object3D.h"
#include "enemy.h"

//================================================
//マクロ定義
//================================================
#define MAGIC_THUNDER_CIRCLE_SIZE				(800.0f)							//魔法陣のサイズ
#define MAGIC_THUNDER_CIRCLE_ADD_SIZE			(30.0f)								//魔法陣を大きくする値
#define MAGIC_THUNDER_CIRCLE_SUBTRACTION_SIZE	(40.0f)								//魔法陣を小さくする値
#define MAGIC_THUNDER_COUNTER					(400)								//魔法陣を出す時間
#define MAGIC_THUNDER_SUBTRACTION_COUNTER		(420)								//魔法陣を小さくし始める時間
#define MAGIC_THUNDER_EFFECT_NUM				(8)									//雷エフェクトの数
#define MAGIC_THUNDER_EFFECT_SIZ_X				(0.1f)								//雷エフェクトのサイズX
#define MAGIC_THUNDER_EFFECT_SIZ_Y				(1200.0f)							//雷エフェクトのサイズY
#define MAGIC_THUNDER_EFFECT_COLOR				(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))	//雷エフェクトの色
#define MAGIC_THUNDER_EFFECT_FLASH_SIZE			(0.1f)								//閃光エフェクトのサイズ
#define MAGIC_THUNDER_EFFECT_FLASH_POS_Y		(120.0f)							//閃光エフェクトのy座標

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CMagicThunder::CMagicThunder(int nPriority) :CObject(nPriority)
{
	m_pMagicCircle = nullptr;
	m_nCounter = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CMagicThunder::~CMagicThunder()
{

}

//================================================
//初期化処理
//================================================
HRESULT CMagicThunder::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//変数初期化
	m_nCounter = 0;
	m_pos = pos;
	m_size = size;

	//オブジェクトの種類を設定
	SetObjType(CObject::OBJTYPE::MAGIC_THUNDER);
	
	//魔法陣を出す
	m_pMagicCircle = CMagicCircle::Create(m_pos, D3DXVECTOR3(1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//テクスチャを設定
	m_pMagicCircle->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_MAGIC_CIRCLE_01"));
	//カリングをオフ
	m_pMagicCircle->SetCulling(false);
	//加算合成をオン
	m_pMagicCircle->SetAlphaBlend(true);
	//プライオリティの設定
	m_pMagicCircle->SetPriority(CObject::PRIORITY_MAGIC);

	//エフェクトの生成
	for (int nCnteffect = 0; nCnteffect < MAGIC_THUNDER_EFFECT_NUM; nCnteffect++)
	{
		CEffect3D *pEffect3D = nullptr;
		pEffect3D = CEffect3D::Create(D3DXVECTOR3(pos.x + cosf(D3DX_PI * 2.0f / (float)MAGIC_THUNDER_EFFECT_NUM * nCnteffect) * MAGIC_THUNDER_CIRCLE_SIZE / 2.0f,
													0.0f,
													pos.z + sinf(D3DX_PI * 2.0f / (float)MAGIC_THUNDER_EFFECT_NUM * nCnteffect) * MAGIC_THUNDER_CIRCLE_SIZE / 2.0f),
									  D3DXVECTOR3(MAGIC_THUNDER_EFFECT_SIZ_X, MAGIC_THUNDER_EFFECT_SIZ_Y, 0.0f),
			                          MAGIC_THUNDER_EFFECT_COLOR, CEffect3D::EFFECT3D_TYPE::THUNDER);
		pEffect3D->SetMode(CBillboard::BILLBOARD_MODE::BESIDE_ONLY);
	}

	//エフェクトの生成
	CEffect3D::Create(D3DXVECTOR3(pos.x, pos.y - MAGIC_THUNDER_EFFECT_FLASH_POS_Y, pos.z),
			          D3DXVECTOR3(MAGIC_THUNDER_EFFECT_FLASH_SIZE, MAGIC_THUNDER_EFFECT_FLASH_SIZE, 0.0f),
					  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CEffect3D::EFFECT3D_TYPE::FLASH);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CMagicThunder::Uninit(void)
{
	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CMagicThunder::Update(void)
{
	//魔法陣に関する処理
	MagicCircle();
}

//================================================
//描画処理
//================================================
void CMagicThunder::Draw(void)
{
	
}

//================================================
//生成処理
//================================================
CMagicThunder* CMagicThunder::Create(D3DXVECTOR3 pos)
{
	//インスタンスの生成
	CMagicThunder *pMagicThunder = nullptr;
	if (pMagicThunder == nullptr)
	{
		pMagicThunder = new CMagicThunder();
		if (pMagicThunder != nullptr)
		{
			pMagicThunder->Init(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}
	return pMagicThunder;
}

//================================================
//当たり判定
//================================================
bool CMagicThunder::Collision(CObject *pSubjectObject)
{
	//オブジェクト情報を入れるポインタ
	CObject *pObject = nullptr;
	//オブジェクト情報を保存するポインタ変数
	CObject *pSaveObject = nullptr;

	//先頭のポインタを代入
	pObject = pObject->GetTopObj(CObject::PRIORITY_MAGIC);

	while (pObject != nullptr)
	{
		//現在のオブジェクトのポインタを保存
		pSaveObject = pObject;

		//オブジェクトの種類が雷魔法だったら
		if (pObject->GetObjType() == CObject::OBJTYPE::MAGIC_THUNDER)
		{
			//雷魔法にキャスト
			CMagicThunder *pMagicThunderObj = nullptr;
			pMagicThunderObj = (CMagicThunder*)pObject;

			//オブジェクトの位置とサイズを取得
			D3DXVECTOR3 posObj = pSubjectObject->GetPos();
			D3DXVECTOR3 sizeObj = pSubjectObject->GetSize();

			//中心点からプレイヤーまでの距離を求める
			float fRadius = sqrtf((posObj.x - pMagicThunderObj->m_pos.x) * (posObj.x - pMagicThunderObj->m_pos.x) +
				                  (posObj.z - pMagicThunderObj->m_pos.z) * (posObj.z - pMagicThunderObj->m_pos.z));
			 
			//魔法陣の半径の1.5倍以下だったら
			if (fRadius <= pMagicThunderObj->m_size.x / 2.0f)
			{
				return true;
			}
		}
		//次のオブジェクトに進める
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
	return false;
}

//================================================
//魔法陣に関する処理
//================================================
void CMagicThunder::MagicCircle(void)
{
	if (m_pMagicCircle != nullptr)
	{
		//位置とサイズを取得
		m_pos = m_pMagicCircle->GetPos();
		m_size = m_pMagicCircle->GetSize();

		//カウンターを加算
		m_nCounter++;

		//既定の値以下の時
		if (m_nCounter <= MAGIC_THUNDER_COUNTER)
		{
			//既定の値より小さかったら
			if (m_size.x < MAGIC_THUNDER_CIRCLE_SIZE)
			{
				//サイズを大きくする
				m_size.x += MAGIC_THUNDER_CIRCLE_ADD_SIZE;
				m_size.z += MAGIC_THUNDER_CIRCLE_ADD_SIZE;

				//既定のサイズを超えたら
				if (m_size.x >= MAGIC_THUNDER_CIRCLE_SIZE)
				{
					//既定のサイズにする
					m_size.x = MAGIC_THUNDER_CIRCLE_SIZE;
					m_size.z = MAGIC_THUNDER_CIRCLE_SIZE;
				}

				//サイズを設定
				m_pMagicCircle->SetPos(m_pos, m_size);
			}
		}
		else
		{//既定の値よりも大きいとき
		 //既定の値よりも小さいとき
			if (m_nCounter < MAGIC_THUNDER_SUBTRACTION_COUNTER)
			{
				//サイズを大きくする
				m_size.x += MAGIC_THUNDER_CIRCLE_ADD_SIZE;
				m_size.z += MAGIC_THUNDER_CIRCLE_ADD_SIZE;
			}
			else
			{//既定の値以上の時
			 //サイズを小さくする
				m_size.x -= MAGIC_THUNDER_CIRCLE_SUBTRACTION_SIZE;
				m_size.z -= MAGIC_THUNDER_CIRCLE_SUBTRACTION_SIZE;

				//見えなくなったら
				if (m_size.x <= 0.0f || m_size.z <= 0.0f)
				{
					//消す
					m_pMagicCircle->Uninit();
					m_pMagicCircle = nullptr;
				}
			}

			if (m_pMagicCircle != nullptr)
			{
				//サイズを設定
				m_pMagicCircle->SetPos(m_pos, m_size);
			}
		}
	}
}
