//===========================================
//雷魔法処理
//Author:KatoMizuki
//===========================================
#ifndef _MAGIC_THUNDER_H_
#define _MAGIC_THUNDER_H_

#include "object.h"

//前方宣言
class CMagicCircle;

//================================================
//マクロ定義
//================================================
#define MAGIC_THUNDER_EFFECT_ENEMY_FAT_DAMAGE	(3)									//太型敵へのダメージ
#define MAGIC_THUNDER_EFFECT_ENEMY_BOSS_DAMAGE	(3)									//太型敵へのダメージ
#define MAGIC_THUNDER_EFFECT_ENEMY_BEE_DAMAGE	(4)									//蜂型敵へのダメージ

//================================================
//クラスの定義
//================================================
//クラスの定義
class CMagicThunder : public CObject
{
public:
	CMagicThunder(int nPriority = PRIORITY_MAGIC);			//コンストラクタ
	~CMagicThunder();										//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMagicThunder *Create(D3DXVECTOR3 pos);
	//当たり判定
	static bool Collision(CObject *pSubjectObject);

private:
	//メンバ関数
	 void MagicCircle(void);				//魔法陣に関する処理

	CMagicCircle *m_pMagicCircle;		//魔法陣のポインタ
	int m_nCounter;						//魔法陣のカウンター
	D3DXVECTOR3 m_pos;					//位置
	D3DXVECTOR3 m_size;					//サイズ
};

#endif // !_MAGIC_THUNDER_H_