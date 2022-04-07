//===========================================
//�Q�[�W����
//Author:KatoMizuki
//===========================================
#ifndef _GAUGE_H_
#define _GAUGE_H_
#include "object2D.h"

//�O���錾

//================================================
//�}�N����`
//================================================
#define GAUGE_HP_POS_X	(63.0f)									//HP�Q�[�W�̈ʒuX
#define GAUGE_HP_POS_Y	(668.0f + GAUGE_HP_SIZE_Y / 2.0f)		//HP�Q�[�W�̈ʒuY
#define GAUGE_HP_SIZE_X	(610.99f)								//HP�Q�[�W�̃T�C�YX
#define GAUGE_HP_SIZE_Y	(15.01f)								//HP�Q�[�W�̃T�C�YY
#define GAUGE_MP_POS_X	(63.0f)									//MP�Q�[�W�̈ʒuX
#define GAUGE_MP_POS_Y	(696.0f + GAUGE_MP_SIZE_Y / 2.0f)		//MP�Q�[�W�̈ʒuY
#define GAUGE_MP_SIZE_X	(610.99f)								//MP�Q�[�W�̃T�C�YX
#define GAUGE_MP_SIZE_Y	(8.99f)									//MP�Q�[�W�̃T�C�YY
#define GAUGE_SP_POS_X	(124.84f)								//SP�Q�[�W�̈ʒuX
#define GAUGE_SP_POS_Y	(644.0f + GAUGE_SP_SIZE_Y / 2.0f)		//SP�Q�[�W�̈ʒuY
#define GAUGE_SP_SIZE_X	(317.36f)								//SP�Q�[�W�̃T�C�YX
#define GAUGE_SP_SIZE_Y	(15.01f)								//SP�Q�[�W�̃T�C�YY

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CGauge : public CObject2D
{
public:
	CGauge(int nPriority = PRIORITY_UI);		//�R���X�g���N�^
	~CGauge();									//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGauge *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nMaxNum, int nNum);

	void AddGauge(int nNum);					//�Q�[�W��������
	void SetGauge(int nNum);					//�Q�[�W�ݒ菈��
	int GetGauge(void) { return m_nNum; }		//�Q�[�W�擾����
	void SetMaxNum(int nMaxNum);				//�Q�[�W�ő吔�l�ݒ菈��
	int GetMaxNum(void) { return m_nMaxNum; }	//�Q�[�W�ő吔�l�擾����

private:
	int m_nMaxNum;					//�Q�[�W�̍ő吔�l
	int m_nNum;						//�Q�[�W�̌��ݐ��l
	D3DXVECTOR3 m_sizeMax;			//�T�C�Y�̍ő�l
};

#endif // !_GAUGE_H_