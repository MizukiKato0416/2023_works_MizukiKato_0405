//===========================================
//�t�F�[�h����
//Author:KatoMizuki
//===========================================
#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"
#include "manager.h"
#include "object.h"
#include "object2D.h"

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CFade : public CObject2D
{
public:
	//�t�F�[�h�̎��
	typedef enum
	{
		FADE_NONE = 0,		//�������Ă��Ȃ�
		FADE_IN,			//�t�F�[�h�C��
		FADE_OUT,			//�t�F�[�h�A�E�g
		FADE_MAX
	} FADE;

	CFade(int nPriority = PRIORITY_FADE);		//�R���X�g���N�^
	~CFade();									//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	FADE GetFade(void);
	void SetFade(CManager::MODE modeNext);
	static CFade *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CManager::MODE modeNext);

private:
	FADE m_fade;							//�t�F�[�h�̏��
	CManager::MODE m_modeNext;				//���̉��(���[�h)
	D3DXCOLOR m_color;						//�t�F�[�h�̐F

};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_FADE_H_