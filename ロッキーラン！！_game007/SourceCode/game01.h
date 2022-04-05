//===========================================
//�Q�[������
//Author:��������
//===========================================
#ifndef _GAME01_H_
#define _GAME01_H_
#include "scene.h"
#include "scene2D.h"
#include "main.h"
#include "player.h"

//�O���錾
class CMeshField;
class CMeshSphere;
class CScore;
class CModelSingle;
class CUi;
class CTimer;
class CPause;
class CScene3D;

//================================================
//�}�N����`
//================================================
#define GAME_MAX_UI_NUM					(3)			//UI�̍ő吔

#define GAME_START_FLOOR_POS_Z			(-1870.0)	//�X�^�[�g����Z���W
#define GAME_FENCE_POS_X				(310.0f)	//�t�F���X��X���W
#define GAME_FENCE_POS_Y				(10.0f)		//�t�F���X��Y���W

#define GAME_PLAYERNUMBER_TEX_POS_Y		(60.0f)		//�v���C���[�i���o�[��posY
#define GAME_PLAYERNUMBER_TEX_SIZE_X	(360.0f)	//�v���C���[�i���o�[��sizeX
#define GAME_PLAYERNUMBER_TEX_SIZE_Y	(300.0f)	//�v���C���[�i���o�[��sizeY
#define GAME_1P_TEX_POS_X				(80.0f)		//1P�e�N�X�`����posX
#define GAME_2P_TEX_POS_X				(1190.0f)	//2P�e�N�X�`����posX

#define GAME_SCAFFOLD_1ST_POS_X			(-260.0f)	//�����1��ڂ�X���W(����񍶁j
#define GAME_SCAFFOLD_2ND_POS_X			(-195.0f)	//�����2��ڂ�X���W(����񍶁j
#define GAME_SCAFFOLD_3RD_POS_X			(-130.0f)	//�����3��ڂ�X���W(����񍶁j
#define GAME_SCAFFOLD_4TH_POS_X			(-65.0f)	//�����4��ڂ�X���W(����񍶁j
#define GAME_SCAFFOLD_MOVE_X			(130.0f)	//����̉��ׂƂ�X��
#define GAME_SCAFFOLD_POS_Z				(-1650.0f)	//�����1��ڂ�Z���W
#define GAME_SCAFFOLD_MOVE_Z			(170.0f)	//����̎��̗�Ƃ�Z��

#define GAME_FLOOR_ICE_POS_X			(-280.0f)	//�X�̏���1��ڂ�X���W(����񍶁j
#define GAME_FLOOR_ICE_MOVE_X			(80.0f)		//�X�̏���1��ڂ���ɂ��̐����𑫂����Y��ɕ���
#define GAME_FLOOR_ICE_POS_Y			(0.0f)		//�X�̏���1��ڂ�Y���W
#define GAME_FLOOR_ICE_POS_Z			(-800.0f)	//�X�̏���1��ڂ�Z���W
#define GAME_FLOOR_ICE_MOVE_Z			(80.0f)		//�X�̏��̈��ڂ���ɂ��̐����𑫂����Y��ɕ���

#define GAME_MIDDLE_FLOOR_POS_Z			(250.0f)	//�~�h�����i��ځj��Z���W
#define GAME_MIDDLE_FLOOR_MOVE_Z		(500.0f)	//�~�h�����̈�ڂ���ɂ��̐����𑫂����Y��ɕ���

#define GAME_WALL_UPDOWN_POS_X			(-213.0f)	//�㉺�ǂ̈���X���W(����񍶁j
#define GAME_WALL_UPDOWN_MOVE_X			(142.0f)	//�㉺�ǂ𓙊Ԋu�Œu�����߂̐��l
#define GAME_WALL_UPDOWN_POS_Z			(200.0f)	//�㉺�ǂ̈��ڂ�Z���W
#define GAME_WALL_UPDOWN_MOVE_Z			(500.0f)	//�㉺�ǂ𓙊Ԋu�Œu�����߂̐��l
#define GAME_WALL_PILLAR_POS_X			(-284.0f)	//�㉺�ǂ̈���Z���W(����񍶁j
#define GAME_WALL_PILLAR_MOVE_X			(142.0f)	//�㉺�ǂ𓙊Ԋu�Œu�����߂̐��l

#define GAME_FLOOR_DISAPPEAR_POS_X		(-280.0f)	//�����鏰�̈��ڂ�X���W(����񍶁j
#define GAME_FLOOR_DISAPPEAR_MOVE_X		(80.0f)		//�����鏰�̈��ڂ���ɂ��̐����𑫂����Y��ɕ���
#define GAME_FLOOR_DISAPPEAR_POS_Y		(0.0f)		//�����鏰�̈��ڂ�Y���W
#define GAME_FLOOR_DISAPPEAR_POS_Z		(1540.0f)	//�����鏰�̈��ڂ�Z���W
#define GAME_FLOOR_DISAPPEAR_MOVE_Z		(80.0f)		//�����鏰�̈��ڂ���ɂ��̐����𑫂����Y��ɕ���

#define GAME_GOAL_FLOOR_POS_Y			(150.0f)	//�S�[������Y���W
#define GAME_GOAL_FLOOR_POS_Z			(2710.0f)	//�S�[������Z���W

