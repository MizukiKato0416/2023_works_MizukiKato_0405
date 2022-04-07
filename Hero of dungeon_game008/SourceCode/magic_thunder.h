//===========================================
//�����@����
//Author:KatoMizuki
//===========================================
#ifndef _MAGIC_THUNDER_H_
#define _MAGIC_THUNDER_H_

#include "object.h"

//�O���錾
class CMagicCircle;

//================================================
//�}�N����`
//================================================
#define MAGIC_THUNDER_EFFECT_ENEMY_FAT_DAMAGE	(3)									//���^�G�ւ̃_���[�W
#define MAGIC_THUNDER_EFFECT_ENEMY_BOSS_DAMAGE	(3)									//���^�G�ւ̃_���[�W
#define MAGIC_THUNDER_EFFECT_ENEMY_BEE_DAMAGE	(4)									//�I�^�G�ւ̃_���[�W

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CMagicThunder : public CObject
{
public:
	CMagicThunder(int nPriority = PRIORITY_MAGIC);			//�R���X�g���N�^
	~CMagicThunder();										//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMagicThunder *Create(D3DXVECTOR3 pos);
	//�����蔻��
	static bool Collision(CObject *pSubjectObject);

private:
	//�����o�֐�
	 void MagicCircle(void);				//���@�w�Ɋւ��鏈��

	CMagicCircle *m_pMagicCircle;		//���@�w�̃|�C���^
	int m_nCounter;						//���@�w�̃J�E���^�[
	D3DXVECTOR3 m_pos;					//�ʒu
	D3DXVECTOR3 m_size;					//�T�C�Y
};

#endif // !_MAGIC_THUNDER_H_