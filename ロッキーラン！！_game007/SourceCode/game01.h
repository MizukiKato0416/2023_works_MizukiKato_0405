//===========================================
//ゲーム処理
//Author:加藤瑞葵
//===========================================
#ifndef _GAME01_H_
#define _GAME01_H_
#include "scene.h"
#include "scene2D.h"
#include "main.h"
#include "player.h"

//前方宣言
class CMeshField;
class CMeshSphere;
class CScore;
class CModelSingle;
class CUi;
class CTimer;
class CPause;
class CScene3D;

//================================================
//マクロ定義
//================================================
#define GAME_MAX_UI_NUM					(3)			//UIの最大数

#define GAME_START_FLOOR_POS_Z			(-1870.0)	//スタート床のZ座標
#define GAME_FENCE_POS_X				(310.0f)	//フェンスのX座標
#define GAME_FENCE_POS_Y				(10.0f)		//フェンスのY座標

#define GAME_PLAYERNUMBER_TEX_POS_Y		(60.0f)		//プレイヤーナンバーのposY
#define GAME_PLAYERNUMBER_TEX_SIZE_X	(360.0f)	//プレイヤーナンバーのsizeX
#define GAME_PLAYERNUMBER_TEX_SIZE_Y	(300.0f)	//プレイヤーナンバーのsizeY
#define GAME_1P_TEX_POS_X				(80.0f)		//1PテクスチャのposX
#define GAME_2P_TEX_POS_X				(1190.0f)	//2PテクスチャのposX

#define GAME_SCAFFOLD_1ST_POS_X			(-260.0f)	//足場の1列目のX座標(横一列左）
#define GAME_SCAFFOLD_2ND_POS_X			(-195.0f)	//足場の2列目のX座標(横一列左）
#define GAME_SCAFFOLD_3RD_POS_X			(-130.0f)	//足場の3列目のX座標(横一列左）
#define GAME_SCAFFOLD_4TH_POS_X			(-65.0f)	//足場の4列目のX座標(横一列左）
#define GAME_SCAFFOLD_MOVE_X			(130.0f)	//足場の横隣とのX幅
#define GAME_SCAFFOLD_POS_Z				(-1650.0f)	//足場の1列目のZ座標
#define GAME_SCAFFOLD_MOVE_Z			(170.0f)	//足場の次の列とのZ幅

#define GAME_FLOOR_ICE_POS_X			(-280.0f)	//氷の床の1列目のX座標(横一列左）
#define GAME_FLOOR_ICE_MOVE_X			(80.0f)		//氷の床の1列目を基準にこの数字を足せば綺麗に並ぶ
#define GAME_FLOOR_ICE_POS_Y			(0.0f)		//氷の床の1列目のY座標
#define GAME_FLOOR_ICE_POS_Z			(-800.0f)	//氷の床の1列目のZ座標
#define GAME_FLOOR_ICE_MOVE_Z			(80.0f)		//氷の床の一列目を基準にこの数字を足せば綺麗に並ぶ

#define GAME_MIDDLE_FLOOR_POS_Z			(250.0f)	//ミドル床（一個目）のZ座標
#define GAME_MIDDLE_FLOOR_MOVE_Z		(500.0f)	//ミドル床の一個目を基準にこの数字を足せば綺麗に並ぶ

#define GAME_WALL_UPDOWN_POS_X			(-213.0f)	//上下壁の一列目X座標(横一列左）
#define GAME_WALL_UPDOWN_MOVE_X			(142.0f)	//上下壁を等間隔で置くための数値
#define GAME_WALL_UPDOWN_POS_Z			(200.0f)	//上下壁の一列目のZ座標
#define GAME_WALL_UPDOWN_MOVE_Z			(500.0f)	//上下壁を等間隔で置くための数値
#define GAME_WALL_PILLAR_POS_X			(-284.0f)	//上下壁の一列目Z座標(横一列左）
#define GAME_WALL_PILLAR_MOVE_X			(142.0f)	//上下壁を等間隔で置くための数値

#define GAME_FLOOR_DISAPPEAR_POS_X		(-280.0f)	//消える床の一列目のX座標(横一列左）
#define GAME_FLOOR_DISAPPEAR_MOVE_X		(80.0f)		//消える床の一列目を基準にこの数字を足せば綺麗に並ぶ
#define GAME_FLOOR_DISAPPEAR_POS_Y		(0.0f)		//消える床の一列目のY座標
#define GAME_FLOOR_DISAPPEAR_POS_Z		(1540.0f)	//消える床の一列目のZ座標
#define GAME_FLOOR_DISAPPEAR_MOVE_Z		(80.0f)		//消える床の一列目を基準にこの数字を足せば綺麗に並ぶ

#define GAME_GOAL_FLOOR_POS_Y			(150.0f)	//ゴール床のY座標
#define GAME_GOAL_FLOOR_POS_Z			(2710.0f)	//ゴール床のZ座標

