//=======================================================================
//���[����ʂɊւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "rule2.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "word.h"


//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================

LPDIRECT3DTEXTURE9 g_pTextureRule2 = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRule2 = NULL;		//���_�o�b�t�@�ւ̃|�C���^

//=======================================================================
//����������
//=======================================================================
void InitRule2(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//rule.png",
		&g_pTextureRule2);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRule2,
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffRule2->Lock(0, 0, (void**)&pVtx, 0);


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
	g_pVtxBuffRule2->Unlock();

	InitWord();
	SetWord(D3DXVECTOR3(SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT - 150.0f, 0.0f), 1, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 700.0f, 150.0f);
	SetWord(D3DXVECTOR3(SCREEN_WIDTH / 8.0f * 7.0f, 650.0f, 0.0f), 4, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 300.0f, 50.0f);
}


//=======================================================================
//�I������
//=======================================================================
void UninitRule2(void)
{
	UninitWord();
	//�e�N�X�`���̔j��
	if (g_pTextureRule2 != NULL)
	{
		g_pTextureRule2->Release();
		g_pTextureRule2 = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRule2 != NULL)
	{
		g_pVtxBuffRule2->Release();
		g_pVtxBuffRule2 = NULL;
	}
}


//=======================================================================
//�X�V����
//=======================================================================
void UpdateRule2(void)
{
	//�X�y�[�X�L�[���������Ƃ��̏���
	if (GetMode() == MODE_RULE2)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			PlaySound(SOUND_LABEL_DECIDE);
			SetFade(MODE_TUTORIAL);
		}
	}

	UpdateWord();
}


//=======================================================================
//�`�揈��
//=======================================================================
void DrawRule2(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����
												//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRule2, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTextureRule2);	//�e�N�X�`���̐ݒ�
											//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,					//�J�n���钸�_�̃C���f�b�N�X
		2);					//�`�悷��v���~�e�B�u��

	DrawWord();
}