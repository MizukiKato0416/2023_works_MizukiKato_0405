//=============================================================================
// �^�C�g��2P�摜�R���g���[������ [control_title_2p.h]
// Author : KUSAKARI KAKERU
//=============================================================================
#ifndef _CONTROL_TITLE_2P_H_
#define _CONTROL_TITLE_2P_H_

#include "control.h"

//================================================
//�}�N����`
//================================================
#define TITLE_2P_GRAVITY	(0.1f)	//�d��
#define TITLE_2P_RISE		(9.5f)	//�㏸��
#define TITLE_2P_STOP_TIME	(90)	//�X�g�b�v�����鎞��

//================================================
//�O���錾
//================================================
class CScene;

//*****************************************************************************
// �^�C�g��2P�摜�R���g���[���N���X
//*****************************************************************************
class CControlTitle2P : public CControl
{
public:
	CControlTitle2P();					// �R���X�g���N�^
	~CControlTitle2P();					// �f�X�g���N�^
	HRESULT Init(void);					// ����������
	void Uninit(void);					// �I������
	void Update(CScene *pScene);		// �X�V����
	static CControlTitle2P *Create();	// ��������

private:
	int m_nStop;						// �ŏ��ɃX�g�b�v�����鎞��
};

#endif	//_CONTROL_TITLE_2P_H_