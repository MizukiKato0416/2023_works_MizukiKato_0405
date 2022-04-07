//===========================================
//�{�X�̏���
//Author:KatoMizuki
//===========================================
#ifndef _ENEMY_BOSS_H_
#define _ENEMY_BOSS_H_
#include "enemy.h"

//�O���錾
class CModel;
class CMotionEnemyBoss;

//================================================
//�}�N����`
//================================================
#define MAX_ENEMY_BOSS_MODEL						(5)			//���f���̐�
#define ENEMY_BOSS_MAX_ATTACK_COLLISION				(2)			//�U�����̓����蔻��̐�
#define ENEMY_BOSS_ATTACK_DAMAGE					(80)		//�U�����̃_���[�W

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CEnemyBoss : public CEnemy
{
public:
	//�U���̎��
	enum class ENEMY_BOSS_ATTACK_PATTERN
	{
		NONE = 0,
		NORMAL,			//�ʏ�
		RUSH,			//�ːi
		MAGIC,			//���@
		MAX
	};

	//�����o�֐�
	CEnemyBoss(int nPriority = PRIORITY_ENEMY);				//�R���X�g���N�^
	~CEnemyBoss();											//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemyBoss *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	void SetModelPos(int nCntModel, D3DXVECTOR3 pos);					//���f���̈ʒu�ݒ菈��
	D3DXVECTOR3 GetModelPos(int nCntModel);								//���f���̈ʒu�擾����
	void SetModelRot(int nCntModel, D3DXVECTOR3 rot);					//���f���̌����ݒ菈��
	D3DXVECTOR3 GetModelRot(int nCntModel);								//���f���̌����擾����
	bool GetDamage(void) { return m_bDamage; }							//�_���[�W���󂯂Ă��邩�ǂ����擾����
	void SetDamage(bool bDamage) { m_bDamage = bDamage; }				//�_���[�W���󂯂Ă��邩�ǂ����ݒ菈��

private:
	//�����o�֐�
	void MoveType(void);							//�����Ɋւ��鏈��
	void ToPlayerAttackCollision(void);				//�v���C���[�ւ̍U���̓����蔻��				
	bool CollisionSlash(void);						//�a���̓����蔻��
	bool CollisionMagicThunder(void);				//�����@�̓����蔻��
	void Damage(void);								//�_���[�W���󂯂Ă���Ƃ��̏���

	//�����o�ϐ�
	CModel *m_apModel[MAX_ENEMY_BOSS_MODEL];						//���f���̃|�C���^
	CModel *m_pParent;												//�e���f���ւ̃|�C���^
	CMotionEnemyBoss *m_pMotionEnemyBoss;							//���[�V�����̃|�C���^
	D3DXMATRIX m_aAttackCollMtx[ENEMY_BOSS_MAX_ATTACK_COLLISION];	//�U������ۂ̓����蔻����s���ꏊ
	bool m_bAttackColl;												//�U���̓����蔻�肪���邩�ǂ���
	ENEMY_BOSS_ATTACK_PATTERN m_attackPattern;						//�U���̎��
	int m_nCntAttack;												//�U��������
	bool m_bDamage;													//�_���[�W���󂯂Ă��邩�ǂ���
};

#endif // !_ENEMY_BOSS_H_