//=======================================================================
//�ǂɊւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "effect.h"
#include "shadow.h"


//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureEffect[EFFECT_TYPE] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;			//���_�o�b�t�@�ւ̃|�C���^
EFFECT g_aEffect[MAX_EFFECT];									//�Ǎ\����


//=======================================================================
//����������
//=======================================================================
HRESULT InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//������
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].fWidth = EFFECT_WIDTH;
		g_aEffect[nCntEffect].fHeight = EFFECT_HEIGHT;
		g_aEffect[nCntEffect].fDepth = EFFECT_DEPTH;
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].scale = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].bUse = false;

	}
	

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/effect000.jpg",
		&g_pTextureEffect[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 *MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fWidth / 2.0f, g_aEffect[nCntEffect].fHeight / 2.0f, g_aEffect[nCntEffect].fDepth / 2.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fWidth / 2.0f, g_aEffect[nCntEffect].fHeight / 2.0f, g_aEffect[nCntEffect].fDepth / 2.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fWidth / 2.0f, -g_aEffect[nCntEffect].fHeight / 2.0f, g_aEffect[nCntEffect].fDepth / 2.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fWidth / 2.0f, -g_aEffect[nCntEffect].fHeight / 2.0f, g_aEffect[nCntEffect].fDepth / 2.0f);

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
	g_pVtxBuffEffect->Unlock();

	return S_OK;
}

//=======================================================================
//�I������
//=======================================================================
void UninitEffect(void)
{
	int nCntEffect;
	for (nCntEffect = 0; nCntEffect < EFFECT_TYPE; nCntEffect++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureEffect[nCntEffect] != NULL)
		{
			g_pTextureEffect[nCntEffect]->Release();
			g_pTextureEffect[nCntEffect] = NULL;
		}
	}


	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateEffect(void)
{
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			g_aEffect[nCntEffect].pos += g_aEffect[nCntEffect].move;
			g_aEffect[nCntEffect].nLife--;
			if (g_aEffect[nCntEffect].nLife <= 0)
			{
				g_aEffect[nCntEffect].nLife = 0;
				g_aEffect[nCntEffect].bUse = false;
			}
			
			if (g_aEffect[nCntEffect].nType == EFFEFCT_MOVETYPE_ENEMY_DEATH)
			{
				g_aEffect[nCntEffect].move.y -= 0.1f;
				if (g_aEffect[nCntEffect].pos.y <= 0.0f)
				{
					g_aEffect[nCntEffect].move.y = 0.5f;
				}
			}
		}
	}

}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����

	D3DXMATRIX mtxTrans;				//�ʒu�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxScale;				//�X�P�[���v�Z�p�}�g���b�N�X


	//���C�g����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);


	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{

			//���u�����f�B���O�����Z�����ɐݒ�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			//���e�X�g
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 190);

			D3DXMatrixIdentity(&g_aEffect[nCntEffect].mtxWorld);		//���[���h�}�g���b�N�X�̏�����


			pDevice->GetTransform(D3DTS_VIEW, &g_aEffect[nCntEffect].mtxView);	//�r���[�}�g���b�N�X���擾


			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			//�t�s������߂�	
			g_aEffect[nCntEffect].mtxWorld._11 = g_aEffect[nCntEffect].mtxView._11 * g_aEffect[nCntEffect].scale.x;
			g_aEffect[nCntEffect].mtxWorld._12 = g_aEffect[nCntEffect].mtxView._21 * g_aEffect[nCntEffect].scale.x;
			g_aEffect[nCntEffect].mtxWorld._13 = g_aEffect[nCntEffect].mtxView._31 * g_aEffect[nCntEffect].scale.x;
			g_aEffect[nCntEffect].mtxWorld._21 = g_aEffect[nCntEffect].mtxView._12 * g_aEffect[nCntEffect].scale.y;
			g_aEffect[nCntEffect].mtxWorld._22 = g_aEffect[nCntEffect].mtxView._22 * g_aEffect[nCntEffect].scale.y;
			g_aEffect[nCntEffect].mtxWorld._23 = g_aEffect[nCntEffect].mtxView._32 * g_aEffect[nCntEffect].scale.y;
			g_aEffect[nCntEffect].mtxWorld._31 = g_aEffect[nCntEffect].mtxView._13;
			g_aEffect[nCntEffect].mtxWorld._32 = g_aEffect[nCntEffect].mtxView._23;
			g_aEffect[nCntEffect].mtxWorld._33 = g_aEffect[nCntEffect].mtxView._33;
			//g_aEffect[nCntEffect].mtxWorld._41 = 0.0f;
			//g_aEffect[nCntEffect].mtxWorld._42 = 0.0f;
			//g_aEffect[nCntEffect].mtxWorld._43 = 0.0f;

			//�X�P�[���𔽉f
			//D3DXMatrixScaling(&mtxScale, g_aEffect[nCntEffect].scale.x, g_aEffect[nCntEffect].scale.y, g_aEffect[nCntEffect].scale.z);		//�X�P�[���s����쐬
			//D3DXMatrixMultiply(&g_aEffect[nCntEffect].mtxWorld, &g_aEffect[nCntEffect].mtxWorld, &mtxScale);	//�X�P�[���𔽉f

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCntEffect].pos.x, g_aEffect[nCntEffect].pos.y, g_aEffect[nCntEffect].pos.z);		//�ړ��s����쐬
			D3DXMatrixMultiply(&g_aEffect[nCntEffect].mtxWorld, &g_aEffect[nCntEffect].mtxWorld, &mtxTrans);	//�ړ��𔽉f

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCntEffect].mtxWorld);

			//Z�e�X�g
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);			//���_�t�H�[�}�b�g�̐ݒ�

			pDevice->SetTexture(0, g_pTextureEffect[0]);	//�e�N�X�`���̐ݒ�

															//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				nCntEffect * 4,					//�J�n���钸�_�̃C���f�b�N�X
				2);					//�`�悷��v���~�e�B�u��

			
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

			//a�u�����f�B���O��ʏ�ɖ߂�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
	}

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, D3DXCOLOR col, int nLife, EFFECT_MOVETYPE nType)
{
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].move = move;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].nType = nType;
			g_aEffect[nCntEffect].scale.x = fWidth;
			g_aEffect[nCntEffect].scale.y = fHeight;

			g_aEffect[nCntEffect].bUse = true;

			VERTEX_3D *pVtx;		//���_���ւ̃|�C���^
			//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
			g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += nCntEffect * 4;

			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffEffect->Unlock();
			break;
		}
	}
}

EFFECT *GetEffect(void)
{
	return &g_aEffect[0];
}