#//=============================================================================
// 上下する壁のコントロール処理 [control_up_down_wall.h]
// Author : KUSAKARI KAKERU
//=============================================================================
#ifndef _CONTROL_UP_DOWN_WALL_H_
#define _CONTROL_UP_DOWN_WALL_H_

#include "control.h"

//前方宣言
class CScene;

//================================================
// マクロ定義
//================================================
#define MOVE_UPDOWN_WALL_SPEED	(0.7f)	// 移動速度
#define MAX_UPDOWN_WALL_SPEED	(0.7f)	// 移動速度の最大値

//*****************************************************************************
// キーボードクラス
//*****************************************************************************
class CControlUpDownWall : public CControl
{
public:
	typedef enum
	{
		UP_WALL = 0,		// 最初に上に上昇する壁
		DOWN_WALL,			// 最初に下に下降する壁
		UP_DOWN_WALL_MAX,
	} UP_DOWN_WALL;

	CControlUpDownWall();				// コンストラクタ
	~CControlUpDownWall();				// デストラクタ
	HRESULT Init(void);					// 初期化処理
	void Uninit(void);					// 終了処理
	void Update(CScene *pScene);		// 更新処理

	static CControlUpDownWall *Create(UP_DOWN_WALL type, float moveLimit);	// 生成処理

private:
	bool m_bUpDown;			// どの方向に移動するか
	float m_fMoveLength;	// 移動した長さ
	float m_moveLimit;		// 移動できる範囲
	int m_nWaitTime;		// 移動後の待機時間
};

#endif	//_CONTROL_UP_DOWN_WALL_H_