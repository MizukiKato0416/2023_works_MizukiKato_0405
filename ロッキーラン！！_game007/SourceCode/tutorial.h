//===========================================
//チュートリアル処理
//Authore: UENOYAMA TAIGA
//===========================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
#include "scene.h"
#include "scene2D.h"
#include "main.h"
#include "player.h"

//前方宣言
class CMeshField;
class CMeshSphere;
class CModelSingle;
class CUi;
class CPause;
class CScene3D;

//================================================
//マクロ定義
//================================================
#define TUTORIAL_PLAYER_SPAWN_POS_Y			(60.0f)										//プレイヤー初期位置Y座標
#define TUTORIAL_PLAYER_SPAWN_POS_Z			(-330.0f)									//プレイヤー初期位置Z座標
#define TUTORIAL_PLAYER_SPAWN_POS_X			(200.0f)									//プレイヤー初期位置X座標
#define TUTORIAL_PLAYER_SPAWN_WIDTH			(400.0f)									//プレイヤーのスポーン間隔
#define TUTORIAL_START_FLOOR_POS_Z			(-330.0f)									//スタート床のZ座標
#define TUTORIAL_MIDDLE_FLOOR_FRONT_POS_Z	(25.0f)										//ミドル床（手前）のZ座標
#define TUTORIAL_MIDDLE_FLOOR_BACK_POS_Z	(625.0f)									//ミドル床（奥）のZ座標
#define TUTORIAL_GOAL_FLOOR_POS_Z			(985.0f)									//ゴール床のZ座標
#define TUTORIAL_GOAL_POLE_POS_X			(280.0f)									//ゴール柱のX座標
#define TUTORIAL_GOAL_POLE_POS_Y			(0.0f)										//ゴール柱のY座標
#define TUTORIAL_GOAL_POLE_POS_Z			(TUTORIAL_GOAL_FLOOR_POS_Z -99.0f)			//ゴール柱のZ座標
#define TUTORIAL_GOAL_FLAG_POS_X			(0.0f)										//ゴール旗のX座標
#define TUTORIAL_GOAL_FLAG_POS_Y			(TUTORIAL_GOAL_POLE_POS_Y + 200.0f)			//ゴール旗のX座標
#define TUTORIAL_GOAL_FLAG_POS_Z			(TUTORIAL_GOAL_FLOOR_POS_Z - 99.0f)			//ゴール旗のX座標
#define TUTORIAL_FENCE_POS_X				(310.0f)									//フェンスのX座標
#define TUTORIAL_FENCE_POS_Y				(10.0f)										//フェンスのY座標
#define TUTORIAL_MAX_MODEL					(40)										//ステージに配置するモデルの最大数
#define TUTORIAL_EXPLANATION_POS_X			(270.0f)									//操作説明のposX
#define TUTORIAL_EXPLANATION_POS_Y			(120.0f)									//操作説明のposY
#define TUTORIAL_EXPLANATION_SIZE_X			(548.0f * 0.8f)								//操作説明のsizeX
#define TUTORIAL_EXPLANATION_SIZE_Y			(305.0f * 0.8f)								//操作説明のsizeY
#define TUTORIAL_PLAYERNUMBER_TEX_POS_Y		(60.0f)										//プレイヤーナンバーのposY
#define TUTORIAL_PLAYERNUMBER_TEX_SIZE_X	(360.0f)									//プレイヤーナンバーのsizeX
#define TUTORIAL_PLAYERNUMBER_TEX_SIZE_Y	(300.0f)									//プレイヤーナンバーのsizeY
#define TUTORIAL_1P_TEX_POS_X				(80.0f)										//1PテクスチャのposX
#define TUTORIAL_2P_TEX_POS_X				(1190.0f)									//2PテクスチャのposX
#define TUTORIAL_CLEAR_POS_X				(800.0f)									//クリアのposX
#define TUTORIAL_CLEAR_POS_Y				(400.0f)									//クリアのposY
#define TUTORIAL_MAX_UI_NUM					(4)											//UIの最大数
#define TUTORIAL_NEXT_SCENE_COUNT			(120)										//次のシーンに進むまでのカウント
#define TUTORIAL_WORLD_SIZE					(20000.0f)									//チュートリアルの世界の大きさ
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
	//フェーズ
	typedef enum
	{
		TUTORIAL_PHASE_NONE = 0,
	} TUTORIAL_PHASE;

	CTutorial();				//コンストラクタ
	~CTutorial();				//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	void SetGoal(bool bGoal);
	bool GetGoal();
private:
	//メンバ関数
	CUi *m_apUi[TUTORIAL_MAX_UI_NUM];					//UIのポインタ
	CMeshField *m_pMeshField;							//メッシュフィールドのポインタ
	CMeshSphere *m_pMeshSphere;							//メッシュスフィアのポインタ
	CPlayer *m_apPlayer[MAX_PLAYER];								//プレイヤーのポインタ
	CModelSingle *m_apModelSingle[TUTORIAL_MAX_MODEL];	//モデルのポインタ
	CPause *m_pPause;									//ポーズのポインタ
	CScene3D *m_pScene3D;								//Scene3Dのポインタ

	int m_nNumScene2D;									//出てるポリゴンの総数
	int m_nSelect;										//今選んでいるポリゴン
	bool m_bGoal;										//ゴールしたかどうか
	int m_nFrame;										//フレーム数

};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_TUTORIAL_H_