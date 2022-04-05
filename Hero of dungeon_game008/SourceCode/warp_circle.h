//===========================================
//���[�v���@�w����
//Author:KatoMizuki
//===========================================
#ifndef _WARP_CIRCLE_H_
#define _WARP_CIRCLE_H_
#include "magic_circle.h"

//�O���錾
class CUi;

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CWarpCircle : public CMagicCircle
{
public:
	CWarpCircle(int nPriority = PRIORITY_POLYGON_3D);		//�R���X�g���N�^
	~CWarpCircle();											//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CWarpCircle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);

private:
	//�����o�֐�
	bool CollisionPlayer(void);		//�v���C���[�Ƃ̓����蔻��
	void EffectSpawn(void);			//�G�t�F�N�g��������
	void Object3DSpawn(void);		//��ɏオ��3D�I�u�W�F�N�g��������

	int m_nEffectCounter;			//�G�t�F�N�g���o���p�x�̃J�E���^�[
	int m_nObject3DCounter;			//��ɏオ��object3D���o���p�x�̃J�E���^�[
	CObject3D *m_pObject3D;			//object3D�̃|�C���^
	CUi *m_pUiMessage;				//���b�Z�[�WUI�̃|�C���^
};

#endif // !_WARP_CIRCLE_H_