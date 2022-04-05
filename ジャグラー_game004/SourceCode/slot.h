//=======================================================================
//�X���b�g�����Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================
#ifndef _SLOT_H_
#define _SLOT_H_

//========================================================
//�}�N����`
//========================================================
#define MAX_SLOT (4)				//�X���b�g�̍ő吔
#define SLOT_SPEED0 (0.002f)		//�X���b�g�̏����̑���
#define SLOT_SPEED1 (-0.003f)		//�X���b�g�̏����̑���
#define SLOT_SPEED2 (0.004f)		//�X���b�g�̏����̑���
#define SLOT_SPEED3 (-0.005f)		//�X���b�g�̏����̑���
#define SLOT_ACCEL (1.5f)			//�X���b�g�̉����x

//========================================================
//�\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ����x
	D3DXVECTOR3 firstmove;	//�ړ����x�̏����l
	float fTexU;			//�e�N�X�`����U
	float fStopTexU;		//�e�N�X�`����U���~�܂�ꏊ
	float fWidth;			//��
	float fHeight;			//����
	bool bUse;				//�g���Ă��邩�ǂ���
	bool bSpin;				//����Ă��邩�ǂ���
	bool bStop;				//�X�g�b�v�����Ă��邩�ǂ���
} SLOT;

//========================================================
//�v���g�^�C�v�錾
//========================================================
void InitSlot(void);
void UninitSlot(void);
void UpdateSlot(void);
void DrawSlot(void);
void SetSlot(D3DXVECTOR3 pos, float fWidth, float fHeight);
SLOT *GetSlot(void);

#endif // !_SLOT_H_
