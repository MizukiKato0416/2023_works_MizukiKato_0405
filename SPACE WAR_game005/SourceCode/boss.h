//=======================================================================
//�{�X�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================
#ifndef _BOSS_H_
#define _BOSS_H_
#include "main.h"
#include "effect.h"

//========================================================
//�}�N����`
//========================================================
#define BOSS_SPEED (4.0f)								//���f���̑���
#define BOSS_SEARCH (1500.0f)							//�v���C���[��T���o���͈�
#define BOSS_SEARCH_ATTACK (1500.0f)					//�v���C���[���U��������͈�
#define BOSS_ATTACK (1500.0f)							//�v���C���[�ɍU��������͈�
#define BOSS_DAMAGE (1500.0f)							//�v���C���[�ɐ�����΂���鋗��
#define BOSS_MAX_TEXTURE (256)							//�e�N�X�`���̍ő吔
#define MAX_BOSS_MODEL (10)							//���f���̍ő吔
#define MAX_BOSS (4)									//�G�̍ő吔
#define MAX_BOSS_LIFE (50)								//�G�̃��C�t�̍ő吔
#define GRAVITY (0.3f)									//�d��
#define BOSS_JUMP (12.0f)								//�W�����v��
#define BOSS_RAND (float (rand() % 629 + -314) / 100)	//�����_���l
#define BOSS_STOP_TIME (rand() % 300 + 150)			//�G���X�g�b�v���Ă鎞��
#define BOSS_R (150.0f)							//�G�{�X�̓����蔻��̔��a

//========================================================
//�{�X�̎��
//========================================================
typedef enum
{
	BOSSTYPE_NOMAL = 0,	//�m�[�}��
	BOSSTYPE_BOSS,			//�{�X
} BOSSTYPE;

//========================================================
//�����̎��
//========================================================
typedef enum
{
	BOSS_MOVETYPE_MOVE = 0,	//����
	BOSS_MOVETYPE_STOP,		//�~�܂�
	BOSS_MOVETYPE_TURN,		//���
	BOSS_MOVETYPE_TO_PLAYER_TURN,		//�v���C���[�̕����Ɍ���
	BOSS_MOVETYPE_ATTACK,		//�U��
	BOSS_MOVETYPE_DAMAGE,		//�_���[�W�H������Ƃ�
	BOSS_MOVETYPE_MAX,
} BOSS_MOVETYPE;


//========================================================
//���[�V�����̎��
//========================================================
typedef enum
{
	BOSS_MOTIONTYPE_NEUTRAL = 0,		//�j���[�g�������[�V����
	BOSS_MOTIONTYPE_MOVE,				//�ړ����[�V����
	BOSS_MOTIONTYPE_BULLET,				//�e�����[�V����
	BOSS_MOTIONTYPE_BULLET_BIG,			//�e�����[�V����
	BOSS_MOTIONTYPE_DAMAGE,				//��e���[�V����

	BOSS_MOTION_MAX,
} BOSS_MOTIONTYPE;


//========================================================
//�\���̂̒�`
//========================================================

//�e�̍\����
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 rot;						//����
	D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X
} BOSSBULLET;

//�L�[�̍\����
typedef struct
{
	float fPosX;	//�ʒuX
	float fPosY;	//�ʒuY
	float fPosZ;	//�ʒuZ
	float fRotX;	//����X
	float fRotY;	//����Y
	float fRotZ;	//����Z
} BOSS_KEY;

//�L�[���̍\����
typedef struct
{
	int nFrame;		//�Đ��t���[��
	BOSS_KEY aKey[MAX_BOSS_MODEL];		//�e���f���̃L�[�v�f(�p�[�c�̍ő吔)
} BOSS_KEY_INFO;

//���[�V�������̍\����
typedef struct
{
	bool bLoop;						//���[�v���邩�ǂ���
	int nNumKey;					//�L�[�̑���
	BOSS_KEY_INFO aKeyInfo[128];	//�L�[�̏��
} BOSS_MOTION_INFO;

