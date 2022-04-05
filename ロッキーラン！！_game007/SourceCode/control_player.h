#//=============================================================================
// �v���C���[�R���g���[������ [control_player.h]
// Author : ��������
//=============================================================================
#ifndef _CONTROL_PLAYER_H_
#define _CONTROL_PLAYER_H_

#include "control.h"

//�O���錾
class CScene;
class CPlayer;

//================================================
// �}�N����`
//================================================
#define PLAYER_JUMP							(5.0f)	// �W�����v��
#define PLAYER_GRAVITY						(0.3f)	// �d�͂̑傫��
#define PLAYER_MOVE_SPEED					(0.3f)	// �ʏ�ړ��̉����x
#define PLAYER_DIVE_SPEED					(1.2f)	// �_�C�u���̉����x
#define PLAYER_INTERIA_SUBTRACTION			(0.86f)	// �����̌��Z�l
#define PLAYER_MOVE_SPEED_ON_ICE			(0.05f)	// �X�̏��ł̈ړ��̉����x
#define PLAYER_DIVE_SPEED_ON_ICE			(0.35f)	// �X�̏��ł̃_�C�u���̉����x
#define PLAYER_INTERIA_SUBTRACTION_ON_ICE	(0.99f)	// �X�̏��ł̊����̌��Z�l
#define PLAYER_JUMP_SPRING					(12.0f)	// �o�l���g�����W�����v��
#define PLAYER_MOVE_FORWARD_SPRING			(6.0f)	// �o�l���g�������̑O�i��
#define PLAYER_MOVE_STOP_COUNT				(0.02f)	// �v���C���[�̈ړ��ʂ�0�ɂ��鎞�̈ړ��ʂ̒l
#define PLAYER_DIVE_COUNT					(10)	// �v���C���[�̃_�C�u����

//*****************************************************************************
// �v���C���[�R���g���[���N���X
//*****************************************************************************
class CControlPlayer : public CControl
{
public:
	//�����o�֐�
	CControlPlayer();				// �R���X�g���N�^
	~CControlPlayer();				// �f�X�g���N�^
	HRESULT Init(void);				// ����������
	void Uninit(void);				// �I������
	void Update(CScene *pScene);	// �X�V����

	static CControlPlayer *Create(void);		//��������

private:
	//�����o�֐�
	void Move(CPlayer *pPlayer);			//�ړ�����
	void MoveInteria(CPlayer *pPlayer);		//�ړ��̊����ɂ��Ă̏���
	void Rotate(CPlayer *pPlayer);			//��]����
	void Dive(CPlayer *pPlayer);			//�_�C�u����
	void Jump(CPlayer *pPlayer);			//�W�����v����

	D3DXVECTOR3 m_speed;	// �ړ��ʂɉ����鑬��
	bool m_bJump;			// �W�����v���Ă邩�ǂ���
	D3DXVECTOR3 m_rot;		//����
	D3DXVECTOR3 m_moveOld;	//1�t���[���O�̈ړ���
	float m_fObjectiveRot;	//�ړI�̌���
	float m_fNumRot;		//������ς����
	bool m_bRotate;			//��]���Ă��邩�ǂ���
	int m_nDiveTime;		//�_�C�u���Ă��鎞��
	bool m_bStop;			//�X�g�b�v���Ă��邩�ǂ���
	bool m_bDive;			//�_�C�u���Ă邩�ǂ���
};

#endif	//_CONTROL_PLAYER_H_