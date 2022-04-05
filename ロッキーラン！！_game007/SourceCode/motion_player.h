//===========================================
//プレイヤーのモーション処理
//Author:加藤瑞葵
//===========================================
#ifndef _MOTION_PLAYER_H_
#define _MOTION_PLAYER_H_
#include "main.h"
#include "motion.h"
#include "player.h"

//================================================
//マクロ定義
//================================================
#define MOTION_PLAYER_MAX_KEY_INFO	(128)	//キーの情報の最大値
#define MOTION_PLAYER_MAX_STRING	(128)	//文字列の最大値

//================================================
//構造体の定義
//================================================
//キーの構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//向き
} KEY;

//キー情報の構造体
typedef struct
{
	int nFrame;						//再生フレーム
	KEY aKey[MAX_PLAYER_MODEL];		//各モデルのキー要素(パーツの最大数)
} KEY_INFO;

//モーション情報の構造体
typedef struct
{
	bool bLoop;				//ループするかどうか
	int nNumKey;			//キーの総数
	KEY_INFO aKeyInfo[MOTION_PLAYER_MAX_KEY_INFO];	//キーの情報
} MOTION_INFO;

//================================================
//クラスの定義
//================================================
//クラスの定義
class CMotionPlayer:CMotion
{
public:
	//モーションの種類
	typedef enum
	{
		MOTION_PLAYER_TYPE_NEUTRAL = 0,			//ニュートラル
		MOTION_PLAYER_TYPE_MOVE,				//移動
		MOTION_PLAYER_TYPE_STEP,				//踏み込み
		MOTION_PLAYER_TYPE_JUMP,				//ジャンプ
		MOTION_PLAYER_TYPE_LAND,				//着地
		MOTION_PLAYER_TYPE_DIVE,				//ダイブ
		MOTION_PLAYER_TYPE_DIVE_LAND,			//ダイブの着地
		MOTION_PLAYER_TYPE_APPLAUSE,			//拍手
		MOTION_PLAYER_TYPE_GLAD_01,				//喜ぶ01
		MOTION_PLAYER_TYPE_GLAD_02,				//喜ぶ02
		MOTION_PLAYER_TYPE_GLAD_03,				//喜ぶ03
		MOTION_PLAYER_TYPE_GLAD_04,				//喜ぶ04
		MOTION_PLAYER_TYPE_MAX
	} MOTION_PLAYER_TYPE;

	CMotionPlayer();			//コンストラクタ
	~CMotionPlayer();			//デストラクタ

	//メンバ関数
	HRESULT Init(CPlayer *pPlayer);
	void Uninit(void);
	void Update(CPlayer *pPlayer);

	static CMotionPlayer *Create(CPlayer *pPlayer);		//生成処理
	void SetMotion(MOTION_PLAYER_TYPE type);			//モーション設定処理
	MOTION_PLAYER_TYPE GetMotion(void);					//モーション取得処理
	bool GetConnect(void);								//モーションをつなげている最中かどうか取得処理

private:
	MOTION_INFO m_aInfo[MOTION_PLAYER_TYPE_MAX];		//モーション情報
	MOTION_PLAYER_TYPE m_type;							//現在のモーションタイプ
	MOTION_PLAYER_TYPE m_typeNext;						//次のモーションタイプ
	int m_nNumKey;										//キー数
	int m_nKey;											//キーNo,(現在のキー)
	int m_nKeyNext;										//キーNo,(次のキー)
	int m_nKeyOld;										//キーNo,(1フレーム前のキー)
	float m_fCounter;									//モーションのカウンター
	bool m_bConnect;									//モーションをつなげているかどうか
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_MOTION_PLAYER_H_