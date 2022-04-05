//=======================================================================
//�v���C���[�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"

//========================================================
//�}�N����`
//========================================================
#define PLAYER_SPEED (7.0f)				//���f���̑���
#define PLAYER_MAX_TEXTURE (128)		//�e�N�X�`���̍ő吔
#define MAX_PLAYER_MODEL (14)			//���f���̍ő吔
#define GRAVITY (0.3f)					//�d��
#define PLAYER_JUMP (12.0f)				//�W�����v��
#define MAX_PLAYER_LIFE (20)			//�v���C���[�̃��C�t
#define SWORD_COLLISION_WIDTH (80.0f)	//���̓����蔻��̕��̒���
#define SWORD_COLLISION_DEPTH (50.0f)	//���̓����蔻��̉��s�̒���

//========================================================
//���[�V�����̎��
//========================================================
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,			//�j���[�g�������[�V����
	MOTIONTYPE_MOVE,				//�ړ����[�V����
	MOTIONTYPE_PUNCH,				//�A�N�V�������[�V����
	MOTIONTYPE_SLASH,				//�A�N�V�������[�V����
	MOTIONTYPE_SLASH03,				//�A�N�V�������[�V����
	MOTIONTYPE_SLASH04,				//��]�؂�
	MOTIONTYPE_DIFENCE,				//�K�[�h���[�V����
	
	MOTION_MAX,
} MOTIONTYPE;


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
} KEY;

//�L�[���̍\����
typedef struct
{
	int nFrame;		//�Đ��t���[��
	KEY aKey[MAX_PLAYER_MODEL];		//�e���f���̃L�[�v�f(�p�[�c�̍ő吔)
} KEY_INFO;

//���[�V�������̍\����
typedef struct
{
	bool bLoop;				//���[�v���邩�ǂ���
	int nNumKey;			//�L�[�̑���
	KEY_INFO aKeyInfo[128];	//�L�[�̏��
} MOTION_INFO;

//���f���̍\����
typedef struct
{
	LPD3DXMESH pMesh;				//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;			//�}�e���A��(�ގ����)�ւ̃|�C���^
	DWORD nNumMat;					//�}�e���A����
	LPDIRECT3DTEXTURE9 pTexture[PLAYER_MAX_TEXTURE];	//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3	pos;				//�ʒu
	D3DXVECTOR3 rot;				//����
	D3DXMATRIX mtxWorld;			//���[���h�}�g���b�N�X
	int nIdxModelParent;			//�e�̃C���f�b�N�X
	D3DXVECTOR3 vtxMax;				//���_���
	D3DXVECTOR3 vtxMin;				//���_���
	float fWidth;							//��
	float fHeight;							//����
	float fDepth;							//���s
} Model;

//�v���C���[�̍\����
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 posOld;						//�O�̈ʒu
	D3DXVECTOR3 rot;						//����
	D3DXVECTOR3 move;						//�ړ���
	D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X
	Model aModel[MAX_PLAYER_MODEL];			//���f��(�p�[�c)
	int nNumModel;							//���f��(�p�[�c)��
	MOTION_INFO aMotionInfo[MOTION_MAX];	//���[�V�������
	int nNumMotion;							//���[�V������
	MOTIONTYPE MotionType;					//���݂̃��[�V�����^�C�v
	MOTIONTYPE MotionTypeNext;				//���̃��[�V�����^�C�v
	MOTIONTYPE MotionTypeOld;				//1�O�̃��[�V�����^�C�v
	bool bLoopMotion;						//���[�v���邩�ǂ���
	int nNumKey;							//�L�[��
	int nKey;								//�L�[No,(���݂̃L�[)
	int nKeyOld;							//�L�[No,(1�t���[���O�̃L�[)
	float fCounterMotion;					//���[�V�����̃J�E���^�[
	bool bJump;								//�W�����v���Ă��邩�ǂ���
	bool bSlash;							//�a��1�����Ă��邩�ǂ���
	bool bUse;								//�g���Ă��邩�ǂ���
	bool bDamage;							//�_���[�W���󂯂Ă��邩�ǂ���
	bool bDifence;							//�Ńt�F���X���Ă��邩�ǂ���
	float fWidth;							//��
	float fHeight;							//����
	float fDepth;							//���s
	float fNumTurnPlayer;					//��]�̊����ɕK�v
	bool bTurnPlayer;						//��]�����Ă��邩�ǂ���
	int nIdx;								//�e
	int nLife;								//�̗�
	int nEffect;							//�G�t�F�N�g
	int nTitle;								//�^�C�g��
} PLAYER;

//========================================================
//�v���g�^�C�v�錾
//========================================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void MotionPlayer(void);
bool CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pBeforePos, D3DXVECTOR3 *pMove, float fWidth, float fHeight, float fDepth);
bool CollisionSword(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pBeforePos, D3DXVECTOR3 *pMove, float fWidth, float fHeight, float fDepth);
PLAYER *GetPlayer(void);
Model *GetSword(void);

#endif // !_PLAYER_H_