//=======================================================================
//���f���Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#ifndef _MODEL_H_
#define _MODEL_H_
#include "main.h"

//========================================================
//�}�N����`
//========================================================
#define MODEL_SPEED (3.0f)			//���f���̑���
#define MAX_MODEL (10)				//���f���̍ő吔
#define MODEL_MAX_TEXTURE (256)		//�e�N�X�`���̍ő吔

//========================================================
//���f���̎��
//========================================================
typedef enum
{
	BUILDING_HIGH = 0,			//�����r��
	BUILDING_HIGH_02,			//�����r��
	BUILDING_LOW,				//�Ⴂ�r��
	BUILDING_LOW_02,			//�Ⴂ�r��
	CAR,						//��
	TYPE_MAX,
} MODELTYPE;

//========================================================
//�\���̂̒�`
//========================================================
typedef struct
{
	LPD3DXMESH pMesh;				//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;			//�}�e���A��(�ގ����)�ւ̃|�C���^
	DWORD nNumMat;					//�}�e���A����
	LPDIRECT3DTEXTURE9 pTexture[MODEL_MAX_TEXTURE];	//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3	pos;				//�ʒu
	D3DXVECTOR3 rot;				//����
	D3DXMATRIX mtxWorld;			//���[���h�}�g���b�N�X
	int nIdxModelParent;			//�e�̃C���f�b�N�X
	D3DXVECTOR3 vtxMin;		//���f���̒��_�̍ŏ��l
	D3DXVECTOR3 vtxMax;		//���f���̒��_�̍ő�l
	bool bUse;				//�g�����g��Ȃ���
	MODELTYPE Type;			//���f���̎��
	float fWidth;			//��
	float fHeight;			//����
	float fDepth;			//���s
	int nNum;				//�e
} MODEL;

//========================================================
//�v���g�^�C�v�錾
//========================================================
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODELTYPE Type);
bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pBeforePos, D3DXVECTOR3 *pMove, float fWidth, float fHeight, float fDepth);
MODEL *GetModel(void);

#endif // !_MODEL_H_