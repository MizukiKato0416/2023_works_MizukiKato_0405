//=======================================================================
//�G�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"
#include "effect.h"

//========================================================
//�}�N����`
//========================================================
#define ENEMY_SPEED (4.0f)			//���f���̑���
#define ENEMY_SEARCH (400.0f)		//�v���C���[��T���o���͈�
#define ENEMY_SEARCH_ATTACK (100.0f)//�v���C���[���U��������͈�
#define ENEMY_ATTACK (200.0f)		//�v���C���[�ɍU��������͈�
#define ENEMY_DAMAGE (500.0f)		//�v���C���[�ɐ�����΂���鋗��
#define ENEMY_MAX_TEXTURE (256)		//�e�N�X�`���̍ő吔
#define MAX_ENEMY_MODEL (14)		//���f���̍ő吔
#define MAX_ENEMY (25)				//�G�̍ő吔
#define MAX_ENEMY_LIFE (7)			//�G�̃��C�t�̍ő吔
#define GRAVITY (0.3f)				//�d��
#define ENEMY_JUMP (12.0f)			//�W�����v��
#define ENEMY_RAND (float (rand() % 629 + -314) / 100)	//�����_���l
#define ENEMY_STOP_TIME (rand() % 300 + 150)	//�G���X�g�b�v���Ă鎞��
#define ENEMY_SWORD_COLLISION_WIDTH (50.0f)	//���̓����蔻��̕��̒���
#define ENEMY_SWORD_COLLISION_DEPTH (50.0f)	//���̓����蔻��̉��s�̒���


//========================================================
//�����̎��
//========================================================
typedef enum
{
	ENEMY_MOVETYPE_MOVE = 0,	//����
	ENEMY_MOVETYPE_STOP,		//�~�܂�
	ENEMY_MOVETYPE_TURN,		//���
	ENEMY_MOVETYPE_TO_PLAYER_TURN,		//�v���C���[�̕����Ɍ���
	ENEMY_MOVETYPE_TO_PLAYER,	//�v���C���[�Ɍ������ē���
	ENEMY_MOVETYPE_ATTACK,		//�U��
	ENEMY_MOVETYPE_DAMAGE,		//�_���[�W�H������Ƃ�
	ENEMY_MOVETYPE_MAX,
} ENEMY_MOVETYPE;


//========================================================
//���[�V�����̎��
//========================================================
typedef enum
{
	ENEMY_MOTIONTYPE_NEUTRAL = 0,		//�j���[�g�������[�V����
	ENEMY_MOTIONTYPE_MOVE,				//�ړ����[�V����
	ENEMY_MOTIONTYPE_PUNCH,				//�A�N�V�������[�V����
	ENEMY_MOTIONTYPE_DAMAGE,			//�A�N�V�������[�V����

	ENEMY_MOTION_MAX,
} ENEMY_MOTIONTYPE;


//========================================================
//�\���̂̒�`
//========================================================
//�L�[�̍\����
typedef struct
{
	float fPosX;	//�ʒuX
	float fPosY;	//�ʒuY
	float fPosZ;	//�ʒuZ
	float fRotX;	//����X
	float fRotY;	//����Y
	float fRotZ;	//����Z
} ENEMY_KEY;

//�L�[���̍\����
typedef struct
{
	int nFrame;		//�Đ��t���[��
	ENEMY_KEY aKey[MAX_ENEMY_MODEL];		//�e���f���̃L�[�v�f(�p�[�c�̍ő吔)
} ENEMY_KEY_INFO;

//���[�V�������̍\����
typedef struct
{
	bool bLoop;				//���[�v���邩�ǂ���
	int nNumKey;			//�L�[�̑���
	ENEMY_KEY_INFO aKeyInfo[128];	//�L�[�̏��
} ENEMY_MOTION_INFO;

