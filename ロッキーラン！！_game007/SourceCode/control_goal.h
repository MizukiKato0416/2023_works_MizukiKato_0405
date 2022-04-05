//=============================================================================
// ゴールのポリゴンを出す処理 [control_goal.h]
// Author : 一戸健
//=============================================================================
#ifndef _CONTROL_GOAL_H_
#define _CONTROL_GOAL_H_

#include "control.h"

//前方宣言
class CScene;

//*****************************************************************************
// タイトルロゴコントロールクラス
//*****************************************************************************
class CControlGoal : public CControl
{
public:
	CControlGoal();						// コンストラクタ
	~CControlGoal();					// デストラクタ
	HRESULT Init(void);					// 初期化処理
	void Uninit(void);					// 終了処理
	void Update(CScene *pScene);		// 更新処理
	static CControlGoal *Create();		// 生成処理

private:
	float m_fMaxMove;
};

#endif	//_CONTROL_GOAL_H_