#//=============================================================================
// �㉺����ǂ̃R���g���[������ [control_up_down_wall.h]
// Author : KUSAKARI KAKERU
//=============================================================================
#ifndef _CONTROL_UP_DOWN_WALL_H_
#define _CONTROL_UP_DOWN_WALL_H_

#include "control.h"

//�O���錾
class CScene;

//================================================
// �}�N����`
//================================================
#define MOVE_UPDOWN_WALL_SPEED	(0.7f)	// �ړ����x
#define MAX_UPDOWN_WALL_SPEED	(0.7f)	// �ړ����x�̍ő�l

//*****************************************************************************
// �L�[�{�[�h�N���X
//*****************************************************************************
class CControlUpDownWall : public CControl
{
public:
	typedef enum
	{
		UP_WALL = 0,		// �ŏ��ɏ�ɏ㏸�����
		DOWN_WALL,			// �ŏ��ɉ��ɉ��~�����
		UP_DOWN_WALL_MAX,
	} UP_DOWN_WALL;

	CControlUpDownWall();				// �R���X�g���N�^
	~CControlUpDownWall();				// �f�X�g���N�^
	HRESULT Init(void);					// ����������
	void Uninit(void);					// �I������
	void Update(CScene *pScene);		// �X�V����

	static CControlUpDownWall *Create(UP_DOWN_WALL type, float moveLimit);	// ��������

private:
	bool m_bUpDown;			// �ǂ̕����Ɉړ����邩
	float m_fMoveLength;	// �ړ���������
	float m_moveLimit;		// �ړ��ł���͈�
	int m_nWaitTime;		// �ړ���̑ҋ@����
};

#endif	//_CONTROL_UP_DOWN_WALL_H_