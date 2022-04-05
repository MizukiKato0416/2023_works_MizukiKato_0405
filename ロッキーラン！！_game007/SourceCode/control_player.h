#//=============================================================================
// プレイヤーコントロール処理 [control_player.h]
// Author : 加藤瑞葵
//=============================================================================
#ifndef _CONTROL_PLAYER_H_
#define _CONTROL_PLAYER_H_

#include "control.h"

//前方宣言
class CScene;
class CPlayer;

//================================================
// マクロ定義
//================================================
#define PLAYER_JUMP							(5.0f)	// ジャンプ力
#define PLAYER_GRAVITY						(0.3f)	// 重力の大きさ
#define PLAYER_MOVE_SPEED					(0.3f)	// 通常移動の加速度
#define PLAYER_DIVE_SPEED					(1.2f)	// ダイブ中の加速度
#define PLAYER_INTERIA_SUBTRACTION			(0.86f)	// 慣性の減算値
#define PLAYER_MOVE_SPEED_ON_ICE			(0.05f)	// 氷の床での移動の加速度
#define PLAYER_DIVE_SPEED_ON_ICE			(0.35f)	// 氷の床でのダイブ中の加速度
#define PLAYER_INTERIA_SUBTRACTION_ON_ICE	(0.99f)	// 氷の床での慣性の減算値
#define PLAYER_JUMP_SPRING					(12.0f)	// バネを使ったジャンプ力
#define PLAYER_MOVE_FORWARD_SPRING			(6.0f)	// バネを使った時の前進力
#define PLAYER_MOVE_STOP_COUNT				(0.02f)	// プレイヤーの移動量を0にする時の移動量の値
#define PLAYER_DIVE_COUNT					(10)	// プレイヤーのダイブ時間

//*****************************************************************************
// プレイヤーコントロールクラス
//*****************************************************************************
class CControlPlayer : public CControl
{
public:
	//メンバ関数
	CControlPlayer();				// コンストラクタ
	~CControlPlayer();				// デストラクタ
	HRESULT Init(void);				// 初期化処理
	void Uninit(void);				// 終了処理
	void Update(CScene *pScene);	// 更新処理

	static CControlPlayer *Create(void);		//生成処理

private:
	//メンバ関数
	void Move(CPlayer *pPlayer);			//移動処理
	void MoveInteria(CPlayer *pPlayer);		//移動の慣性についての処理
	void Rotate(CPlayer *pPlayer);			//回転処理
	void Dive(CPlayer *pPlayer);			//ダイブ処理
	void Jump(CPlayer *pPlayer);			//ジャンプ処理

	D3DXVECTOR3 m_speed;	// 移動量に加える速さ
	bool m_bJump;			// ジャンプしてるかどうか
	D3DXVECTOR3 m_rot;		//向き
	D3DXVECTOR3 m_moveOld;	//1フレーム前の移動量
	float m_fObjectiveRot;	//目的の向き
	float m_fNumRot;		//向きを変える量
	bool m_bRotate;			//回転しているかどうか
	int m_nDiveTime;		//ダイブしている時間
	bool m_bStop;			//ストップしているかどうか
	bool m_bDive;			//ダイブしてるかどうか
};

#endif	//_CONTROL_PLAYER_H_