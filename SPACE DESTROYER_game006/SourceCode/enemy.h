//===========================================
//�G����
//Authore:��������
//===========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "scene2D.h"
#include "mover.h"

//================================================
//�}�N����`
//================================================
#define ENEMY_DAMAGE_COUNT				(20)		//�_���[�W���󂯂Ă����Ԃ̎���
#define ENEMY_DELETE_EFFECT_IN_MAX		(6)			//�G�̗̑͂��[���ɂȂ������ɏo������̃G�t�F�N�g�̍ő吔
#define ENEMY_DELETE_EFFECT_IN_SIZE		(50.0f)		//�G�̗̑͂��[���ɂȂ������ɏo������̃G�t�F�N�g�̃T�C�Y
#define ENEMY_DELETE_EFFECT_IN_MOVE		(3.0f)		//�G�̗̑͂��[���ɂȂ������ɏo������̃G�t�F�N�g�̈ړ���
#define ENEMY_DELETE_EFFECT_OUT_MAX		(8)			//�G�̗̑͂��[���ɂȂ������ɏo��O���̃G�t�F�N�g�̍ő吔
#define ENEMY_DELETE_EFFECT_OUT_SIZE	(30.0f)		//�G�̗̑͂��[���ɂȂ������ɏo��O���̃G�t�F�N�g�̃T�C�Y
#define ENEMY_DELETE_EFFECT_OUT_MOVE	(6.0f)		//�G�̗̑͂��[���ɂȂ������ɏo��O���̃G�t�F�N�g�̈ړ���

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CEnemy : public CScene2D
{
public:
	typedef enum
	{
		ENEMY_TYPE_NONE = 0,
		ENEMY_TYPE_FIGHTER,
		ENEMY_TYPE_UFO,
		ENEMY_TYPE_SPHERE,
		ENEMY_TYPE_ITEM_POWER,
		ENEMY_TYPE_ITEM_SPEED,
		ENEMY_TYPE_MAX
	} ENEMY_TYPE;

	CEnemy(int nPriority = PRIORITY_ENEMY);				//�R���X�g���N�^
	~CEnemy();			//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move);		

protected:
	//�G�̏��
	typedef enum
	{
		ENEMY_STATE_NONE = 0,
		ENEMY_STATE_NORMAL,
		ENEMY_STATE_DAMAGE,
		ENEMY_STATE_MAX
	} ENEMY_STATE;

	static LPDIRECT3DTEXTURE9 m_pTexture;			//���L�e�N�X�`���̃|�C���^
	D3DXVECTOR3	m_size;								//�T�C�Y
	D3DXVECTOR3	m_pos;								//�ʒu
	D3DXVECTOR3 m_move;								//�|���S���̈ړ���
	int m_nCntFrame;								//�t���[�����J�E���g����ϐ�
	CMover *m_pMover;								//CMover�̃|�C���^
	CMover::MOVER_TYPE m_moverType;					//�����̎��
	int m_nLife;									//���C�t
	int m_nBulletCounter;							//�e�̐����Ԋu�J�E���g�p
	ENEMY_TYPE m_type;								//�G�̎��

private:
	//�����o�֐�
	void StateColor(void);							//��Ԃɉ������F�ɕω������鏈��
	bool Collision(void);							//�����蔻��

	ENEMY_STATE m_state;							//�G�̏��
	int m_nDamageCounter;							//�_���[�W���󂯂Ă����Ԃ̃J�E���^�[
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_ENEMY_H_