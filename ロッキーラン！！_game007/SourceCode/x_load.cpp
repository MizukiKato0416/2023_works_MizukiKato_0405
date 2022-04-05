//=============================================================================
//X�t�@�C���ǂݍ��ݏ���
//Authore:��������
//=============================================================================
#include "x_load.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CXload::CXload()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CXload::~CXload()
{

}

//=============================================================================
//�e�N�X�`���̐���
//=============================================================================
void CXload::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X���擾����

	//X�t�@�C���ǂݍ���

	//�v���C���[�̑�
	D3DXLoadMeshFromX("data/MODEL/body.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_BODY], NULL, &m_aNumMat[X_TYPE_PLAYER_BODY], &m_apMesh[X_TYPE_PLAYER_BODY]);

	//�v���C���[�̉E�r
	D3DXLoadMeshFromX("data/MODEL/armR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_ARM_R], NULL, &m_aNumMat[X_TYPE_PLAYER_ARM_R], &m_apMesh[X_TYPE_PLAYER_ARM_R]);

	//�v���C���[�̍��r
	D3DXLoadMeshFromX("data/MODEL/armL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_ARM_L], NULL, &m_aNumMat[X_TYPE_PLAYER_ARM_L], &m_apMesh[X_TYPE_PLAYER_ARM_L]);

	//�v���C���[�̉E��
	D3DXLoadMeshFromX("data/MODEL/legsR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_LEG_R], NULL, &m_aNumMat[X_TYPE_PLAYER_LEG_R], &m_apMesh[X_TYPE_PLAYER_LEG_R]);

	//�v���C���[�̍���
	D3DXLoadMeshFromX("data/MODEL/legsL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_LEG_L], NULL, &m_aNumMat[X_TYPE_PLAYER_LEG_L], &m_apMesh[X_TYPE_PLAYER_LEG_L]);

	//�v���C���[���̎q�̑�
	D3DXLoadMeshFromX("data/MODEL/girlBody.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_GIRL_BODY], NULL, &m_aNumMat[X_TYPE_PLAYER_GIRL_BODY], &m_apMesh[X_TYPE_PLAYER_GIRL_BODY]);

	//�v���C���[���̎q�̉E�r
	D3DXLoadMeshFromX("data/MODEL/girlArmR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_GIRL_ARM_R], NULL, &m_aNumMat[X_TYPE_PLAYER_GIRL_ARM_R], &m_apMesh[X_TYPE_PLAYER_GIRL_ARM_R]);

	//�v���C���[���̎q�̍��r
	D3DXLoadMeshFromX("data/MODEL/girlArmL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_GIRL_ARM_L], NULL, &m_aNumMat[X_TYPE_PLAYER_GIRL_ARM_L], &m_apMesh[X_TYPE_PLAYER_GIRL_ARM_L]);

	//�v���C���[���̎q�̉E��
	D3DXLoadMeshFromX("data/MODEL/girlLegsR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_GIRL_LEG_R], NULL, &m_aNumMat[X_TYPE_PLAYER_GIRL_LEG_R], &m_apMesh[X_TYPE_PLAYER_GIRL_LEG_R]);

	//�v���C���[���̎q�̍���
	D3DXLoadMeshFromX("data/MODEL/girlLegsL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_GIRL_LEG_L], NULL, &m_aNumMat[X_TYPE_PLAYER_GIRL_LEG_L], &m_apMesh[X_TYPE_PLAYER_GIRL_LEG_L]);

	//�`���[�g���A���̃X�^�[�g�̏�
	D3DXLoadMeshFromX("data/MODEL/TUTORIAL/start_floor.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_TUTORIAL_START_FLOOR], NULL, &m_aNumMat[X_TYPE_TUTORIAL_START_FLOOR], &m_apMesh[X_TYPE_TUTORIAL_START_FLOOR]);

	//�`���[�g���A���̃~�h���̏�
	D3DXLoadMeshFromX("data/MODEL/TUTORIAL/middle_floor.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_TUTORIAL_MIDDLE_FLOOR], NULL, &m_aNumMat[X_TYPE_TUTORIAL_MIDDLE_FLOOR], &m_apMesh[X_TYPE_TUTORIAL_MIDDLE_FLOOR]);

	//�`���[�g���A���̃S�[���̏�
	D3DXLoadMeshFromX("data/MODEL/TUTORIAL/goal_floor.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_TUTORIAL_GOAL_FLOOR], NULL, &m_aNumMat[X_TYPE_TUTORIAL_GOAL_FLOOR], &m_apMesh[X_TYPE_TUTORIAL_GOAL_FLOOR]);

	//�`���[�g���A���̃~�h���̍�
	D3DXLoadMeshFromX("data/MODEL/TUTORIAL/middle_fence.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_TUTORIAL_MIDDLE_FENCE], NULL, &m_aNumMat[X_TYPE_TUTORIAL_MIDDLE_FENCE], &m_apMesh[X_TYPE_TUTORIAL_MIDDLE_FENCE]);

	//�`���[�g���A���̃X�^�[�g�ƃS�[���̃T�C�h��
	D3DXLoadMeshFromX("data/MODEL/TUTORIAL/startgoal_sidefence.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_TUTORIAL_SIDEFENCE], NULL, &m_aNumMat[X_TYPE_TUTORIAL_SIDEFENCE], &m_apMesh[X_TYPE_TUTORIAL_SIDEFENCE]);

	//�`���[�g���A���̃X�^�[�g�ƃS�[���̌���
	D3DXLoadMeshFromX("data/MODEL/TUTORIAL/startgoal_backfence.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_TUTORIAL_BACKFENCE], NULL, &m_aNumMat[X_TYPE_TUTORIAL_BACKFENCE], &m_apMesh[X_TYPE_TUTORIAL_BACKFENCE]);

	//�`���[�g���A���̃S�[���̒�
	D3DXLoadMeshFromX("data/MODEL/TUTORIAL/goal_pole.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_TUTORIAL_GOAL_POLE], NULL, &m_aNumMat[X_TYPE_TUTORIAL_GOAL_POLE], &m_apMesh[X_TYPE_TUTORIAL_GOAL_POLE]);

	//�`���[�g���A���̃S�[���̊�
	D3DXLoadMeshFromX("data/MODEL/TUTORIAL/goal_flag.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_TUTORIAL_GOAL_FLAG], NULL, &m_aNumMat[X_TYPE_TUTORIAL_GOAL_FLAG], &m_apMesh[X_TYPE_TUTORIAL_GOAL_FLAG]);

	//�X�e�[�W�̑���
	D3DXLoadMeshFromX("data/MODEL/GAME/scaffold.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_GAME_SCAFFOLD], NULL, &m_aNumMat[X_TYPE_GAME_SCAFFOLD], &m_apMesh[X_TYPE_GAME_SCAFFOLD]);

	//�X�e�[�W�̂̏㉺��
	D3DXLoadMeshFromX("data/MODEL/GAME/wall_updown.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_GAME_WALL_UPDOWN], NULL, &m_aNumMat[X_TYPE_GAME_WALL_UPDOWN], &m_apMesh[X_TYPE_GAME_WALL_UPDOWN]);

	//�X�e�[�W�̏㉺�ǂ̒�
	D3DXLoadMeshFromX("data/MODEL/GAME/wall_pillar.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_GAME_WALL_PILLAR], NULL, &m_aNumMat[X_TYPE_GAME_WALL_PILLAR], &m_apMesh[X_TYPE_GAME_WALL_PILLAR]);

	//�X�e�[�W�̏����鏰
	D3DXLoadMeshFromX("data/MODEL/GAME/floor_disappear.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_GAME_FLOOR_DISAPPEAR], NULL, &m_aNumMat[X_TYPE_GAME_FLOOR_DISAPPEAR], &m_apMesh[X_TYPE_GAME_FLOOR_DISAPPEAR]);

	//�X�e�[�W�̊��鏰�i�X�j
	D3DXLoadMeshFromX("data/MODEL/GAME/floor_ice.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_GAME_FLOOR_ICE], NULL, &m_aNumMat[X_TYPE_GAME_FLOOR_ICE], &m_apMesh[X_TYPE_GAME_FLOOR_ICE]);

	//�X�e�[�W�̃o�l
	D3DXLoadMeshFromX("data/MODEL/GAME/spring.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_GAME_SPRING], NULL, &m_aNumMat[X_TYPE_GAME_SPRING], &m_apMesh[X_TYPE_GAME_SPRING]);

	//���U���g�̉���
	D3DXLoadMeshFromX("data/MODEL/GAME/crown.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_RESULT_CROWN], NULL, &m_aNumMat[X_TYPE_RESULT_CROWN], &m_apMesh[X_TYPE_RESULT_CROWN]);

	//�_
	D3DXLoadMeshFromX("data/MODEL/GAME/cloud.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_CLOUD], NULL, &m_aNumMat[X_TYPE_CLOUD], &m_apMesh[X_TYPE_CLOUD]);

	//�C��
	D3DXLoadMeshFromX("data/MODEL/GAME/balloon.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_BALLOON], NULL, &m_aNumMat[X_TYPE_BALLOON], &m_apMesh[X_TYPE_BALLOON]);

	//��s�D
	D3DXLoadMeshFromX("data/MODEL/GAME/airship.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_AIRSHIP], NULL, &m_aNumMat[X_TYPE_AIRSHIP], &m_apMesh[X_TYPE_AIRSHIP]);

	//���
	D3DXLoadMeshFromX("data/MODEL/GAME/arrow.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_ARROW], NULL, &m_aNumMat[X_TYPE_ARROW], &m_apMesh[X_TYPE_ARROW]);

	//�`�F�b�N�|�C���g
	D3DXLoadMeshFromX("data/MODEL/GAME/checkpoint.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_CHECKPOINT], NULL, &m_aNumMat[X_TYPE_CHECKPOINT], &m_apMesh[X_TYPE_CHECKPOINT]);
}	

//=============================================================================
//�I��
//=============================================================================
void CXload::Uninit(void)
{
	for (int nCntXload = 0; nCntXload < X_TYPE_MAX; nCntXload++)
	{
		//���b�V���̔j��
		if (m_apMesh[nCntXload] != NULL)
		{
			m_apMesh[nCntXload]->Release();
			m_apMesh[nCntXload] = NULL;
		}

		//�}�e���A���̔j��
		if (m_apBuffMat[nCntXload] != NULL)
		{
			m_apBuffMat[nCntXload]->Release();
			m_apBuffMat[nCntXload] = NULL;
		}
	}
}

//=============================================================================
//���b�V���̊��蓖��
//=============================================================================
LPD3DXMESH CXload::GetMesh(X_TYPE type)
{
	return m_apMesh[type];
}

//=============================================================================
//�}�e���A�����蓖��
//=============================================================================
LPD3DXBUFFER CXload::GetBuffMat(X_TYPE type)
{
	return m_apBuffMat[type];
}

//=============================================================================
//�}�e���A�������蓖��
//=============================================================================
DWORD CXload::GetNumMat(X_TYPE type)
{
	return m_aNumMat[type];
}
