#//=============================================================================
// �^�C�g���G���^�[�����R���g���[������ [control_title_enter.h]
// Author : KUSAKARI KAKERU
//=============================================================================
#ifndef _CONTROL_TITLE_ENTER_H_
#define _CONTROL_TITLE_ENTER_H_

#include "control.h"

//�O���錾
class CScene;

//*****************************************************************************
// �^�C�g���G���^�[�R���g���[���N���X
//*****************************************************************************
class CControlTitleEnter : public CControl
{
public:
	CControlTitleEnter();					// �R���X�g���N�^
	~CControlTitleEnter();					// �f�X�g���N�^
	HRESULT Init(void);						// ����������
	void Uninit(void);						// �I������
	void Update(CScene *pScene);			// �X�V����
	static CControlTitleEnter *Create();	// ��������

private:
	int m_nCount;							// �J�E���g
	D3DXCOLOR m_col;						//�|���S���̐F
	bool m_bAlphaUp;						// �A���t�@�x���グ�邩�ǂ���
};

#endif	//_CONTROL_TITLE_LOGO_H_