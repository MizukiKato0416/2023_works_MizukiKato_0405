//===========================================
//�^�C�g������
//Authore:��������
//===========================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include "scene.h"
#include "scene2D.h"
#include "main.h"

//�O���錾

//================================================
//�}�N����`
//================================================
#define TITLE_TO_RESULT_COUNT	(600)			//���U���g�ɍs���܂ł̊Ԋu

//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CTitle : public CScene
{
public:
	CTitle();				//�R���X�g���N�^
	~CTitle();				//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	
private:
	CScene2D *m_pScene2D;
	int m_nResultCounter;		//���U���g�ɍs���܂ł̃J�E���^�[
	
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_TITLE_H_