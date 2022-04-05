//===========================================
//ゲーム01処理
//Authore:加藤瑞葵
//===========================================
#ifndef _GAME01_H_
#define _GAME01_H_
#include "scene.h"
#include "scene2D.h"
#include "main.h"
#include "enemy.h"
#include "mover.h"

//前方宣言
class CScore;
class CNumber;
class CPolygon;
class CLife;
class CBoss;
class CPlayer;
class CUi;

//================================================
//マクロ定義
//================================================
#define STAGE01_MAX_ENEMY	(128)	//ステージ1の敵の最大数
#define STAGE01_MAX_BOSS	(1)		//ステージ1のBOSSの最大数
#define MAX_PAUSE_UI		(3)		//ポーズ中のUIの数

//========================================================
//構造体の定義
//========================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CGame01 : public CScene
{
public:
	//選択肢
	typedef enum
	{
		SELECT_GAME01_PAUSE_TYPE_NONE = 0,
		SELECT_GAME01_PAUSE_TYPE_CONTINUE,		//Coutinue
		SELECT_GAME01_PAUSE_TYPE_EXIT,			//Exit
		SELECT_GAME01_PAUSE_TYPE_MAX			//選択肢最大値
	} SELECT_GAME01_PAUSE_TYPE;

	//ゲームの状態
	typedef enum
	{
		GAME_STATE_NONE = 0,
		GAME_STATE_GAME,		//ゲーム中
		GAME_STATE_CLEAR,		//ゲームクリア
		GAME_STATE_OVER,		//ゲームオーバー
		GAME_STATE_MAX
	} GAME_STATE;

	CGame01();				//コンストラクタ
	~CGame01();				//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static int GetFrame(void);
	static CScore *GetScore(void);
	static CPolygon *GetPolygon(void);
	static CLife *GetLife(void);
	static CBoss *GetBoss(void);
	static bool GetPause(void);						//ポーズ取得処理
	static int GetSelect(void);						//ポーズ中の選択肢取得処理
	GAME_STATE GetState(void);						//ゲームの状態取得処理
	void SetState(GAME_STATE state);				//ゲームの状態設定処理
	static int GetFinishCounter(void);				//終了してからのフレーム数
	
private:
	//メンバ関数
	void State(void);											//状態による処理分け

	static CScore *m_pScore;									//スコアポインタ
	static CPolygon *m_pPolygon;								//ポリゴンポインタ
	static CLife *m_pLife;										//ライフポインタ
	static CBoss *m_pBoss;										//ボスポインタ
	static CUi *m_pUi[MAX_PAUSE_UI];							//UIのポインタ

	static int m_nFrame;										//ゲームを開始して経過したフレーム数
	static int m_nFrameEnemy[STAGE01_MAX_ENEMY];				//敵を出現させるフレーム数保存用
	static int m_nFrameBoss[STAGE01_MAX_BOSS];					//ボスを出現させるフレーム数保存用
	static D3DXVECTOR3 m_enemyPos[STAGE01_MAX_ENEMY];			//敵を出す場所保存用
	static D3DXVECTOR3 m_enemyMove[STAGE01_MAX_ENEMY];			//敵の移動初期値保存用
	static D3DXVECTOR3 m_bossPos[STAGE01_MAX_BOSS];				//ボスを出す場所保存用
	static CEnemy::ENEMY_TYPE m_enemyType[STAGE01_MAX_ENEMY];	//出す敵のタイプ保存用
	static CMover::MOVER_TYPE m_moverType[STAGE01_MAX_ENEMY];	//出す敵の動き方のタイプ保存用
	static int m_nSelect;										//どの選択肢が選択されているか
	static bool m_bPause;										//ポーズ中かどうかのフラグ
	static int m_nFinishCounter;								//ゲーム終了してからのFrameカウント用		
	GAME_STATE m_state;											//ゲームの状態
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_GAME01_H_