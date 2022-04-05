//=======================================================================
//�J�����Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"

//========================================================
//�}�N����`
//========================================================
#define MAX_CAMERA				(2)			//�J�����̍ő吔
#define MAX_RESULT_CAMERA		(1)			//���U���g�̃J�����̍ő吔
#define CAMERA_R_SPEED			(0.03f)		//�J�����̐���X�s�[�h
#define CAMERA_VR_SPEED			(4.0f)		//�J�����̈ړ�
#define CAMERA_DISTANCE			(300.0f)	//���_�ƒ����_�̋���
#define CAMERA_RESULT_DISTANCE	(200.0f)	//���U���g�̎��_�ƒ����_�̋���
#define CAMERA_V_MAX_POS_Y		(400.0f)	//���_��y���W�ő�l
#define CAMERA_V_MIN_POS_Y		(50.0f)		//���_��y���W�ŏ��l
#define CAMERA_MAX_RENDERER		(20000.0f)	//camera�ł̕`��ő�Z�l
#define CAMERA_MIN_RENDERER		(10.0f)		//camera�ł̕`��ŏ�Z�l

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CCamera
{
public:
	CCamera();				//�R���X�g���N�^
	~CCamera();				//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 m_pos, D3DXVECTOR3 rot, float viewportX, float viewportY, float viewportWidth, float viewporHeight);
	void Uninit(void);
	void Update(void);
	static CCamera *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float viewportX, float viewportY, float viewportWidth, float viewporHeight);
	void Set(void);
	D3DXVECTOR3 GetPosV(void);		//���_�擾����
	D3DXVECTOR3 GetPosR(void);		//�����_�擾����
	void SetPosV(D3DXVECTOR3 pos);	//���_�ݒ菈��
	void SetPosR(D3DXVECTOR3 pos);	//�����_�ݒ菈��
	D3DXVECTOR3 GetRotV(void);		//���_�̌����擾����
	void SetRotV(D3DXVECTOR3 rot);	//���_�̌����ݒ菈��
	void SetNum(int nNum);			//camera�̌̎��ʔԍ��ݒ菈��
	int GetNum(void);				//camera�̌̎��ʔԍ��擾����
	D3DVIEWPORT9 *GetViewPort(void) { return &m_viewport; }

private:
	D3DXVECTOR3 m_posV;						//���݂̎��_
	D3DXVECTOR3 m_posVDest;					//�ړI�̎��_
	D3DXVECTOR3 m_posR;						//���݂̒����_
	D3DXVECTOR3 m_posRDest;					//�ړI�̒����_
	D3DXVECTOR3 m_vecU;						//������x�N�g��
	D3DXVECTOR3 m_rot;						//���_�̌���
	D3DXVECTOR3 m_rotAsk;					//�ړI�̌���
	float m_rotDiffer;						//�ړI�̌����Ƃ̍�
	D3DXMATRIX m_mtxProjection;				//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;					//�r���[�}�g���b�N�X
	D3DVIEWPORT9 m_viewport;				//�r���[�|�[�g
	D3DXMATRIX m_mtxWorldCamera;			//���[���h�}�g���b�N�X
	bool m_bTurn;							//�J��������]�����ǂ���
	int m_nNum;								//camera�̌̎��ʔԍ�
};

#endif //!_CAMERA_H_

