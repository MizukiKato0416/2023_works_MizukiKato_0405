//================================================
//�GUFO�̏���
//Authore:��������
//================================================
#include "scene2D.h"
#include "scene.h"
#include "manager.h"
#include "enemy_ufo.h"
#include "enemy.h"
#include "renderer.h"
#include "sound.h"
#include "texture.h"
#include "bullet_enemy.h"
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
CEnemyUfo::CEnemyUfo()
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
CEnemyUfo::~CEnemyUfo()
{

}

//================================================
//����������
//================================================
HRESULT CEnemyUfo::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move)
{
	m_pos = pos;
	m_size = size;
	m_move = move;
	m_type = ENEMY_TYPE_UFO;
	m_nLife = ENEMY_UFO_LIFE;

	CEnemy::Init(pos, size, move);

	return S_OK;
}

//================================================
//�I������
//================================================
void CEnemyUfo::Uninit(void)
{
	CEnemy::Uninit();
}

//================================================
//�X�V����
//================================================
void CEnemyUfo::Update(void)
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
	//�ˌ�����
	ShootBullet();

	//�ʒu���f
	CScene2D::SetPos(m_pos, m_size);

	//�G�̍X�V����
	CEnemy::Update();
}

//================================================
//�`�揈��
//================================================
void CEnemyUfo::Draw(void)
{
	CEnemy::Draw();
}

//================================================
//��������
//================================================
CEnemyUfo *CEnemyUfo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, CMover::MOVER_TYPE moverType)
{
	//�C���X�^���X�̐���
	CEnemyUfo *pEnemyUfo = NULL;
	if (pEnemyUfo == NULL)
	{
		pEnemyUfo = new CEnemyUfo;
		if (pEnemyUfo != NULL)
		{
			//�ϐ��ɑ��
			pEnemyUfo->m_moverType = moverType;
			//���[�u�N���X�𐶐�
			switch (moverType)
			{
			case CMover::MOVER_TYPE_FALL_STOP_RISE:
				pEnemyUfo->m_pMover = CMoverFallStopRise::Create();
				break;
			case CMover::MOVER_TYPE_RIGHT_STOP_LEFT:
				pEnemyUfo->m_pMover = CMoverRightStopLeft::Create();
				break;
			case CMover::MOVER_TYPE_LEFT_STOP_RIGHT:
				pEnemyUfo->m_pMover = CMoverLeftStopRight::Create();
				break;
			case CMover::MOVER_TYPE_FALL_LOWER_LEFT:
				pEnemyUfo->m_pMover = CMoverFallLowerLeft::Create();
				break;
			case CMover::MOVER_TYPE_FALL_LOWER_RIGHT:
				pEnemyUfo->m_pMover = CMoverFallLowerRight::Create();
				break;
			case CMover::MOVER_TYPE_FALL_RANDOM_RIGHT_LEFT:
				pEnemyUfo->m_pMover = CMoverFallRandomRightLeft::Create();
				break;
			case CMover::MOVER_TYPE_RIGHT_STOP:
				pEnemyUfo->m_pMover = CMoverRightStop::Create();
				break;
			case CMover::MOVER_TYPE_LEFT_STOP:
				pEnemyUfo->m_pMover = CMoverLeftStop::Create();
				break;
			default:
				break;
			}
			//������
			pEnemyUfo->Init(pos, size, move);
			//�e�N�X�`���̎擾
			m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_ENEMY_UFO);
			//�e�N�X�`���̐ݒ�
			pEnemyUfo->BindTexture(m_pTexture);
		}
	}
	return pEnemyUfo;
}

//================================================
//�ړ��ʊǗ�����
//================================================
void CEnemyUfo::MoveType(void)
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

//================================================
//�ˌ�����
//================================================
void CEnemyUfo::ShootBullet(void)
{
	//�J�E���^�[�����Z
	m_nBulletCounter++;
	if (m_nBulletCounter >= ENEMY_UFO_SHOOT_COUNTER)
	{
		m_nBulletCounter = 0;

		//�T�E���h�擾����
		CSound *pSound;
		pSound = CManager::GetSound();

		//�e�̐���
		CBulletEnemy::Create(m_pos, D3DXVECTOR3(BULLET_ENEMY_WIDTH, BULLET_ENEMY_HEIGHT, 0.0f),
							D3DXVECTOR3(0.0f, BULLET_ENEMY_HOMING_SPEED, 0.0f), CBulletEnemy::BULLET_TYPE_HOMING, CTexture::TYPE_BULLET_SPHERE);
	}
}