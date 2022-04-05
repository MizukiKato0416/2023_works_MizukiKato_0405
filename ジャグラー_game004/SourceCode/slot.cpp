//=======================================================================
//�X���b�g�����Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================
#include "main.h"
#include "slot.h"
#include "input.h"
#include "score.h"
#include "databox.h"
#include "sound.h"


//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================

LPDIRECT3DTEXTURE9 g_pTextureSlot = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSlot = NULL;		//���_�o�b�t�@�ւ̃|�C���^
SLOT g_aSlot[MAX_SLOT];								//�\����
float g_fAcceleration;								//�����x
int g_nNumStopSlot;									//�X�g�b�v�������X���b�g�̐�
int g_nSlotCounter;									//�X���b�g�����������
int g_nScoreCounter;								//�X�R�A�𑝂₵�Ă��鎞��
bool g_bAcceleration;								//�������Ă����Ԃ������łȂ���
bool g_bScoreUp;									//�X�R�A���オ��
bool g_bScoreUpStop;								//�X�R�A�������邽�߂ɕK�v
bool g_bSpin;										//����Ă��邩�ǂ���

//=======================================================================
//����������
//=======================================================================
void InitSlot(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//������
	g_aSlot[0].firstmove = D3DXVECTOR3(SLOT_SPEED0, 0.0f, 0.0f);
	g_aSlot[1].firstmove = D3DXVECTOR3(SLOT_SPEED1, 0.0f, 0.0f);
	g_aSlot[2].firstmove = D3DXVECTOR3(SLOT_SPEED2, 0.0f, 0.0f);
	g_aSlot[3].firstmove = D3DXVECTOR3(SLOT_SPEED3, 0.0f, 0.0f);
	g_nNumStopSlot = 4;
	g_nScoreCounter = 0;
	g_nSlotCounter = 0;
	g_bAcceleration = false;
	g_bScoreUp = false;
	g_bScoreUpStop = false;
	g_bSpin = false;
	g_fAcceleration = SLOT_ACCEL;

	for (int nCntSlot = 0; nCntSlot < MAX_SLOT; nCntSlot++)
	{
		g_aSlot[nCntSlot].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSlot[nCntSlot].move = g_aSlot[nCntSlot].firstmove;
		g_aSlot[nCntSlot].fWidth = 0.0f;
		g_aSlot[nCntSlot].fHeight = 0.0f;
		g_aSlot[nCntSlot].fTexU = 0.0f;
		g_aSlot[nCntSlot].fStopTexU = 0.0f;
		g_aSlot[nCntSlot].bUse = false;
		g_aSlot[nCntSlot].bSpin = true;
		g_aSlot[nCntSlot].bStop = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//Round2.png",
		&g_pTextureSlot);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SLOT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSlot,
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffSlot->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntSlot = 0; nCntSlot < MAX_SLOT; nCntSlot++)
	{
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f / MAX_SLOT * nCntSlot);
		pVtx[1].tex = D3DXVECTOR2(1.0f / MAX_SLOT, 1.0f / MAX_SLOT * nCntSlot);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f / MAX_SLOT * (nCntSlot + 1));
		pVtx[3].tex = D3DXVECTOR2(1.0f / MAX_SLOT, 1.0f / MAX_SLOT * (nCntSlot + 1));

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSlot->Unlock();
}


//=======================================================================
//�I������
//=======================================================================
void UninitSlot(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureSlot != NULL)
	{
		g_pTextureSlot->Release();
		g_pTextureSlot = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSlot != NULL)
	{
		g_pVtxBuffSlot->Release();
		g_pVtxBuffSlot = NULL;
	}
}


