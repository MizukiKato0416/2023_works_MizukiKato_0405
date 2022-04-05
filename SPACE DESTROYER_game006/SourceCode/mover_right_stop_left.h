//===========================================
//���ɍs����~���E�ɍs�������̏���
//Authore:��������
//===========================================
#ifndef _MOVER_RIGHT_STOP_LEFT_H_
#define _MOVER_RIGHT_STOP_LEFT_H_
#include "mover.h"

//================================================
//�}�N����`
//================================================
#define MOVER_RIGHT_SPEED			(1.0f)		//�E�ɐi�ރX�s�[�h
#define MOVER_LEFT_SPEED			(-1.0f)		//���ɐi�ރX�s�[�h
#define MOVER_RIGHT_FINISH_COUNT	(300)		//�E�ɐi�ނ̂���߂�܂ł̃J�E���g
#define MOVER_STOP_FINISH_COUNT		(300)		//��~����߂�܂ł̃J�E���g

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CMoverRightStopLeft : public CMover
{
public:
	CMoverRightStopLeft();				//�R���X�g���N�^
	~CMoverRightStopLeft();				//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CMoverRightStopLeft *Create(void);

private:
	//�����̎��
	typedef enum
	{
		MOVE_TYPE_NONE = 0,
		MOVE_TYPE_RIGHT,
		MOVE_TYPE_STOP,
		MOVE_TYPE_LEFT,
		MOVE_TYPE_MAX
	} MOVE_TYPE;

	int m_nFrameCounter;				//Frame�J�E���g�p�ϐ�
	MOVE_TYPE m_moveType;				//�����̎��
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_MOVER_RIGHT_STOP_LEFT_H_