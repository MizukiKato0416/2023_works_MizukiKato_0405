//===========================================
//���U���g����
//Authore:��������
//===========================================
#ifndef _RESULT_H_
#define _RESULT_H_
#include "scene.h"
#include "scene2D.h"
#include "main.h"

//�O���錾
class CTexture;
class CBg;
class CRanking;

//================================================
//�}�N����`
//================================================
#define RESULT_TO_TITLE_COUNT	(600)			//�^�C�g���ɍs���܂ł̊Ԋu

//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CResult : public CScene
{
public:
	CResult();				//�R���X�g���N�^
	~CResult();				//�f�X�g���N�^

							//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTexture *GetTexture(void);
	static CBg *GetBg(void);
	static CRanking *GetRanking(void);

private:
	CScene2D *m_pScene2D;

	static CTexture *m_pTexture;
	static CBg *m_pBg;
	static CRanking *m_pRanking;
	int m_nTitleCounter;			//�^�C�g���ɍs���܂ł̃J�E���^�[
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_RESULT_H_