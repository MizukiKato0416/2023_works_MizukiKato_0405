//=============================================================================
//�e�N�X�`������
//Authore:��������
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CTexture
{
public:
	//�e�N�X�`���^�C�v
	typedef enum
	{
		TEX_TYPE_SKY = 0,							//��
		TEX_TYPE_TILE,								//�n��
		TEX_TYPE_NUMBER,							//�i���o�[
		TEX_TYPE_COMMA,								//�J���}

		TEX_TYPE_TITLE_BG,							//�^�C�g���w�i
		TEX_TYPE_TITLE_UI_LOGO,						//�^�C�g��UI:�^�C�g�����S
		TEX_TYPE_TITLE_UI_PRESS,					//�^�C�g��UI:Press����
		TEX_TYPE_TITLE_UI_PLAYER_1P,				//�^�C�g��UI:1P�؂蔲���摜
		TEX_TYPE_TITLE_UI_PLAYER_2P,				//�^�C�g��UI:2P�؂蔲���摜

		TEX_TYPE_MENU_BG,							//���j���[�w�i
		TEX_TYPE_MEMU_EXPLANATION_FRAME,			//���j���[�����g
		TEX_TYPE_MENU_UI_STAR,						//���j���[UI:��
		TEX_TYPE_MENU_LOGO,							//���j���[UI:���j���[���S
		TEX_TYPE_MENU_UI_TUTORIAL,					//���j���[UI:�I����(�`���[�g���A��)
		TEX_TYPE_MENU_UI_GAME,						//���j���[UI:�I����(�Q�[���X�^�[�g)
		TEX_TYPE_MENU_UI_BACKTITLE,					//���j���[UI:�I����(�^�C�g���ɖ߂�)
		TEX_TYPE_MENU_UI_TUTORIAL_EXPLANATION,		//���j���[UI:�I�����̐���(�`���[�g���A��)
		TEX_TYPE_MENU_UI_GAME_EXPLANATION,			//���j���[UI:�I�����̐���(�Q�[���X�^�[�g)
		TEX_TYPE_MENU_UI_BACKTITLE_EXPLANATION,		//���j���[UI:�I�����̐���(�^�C�g���ɖ߂�)

		TEX_TYPE_TUTORIAL_EXPLANATION,				//�`���[�g���A��UI:�������
			
		TEX_TYPE_GAME_UI_COUNTDOWN03,				//�Q�[��UI:�J�E���g�_�E��3
		TEX_TYPE_GAME_UI_COUNTDOWN02,				//�Q�[��UI:�J�E���g�_�E��2
		TEX_TYPE_GAME_UI_COUNTDOWN01,				//�Q�[��UI:�J�E���g�_�E��1
		TEX_TYPE_GAME_UI_START,						//�Q�[��UI:�X�^�[�g
		TEX_TYPE_GAME_UI_CLEAR,						//�Q�[��UI:�Q�[���N���A
		TEX_TYPE_GAME_UI_TIME_UP,					//�Q�[��UI:�^�C���A�b�v
		TEX_TYPE_GOAL_TAPE,							//�S�[���e�[�v

		TEX_TYPE_RESULT_BG,							//���U���g�w�i
		TEX_TYPE_RESULT_UI_WIN,						//���U���gUI:Win
		TEX_TYPE_RESULT_UI_RANKING01,				//���U���gUI:�����L���O1��
		TEX_TYPE_RESULT_UI_RANKING02,				//���U���gUI:�����L���O2��
		TEX_TYPE_RESULT_UI_RANKING03,				//���U���gUI:�����L���O3��
		TEX_TYPE_RESULT_UI_RANKING04,				//���U���gUI:�����L���O4��
		TEX_TYPE_RESULT_UI_RANKING05,				//���U���gUI:�����L���O5��

		TEX_TYPE_PAUSE_UI_FRAME,					//�|�[�YUI:�g
		TEX_TYPE_PAUSE_UI_START,					//�|�[�YUI:�ĊJ
		TEX_TYPE_PAUSE_UI_EXIT,						//�|�[�YUI:�I��
		TEX_TYPE_PAUSE_UI_RESTART,					//�|�[�YUI:��蒼��

		TEX_TYPE_JUMP_SMOKE,						//�W�����v�G�t�F�N�g
		TEX_TYPE_EFFECT,							//�G�t�F�N�g
		TEX_TYPE_PLAYER_UI_1P,						//�v���C���[UI:1P
		TEX_TYPE_PLAYER_UI_2P,						//�v���C���[UI:2P
		TEX_TYPE_MAX								//�e�N�X�`���̍ő吔
	} TEX_TYPE;

	CTexture();										//�R���X�g���N�^
	~CTexture();									//�f�X�g���N�^

	void Init(void);								// �e�N�X�`���̐���
	LPDIRECT3DTEXTURE9 GetTexture(TEX_TYPE Type);	// �e�N�X�`���̊��蓖��
	void Uninit(void);								// �I��
private:
	LPDIRECT3DTEXTURE9	m_pTexture[TEX_TYPE_MAX];	//�e�N�X�`��
};

#endif