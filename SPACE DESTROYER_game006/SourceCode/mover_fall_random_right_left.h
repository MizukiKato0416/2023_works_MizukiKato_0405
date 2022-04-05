//===========================================
//�~���Ȃ��烉���_���ō��E�ɍs�������̏���
//Authore:��������
//===========================================
#ifndef _MOVER_FALL_RANDOM_RIGHT_LEFT_H_
#define _MOVER_FALL_RANDOM_RIGHT_LEFT_H_
#include "mover.h"

//================================================
//�}�N����`
//================================================
#define MOVER_FALL_RANDOM_RIGHT_LEFT_SPEED			(2.0f)					//���~����X�s�[�h
#define MOVER_RANDOM_RIGHT_LEFT_SPEED				(2.0f)					//���E���ɍs���X�s�[�h
#define MOVER_RIGHT_LEFT_FINISH_COUNT				(rand() % 1020 + 60)	//�ړ��ʂ�ς���^�C�~���O�̃J�E���g

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CMoverFallRandomRightLeft : public CMover
{
public:
	CMoverFallRandomRightLeft();				//�R���X�g���N�^
	~CMoverFallRandomRightLeft();				//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CMoverFallRandomRightLeft *Create(void);

private:
	//�����̎��
	typedef enum
	{
		MOVE_TYPE_NONE = 0,
		MOVE_TYPE_LOWER_LEFT,	//����
		MOVE_TYPE_LOWER_RIGHT,	//�E��
		MOVE_TYPE_MAX
	} MOVE_TYPE;

	int m_nFrameCounter;				//Frame�J�E���g�p�ϐ�
	MOVE_TYPE m_moveType;				//�����̎��
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_MOVER_FALL_RANDOM_RIGHT_LEFT_H_