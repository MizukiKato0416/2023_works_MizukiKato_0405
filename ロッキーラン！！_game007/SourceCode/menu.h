//===========================================
//���j���[����
//Authore:��������
//===========================================
#ifndef _MENU_H_
#define _MENU_H_
#include "scene.h"
#include "scene2D.h"
#include "main.h"

//�O���錾
class CTexture;
class CScene2D;

//================================================
//�}�N����`
//================================================
#define MENU_SELECT_COL						(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))		//�I�𒆂̐F(������)
#define MENU_DEFAULT_COL					(D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f))		//�f�t�H�̐F(�O���[�̕�)
#define MENU_HIDE							(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f))		//��\��

#define MENU_MAX_STAR						(3)										//���̍ő吔
#define MENU_STAR_CREATE_SPAN				(480)									//���̐����Ԋu
#define MENU_LOGO_POSX						(290.0f)								//�^�C�g�����S��posX
#define MENU_LOGO_POSY						(58.0f)									//�^�C�g�����S��posY
#define MENU_LOGO_SIXEX						(650.0f)								//�^�C�g�����S��sizeX
#define MENU_LOGO_SIXEY						(150.0f)								//�^�C�g�����S��sizeY
#define MENU_CHOICES_SPACE					(150.0f)								//�I�����̊Ԋu	
#define MENU_UI_SIZEX						(400.0f)								//�I�����Ƃ��̐�����sizeX
#define MENU_UI_SIZEY						(100.0f)								//�I�����Ƃ��̐�����sizeY
#define MENU_TUTORIAL_BUTTON_POSY			(80.0f)									//�I����:�`���[�g���A����posY
#define MENU_GAME_BUTTON_POSY				(220.0f)								//�I����:�Q�[����posY
#define MENU_EXIT_BUTTON_POSY				(360.0f)								//�I����:�I����posY
#define MENU_EXPLANATION_POSY				(650.0f)								//�I�����̐�����posY
//========================================================
//�\���̂̒�`
//========================================================

//========================================================
//�O���錾
//========================================================
class CUi;
class CScene2D;

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CMenu : public CScene
{
public:
	CMenu();				//�R���X�g���N�^
	~CMenu();				//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	//��ʑJ�ڂ̑I�����{�^��
	typedef enum
	{
		SELECT_TUTORIAL,		//�`���[�g���A���{�^��
		SELECT_GAME,			//�Q�[���{�^��
		SELECT_BACKTITLE,		//�^�C�g���ɖ߂�{�^��
		SELECT_MAX
	}SELECT;

	//�I�����̐���
	typedef enum
	{
		EXPLANATION_TUTORIAL,	//�`���[�g���A������
		EXPLANATION_GAME,		//�Q�[������
		EXPLANATION_EXIT,		//�I������
		EXPLANATION_MAX
	}EXPLANATION;

	//�������̃p�^�[��
	typedef enum
	{
		STARPATTERN_01,
		STARPATTERN_02,
		STARPATTERN_03,
		STARPATTERN_MAX
	}STARPATTERN;

	CUi *m_pMenu;						   //���j���[���S
	CUi *m_apSelect[SELECT_MAX];		   //�e�I����
	CUi *m_apExplanation[EXPLANATION_MAX]; //�e�I�����̐���
	CUi *m_apStar[MENU_MAX_STAR];		   //��
	CScene2D *m_pScene2D;				   //Scene2D�̃|�C���^
	int m_nSelect;						   //���̑I����
	int m_nExplanation;					   //���̑I�����̐���
	int m_nSpan;						   //���̐����Ԋu
	int m_nPattern;						   //�������p�^�[��
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_MENU_H_