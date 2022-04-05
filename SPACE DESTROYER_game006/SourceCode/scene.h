//===========================================
//シーン処理
//Authore:加藤瑞葵
//===========================================
#ifndef _SCENE_H_
#define _SCENE_H_
#include "main.h"

//================================================
//マクロ定義
//================================================
#define MAX_SCENE (2048)

//================================================
//クラスの定義
//================================================
//クラスの定義
class CScene
{
public:
	typedef enum
	{
		PRIORITY_NONE = 0,					//なし
		PRIORITY_BG_0,						//背景0
		PRIORITY_EFFECT,					//エフェクト
		PRIORITY_ITEM,						//アイテム
		PRIORITY_BULLET_ENEMY,				//弾
		PRIORITY_ENEMY,						//敵
		PRIORITY_BOSS,						//ボス
		PRIORITY_BULLET_PLAYER,				//弾
		PRIORITY_PLAYER,					//プレイヤー
		PRIORITY_EXPLOSION,					//爆発
		PRIORITY_UI,						//UI
		PRIORITY_FADE,						//フェード
		PRIORITY_MAX
	} PRIORITY;

	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,				//プレイヤー
		OBJTYPE_BULLET_PLAYER,		//プレイヤーの弾
		OBJTYPE_BULLET_ENEMY,		//敵の弾
		OBJTYPE_ENEMY,				//敵
		OBJTYPE_EXPLOSION,			//爆発
		OBJTYPE_ITEM_SCORE,			//スコアアップアイテム
		OBJTYPE_ITEM_SPEED,			//スピードアップアイテム
		OBJTYPE_ITEM_POWER,			//パワーアップアイテム
		OBJTYPE_BOSS,				//ボス
		OBJTYPE_MAX
	} OBJTYPE;

	CScene(int nPriority = PRIORITY_NONE);			//コンストラクタ
	virtual ~CScene();								//デストラクタ

	//メンバ関数
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

	void SetObjType(OBJTYPE objType);
	OBJTYPE GetObjType(void);
	static CScene *GetScene(int nScene, int nPriority);
	D3DXVECTOR3 GetPos(void);
	void SetPos(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetSize(void);
	void SetSize(D3DXVECTOR3 size);

protected:
	void Release(void);

private:
	static CScene *m_apScene[PRIORITY_MAX][MAX_SCENE];
	static int m_nNumAll;					//使用しているシーンの総数
	int m_nID;								//格納先の番号
	int m_nPriority;						//優先順位の番号
	OBJTYPE m_objType;						//オブジェクトの種類
	D3DXVECTOR3 m_pos;						//ポリゴンの位置
	D3DXVECTOR3 m_size;					//ポリゴンのサイズ
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_SCENE_H_