//=======================================================================
//�X�V����
//=======================================================================
void UpdateSlot(void)
{
	Data *pData;
	pData = GetData();
	for (int nCntSlot = 0; nCntSlot < MAX_SLOT; nCntSlot++)
	{
		if (g_aSlot[nCntSlot].bUse == true)
		{
			if (g_bSpin == true)
			{
				g_aSlot[nCntSlot].fTexU += g_aSlot[nCntSlot].move.x;
			}

			if (g_bAcceleration == true)
			{
				g_aSlot[nCntSlot].move.x *= 0.95f;
				if (g_aSlot[nCntSlot].move.x > 0.0f && g_aSlot[nCntSlot].move.x <= g_aSlot[nCntSlot].firstmove.x)
				{
					g_aSlot[nCntSlot].move.x = g_aSlot[nCntSlot].firstmove.x;
				}
				else if (g_aSlot[nCntSlot].move.x < 0.0f && g_aSlot[nCntSlot].move.x >= g_aSlot[nCntSlot].firstmove.x)
				{
					g_aSlot[nCntSlot].move.x = g_aSlot[nCntSlot].firstmove.x;
				}
			}

			if (g_aSlot[nCntSlot].move.x == g_aSlot[nCntSlot].firstmove.x)
			{
				g_bAcceleration = false;
			}


			VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
			//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
			g_pVtxBuffSlot->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (nCntSlot * 4);

			pVtx[0].tex = D3DXVECTOR2(g_aSlot[nCntSlot].fTexU, 1.0f / MAX_SLOT * nCntSlot);
			pVtx[1].tex = D3DXVECTOR2(g_aSlot[nCntSlot].fTexU + 1.0f / MAX_SLOT, 1.0f / MAX_SLOT * nCntSlot);
			pVtx[2].tex = D3DXVECTOR2(g_aSlot[nCntSlot].fTexU, 1.0f / MAX_SLOT * (nCntSlot + 1));
			pVtx[3].tex = D3DXVECTOR2(g_aSlot[nCntSlot].fTexU + 1.0f / MAX_SLOT, 1.0f / MAX_SLOT * (nCntSlot + 1));

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffSlot->Unlock();
		}
	}

	//�X���b�g���~�߂�
	if (g_nNumStopSlot < MAX_SLOT)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetKeyboardTrigger(DIK_SPACE) == true)
		{
			//PlaySound(SOUND_LABEL_ENTER_SE);


			if (g_aSlot[g_nNumStopSlot].move.x > 0.0f)
			{
				if (g_aSlot[g_nNumStopSlot].fTexU > 0.0f && g_aSlot[g_nNumStopSlot].fTexU <= 0.25f)
				{
					g_aSlot[g_nNumStopSlot].fStopTexU = 0.25f;
				}
				else if (g_aSlot[g_nNumStopSlot].fTexU > 0.25f && g_aSlot[g_nNumStopSlot].fTexU <= 0.5f)
				{
					g_aSlot[g_nNumStopSlot].fStopTexU = 0.5f;
				}
				else if (g_aSlot[g_nNumStopSlot].fTexU > 0.5f && g_aSlot[g_nNumStopSlot].fTexU <= 0.75f)
				{
					g_aSlot[g_nNumStopSlot].fStopTexU = 0.75f;
				}
				else if (g_aSlot[g_nNumStopSlot].fTexU > 0.75f && g_aSlot[g_nNumStopSlot].fTexU <= 1.0f)
				{
					g_aSlot[g_nNumStopSlot].fStopTexU = 1.0f;
				}
			}
			else if (g_aSlot[g_nNumStopSlot].move.x < 0.0f)
			{
				if (g_aSlot[g_nNumStopSlot].fTexU >= 0.0f && g_aSlot[g_nNumStopSlot].fTexU < 0.25f)
				{
					g_aSlot[g_nNumStopSlot].fStopTexU = 0.0f;
				}
				else if (g_aSlot[g_nNumStopSlot].fTexU >= 0.25f && g_aSlot[g_nNumStopSlot].fTexU < 0.5f)
				{
					g_aSlot[g_nNumStopSlot].fStopTexU = 0.25f;
				}
				else if (g_aSlot[g_nNumStopSlot].fTexU >= 0.5f && g_aSlot[g_nNumStopSlot].fTexU < 0.75f)
				{
					g_aSlot[g_nNumStopSlot].fStopTexU = 0.5f;
				}
				else if (g_aSlot[g_nNumStopSlot].fTexU >= 0.75f && g_aSlot[g_nNumStopSlot].fTexU < 1.0f)
				{
					g_aSlot[g_nNumStopSlot].fStopTexU = 0.75f;
				}
			}
			
			g_aSlot[g_nNumStopSlot].bStop = true;

			g_nNumStopSlot++;
			
		}
	}

	for (int nCntSlot = 0; nCntSlot < MAX_SLOT; nCntSlot++)
	{
		if (g_aSlot[nCntSlot].bStop == true)
		{
			if (g_aSlot[nCntSlot].move.x > 0.0f && g_aSlot[nCntSlot].fTexU >= g_aSlot[nCntSlot].fStopTexU)
			{
				g_aSlot[nCntSlot].fTexU = g_aSlot[nCntSlot].fStopTexU;
				if(g_aSlot[nCntSlot].fTexU == 1.0f)
				{
					g_aSlot[nCntSlot].fTexU = 0.0f;
				}
				g_aSlot[nCntSlot].move.x = 0.0f;
				g_aSlot[nCntSlot].bStop = false;
			}
			else if (g_aSlot[nCntSlot].move.x < 0.0f && g_aSlot[nCntSlot].fTexU <= g_aSlot[nCntSlot].fStopTexU)
			{
				g_aSlot[nCntSlot].fTexU = g_aSlot[nCntSlot].fStopTexU;
				g_aSlot[nCntSlot].move.x = 0.0f;
				g_aSlot[nCntSlot].bStop = false;
			}
		}
	}

	//��������
	if (g_nNumStopSlot >= MAX_SLOT && g_aSlot[0].bStop == false && g_aSlot[1].bStop == false && g_aSlot[2].bStop == false && g_aSlot[3].bStop == false)
	{
		StopSound(SOUND_LABEL_DRUM_SE);
		g_bSpin = false;
		if (g_aSlot[0].fTexU == g_aSlot[1].fTexU && g_aSlot[1].fTexU == g_aSlot[2].fTexU &&g_aSlot[2].fTexU == g_aSlot[3].fTexU && g_bScoreUp == true)
		{
			g_bScoreUpStop = true;
		}
	}

	if (g_bScoreUpStop == true)
	{
		g_nScoreCounter++;
		SetScore(10);
		if (g_nScoreCounter >= 100)
		{
			g_nScoreCounter = 0;
			g_bScoreUp = false;
			g_bScoreUpStop = false;

			pData->bOK = true;
		}
	}

	for (int nCntSlot = 0; nCntSlot < MAX_SLOT; nCntSlot++)
	{
		if (g_aSlot[nCntSlot].move.x > 0.0f && g_aSlot[nCntSlot].fTexU >= 1.0f)
		{
			g_aSlot[nCntSlot].fTexU = 0.0f;
		}
		else if (g_aSlot[nCntSlot].move.x < 0.0f && g_aSlot[nCntSlot].fTexU <= 0.0f)
		{
			g_aSlot[nCntSlot].fTexU = 1.0f;
		}
	}


	//�X���b�g����
	if (g_nNumStopSlot >= MAX_SLOT && g_aSlot[0].bStop == false && g_aSlot[1].bStop == false && g_aSlot[2].bStop == false && g_aSlot[3].bStop == false)
	{
		if (g_aSlot[0].fTexU == g_aSlot[1].fTexU && g_aSlot[1].fTexU == g_aSlot[2].fTexU &&g_aSlot[2].fTexU == g_aSlot[3].fTexU && g_bScoreUpStop == false)
		{
			if (GetKeyboardTrigger(DIK_SPACE) == true || GetKeyboardTrigger(DIK_RETURN) == true)
			{
				PlaySound(SOUND_LABEL_SPACE_SE);
				PlaySound(SOUND_LABEL_ROLL_SE);
				if (g_aSlot[0].fTexU == g_aSlot[1].fTexU && g_aSlot[1].fTexU == g_aSlot[2].fTexU &&g_aSlot[2].fTexU == g_aSlot[3].fTexU)
				{
					g_aSlot[0].firstmove.x *= g_fAcceleration;
					g_aSlot[1].firstmove.x *= g_fAcceleration;
					g_aSlot[2].firstmove.x *= g_fAcceleration;
					g_aSlot[3].firstmove.x *= g_fAcceleration;
				}
				g_nNumStopSlot = 0;
				g_aSlot[0].move.x = g_aSlot[0].firstmove.x * 20.0f;
				g_aSlot[1].move.x = g_aSlot[1].firstmove.x * 20.0f;
				g_aSlot[2].move.x = g_aSlot[2].firstmove.x * 20.0f;
				g_aSlot[3].move.x = g_aSlot[3].firstmove.x * 20.0f;
				g_bAcceleration = true;
				//g_bScoreUpStop = false;
				g_bSpin = true;
				g_bScoreUp = true;
			}
		}
		else if(g_aSlot[0].fTexU != g_aSlot[1].fTexU || g_aSlot[1].fTexU != g_aSlot[2].fTexU || g_aSlot[2].fTexU != g_aSlot[3].fTexU)
		{
			if (GetKeyboardTrigger(DIK_SPACE) == true || GetKeyboardTrigger(DIK_RETURN) == true)
			{
				PlaySound(SOUND_LABEL_SPACE_SE);
				PlaySound(SOUND_LABEL_ROLL_SE);


				if (g_aSlot[0].fTexU == g_aSlot[1].fTexU && g_aSlot[1].fTexU == g_aSlot[2].fTexU &&g_aSlot[2].fTexU == g_aSlot[3].fTexU)
				{
					g_aSlot[0].firstmove.x *= g_fAcceleration;
					g_aSlot[1].firstmove.x *= g_fAcceleration;
					g_aSlot[2].firstmove.x *= g_fAcceleration;
					g_aSlot[3].firstmove.x *= g_fAcceleration;
				}
				g_nNumStopSlot = 0;
				g_aSlot[0].move.x = g_aSlot[0].firstmove.x * 20.0f;
				g_aSlot[1].move.x = g_aSlot[1].firstmove.x * 20.0f;
				g_aSlot[2].move.x = g_aSlot[2].firstmove.x * 20.0f;
				g_aSlot[3].move.x = g_aSlot[3].firstmove.x * 20.0f;
				g_bAcceleration = true;
				//g_bScoreUpStop = false;
				g_bSpin = true;
				g_bScoreUp = true;
			}
		}
		
	}
}


