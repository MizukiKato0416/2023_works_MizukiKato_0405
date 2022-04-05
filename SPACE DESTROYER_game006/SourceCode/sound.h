//===========================================
//サウンド処理
//Authore:加藤瑞葵
//===========================================
#ifndef _SOUND_H_
#define _SOUND_H_
#include "main.h"

//================================================
//マクロ定義
//================================================

//========================================================
//構造体の定義
//========================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CSound
{
public:
	CSound();				//コンストラクタ
	~CSound();				//デストラクタ

	//サウンドファイル
	typedef enum
	{
		SOUND_LABEL_BULLET_SE = 0,			//弾発射SE
		SOUND_LABEL_EXPLOSION_SE,			//爆発SE
		SOUND_LABEL_TITLE_START_SE,			//タイトルのスタートボタンSE
		SOUND_LABEL_CURSOR_SE,				//カーソル移動SE
		SOUND_LABEL_DECIDE_SE_00,			//決定SE00
		SOUND_LABEL_EXIT_SE,				//戻るSE
		SOUND_LABEL_EXIT_TUTORIAL_SE,		//チュートリアルの戻るSE
		SOUND_LABEL_PAUSE_SE,				//ポーズSE
		SOUND_LABEL_NEXT_PAGE_SE,			//次の説明ページSE
		SOUND_LABEL_BOSS_BULLET_SE,			//ボスの弾SE
		SOUND_LABEL_BOSS_LASER_SE,			//ボスのレーザーSE
		SOUND_LABEL_DIE_EXPLOSION_SE,		//ボスとプレイヤーが死んだSE
		SOUND_LABEL_GAME_CLEAR_SE,			//ゲームクリアSE
		SOUND_LABEL_ITEM_POWER_SE,			//パワーアイテムSE
		SOUND_LABEL_ITEM_SPEED_SE,			//スピードアイテムSE
		SOUND_LABEL_TITLE_BGM,				//タイトルBGM
		SOUND_LABEL_MENU_BGM,				//メニューBGM
		SOUND_LABEL_GAME01_BGM,				//ゲーム01BGM
		SOUND_LABEL_BOSS_BGM,				//ボス登場以降BGM
		SOUND_LABEL_RESULT_BGM,				//リザルトBGM
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	//メンバ関数
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);
	void ControllVoice(SOUND_LABEL label, float fVolume) { m_apSourceVoice[label]->SetVolume(fVolume); }	//音量調整

private:
	//パラメーター構造体
	typedef struct
	{
		char *filename;		// ファイル名
		int nCntLoop;		// ループカウント
	} PARAM;

	//メンバ関数
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunksize, DWORD *pChunkDataPosition);
	HRESULT ReadChunk(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 = NULL;										// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;					// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};			// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};							// オーディオデータ
	DWORD m_asizeAudio[SOUND_LABEL_MAX] = {};							// オーディオデータサイズ

	static PARAM m_aParam[SOUND_LABEL_MAX];								// 各音素材のパラメータ
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_SOUND_H_