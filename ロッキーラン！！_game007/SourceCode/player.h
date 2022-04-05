//===========================================
//�v���C���[����
//Author:��������
//===========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "scene.h"

//�O���錾
class CModel;
class CControl;
class CMotionPlayer;
class CShadow;

//================================================
//�}�N����`
//================================================
#define MAX_PLAYER_MODEL						(5)			//���f���̐�
#define PLAYER_UNINIT_POS_Y						(-300.0f)	//�v���C���[�������ꏊ
#define MAX_PLAYER								(2)			//�v���C���[�̐�

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CPlayer : public CScene
{
public:
	//�`�F�b�N�|�C���g
	typedef enum
	{
		PLAYER_CHECK_POINT_NONE = 0,
		PLAYER_CHECK_POINT_GAME01_MIDDLE1,		//�Q�[��01�̒��Ԓn�_1
		PLAYER_CHECK_POINT_GAME01_MIDDLE2,		//�Q�[��01�̒��Ԓn�_2
		PLAYER_CHECK_POINT_MAX
	} PLAYER_CHECK_POINT;

	CPlayer(int nPriority = PRIORITY_MODEL);				//�R���X�g���N�^
	~CPlayer();												//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3	rot, int nNum);

	D3DXVECTOR3 GetPosOld(void);						//1�t���[���O�̈ʒu
	void SetLand(bool bLand);							//���n�ݒ菈��
	bool GetLand(void);									//���n�擾����
	D3DXVECTOR3 GetRot(void);							//�����擾����
	void SetRot(D3DXVECTOR3 rot);						//�����ݒ菈��
	void SetMove(D3DXVECTOR3 move);						//�ړ��ʐݒ菈��
	D3DXVECTOR3 GetMove(void);							//�ړ��ʎ擾����
	void SetJump(bool bJump);							//�W�����v�ݒ菈��
	bool GetJump(void);									//�W�����v�擾����
	void SetDive(bool bDive);							//�_�C�u�ݒ菈��
	bool GetDive(void);									//�_�C�u�擾����
	void SetOnIce(bool bOnIce);							//�X�̏����ǂ����ݒ菈��
	bool GetOnIce(void);								//�X�̏����ǂ����擾����
	void SetOnSpring(bool bOnSpring);					//�o�l���ǂ����ݒ菈��
	bool GetOnSpring(void);								//�o�l���ǂ����擾����
	void SetModelPos(int nCntModel, D3DXVECTOR3 pos);	//���f���̈ʒu�ݒ菈��
	D3DXVECTOR3 GetModelPos(int nCntModel);				//���f���̈ʒu�擾����
	void SetModelRot(int nCntModel, D3DXVECTOR3 rot);	//���f���̌����ݒ菈��
	D3DXVECTOR3 GetModelRot(int nCntModel);				//���f���̌����擾����
	CMotionPlayer *GetMotionPlayer(void);				//���[�V�����v���C���[�擾����
	void Collision(CScene *pSCene);						//�I�u�W�F�N�g�Ƃ̓����蔻��
	int GetNum(void);									//�v���C���[�̌̎��ʔԍ��擾����
	void SetNum(int nNum);								//�v���C���[�̌̎��ʔԍ��ݒ菈��
	void SetCheckPoint(PLAYER_CHECK_POINT checkPoint);	//�`�F�b�N�|�C���g�ݒ菈��
	PLAYER_CHECK_POINT GetCheckPoint(void);				//�`�F�b�N�|�C���g�擾����
	void ShadowCollision(void);							//�e�̕\���̂��߂̃I�u�W�F�N�g�Ƃ̓����蔻��

private:
	//�����o�֐�
	bool Collision(void);							//�����蔻��
	static void CollisionPlayer(CPlayer *pPlayer);	//�v���C���[�Ƃ̓����蔻��
	void Move(void);								//�ړ�

	D3DXVECTOR3 m_pos;								//�ʒu
	D3DXVECTOR3 m_posOld;							//1�t���[���O�̈ʒu
	D3DXVECTOR3 m_move;								//�|���S���̈ړ���
	D3DXVECTOR3	m_size;								//�T�C�Y
	D3DXVECTOR3 m_rot;								//����
	CModel *m_apModel[MAX_PLAYER_MODEL];			//���f���̃|�C���^
	D3DXMATRIX m_mtxWorld;							//���[���h�}�g���b�N�X
	CModel *m_pParent;								//�e���f���ւ̃|�C���^
	CControl *m_pControl;							//�R���g���[���N���X�̃|�C���^
	CShadow *m_pShadow;								//�V���h�E�N���X�̃|�C���^
	bool m_bLand;									//���n���Ă��邩�ǂ���
	bool m_bJump;									//�W�����v���Ă��邩�ǂ���
	bool m_bJumpOld;								//�O�t���[���W�����v���Ă��邩�ǂ���
	bool m_bDive;									//�_�C�u���Ă��邩�ǂ���
	bool m_bOnIce;									//�X�̏ォ�ǂ���
	bool m_bOnSpring;								//�o�l���ǂ���
	CMotionPlayer *m_pMotionPlayer;					//���[�V�����v���C���[�̃|�C���^
	bool m_bLandMoment;								//���n�����u�Ԃ��ǂ���
	int m_nNum;										//�v���C���[�̌̎��ʔԍ�
	PLAYER_CHECK_POINT m_checkPoint;				//�`�F�b�N�|�C���g
};

#endif // !_PLAYER_H_