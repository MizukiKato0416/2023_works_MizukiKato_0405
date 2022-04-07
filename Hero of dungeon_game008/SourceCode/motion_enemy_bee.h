//===========================================
//�I�^�G�̃��[�V��������
//Author:KatoMizuki
//===========================================
#ifndef _MOTION_ENEMY_BEE_H_
#define _MOTION_ENEMY_BEE_H_
#include "main.h"
#include "enemy_bee.h"
#include "motion_road.h"
#include "manager.h"

//================================================
//�}�N����`
//================================================

//================================================
//�\���̂̒�`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CMotionEnemyBee
{
public:

	CMotionEnemyBee();			//�R���X�g���N�^
	~CMotionEnemyBee();			//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(CEnemyBee *pEnemyBee);
	void Uninit(void);
	void Update(CEnemyBee *pEnemyBee);

	static CMotionEnemyBee *Create(CEnemyBee *pEnemyBee);									//��������
	void SetMotion(CMotionRoad::MOTION_ENEMY_BEE_TYPE type, CEnemyBee *pEnemyBee);			//���[�V�����ݒ菈��
	void SetMotion(int nType, CEnemyBee *pEnemyBee);									//���[�V�����ݒ菈��
	CMotionRoad::MOTION_ENEMY_BEE_TYPE GetMotion(void);								//���[�V�����擾����
	bool GetConnect(void);															//���[�V�������Ȃ��Ă���Œ����ǂ����擾����
	int GetKey(void) { return m_nKey; }												//�L�[�擾����
	int GetFrame(void) { return (int)m_fCounter; }									//���[�V�����J�E���^�[�擾����
	void SetFrameMax(int nFrame) { m_fConnectMaxFrame = (float)nFrame; }			//���[�V�����J�E���^�[�ő�l�ݒ菈��
	//�L�[�ő吔�擾����
	int GetKeyMax(void) { return CManager::GetInstance()->GetMotionRoad()->GetMotionInfo(CMotionRoad::MOTION_HAVE_TYPE_ENEMY_BEE, m_type).nNumKey; }
	//���[�V�����J�E���^�[�ő吔�擾����
	int GetFrameMax(void) { return CManager::GetInstance()->GetMotionRoad()->GetMotionInfo(CMotionRoad::MOTION_HAVE_TYPE_ENEMY_BEE, m_type).aKeyInfo[m_nKey].nFrame; }
	

private:
	std::vector<MOTION_INFO> m_aInfo;					//���[�V�������
	CMotionRoad::MOTION_ENEMY_BEE_TYPE m_type;				//���݂̃��[�V�����^�C�v
	CMotionRoad::MOTION_ENEMY_BEE_TYPE m_typeNext;			//���̃��[�V�����^�C�v
	CMotionRoad::MOTION_ENEMY_BEE_TYPE m_typeOld;			//�O�̃��[�V�����^�C�v
	int m_nKey;											//�L�[No,(���݂̃L�[)
	float m_fCounter;									//���[�V�����̃J�E���^�[
	bool m_bConnect;									//���[�V�������Ȃ��Ă��邩�ǂ���
	float m_fConnectMaxFrame;							//���[�V�������Ȃ���Ƃ��̃t���[�����ő�l
	std::vector<D3DXVECTOR3> m_posOld;					//���[�V�������Ȃ���Ƃ��̑O�̃��f���̈ʒu
	std::vector<D3DXVECTOR3> m_rotOld;					//���[�V�������Ȃ���Ƃ��̑O�̃��f���̌���
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_MOTION_ENEMY_BEE_H_