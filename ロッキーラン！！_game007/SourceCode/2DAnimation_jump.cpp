//=============================================================================
// �W�����v��2D�A�j���[�V�������� [2Danimation_jump.cpp]
// Author : KUSAKARI KAKERU
//=============================================================================
#include "2Danimation_jump.h"
#include "billboard.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "player.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
C2DAnimationJump::C2DAnimationJump()
{
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_nLife = 0;
	m_fMaxSpeed = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
C2DAnimationJump::~C2DAnimationJump()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT C2DAnimationJump::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_nLife = 24;

	CBillboard::Init(pos, size);

	SetTex(m_nPatternAnim, 4);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void C2DAnimationJump::Uninit(void)
{
	CBillboard::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void C2DAnimationJump::Update(void)
{
	// �����ɍ��킹�đO�i
	m_move.z += -cosf(m_rot.y) * 0.2f;
	m_move.x += -sinf(m_rot.y) * 0.2f;

	// �ړ��ʂ��ő�ړ��ʂ𒴂��Ȃ��悤�ɂ���
	if (m_move.x <= -sinf(m_rot.y) *  m_fMaxSpeed)
	{
		m_move.x = -sinf(m_rot.y) *  m_fMaxSpeed;
	}

	if (m_move.x >= -sinf(m_rot.y) *  m_fMaxSpeed)
	{
		m_move.x = -sinf(m_rot.y) *  m_fMaxSpeed;
	}

	if (m_move.z <= -cosf(m_rot.y) * m_fMaxSpeed)
	{
		m_move.z = -cosf(m_rot.y) * m_fMaxSpeed;
	}

	if (m_move.z >= -cosf(m_rot.y) * m_fMaxSpeed)
	{
		m_move.z = -cosf(m_rot.y) * m_fMaxSpeed;
	}

	// �p�����N���X�̍X�V����
	CBillboard::Update();

	// �A�j���[�V�����J�E���^�[�̍X�V
	m_nCounterAnim++;

	if (m_nCounterAnim % 6 == 0)
	{
		// �A�j���[�V�����p�^�[���̍X�V
		m_nPatternAnim++;

		if (m_nPatternAnim >= 4)
		{
			m_nPatternAnim = 3;
		}

		// �e�N�X�`�����W�̍X�V
		SetTex(m_nPatternAnim, 4);
	}

	// ���������炷
	m_nLife--;

	// ���������炵�������
	if (m_nLife <= 0)
	{
		Uninit();
	}
}

//================================================
//�`�揈��
//================================================
void C2DAnimationJump::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		//�A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	//�A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHAREF, 240);				//�A���t�@�l�̎Q�ƒl

	D3DXMATRIX mtxView;						//�r���[�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;	//�v�Z�p�}�g���b�N�X
	D3DXMatrixIdentity(&m_mtxWorld);		//���[���h�}�g���b�N�X�̏�����

											//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);


	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetFVF(FVF_VERTEX_3D);					//���_�t�H�[�}�b�g�̐ݒ�

	pDevice->SetTexture(0, m_pTexture);				//�e�N�X�`���̐ݒ�

													//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,											//�J�n���钸�_�̃C���f�b�N�X
		2);											//�`�悷��v���~�e�B�u��

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		//�A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);	//�A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);				//�A���t�@�l�̎Q�ƒl

																//���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//================================================
//��������
//================================================
C2DAnimationJump *C2DAnimationJump::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, float fMaxSpeed)
{
	//�C���X�^���X�̐���
	C2DAnimationJump *p2DAnimationJump = NULL;
	if (p2DAnimationJump == NULL)
	{
		p2DAnimationJump = new C2DAnimationJump;
		if (p2DAnimationJump != NULL)
		{
			p2DAnimationJump->Init(pos, size);
			p2DAnimationJump->m_rot = rot;
			p2DAnimationJump->m_fMaxSpeed = fMaxSpeed;
			p2DAnimationJump->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_JUMP_SMOKE);
		}
	}
	return p2DAnimationJump;
}