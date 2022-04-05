//=============================================================================
// �S�[���̃|���S�����o������ [control_goal.h]
// Author : ��ˌ�
//=============================================================================
#ifndef _CONTROL_GOAL_H_
#define _CONTROL_GOAL_H_

#include "control.h"

//�O���錾
class CScene;

//*****************************************************************************
// �^�C�g�����S�R���g���[���N���X
//*****************************************************************************
class CControlGoal : public CControl
{
public:
	CControlGoal();						// �R���X�g���N�^
	~CControlGoal();					// �f�X�g���N�^
	HRESULT Init(void);					// ����������
	void Uninit(void);					// �I������
	void Update(CScene *pScene);		// �X�V����
	static CControlGoal *Create();		// ��������

private:
	float m_fMaxMove;
};

#endif	//_CONTROL_GOAL_H_