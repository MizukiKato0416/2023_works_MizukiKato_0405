//===========================================
//UI����
//Authore:��������
//===========================================
#ifndef _UI_H_
#define _UI_H_
#include "scene2D.h"

//================================================
//�}�N����`
//================================================

//================================================
//�O���錾
//================================================
class CControl;

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CUi : public CScene2D
{
public:
	typedef enum
	{
		UI_TYPE_TITLE_LOGO,					//�^�C�g�����S
		UI_TYPE_TITLE_PRESS,				//�^�C�g��UI:Press����
		UI_TYPE_TITLE_PLAYER_1P,			//�^�C�g��UI:1P
		UI_TYPE_TITLE_PLAYER_2P,			//�^�C�g��UI:2P

		UI_TYPE_MENU_LOGO,					//���j���[���S
		UI_TYPE_MENU_STAR,					//���j���[UI:��
		UI_TYPE_MENU_SELECT_TUTORIAL,		//���j���[UI:�I����(�`���[�g���A��)
		UI_TYPE_MENU_SELECT_GAME,			//���j���[UI:�I����(�Q�[���X�^�[�g)
		UI_TYPE_MENU_SELECT_BACKTITLE,		//���j���[UI:�I����(�^�C�g���ɖ߂�)
		UI_TYPE_MENU_EXPLANATION_TUTORIAL,	//���j���[UI:�I�����̐���(�`���[�g���A��)
		UI_TYPE_MENU_EXPLANATION_GAME,		//���j���[UI:�I�����̐���(�Q�[���X�^�[�g)
		UI_TYPE_MENU_EXPLANATION_BACKTITLE,	//���j���[UI:�I�����̐���(�^�C�g���ɖ߂�)

		UI_TYPE_TUTORIAL_EXPLANATION,		//�`���[�g���A��UI:�������

		UI_TYPE_GAME_COUNTDOWN03,			//�Q�[��UI:�J�E���g�_�E��3
		UI_TYPE_GAME_COUNTDOWN02,			//�Q�[��UI:�J�E���g�_�E��2
		UI_TYPE_GAME_COUNTDOWN01,			//�Q�[��UI:�J�E���g�_�E��1
		UI_TYPE_GAME_START,					//�Q�[��UI:�X�^�[�g
		UI_TYPE_GAME_GOAL,					//�Q�[��UI:�Q�[���N���A
		UI_TYPE_GAME_TIME_UP,				//�Q�[��UI:�^�C���A�b�v
		UI_TYPE_GAME_TIME_COMMA,			//�Q�[��UI:�^�C��(�J���})

		UI_TYPE_RESULT_WIN,					//���U���gUI:Win
		UI_TYPE_RESULT_RANKING01,			//���U���gUI:�����L���O1��
		UI_TYPE_RESULT_RANKING02,			//���U���gUI:�����L���O2��
		UI_TYPE_RESULT_RANKING03,			//���U���gUI:�����L���O3��
		UI_TYPE_RESULT_RANKING04,			//���U���gUI:�����L���O4��
		UI_TYPE_RESULT_RANKING05,			//���U���gUI:�����L���O5��

		UI_TYPE_PAUSE_FRAME,				//�|�[�YUI:�g
		UI_TYPE_PAUSE_START,				//�|�[�YUI:�ĊJ
		UI_TYPE_PAUSE_EXIT,					//�|�[�YUI:�I��
		UI_TYPE_PAUSE_RESTART,				//�|�[�YUI:��蒼��

		UI_TYPE_PLAYER_1P,					//�v���C���[UI:1P
		UI_TYPE_PLAYER_2P,					//�v���C���[UI:2P
		UI_TYPE_MAX,
	}UI_TYPE;

	CUi(int nPriority = PRIORITY_UI);	//�R���X�g���N�^
	~CUi();								//�f�X�g���N�^

										//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CUi *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriolty, UI_TYPE type);
	UI_TYPE GetUIType(void);

private:
	UI_TYPE m_type;						// UI�̎��
	LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	CControl *m_pControl;
	D3DXVECTOR3 m_size;
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_UI_H_