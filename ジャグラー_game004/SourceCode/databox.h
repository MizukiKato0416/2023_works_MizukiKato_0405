#ifndef _DATABOX_H_
#define _DATABOX_H_

#include "main.h"

typedef enum
{
	EAWASE_ANIMALS = 0,
	EAWASE_SHAPE,
	EAWASE_CARS,
	EAWASE_MAX
}Eawase;

//�����f�[�^++++++++++++++++++++++++++++

typedef struct
{
	bool bPause;		//�|�[�Y
	int nFever;			//�t�B�[�o�[�Q�[�W(MAX300)
	bool bFever;		//�t�B�[�o�[��������
	int nFeverTime;		//�t�B�[�o�[�I���܂ł̎c�莞��
	bool nTitleNum;		//�^�C�g���ԍ�
	bool bFeverMan;
	bool bOK;
}Data;

//---------------------------------

//�v���g�^�C�v�錾
void Initdata(void);		//���S������
void Resetdata(void);		//������
Data *GetData(void);

#endif //_DATABOX_H_