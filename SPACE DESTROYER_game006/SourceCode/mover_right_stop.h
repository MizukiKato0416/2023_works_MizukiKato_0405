//===========================================
//���ɍs����~���铮���̏���
//Authore:��������
//===========================================
#ifndef _MOVER_RIGHT_STOP_H_
#define _MOVER_RIGHT_STOP_H_
#include "mover.h"

//================================================
//�}�N����`
//================================================
#define MOVER_RIGHT_STOP_RIGHT_SPEED			(1.0f)		//�E�ɐi�ރX�s�[�h
#define MOVER_RIGHT_STOP_RIGHT_FINISH_COUNT		(300)		//�E�ɐi�ނ̂���߂�܂ł̃J�E���g

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CMoverRightStop : public CMover
{
public:
	CMoverRightStop();				//�R���X�g���N�^
	~CMoverRightStop();				//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CMoverRightStop *Create(void);

private:
	//�����̎��
	typedef enum
	{
		MOVE_TYPE_NONE = 0,
		MOVE_TYPE_RIGHT,
		MOVE_TYPE_STOP,
		MOVE_TYPE_MAX
	} MOVE_TYPE;

	int m_nFrameCounter;				//Frame�J�E���g�p�ϐ�
	MOVE_TYPE m_moveType;				//�����̎��
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_MOVER_RIGHT_STOP_H_