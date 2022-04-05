//===========================================
//�`���[�g���A������
//Authore:��������
//===========================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
#include "scene.h"
#include "scene2D.h"
#include "main.h"

//�O���錾
class CUi;
class CEnemyItemPower;
class CEnemyItemSpeed;
class CPlayer;

//================================================
//�}�N����`
//================================================
#define MAX_TUTORIAL_UI						(4)								//�`���[�g���A�����Ɉ�x�ɏo��UI�̍ő吔
#define TUTORIAL_NEXT_PHASE_COUNTER			(120)							//���̃t�F�[�Y�ɐi�ނ��Ƃ��ł���܂ł̎���
#define MAX_PLAYER_CONTROL_KEY				(4)								//�v���C���[�𓮂����L�[�̐�
#define TUTORIAL_ENEMY_POS_X				(SCREEN_WIDTH / 2.0f)			//�G���o��X���W
#define TUTORIAL_ENEMY_POS_Y				(100.0f)						//�G���o��Y���W
#define TUTORIAL_ENEMY_ITEM_POWER_POS_X		(SCREEN_WIDTH / 3.0f)			//�p���[�A�b�v�A�C�e���𐶐�����G���o��X���W
#define TUTORIAL_ENEMY_ITEM_POWER_POS_Y		(100.0f)						//�p���[�A�b�v�A�C�e���𐶐�����G���o��Y���W
#define TUTORIAL_ENEMY_ITEM_SPEED_POS_X		(SCREEN_WIDTH / 3.0f * 2.0f)	//�X�s�[�h�A�b�v�A�C�e���𐶐�����G���o��X���W
#define TUTORIAL_ENEMY_ITEM_SPEED_POS_Y		(100.0f)						//�X�s�[�h�A�b�v�A�C�e���𐶐�����G���o��Y���W
#define TUTORIAL_PLAYER_POS_X				(SCREEN_WIDTH / 2.0f)			//�v���C���[���o��X���W
#define TUTORIAL_PLAYER_POS_Y				(400.0f)						//�v���C���[���o��Y���W
#define MAX_TUTORIL_PAUSE_UI				(3)								//�|�[�Y����UI�̐�

//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CTutorial : public CScene
{
public:
	//�`���[�g���A���̃t�F�[�Y
	typedef enum 
	{
		TUTORIAL_PHASE_NONE = 0,
		TUTORIAL_PHASE_FIRST_EXPLANATION,				//���߂̐���
		TUTORIAL_PHASE_PLAYER_CONTROL_EXPLANATION,		//�v���C���[�̈ړ��������
		TUTORIAL_PHASE_PLAYER_CONTROL,					//�v���C���[�̈ړ�����
		TUTORIAL_PHASE_PLAYER_SHOOT_EXPLANATION,		//�v���C���[�̎ˌ��������
		TUTORIAL_PHASE_PLAYER_SHOOT,					//�v���C���[�̎ˌ�����
		TUTORIAL_PHASE_ITEM_EXPLANATION_000,			//�A�C�e���̐���000
		TUTORIAL_PHASE_ITEM_EXPLANATION_001,			//�A�C�e���̐���001
		TUTORIAL_PHASE_PLAYER_LEVEL_UP_SHOOT,			//���x���A�b�v�����v���C���[�̎ˌ�����
		TUTORIAL_PHASE_FINISH,							//�I��
		TUTORIAL_PHASE_MAX,								//�t�F�[�Y�̍ő�l
	} TUTORIAL_PHASE;

	//�I����
	typedef enum
	{
		SELECT_TUTORIAL_PAUSE_TYPE_NONE = 0,
		SELECT_TUTORIAL_PAUSE_TYPE_CONTINUE,		//Coutinue
		SELECT_TUTORIAL_PAUSE_TYPE_EXIT,			//Exit
		SELECT_TUTORIAL_PAUSE_TYPE_MAX			//�I�����ő�l
	} SELECT_TUTORIAL_PAUSE_TYPE;

	CTutorial();				//�R���X�g���N�^
	~CTutorial();				//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetEnemyKill(bool bEnemyKill);		//�G��|�����̂�ݒ肷�鏈��
	static void SetPowerUp(bool bPowerUp);			//�p���[�A�b�v�����̂��̂�ݒ肷�鏈��
	static void SetSpeedUp(bool bSpeedUp);			//�X�s�[�h�A�b�v�����̂�ݒ肷�鏈��
	static bool GetPause(void);						//�|�[�Y�擾����
	static int GetSelect(void);						//�|�[�Y���̑I�����擾����
	TUTORIAL_PHASE GetPhase(void);					//�t�F�[�Y�擾����
	void Pause(void);								//�|�[�Y�Ɋւ��鏈��
	
private:
	//�����o�֐�
	void phase(void);								//�t�F�[�Y���Ƃ̏���

	CScene2D *m_pScene2D;							//scene2D�̃|�C���^
	TUTORIAL_PHASE m_phase;							//�t�F�[�Y
	CUi *m_pUi[MAX_TUTORIAL_UI];					//UI�̃|�C���^
	CEnemyItemPower *m_pEnemyItemPower;				//EnemyItemPower�̃|�C���^
	CEnemyItemSpeed *m_pEnemyItemSpeed;				//EnemyItemSpeed�̃|�C���^
	CPlayer *m_pPlayer;								//Player�̃|�C���^
	int m_nNextPhaseCounter;						//���̃t�F�[�Y�ɍs����悤�ɂȂ�܂ł̃J�E���^�[
	bool m_bPlayerMove[MAX_PLAYER_CONTROL_KEY];		//�v���C���[�̈ړ����ł������ǂ����̃t���O
	bool m_bPlayerShoot;							//�v���C���[�̎ˌ����ł������ǂ����̃t���O
	static bool m_bEnemyKill;						//�G��|�������ǂ���
	static bool m_bPowerUp;							//�p���[�A�b�v���������ǂ���
	static bool m_bSpeedUp;							//�X�s�[�h�A�b�v���������ǂ���
	static int m_nSelect;							//�ǂ̑I�������I������Ă��邩
	static bool m_bPause;							//�|�[�Y�����ǂ����̃t���O
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_TUTORIAL_H_