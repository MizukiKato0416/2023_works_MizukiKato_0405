#//=============================================================================
// ���j���[���R���g���[������ [control_menu_star.h]
// Author : ��������
//=============================================================================
#ifndef _CONTROL_MENU_STAR_H_
#define  _CONTROL_MENU_STAR_H_

#include "control.h"

//================================================
//�O���錾
//================================================
class CScene;

//================================================
//�}�N����`
//================================================
#define STAR_COL				(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))		//�\��
#define STAR_HIDE				(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f))		//��\��
#define STAR_LOWERLIMIT_POSY	(510.0f)								//posY�̉���
//*****************************************************************************
// ���j���[���R���g���[���N���X
//*****************************************************************************
class CControlMenuStar : public CControl
{
public:
	CControlMenuStar();					// �R���X�g���N�^
	~CControlMenuStar();				// �f�X�g���N�^
	HRESULT Init(void);					// ����������
	void Uninit(void);					// �I������
	void Update(CScene *pScene);		// �X�V����
	static CControlMenuStar *Create();	// ��������

private:
	D3DXCOLOR m_col;					//�F
	float m_fMaxMoveX;					// �ړ��ʂ̍ő�lX
	float m_fMaxMoveY;					// �ړ��ʂ̍ő�lX
	int m_nFrame;						//�t���[����
};

#endif	//_CONTROL_TITLE_LOGO_H_