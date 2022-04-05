//===========================================
//�X�R�A����
//Author:��������
//===========================================
#ifndef _SCORE_H_
#define _SCORE_H_
#include "scene.h"
#include "number.h"

//================================================
//�}�N����`
//================================================
#define MAX_SCORE_POLYGON		(6)				//�|���S���̍ő吔
#define SCORE_POLYGON_WIDTH		(40.0f)			//�|���S���̕�
#define SCORE_POLYGON_HEIGHT	(70.0f)			//�|���S���̍���
#define MAX_SCORE				(999999)		//�ő�X�R�A

//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CScore : public CScene
{
public:
	CScore(int nPriority = PRIORITY_UI);	//�R���X�g���N�^
	~CScore();								//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetScore(int nScore);			//�X�R�A�ݒ菈��
	void AddScore(int nValue);			//�X�R�A���Z����
	int GetScore(void);					//�X�R�A�擾����
	void SetScorePos(D3DXVECTOR3 pos);	//�X�R�A�ʒu�ݒ菈��
	CNumber *GetNumber(int nNumber);

	static CScore *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	CNumber *m_apNumber[MAX_SCORE_POLYGON];			//number�̃C���X�^���X
	int m_nScore;									//�X�R�A
	D3DXVECTOR3 m_size;								//�T�C�Y
	D3DXVECTOR3 m_pos;								//�ʒu
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_SCORE_H_