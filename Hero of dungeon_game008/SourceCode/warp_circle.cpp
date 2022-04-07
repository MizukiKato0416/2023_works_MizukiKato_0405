//================================================
//ワープ魔法陣の処理
//Author:KatoMizuki
//================================================
#include "warp_circle.h"
#include "effect3D.h"
#include "texture.h"
#include "manager.h"
#include "fade.h"
#include "enemy.h"
#include "ui.h"

//================================================
//マクロ定義
//================================================
#define WARP_CIRCLE_EFFECT_NUM						(rand() % 16 + 8)						//エフェクトの数
#define WARP_CIRCLE_EFFECT_ROT						(float (rand() % 629 + -314) / 100)		//エフェクトを出す場所を決めるための角度
#define WARP_CIRCLE_EFFECT_COUNTER					(rand() % 120 + 30)						//エフェクトを出す頻度
#define WARP_CIRCLE_OBJECT3D_COUNTER				(120)									//上に上がるオブジェクトを表示する時間
#define WARP_CIRCLE_OBJECT3D_MOVE					(0.5f)									//上に上がるオブジェクトの移動量
#define WARP_CIRCLE_OBJECT3D_COLOR_SUBTRACTION		(0.006f)								//上に上がるオブジェクトのカラー減算値

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CWarpCircle::CWarpCircle(int nPriority) :CMagicCircle(nPriority)
{
	m_nEffectCounter = 0;
	m_pObject3D = nullptr;
	m_nObject3DCounter = 0;
	m_pUiMessage = nullptr;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CWarpCircle::~CWarpCircle()
{

}

//================================================
//初期化処理
//================================================
HRESULT CWarpCircle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CMagicCircle::Init(pos,size);

	//オブジェクトの種類を設定
	SetObjType(CObject::OBJTYPE::WARP_CIRCLE);

	m_nEffectCounter = 0;
	m_pObject3D = nullptr;
	m_nObject3DCounter = 0;
	m_pUiMessage = nullptr;

	return S_OK;
}

//================================================
//終了処理
//================================================
void CWarpCircle::Uninit(void)
{
	CMagicCircle::Uninit();
}

//================================================
//更新処理
//================================================
void CWarpCircle::Update(void)
{
	CMagicCircle::Update();

	//エフェクト生成処理
	EffectSpawn();

	//上に上がる3Dオブジェクト生成処理
	Object3DSpawn();

	//プレイヤーとの当たり判定
	if (CollisionPlayer() == true)
	{
		//敵をすべて倒していたら
		if (CEnemy::GetNum() == 0)
		{
			//フェード取得処理
			CFade *pFade;
			pFade = CManager::GetInstance()->GetFade();

			//フェードしていないとき
			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				//現在のモードによって遷移先を変更
				switch (CManager::GetMode())
				{
				case CManager::MODE::GAME01:
					pFade->SetFade(CManager::MODE::GAME02);
					break;
				case CManager::MODE::GAME02:
					pFade->SetFade(CManager::MODE::GAME03);
					break;
				default:
					break;
				}
			}
		}
		else
		{//敵が残っていたら
			if (m_pUiMessage == nullptr)
			{
				//メッセージUIの作成
				m_pUiMessage = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
					                       D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
					                       CObject::PRIORITY_UI, CUi::TYPE::MESSAGE_02);
			}
			
		}
	}
	else
	{//プレイヤーに当たっていないとき
		if (m_pUiMessage != nullptr)
		{
			
			m_pUiMessage = nullptr;
		}
	}
}

//================================================
//描画処理
//================================================
void CWarpCircle::Draw(void)
{
	CMagicCircle::Draw();
}

//================================================
//生成処理
//================================================
CWarpCircle* CWarpCircle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	//インスタンスの生成
	CWarpCircle *pWarpCircle = nullptr;
	if (pWarpCircle == nullptr)
	{
		pWarpCircle = new CWarpCircle();
		if (pWarpCircle != nullptr)
		{
			pWarpCircle->m_rot = rot;
			pWarpCircle->Init(pos, size);
		}
	}
	return pWarpCircle;
}

//================================================
//プレイヤーとの当たり判定
//================================================
bool CWarpCircle::CollisionPlayer(void)
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

//================================================
//エフェクト生成処理
//================================================
void CWarpCircle::EffectSpawn(void)
{
	//カウンターを加算
	m_nEffectCounter++;
	//規定値よりも大きくなったら
	if (m_nEffectCounter >= WARP_CIRCLE_EFFECT_COUNTER)
	{
		//エフェクトの生成
		for (int nCnteffect = 0; nCnteffect < WARP_CIRCLE_EFFECT_NUM; nCnteffect++)
		{
			float fRot = WARP_CIRCLE_EFFECT_ROT;
			CEffect3D *pEffect3D = nullptr;
			pEffect3D = CEffect3D::Create(D3DXVECTOR3(m_pos.x + cosf(fRot) * m_size.x / 2.0f,
				m_pos.y,
				m_pos.z + sinf(fRot) * m_size.z / 2.0f),
				D3DXVECTOR3(3.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CEffect3D::EFFECT3D_TYPE::CHECK);
			pEffect3D->SetMode(CBillboard::BILLBOARD_MODE::BESIDE_ONLY);
		}
		//0にする
		m_nEffectCounter = 0;
	}
}

//================================================
//上に上がる3Dオブジェクト生成処理
//================================================
void CWarpCircle::Object3DSpawn(void)
{
	//カウンターを加算
	m_nObject3DCounter++;
	//規定値よりも大きくなったら
	if (m_nObject3DCounter >= WARP_CIRCLE_OBJECT3D_COUNTER)
	{
		//0にする
		m_nObject3DCounter = 0;
		//nullptrじゃなかったら
		if (m_pObject3D != nullptr)
		{
			//消す
			m_pObject3D->Uninit();
			m_pObject3D = nullptr;
		}
		//上に上がる3Dポリゴンを生成
		m_pObject3D = CObject3D::Create(m_pos, m_size, m_rot);
		//カラーを設定
		m_pObject3D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
		//テクスチャを設定
		m_pObject3D->BindTexture(m_pTexture);
		//カリングを行わないようにする
		m_pObject3D->SetCulling(false);
		//αテストをする
		m_pObject3D->SetAlphaTest(true);
	}
	else
	{
		//nullptrじゃなかったら
		if (m_pObject3D != nullptr)
		{
			//位置を取得
			D3DXVECTOR3 pos = m_pObject3D->GetPos();
			//カラーを取得
			D3DXCOLOR col = m_pObject3D->GetCol();
			//移動量を加算
			pos.y += WARP_CIRCLE_OBJECT3D_MOVE;
			//色を薄くする
			col.a -= WARP_CIRCLE_OBJECT3D_COLOR_SUBTRACTION;

			//見えなくなったら
			if (col.a <= 0.0f)
			{
				//消す
				m_pObject3D->Uninit();
				m_pObject3D = nullptr;
			}
			else
			{//見えているとき
			 //位置設定
				m_pObject3D->SetPos(pos, m_size);
				//色を設定
				m_pObject3D->SetCol(col);
			}
		}
	}
}

