//=======================================================================
//�����L���O�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdio.h>
#include "main.h"
#include "score.h"
#include "ranking.h"

//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureRanking = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Ranking g_aRankingPolygon[MAX_RANKING][MAX_SCORE_POLYGON];				//�X�R�A
int g_aScore[MAX_RANKING];
bool g_bData;
int g_nCol;
int g_nData;
int g_nCntFirst;
int g_newRanking;
bool g_bData2;
bool g_bCnt;

//=======================================================================
//����������
//=======================================================================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�ŃA�C�X�̃|�C���^
	int nCntScorePolygon;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�X�R�A�̈ʒu�̏�����
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING - 1; nCntRanking++)
	{
		for (nCntScorePolygon = 0; nCntScorePolygon < MAX_SCORE_POLYGON; nCntScorePolygon++)
		{
			g_aRankingPolygon[nCntRanking][nCntScorePolygon].pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) - (RANKING_POLYGON_WIDTH * 1.5f) + (RANKING_POLYGON_WIDTH * nCntScorePolygon) ,200.0f + (SCREEN_HEIGHT / 8.0f * nCntRanking), 0.0f);
			g_aRankingPolygon[nCntRanking][nCntScorePolygon].bUse = true;
		}
		g_aScore[nCntRanking] = 0;
	}
	
	g_aScore[MAX_RANKING - 1] = GetScore();
	g_bData = false;
	g_bData2 = false;
	g_bCnt = false;
	g_nCol = 0;
	g_newRanking = 0;
	g_nCntFirst = 0;
	g_nData = GetScore();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//number.png",
		&g_pTextureRanking);



	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE_POLYGON * MAX_RANKING,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCntRanking = 0; nCntRanking < MAX_RANKING - 1; nCntRanking++)
	{
		for (int nCntScorePolygon = 0; nCntScorePolygon < MAX_SCORE_POLYGON; nCntScorePolygon++)
		{
			//���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aRankingPolygon[nCntRanking][nCntScorePolygon].pos.x - RANKING_POLYGON_WIDTH / 2.0f, g_aRankingPolygon[nCntRanking][nCntScorePolygon].pos.y - RANKING_POLYGON_HEIGHT / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aRankingPolygon[nCntRanking][nCntScorePolygon].pos.x + RANKING_POLYGON_WIDTH / 2.0f, g_aRankingPolygon[nCntRanking][nCntScorePolygon].pos.y - RANKING_POLYGON_HEIGHT / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aRankingPolygon[nCntRanking][nCntScorePolygon].pos.x - RANKING_POLYGON_WIDTH / 2.0f, g_aRankingPolygon[nCntRanking][nCntScorePolygon].pos.y + RANKING_POLYGON_HEIGHT / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aRankingPolygon[nCntRanking][nCntScorePolygon].pos.x + RANKING_POLYGON_WIDTH / 2.0f, g_aRankingPolygon[nCntRanking][nCntScorePolygon].pos.y + RANKING_POLYGON_HEIGHT / 2.0f, 0.0f);

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
	g_pVtxBuffRanking->Unlock();

	
	int nCntRanking;
	//���[�h����
	FILE *pFile;

	pFile = fopen("data/score.txt", "r");
	if (pFile != NULL)
	{
		for (nCntRanking = 0; nCntRanking < MAX_RANKING - 1; nCntRanking++)
		{
 			fscanf(pFile, "%d", &g_aScore[nCntRanking]);
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
void UninitRanking(void)
{
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING - 1; nCntRanking++)
	{
		for (int nCntScorePolygon = 0; nCntScorePolygon < MAX_SCORE_POLYGON; nCntScorePolygon++)
		{
			g_aRankingPolygon[nCntRanking][nCntScorePolygon].bUse = false;
		}
	}


	//�e�N�X�`���̔j��
	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateRanking(void)
{
	//�X�R�A�̎擾
	int nCntRanking;
	
	//=======================================================================
	//�\�[�g����
	//=======================================================================

	int nCnt, nCnt2, nSubData = 0;


	for (nCnt = 0; nCnt < MAX_RANKING -1; nCnt++)
	{
		for (nCnt2 = 0; nCnt2 < MAX_RANKING; nCnt2++)
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
	pFile = fopen("data/score.txt", "w");
	if (pFile != NULL)
	{
		for (nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			fprintf(pFile, "%d\n", g_aScore[nCntRanking]);
		}
		fclose(pFile);
	}
	else
	{
		printf("�t�@�C�����J���܂���ł���");
	}

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
							//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aScore[0] >= g_aScore[1] && g_aScore[1] >= g_aScore[2] &&
		g_aScore[2] >= g_aScore[3] && g_aScore[3] >= g_aScore[4])
	{
		g_bCnt = true;
	}


	for (nCntRanking = 0; nCntRanking < MAX_RANKING - 1; nCntRanking++)
	{
		for (int nCntScorePolygon = 0; nCntScorePolygon < MAX_SCORE_POLYGON; nCntScorePolygon++)
		{
			if (g_aRankingPolygon[nCntRanking][nCntScorePolygon].bUse == true)
			{
				if (nCntScorePolygon == 0)
				{
					pVtx[0].tex = D3DXVECTOR2(g_aScore[nCntRanking] / (int)powf(10, MAX_RANKING_POLYGON - 1)*0.1f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(g_aScore[nCntRanking] / (int)powf(10, MAX_RANKING_POLYGON - 1)*0.1f + 0.1f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(g_aScore[nCntRanking] / (int)powf(10, MAX_RANKING_POLYGON - 1)*0.1f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(g_aScore[nCntRanking] / (int)powf(10, MAX_RANKING_POLYGON - 1)*0.1f + 0.1f, 1.0f);
				}
				else if (nCntScorePolygon == MAX_RANKING_POLYGON - 1)
				{
					pVtx[0].tex = D3DXVECTOR2(g_aScore[nCntRanking] % 10 * 0.1f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(g_aScore[nCntRanking] % 10 * 0.1f + 0.1f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(g_aScore[nCntRanking] % 10 * 0.1f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(g_aScore[nCntRanking] % 10 * 0.1f + 0.1f, 1.0f);
				}
				else
				{
					pVtx[0].tex = D3DXVECTOR2(g_aScore[nCntRanking] % (int)powf(10, MAX_SCORE_POLYGON - nCntScorePolygon) / (int)powf(10, MAX_RANKING_POLYGON - 1 - nCntScorePolygon) *0.1f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(g_aScore[nCntRanking] % (int)powf(10, MAX_SCORE_POLYGON - nCntScorePolygon) / (int)powf(10, MAX_RANKING_POLYGON - 1 - nCntScorePolygon)*0.1f + 0.1f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(g_aScore[nCntRanking] % (int)powf(10, MAX_SCORE_POLYGON - nCntScorePolygon) / (int)powf(10, MAX_RANKING_POLYGON - 1 - nCntScorePolygon)*0.1f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(g_aScore[nCntRanking] % (int)powf(10, MAX_SCORE_POLYGON - nCntScorePolygon) / (int)powf(10, MAX_RANKING_POLYGON - 1 - nCntScorePolygon)*0.1f + 0.1f, 1.0f);
				}
			}

			if (g_bCnt == true)
			{
				if (g_aScore[nCntRanking] == g_nData && g_bData2 == false)
				{
					g_bData2 = true;
					g_newRanking = nCntRanking;
				}

				g_nCol++;
				if (g_nCol >= 600)
				{
					if (g_nData >= g_aScore[4] && g_nData != 0)
					{
						if (g_aRankingPolygon[g_newRanking][nCntScorePolygon].bUse == false)
						{
							for (int nCnt3 = 0; nCnt3 < MAX_SCORE_POLYGON; nCnt3++)
							{
								g_aRankingPolygon[g_newRanking][nCnt3].bUse = true;
							}
						}
						else if (g_aRankingPolygon[g_newRanking][nCntScorePolygon].bUse == true)
						{
							for (int nCnt3 = 0; nCnt3 < MAX_SCORE_POLYGON; nCnt3++)
							{
								g_aRankingPolygon[g_newRanking][nCnt3].bUse = false;
							}
						}
					}
					
					g_nCol = 0;
				}
			}

			pVtx += 4;
		}
	}


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRanking->Unlock();



}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawRanking(void)
{
	int nCntRanking;

	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����
												//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//���_�t�H�[�}�b�g�̐ݒ�

	int nCnt=0;
	
	for (nCntRanking = 0; nCntRanking < MAX_RANKING - 1; nCntRanking++)
	{
		for (int nCntScorePolygon = 0; nCntScorePolygon < MAX_SCORE_POLYGON; nCntScorePolygon++)
		{
			if (g_aRankingPolygon[nCntRanking][nCntScorePolygon].bUse == true)
			{
				//�e�N�X�`��
				pDevice->SetTexture(0, g_pTextureRanking);

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
void SetRanking(int nRanking)
{
	//g_aRanking[0][0] += nRanking;
}

