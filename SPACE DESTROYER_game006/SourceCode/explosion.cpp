//================================================
//爆発処理
//Authore:加藤瑞葵
//================================================
#include "scene2D.h"
#include "manager.h"
#include "explosion.h"
#include "renderer.h"
#include "texture.h"

//================================================
//静的メンバ変数宣言
//================================================
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

//================================================
//デフォルトコンストラクタ
//================================================
CExplosion::CExplosion(int nPriority) :CScene2D(nPriority)
{
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CExplosion::~CExplosion()
{

}

//================================================
//初期化処理
//================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);

	//オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_EXPLOSION);

	//テクスチャ座標更新
	SetTex(m_nPatternAnim, MAX_PATTERN);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}

//================================================
//更新処理
//================================================
void CExplosion::Update(void)
{
	//カウンター更新
	m_nCounterAnim++;
	if (m_nCounterAnim % PATTERN_FRAME == 0)
	{
		//パターンNo更新
		m_nPatternAnim++;
		//テクスチャ座標更新
		SetTex(m_nPatternAnim , MAX_PATTERN);

		if (m_nPatternAnim > MAX_PATTERN)
		{
			Uninit();
			return;
		}
	}
}

//================================================
//描画処理
//================================================
void CExplosion::Draw(void)
{
	CScene2D::Draw();
}

//================================================
//生成処理
//================================================
CExplosion *CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//インスタンスの生成
	CExplosion *pExplosion = NULL;
	if (pExplosion == NULL)
	{
		pExplosion = new CExplosion;
		if (pExplosion != NULL)
		{
			m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_EXPLOSION);
			pExplosion->Init(pos, size);
			pExplosion->BindTexture(m_pTexture);
		}
	}
	return pExplosion;
}
