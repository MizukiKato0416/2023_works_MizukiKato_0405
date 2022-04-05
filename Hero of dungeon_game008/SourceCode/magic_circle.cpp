//================================================
//魔法陣の処理
//Author:KatoMizuki
//================================================
#include "magic_circle.h"
#include "manager.h"
#include "renderer.h"
#include "effect3D.h"
#include "texture.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CMagicCircle::CMagicCircle(int nPriority) :CObject3D(nPriority)
{
	m_rotateType = ROTATE_TYPE::NONE;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CMagicCircle::~CMagicCircle()
{

}

//================================================
//初期化処理
//================================================
HRESULT CMagicCircle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CObject3D::Init(pos,size);

	//オブジェクトの種類を設定
	SetObjType(CObject::OBJTYPE::MAGIC_CIRCLE);
	
	//変数初期化
	m_rotateType = ROTATE_TYPE::Y;

	//ライティングを無効にする
	SetLighting(false);
	//αテストを有効にする
	SetAlphaTest(true);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CMagicCircle::Uninit(void)
{
	CObject3D::Uninit();
}

//================================================
//更新処理
//================================================
void CMagicCircle::Update(void)
{
	switch (m_rotateType)
	{
	case CMagicCircle::ROTATE_TYPE::NONE:
		break;
	case CMagicCircle::ROTATE_TYPE::X:
		//回転させる
		m_rot.x += 0.01f;

		if (m_rot.x >= D3DX_PI)
		{
			m_rot.x -= D3DX_PI * 2.0f;
		}
		break;
	case CMagicCircle::ROTATE_TYPE::Y:
		//回転させる
		m_rot.y += 0.01f;

		if (m_rot.y >= D3DX_PI)
		{
			m_rot.y -= D3DX_PI * 2.0f;
		}
		break;
	case CMagicCircle::ROTATE_TYPE::Z:
		//回転させる
		m_rot.z += 0.01f;

		if (m_rot.z >= D3DX_PI)
		{
			m_rot.z -= D3DX_PI * 2.0f;
		}
		break;
	default:
		break;
	}
}

//================================================
//描画処理
//================================================
void CMagicCircle::Draw(void)
{
	CObject3D::Draw();
}

//================================================
//生成処理
//================================================
CMagicCircle* CMagicCircle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	//インスタンスの生成
	CMagicCircle *pMagicCircle = nullptr;
	if (pMagicCircle == nullptr)
	{
		pMagicCircle = new CMagicCircle();
		if (pMagicCircle != nullptr)
		{
			pMagicCircle->m_rot = rot;
			pMagicCircle->Init(pos, size);
		}
	}
	return pMagicCircle;
}
