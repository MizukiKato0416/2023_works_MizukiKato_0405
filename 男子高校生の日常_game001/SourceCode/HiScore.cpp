//=======================================================================
//�n�C�X�R�A�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdio.h>
#include "main.h"
#include "HiScore.h"

//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureHiScore = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHiScore = NULL;		//���_�o�b�t�@�ւ̃|�C���^
HiScore g_aHiScorePolygon[MAX_HI_SCORE_POLYGON];							//�X�R�A
int g_aHiScore[2];										//0���V�����X�R�A

//=======================================================================
//����������
//=======================================================================
void InitHiScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�ŃA�C�X�̃|�C���^
	int nCntHiScore;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�X�R�A�̈ʒu�̏�����
	for (nCntHiScore = 0; nCntHiScore < MAX_HI_SCORE_POLYGON; nCntHiScore++)
	{
		g_aHiScorePolygon[nCntHiScore].pos = D3DXVECTOR3(HI_SCORE_POLYGON_POS_WIDTH - (HI_SCORE_POLYGON_WIDTH*(MAX_HI_SCORE_POLYGON - nCntHiScore) + (HI_SCORE_POLYGON_WIDTH / 2)), HI_SCORE_POLYGON_POS_HEIGHT, 0.0f);
	}


	g_aHiScore[0] = 0;
	g_aHiScore[1] = 0;



	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//score.png",
		&g_pTextureHiScore);



	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_HI_SCORE_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffHiScore,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffHiScore->Lock(0, 0, (void**)&pVtx, 0);


	for (nCntHiScore = 0; nCntHiScore < MAX_HI_SCORE_POLYGON; nCntHiScore++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(HI_SCORE_POLYGON_POS_WIDTH - (HI_SCORE_POLYGON_WIDTH*(MAX_HI_SCORE_POLYGON - nCntHiScore)), HI_SCORE_POLYGON_POS_HEIGHT - HI_SCORE_POLYGON_HEIGHT / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(HI_SCORE_POLYGON_POS_WIDTH - (HI_SCORE_POLYGON_WIDTH*(MAX_HI_SCORE_POLYGON - nCntHiScore - 1)), HI_SCORE_POLYGON_POS_HEIGHT - HI_SCORE_POLYGON_HEIGHT / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(HI_SCORE_POLYGON_POS_WIDTH - (HI_SCORE_POLYGON_WIDTH*(MAX_HI_SCORE_POLYGON - nCntHiScore)), HI_SCORE_POLYGON_POS_HEIGHT + HI_SCORE_POLYGON_HEIGHT / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(HI_SCORE_POLYGON_POS_WIDTH - (HI_SCORE_POLYGON_WIDTH*(MAX_HI_SCORE_POLYGON - nCntHiScore - 1)), HI_SCORE_POLYGON_POS_HEIGHT + HI_SCORE_POLYGON_HEIGHT / 2, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

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
	g_pVtxBuffHiScore->Unlock();



	//���[�h����
	FILE *pFile;

	pFile = fopen("score.txt", "r");
	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &g_aHiScore[1]);
		fclose(pFile);
	}
	else
	{
		printf("�t�@�C�����J���܂���ł���\n");
	}

}

//=======================================================================
//�I������
//=======================================================================
void UninitHiScore(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureHiScore != NULL)
	{
		g_pTextureHiScore->Release();
		g_pTextureHiScore = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffHiScore != NULL)
	{
		g_pVtxBuffHiScore->Release();
		g_pVtxBuffHiScore = NULL;
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateHiScore(void)
{
	int nCntHiScore;
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
							//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffHiScore->Lock(0, 0, (void**)&pVtx, 0);

	
	if (g_aHiScore[0] >= g_aHiScore[1])
	{
		//�Z�[�u����
		FILE *pFile;
		pFile = fopen("score.txt", "w");
		if (pFile != NULL)
		{
			fprintf(pFile, "%d\n", g_aHiScore[0]);
			fclose(pFile);
		}
		else
		{
			printf("�t�@�C�����J���܂���ł���");
		}

		for (nCntHiScore = 0; nCntHiScore < MAX_HI_SCORE_POLYGON; nCntHiScore++)
		{
			//���_���W
			pVtx[0].pos = D3DXVECTOR3(HI_SCORE_POLYGON_POS_WIDTH - (HI_SCORE_POLYGON_WIDTH*(MAX_HI_SCORE_POLYGON - nCntHiScore)), HI_SCORE_POLYGON_POS_HEIGHT - HI_SCORE_POLYGON_HEIGHT / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(HI_SCORE_POLYGON_POS_WIDTH - (HI_SCORE_POLYGON_WIDTH*(MAX_HI_SCORE_POLYGON - nCntHiScore - 1)), HI_SCORE_POLYGON_POS_HEIGHT - HI_SCORE_POLYGON_HEIGHT / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(HI_SCORE_POLYGON_POS_WIDTH - (HI_SCORE_POLYGON_WIDTH*(MAX_HI_SCORE_POLYGON - nCntHiScore)), HI_SCORE_POLYGON_POS_HEIGHT + HI_SCORE_POLYGON_HEIGHT / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(HI_SCORE_POLYGON_POS_WIDTH - (HI_SCORE_POLYGON_WIDTH*(MAX_HI_SCORE_POLYGON - nCntHiScore - 1)), HI_SCORE_POLYGON_POS_HEIGHT + HI_SCORE_POLYGON_HEIGHT / 2, 0.0f);
			
			if (nCntHiScore == 0)
			{
				pVtx[0].tex = D3DXVECTOR2(g_aHiScore[0] / (int)powf(10, 7)*0.1f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_aHiScore[0] / (int)powf(10, 7)*0.1f + 0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aHiScore[0] / (int)powf(10, 7)*0.1f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_aHiScore[0] / (int)powf(10, 7)*0.1f + 0.1f, 1.0f);
			}
			else if (nCntHiScore == 7)
			{
				pVtx[0].tex = D3DXVECTOR2(g_aHiScore[0] % 10 * 0.1f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_aHiScore[0] % 10 * 0.1f + 0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aHiScore[0] % 10 * 0.1f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_aHiScore[0] % 10 * 0.1f + 0.1f, 1.0f);
			}
			else
			{
				pVtx[0].tex = D3DXVECTOR2(g_aHiScore[0] % (int)powf(10, MAX_HI_SCORE_POLYGON - nCntHiScore) / (int)powf(10, 7 - nCntHiScore) *0.1f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_aHiScore[0] % (int)powf(10, MAX_HI_SCORE_POLYGON - nCntHiScore) / (int)powf(10, 7 - nCntHiScore)*0.1f + 0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aHiScore[0] % (int)powf(10, MAX_HI_SCORE_POLYGON - nCntHiScore) / (int)powf(10, 7 - nCntHiScore)*0.1f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_aHiScore[0] % (int)powf(10, MAX_HI_SCORE_POLYGON - nCntHiScore) / (int)powf(10, 7 - nCntHiScore)*0.1f + 0.1f, 1.0f);
			}

			pVtx += 4;
		}
	}
	else if (g_aHiScore[0] <= g_aHiScore[1])
	{
		for (nCntHiScore = 0; nCntHiScore < MAX_HI_SCORE_POLYGON; nCntHiScore++)
		{

			//���_���W
			pVtx[0].pos = D3DXVECTOR3(HI_SCORE_POLYGON_POS_WIDTH - (HI_SCORE_POLYGON_WIDTH*(MAX_HI_SCORE_POLYGON - nCntHiScore)), HI_SCORE_POLYGON_POS_HEIGHT - HI_SCORE_POLYGON_HEIGHT / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(HI_SCORE_POLYGON_POS_WIDTH - (HI_SCORE_POLYGON_WIDTH*(MAX_HI_SCORE_POLYGON - nCntHiScore - 1)), HI_SCORE_POLYGON_POS_HEIGHT - HI_SCORE_POLYGON_HEIGHT / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(HI_SCORE_POLYGON_POS_WIDTH - (HI_SCORE_POLYGON_WIDTH*(MAX_HI_SCORE_POLYGON - nCntHiScore)), HI_SCORE_POLYGON_POS_HEIGHT + HI_SCORE_POLYGON_HEIGHT / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(HI_SCORE_POLYGON_POS_WIDTH - (HI_SCORE_POLYGON_WIDTH*(MAX_HI_SCORE_POLYGON - nCntHiScore - 1)), HI_SCORE_POLYGON_POS_HEIGHT + HI_SCORE_POLYGON_HEIGHT / 2, 0.0f);

			if (nCntHiScore == 0)
			{
				pVtx[0].tex = D3DXVECTOR2(g_aHiScore[1] / (int)powf(10, 7)*0.1f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_aHiScore[1] / (int)powf(10, 7)*0.1f + 0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aHiScore[1] / (int)powf(10, 7)*0.1f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_aHiScore[1] / (int)powf(10, 7)*0.1f + 0.1f, 1.0f);
			}
			else if (nCntHiScore == 7)
			{
				pVtx[0].tex = D3DXVECTOR2(g_aHiScore[1] % 10 * 0.1f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_aHiScore[1] % 10 * 0.1f + 0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aHiScore[1] % 10 * 0.1f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_aHiScore[1] % 10 * 0.1f + 0.1f, 1.0f);
			}
			else
			{
				pVtx[0].tex = D3DXVECTOR2(g_aHiScore[1] % (int)powf(10, MAX_HI_SCORE_POLYGON - nCntHiScore) / (int)powf(10, 7 - nCntHiScore) *0.1f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_aHiScore[1] % (int)powf(10, MAX_HI_SCORE_POLYGON - nCntHiScore) / (int)powf(10, 7 - nCntHiScore)*0.1f + 0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aHiScore[1] % (int)powf(10, MAX_HI_SCORE_POLYGON - nCntHiScore) / (int)powf(10, 7 - nCntHiScore)*0.1f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_aHiScore[1] % (int)powf(10, MAX_HI_SCORE_POLYGON - nCntHiScore) / (int)powf(10, 7 - nCntHiScore)*0.1f + 0.1f, 1.0f);
			}

			pVtx += 4;
		}
	}
	


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHiScore->Unlock();


	
	
}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawHiScore(void)
{
	int nCntHiScore;

	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����
												//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffHiScore, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//���_�t�H�[�}�b�g�̐ݒ�

	for (nCntHiScore = 0; nCntHiScore < MAX_HI_SCORE_POLYGON; nCntHiScore++)
	{
		//�e�N�X�`��
		pDevice->SetTexture(0, g_pTextureHiScore);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
			nCntHiScore * 4,					//�`����J�n���钸�_�̃C���f�b�N�X
			2);					//�`�悷��v���~�e�B�u��
	}

}

//=======================================================================
//�ݒ菈��
//=======================================================================
void SetHiScore(int nHiScore)
{
	g_aHiScore[0] = nHiScore;
}
