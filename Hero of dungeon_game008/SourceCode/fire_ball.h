//===========================================
//���̒e����
//Author:KatoMizuki
//===========================================
#ifndef _FIRE_BALL_H_
#define _FIRE_BALL_H_

#include "object.h"

//�O���錾
class CEffect3D;
class CEnemy;

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CFireBall : public CObject
{
public:
	CFireBall(int nPriority = PRIORITY_FIRE_BALL);		//�R���X�g���N�^
	~CFireBall();										//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CFireBall *Create(D3DXVECTOR3 pos, int nRotPartitionNum, int nLayer,int nLife, float fPower, D3DXVECTOR3 move, D3DXVECTOR3 size);

private:
	int m_nRotPartitionNum;					//�p�x������
	int m_nLayer;							//�w�̐�
	int m_nLife;							//����
	float m_fPower;							//y=a(x*x)��a�̕���
	D3DXVECTOR3 m_move;						//�ړ���
	D3DXVECTOR3 m_size;						//�T�C�Y
	D3DXVECTOR3 m_pos;						//�ʒu
	std::vector<CEffect3D*> m_pEffect3D;	//�G�t�F�N�g�̃|�C���^
	bool m_bHoming;							//�ǔ����邩�ǂ���
	CEnemy *m_pTargetEnemy;					//�ǔ�����G�̃|�C���^
};

#endif // !_FIRE_BALL_H_