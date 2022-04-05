//===========================================
//プレイヤー処理
//Author:加藤瑞葵
//===========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "scene.h"

//前方宣言
class CModel;
class CControl;
class CMotionPlayer;
class CShadow;

//================================================
//マクロ定義
//================================================
#define MAX_PLAYER_MODEL						(5)			//モデルの数
#define PLAYER_UNINIT_POS_Y						(-300.0f)	//プレイヤーを消す場所
#define MAX_PLAYER								(2)			//プレイヤーの数

//================================================
//クラスの定義
//================================================
//クラスの定義
class CPlayer : public CScene
{
public:
	//チェックポイント
	typedef enum
	{
		PLAYER_CHECK_POINT_NONE = 0,
		PLAYER_CHECK_POINT_GAME01_MIDDLE1,		//ゲーム01の中間地点1
		PLAYER_CHECK_POINT_GAME01_MIDDLE2,		//ゲーム01の中間地点2
		PLAYER_CHECK_POINT_MAX
	} PLAYER_CHECK_POINT;

	CPlayer(int nPriority = PRIORITY_MODEL);				//コンストラクタ
	~CPlayer();												//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3	rot, int nNum);

	D3DXVECTOR3 GetPosOld(void);						//1フレーム前の位置
	void SetLand(bool bLand);							//着地設定処理
	bool GetLand(void);									//着地取得処理
	D3DXVECTOR3 GetRot(void);							//向き取得処理
	void SetRot(D3DXVECTOR3 rot);						//向き設定処理
	void SetMove(D3DXVECTOR3 move);						//移動量設定処理
	D3DXVECTOR3 GetMove(void);							//移動量取得処理
	void SetJump(bool bJump);							//ジャンプ設定処理
	bool GetJump(void);									//ジャンプ取得処理
	void SetDive(bool bDive);							//ダイブ設定処理
	bool GetDive(void);									//ダイブ取得処理
	void SetOnIce(bool bOnIce);							//氷の床かどうか設定処理
	bool GetOnIce(void);								//氷の床かどうか取得処理
	void SetOnSpring(bool bOnSpring);					//バネかどうか設定処理
	bool GetOnSpring(void);								//バネかどうか取得処理
	void SetModelPos(int nCntModel, D3DXVECTOR3 pos);	//モデルの位置設定処理
	D3DXVECTOR3 GetModelPos(int nCntModel);				//モデルの位置取得処理
	void SetModelRot(int nCntModel, D3DXVECTOR3 rot);	//モデルの向き設定処理
	D3DXVECTOR3 GetModelRot(int nCntModel);				//モデルの向き取得処理
	CMotionPlayer *GetMotionPlayer(void);				//モーションプレイヤー取得処理
	void Collision(CScene *pSCene);						//オブジェクトとの当たり判定
	int GetNum(void);									//プレイヤーの個体識別番号取得処理
	void SetNum(int nNum);								//プレイヤーの個体識別番号設定処理
	void SetCheckPoint(PLAYER_CHECK_POINT checkPoint);	//チェックポイント設定処理
	PLAYER_CHECK_POINT GetCheckPoint(void);				//チェックポイント取得処理
	void ShadowCollision(void);							//影の表示のためのオブジェクトとの当たり判定

private:
	//メンバ関数
	bool Collision(void);							//当たり判定
	static void CollisionPlayer(CPlayer *pPlayer);	//プレイヤーとの当たり判定
	void Move(void);								//移動

	D3DXVECTOR3 m_pos;								//位置
	D3DXVECTOR3 m_posOld;							//1フレーム前の位置
	D3DXVECTOR3 m_move;								//ポリゴンの移動量
	D3DXVECTOR3	m_size;								//サイズ
	D3DXVECTOR3 m_rot;								//向き
	CModel *m_apModel[MAX_PLAYER_MODEL];			//モデルのポインタ
	D3DXMATRIX m_mtxWorld;							//ワールドマトリックス
	CModel *m_pParent;								//親モデルへのポインタ
	CControl *m_pControl;							//コントロールクラスのポインタ
	CShadow *m_pShadow;								//シャドウクラスのポインタ
	bool m_bLand;									//着地しているかどうか
	bool m_bJump;									//ジャンプしているかどうか
	bool m_bJumpOld;								//前フレームジャンプしているかどうか
	bool m_bDive;									//ダイブしているかどうか
	bool m_bOnIce;									//氷の上かどうか
	bool m_bOnSpring;								//バネかどうか
	CMotionPlayer *m_pMotionPlayer;					//モーションプレイヤーのポインタ
	bool m_bLandMoment;								//着地した瞬間かどうか
	int m_nNum;										//プレイヤーの個体識別番号
	PLAYER_CHECK_POINT m_checkPoint;				//チェックポイント
};

#endif // !_PLAYER_H_