#define GAME_POLE_POS_X					(280.0f)	//�S�[������X���W
#define GAME_POLE_POS_Y					(0.0f)		//�S�[������Y���W

#define GAME_SPRING_POS_X				(150.0f)	//�o�l��posX
#define GAME_SPRING_POS_Z				(2450.0f)	//�o�l��posZ

#define GAME_CHECKPOINT01_POS_X			(310.0f)	//�`�F�b�N�|�C���g01��posX
#define GAME_CHECKPOINT01_POS_Y			(60.0f)		//�`�F�b�N�|�C���g01��posY
#define GAME_CHECKPOINT01_POS_Z			(14.0f)		//�`�F�b�N�|�C���g01��posZ
#define GAME_CHECKPOINT02_POS_X			(310.0f)	//�`�F�b�N�|�C���g02��posX
#define GAME_CHECKPOINT02_POS_Y			(60.0f)		//�`�F�b�N�|�C���g02��posY
#define GAME_CHECKPOINT02_POS_Z			(1487.0f)	//�`�F�b�N�|�C���g02��posZ

#define GAME_SEPARATE_MESH				(20000.0f)	//���b�V���t�B�[���h�ƃ��b�V���X�t�B�A�̕�����

#define GAME_MAX_MODEL					(300)		//�X�e�[�W�ɔz�u���郂�f���̍ő吔
#define GAME_COUNT_DOWN_COUNT			(60)		//�J�E���g�_�E����\�����鎞��
#define GAME_COUNT_DOWN_POS_Y			(240)		//�J�E���g�_�E����Y���W
#define GAME_NEXT_SCENE_COUNT			(300)		//���̃V�[���ɐi�ނ܂ł̃J�E���g
#define GAME_PLAYER_CREATE_POS_Y		(40.0f)		//�v���C���[������y���W
#define GAME_PLAYER_INITCREATE_POS_Z	(-1870.0f)	//�X�^�[�g�n�_�̃v���C���[������z���W
#define GAME_PLAYER_CHECK_01_POS_Z		(50.0f)		//�`�F�b�N�|�C���g1�n�_�̃v���C���[������z���W
#define GAME_PLAYER_INITCREATE_POS_X	(200.0f)	//�X�^�[�g�n�_�̃v���C���[1�̐�����x���W
#define GAME_PLAYER_INITCREATE_WIDTH	(400.0f)	//�X�^�[�g�n�_�̃v���C���[�̐�����x���W�̊Ԋu

//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CGame01 : public CScene
{
public:
	//�t�F�[�Y
	typedef enum
	{
		GAME01_PHASE_NONE = 0,
		GAME01_PHASE_SHOW_STAGE,	//�X�e�[�W��������
		GAME01_PHASE_3,				//�J�E���g�_�E��3
		GAME01_PHASE_2,				//�J�E���g�_�E��2
		GAME01_PHASE_1,				//�J�E���g�_�E��1
		GAME01_PHASE_GO,			//�J�E���g�_�E���X�^�[�g
		GAME01_PHASE_CLEAR,			//�Q�[���N���A
		GAME01_PHASE_OVER,			//�Q�[���I�[�o�[
		GAME01_PHASE_MAX
	} GAME01_PHASE;

	//�X�̏��̃p�^�[��
	typedef enum
	{
		ICE_FLOOR_PATTERN_NONE = 0,
		ICE_FLOOR_PATTERN_1,
		ICE_FLOOR_PATTERN_2,
		ICE_FLOOR_PATTERN_3,
		ICE_FLOOR_PATTERN_MAX
	} ICE_FLOOR_PATTERN;

	CGame01(int nPriority = PRIORITY_NONE);		//�R���X�g���N�^
	~CGame01();									//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	GAME01_PHASE GetPhase(void);			//�t�F�[�Y�擾����
	void SetPhase(GAME01_PHASE phase);		//�t�F�[�Y�ݒ菈��
	bool GetGame(void);						//�Q�[�������ǂ����擾����


private:
	//�����o�֐�
	void Phase(void);									//�t�F�[�Y����
	void Respawn(void);									//���X�|�[������

	CMeshField *m_pMeshField;							//���b�V���t�B�[���h�̃|�C���^
	CMeshSphere *m_pMeshSphere;							//���b�V���X�t�B�A�̃|�C���^
	CPlayer *m_apPlayer[MAX_PLAYER];					//�v���C���[�̃|�C���^
	CModelSingle *m_apModelSingle[GAME_MAX_MODEL];	    //���f���̃|�C���^
	CScore *m_pScore;									//�X�R�A�̃|�C���^
	CTimer *m_pTime;									//�^�C���̃|�C���^
	CUi *m_apUi[GAME_MAX_UI_NUM];						//UI�̃|�C���^
	CPause *m_pPause;									//�|�[�Y�̃|�C���^
	CScene3D *m_pScene3D;								//Scene3D�̃|�C���^
	int m_nNumScene2D;									//�o�Ă�|���S���̑���
	int m_nSelect;										//���I��ł���|���S��
	GAME01_PHASE m_phase;								//�t�F�[�Y
	int m_nFrame;										//�t���[����
	int m_nTime;										//�^�C���p�t���[�����J�E���g�ϐ�
	bool m_bGame;										//�Q�[�������ǂ����̃t���O
	ICE_FLOOR_PATTERN m_icePattern;
};

#endif // !_GAME01_H_