//���f���̍\����
typedef struct
{
	LPD3DXMESH pMesh;				//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;			//�}�e���A��(�ގ����)�ւ̃|�C���^
	DWORD nNumMat;					//�}�e���A����
	LPDIRECT3DTEXTURE9 pTexture[BOSS_MAX_TEXTURE];	//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3	pos;				//�ʒu
	D3DXVECTOR3 rot;				//����
	D3DXMATRIX mtxWorld;			//���[���h�}�g���b�N�X
	int nIdxModelParent;			//�e�̃C���f�b�N�X
} BOSS_Model;

//�G�̍\����
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 posOld;						//�O�̈ʒu
	D3DXVECTOR3 posPlayer;					//�v���C���[�̈ʒu�ۑ�
	D3DXVECTOR3 rot;						//����
	D3DXVECTOR3 move;						//�ړ���
	D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X
	BOSS_Model aModel[MAX_BOSS_MODEL];			//���f��(�p�[�c)
	int nNumModel;							//���f��(�p�[�c)��
	BOSS_MOTION_INFO aMotionInfo[BOSS_MOTION_MAX];	//���[�V�������
	int nNumMotion;							//���[�V������
	int nCntMove;							//�����̃����_�����ɕK�v
	BOSS_MOTIONTYPE MotionType;			//���݂̃��[�V�����^�C�v
	BOSS_MOTIONTYPE MotionTypeOld;			//1�O�̃��[�V�����^�C�v
	BOSS_MOVETYPE MoveType;				//�G�̓����̎��
	bool bLoopMotion;						//���[�v���邩�ǂ���
	int nNumKey;							//�L�[��
	int nKey;								//�L�[No,(���݂̃L�[)
	float fCounterMotion;					//���[�V�����̃J�E���^�[
	bool bJump;								//�W�����v���Ă��邩�ǂ���
	float fWidth;							//��
	float fHeight;							//����
	float fDepth;							//���s
	float frotVecX;							//�v���C���[�̊p�x�����߂邽�߂̃x�N�g��
	float frotVecZ;							//�v���C���[�̊p�x�����߂邽�߂̃x�N�g��
	float fToPlayerR;						//�v���C���[�Ƃ̋���
	float fDifferRot;						//�ړI�ƌ��݂�rot�̍�
	int nIdx;								//�e
	int nIdxLife;							//�̗̓Q�[�W
	int nIdxEffect[MAX_EFFECT];				//�p�[�e�B�N��
	int nLife;								//�̗�
	int nCntStop;							//�~�܂��Ă鎞�Ԃ��J�E���g����ϐ�
	int nCntMoveTime;						//�����Ă��鎞�Ԃ��J�E���g����ϐ�
	int nCntAttack;							//�U��������(�U���p�^�[���ω��̂��߂ɕK�v)
	int nCntAttack2;						//�U��������(�U���p�^�[���ω��̂��߂ɕK�v)
	float fNumTurnBoss;					//�ړI��rot
	float fNumBoss;						//�ړI�ƌ��݂�rot�̍�
	float fSwordCollZ;						//���̓����蔻���Z���̒���
	float fSwordCollX;						//���̓����蔻���X���̒���
	bool bTurnBoss;						//��]�̊���
	bool bTurnBoss2;						//�ړG���ĂȂ��Ƃ��̊���
	bool bUse;								//�g�����ǂ���
	bool bDamage;							//�_���[�W���󂯂Ă��邩�ǂ���
	BOSSTYPE nType;						//�G�̎��
	BOSSBULLET bullet[2];					//�e
} BOSS;

//========================================================
//�v���g�^�C�v�錾
//========================================================
void InitBoss(void);
void UninitBoss(void);
void UpdateBoss(void);
void DrawBoss(void);
void MotionBoss(int nCntBoss);
void MoveTypeBoss(int nCntBoss);
void SetBoss(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void CollisionBoss(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pBeforePos, D3DXVECTOR3 *pMove, float fWidth, float fHeight, float fDepth);
BOSS *GetBoss(void);
BOSS *GetAttackBoss(void);
int GetUseBoss(void);
int GetAllBoss(void);

#endif // !_BOSS_H_