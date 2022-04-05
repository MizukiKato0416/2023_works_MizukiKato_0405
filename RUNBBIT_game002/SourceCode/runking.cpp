//=======================================================================
//�����L���O�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdio.h>
#include "main.h"
#include "score.h"
#include "runking.h"

//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureRunking = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRunking = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Runking g_aRunkingPolygon[MAX_RUNKING][MAX_SCORE_POLYGON];				//�X�R�A
int g_aScore[MAX_RUNKING];
bool g_bData;
int g_nCol;
int g_nData;
int g_nCntFirst;
int g_newRunking;
bool g_bData2;
bool g_bCnt;

//=======================================================================
//����������
//=======================================================================
void InitRunking(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�ŃA�C�X�̃|�C���^
	int nCntScorePolygon;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�X�R�A�̈ʒu�̏�����
	for (int nCntRunking = 0; nCntRunking < MAX_RUNKING - 1; nCntRunking++)
	{
		for (nCntScorePolygon = 0; nCntScorePolygon < MAX_SCORE_POLYGON; nCntScorePolygon++)
		{
			g_aRunkingPolygon[nCntRunking][nCntScorePolygon].pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) - (RUNKING_POLYGON_WIDTH * 3.5f) + (RUNKING_POLYGON_WIDTH * nCntScorePolygon) ,SCREEN_HEIGHT / 6.0f + (SCREEN_HEIGHT / 6.0f * nCntRunking), 0.0f);
			g_aRunkingPolygon[nCntRunking][nCntScorePolygon].bUse = true;
		}
		g_aScore[nCntRunking] = 0;
	}
	g_aScore[MAX_RUNKING - 1] = GetScore();
	g_bData = false;
	g_bData2 = false;
	g_bCnt = false;
	g_nCol = 0;
	g_newRunking = 0;
	g_nCntFirst = 0;
	g_nData = GetScore();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//score.png",
		&g_pTextureRunking);



	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE_POLYGON * MAX_RUNKING,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRunking,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffRunking->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCntRunking = 0; nCntRunking < MAX_RUNKING - 1; nCntRunking++)
	{
		for (int nCntScorePolygon = 0; nCntScorePolygon < MAX_SCORE_POLYGON; nCntScorePolygon++)
		{
			//���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aRunkingPolygon[nCntRunking][nCntScorePolygon].pos.x - RUNKING_POLYGON_WIDTH / 2.0f, g_aRunkingPolygon[nCntRunking][nCntScorePolygon].pos.y - RUNKING_POLYGON_HEIGHT / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aRunkingPolygon[nCntRunking][nCntScorePolygon].pos.x + RUNKING_POLYGON_WIDTH / 2.0f, g_aRunkingPolygon[nCntRunking][nCntScorePolygon].pos.y - RUNKING_POLYGON_HEIGHT / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aRunkingPolygon[nCntRunking][nCntScorePolygon].pos.x - RUNKING_POLYGON_WIDTH / 2.0f, g_aRunkingPolygon[nCntRunking][nCntScorePolygon].pos.y + RUNKING_POLYGON_HEIGHT / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aRunkingPolygon[nCntRunking][nCntScorePolygon].pos.x + RUNKING_POLYGON_WIDTH / 2.0f, g_aRunkingPolygon[nCntRunking][nCntScorePolygon].pos.y + RUNKING_POLYGON_HEIGHT / 2.0f, 0.0f);

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
	}


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRunking->Unlock();

	
	int nCntRunking;
	//���[�h����
	FILE *pFile;

	pFile = fopen("score.txt", "r");
	if (pFile != NULL)
	{
		for (nCntRunking = 0; nCntRunking < MAX_RUNKING - 1; nCntRunking++)
		{
 			fscanf(pFile, "%d", &g_aScore[nCntRunking]);
		}
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
void UninitRunking(void)
{
	for (int nCntRunking = 0; nCntRunking < MAX_RUNKING - 1; nCntRunking++)
	{
		for (int nCntScorePolygon = 0; nCntScorePolygon < MAX_SCORE_POLYGON; nCntScorePolygon++)
		{
			g_aRunkingPolygon[nCntRunking][nCntScorePolygon].bUse = false;
		}
	}


	//�e�N�X�`���̔j��
	if (g_pTextureRunking != NULL)
	{
		g_pTextureRunking->Release();
		g_pTextureRunking = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRunking != NULL)
	{
		g_pVtxBuffRunking->Release();
		g_pVtxBuffRunking = NULL;
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateRunking(void)
{
	//�X�R�A�̎擾
	int nCntRunking;
	
	//=======================================================================
	//�\�[�g����
	//=======================================================================

	int nCnt, nCnt2, nSubData = 0;


	for (nCnt = 0; nCnt < MAX_RUNKING -1; nCnt++)
	{
		for (nCnt2 = 0; nCnt2 < MAX_RUNKING; nCnt2++)
		{
			if (g_aScore[nCnt] < g_aScore[nCnt + 1])
			{
				nSubData = g_aScore[nCnt];
				g_aScore[nCnt] = g_aScore[nCnt + 1];
				g_aScore[nCnt + 1] = nSubData;
			}			
		}
	}


	//=======================================================================
	//�Z�[�u����
	//=======================================================================
	FILE *pFile;
	pFile = fopen("score.txt", "w");
	if (pFile != NULL)
	{
		for (nCntRunking = 0; nCntRunking < MAX_RUNKING; nCntRunking++)
		{
			fprintf(pFile, "%d\n", g_aScore[nCntRunking]);
		}
		fclose(pFile);
	}
	else
	{
		printf("�t�@�C�����J���܂���ł���");
	}

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
							//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffRunking->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aScore[0] >= g_aScore[1] && g_aScore[1] >= g_aScore[2] &&
		g_aScore[2] >= g_aScore[3] && g_aScore[3] >= g_aScore[4])
	{
		g_bCnt = true;
	}


	for (nCntRunking = 0; nCntRunking < MAX_RUNKING - 1; nCntRunking++)
	{
		for (int nCntScorePolygon = 0; nCntScorePolygon < MAX_SCORE_POLYGON; nCntScorePolygon++)
		{
			if (g_aRunkingPolygon[nCntRunking][nCntScorePolygon].bUse == true)
			{
				if (nCntScorePolygon == 0)
				{
					pVtx[0].tex = D3DXVECTOR2(g_aScore[nCntRunking] / (int)powf(10, 7)*0.1f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(g_aScore[nCntRunking] / (int)powf(10, 7)*0.1f + 0.1f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(g_aScore[nCntRunking] / (int)powf(10, 7)*0.1f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(g_aScore[nCntRunking] / (int)powf(10, 7)*0.1f + 0.1f, 1.0f);
				}
				else if (nCntScorePolygon == 7)
				{
					pVtx[0].tex = D3DXVECTOR2(g_aScore[nCntRunking] % 10 * 0.1f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(g_aScore[nCntRunking] % 10 * 0.1f + 0.1f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(g_aScore[nCntRunking] % 10 * 0.1f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(g_aScore[nCntRunking] % 10 * 0.1f + 0.1f, 1.0f);
				}
				else
				{
					pVtx[0].tex = D3DXVECTOR2(g_aScore[nCntRunking] % (int)powf(10, MAX_SCORE_POLYGON - nCntScorePolygon) / (int)powf(10, 7 - nCntScorePolygon) *0.1f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(g_aScore[nCntRunking] % (int)powf(10, MAX_SCORE_POLYGON - nCntScorePolygon) / (int)powf(10, 7 - nCntScorePolygon)*0.1f + 0.1f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(g_aScore[nCntRunking] % (int)powf(10, MAX_SCORE_POLYGON - nCntScorePolygon) / (int)powf(10, 7 - nCntScorePolygon)*0.1f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(g_aScore[nCntRunking] % (int)powf(10, MAX_SCORE_POLYGON - nCntScorePolygon) / (int)powf(10, 7 - nCntScorePolygon)*0.1f + 0.1f, 1.0f);
				}
			}

			if (g_bCnt == true)
			{
				if (g_aScore[nCntRunking] == g_nData && g_bData2 == false)
				{
					g_bData2 = true;
					g_newRunking = nCntRunking;
				}

				g_nCol++;
				if (g_nCol >= 800)
				{
					if (g_aRunkingPolygon[g_newRunking][nCntScorePolygon].bUse == false)
					{
						for (int nCnt3 = 0; nCnt3 < MAX_SCORE_POLYGON; nCnt3++)
						{
							g_aRunkingPolygon[g_newRunking][nCnt3].bUse = true;
						}
					}
					else if (g_aRunkingPolygon[g_newRunking][nCntScorePolygon].bUse == true)
					{
						for (int nCnt3 = 0; nCnt3 < MAX_SCORE_POLYGON; nCnt3++)
						{
							g_aRunkingPolygon[g_newRunking][nCnt3].bUse = false;
						}
					}
					g_nCol = 0;
				}
			}

			pVtx += 4;
		}
	}


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRunking->Unlock();



}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawRunking(void)
{
	int nCntRunking;

	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����
												//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRunking, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//���_�t�H�[�}�b�g�̐ݒ�

	int nCnt=0;
	
	for (nCntRunking = 0; nCntRunking < MAX_RUNKING - 1; nCntRunking++)
	{
		for (int nCntScorePolygon = 0; nCntScorePolygon < MAX_SCORE_POLYGON; nCntScorePolygon++)
		{
			if (g_aRunkingPolygon[nCntRunking][nCntScorePolygon].bUse == true)
			{
				//�e�N�X�`��
				pDevice->SetTexture(0, g_pTextureRunking);

				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
					nCnt * 4,					//�`����J�n���钸�_�̃C���f�b�N�X
					2);					//�`�悷��v���~�e�B�u��
			}
			nCnt++;
		}
	}
	
}

//=======================================================================
//�ݒ菈��
//=======================================================================
void SetRunking(int nRunking)
{
	//g_aRunking[0][0] += nRunking;
}

