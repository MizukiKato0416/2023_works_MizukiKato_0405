//===========================================
//�^�C������
//Author:��������
//===========================================
#ifndef _TIME_H_
#define _TIME_H_
#include "scene.h"
#include "number.h"

//================================================
//�}�N����`
//================================================
#define MAX_TIME_POLYGON		(6)				//�|���S���̍ő吔
#define TIME_POLIGON_POSY		(30.0f)			//�^�C���̃|���S����posY
#define TIME_POLYGON_WIDTH		(50.0f)			//�|���S���̕�
#define TIME_POLYGON_HEIGHT		(80.0f)			//�|���S���̍���
#define START_TIME				(0)				//�ŏ��̃^�C��

//================================================
//�O���錾
//================================================
class CUi;

//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CTimer : public CScene
{
public:
	CTimer(int nPriority = PRIORITY_UI);	//�R���X�g���N�^
	~CTimer();								//�f�X�g���N�^

											//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddTime(int nValue);
	void SetTime(int nTime);
	int GetTime(void);
	CNumber *GetNumber(int nNumber);

	static CTimer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	CNumber *m_apNumber[MAX_TIME_POLYGON];	//number�̃C���X�^���X
	int m_nTime;							//�^�C��
	CUi *m_pUi;								//UI�̃|�C���^

};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_SCORE_H_#pragma once
