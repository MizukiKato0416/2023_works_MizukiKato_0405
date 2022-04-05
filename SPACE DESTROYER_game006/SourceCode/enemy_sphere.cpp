//================================================
//���̌^�G�̏���
//Authore:��������
//================================================
#include "scene2D.h"
#include "scene.h"
#include "manager.h"
#include "enemy_sphere.h"
#include "enemy.h"
#include "renderer.h"
#include "sound.h"
#include "texture.h"
#include "mover_fall_stop_rise.h"
#include "mover_right_stop_left.h"
#include "mover_left_stop_right.h"
#include "mover_fall_lower_left.h"
#include "mover_fall_lower_right.h"
#include "mover_fall_random_right_left.h"
#include "mover_right_stop.h"
#include "mover_left_stop.h"

#ifndef _DEBUG
//#define NDEBUG
#endif // !_DEBUG
#include <assert.h>

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CEnemySphere::CEnemySphere()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CEnemySphere::~CEnemySphere()
{

}

//================================================
//����������
//================================================
HRESULT CEnemySphere::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move)
{
	m_pos = pos;
	m_size = size;
	m_move = move;
	m_type = ENEMY_TYPE_SPHERE;
	m_nLife = ENEMY_SPHERE_LIFE;

	CEnemy::Init(pos, size, move);

	return S_OK;
}

//================================================
//�I������
//================================================
void CEnemySphere::Uninit(void)
{
	CEnemy::Uninit();
}

//================================================
//�X�V����
//================================================
void CEnemySphere::Update(void)
{
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	//�ʒu�擾
	m_pos = GetPos();

	m_pos += m_move;		//�ړ��ʔ��f

	//��ʊO�ɏo����
	if (m_pos.x + m_size.x / 2.0f < 0.0f || m_pos.x - m_size.x / 2.0f > SCREEN_WIDTH ||
		m_pos.y + m_size.y / 2.0f < 0.0f || m_pos.y - m_size.y / 2.0f > SCREEN_HEIGHT)
	{
		Uninit();
		return;
	}

	//�ړ��̐ݒ�
	MoveType();

	//�ʒu���f
	CScene2D::SetPos(m_pos, m_size);

	//�G�̍X�V����
	CEnemy::Update();
}

//================================================
//�`�揈��
//================================================
void CEnemySphere::Draw(void)
{
	CEnemy::Draw();
}

//================================================
//��������
//================================================
CEnemySphere *CEnemySphere::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, CMover::MOVER_TYPE moverType)
{
	//�C���X�^���X�̐���
	CEnemySphere *pEnemySphere = NULL;
	if (pEnemySphere == NULL)
	{
		pEnemySphere = new CEnemySphere;
		if (pEnemySphere != NULL)
		{
			//�ϐ��ɑ��
			pEnemySphere->m_moverType = moverType;
			//���[�u�N���X�𐶐�
			switch (moverType)
			{
			case CMover::MOVER_TYPE_FALL_STOP_RISE:
				pEnemySphere->m_pMover = CMoverFallStopRise::Create();
				break;
			case CMover::MOVER_TYPE_RIGHT_STOP_LEFT:
				pEnemySphere->m_pMover = CMoverRightStopLeft::Create();
				break;
			case CMover::MOVER_TYPE_LEFT_STOP_RIGHT:
				pEnemySphere->m_pMover = CMoverLeftStopRight::Create();
				break;
			case CMover::MOVER_TYPE_FALL_LOWER_LEFT:
				pEnemySphere->m_pMover = CMoverFallLowerLeft::Create();
				break;
			case CMover::MOVER_TYPE_FALL_LOWER_RIGHT:
				pEnemySphere->m_pMover = CMoverFallLowerRight::Create();
				break;
			case CMover::MOVER_TYPE_FALL_RANDOM_RIGHT_LEFT:
				pEnemySphere->m_pMover = CMoverFallRandomRightLeft::Create();
				break;
			case CMover::MOVER_TYPE_RIGHT_STOP:
				pEnemySphere->m_pMover = CMoverRightStop::Create();
				break;
			case CMover::MOVER_TYPE_LEFT_STOP:
				pEnemySphere->m_pMover = CMoverLeftStop::Create();
				break;
			default:
				break;
			}
			//����������
			pEnemySphere->Init(pos, size, move);
			//�e�N�X�`�����擾
			m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_ENEMY_SPHERE);
			//�e�N�X�`����ݒ�
			pEnemySphere->BindTexture(m_pTexture);
		}
	}
	return pEnemySphere;
}

//================================================
//�ړ��ʊǗ�����
//================================================
void CEnemySphere::MoveType(void)
{
	if (m_moverType != CMover::MOVER_TYPE_NONE)
	{
		//���[�u�N���X�̃A�b�v�f�[�g���Ăяo��
		m_pMover->Update();

		//�ړ��ʂ��擾
		D3DXVECTOR3 move = m_pMover->GetMove();
		m_move = move;
	}
}