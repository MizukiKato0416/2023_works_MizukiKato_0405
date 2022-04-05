//=======================================================================
//�i���Q�[�W�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================
#ifndef _EVOLUTIONGAUGE_H_
#define _EVOLUTIONGAUGE_H_
#include "main.h"

//========================================================
////�}�N����`
//========================================================
#define MAX_EVOLUTIONGAUGE (1)			//�Q�[�W�̍ő吔
#define MAX_EVOLUTIONGAUGE_ADD (20)		//�Q�[�W�̂��܂�ő吔
#define EVOLUTIONGAUGE_WIDTH (450.0f)	//�Q�[�W�̉���
#define EVOLUTIONGAUGE_HEIGHT (50.0f)	//�Q�[�W�̏c��

//========================================================
//�Q�[�W�̎��
//========================================================
typedef enum
{
	EVOLUTION_GAUGETYPE_PLAYER = 0,			//�v���C���[
	EVOLUTION_GAUGETYPE_MAX,
} EVOLUTION_GAUGETYPE;

//========================================================
//�����̂̍\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	EVOLUTION_GAUGETYPE nType;		//�^�C�v
	float fWidth;					//��
	float fHeight;					//����
	float fCnt;						//���݂̃Q�[�W��
	bool bUse;						//�g�p���Ă��邩�ǂ���
	bool bGaugeMax;					//�Q�[�W���}�b�N�X���ǂ���
	bool bEvolution;				//�i�������ǂ���
	int nTransparency;				//�����x
	int nCounter;					//�����x��ς���J�E���^�[
} EvolutionGauge;

//========================================================
//�v���g�^�C�v�錾
//========================================================
void InitEvolutionGauge(void);
void UninitEvolutionGauge(void);
void UpdateEvolutionGauge(void);
void DrawEvolutionGauge(void);
void SetEvolutionGauge(D3DXVECTOR3 pos, EVOLUTION_GAUGETYPE nType, float fWidth, float fHeight);
void SetAddEvolutionGauge(float fGauge);
EvolutionGauge *GetEvolutionGauge(void);
#endif //!_EVOLUTIONGAUGE_H_
