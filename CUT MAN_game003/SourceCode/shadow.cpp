//=======================================================================
//�v���C���[�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "shadow.h"
#include "model.h"
#include "enemy.h"


//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureShadow[SHADOW_TYPE] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;			//���_�o�b�t�@�ւ̃|�C���^
SHADOW g_aShadow[MAX_SHADOW];											//�v���C���[�\����

//=======================================================================
//����������
//=======================================================================
HRESULT InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//������
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_aShadow[nCntShadow].fWidth = 50.0f;
		g_aShadow[nCntShadow].fHeight = 0.0f;
		g_aShadow[nCntShadow].fDepth = 50.0f;
		g_aShadow[nCntShadow].nType = 0;
		g_aShadow[nCntShadow].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].bUse = false;
	}


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/shadow000.jpg",
		&g_pTextureShadow[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 *MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		pVtx[0].pos = D3DXVECTOR3(-g_aShadow[nCntShadow].fWidth / 2.0f, g_aShadow[nCntShadow].pos.y ,  g_aShadow[nCntShadow].fDepth / 2.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aShadow[nCntShadow].fWidth / 2.0f, g_aShadow[nCntShadow].pos.y ,  g_aShadow[nCntShadow].fDepth / 2.0f);
		pVtx[2].pos = D3DXVECTOR3(- g_aShadow[nCntShadow].fWidth / 2.0f, g_aShadow[nCntShadow].pos.y ,  - g_aShadow[nCntShadow].fDepth / 2.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aShadow[nCntShadow].fWidth / 2.0f, g_aShadow[nCntShadow].pos.y ,  - g_aShadow[nCntShadow].fDepth / 2.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 40);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 40);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 40);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 40);


		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();

	return S_OK;
}

//=======================================================================
//�I������
//=======================================================================
void UninitShadow(void)
{
	int nCntShadow;
	for (nCntShadow = 0; nCntShadow < SHADOW_TYPE; nCntShadow++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureShadow[nCntShadow] != NULL)
		{
			g_pTextureShadow[nCntShadow]->Release();
			g_pTextureShadow[nCntShadow] = NULL;
		}
	}


	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateShadow(void)
{

}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	


	//���e�X�g
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 180);

	//z�e�X�g
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//���C�g����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == true)
		{
			//���Z�����̐ݒ�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorld);		//���[���h�}�g���b�N�X�̏�����

			//�X�P�[���𔽉f
//			g_aShadow[nCntShadow].mtxWorld._11 = g_aShadow[nCntShadow].fWidth;
//			g_aShadow[nCntShadow].mtxWorld._22 = g_aShadow[nCntShadow].fHeight;
//			g_aShadow[nCntShadow].mtxWorld._33 = g_aShadow[nCntShadow].fDepth;

																		//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);			//���_�t�H�[�}�b�g�̐ݒ�

			pDevice->SetTexture(0, g_pTextureShadow[g_aShadow[nCntShadow].nType]);	//�e�N�X�`���̐ݒ�

																					//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				nCntShadow * 4,					//�J�n���钸�_�̃C���f�b�N�X
				2);					//�`�悷��v���~�e�B�u��
			//�ʏ�̍����ɖ߂�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		}
	}


	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);


	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
}

int SetShadow(D3DXVECTOR3 pos, float fWidth, float fDepth)
{
	int nIdx = -1;
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == false)
		{
			g_aShadow[nCntShadow].pos = pos;
			g_aShadow[nCntShadow].fWidth = fWidth;
			g_aShadow[nCntShadow].fDepth = fDepth;

			g_aShadow[nCntShadow].bUse = true;
			nIdx = nCntShadow;
			break;
		}
	}
	return nIdx;
}

void SetPositionShadow(int nIdx, D3DXVECTOR3 pos , bool bUse)
{
	if (g_aShadow[nIdx].bUse == true)
	{
		g_aShadow[nIdx].pos.x = pos.x;
		//g_aShadow[nIdx].pos.y = pos.y;
		g_aShadow[nIdx].pos.z = pos.z;

		if (bUse == false)
		{
			g_aShadow[nIdx].bUse = false;
		}
	}
}

//=======================================================================
//�擾����
//=======================================================================
SHADOW *GetShadow(void)
{
	return &g_aShadow[0];
}