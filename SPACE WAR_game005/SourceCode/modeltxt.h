//=======================================================================
//���f���Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#ifndef _MODELTXT_H_
#define _MODELTXT_H_
#include "main.h"

//========================================================
//�}�N����`
//========================================================
#define MAX_MODELTXT (512)				//���f���̍ő吔
#define MODELTXT_MAX_TEXTURE (512)		//�e�N�X�`���̍ő吔

//========================================================
//���f���̎��
//========================================================
typedef enum
{
	MODELTXTTYPE_BUILDING_HIGH = 0,			//�����r��
	MODELTXTTYPE_BUILDING_HIGH_02,			//�����r��
	MODELTXTTYPE_BUILDING_LOW,				//�Ⴂ�r��
	MODELTXTTYPE_BUILDING_LOW_02,			//�Ⴂ�r��
	MODELTXTTYPE_CAR,						//��
	MODELTXTTYPE_MAX,
} MODELTXTTYPE;

//========================================================
//8���_�̍\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 pos[8];			//8���_�̈ʒu�ۑ��p�ϐ�
	D3DXVECTOR3 rot[8];			//8���_�̉�]�ۑ��p�ϐ�
	D3DXMATRIX mtxWorld[8];		//8���_�̃��[���h�}�g���b�N�X�ۑ��p�ϐ�
	float fVecX[4];				//�����蔻��Ɏg���x�N�g��
	float fVecX2[4];			//�����蔻��Ɏg���x�N�g��
	float fVecZ[4];				//�����蔻��Ɏg���x�N�g��
	float fVecZ2[4];			//�����蔻��Ɏg���x�N�g��

} VTX;

//========================================================
//�\���̂̒�`
//========================================================
typedef struct
{
	LPD3DXMESH pMesh;				//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;			//�}�e���A��(�ގ����)�ւ̃|�C���^
	DWORD nNumMat;					//�}�e���A����
	LPDIRECT3DTEXTURE9 pTexture[MODELTXT_MAX_TEXTURE];	//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3	pos;				//�ʒu
	D3DXVECTOR3 rot;				//����
	D3DXMATRIX mtxWorld;			//���[���h�}�g���b�N�X
	int nIdxModelTxtParent;			//�e�̃C���f�b�N�X
	D3DXVECTOR3 vtxMin;				//���f���̒��_�̍ŏ��l
	D3DXVECTOR3 vtxMax;				//���f���̒��_�̍ő�l
	bool bUse;						//�g�����g��Ȃ���
	MODELTXTTYPE Type;				//���f���̎��
	float fWidth;					//��
	float fHeight;					//����
	float fDepth;					//���s
	int nNum;						//�e
	int nType;						//���f���̎��
	VTX Vtx;						//���_�\����

} MODELTXT;

//========================================================
//�v���g�^�C�v�錾
//========================================================
void InitModelTxt(void);
void UninitModelTxt(void);
void UpdateModelTxt(void);
void DrawModelTxt(void);
void CollisionModelTxt(D3DXVECTOR3 *pMove, D3DXVECTOR3 *pPosMother, D3DXVECTOR3 *pPosMotherOld, float fWidth);
bool CollisionModelTxtBool(D3DXVECTOR3 *pPos);
bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pBeforePos, D3DXVECTOR3 *pMove, float fWidth, float fHeight, float fDepth);
MODELTXT *GetModelTxt(void);

#endif // !_MODELTXT_H_