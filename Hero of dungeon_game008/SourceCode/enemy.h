//===========================================
//�G�̏���
//Author:KatoMizuki
//===========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "object.h"

//�O���錾
class CBillboard;
class CShadow;

//================================================
//�}�N����`
//================================================
#define ENEMY_GRAVITY						(0.2f)								//�d�͂̑傫��
#define ENEMY_STOP_MAX_COUNT				(120)								//�~�܂��Ă��鎞��
#define ENEMY_ATTACK_STOP_MAX_COUNT			(150)								//�U�����J��o���܂ł̎���
#define ENEMY_DAMAGE_MAX_COUNT				(15)								//�m�b�N�o�b�N���Ă��鎞��
#define ENEMY_MOVE_MAX_COUNT				(rand() % 840 + 240)				//�i��ł��鎞��
#define ENEMY_TURN_RAND						(float (rand() % 629 + -314) / 100)	//��]����ۂ̕��������߂邽�߂̃����_���l
#define ENEMY_MOVE_TO_PLAYER_MAX_DIFFER		(500.0f)							//�v���C���[��ǂ�������͈�
#define ENEMY_ATTACK_DIFFER					(80.0f)								//�v���C���[���U������͈�
#define ENEMY_DRAW_DIFFER					(1500.0f)							//�`�悷��͈�
#define ENEMY_SPARK_SIZE					(2.0f)								//�΂̕��G�t�F�N�g�̃T�C�Y
#define ENEMY_SPARK_EFFECT_NUM				(50)								//�΂̕��G�t�F�N�g�̐�
#define ENEMY_SPARK_EFFECT_COLOR			(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))	//�΂̕��G�t�F�N�g�̐F
#define ENEMY_SPARK_MOVE_MIN				(2.0f)								//�΂̕��G�t�F�N�g�̏��������_���ŏ��l
#define ENEMY_SPARK_MOVE_MAX				(5.0f)								//�΂̕��G�t�F�N�g�̏��������_���ő�l
#define ENEMY_SPARK_GRAVITY					(0.3f)								//�΂̕��G�t�F�N�g�̏d��
#define ENEMY_SPARK_COL_A_MIN				(0.02f)								//�΂̕��G�t�F�N�g�̃��l���Z�����_���ŏ��l
#define ENEMY_SPARK_COL_A_MAX				(0.04f)								//�΂̕��G�t�F�N�g�̃��l���Z�����_���ő�l
#define ENEMY_SPARK_SUBTRACTION_MOVE		(0.94f)								//�΂̕��G�t�F�N�g�̈ړ��ʌ��Z����
#define ENEMY_EXCLAMATION_MARK_SIZE			(70.0f)								//�r�b�N���}�[�N�̑傫��
#define ENEMY_EXCLAMATION_MARK_ADD_SIZE		(20.0f)								//�r�b�N���}�[�N�̑傫�����Z��
#define ENEMY_EXCLAMATION_MARK_LIFE			(60)								//�r�b�N���}�[�N�̎���
#define ENEMY_BOSS_UNINIT_SCORE				(10000000)							//�{�X��|�������ɓ�����X�R�A
#define ENEMY_FAT_UNINIT_SCORE				(150000)							//���^�G�|�������ɓ�����X�R�A
#define ENEMY_BEE_UNINIT_SCORE				(200000)							//�I�^�G�|�������ɓ�����X�R�A


//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CEnemy : public CObject
{
public:
	//�s���p�^�[��
	enum class ENEMY_MOVE_PATTERN
	{
		NONE = 0,
		MOVE,				//�ړ�
		STOP,				//��~
		TURN,				//��]
		MOVE_TO_PLAYER,		//�v���C���[�̂ق��Ɍ������Ĉړ�
		ATTACK,				//�U��
		DAMAGE,				//��_���[�W
		MAX
	};

	//�����o�֐�
	CEnemy(int nPriority = PRIORITY_ENEMY);				//�R���X�g���N�^
	~CEnemy();											//�f�X�g���N�^

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size) = 0;
	void Uninit(void);
	virtual void Update(void) = 0;
	void Draw(void);
	static int GetNum(void) { return m_nNum; }												//�����擾����
	static void Collision(CObject *pSubjectObject, float fObjRadius);						//�����蔻��
	bool CEnemy::CollisionOnly(CObject * pSubjectObject, float fObjRadius);					//�Փ˔���݂̂̏���
	ENEMY_MOVE_PATTERN GetMovePattern(void) { return m_movePattern; }						//�s���p�^�[���擾����
	void SetMovePattern(ENEMY_MOVE_PATTERN movePattern) { m_movePattern = movePattern; }	//�s���p�^�[���ݒ菈��
	int GetLife(void) { return m_nLife; }													//���C�t�擾����
	void AddLife(int nLife) { m_nLife += nLife; }											//���C�t��������
	bool GetDraw(void) { return m_bDraw; }													//�`�悳��Ă��邩�擾����

protected:
	//�����o�֐�
	void Rotate(void);							//��]����

	//�����o�ϐ�
	static int m_nNum;							//�G�̑���
	D3DXVECTOR3 m_pos;							//�ʒu
	D3DXVECTOR3 m_posOld;						//1�t���[���O�̈ʒu
	D3DXVECTOR3 m_move;							//�|���S���̈ړ���
	D3DXVECTOR3	m_size;							//�T�C�Y
	D3DXVECTOR3 m_rot;							//����
	D3DXMATRIX m_mtxWorld;						//���[���h�}�g���b�N�X
	float m_fObjectiveRot;						//�ړI�̌���
	float m_fNumRot;							//������ς����
	bool m_bRotate;								//��]���Ă��邩�ǂ���
	bool m_bDraw;								//�`�悵�Ă��邩�ǂ���
	bool m_bNotice;								//�v���C���[�ɋC�Â��Ă��邩�ǂ���
	ENEMY_MOVE_PATTERN m_movePattern;			//�����̎��
	int m_nStopCounter;							//��~���Ă��鎞��
	int m_nMoveCounter;							//�ړ����Ă��鎞��
	int m_nAttackCounter;						//�U�����o���܂ł̎���
	int m_nDamageCounter;						//�m�b�N�o�b�N���Ă��鎞��
	int m_nLife;								//�̗�
	CShadow *m_pShadow;							//�e�̃|�C���^
};

#endif // !_ENEMY_H_