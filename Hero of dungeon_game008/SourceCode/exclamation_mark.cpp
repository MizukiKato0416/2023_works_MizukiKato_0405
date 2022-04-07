//================================================
//ビックリマーク処理
//Author:KatoMizuki
//================================================
#include "exclamation_mark.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//================================================
//マクロ定義
//================================================


//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CExclamationMark::CExclamationMark(int nPriority) :CBillboard(nPriority)
{
	m_addSize = { 0.0f, 0.0f, 0.0f };
	m_size = { 0.0f, 0.0f, 0.0f };
	m_pObject = nullptr;
	m_nLife = 0;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CExclamationMark::~CExclamationMark()
{

}

//================================================
//初期化処理
//================================================
HRESULT CExclamationMark::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CBillboard::Init(pos,size);

	//オブジェクトの種類を設定
	SetObjType(CObject::OBJTYPE::EXCLAMATION_MARK);

	//αテストを行う設定
	SetAlphaTest(true);
	//ライティングを無効にする
	SetLighting(false);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CExclamationMark::Uninit(void)
{
	CBillboard::Uninit();
}

//================================================
//更新処理
//================================================
void CExclamationMark::Update(void)
{
	//寿命を減らす
	m_nLife--;

	//寿命が0以下になったら
	if (m_nLife <= 0)
	{
		//0にする
		m_nLife = 0;
		//消す
		Uninit();
		return;
	}

	//位置とサイズを取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();

	//対象のオブジェクトの位置を取得して現在の位置に代入
	D3DXVECTOR3 objectPos = m_pObject->GetPos();
	pos.x = objectPos.x;
	pos.z = objectPos.z;

	//サイズを加算
	size += m_addSize;

	//既定の値以上になったら
	if (size.x >= m_size.x)
	{
		//既定の値にする
		size.x = m_size.x;
	}
	if (size.y >= m_size.y)
	{
		//既定の値にする
		size.y = m_size.y;
	}

	//位置の設定
	SetPos(pos,size);
}

//================================================
//描画処理
//================================================
void CExclamationMark::Draw(void)
{
	CBillboard::Draw();
}

//================================================
//生成処理
//================================================
CExclamationMark* CExclamationMark::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 initSize, D3DXVECTOR3 addSize, CObject *pObject, int nLife)
{
	//インスタンスの生成
	CExclamationMark *pExclamationMark = nullptr;
	if (pExclamationMark == nullptr)
	{
		pExclamationMark = new CExclamationMark();
		if (pExclamationMark != nullptr)
		{
			pExclamationMark->m_size = size;
			pExclamationMark->m_addSize = addSize;
			pExclamationMark->m_pObject = pObject;
			pExclamationMark->m_nLife = nLife;
			pExclamationMark->Init(pos, initSize);
			pExclamationMark->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_EXCLAMATION_MARK");
		}
	}
	return pExclamationMark;
}
