//===========================================
//�`���[�g���A������
//Authore: UENOYAMA TAIGA
//===========================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
#include "scene.h"
#include "scene2D.h"
#include "main.h"
#include "player.h"

//�O���錾
class CMeshField;
class CMeshSphere;
class CModelSingle;
class CUi;
class CPause;
class CScene3D;

//================================================
//�}�N����`
//================================================
#define TUTORIAL_PLAYER_SPAWN_POS_Y			(60.0f)										//�v���C���[�����ʒuY���W
#define TUTORIAL_PLAYER_SPAWN_POS_Z			(-330.0f)									//�v���C���[�����ʒuZ���W
#define TUTORIAL_PLAYER_SPAWN_POS_X			(200.0f)									//�v���C���[�����ʒuX���W
#define TUTORIAL_PLAYER_SPAWN_WIDTH			(400.0f)									//�v���C���[�̃X�|�[���Ԋu
#define TUTORIAL_START_FLOOR_POS_Z			(-330.0f)									//�X�^�[�g����Z���W
#define TUTORIAL_MIDDLE_FLOOR_FRONT_POS_Z	(25.0f)										//�~�h�����i��O�j��Z���W
#define TUTORIAL_MIDDLE_FLOOR_BACK_POS_Z	(625.0f)									//�~�h�����i���j��Z���W
#define TUTORIAL_GOAL_FLOOR_POS_Z			(985.0f)									//�S�[������Z���W
#define TUTORIAL_GOAL_POLE_POS_X			(280.0f)									//�S�[������X���W
#define TUTORIAL_GOAL_POLE_POS_Y			(0.0f)										//�S�[������Y���W
#define TUTORIAL_GOAL_POLE_POS_Z			(TUTORIAL_GOAL_FLOOR_POS_Z -99.0f)			//�S�[������Z���W
#define TUTORIAL_GOAL_FLAG_POS_X			(0.0f)										//�S�[������X���W
#define TUTORIAL_GOAL_FLAG_POS_Y			(TUTORIAL_GOAL_POLE_POS_Y + 200.0f)			//�S�[������X���W
#define TUTORIAL_GOAL_FLAG_POS_Z			(TUTORIAL_GOAL_FLOOR_POS_Z - 99.0f)			//�S�[������X���W
#define TUTORIAL_FENCE_POS_X				(310.0f)									//�t�F���X��X���W
#define TUTORIAL_FENCE_POS_Y				(10.0f)										//�t�F���X��Y���W
#define TUTORIAL_MAX_MODEL					(40)										//�X�e�[�W�ɔz�u���郂�f���̍ő吔
#define TUTORIAL_EXPLANATION_POS_X			(270.0f)									//���������posX
#define TUTORIAL_EXPLANATION_POS_Y			(120.0f)									//���������posY
#define TUTORIAL_EXPLANATION_SIZE_X			(548.0f * 0.8f)								//���������sizeX
#define TUTORIAL_EXPLANATION_SIZE_Y			(305.0f * 0.8f)								//���������sizeY
#define TUTORIAL_PLAYERNUMBER_TEX_POS_Y		(60.0f)										//�v���C���[�i���o�[��posY
#define TUTORIAL_PLAYERNUMBER_TEX_SIZE_X	(360.0f)									//�v���C���[�i���o�[��sizeX
#define TUTORIAL_PLAYERNUMBER_TEX_SIZE_Y	(300.0f)									//�v���C���[�i���o�[��sizeY
#define TUTORIAL_1P_TEX_POS_X				(80.0f)										//1P�e�N�X�`����posX
#define TUTORIAL_2P_TEX_POS_X				(1190.0f)									//2P�e�N�X�`����posX
#define TUTORIAL_CLEAR_POS_X				(800.0f)									//�N���A��posX
#define TUTORIAL_CLEAR_POS_Y				(400.0f)									//�N���A��posY
#define TUTORIAL_MAX_UI_NUM					(4)											//UI�̍ő吔
#define TUTORIAL_NEXT_SCENE_COUNT			(120)										//���̃V�[���ɐi�ނ܂ł̃J�E���g
#define TUTORIAL_WORLD_SIZE					(20000.0f)									//�`���[�g���A���̐��E�̑傫��
//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CTutorial : public CScene
{
public:
	//�t�F�[�Y
	typedef enum
	{
		TUTORIAL_PHASE_NONE = 0,
	} TUTORIAL_PHASE;

	CTutorial();				//�R���X�g���N�^
	~CTutorial();				//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	void SetGoal(bool bGoal);
	bool GetGoal();
private:
	//�����o�֐�
	CUi *m_apUi[TUTORIAL_MAX_UI_NUM];					//UI�̃|�C���^
	CMeshField *m_pMeshField;							//���b�V���t�B�[���h�̃|�C���^
	CMeshSphere *m_pMeshSphere;							//���b�V���X�t�B�A�̃|�C���^
	CPlayer *m_apPlayer[MAX_PLAYER];								//�v���C���[�̃|�C���^
	CModelSingle *m_apModelSingle[TUTORIAL_MAX_MODEL];	//���f���̃|�C���^
	CPause *m_pPause;									//�|�[�Y�̃|�C���^
	CScene3D *m_pScene3D;								//Scene3D�̃|�C���^

	int m_nNumScene2D;									//�o�Ă�|���S���̑���
	int m_nSelect;										//���I��ł���|���S��
	bool m_bGoal;										//�S�[���������ǂ���
	int m_nFrame;										//�t���[����

};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_TUTORIAL_H_