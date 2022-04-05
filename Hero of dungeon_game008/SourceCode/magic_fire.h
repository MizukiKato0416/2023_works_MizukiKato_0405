//===========================================
//�����@����
//Author:KatoMizuki
//===========================================
#ifndef _MAGIC_FIRE_H_
#define _MAGIC_FIRE_H_

#include "object.h"

//�O���錾
class CMagicCircle;
class CFireBall;

//================================================
//�}�N����`
//================================================
#define MAGIC_FIRE_BALL_MOVE				(15.0f)		//�ړ���

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CMagicFire : public CObject
{
public:
	CMagicFire(int nPriority = PRIORITY_MAGIC);			//�R���X�g���N�^
	~CMagicFire();										//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMagicFire *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:
	CMagicCircle *m_pMagicCircle;		//���@�w�̃|�C���^
	CFireBall *m_pFireBall;				//�΋��̃|�C���^
	int m_nCounter;						//���@�w�̃J�E���^�[
	D3DXVECTOR3 m_rot;					//����
};

#endif // !_MAGIC_FIRE_H_