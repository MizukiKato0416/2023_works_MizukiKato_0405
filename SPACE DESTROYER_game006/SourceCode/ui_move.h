//===========================================
//�����̂���UI�̏���
//Authore:��������
//===========================================
#ifndef _UI_MOVE_H_
#define _UI_MOVE_H_
#include "ui.h"

//================================================
//�}�N����`
//================================================
#define UI_MENU_CIRCLE_SMALL_WIDTH					(458.0f)				//�~(��)�̃|���S���̕�
#define UI_MENU_CIRCLE_SMALL_HEIGHT					(460.0f)				//�~(��)�̃|���S���̍���
#define UI_MENU_CIRCLE_BIG_WIDTH					(594.0f)				//�~(��)�̃|���S���̕�
#define UI_MENU_CIRCLE_BIG_HEIGHT					(596.0f)				//�~(��)�̃|���S���̍���
#define UI_MENU_CIRCLE_POS_X						(239.0f)				//�~�̃|���S����X���W
#define UI_MENU_CIRCLE_POS_Y						(295.0f)				//�~�̃|���S����Y���W
#define UI_MENU_CIRCLE_INIT_POS_Y					(-295.0f)				//�~�̃|���S���̏���Y���W
#define UI_MENU_EXPLANATION_GAME_WIDTH				(402.0f)				//������(GameStart)�̃|���S���̕�
#define UI_MENU_EXPLANATION_GAME_HEIGHT				(440.0f)				//������(GameStart)�̃|���S���̍���
#define UI_MENU_EXPLANATION_TUTORIAL_WIDTH			(388.0f)				//������(Tutorial)�̃|���S���̕�
#define UI_MENU_EXPLANATION_TUTORIAL_HEIGHT			(429.0f)				//������(Tutorial)�̃|���S���̍���
#define UI_MENU_EXPLANATION_EXIT_WIDTH				(388.0f)				//������(Exit)�̃|���S���̕�
#define UI_MENU_EXPLANATION_EXIT_HEIGHT				(429.0f)				//������(Exit)�̃|���S���̍���
#define UI_MENU_EXPLANATION_TRUE_POS_X				(385.0f)				//�\������Ă�������̃|���S����X���W
#define UI_MENU_EXPLANATION_TRUE_POS_Y				(360.0f)				//�\������Ă�������̃|���S����Y���W
#define UI_MENU_EXPLANATION_FALSE_POS_X				(-385.0f)				//�\������Ă��Ȃ��������̃|���S����X���W
#define UI_MENU_EXPLANATION_FALSE_POS_Y				(360.0f)				//�\������Ă��Ȃ��������̃|���S����Y���W
#define UI_MENU_GAME_POS_Y							(360.0f)				//GameStart�̃|���S����Y���W
#define UI_MENU_TUTORIAL_POS_Y						(210.0f)				//Tutorial�̃|���S����Y���W
#define UI_MENU_EXIT_POS_Y							(520.0f)				//Exit�̃|���S����Y���W
#define UI_MENU_SELECT_TRUE_POS_X					(950.0f)				//�\������Ă���I�����̃|���S����X���W
#define UI_MENU_SELECT_FALSE_POS_X					(1847.0f)				//�\������Ă��Ȃ��I�����̃|���S����X���W
#define UI_MENU_SELECT_TRUE_WIDTH					(567.0f)				//�I������Ă���I�����̃|���S���̕�
#define UI_MENU_SELECT_TRUE_HEIGHT					(131.0f)				//�I������Ă���I�����̃|���S���̍���
#define UI_MENU_SELECT_FALSE_WIDTH					(379.0f)				//�I������Ă��Ȃ��I�����̃|���S���̕�
#define UI_MENU_SELECT_FALSE_HEIGHT					(80.0f)					//�I������Ă��Ȃ��I�����̃|���S���̍���
#define UI_MENU_FLOAT_MOVE							(0.1f)					//���V�̓����̑���
#define UI_MENU_CIRCLE_FLOAT_MOVE_REVERSE			(120)					//�~�̕��V�̓����̏㉺�𔽓]������܂ł̃J�E���g��
#define UI_MENU_EXPLANATION_FLOAT_MOVE_REVERSE		(130)					//�������̕��V�̓����̏㉺�𔽓]������܂ł̃J�E���g��
#define UI_MENU_SELECT_FLOAT_MOVE_REVERSE			(140)					//�I�����̕��V�̓����̏㉺�𔽓]������܂ł̃J�E���g��
#define UI_MENU_EXPLANATION_MOVE					(60.0f)					//�������̏o���A�ދ��̑��x
#define UI_MENU_CIRCLE_INIT_MOVE					(40.0f)					//�~���o������Ƃ��̏���
#define UI_MENU_SELECT_INIT_MOVE					(-60.0f)				//�I�������o������Ƃ��̏���
#define UI_MENU_CIRCLE_SMALL_ROTATE_MAX_SPEED		(0.08f)					//�~(��)�̍ő��]���x
#define UI_MENU_CIRCLE_BIG_ROTATE_MAX_SPEED			(0.06f)					//�~(��)�̍ő��]���x
#define UI_MENU_CIRCLE_SMALL_ADD_ROTATE_SPEED		(0.001f)				//�~(��)�̉�]���x�̏㏸�X�s�[�h
#define UI_MENU_CIRCLE_BIG_ADD_ROTATE_SPEED			(0.0005f)				//�~(��)�̉�]���x�̏㏸�X�s�[�h
#define UI_MENU_NOT_SELECT_COLOR					(0.5f)					//�I�΂�Ă��Ȃ��Ƃ��̑I�����̐F�̔Z��
#define UI_PAUSE_CONTINUE_POS_X						(640.0f)				//�|�[�Y��ʂɂ���Continue�̃|���S����X���W
#define UI_PAUSE_CONTINUE_POS_Y						(333.0f)				//�|�[�Y��ʂɂ���Continue�̃|���S����Y���W
#define UI_PAUSE_CONTINUE_WIDTH						(316.0f)				//�|�[�Y��ʂɂ���Continue�̃|���S���̕�
#define UI_PAUSE_CONTINUE_HEIGHT					(50.0f)					//�|�[�Y��ʂɂ���Continue�̃|���S���̍���
#define UI_PAUSE_EXIT_POS_X							(640.0f)				//�|�[�Y��ʂɂ���Exit�̃|���S����X���W
#define UI_PAUSE_EXIT_POS_Y							(441.0f)				//�|�[�Y��ʂɂ���Exit�̃|���S����Y���W
#define UI_PAUSE_EXIT_WIDTH							(316.0f)				//�|�[�Y��ʂɂ���Exit�̃|���S���̕�
#define UI_PAUSE_EXIT_HEIGHT						(50.0f)					//�|�[�Y��ʂɂ���Exit�̃|���S���̍���
#define UI_TITLE_INIT_POS_X							(SCREEN_WIDTH / 2.0f)	//�^�C�g���̃|���S����X���W
#define UI_TITLE_INIT_POS_Y							(-230.0f / 2.0f)		//�^�C�g���̃|���S����Y���W
#define UI_TITLE_WIDTH								(860.0f)				//�^�C�g���̃|���S���̕�
#define UI_TITLE_HEIGHT								(230.0f)				//�^�C�g���̃|���S���̍���
#define UI_TITLE_MOVE_Y								(4.0f)					//�^�C�g���̃|���S���̈ړ���
#define UI_TITLE_PRESS_START_POS_X					(SCREEN_WIDTH / 2.0f)	//PRESSSTART�̃|���S����X���W
#define UI_TITLE_PRESS_START_POS_Y					(556.0f)				//PRESSSTART�̃|���S����Y���W
#define UI_TITLE_PRESS_START_WIDTH					(298.0f)				//PRESSSTART�̃|���S���̕�
#define UI_TITLE_PRESS_START_HEIGHT					(52.0f)					//PRESSSTART�̃|���S���̍���
#define UI_TITLE_PRESS_START_BLINK_COUNT			(30)					//PRESSSTART�̓_�ł̊Ԋu
#define UI_ENEMY_KILL_SCORE_WIDTH					(50.0f * 1.2f)			//�G��|�����Ƃ��ɏo��X�R�A�̕�
#define UI_ENEMY_KILL_SCORE_HEIGHT					(14.0f * 1.2f)			//�G��|�����Ƃ��ɏo��X�R�A�̍���
#define UI_ENEMY_KILL_SCORE_COUNT					(30)					//�G��|�����Ƃ��ɏo��X�R�A�\������

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CUiMove : public CUi
{
public:
	//UI�̎��
	typedef enum
	{
		UI_MOVE_TYPE_NONE = 0,
		UI_MOVE_TYPE_TITLE,							//�^�C�g��
		UI_MOVE_TYPE_PRESS_START,					//press�X�^�[�g��UI
		UI_MOVE_TYPE_MENU_CIRCLE_SMALL,				//���j���[��ʂɂ���~(��)
		UI_MOVE_TYPE_MENU_CIRCLE_BIG,				//���j���[��ʂɂ���~(��)
		UI_MOVE_TYPE_MENU_EXPLANATION_GAME,			//���j���[��ʂɂ��������(GameStart)
		UI_MOVE_TYPE_MENU_EXPLANATION_TUTORIAL,		//���j���[��ʂɂ��������(Tutorial)
		UI_MOVE_TYPE_MENU_EXPLANATION_EXIT,			//���j���[��ʂɂ��������(Exit)
		UI_MOVE_TYPE_MENU_GAME_START,				//���j���[��ʂɂ���GameStart
		UI_MOVE_TYPE_MENU_TUTORIAL,					//���j���[��ʂɂ���Tutorial
		UI_MOVE_TYPE_MENU_EXIT,						//���j���[��ʂɂ���Exit
		UI_MOVE_TYPE_PAUSE_EXIT,					//�|�[�Y��ʂɂ���Exit
		UI_MOVE_TYPE_PAUSE_CONTINUE,				//�|�[�Y��ʂɂ���Continue
		UI_MOVE_TYPE_ENEMY_KILL_SCORE_100,			//�G��|�����Ƃ��ɏo��X�R�A
		UI_MOVE_TYPE_ENEMY_KILL_SCORE_200,			//�G��|�����Ƃ��ɏo��X�R�A
		UI_MOVE_TYPE_ENEMY_KILL_SCORE_400,			//�G��|�����Ƃ��ɏo��X�R�A
		UI_MOVE_TYPE_MAX
	} UI_MOVE_TYPE;

	CUiMove();				//�R���X�g���N�^
	~CUiMove();				//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CUiMove *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, CUiMove::UI_MOVE_TYPE);

private:
	//�����o�֐�
	void TitleUi(void);		//�^�C�g���Ɏg��Ui�̏���
	void MenuUi(void);		//���j���[�Ɏg��Ui�̏���
	void TutorialUi(void);	//�`���[�g���A���Ɏg��Ui�̏���
	bool GameUi(void);		//�Q�[�����Ɏg��Ui�̏���
	void ResultUi(void);	//���U���g�Ɏg��Ui�̏���
	void FloatMove(void);	//���V�̓����̏���

	D3DXVECTOR3 m_pos;									//�|���S���̈ʒu
	D3DXVECTOR3	m_size;									//�T�C�Y
	D3DXVECTOR3	m_move;									//�ړ���
	static LPDIRECT3DTEXTURE9 m_pTexture;				//���L�e�N�X�`���̃|�C���^
	UI_MOVE_TYPE m_nType;								//UI�̎��
	bool m_bFloatMove;									//���V���Ă��邩���Ă��Ȃ����̃t���O
	float m_fRot;										//�|���S������]�����邽�߂̊p�x
	D3DXVECTOR3 m_vertex[VERTEX_NUM];					//�|���S����4���_�̈ʒu
	float m_fTanR;										//���_���璸�_�܂ł̊p�x
	float m_fCircleR;									//��]������|���S����4���_�̉~�O���̔��a
	float m_fRotateSpeed;								//��]�����鑬�x
	bool m_bRotateReverse;								//�t��]��Ԃ��ǂ���false�ŋt��]
	int m_nBlinkCounter;								//�_�ł����邽�߂̃J�E���^�[
	bool m_bBlink;										//�_�ł̏��
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_UI_MOVE_H_