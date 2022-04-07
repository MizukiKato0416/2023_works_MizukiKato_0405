//===========================================
//�Q�[��03����
//Author:KatoMizuki
//===========================================
#ifndef _GAME03_H_
#define _GAME03_H_
#include "object.h"
#include "main.h"
#include "player.h"

//�O���錾
class CGauge;
class CObject2D;

//================================================
//�}�N����`
//================================================

//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CGame03 : public CObject
{
public:
	CGame03(int nPriority = PRIORITY_NONE);		//�R���X�g���N�^
	~CGame03();									//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	//�����o�֐�
	void GameOver(void);		//�Q�[���I�[�o�[����

	//�����o�ϐ�
	CGauge *m_pHpGauge;			//HP�Q�[�W�̃|�C���^
	CGauge *m_pMpGauge;			//MP�Q�[�W�̃|�C���^
	CGauge *m_pSpGauge;			//SP�Q�[�W�̃|�C���^
	int m_nRecoveryCounter;		//�񕜂���J�E���^�[
	int m_nGameCounter;			//�Q�[�����̃J�E���^�[
	CObject2D *m_pObjet2DGame;	//�Q�[���I�[�o�[����UI
};

#endif // !_GAME03_H_