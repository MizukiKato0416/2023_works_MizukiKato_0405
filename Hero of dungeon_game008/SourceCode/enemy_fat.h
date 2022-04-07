//===========================================
//���^�G�̏���
//Author:KatoMizuki
//===========================================
#ifndef _ENEMY_FAT_H_
#define _ENEMY_FAT_H_
#include "enemy.h"

//�O���錾
class CModel;
class CMotionEnemyFat;

//================================================
//�}�N����`
//================================================
#define MAX_ENEMY_FAT_MODEL						(5)			//���f���̐�
#define ENEMY_FAT_MAX_ATTACK_COLLISION			(2)			//�U�����̓����蔻��̐�
#define ENEMY_FAT_ATTACK_DAMAGE					(50)		//�U�����̃_���[�W

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CEnemyFat : public CEnemy
{
public:
	//�����o�֐�
	CEnemyFat(int nPriority = PRIORITY_ENEMY);				//�R���X�g���N�^
	~CEnemyFat();											//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemyFat *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	void SetModelPos(int nCntModel, D3DXVECTOR3 pos);					//���f���̈ʒu�ݒ菈��
	D3DXVECTOR3 GetModelPos(int nCntModel);								//���f���̈ʒu�擾����
	void SetModelRot(int nCntModel, D3DXVECTOR3 rot);					//���f���̌����ݒ菈��
	D3DXVECTOR3 GetModelRot(int nCntModel);								//���f���̌����擾����

private:
	//�����o�֐�
	void MoveType(void);							//�����Ɋւ��鏈��
	void ToPlayerAttackCollision(void);				//�v���C���[�ւ̍U���̓����蔻��				
	bool CollisionSlash(void);						//�a���̓����蔻��
	bool CollisionMagicThunder(void);				//�����@�̓����蔻��

	//�����o�ϐ�
	CModel *m_apModel[MAX_ENEMY_FAT_MODEL];							//���f���̃|�C���^
	CModel *m_pParent;												//�e���f���ւ̃|�C���^
	CMotionEnemyFat *m_pMotionEnemyFat;								//���[�V�����̃|�C���^
	D3DXMATRIX m_aAttackCollMtx[ENEMY_FAT_MAX_ATTACK_COLLISION];	//�U������ۂ̓����蔻����s���ꏊ
	bool m_bAttackColl;												//�U���̓����蔻�肪���邩�ǂ���
};

#endif // !_ENEMY_FAT_H_