//=============================================================================
// タイトルエンター文字コントロール処理 [control_title_enter.cpp]
// Author : 寺下琉生
//=============================================================================
#include "control_game_start.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "title.h"
#include "ui.h"
#include "scene.h"
#include "game01.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CControlGameStart::CControlGameStart()
{
	m_nCount = 0;
	MIN_Size = D3DXVECTOR3(300.0f, 300.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CControlGameStart::~CControlGameStart()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CControlGameStart::Init(void)
{
	m_nCount = 0;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CControlGameStart::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CControlGameStart::Update(CScene *pScene)
{
	//引数のポインタをUiクラスのポインタにキャスト
	CUi *pUi = NULL;
	pUi = (CUi*)pScene;

	m_nCount++;

	//UIの取得→オブジェクトの位置を取得
	D3DXVECTOR3 pos;
	pos = pUi->GetPos();

	//UIの取得→オブジェクトのサイズを取得
	D3DXVECTOR3 size;
	size = pUi->GetSize();

	// アルファ値を上げる(不透明にする)
	m_col.a += 0.025f;
	size.x -= SMALL_SPEED;
	size.y -= SMALL_SPEED;
	if (size.y <= MIN_SIZE)
	{
		size.y = MIN_SIZE;
	}
	if (size.x <= MIN_SIZE)
	{
		size.x = MIN_SIZE;
	}

	if (m_col.a > 1.0f && m_nCount >= 70)
	{
		m_nCount = 0;
		m_col.a = 1.0f;
	}

	// m_fAlphaの値を透明度に入れる
	pUi->SetCol(m_col);
	// 位置やサイズの設定
	pUi->SetPos(pos, size);
}

//=============================================================================
// 生成処理
//=============================================================================
CControlGameStart *CControlGameStart::Create()
{
	//インスタンスの生成
	CControlGameStart *pControlGameStart = NULL;

	if (pControlGameStart == NULL)
	{
		pControlGameStart = new CControlGameStart;

		if (pControlGameStart != NULL)
		{
			pControlGameStart->Init();
		}
	}

	return pControlGameStart;
}