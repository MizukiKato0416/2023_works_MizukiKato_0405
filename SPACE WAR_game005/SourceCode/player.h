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
#define PLAYER_SPEED (0.5f)				//���f���̑���
#define PLAYER_SLASH_MOVE (5.0f)		//�a�����̃��f���̑���
#define PLAYER_POWER_SPEED (0.35f)		//���f���̑���
#define PLAYER_SPEED_SPEED (0.8f)		//���f���̑���
#define PLAYER_SPEEDDOWN (0.7f)			//���f���̑����̌�������
#define MAX_PLAYER_SPEED (9.0f)			//���f���̍ő�̑���
#define MAX_PLAYER_POWER_SPEED (7.0f)	//���f���̍ő�̑���
#define MAX_PLAYER_SPEED_SPEED (12.0f)	//���f���̍ő�̑���
#define PLAYER_MAX_TEXTURE (128)		//�e�N�X�`���̍ő吔
#define MAX_PLAYER_MODEL (16)			//���f���̍ő吔
#define GRAVITY (0.3f)					//�d��
#define PLAYER_JUMP (12.0f)				//�W�����v��
#define PLAYER_LIMIT (2400.0f)			//���E�ړ���
#define MAX_PLAYER_LIFE (80)			//�v���C���[�̃��C�t
#define PLAYER_LIFE_WIDTH (450.0f)		//�v���C���[�̃��C�t�̕�
#define SWORD_COLLISION_WIDTH (80.0f)	//���̓����蔻��̕��̒���
#define SWORD_COLLISION_DEPTH (50.0f)	//���̓����蔻��̉��s�̒���

//========================================================
//���[�V�����̎��
//========================================================
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,			//�j���[�g�������[�V����
	MOTIONTYPE_MOVE,				//�ړ����[�V����
	MOTIONTYPE_SHOOT_N,				//�ˌ��m�[�}��
	MOTIONTYPE_SHOOT_P,				//�ˌ��p���[
	MOTIONTYPE_SHOOT_S,				//�ˌ��X�s�[�h
	MOTIONTYPE_SLASH_N,				//�a���m�[�}��
	MOTIONTYPE_SLASH_N1,			//�a���m�[�}��
	MOTIONTYPE_SLASH_N2,			//�a���m�[�}��
	MOTIONTYPE_SLASH_S,				//�a���X�s�[�h
	MOTIONTYPE_SLASH_S1,			//�a���X�s�[�h
	MOTIONTYPE_SLASH_S2,			//�a���X�s�[�h
	MOTIONTYPE_SLASH_P,				//�a���p���[
	MOTIONTYPE_SLASH_P1,			//�a���p���[
	MOTIONTYPE_SLASH_P2,			//�a���p���[
	MOTIONTYPE_DAMAGE,				//��e���[�V����
	MOTIONTYPE_DOWN,				//�_�E�����[�V����
	
	MOTION_MAX,
} MOTIONTYPE;

//========================================================
//�v���C���[�̎��
//========================================================
typedef enum
{
	PLAYERTYPE_NOMAL = 0,	//�m�[�}���^�C�v
	PLAYERTYPE_SPEED,		//�X�s�[�h�^�C�v
	PLAYERTYPE_POWER,		//�p���[�^�C�v
	PLAYERTYPE_MAX,
} PLAYERTYPE;

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
	float fWidth;					//��
	float fHeight;					//����
	float fDepth;					//���s
} Model;

//�e�̍\����
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 rot;						//����
	D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X
} GUN;

//���̍\����
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 rot;						//����
	D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X
} SWORD;

//�v���C���[�̍\����
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 posOld;						//�O�̈ʒu
	D3DXVECTOR3 rot;						//����
	D3DXVECTOR3 rotBullet;					//�e��łu�Ԃ̃v���C���[�̌���
	D3DXVECTOR3 move;						//�ړ���
	D3DXVECTOR3 moveA;						//�����x
	D3DXVECTOR3 VtxPos[4];					//�l���_�̈ʒu
	D3DXVECTOR3 VtxPosSave[4];				//�l���_�̈ʒu�ۑ��p�ϐ�
	D3DXVECTOR3 VtxPosOld[4];				//�l���_�̑O�̈ʒu
	D3DXVECTOR3 VtxRot[4];					//�l���_�̌���
	D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X
	D3DXMATRIX VtxMtxWorld[4];					//4���_�̃��[���h�}�g���b�N�X
	Model aModel[MAX_PLAYER_MODEL];			//���f��(�p�[�c)
	int nNumModel;							//���f��(�p�[�c)��
	MOTION_INFO aMotionInfo[MOTION_MAX];	//���[�V�������
	int nNumMotion;							//���[�V������
	MOTIONTYPE MotionType;					//���݂̃��[�V�����^�C�v
	MOTIONTYPE MotionTypeNext;				//���̃��[�V�����^�C�v
	MOTIONTYPE MotionTypeOld;				//1�O�̃��[�V�����^�C�v
	PLAYERTYPE nType;						//�v���C���[�̃^�C�v
	PLAYERTYPE nTypeNext;					//���̃v���C���[�̃^�C�v
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
	bool bEvolutionButton;					//�i���{�^�������������ǂ���
	bool bEvolution;						//�i�����Ă��邩�ǂ���
	bool bDegenerate;						//�މ����Ă��邩�ǂ���
	bool bWeapon;							//���̕�����g���Ă��邩true�Ȃ猕false�Ȃ�e
	bool bWeaponX;							//x�t�@�C���̓ǂݍ���
	float fWidth;							//��
	float fHeight;							//����
	float fDepth;							//���s
	float fNumTurnPlayer;					//��]�̊����ɕK�v
	float fNumPlayer;						//�ړI�̌���
	float fMoveSpeed;						//��������
	float fMaxSpeed;						//���������̍ő�l
	bool bTurnPlayer;						//��]�����Ă��邩�ǂ���
	bool bMotion;							//���[�V�������Ȃ��ϐ�
	int nIdx;								//�e
	int nLife;								//�̗�
	int nEffect;							//�G�t�F�N�g
	int nTitle;								//�^�C�g��
	bool bFinishMotion;						//���[�V�������I���������ǂ���
	bool bBlendMotion;						//�u�����h���[�V���������邩�ǂ���
	int nNumKeyBlend;						//�u�����h�L�[��
	int nKeyBlend;							//�u�����h�L�[No,(���݂̃L�[)
	float fCounterMotionBlend;				//�u�����h���[�V�����̃J�E���^�[
	int nFrameBlend;						//�u�����h���邽�߂̃t���[����
	int nCounterBlend;						//�u�����h�J�E���^�[

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
bool CollisionSword(D3DXVECTOR3 *pPos, float fWidth);
void InputPlayer(void);
PLAYER *GetPlayer(void);
#endif // !_PLAYER_H_