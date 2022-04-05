//=======================================================================
//敵に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"
#include "effect.h"

//========================================================
//マクロ定義
//========================================================
#define ENEMY_SPEED (4.0f)			//モデルの速さ
#define ENEMY_SEARCH (400.0f)		//プレイヤーを探し出す範囲
#define ENEMY_SEARCH_ATTACK (100.0f)//プレイヤーを攻撃をする範囲
#define ENEMY_ATTACK (200.0f)		//プレイヤーに攻撃をする範囲
#define ENEMY_DAMAGE (500.0f)		//プレイヤーに吹っ飛ばされる距離
#define ENEMY_MAX_TEXTURE (256)		//テクスチャの最大数
#define MAX_ENEMY_MODEL (14)		//モデルの最大数
#define MAX_ENEMY (25)				//敵の最大数
#define MAX_ENEMY_LIFE (7)			//敵のライフの最大数
#define GRAVITY (0.3f)				//重力
#define ENEMY_JUMP (12.0f)			//ジャンプ力
#define ENEMY_RAND (float (rand() % 629 + -314) / 100)	//ランダム値
#define ENEMY_STOP_TIME (rand() % 300 + 150)	//敵がストップしてる時間
#define ENEMY_SWORD_COLLISION_WIDTH (50.0f)	//剣の当たり判定の幅の長さ
#define ENEMY_SWORD_COLLISION_DEPTH (50.0f)	//剣の当たり判定の奥行の長さ


//========================================================
//動きの種類
//========================================================
typedef enum
{
	ENEMY_MOVETYPE_MOVE = 0,	//動く
	ENEMY_MOVETYPE_STOP,		//止まる
	ENEMY_MOVETYPE_TURN,		//回る
	ENEMY_MOVETYPE_TO_PLAYER_TURN,		//プレイヤーの方向に向く
	ENEMY_MOVETYPE_TO_PLAYER,	//プレイヤーに向かって動く
	ENEMY_MOVETYPE_ATTACK,		//攻撃
	ENEMY_MOVETYPE_DAMAGE,		//ダメージ食らったとき
	ENEMY_MOVETYPE_MAX,
} ENEMY_MOVETYPE;


//========================================================
//モーションの種類
//========================================================
typedef enum
{
	ENEMY_MOTIONTYPE_NEUTRAL = 0,		//ニュートラルモーション
	ENEMY_MOTIONTYPE_MOVE,				//移動モーション
	ENEMY_MOTIONTYPE_PUNCH,				//アクションモーション
	ENEMY_MOTIONTYPE_DAMAGE,			//アクションモーション

	ENEMY_MOTION_MAX,
} ENEMY_MOTIONTYPE;


//========================================================
//構造体の定義
//========================================================
//キーの構造体
typedef struct
{
	float fPosX;	//位置X
	float fPosY;	//位置Y
	float fPosZ;	//位置Z
	float fRotX;	//向きX
	float fRotY;	//向きY
	float fRotZ;	//向きZ
} ENEMY_KEY;

//キー情報の構造体
typedef struct
{
	int nFrame;		//再生フレーム
	ENEMY_KEY aKey[MAX_ENEMY_MODEL];		//各モデルのキー要素(パーツの最大数)
} ENEMY_KEY_INFO;

//モーション情報の構造体
typedef struct
{
	bool bLoop;				//ループするかどうか
	int nNumKey;			//キーの総数
	ENEMY_KEY_INFO aKeyInfo[128];	//キーの情報
} ENEMY_MOTION_INFO;

//モデルの構造体
typedef struct
{
	LPD3DXMESH pMesh;				//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER pBuffMat;			//マテリアル(材質情報)へのポインタ
	DWORD nNumMat;					//マテリアル数
	LPDIRECT3DTEXTURE9 pTexture[ENEMY_MAX_TEXTURE];	//テクスチャへのポインタ
	D3DXVECTOR3	pos;				//位置
	D3DXVECTOR3 rot;				//向き
	D3DXMATRIX mtxWorld;			//ワールドマトリックス
	int nIdxModelParent;			//親のインデックス
} ENEMY_Model;

//敵の構造体
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 posOld;						//前の位置
	D3DXVECTOR3 posPlayer;					//プレイヤーの位置保存
	D3DXVECTOR3 rot;						//向き
	D3DXVECTOR3 move;						//移動量
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
	ENEMY_Model aModel[MAX_ENEMY_MODEL];			//モデル(パーツ)
	int nNumModel;							//モデル(パーツ)数
	ENEMY_MOTION_INFO aMotionInfo[ENEMY_MOTION_MAX];	//モーション情報
	int nNumMotion;							//モーション数
	int nCntMove;							//動きのランダム性に必要
	ENEMY_MOTIONTYPE MotionType;			//現在のモーションタイプ
	ENEMY_MOTIONTYPE MotionTypeOld;			//1つ前のモーションタイプ
	ENEMY_MOVETYPE MoveType;				//敵の動きの種類
	bool bLoopMotion;						//ループするかどうか
	int nNumKey;							//キー数
	int nKey;								//キーNo,(現在のキー)
	float fCounterMotion;					//モーションのカウンター
	bool bJump;								//ジャンプしているかどうか
	bool bSlash;							//斬撃1をしているかどうか
	float fWidth;							//幅
	float fHeight;							//高さ
	float fDepth;							//奥行
	float frotVecX;							//プレイヤーの角度を求めるためのベクトル
	float frotVecZ;							//プレイヤーの角度を求めるためのベクトル
	float fToPlayerR;						//プレイヤーとの距離
	float fDifferRot;						//目的と現在のrotの差
	int nIdx;								//影
	int nIdxEffect[MAX_EFFECT];							//パーティクル
	int nLife;								//体力
	int nCntStop;							//止まってる時間をカウントする変数
	int nCntMoveTime;						//動いている時間をカウントする変数
	float fNumTurnEnemy;					//目的のrot
	float fNumEnemy;						//目的と現在のrotの差
	float fSwordCollZ;						//剣の当たり判定のZ軸の長さ
	float fSwordCollX;						//剣の当たり判定のX軸の長さ
	bool bTurnEnemy;						//回転の慣性
	bool bTurnEnemy2;						//接敵してないときの慣性
	bool bUse;								//使うかどうか
	bool bDamage;							//ダメージを受けているかどうか
	bool bPlayerDamage;						//プレイヤーにダメージを与えているかどうか
} ENEMY;

//========================================================
//プロトタイプ宣言
//========================================================
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void MotionEnemy(int nCntEnemy);
void MoveTypeEnemy(int nCntEnemy);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pBeforePos, D3DXVECTOR3 *pMove, float fWidth, float fHeight, float fDepth);
bool CollisionEnemySword(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pBeforePos, D3DXVECTOR3 *pMove, float fWidth, float fHeight, float fDepth);
ENEMY *GetEnemy(void);
ENEMY *GetAttackEnemy(void);
int GetUseEnemy(void);
int GetAllEnemy(void);

#endif // !_ENEMY_H_