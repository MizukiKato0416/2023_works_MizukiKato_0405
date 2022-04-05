//=============================================================================
//x�t�@�C�����[�h����
//Authore:��������
//=============================================================================
#ifndef _X_LOAD_H_
#define _X_LOAD_H_

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CXload
{
public:
	//�^�C�v
	typedef enum
	{
		X_TYPE_PLAYER_BODY = 0,					//�v���C���[�̑�
		X_TYPE_PLAYER_ARM_R,					//�v���C���[�̉E�r
		X_TYPE_PLAYER_ARM_L,					//�v���C���[�̍��r
		X_TYPE_PLAYER_LEG_R,					//�v���C���[�̉E��
		X_TYPE_PLAYER_LEG_L,					//�v���C���[�̉E��
		X_TYPE_PLAYER_GIRL_BODY,				//�v���C���[���̎q�̑�
		X_TYPE_PLAYER_GIRL_ARM_R,				//�v���C���[���̎q�̉E�r
		X_TYPE_PLAYER_GIRL_ARM_L,				//�v���C���[���̎q�̍��r
		X_TYPE_PLAYER_GIRL_LEG_R,				//�v���C���[���̎q�̉E��
		X_TYPE_PLAYER_GIRL_LEG_L,				//�v���C���[���̎q�̉E��
		X_TYPE_TUTORIAL_START_FLOOR,            //�`���[�g���A���̃X�^�[�g�̏�
		X_TYPE_TUTORIAL_MIDDLE_FLOOR,           //�`���[�g���A���̃~�h���̏�
		X_TYPE_TUTORIAL_GOAL_FLOOR,             //�`���[�g���A���̃S�[���̏�
		X_TYPE_TUTORIAL_MIDDLE_FENCE,           //�`���[�g���A���̃~�h���̍�
		X_TYPE_TUTORIAL_SIDEFENCE,              //�`���[�g���A���̃X�^�[�g�ƃS�[���̃T�C�h��
		X_TYPE_TUTORIAL_BACKFENCE,              //�`���[�g���A���̃X�^�[�g�ƃS�[���̌���
		X_TYPE_TUTORIAL_GOAL_POLE,              //�`���[�g���A���̃S�[���̒�
		X_TYPE_TUTORIAL_GOAL_FLAG,              //�`���[�g���A���̃S�[���̊�
		X_TYPE_GAME_SCAFFOLD,                   //�X�e�[�W�̑���
		X_TYPE_GAME_WALL_UPDOWN,                //�X�e�[�W�̏㉺��
		X_TYPE_GAME_WALL_PILLAR,                //�X�e�[�W�̏㉺�ǂ̒�
		X_TYPE_GAME_FLOOR_DISAPPEAR,            //�X�e�[�W�̏����鏰
		X_TYPE_GAME_FLOOR_ICE,				    //�X�e�[�W�̊��鏰�i�X�j
		X_TYPE_GAME_SPRING,				        //�X�e�[�W�̃o�l
		X_TYPE_RESULT_CROWN,				    //���U���g�̉���
		X_TYPE_CLOUD,							//�_
		X_TYPE_BALLOON,							//�C��
		X_TYPE_AIRSHIP,							//��s�D
		X_TYPE_ARROW,							//���
		X_TYPE_CHECKPOINT,						//�`�F�b�N�|�C���g
		X_TYPE_MAX								//�e�N�X�`���̍ő吔
	} X_TYPE;

	CXload();									//�R���X�g���N�^
	~CXload();									//�f�X�g���N�^

	void Init(void);							// �e�N�X�`���̐���
	LPD3DXMESH GetMesh(X_TYPE type);			// ���b�V���̊��蓖��
	LPD3DXBUFFER GetBuffMat(X_TYPE type);		// �}�e���A���̊��蓖��
	DWORD GetNumMat(X_TYPE type);				// �}�e���A�����̊��蓖��
	void Uninit(void);							// �I��
private:
	LPD3DXMESH m_apMesh[X_TYPE_MAX];			//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER m_apBuffMat[X_TYPE_MAX];		//�}�e���A��(�ގ����)�ւ̃|�C���^
	DWORD m_aNumMat[X_TYPE_MAX];				//�}�e���A����
};

#endif