#define GAME_POLE_POS_X					(280.0f)	//ゴール柱のX座標
#define GAME_POLE_POS_Y					(0.0f)		//ゴール柱のY座標

#define GAME_SPRING_POS_X				(150.0f)	//バネのposX
#define GAME_SPRING_POS_Z				(2450.0f)	//バネのposZ

#define GAME_CHECKPOINT01_POS_X			(310.0f)	//チェックポイント01のposX
#define GAME_CHECKPOINT01_POS_Y			(60.0f)		//チェックポイント01のposY
#define GAME_CHECKPOINT01_POS_Z			(14.0f)		//チェックポイント01のposZ
#define GAME_CHECKPOINT02_POS_X			(310.0f)	//チェックポイント02のposX
#define GAME_CHECKPOINT02_POS_Y			(60.0f)		//チェックポイント02のposY
#define GAME_CHECKPOINT02_POS_Z			(1487.0f)	//チェックポイント02のposZ

#define GAME_SEPARATE_MESH				(20000.0f)	//メッシュフィールドとメッシュスフィアの分割数

#define GAME_MAX_MODEL					(300)		//ステージに配置するモデルの最大数
#define GAME_COUNT_DOWN_COUNT			(60)		//カウントダウンを表示する時間
#define GAME_COUNT_DOWN_POS_Y			(240)		//カウントダウンのY座標
#define GAME_NEXT_SCENE_COUNT			(300)		//次のシーンに進むまでのカウント
#define GAME_PLAYER_CREATE_POS_Y		(40.0f)		//プレイヤー生成のy座標
#define GAME_PLAYER_INITCREATE_POS_Z	(-1870.0f)	//スタート地点のプレイヤー生成のz座標
#define GAME_PLAYER_CHECK_01_POS_Z		(50.0f)		//チェックポイント1地点のプレイヤー生成のz座標
#define GAME_PLAYER_INITCREATE_POS_X	(200.0f)	//スタート地点のプレイヤー1の生成のx座標
#define GAME_PLAYER_INITCREATE_WIDTH	(400.0f)	//スタート地点のプレイヤーの生成のx座標の間隔

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
	//フェーズ
	typedef enum
	{
		GAME01_PHASE_NONE = 0,
		GAME01_PHASE_SHOW_STAGE,	//ステージを見せる
		GAME01_PHASE_3,				//カウントダウン3
		GAME01_PHASE_2,				//カウントダウン2
		GAME01_PHASE_1,				//カウントダウン1
		GAME01_PHASE_GO,			//カウントダウンスタート
		GAME01_PHASE_CLEAR,			//ゲームクリア
		GAME01_PHASE_OVER,			//ゲームオーバー
		GAME01_PHASE_MAX
	} GAME01_PHASE;

	//氷の床のパターン
	typedef enum
	{
		ICE_FLOOR_PATTERN_NONE = 0,
		ICE_FLOOR_PATTERN_1,
		ICE_FLOOR_PATTERN_2,
		ICE_FLOOR_PATTERN_3,
		ICE_FLOOR_PATTERN_MAX
	} ICE_FLOOR_PATTERN;

	CGame01(int nPriority = PRIORITY_NONE);		//コンストラクタ
	~CGame01();									//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	GAME01_PHASE GetPhase(void);			//フェーズ取得処理
	void SetPhase(GAME01_PHASE phase);		//フェーズ設定処理
	bool GetGame(void);						//ゲーム中かどうか取得処理


private:
	//メンバ関数
	void Phase(void);									//フェーズ処理
	void Respawn(void);									//リスポーン処理

	CMeshField *m_pMeshField;							//メッシュフィールドのポインタ
	CMeshSphere *m_pMeshSphere;							//メッシュスフィアのポインタ
	CPlayer *m_apPlayer[MAX_PLAYER];					//プレイヤーのポインタ
	CModelSingle *m_apModelSingle[GAME_MAX_MODEL];	    //モデルのポインタ
	CScore *m_pScore;									//スコアのポインタ
	CTimer *m_pTime;									//タイムのポインタ
	CUi *m_apUi[GAME_MAX_UI_NUM];						//UIのポインタ
	CPause *m_pPause;									//ポーズのポインタ
	CScene3D *m_pScene3D;								//Scene3Dのポインタ
	int m_nNumScene2D;									//出てるポリゴンの総数
	int m_nSelect;										//今選んでいるポリゴン
	GAME01_PHASE m_phase;								//フェーズ
	int m_nFrame;										//フレーム数
	int m_nTime;										//タイム用フレーム数カウント変数
	bool m_bGame;										//ゲーム中かどうかのフラグ
	ICE_FLOOR_PATTERN m_icePattern;
};

#endif // !_GAME01_H_