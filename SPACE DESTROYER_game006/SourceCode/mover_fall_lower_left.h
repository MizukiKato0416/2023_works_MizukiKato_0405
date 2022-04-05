//===========================================
//�~�����č����ɍs�������̏���
//Authore:��������
//===========================================
#ifndef _MOVER_FALL_LOWER_LEFT_H_
#define _MOVER_FALL_LOWER_LEFT_H_
#include "mover.h"

//================================================
//�}�N����`
//================================================
#define MOVER_LOWER_LEFT_FALL_SPEED		(1.5f)		//���~����X�s�[�h
#define MOVER_LOWER_LEFT_SPEED			(1.5f)		//�����ɍs���X�s�[�h
#define MOVER_FALL_FINISH_COUNT			(120)		//���~����߂�܂ł̃J�E���g

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CMoverFallLowerLeft : public CMover
{
public:
	CMoverFallLowerLeft();				//�R���X�g���N�^
	~CMoverFallLowerLeft();				//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CMoverFallLowerLeft *Create(void);

private:
	//�����̎��
	typedef enum
	{
		MOVE_TYPE_NONE = 0,
		MOVE_TYPE_FALL,
		MOVE_TYPE_LOWER_LEFT,
		MOVE_TYPE_MAX
	} MOVE_TYPE;

	int m_nFrameCounter;				//Frame�J�E���g�p�ϐ�
	MOVE_TYPE m_moveType;				//�����̎��
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_MOVER_FALL_LOWER_LEFT_H_