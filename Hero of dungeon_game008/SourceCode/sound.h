//===========================================
//サウンド処理
//Author:KatoMizuki
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
		SOUND_LABEL_CANCEL_SE = 0,			//キャンセルSE
		SOUND_LABEL_DECIDE_SE,				//決定SE
		SOUND_LABEL_CURSOR_SE,				//カーソルのSE
		SOUND_LABEL_PAUSE_SE,				//ポーズSE
		SOUND_LABEL_POOR_SE,				//不十分SE
		SOUND_LABEL_CURE_SE,				//回復SE
		SOUND_LABEL_GAMECLEAR_SE,			//ゲームクリアSE
		SOUND_LABEL_GAMEOVER_SE,			//ゲームオーバーSE
		SOUND_LABEL_SLASH_01_SE,			//斬撃01SE
		SOUND_LABEL_SLASH_02_SE,			//斬撃02SE
		SOUND_LABEL_GUARD_SE,				//ガードSE
		SOUND_LABEL_MAGIC_SE,				//魔法SE
		SOUND_LABEL_EARTH_QUAKE_01_SE,		//地震01SE
		SOUND_LABEL_EARTH_QUAKE_02_SE,		//地震02SE
		SOUND_LABEL_MAGIC_CIRCLE_SE,		//魔法陣SE
		SOUND_LABEL_THUNDER_01_SE,			//雷01SE
		SOUND_LABEL_THUNDER_02_SE,			//雷02SE
		SOUND_LABEL_TITLE_BGM,				//タイトルBGM
		SOUND_LABEL_MENU_BGM,				//メニューBGM
		SOUND_LABEL_GAME_BGM,				//ゲーム内BGM
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