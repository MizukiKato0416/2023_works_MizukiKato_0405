//=======================================================================
//���U���g�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "result.h"
#include "sound.h"
#include "input.h"
#include "score.h"
#include "HiScore.h"
#include "fade.h"


//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;		//���_�o�b�t�@�ւ̃|�C���^
int g_nCnt;

//=======================================================================
//����������
//=======================================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	g_nCnt = 0;			//������


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//result.png",
		&g_pTextureResult);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);


	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);


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

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();
	PlaySound(SOUND_LABEL_BGM003);

	InitScore();
	InitHiScore();

}

//=======================================================================
//�I������
//=======================================================================
void UninitResult(void)
{
	StopSound(SOUND_LABEL_BGM003);
	//�e�N�X�`���̔j��
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}


	UninitScore();
	UninitHiScore();
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateResult(void)
{
	g_nCnt++;
	//�X�y�[�X�L�[���������Ƃ��̏���
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		PlaySound(SOUND_LABEL_START001);
		SetFade(MODE_TITLE);
	}
	
	else if (g_nCnt == 10000)
	{
		g_nCnt = 0;
		SetFade(MODE_TITLE);
	}


	

	UpdateScore();
	UpdateHiScore();

}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����
												//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTextureResult);	//�e�N�X�`���̐ݒ�
												//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,					//�J�n���钸�_�̃C���f�b�N�X
		2);					//�`�悷��v���~�e�B�u��

	DrawScore();
	DrawHiScore();
}