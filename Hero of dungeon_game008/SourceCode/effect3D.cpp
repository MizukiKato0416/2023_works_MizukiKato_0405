//================================================
//パーティクル処理
//Author:KatoMizuki
//================================================
#include "effect3D.h"
#include "manager.h"
#include "renderer.h"
#include "control_effect_check.h"
#include "control_effect_hit.h"
#include "control_effect_thunder.h"
#include "control_effect_flash.h"
#include "control_effect_fire.h"
#include "control_effect_explosion.h"
#include "texture.h"

//================================================
//マクロ定義
//================================================
#define EFFECT3D_DRAW_DIFFERE		(1000)	//エフェクトの描画する範囲


//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CEffect3D::CEffect3D(int nPriority) :CBillboard(nPriority)
{
	m_type = EFFECT3D_TYPE::NONE;
	m_pControl = nullptr;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CEffect3D::~CEffect3D()
{

}

//================================================
//初期化処理
//================================================
HRESULT CEffect3D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CBillboard::Init(pos,size);

	//オブジェクトの種類を設定
	SetObjType(CObject::OBJTYPE::EFFECT_3D);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CEffect3D::Uninit(void)
{
	CBillboard::Uninit();
	if (m_pControl != nullptr)
	{
		m_pControl->Uninit();
		m_pControl = nullptr;
	}
}

//================================================
//更新処理
//================================================
void CEffect3D::Update(void)
{
	if (m_pControl != nullptr)
	{
		//コントロールクラス更新処理を呼び出す
		m_pControl->Update(this);

		if (m_pControl != nullptr)
		{
			//位置に移動量を割り当てる
			m_pos += m_pControl->GetMove();
			//位置の設定
			CObject::SetPos(m_pos);
		}
	}
}

//================================================
//描画処理
//================================================
void CEffect3D::Draw(void)
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
			//オブジェクトの位置を取得
			D3DXVECTOR3 posObj = pObject->GetPos();

			//自身から対象のオブジェクトまでの距離を求める
			float fRadius = sqrtf((posObj.x - m_pos.x) * (posObj.x - m_pos.x) +
				                  (posObj.z - m_pos.z) * (posObj.z - m_pos.z));

			//デバイスのポインタ
			LPDIRECT3DDEVICE9 pDevice;
			//デバイスの取得
			pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

			if (m_type == EFFECT3D_TYPE::CHECK)
			{
				//求めた距離が既定の数値以下だったら
				if (fRadius <= EFFECT3D_DRAW_DIFFERE)
				{
					//αブレンディングを加算合成に設定
					pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
					pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
					pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

					//ライティングを無効にする
					pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

					//アルファテスト
					pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
					pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
					pDevice->SetRenderState(D3DRS_ALPHAREF, 50);

					//Zバッファの書き込み
					pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

					CBillboard::Draw();

					//Zテストを元に戻す
					pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

					//ライティングを有効にする
					pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

					//アルファテスト元に戻す
					pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
					pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
					pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

					//aブレンディングを通常に戻す
					pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
					pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);
					pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
				}
			}
			else
			{
				//αブレンディングを加算合成に設定
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

				//ライティングを無効にする
				pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

				//アルファテスト
				pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
				pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
				pDevice->SetRenderState(D3DRS_ALPHAREF, 50);

				//Zバッファの書き込み
				pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

				CBillboard::Draw();

				//Zテストを元に戻す
				pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

				//ライティングを有効にする
				pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

				//アルファテスト元に戻す
				pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
				pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
				pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

				//aブレンディングを通常に戻す
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			}
		}
		//次のオブジェクトに進める
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}

//================================================
//生成処理
//================================================
CEffect3D* CEffect3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, EFFECT3D_TYPE type)
{
	//インスタンスの生成
	CEffect3D *pEffect3D = nullptr;
	if (pEffect3D == nullptr)
	{
		pEffect3D = new CEffect3D();
		if (pEffect3D != nullptr)
		{
			pEffect3D->m_type = type;
			pEffect3D->m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pEffect3D->Init(pos, size);

			//種類によってどのコントロールクラスの派生クラスを割り当てるかを決める
			switch (pEffect3D->m_type)
			{
			case EFFECT3D_TYPE::NONE:
				pEffect3D->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_EFFECT_3D");
				break;
			case EFFECT3D_TYPE::CHECK:
				pEffect3D->m_pControl = CControlEffectCheck::Create(pEffect3D);
				pEffect3D->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_EFFECT_3D");
				break;
			case EFFECT3D_TYPE::HIT:
				pEffect3D->m_pControl = CControlEffectHit::Create(pEffect3D);
				pEffect3D->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_EFFECT_HIT");
				break;
			case EFFECT3D_TYPE::THUNDER:
				pEffect3D->m_pControl = CControlEffectThunder::Create(pEffect3D);
				pEffect3D->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_EFFECT_3D_002");
				break;
			case EFFECT3D_TYPE::FLASH:
				pEffect3D->m_pControl = CControlEffectFlash::Create(pEffect3D);
				pEffect3D->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_EFFECT_3D");
				break;
			case EFFECT3D_TYPE::FIRE:
				pEffect3D->m_pControl = CControlEffectFire::Create(pEffect3D);
				pEffect3D->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_EFFECT_FIRE");
				break;
			case EFFECT3D_TYPE::EXPLOSION:
				pEffect3D->m_pControl = CControlEffectExplosion::Create(pEffect3D);
				pEffect3D->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_EFFECT_3D");
				break;
			default:
				pEffect3D->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_EFFECT_3D");
				break;
			}
			pEffect3D->SetCol(col);
		}
	}
	return pEffect3D;
}
