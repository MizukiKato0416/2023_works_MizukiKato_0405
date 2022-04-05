//=======================================================================
//ボスに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#ifndef _BOSS_H_
#define _BOSS_H_
#include "main.h"
#include "effect.h"

//========================================================
//マクロ定義
//========================================================
#define BOSS_SPEED (4.0f)								//モデルの速さ
#define BOSS_SEARCH (1500.0f)							//プレイヤーを探し出す範囲
#define BOSS_SEARCH_ATTACK (1500.0f)					//プレイヤーを攻撃をする範囲
#define BOSS_ATTACK (1500.0f)							//プレイヤーに攻撃をする範囲
#define BOSS_DAMAGE (1500.0f)							//プレイヤーに吹っ飛ばされる距離
#define BOSS_MAX_TEXTURE (256)							//テクスチャの最大数
#define MAX_BOSS_MODEL (10)							//モデルの最大数
#define MAX_BOSS (4)									//敵の最大数
#define MAX_BOSS_LIFE (50)								//敵のライフの最大数
#define GRAVITY (0.3f)									//重力
#define BOSS_JUMP (12.0f)								//ジャンプ力
#define BOSS_RAND (float (rand() % 629 + -314) / 100)	//ランダム値
#define BOSS_STOP_TIME (rand() % 300 + 150)			//敵がストップしてる時間
#define BOSS_R (150.0f)							//敵ボスの当たり判定の半径

//========================================================
//ボスの種類
//========================================================
typedef enum
{
	BOSSTYPE_NOMAL = 0,	//ノーマル
	BOSSTYPE_BOSS,			//ボス
} BOSSTYPE;

//========================================================
//動きの種類
//========================================================
typedef enum
{
	BOSS_MOVETYPE_MOVE = 0,	//動く
	BOSS_MOVETYPE_STOP,		//止まる
	BOSS_MOVETYPE_TURN,		//回る
	BOSS_MOVETYPE_TO_PLAYER_TURN,		//プレイヤーの方向に向く
	BOSS_MOVETYPE_ATTACK,		//攻撃
	BOSS_MOVETYPE_DAMAGE,		//ダメージ食らったとき
	BOSS_MOVETYPE_MAX,
} BOSS_MOVETYPE;


//========================================================
//モーションの種類
//========================================================
typedef enum
{
	BOSS_MOTIONTYPE_NEUTRAL = 0,		//ニュートラルモーション
	BOSS_MOTIONTYPE_MOVE,				//移動モーション
	BOSS_MOTIONTYPE_BULLET,				//銃撃モーション
	BOSS_MOTIONTYPE_BULLET_BIG,			//銃撃モーション
	BOSS_MOTIONTYPE_DAMAGE,				//被弾モーション

	BOSS_MOTION_MAX,
} BOSS_MOTIONTYPE;


//========================================================
//構造体の定義
//========================================================

//銃の構造体
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 rot;						//向き
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
} BOSSBULLET;

//キーの構造体
typedef struct
{
	float fPosX;	//位置X
	float fPosY;	//位置Y
	float fPosZ;	//位置Z
	float fRotX;	//向きX
	float fRotY;	//向きY
	float fRotZ;	//向きZ
} BOSS_KEY;

//キー情報の構造体
typedef struct
{
	int nFrame;		//再生フレーム
	BOSS_KEY aKey[MAX_BOSS_MODEL];		//各モデルのキー要素(パーツの最大数)
} BOSS_KEY_INFO;

//モーション情報の構造体
typedef struct
{
	bool bLoop;						//ループするかどうか
	int nNumKey;					//キーの総数
	BOSS_KEY_INFO aKeyInfo[128];	//キーの情報
} BOSS_MOTION_INFO;

//モデルの構造体
typedef struct
{
	LPD3DXMESH pMesh;				//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER pBuffMat;			//マテリアル(材質情報)へのポインタ
	DWORD nNumMat;					//マテリアル数
	LPDIRECT3DTEXTURE9 pTexture[BOSS_MAX_TEXTURE];	//テクスチャへのポインタ
	D3DXVECTOR3	pos;				//位置
	D3DXVECTOR3 rot;				//向き
	D3DXMATRIX mtxWorld;			//ワールドマトリックス
	int nIdxModelParent;			//親のインデックス
} BOSS_Model;

//敵の構造体
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 posOld;						//前の位置
	D3DXVECTOR3 posPlayer;					//プレイヤーの位置保存
	D3DXVECTOR3 rot;						//向き
	D3DXVECTOR3 move;						//移動量
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
	BOSS_Model aModel[MAX_BOSS_MODEL];			//モデル(パーツ)
	int nNumModel;							//モデル(パーツ)数
	BOSS_MOTION_INFO aMotionInfo[BOSS_MOTION_MAX];	//モーション情報
	int nNumMotion;							//モーション数
	int nCntMove;							//動きのランダム性に必要
	BOSS_MOTIONTYPE MotionType;			//現在のモーションタイプ
	BOSS_MOTIONTYPE MotionTypeOld;			//1つ前のモーションタイプ
	BOSS_MOVETYPE MoveType;				//敵の動きの種類
	bool bLoopMotion;						//ループするかどうか
	int nNumKey;							//キー数
	int nKey;								//キーNo,(現在のキー)
	float fCounterMotion;					//モーションのカウンター
	bool bJump;								//ジャンプしているかどうか
	float fWidth;							//幅
	float fHeight;							//高さ
	float fDepth;							//奥行
	float frotVecX;							//プレイヤーの角度を求めるためのベクトル
	float frotVecZ;							//プレイヤーの角度を求めるためのベクトル
	float fToPlayerR;						//プレイヤーとの距離
	float fDifferRot;						//目的と現在のrotの差
	int nIdx;								//影
	int nIdxLife;							//体力ゲージ
	int nIdxEffect[MAX_EFFECT];				//パーティクル
	int nLife;								//体力
	int nCntStop;							//止まってる時間をカウントする変数
	int nCntMoveTime;						//動いている時間をカウントする変数
	int nCntAttack;							//攻撃した回数(攻撃パターン変化のために必要)
	int nCntAttack2;						//攻撃した回数(攻撃パターン変化のために必要)
	float fNumTurnBoss;					//目的のrot
	float fNumBoss;						//目的と現在のrotの差
	float fSwordCollZ;						//剣の当たり判定のZ軸の長さ
	float fSwordCollX;						//剣の当たり判定のX軸の長さ
	bool bTurnBoss;						//回転の慣性
	bool bTurnBoss2;						//接敵してないときの慣性
	bool bUse;								//使うかどうか
	bool bDamage;							//ダメージを受けているかどうか
	BOSSTYPE nType;						//敵の種類
	BOSSBULLET bullet[2];					//銃
} BOSS;

//========================================================
//プロトタイプ宣言
//========================================================
void InitBoss(void);
void UninitBoss(void);
void UpdateBoss(void);
void DrawBoss(void);
void MotionBoss(int nCntBoss);
void MoveTypeBoss(int nCntBoss);
void SetBoss(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void CollisionBoss(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pBeforePos, D3DXVECTOR3 *pMove, float fWidth, float fHeight, float fDepth);
BOSS *GetBoss(void);
BOSS *GetAttackBoss(void);
int GetUseBoss(void);
int GetAllBoss(void);

#endif // !_BOSS_H_