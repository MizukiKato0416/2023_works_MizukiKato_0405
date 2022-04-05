//===========================================
//�����̏���
//Authore:��������
//===========================================
#ifndef _MOVER_H_
#define _MOVER_H_

#include "main.h"

//================================================
//�}�N����`
//================================================


//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CMover
{
public:
	//�����̎��
	typedef enum
	{
		MOVER_TYPE_NONE = 0,
		MOVER_TYPE_FALL_STOP_RISE,			//���~���Ē�~���㏸����
		MOVER_TYPE_RIGHT_STOP_LEFT,			//�E�ɍs����~�����ɍs��
		MOVER_TYPE_LEFT_STOP_RIGHT,			//���ɍs����~���E�ɍs��
		MOVER_TYPE_FALL_LOWER_LEFT,			//���~���č����ɍ~��
		MOVER_TYPE_FALL_LOWER_RIGHT,		//���~���ĉE���ɍ~��
		MOVER_TYPE_FALL_RANDOM_RIGHT_LEFT,	//���~���Ȃ��獶�E�ɕs�K���Ɉړ�
		MOVER_TYPE_RIGHT_STOP,				//�E�ɍs����~
		MOVER_TYPE_LEFT_STOP,				//���ɍs����~
		MOVER_TYPE_MAX
	} MOVER_TYPE;

	CMover();						//�R���X�g���N�^
	virtual ~CMover();				//�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	D3DXVECTOR3 GetMove(void);					//�ړ��ʎ擾����
	
protected:
	D3DXVECTOR3 m_move;			//�ړ���
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_MOVER_H_