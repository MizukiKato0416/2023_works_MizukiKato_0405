//=======================================================================
//プレイヤーに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"

//========================================================
//マクロ定義
//========================================================
#define PLAYER_SPEED (7.0f)				//モデルの速さ
#define PLAYER_MAX_TEXTURE (128)		//テクスチャの最大数
#define MAX_PLAYER_MODEL (14)			//モデルの最大数
#define GRAVITY (0.3f)					//重力
#define PLAYER_JUMP (12.0f)				//ジャンプ力
#define MAX_PLAYER_LIFE (20)			//プレイヤーのライフ
#define SWORD_COLLISION_WIDTH (80.0f)	//剣の当たり判定の幅の長さ
#define SWORD_COLLISION_DEPTH (50.0f)	//剣の当たり判定の奥行の長さ

//========================================================
//モーションの種類
//========================================================
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,			//ニュートラルモーション
	MOTIONTYPE_MOVE,				//移動モーション
	MOTIONTYPE_PUNCH,				//アクションモーション
	MOTIONTYPE_SLASH,				//アクションモーション
	MOTIONTYPE_SLASH03,				//アクションモーション
	MOTIONTYPE_SLASH04,				//回転切り
	MOTIONTYPE_DIFENCE,				//ガードモーション
	
	MOTION_MAX,
} MOTIONTYPE;


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
} KEY;

//キー情報の構造体
typedef struct
{
	int nFrame;		//再生フレーム
	KEY aKey[MAX_PLAYER_MODEL];		//各モデルのキー要素(パーツの最大数)
} KEY_INFO;

//モーション情報の構造体
typedef struct
{
	bool bLoop;				//ループするかどうか
	int nNumKey;			//キーの総数
	KEY_INFO aKeyInfo[128];	//キーの情報
} MOTION_INFO;

//モデルの構造体
typedef struct
{
	LPD3DXMESH pMesh;				//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER pBuffMat;			//マテリアル(材質情報)へのポインタ
	DWORD nNumMat;					//マテリアル数
	LPDIRECT3DTEXTURE9 pTexture[PLAYER_MAX_TEXTURE];	//テクスチャへのポインタ
	D3DXVECTOR3	pos;				//位置
	D3DXVECTOR3 rot;				//向き
	D3DXMATRIX mtxWorld;			//ワールドマトリックス
	int nIdxModelParent;			//親のインデックス
	D3DXVECTOR3 vtxMax;				//頂点情報
	D3DXVECTOR3 vtxMin;				//頂点情報
	float fWidth;							//幅
	float fHeight;							//高さ
	float fDepth;							//奥行
} Model;

//プレイヤーの構造体
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 posOld;						//前の位置
	D3DXVECTOR3 rot;						//向き
	D3DXVECTOR3 move;						//移動量
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
	Model aModel[MAX_PLAYER_MODEL];			//モデル(パーツ)
	int nNumModel;							//モデル(パーツ)数
	MOTION_INFO aMotionInfo[MOTION_MAX];	//モーション情報
	int nNumMotion;							//モーション数
	MOTIONTYPE MotionType;					//現在のモーションタイプ
	MOTIONTYPE MotionTypeNext;				//次のモーションタイプ
	MOTIONTYPE MotionTypeOld;				//1つ前のモーションタイプ
	bool bLoopMotion;						//ループするかどうか
	int nNumKey;							//キー数
	int nKey;								//キーNo,(現在のキー)
	int nKeyOld;							//キーNo,(1フレーム前のキー)
	float fCounterMotion;					//モーションのカウンター
	bool bJump;								//ジャンプしているかどうか
	bool bSlash;							//斬撃1をしているかどうか
	bool bUse;								//使っているかどうか
	bool bDamage;							//ダメージを受けているかどうか
	bool bDifence;							//でフェンスしているかどうか
	float fWidth;							//幅
	float fHeight;							//高さ
	float fDepth;							//奥行
	float fNumTurnPlayer;					//回転の慣性に必要
	bool bTurnPlayer;						//回転をしているかどうか
	int nIdx;								//影
	int nLife;								//体力
	int nEffect;							//エフェクト
	int nTitle;								//タイトル
} PLAYER;

//========================================================
//プロトタイプ宣言
//========================================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void MotionPlayer(void);
bool CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pBeforePos, D3DXVECTOR3 *pMove, float fWidth, float fHeight, float fDepth);
bool CollisionSword(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pBeforePos, D3DXVECTOR3 *pMove, float fWidth, float fHeight, float fDepth);
PLAYER *GetPlayer(void);
Model *GetSword(void);

#endif // !_PLAYER_H_