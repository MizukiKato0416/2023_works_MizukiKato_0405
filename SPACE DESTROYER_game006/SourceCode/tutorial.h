//===========================================
//チュートリアル処理
//Authore:加藤瑞葵
//===========================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
#include "scene.h"
#include "scene2D.h"
#include "main.h"

//前方宣言
class CUi;
class CEnemyItemPower;
class CEnemyItemSpeed;
class CPlayer;

//================================================
//マクロ定義
//================================================
#define MAX_TUTORIAL_UI						(4)								//チュートリアル中に一度に出すUIの最大数
#define TUTORIAL_NEXT_PHASE_COUNTER			(120)							//次のフェーズに進むことができるまでの時間
#define MAX_PLAYER_CONTROL_KEY				(4)								//プレイヤーを動かすキーの数
#define TUTORIAL_ENEMY_POS_X				(SCREEN_WIDTH / 2.0f)			//敵を出すX座標
#define TUTORIAL_ENEMY_POS_Y				(100.0f)						//敵を出すY座標
#define TUTORIAL_ENEMY_ITEM_POWER_POS_X		(SCREEN_WIDTH / 3.0f)			//パワーアップアイテムを生成する敵を出すX座標
#define TUTORIAL_ENEMY_ITEM_POWER_POS_Y		(100.0f)						//パワーアップアイテムを生成する敵を出すY座標
#define TUTORIAL_ENEMY_ITEM_SPEED_POS_X		(SCREEN_WIDTH / 3.0f * 2.0f)	//スピードアップアイテムを生成する敵を出すX座標
#define TUTORIAL_ENEMY_ITEM_SPEED_POS_Y		(100.0f)						//スピードアップアイテムを生成する敵を出すY座標
#define TUTORIAL_PLAYER_POS_X				(SCREEN_WIDTH / 2.0f)			//プレイヤーを出すX座標
#define TUTORIAL_PLAYER_POS_Y				(400.0f)						//プレイヤーを出すY座標
#define MAX_TUTORIL_PAUSE_UI				(3)								//ポーズ中のUIの数

//========================================================
//構造体の定義
//========================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CTutorial : public CScene
{
public:
	//チュートリアルのフェーズ
	typedef enum 
	{
		TUTORIAL_PHASE_NONE = 0,
		TUTORIAL_PHASE_FIRST_EXPLANATION,				//初めの説明
		TUTORIAL_PHASE_PLAYER_CONTROL_EXPLANATION,		//プレイヤーの移動操作説明
		TUTORIAL_PHASE_PLAYER_CONTROL,					//プレイヤーの移動操作
		TUTORIAL_PHASE_PLAYER_SHOOT_EXPLANATION,		//プレイヤーの射撃操作説明
		TUTORIAL_PHASE_PLAYER_SHOOT,					//プレイヤーの射撃操作
		TUTORIAL_PHASE_ITEM_EXPLANATION_000,			//アイテムの説明000
		TUTORIAL_PHASE_ITEM_EXPLANATION_001,			//アイテムの説明001
		TUTORIAL_PHASE_PLAYER_LEVEL_UP_SHOOT,			//レベルアップしたプレイヤーの射撃操作
		TUTORIAL_PHASE_FINISH,							//終了
		TUTORIAL_PHASE_MAX,								//フェーズの最大値
	} TUTORIAL_PHASE;

	//選択肢
	typedef enum
	{
		SELECT_TUTORIAL_PAUSE_TYPE_NONE = 0,
		SELECT_TUTORIAL_PAUSE_TYPE_CONTINUE,		//Coutinue
		SELECT_TUTORIAL_PAUSE_TYPE_EXIT,			//Exit
		SELECT_TUTORIAL_PAUSE_TYPE_MAX			//選択肢最大値
	} SELECT_TUTORIAL_PAUSE_TYPE;

	CTutorial();				//コンストラクタ
	~CTutorial();				//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetEnemyKill(bool bEnemyKill);		//敵を倒したのを設定する処理
	static void SetPowerUp(bool bPowerUp);			//パワーアップしたのをのを設定する処理
	static void SetSpeedUp(bool bSpeedUp);			//スピードアップしたのを設定する処理
	static bool GetPause(void);						//ポーズ取得処理
	static int GetSelect(void);						//ポーズ中の選択肢取得処理
	TUTORIAL_PHASE GetPhase(void);					//フェーズ取得処理
	void Pause(void);								//ポーズに関する処理
	
private:
	//メンバ関数
	void phase(void);								//フェーズごとの処理

	CScene2D *m_pScene2D;							//scene2Dのポインタ
	TUTORIAL_PHASE m_phase;							//フェーズ
	CUi *m_pUi[MAX_TUTORIAL_UI];					//UIのポインタ
	CEnemyItemPower *m_pEnemyItemPower;				//EnemyItemPowerのポインタ
	CEnemyItemSpeed *m_pEnemyItemSpeed;				//EnemyItemSpeedのポインタ
	CPlayer *m_pPlayer;								//Playerのポインタ
	int m_nNextPhaseCounter;						//次のフェーズに行けるようになるまでのカウンター
	bool m_bPlayerMove[MAX_PLAYER_CONTROL_KEY];		//プレイヤーの移動ができたかどうかのフラグ
	bool m_bPlayerShoot;							//プレイヤーの射撃ができたかどうかのフラグ
	static bool m_bEnemyKill;						//敵を倒したかどうか
	static bool m_bPowerUp;							//パワーアップをしたかどうか
	static bool m_bSpeedUp;							//スピードアップをしたかどうか
	static int m_nSelect;							//どの選択肢が選択されているか
	static bool m_bPause;							//ポーズ中かどうかのフラグ
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_TUTORIAL_H_