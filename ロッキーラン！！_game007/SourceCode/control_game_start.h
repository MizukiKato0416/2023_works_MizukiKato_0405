//=============================================================================
// ゲームGO文字コントロール処理 [control_game_start.h]
// Author : 寺下琉生
//=============================================================================
#ifndef _CONTROL_GAME_START_H_
#define _CONTROL_GAME_START_H_

#include "control.h"

//前方宣言
class CScene;

//================================================
//マクロ定義
//================================================
#define COL_SPEED		(0.025f)	//α値の変動する早さ
#define SMALL_SPEED		(25.0f)		//文字が小さくなる早さ
#define MIN_SIZE		(300.0f)	//最小サイズ

//*****************************************************************************
// ゲームGO文字コントロールクラス
//*****************************************************************************
class CControlGameStart : public CControl
{
public:
	CControlGameStart();					// コンストラクタ
	~CControlGameStart();					// デストラクタ
	HRESULT Init(void);						// 初期化処理
	void Uninit(void);						// 終了処理
	void Update(CScene *pScene);			// 更新処理
	static CControlGameStart *Create();	// 生成処理

private:
	int m_nCount;							// カウント
	D3DXVECTOR3 MIN_Size;					// 最小サイズ
	D3DXCOLOR m_col;						//ポリゴンの色
};

#endif	//_CONTROL_TITLE_LOGO_H_