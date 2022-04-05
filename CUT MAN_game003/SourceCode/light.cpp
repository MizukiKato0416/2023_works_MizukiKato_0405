//=======================================================================
//���C�g�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "light.h"

//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================
D3DLIGHT9 g_alight[3];

//=======================================================================
//����������
//=======================================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	D3DXVECTOR3 vecDir[MAX_LIGHT];				//�ݒ�p�����x�N�g��

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//���C�g���N���A����
		ZeroMemory(&g_alight[nCntLight], sizeof(D3DLIGHT9));

		//���C�g�̎�ނ�ݒ�
		g_alight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;		//���s����

													//���C�g�̊g�U����ݒ�
		g_alight[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//���C�g�̕�����ݒ�
		vecDir[0] = D3DXVECTOR3(-0.4f, 0.8f, 0.4f);
		vecDir[1] = D3DXVECTOR3(0.4f, -0.2f, -0.4f);
		vecDir[2] = D3DXVECTOR3(0.0f, 0.4f, 0.4f);
		D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);			//���K������(�x�N�g���̑傫����1�ɂ���)
		g_alight[nCntLight].Direction = vecDir[nCntLight];

		//���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &g_alight[nCntLight]);

		//���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//=======================================================================
//�I������
//=======================================================================
void UninitLight(void)
{
	
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateLight(void)
{
	
}