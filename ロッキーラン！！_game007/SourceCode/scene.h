//===========================================
//シーン処理
//Author:加藤瑞葵
//===========================================
#ifndef _SCENE_H_
#define _SCENE_H_
#include "main.h"

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CScene
{
public:
	typedef enum
	{
		PRIORITY_NONE = 0,			//なし
		PRIORITY_PLAYER,			//プレイヤー
		PRIORITY_MODEL,				//モデル
		PRIORITY_UI,				//UI
		PRIORITY_PAUSE,				//ポーズ
		PRIORITY_FADE,				//フェード
		PRIORITY_MAX
	} PRIORITY;

	typedef enum
	{
		OBJTYPE_NONE = 0,			//なし
		OBJTYPE_PLAYER,				//プレイヤー
		OBJTYPE_MODEL,				//モデル
		OBJTYPE_ENEMY,				//敵
		OBJTYPE_UI,					//UI
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

	void SetObjType(OBJTYPE objType);			//オブジェクトタイプ設定処理
	OBJTYPE GetObjType(void);					//オブジェクトタイプ取得処理
	CScene *GetObjNext(CScene *pObject);		//引数のオブジェクトの次のオブジェクト情報取得処理
	static CScene *GetTopObj(int nPriority);	//引数のプライオリティの先頭オブジェクト取得処理
	D3DXVECTOR3 GetPos(void);					//位置取得処理
	void SetPos(D3DXVECTOR3 pos);				//位置設定処理
	void SetPosOld(D3DXVECTOR3 posOld);			//1フレーム前の位置設定処理
	D3DXVECTOR3 GetPosOld(void);				//1フレーム前の位置取得処理
	D3DXVECTOR3 GetSize(void);					//サイズ取得処理
	void SetSize(D3DXVECTOR3 size);				//サイズ設定処理

protected:
	void Release(void);

private:
	static CScene *m_pTop[PRIORITY_MAX];	//先頭オブジェクトのポインタ
	static CScene *m_pCur[PRIORITY_MAX];	//現在(一番後ろ)オブジェクトのポインタ
	CScene *m_pPrev;						//前のオブジェクトへのポインタ
	CScene *m_pNext;						//次のオブジェクトへのポインタ
	int m_nPriority;						//優先順位の番号
	OBJTYPE m_objType;						//オブジェクトの種類
	D3DXVECTOR3 m_pos;						//ポリゴンの位置
	D3DXVECTOR3 m_posOld;					//1フレーム前のポリゴンの位置
	D3DXVECTOR3 m_size;						//ポリゴンのサイズ
	bool m_bDeath;							//死亡フラグ
};

#endif // !_SCENE_H_