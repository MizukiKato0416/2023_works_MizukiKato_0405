//===========================================
//�v���C���[�̃��[�V��������
//Author:��������
//===========================================
#ifndef _MOTION_PLAYER_H_
#define _MOTION_PLAYER_H_
#include "main.h"
#include "motion.h"
#include "player.h"

//================================================
//�}�N����`
//================================================
#define MOTION_PLAYER_MAX_KEY_INFO	(128)	//�L�[�̏��̍ő�l
#define MOTION_PLAYER_MAX_STRING	(128)	//������̍ő�l

//================================================
//�\���̂̒�`
//================================================
//�L�[�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//����
} KEY;

//�L�[���̍\����
typedef struct
{
	int nFrame;						//�Đ��t���[��
	KEY aKey[MAX_PLAYER_MODEL];		//�e���f���̃L�[�v�f(�p�[�c�̍ő吔)
} KEY_INFO;

//���[�V�������̍\����
typedef struct
{
	bool bLoop;				//���[�v���邩�ǂ���
	int nNumKey;			//�L�[�̑���
	KEY_INFO aKeyInfo[MOTION_PLAYER_MAX_KEY_INFO];	//�L�[�̏��
} MOTION_INFO;

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CMotionPlayer:CMotion
{
public:
	//���[�V�����̎��
	typedef enum
	{
		MOTION_PLAYER_TYPE_NEUTRAL = 0,			//�j���[�g����
		MOTION_PLAYER_TYPE_MOVE,				//�ړ�
		MOTION_PLAYER_TYPE_STEP,				//���ݍ���
		MOTION_PLAYER_TYPE_JUMP,				//�W�����v
		MOTION_PLAYER_TYPE_LAND,				//���n
		MOTION_PLAYER_TYPE_DIVE,				//�_�C�u
		MOTION_PLAYER_TYPE_DIVE_LAND,			//�_�C�u�̒��n
		MOTION_PLAYER_TYPE_APPLAUSE,			//����
		MOTION_PLAYER_TYPE_GLAD_01,				//���01
		MOTION_PLAYER_TYPE_GLAD_02,				//���02
		MOTION_PLAYER_TYPE_GLAD_03,				//���03
		MOTION_PLAYER_TYPE_GLAD_04,				//���04
		MOTION_PLAYER_TYPE_MAX
	} MOTION_PLAYER_TYPE;

	CMotionPlayer();			//�R���X�g���N�^
	~CMotionPlayer();			//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(CPlayer *pPlayer);
	void Uninit(void);
	void Update(CPlayer *pPlayer);

	static CMotionPlayer *Create(CPlayer *pPlayer);		//��������
	void SetMotion(MOTION_PLAYER_TYPE type);			//���[�V�����ݒ菈��
	MOTION_PLAYER_TYPE GetMotion(void);					//���[�V�����擾����
	bool GetConnect(void);								//���[�V�������Ȃ��Ă���Œ����ǂ����擾����

private:
	MOTION_INFO m_aInfo[MOTION_PLAYER_TYPE_MAX];		//���[�V�������
	MOTION_PLAYER_TYPE m_type;							//���݂̃��[�V�����^�C�v
	MOTION_PLAYER_TYPE m_typeNext;						//���̃��[�V�����^�C�v
	int m_nNumKey;										//�L�[��
	int m_nKey;											//�L�[No,(���݂̃L�[)
	int m_nKeyNext;										//�L�[No,(���̃L�[)
	int m_nKeyOld;										//�L�[No,(1�t���[���O�̃L�[)
	float m_fCounter;									//���[�V�����̃J�E���^�[
	bool m_bConnect;									//���[�V�������Ȃ��Ă��邩�ǂ���
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_MOTION_PLAYER_H_