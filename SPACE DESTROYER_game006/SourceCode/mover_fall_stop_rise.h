//===========================================
//�~�����Ē�~���㏸���铮���̏���
//Authore:��������
//===========================================
#ifndef _MOVER_FALL_STOP_RISE_H_
#define _MOVER_FALL_STOP_RISE_H_
#include "mover.h"

//================================================
//�}�N����`
//================================================
#define MOVER_FALL_SPEED			(1.0f)		//���~����X�s�[�h
#define MOVER_RISE_SPEED			(-1.0f)		//�㏸����X�s�[�h
#define MOVER_FALL_FINISH_COUNT		(120)		//���~����߂�܂ł̃J�E���g
#define MOVER_STOP_FINISH_COUNT		(300)		//��~����߂�܂ł̃J�E���g

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CMoverFallStopRise : public CMover
{
public:
	CMoverFallStopRise();				//�R���X�g���N�^
	~CMoverFallStopRise();				//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CMoverFallStopRise *Create(void);

private:
	//�����̎��
	typedef enum
	{
		MOVE_TYPE_NONE = 0,
		MOVE_TYPE_FALL,
		MOVE_TYPE_STOP,
		MOVE_TYPE_RISE,
		MOVE_TYPE_MAX
	} MOVE_TYPE;

	int m_nFrameCounter;				//Frame�J�E���g�p�ϐ�
	MOVE_TYPE m_moveType;				//�����̎��
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_MOVER_FALL_STOP_RISE_H_