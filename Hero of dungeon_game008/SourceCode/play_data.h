//===========================================
//�v���C�f�[�^�Ǘ�����
//Author:KatoMizuki
//===========================================
#ifndef _PLAY_DATA_H_
#define _PLAY_DATA_H_
#include "main.h"

//�O���錾
class CGauge;
class CScore;

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CPlayData
{
public:
	CPlayData();			//�R���X�g���N�^
	~CPlayData();			//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);

	void SetHitPoint(int nHitPoint) { m_nHitPoint = nHitPoint; }					//HP�ݒ菈��
	int GetHitPoint(void) { return m_nHitPoint; }									//HP�擾����
	void SetHpGauge(CGauge *pHpGauge) { m_pHpGauge = pHpGauge; }					//HP�Q�[�W�̃|�C���^�ݒ菈��
	CGauge *GetHpGauge(void) { return m_pHpGauge; }									//HP�Q�[�W�̃|�C���^�擾����
	void SetMagicPoint(int nMagicPoint) { m_nMagicPoint = nMagicPoint; }			//MP�ݒ菈��
	int GetMagicPoint(void) { return m_nMagicPoint; }								//MP�擾����
	void SetMpGauge(CGauge *pMpGauge) { m_pMpGauge = pMpGauge; }					//MP�Q�[�W�̃|�C���^�ݒ菈��
	CGauge *GetMpGauge(void) { return m_pMpGauge; }									//MP�Q�[�W�̃|�C���^�擾����
	void SetSpecialPoint(int nSpecialPoint) { m_nSpecialPoint = nSpecialPoint; }	//SP�ݒ菈��
	int GetSpecialPoint(void) { return m_nSpecialPoint; }							//SP�擾����
	void SetSpGauge(CGauge *pSpGauge) { m_pSpGauge = pSpGauge; }					//SP�Q�[�W�̃|�C���^�ݒ菈��
	CGauge *GetSpGauge(void) { return m_pSpGauge; }									//SP�Q�[�W�̃|�C���^�擾����
	void SetScore(int nScore) { m_nScore = nScore; }								//�X�R�A�̐ݒ�
	int GetScore(void) { return m_nScore; }											//�X�R�A�̎擾
	void SetScorePoint(CScore *pScore) { m_pScore = pScore; }						//�X�R�A�̃|�C���^�ݒ菈��
	CScore *GetScorePoint(void) { return m_pScore; }								//�X�R�A�̃|�C���^�擾����
	void SetTime(int nTime) { m_nTime = nTime; }									//���Ԃ̐ݒ�
	int GetTime(void) { return m_nTime; }											//���Ԃ̎擾
	void SetGameOver(bool bGameOver) { m_bGameOver = bGameOver; }					//�Q�[���I�[�o�[�ݒ菈��
	bool GetGameOver(void) { return m_bGameOver; }									//�Q�[���I�[�o�[�擾����
	void SetGameClear(bool bGameClear) { m_bGameClear = bGameClear; }				//�Q�[���N���A�ݒ菈��
	bool GetGameClear(void) { return m_bGameClear; }								//�Q�[���N���A�擾����

private:
	//�����o�ϐ�
	int m_nHitPoint;				//�v���C���[��HP
	int m_nMagicPoint;				//�v���C���[��MP
	int m_nSpecialPoint;			//�v���C���[��SP
	CGauge *m_pHpGauge;				//HP�Q�[�W�̃|�C���^
	CGauge *m_pMpGauge;				//MP�Q�[�W�̃|�C���^
	CGauge *m_pSpGauge;				//SP�Q�[�W�̃|�C���^
	int m_nScore;					//�X�R�A
	CScore *m_pScore;				//�X�R�A�̃|�C���^
	int m_nTime;					//����
	bool m_bGameOver;				//�Q�[���I�[�o�[���ǂ���
	bool m_bGameClear;				//�Q�[���N���A���ǂ���
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_PLAY_DATA_H_