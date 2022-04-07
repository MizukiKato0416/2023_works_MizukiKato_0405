//===========================================
//�v���C���[����
//Author:KatoMizuki
//===========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "object.h"

//�O���錾
class CModel;
class CMotionPlayer;
class CMeshTrajectory;
class CBillboard;
class CEnemy;

//================================================
//�}�N����`
//================================================
#define MAX_PLAYER_MODEL					(16)		//���f���̐�
#define PLAYER_MAX_HP						(1000)		//�ő�HP
#define PLAYER_MAX_MP						(1000)		//�ő�MP
#define PLAYER_MAX_SP						(100)		//�ő�SP
#define PLAYER_MAGIC_01_POS					(50.0f)		//���@1�̈ʒuXZ�����l
#define PLAYER_MAGIC_01_POS_Y				(40.0f)		//���@1�̈ʒuY�����l

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CPlayer : public CObject
{
public:
	//�v���C���[�̏��
	enum class PLAYER_STATE
	{
		NONE = 0,
		NORMAL,		//�ʏ�
		DAMAGE,		//�_���[�W
		INVINCIBLE,	//���G
		MAX
	};


	//�����o�֐�
	CPlayer(int nPriority = PRIORITY_PLAYER);				//�R���X�g���N�^
	~CPlayer();												//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	void SetModelPos(int nCntModel, D3DXVECTOR3 pos);								//���f���̈ʒu�ݒ菈��
	D3DXVECTOR3 GetModelPos(int nCntModel);											//���f���̈ʒu�擾����
	D3DXVECTOR3 GetRot(void) { return m_rot; }										//�v���C���[�̌����擾����
	void SetModelRot(int nCntModel, D3DXVECTOR3 rot);								//���f���̌����ݒ菈��
	D3DXVECTOR3 GetModelRot(int nCntModel);											//���f���̌����擾����
	void SetMove(D3DXVECTOR3 move) { m_move = move; }								//�ړ��ʐݒ菈��
	PLAYER_STATE GetState(void) { return m_state; }									//��Ԏ擾����
	void SetState(PLAYER_STATE state) { m_state = state; }							//��Ԑݒ菈��
	CEnemy *GetEnemyNear(void) { return m_pEnemyNear; }								//��ԋ߂��̓G�擾����
	void SetEnemyNear(CEnemy *pEnemy) { m_pEnemyNear = pEnemy; }					//��ԋ߂��̓G�ݒ菈��
	bool GetGuard(void) { return m_bGuard; }										//�K�[�h�擾����
	static void CPlayer::Collision(CObject *pSubjectObject, float fObjRadius);		//�����蔻�菈��
	bool CPlayer::CollisionOnly(CObject *pSubjectObject, float fObjRadius);			//�Փ˔���݂̂̏���

private:
	//�����o�֐�
	void Move(void);								//�ړ�����
	void Rotate(void);								//��]����
	void Jump(void);								//�W�����v����
	void Slash(void);								//���U������
	void Special(void);								//�K�E�Z����
	void Magic(void);								//���@�U������
	void Guard(void);								//�K�[�h����
	void State(void);								//��Ԃɂ�鏈������
	void LockOn(void);								//���b�N�I������

	//�����o�ϐ�
	D3DXVECTOR3 m_pos;								//�ʒu
	D3DXVECTOR3 m_posOld;							//1�t���[���O�̈ʒu
	D3DXVECTOR3 m_move;								//�|���S���̈ړ���
	D3DXVECTOR3	m_size;								//�T�C�Y
	D3DXVECTOR3 m_rot;								//����
	CModel *m_apModel[MAX_PLAYER_MODEL];			//���f���̃|�C���^
	D3DXMATRIX m_mtxWorld;							//���[���h�}�g���b�N�X
	CModel *m_pParent;								//�e���f���ւ̃|�C���^
	CMotionPlayer *m_pMotionPlayer;					//���[�V�����v���C���[�̃|�C���^
	CMeshTrajectory *m_pMeshTrajectory[2];			//���̋O��
	CBillboard *m_pLockOn;							//���b�N�I��UI
	CEnemy *m_pEnemyNear;							//�v���C���[�Ɉ�ԋ߂��G
	float m_fObjectiveRot;							//�ړI�̌���
	float m_fLockOnObjectiveRot;					//lock-on���̖ړI�̌���
	float m_fNumRot;								//������ς����
	bool m_bRotate;									//��]���Ă��邩�ǂ���
	bool m_bJump;									//�W�����v���Ă邩�ǂ���
	bool m_bBurst;									//�A�����Ă��邩�ǂ���
	bool m_bSpecial;								//�K�E�Z�����Ă��邩�ǂ���
	bool m_bLockOn;									//���b�N�I�������Ă��邩�ǂ���
	bool m_bGuard;									//�K�[�h�����Ă��邩�ǂ���
	int m_nCntBurst;								//�A����
	int m_nInvincibleCounter;						//���G��Ԃ̃J�E���^�[
	PLAYER_STATE m_state;							//���
	
};

#endif // !_PLAYER_H_