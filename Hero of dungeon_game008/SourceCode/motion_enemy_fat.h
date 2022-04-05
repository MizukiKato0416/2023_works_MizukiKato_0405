//===========================================
//太型敵のモーション処理
//Author:KatoMizuki
//===========================================
#ifndef _MOTION_ENEMY_FAT_H_
#define _MOTION_ENEMY_FAT_H_
#include "main.h"
#include "enemy_fat.h"
#include "motion_road.h"
#include "manager.h"

//================================================
//マクロ定義
//================================================

//================================================
//構造体の定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CMotionEnemyFat
{
public:

	CMotionEnemyFat();			//コンストラクタ
	~CMotionEnemyFat();			//デストラクタ

	//メンバ関数
	HRESULT Init(CEnemyFat *pEnemyFat);
	void Uninit(void);
	void Update(CEnemyFat *pEnemyFat);

	static CMotionEnemyFat *Create(CEnemyFat *pEnemyFat);									//生成処理
	void SetMotion(CMotionRoad::MOTION_ENEMY_FAT_TYPE type, CEnemyFat *pEnemyFat);			//モーション設定処理
	void SetMotion(int nType, CEnemyFat *pEnemyFat);									//モーション設定処理
	CMotionRoad::MOTION_ENEMY_FAT_TYPE GetMotion(void);								//モーション取得処理
	bool GetConnect(void);															//モーションをつなげている最中かどうか取得処理
	int GetKey(void) { return m_nKey; }												//キー取得処理
	int GetFrame(void) { return (int)m_fCounter; }									//モーションカウンター取得処理
	void SetFrameMax(int nFrame) { m_fConnectMaxFrame = (float)nFrame; }			//モーションカウンター最大値設定処理
	//キー最大数取得処理
	int GetKeyMax(void) { return CManager::GetInstance()->GetMotionRoad()->GetMotionInfo(CMotionRoad::MOTION_HAVE_TYPE_ENEMY_FAT, m_type).nNumKey; }
	//モーションカウンター最大数取得処理
	int GetFrameMax(void) { return CManager::GetInstance()->GetMotionRoad()->GetMotionInfo(CMotionRoad::MOTION_HAVE_TYPE_ENEMY_FAT, m_type).aKeyInfo[m_nKey].nFrame; }
	

private:
	std::vector<MOTION_INFO> m_aInfo;					//モーション情報
	CMotionRoad::MOTION_ENEMY_FAT_TYPE m_type;				//現在のモーションタイプ
	CMotionRoad::MOTION_ENEMY_FAT_TYPE m_typeNext;			//次のモーションタイプ
	CMotionRoad::MOTION_ENEMY_FAT_TYPE m_typeOld;			//前のモーションタイプ
	int m_nKey;											//キーNo,(現在のキー)
	float m_fCounter;									//モーションのカウンター
	bool m_bConnect;									//モーションをつなげているかどうか
	float m_fConnectMaxFrame;							//モーションをつなげるときのフレーム数最大値
	std::vector<D3DXVECTOR3> m_posOld;					//モーションをつなげるときの前のモデルの位置
	std::vector<D3DXVECTOR3> m_rotOld;					//モーションをつなげるときの前のモデルの向き
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_MOTION_ENEMY_FAT_H_