//���f���̍\����
typedef struct
{
	LPD3DXMESH pMesh;				//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;			//�}�e���A��(�ގ����)�ւ̃|�C���^
	DWORD nNumMat;					//�}�e���A����
	LPDIRECT3DTEXTURE9 pTexture[ENEMY_MAX_TEXTURE];	//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3	pos;				//�ʒu
	D3DXVECTOR3 rot;				//����
	D3DXMATRIX mtxWorld;			//���[���h�}�g���b�N�X
	int nIdxModelParent;			//�e�̃C���f�b�N�X
} ENEMY_Model;

//�G�̍\����
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 posOld;						//�O�̈ʒu
	D3DXVECTOR3 posPlayer;					//�v���C���[�̈ʒu�ۑ�
	D3DXVECTOR3 rot;						//����
	D3DXVECTOR3 move;						//�ړ���
	D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X
	ENEMY_Model aModel[MAX_ENEMY_MODEL];			//���f��(�p�[�c)
	int nNumModel;							//���f��(�p�[�c)��
	ENEMY_MOTION_INFO aMotionInfo[ENEMY_MOTION_MAX];	//���[�V�������
	int nNumMotion;							//���[�V������
	int nCntMove;							//�����̃����_�����ɕK�v
	ENEMY_MOTIONTYPE MotionType;			//���݂̃��[�V�����^�C�v
	ENEMY_MOTIONTYPE MotionTypeOld;			//1�O�̃��[�V�����^�C�v
	ENEMY_MOVETYPE MoveType;				//�G�̓����̎��
	bool bLoopMotion;						//���[�v���邩�ǂ���
	int nNumKey;							//�L�[��
	int nKey;								//�L�[No,(���݂̃L�[)
	float fCounterMotion;					//���[�V�����̃J�E���^�[
	bool bJump;								//�W�����v���Ă��邩�ǂ���
	bool bSlash;							//�a��1�����Ă��邩�ǂ���
	float fWidth;							//��
	float fHeight;							//����
	float fDepth;							//���s
	float frotVecX;							//�v���C���[�̊p�x�����߂邽�߂̃x�N�g��
	float frotVecZ;							//�v���C���[�̊p�x�����߂邽�߂̃x�N�g��
	float fToPlayerR;						//�v���C���[�Ƃ̋���
	float fDifferRot;						//�ړI�ƌ��݂�rot�̍�
	int nIdx;								//�e
	int nIdxEffect[MAX_EFFECT];							//�p�[�e�B�N��
	int nLife;								//�̗�
	int nCntStop;							//�~�܂��Ă鎞�Ԃ��J�E���g����ϐ�
	int nCntMoveTime;						//�����Ă��鎞�Ԃ��J�E���g����ϐ�
	float fNumTurnEnemy;					//�ړI��rot
	float fNumEnemy;						//�ړI�ƌ��݂�rot�̍�
	float fSwordCollZ;						//���̓����蔻���Z���̒���
	float fSwordCollX;						//���̓����蔻���X���̒���
	bool bTurnEnemy;						//��]�̊���
	bool bTurnEnemy2;						//�ړG���ĂȂ��Ƃ��̊���
	bool bUse;								//�g�����ǂ���
	bool bDamage;							//�_���[�W���󂯂Ă��邩�ǂ���
	bool bPlayerDamage;						//�v���C���[�Ƀ_���[�W��^���Ă��邩�ǂ���
} ENEMY;

//========================================================
//�v���g�^�C�v�錾
//========================================================
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void MotionEnemy(int nCntEnemy);
void MoveTypeEnemy(int nCntEnemy);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pBeforePos, D3DXVECTOR3 *pMove, float fWidth, float fHeight, float fDepth);
bool CollisionEnemySword(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pBeforePos, D3DXVECTOR3 *pMove, float fWidth, float fHeight, float fDepth);
ENEMY *GetEnemy(void);
ENEMY *GetAttackEnemy(void);
int GetUseEnemy(void);
int GetAllEnemy(void);

#endif // !_ENEMY_H_