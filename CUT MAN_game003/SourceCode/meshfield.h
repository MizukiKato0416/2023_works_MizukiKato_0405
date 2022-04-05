//=======================================================================
//���b�V���t�B�[���h�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
#include "main.h"
//========================================================
//�}�N����`
//========================================================
#define MESHFIELD_WIDTH (800.0f*1.0)		//���b�V���t�B�[���h�̕�
#define MESHFIELD_HEIGHT (0.0f*1.0)			//���b�V���t�B�[���h�̍���
#define MESHFIELD_DEPTH (800.0f*1.0f)		//���b�V���t�B�[���h�̉��s
#define MESHFIELD_X (255)						//X�̐�
#define MESHFIELD_Z (255)						//Z�̐�
#define MESHFIELD_TYPE (1)					//���b�V���t�B�[���h�̎��
#define MAX_MESHFIELD (1)					//���b�V���t�B�[���h�̍ő吔

//========================================================
//�\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	float fWidth;			//�u���b�N�̉���
	float fHeight;			//�u���b�N�̏c��
	float fDepth;			//�u���b�N�̉��s
	bool bUse;				//�g�����ǂ���
} MESHFIELD;


//========================================================
//�v���g�^�C�v�錾
//========================================================
HRESULT InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);
MESHFIELD *GetMeshField(void);

#endif // !_MESHFIELD_H_