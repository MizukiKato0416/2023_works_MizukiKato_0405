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
#define PLAYER_SPEED (0.5f)				//モデルの速さ
#define PLAYER_SLASH_MOVE (5.0f)		//斬撃中のモデルの速さ
#define PLAYER_POWER_SPEED (0.35f)		//モデルの速さ
#define PLAYER_SPEED_SPEED (0.8f)		//モデルの速さ
#define PLAYER_SPEEDDOWN (0.7f)			//モデルの速さの減速加減
#define MAX_PLAYER_SPEED (9.0f)			//モデルの最大の速さ
#define MAX_PLAYER_POWER_SPEED (7.0f)	//モデルの最大の速さ
#define MAX_PLAYER_SPEED_SPEED (12.0f)	//モデルの最大の速さ
#define PLAYER_MAX_TEXTURE (128)		//テクスチャの最大数
#define MAX_PLAYER_MODEL (16)			//モデルの最大数
#define GRAVITY (0.3f)					//重力
#define PLAYER_JUMP (12.0f)				//ジャンプ力
#define PLAYER_LIMIT (2400.0f)			//限界移動量
#define MAX_PLAYER_LIFE (80)			//プレイヤーのライフ
#define PLAYER_LIFE_WIDTH (450.0f)		//プレイヤーのライフの幅
#define SWORD_COLLISION_WIDTH (80.0f)	//剣の当たり判定の幅の長さ
#define SWORD_COLLISION_DEPTH (50.0f)	//剣の当たり判定の奥行の長さ

//========================================================
//モーションの種類
//========================================================
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,			//ニュートラルモーション
	MOTIONTYPE_MOVE,				//移動モーション
	MOTIONTYPE_SHOOT_N,				//射撃ノーマル
	MOTIONTYPE_SHOOT_P,				//射撃パワー
	MOTIONTYPE_SHOOT_S,				//射撃スピード
	MOTIONTYPE_SLASH_N,				//斬撃ノーマル
	MOTIONTYPE_SLASH_N1,			//斬撃ノーマル
	MOTIONTYPE_SLASH_N2,			//斬撃ノーマル
	MOTIONTYPE_SLASH_S,				//斬撃スピード
	MOTIONTYPE_SLASH_S1,			//斬撃スピード
	MOTIONTYPE_SLASH_S2,			//斬撃スピード
	MOTIONTYPE_SLASH_P,				//斬撃パワー
	MOTIONTYPE_SLASH_P1,			//斬撃パワー
	MOTIONTYPE_SLASH_P2,			//斬撃パワー
	MOTIONTYPE_DAMAGE,				//被弾モーション
	MOTIONTYPE_DOWN,				//ダウンモーション
	
	MOTION_MAX,
} MOTIONTYPE;

//========================================================
//プレイヤーの種類
//========================================================
typedef enum
{
	PLAYERTYPE_NOMAL = 0,	//ノーマルタイプ
	PLAYERTYPE_SPEED,		//スピードタイプ
	PLAYERTYPE_POWER,		//パワータイプ
	PLAYERTYPE_MAX,
} PLAYERTYPE;

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
	float fWidth;					//幅
	float fHeight;					//高さ
	float fDepth;					//奥行
} Model;

//銃の構造体
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 rot;						//向き
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
} GUN;

//剣の構造体
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 rot;						//向き
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
} SWORD;

//プレイヤーの構造体
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 posOld;						//前の位置
	D3DXVECTOR3 rot;						//向き
	D3DXVECTOR3 rotBullet;					//弾を打つ瞬間のプレイヤーの向き
	D3DXVECTOR3 move;						//移動量
	D3DXVECTOR3 moveA;						//加速度
	D3DXVECTOR3 VtxPos[4];					//四頂点の位置
	D3DXVECTOR3 VtxPosSave[4];				//四頂点の位置保存用変数
	D3DXVECTOR3 VtxPosOld[4];				//四頂点の前の位置
	D3DXVECTOR3 VtxRot[4];					//四頂点の向き
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
	D3DXMATRIX VtxMtxWorld[4];					//4頂点のワールドマトリックス
	Model aModel[MAX_PLAYER_MODEL];			//モデル(パーツ)
	int nNumModel;							//モデル(パーツ)数
	MOTION_INFO aMotionInfo[MOTION_MAX];	//モーション情報
	int nNumMotion;							//モーション数
	MOTIONTYPE MotionType;					//現在のモーションタイプ
	MOTIONTYPE MotionTypeNext;				//次のモーションタイプ
	MOTIONTYPE MotionTypeOld;				//1つ前のモーションタイプ
	PLAYERTYPE nType;						//プレイヤーのタイプ
	PLAYERTYPE nTypeNext;					//次のプレイヤーのタイプ
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
	bool bEvolutionButton;					//進化ボタンを押したかどうか
	bool bEvolution;						//進化しているかどうか
	bool bDegenerate;						//退化しているかどうか
	bool bWeapon;							//何の武器を使っているかtrueなら剣falseなら銃
	bool bWeaponX;							//xファイルの読み込み
	float fWidth;							//幅
	float fHeight;							//高さ
	float fDepth;							//奥行
	float fNumTurnPlayer;					//回転の慣性に必要
	float fNumPlayer;						//目的の向き
	float fMoveSpeed;						//動く速さ
	float fMaxSpeed;						//動く速さの最大値
	bool bTurnPlayer;						//回転をしているかどうか
	bool bMotion;							//モーションをつなぐ変数
	int nIdx;								//影
	int nLife;								//体力
	int nEffect;							//エフェクト
	int nTitle;								//タイトル
	bool bFinishMotion;						//モーションが終了したかどうか
	bool bBlendMotion;						//ブレンドモーションがあるかどうか
	int nNumKeyBlend;						//ブレンドキー数
	int nKeyBlend;							//ブレンドキーNo,(現在のキー)
	float fCounterMotionBlend;				//ブレンドモーションのカウンター
	int nFrameBlend;						//ブレンドするためのフレーム数
	int nCounterBlend;						//ブレンドカウンター

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
bool CollisionSword(D3DXVECTOR3 *pPos, float fWidth);
void InputPlayer(void);
PLAYER *GetPlayer(void);
#endif // !_PLAYER_H_