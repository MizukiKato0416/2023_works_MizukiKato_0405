//=======================================================================
//���b�V���t�B�[���h(����)�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#ifndef _MESHSPHERE_H_
#define _MESHSPHERE_H_
#include "main.h"
//========================================================
//�}�N����`
//========================================================
#define MESHSPHERE_WIDTH (5000.0f*1.0f)		//���b�V���t�B�[���h�̕�



#define MESHSPHERE_HEIGHT (6000.0f*1.0f)		//���b�V���t�B�[���h�̍���
#define MESHSPHERE_DEPTH (1000.0f*1.0f)		//���b�V���t�B�[���h�̉��s
#define MESHSPHERE_X (32)					//X�̐�
#define MESHSPHERE_Y (8)					//Y�̐�(X / 2 - 1)
#define MESHSPHERE_TYPE (1)					//���b�V���t�B�[���h�̎��
#define MAX_MESHSPHERE (1)					//���b�V���t�B�[���h�̍ő吔

//========================================================
//�\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	float fWidth;			//�u���b�N�̉���
	float fHeight;			//�u���b�N�̏c��
	float fDepth;			//�u���b�N�̉��s
	bool bUse;				//�g�����ǂ���
	
} MESHSPHERE;


//========================================================
//�v���g�^�C�v�錾
//========================================================
HRESULT InitMeshSphere(void);
void UninitMeshSphere(void);
void UpdateMeshSphere(void);
void DrawMeshSphere(void);
MESHSPHERE *GetMeshSphere(void);

#endif // !_MESHSPHERE_H_