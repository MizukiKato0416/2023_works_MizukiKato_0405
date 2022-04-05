//===========================================
//�T�E���h����
//Authore:��������
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
		SOUND_LABEL_BULLET_SE = 0,			//�e����SE
		SOUND_LABEL_EXPLOSION_SE,			//����SE
		SOUND_LABEL_TITLE_START_SE,			//�^�C�g���̃X�^�[�g�{�^��SE
		SOUND_LABEL_CURSOR_SE,				//�J�[�\���ړ�SE
		SOUND_LABEL_DECIDE_SE_00,			//����SE00
		SOUND_LABEL_EXIT_SE,				//�߂�SE
		SOUND_LABEL_EXIT_TUTORIAL_SE,		//�`���[�g���A���̖߂�SE
		SOUND_LABEL_PAUSE_SE,				//�|�[�YSE
		SOUND_LABEL_NEXT_PAGE_SE,			//���̐����y�[�WSE
		SOUND_LABEL_BOSS_BULLET_SE,			//�{�X�̒eSE
		SOUND_LABEL_BOSS_LASER_SE,			//�{�X�̃��[�U�[SE
		SOUND_LABEL_DIE_EXPLOSION_SE,		//�{�X�ƃv���C���[������SE
		SOUND_LABEL_GAME_CLEAR_SE,			//�Q�[���N���ASE
		SOUND_LABEL_ITEM_POWER_SE,			//�p���[�A�C�e��SE
		SOUND_LABEL_ITEM_SPEED_SE,			//�X�s�[�h�A�C�e��SE
		SOUND_LABEL_TITLE_BGM,				//�^�C�g��BGM
		SOUND_LABEL_MENU_BGM,				//���j���[BGM
		SOUND_LABEL_GAME01_BGM,				//�Q�[��01BGM
		SOUND_LABEL_BOSS_BGM,				//�{�X�o��ȍ~BGM
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