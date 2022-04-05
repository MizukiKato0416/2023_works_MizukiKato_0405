//=======================================================================
//�e�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "bullet.h"
#include "shadow.h"
#include "model.h"
#include "camera.h"


//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureBullet[BULLET_TYPE] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;			//���_�o�b�t�@�ւ̃|�C���^
BULLET g_aBullet[MAX_BULLET];									//�Ǎ\����


//=======================================================================
//����������
//=======================================================================
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//������
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].fWidth = BULLET_WIDTH;
		g_aBullet[nCntBullet].fHeight = BULLET_HEIGHT;
		g_aBullet[nCntBullet].fDepth = BULLET_DEPTH;
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].scale = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].bUse = false;
	}
	

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/test000.jpg",
		&g_pTextureBullet[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 *MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		pVtx[0].pos = D3DXVECTOR3(-g_aBullet[nCntBullet].fWidth / 2.0f, g_aBullet[nCntBullet].fHeight / 2.0f, g_aBullet[nCntBullet].fDepth / 2.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].fWidth / 2.0f, g_aBullet[nCntBullet].fHeight / 2.0f, g_aBullet[nCntBullet].fDepth / 2.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aBullet[nCntBullet].fWidth / 2.0f, -g_aBullet[nCntBullet].fHeight / 2.0f, g_aBullet[nCntBullet].fDepth / 2.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].fWidth / 2.0f, -g_aBullet[nCntBullet].fHeight / 2.0f, g_aBullet[nCntBullet].fDepth / 2.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();

	/*for (int nCntBullet = 0; nCntBullet < MAX_Bullet; nCntBullet++)
	{
		SetShadow(D3DXVECTOR3(g_aBullet[nCntBullet].pos.x,0.0f, g_aBullet[nCntBullet].pos.z), 50.0f, 50.0f);

	}

*/


	return S_OK;
}

//=======================================================================
//�I������
//=======================================================================
void UninitBullet(void)
{
	int nCntBullet;
	for (nCntBullet = 0; nCntBullet < BULLET_TYPE; nCntBullet++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureBullet[nCntBullet] != NULL)
		{
			g_pTextureBullet[nCntBullet]->Release();
			g_pTextureBullet[nCntBullet] = NULL;
		}
	}


	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateBullet(void)
{
	MODEL *pModel;
	pModel = GetModel();

	Camera * pCamera;
	pCamera = GetCamera();

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			if (g_aBullet[nCntBullet].pos.x >= 1000.0f || g_aBullet[nCntBullet].pos.x <= -1000.0f ||
				g_aBullet[nCntBullet].pos.z >= 1000.0f || g_aBullet[nCntBullet].pos.z <= -1000.0f)
			{
				g_aBullet[nCntBullet].bUse = false;
			}
		}
	}

}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����

	D3DXMATRIX mtxTrans;				//�ʒu�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxScale;				//�X�P�[���v�Z�p�}�g���b�N�X

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			D3DXMatrixIdentity(&g_aBullet[nCntBullet].mtxWorld);		//���[���h�}�g���b�N�X�̏�����


			pDevice->GetTransform(D3DTS_VIEW, &g_aBullet[nCntBullet].mtxView);	//�r���[�}�g���b�N�X���擾


			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			//�t�s������߂�	
			g_aBullet[nCntBullet].mtxWorld._11 = g_aBullet[nCntBullet].mtxView._11 * g_aBullet[nCntBullet].scale.x;
			g_aBullet[nCntBullet].mtxWorld._12 = g_aBullet[nCntBullet].mtxView._21 * g_aBullet[nCntBullet].scale.x;
			g_aBullet[nCntBullet].mtxWorld._13 = g_aBullet[nCntBullet].mtxView._31 * g_aBullet[nCntBullet].scale.x;
			g_aBullet[nCntBullet].mtxWorld._21 = g_aBullet[nCntBullet].mtxView._12 * g_aBullet[nCntBullet].scale.y;
			g_aBullet[nCntBullet].mtxWorld._22 = g_aBullet[nCntBullet].mtxView._22 * g_aBullet[nCntBullet].scale.y;
			g_aBullet[nCntBullet].mtxWorld._23 = g_aBullet[nCntBullet].mtxView._32 * g_aBullet[nCntBullet].scale.y;
			g_aBullet[nCntBullet].mtxWorld._31 = g_aBullet[nCntBullet].mtxView._13;
			g_aBullet[nCntBullet].mtxWorld._32 = g_aBullet[nCntBullet].mtxView._23;
			g_aBullet[nCntBullet].mtxWorld._33 = g_aBullet[nCntBullet].mtxView._33;
			//g_aBullet[nCntBullet].mtxWorld._41 = 0.0f;
			//g_aBullet[nCntBullet].mtxWorld._42 = 0.0f;
			//g_aBullet[nCntBullet].mtxWorld._43 = 0.0f;

			//�X�P�[���𔽉f
			//D3DXMatrixScaling(&mtxScale, g_aBullet[nCntBullet].scale.x, g_aBullet[nCntBullet].scale.y, g_aBullet[nCntBullet].scale.z);		//�X�P�[���s����쐬
			//D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorld, &g_aBullet[nCntBullet].mtxWorld, &mtxScale);	//�X�P�[���𔽉f

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);		//�ړ��s����쐬
			D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorld, &g_aBullet[nCntBullet].mtxWorld, &mtxTrans);	//�ړ��𔽉f

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].mtxWorld);

			//�ǂւ̂߂荞�݉��
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);		//Z�e�X�g
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);			//Z�o�b�t�@�̍X�V

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);			//���_�t�H�[�}�b�g�̐ݒ�

			pDevice->SetTexture(0, g_pTextureBullet[0]);	//�e�N�X�`���̐ݒ�

															//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				nCntBullet * 4,					//�J�n���钸�_�̃C���f�b�N�X
				2);					//�`�悷��v���~�e�B�u��

			//�ǂւ̂߂荞�݉��
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		}
	}
}

void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight)
{
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].scale.x = fWidth;
			g_aBullet[nCntBullet].scale.y = fHeight;

			g_aBullet[nCntBullet].bUse = true;
			break;
		}
	}
}

BULLET *GetBullet(void)
{
	return &g_aBullet[0];
}