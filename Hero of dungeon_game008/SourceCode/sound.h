//===========================================
//�T�E���h����
//Author:KatoMizuki
//===========================================
#ifndef _SOUND_H_
#define _SOUND_H_
#include "main.h"

//================================================
//�}�N����`
//================================================

//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CSound
{
public:
	CSound();				//�R���X�g���N�^
	~CSound();				//�f�X�g���N�^

	//�T�E���h�t�@�C��
	typedef enum
	{
		SOUND_LABEL_CANCEL_SE = 0,			//�L�����Z��SE
		SOUND_LABEL_DECIDE_SE,				//����SE
		SOUND_LABEL_CURSOR_SE,				//�J�[�\����SE
		SOUND_LABEL_PAUSE_SE,				//�|�[�YSE
		SOUND_LABEL_POOR_SE,				//�s�\��SE
		SOUND_LABEL_CURE_SE,				//��SE
		SOUND_LABEL_GAMECLEAR_SE,			//�Q�[���N���ASE
		SOUND_LABEL_GAMEOVER_SE,			//�Q�[���I�[�o�[SE
		SOUND_LABEL_SLASH_01_SE,			//�a��01SE
		SOUND_LABEL_SLASH_02_SE,			//�a��02SE
		SOUND_LABEL_GUARD_SE,				//�K�[�hSE
		SOUND_LABEL_MAGIC_SE,				//���@SE
		SOUND_LABEL_EARTH_QUAKE_01_SE,		//�n�k01SE
		SOUND_LABEL_EARTH_QUAKE_02_SE,		//�n�k02SE
		SOUND_LABEL_MAGIC_CIRCLE_SE,		//���@�wSE
		SOUND_LABEL_THUNDER_01_SE,			//��01SE
		SOUND_LABEL_THUNDER_02_SE,			//��02SE
		SOUND_LABEL_TITLE_BGM,				//�^�C�g��BGM
		SOUND_LABEL_MENU_BGM,				//���j���[BGM
		SOUND_LABEL_GAME_BGM,				//�Q�[����BGM
		SOUND_LABEL_RESULT_BGM,				//���U���gBGM
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	//�����o�֐�
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);
	void ControllVoice(SOUND_LABEL label, float fVolume) { m_apSourceVoice[label]->SetVolume(fVolume); }	//���ʒ���

private:
	//�p�����[�^�[�\����
	typedef struct
	{
		char *filename;		// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} PARAM;

	//�����o�֐�
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunksize, DWORD *pChunkDataPosition);
	HRESULT ReadChunk(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 = NULL;										// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;					// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};			// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};							// �I�[�f�B�I�f�[�^
	DWORD m_asizeAudio[SOUND_LABEL_MAX] = {};							// �I�[�f�B�I�f�[�^�T�C�Y

	static PARAM m_aParam[SOUND_LABEL_MAX];								// �e���f�ނ̃p�����[�^
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_SOUND_H_