//=======================================================================
//�`�揈��
//=======================================================================
void DrawSlot(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����
												//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSlot, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//���_�t�H�[�}�b�g�̐ݒ�

	for (int nCntSlot = 0; nCntSlot < MAX_SLOT; nCntSlot++)
	{
		if (g_aSlot[nCntSlot].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureSlot);	//�e�N�X�`���̐ݒ�
													//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				nCntSlot * 4,					//�J�n���钸�_�̃C���f�b�N�X
				2);					//�`�悷��v���~�e�B�u��
		}
	}
}

//=======================================================================
//�ݒ菈��
//=======================================================================
void SetSlot(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	for (int nCntSlot = 0; nCntSlot < MAX_SLOT; nCntSlot++)
	{
		if (g_aSlot[nCntSlot].bUse == false)
		{
			g_aSlot[nCntSlot].pos = pos;
			g_aSlot[nCntSlot].fWidth = fWidth;
			g_aSlot[nCntSlot].fHeight = fHeight;
			g_aSlot[nCntSlot].bUse = true;

			//���_���W�̐ݒ�

			VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
									//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
			g_pVtxBuffSlot->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += (nCntSlot * 4);

			pVtx[0].pos = D3DXVECTOR3(g_aSlot[nCntSlot].pos.x - g_aSlot[nCntSlot].fWidth / 2.0f, g_aSlot[nCntSlot].pos.y - g_aSlot[nCntSlot].fHeight / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aSlot[nCntSlot].pos.x + g_aSlot[nCntSlot].fWidth / 2.0f, g_aSlot[nCntSlot].pos.y - g_aSlot[nCntSlot].fHeight / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aSlot[nCntSlot].pos.x - g_aSlot[nCntSlot].fWidth / 2.0f, g_aSlot[nCntSlot].pos.y + g_aSlot[nCntSlot].fHeight / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aSlot[nCntSlot].pos.x + g_aSlot[nCntSlot].fWidth / 2.0f, g_aSlot[nCntSlot].pos.y + g_aSlot[nCntSlot].fHeight / 2.0f, 0.0f);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffSlot->Unlock();

			break;
		}
	}
}

//=======================================================================
//�擾����
//=======================================================================
SLOT *GetSlot(void)
{
	return &g_aSlot[0];
}