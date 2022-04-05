//===========================================
//���ɍs����~���铮���̏���
//Authore:��������
//===========================================
#ifndef _MOVER_LEFT_STOP_H_
#define _MOVER_LEFT_STOP_H_
#include "mover.h"

//================================================
//�}�N����`
//================================================
#define MOVER_LEFT_STOP_LEFT_SPEED			(-1.0f)		//���ɐi�ރX�s�[�h
#define MOVER_LEFT_STOP_LEFT_FINISH_COUNT	(300)		//���ɐi�ނ̂���߂�܂ł̃J�E���g

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CMoverLeftStop : public CMover
{
public:
	CMoverLeftStop();				//�R���X�g���N�^
	~CMoverLeftStop();				//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CMoverLeftStop *Create(void);

private:
	//�����̎��
	typedef enum
	{
		MOVE_TYPE_NONE = 0,
		MOVE_TYPE_LEFT,
		MOVE_TYPE_STOP,
		MOVE_TYPE_MAX
	} MOVE_TYPE;

	int m_nFrameCounter;				//Frame�J�E���g�p�ϐ�
	MOVE_TYPE m_moveType;				//�����̎��
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_MOVER_LEFT_STOP_H_