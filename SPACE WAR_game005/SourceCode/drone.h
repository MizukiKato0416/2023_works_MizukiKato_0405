//=======================================================================
//�h���[���Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#ifndef _DRONE_H_
#define _DRONE_H_
#include "main.h"
#include "effect.h"

//========================================================
//�}�N����`
//========================================================
#define DRONE_SPEED (1.0f)								//�h���[���̑���
#define MAX_DRONE (6)									//�h���[���̍ő吔
#define DRONE_MAX_TEXTURE (256)							//�e�N�X�`���̍ő吔
#define DRONE_SEARCH (900.0f)							//�v���C���[��T���o���͈�
#define DRONE_ATTACK (200.0f)							//�v���C���[�ɍU��������͈�
#define DRONE_RAND (float (rand() % 629 + -314) / 100)	//�����_���l
#define DRONE_STOP_TIME (rand() % 300 + 150)			//�G���X�g�b�v���Ă鎞��
#define DRONE001_LIFE (3)								//�h���[��001�̗̑�
#define DRONE002_LIFE (3)								//�h���[��002�̗̑�
#define DRONE003_LIFE (10)								//�h���[��003�̗̑�

//========================================================
//�����̎��
//========================================================
typedef enum
{
	DRONE_MOVETYPE_MOVE = 0,			//����
	DRONE_MOVETYPE_STOP,				//�~�܂�
	DRONE_MOVETYPE_TURN,				//���
	DRONE_MOVETYPE_TO_PLAYER_TURN,		//�v���C���[�̕����Ɍ���
	DRONE_MOVETYPE_TO_PLAYER,			//�v���C���[�Ɍ������ē���
	DRONE_MOVETYPE_ATTACK,				//�U��
	DRONE_MOVETYPE_DAMAGE,				//�_���[�W�H������Ƃ�
	DRONE_MOVETYPE_MAX,
} DRONE_MOVETYPE;

//========================================================
//�h���[���̎��
//========================================================
typedef enum
{
	DRONETYPE_001 = 0,		//�����r��
	DRONETYPE_002,			//�����r��
	DRONETYPE_003,			//
	DRONETYPE_MAX,
} DRONETYPE;

//========================================================
//�\���̂̒�`
//========================================================
typedef struct
{
	LPD3DXMESH pMesh;						//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;					//�}�e���A��(�ގ����)�ւ̃|�C���^
	DWORD nNumMat;							//�}�e���A����
	LPDIRECT3DTEXTURE9 pTexture[DRONE_MAX_TEXTURE];	//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3	pos;						//�ʒu
	D3DXVECTOR3	posOld;						//�ʒu
	D3DXVECTOR3 rot;						//����
	D3DXVECTOR3 move;						//�ړ���
	D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X
	int nIdxParent;							//�e�̃C���f�b�N�X
	D3DXVECTOR3 vtxMin;						//�h���[���̒��_�̍ŏ��l
	D3DXVECTOR3 vtxMax;						//�h���[���̒��_�̍ő�l
	bool bUse;								//�g�����g��Ȃ���
	DRONETYPE Type;							//�h���[���̎��
	DRONE_MOVETYPE MoveType;				//�h���[���̓����̎��
	float fWidth;							//��
	float fHeight;							//����
	float fDepth;							//���s
	int nNum;								//�e
	bool bTurnDrone;						//��]�̊���
	bool bTurnDrone2;						//�ړG���ĂȂ��Ƃ��̊���
	bool bDamage;							//�_���[�W���󂯂Ă��邩�ǂ���
	int nCntStop;							//�~�܂��Ă鎞�Ԃ��J�E���g����ϐ�
	int nCntMoveTime;						//�����Ă��鎞�Ԃ��J�E���g����ϐ�
	int nLife;								//�̗�
	float fNumTurnDrone;					//�ړI��rot
	float fNumDrone;						//�ړI�ƌ��݂�rot�̍�
	float fToPlayerR;						//�v���C���[�Ƃ̋���
	float fDifferRot;						//�ړI�ƌ��݂�rot�̍�
	float frotVecX;							//�v���C���[�̊p�x�����߂邽�߂̃x�N�g��
	float frotVecZ;							//�v���C���[�̊p�x�����߂邽�߂̃x�N�g��
	int nIdx;								//�e
	int nIdxLife;							//�̗̓Q�[�W
	int nIdxEffect[MAX_EFFECT];				//�p�[�e�B�N��
} DRONE;

//========================================================
//�v���g�^�C�v�錾
//========================================================
void InitDrone(void);
void UninitDrone(void);
void UpdateDrone(void);
void DrawDrone(void);
void MoveTypeDrone(int nCntDrone);
void SetDrone(D3DXVECTOR3 pos, D3DXVECTOR3 rot, DRONETYPE Type);
void CollisionDrone(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pBeforePos, D3DXVECTOR3 *pMove, float fWidth, float fHeight, float fDepth);
DRONE *GetDrone(void);
int GetAllDrone(void);

#endif // !_DRONE_H_