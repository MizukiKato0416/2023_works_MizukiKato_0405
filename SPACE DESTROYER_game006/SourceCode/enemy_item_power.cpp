//================================================
//�p���[�A�b�v�̃A�C�e���𗎂Ƃ��G�̏���
//Authore:��������
//================================================
#include "scene2D.h"
#include "scene.h"
#include "manager.h"
#include "enemy_item_power.h"
#include "renderer.h"
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
CEnemyItemPower::CEnemyItemPower()
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
CEnemyItemPower::~CEnemyItemPower()
{

}

//================================================
//����������
//================================================
HRESULT CEnemyItemPower::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move)
{
	m_pos = pos;
	m_size = size;
	m_move = move;
	m_type = ENEMY_TYPE_ITEM_POWER;
	m_nLife = ENEMY_ITEM_POWER_LIFE;

	CEnemy::Init(pos, size, move);

	return S_OK;
}

//================================================
//�I������
//================================================
void CEnemyItemPower::Uninit(void)
{
	CEnemy::Uninit();
}

//================================================
//�X�V����
//================================================
void CEnemyItemPower::Update(void)
{
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

	//�ʒu���f
	CScene2D::SetPos(m_pos, m_size);

	//�G�̍X�V����
	CEnemy::Update();
}

//================================================
//�`�揈��
//================================================
void CEnemyItemPower::Draw(void)
{
	CEnemy::Draw();
}

//================================================
//��������
//================================================
CEnemyItemPower *CEnemyItemPower::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, CMover::MOVER_TYPE moverType)
{
	//�C���X�^���X�̐���
	CEnemyItemPower *pEnemyItemPower = NULL;
	if (pEnemyItemPower == NULL)
	{
		pEnemyItemPower = new CEnemyItemPower;
		if (pEnemyItemPower != NULL)
		{
			//�ϐ��ɑ��
			pEnemyItemPower->m_moverType = moverType;
			//���[�u�N���X�𐶐�
			switch (moverType)
			{
			case CMover::MOVER_TYPE_FALL_STOP_RISE:
				pEnemyItemPower->m_pMover = CMoverFallStopRise::Create();
				break;
			case CMover::MOVER_TYPE_RIGHT_STOP_LEFT:
				pEnemyItemPower->m_pMover = CMoverRightStopLeft::Create();
				break;
			case CMover::MOVER_TYPE_LEFT_STOP_RIGHT:
				pEnemyItemPower->m_pMover = CMoverLeftStopRight::Create();
				break;
			case CMover::MOVER_TYPE_FALL_LOWER_LEFT:
				pEnemyItemPower->m_pMover = CMoverFallLowerLeft::Create();
				break;
			case CMover::MOVER_TYPE_FALL_LOWER_RIGHT:
				pEnemyItemPower->m_pMover = CMoverFallLowerRight::Create();
				break;
			case CMover::MOVER_TYPE_FALL_RANDOM_RIGHT_LEFT:
				pEnemyItemPower->m_pMover = CMoverFallRandomRightLeft::Create();
				break;
			case CMover::MOVER_TYPE_RIGHT_STOP:
				pEnemyItemPower->m_pMover = CMoverRightStop::Create();
				break;
			case CMover::MOVER_TYPE_LEFT_STOP:
				pEnemyItemPower->m_pMover = CMoverLeftStop::Create();
				break;
			default:
				break;
			}
			//����������
			pEnemyItemPower->Init(pos, size, move);
			//�e�N�X�`�����擾
			m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_ENEMY_ITEM_POWER);
			//�e�N�X�`����ݒ�
			pEnemyItemPower->BindTexture(m_pTexture);
		}
	}
	return pEnemyItemPower;
}

//================================================
//�ړ��ʊǗ�����
//================================================
void CEnemyItemPower::MoveType(void)
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