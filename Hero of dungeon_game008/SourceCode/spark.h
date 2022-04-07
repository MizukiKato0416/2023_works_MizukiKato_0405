//===========================================
//�΂̕��̏���
//Author:KatoMizuki
//===========================================
#ifndef _SPARK_H_
#define _SPARK_H_

#include "object.h"

//�O���錾
class CEffect3D;

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CSpark : public CObject
{
public:
	CSpark(int nPriority = PRIORITY_SPARK);		//�R���X�g���N�^
	~CSpark();									//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//�ʒu�A�T�C�Y�A�G�t�F�N�g�̐��A�F�A���������_���ŏ��l�A���������_���ő�l�A�d�́A���l���Z�ʃ����_���ŏ��l�A���l���Z�ʃ����_���ő�l�A�ړ��ʌ��Z�l
	static CSpark *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumEffect, D3DXCOLOR col, float fMoveMin, float fMoveMax,
		                  float fGravity, float fColAMin, float fColAMax, float fSubtractionMove);

private:
	std::vector<CEffect3D*> m_pEffect3D;		//�G�t�F�N�g�̃|�C���^
	D3DXVECTOR3 m_size;							//�G�t�F�N�g�̃T�C�Y
	std::vector<float> m_fInitMove;				//����
	std::vector<float> m_fRotX;					//�ړ��������
	std::vector<float> m_fRotY;					//�ړ��������
	D3DXCOLOR m_col;							//�G�t�F�N�g�̐F
	int m_nNumEffect;							//�G�t�F�N�g�̐�
	float m_fGravity;							//�d��
	int m_nColAMin;					    		//���l���Z�ʃ����_���ŏ��l
	int m_nColAMax;					    		//���l���Z�ʃ����_���ő�l
	float m_fSubtractionMove;					//�ړ��ʌ��Z�l
};

#endif // !_SPARK_H_