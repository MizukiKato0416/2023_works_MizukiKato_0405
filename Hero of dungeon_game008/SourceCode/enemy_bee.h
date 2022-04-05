//===========================================
//�G(�I)�̏���
//Author:KatoMizuki
//===========================================
#ifndef _ENEMY_BEE_H_
#define _ENEMY_BEE_H_
#include "enemy.h"

//�O���錾
class CModel;
class CMotionEnemyBee;

//================================================
//�}�N����`
//================================================
#define MAX_ENEMY_BEE_MODEL							(1)			//�I�^�G1�̂Ɏg�����f���̐�

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CEnemyBee : public CEnemy
{
public:
	//�����o�֐�
	CEnemyBee(int nPriority = PRIORITY_ENEMY);				//�R���X�g���N�^
	~CEnemyBee();											//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	static CEnemyBee *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			//��������
	void SetModelPos(D3DXVECTOR3 pos);									//���f���̈ʒu�ݒ菈��
	D3DXVECTOR3 GetModelPos(void);										//���f���̈ʒu�擾����
	void SetModelRot(D3DXVECTOR3 rot);									//���f���̌����ݒ菈��
	D3DXVECTOR3 GetModelRot(void);										//���f���̌����擾����
private:
	void Move(void);							//�ړ�����
	void MoveType(void);						//�����Ɋւ��鏈��
	bool CollisionSlash(void);					//�a���̓����蔻��
	bool CollisionMagicThunder(void);			//�����@�̓����蔻��

	CModel *m_pModel;						//ModelSingle�̃|�C���^
	int m_nFlyMoveCounter;					//��s���̏㉺�ړ��̃J�E���^�[
	CMotionEnemyBee *m_pMotionEnemyBee;		//���[�V�����̃|�C���^

};

#endif // !_ENEMY_BEE_H_