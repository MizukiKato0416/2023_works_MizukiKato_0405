//===========================================
//�����̂Ȃ�UI�̏���
//Authore:��������
//===========================================
#ifndef _UI_REST_H_
#define _UI_REST_H_
#include "ui.h"

//================================================
//�}�N����`
//================================================
#define UI_REST_MENU_BAND_WIDTH					(SCREEN_WIDTH)			//���j���[��ʂ̑т̃|���S���̕�
#define UI_REST_MENU_BAND_HEIGHT				(SCREEN_HEIGHT)			//���j���[��ʂ̑т̃|���S���̍���
#define UI_REST_PAUSE_WIDTH						(SCREEN_WIDTH)			//�|�[�Y��ʂ̘g�̃|���S���̕�
#define UI_REST_PAUSE_HEIGHT					(SCREEN_HEIGHT)			//�|�[�Y��ʂ̘g�̃|���S���̍���
#define UI_REST_GAME_CLEAR_WIDTH				(1112.0f)				//GAMECLEAR�̃|���S���̕�
#define UI_REST_GAME_CLEAR_HEIGHT				(124.0f)				//GAMECLEAR�̃|���S���̍���
#define UI_REST_GAME_OVER_WIDTH					(1112.0f)				//GAMEOVER�̃|���S���̕�
#define UI_REST_GAME_OVER_HEIGHT				(124.0f)				//GAMEOVER�̃|���S���̍���
#define UI_REST_TUTORIAL_EXPLANATION_WIDTH		(1230.0f)				//�`���[�g���A���̐������̃|���S���̕�
#define UI_REST_TUTORIAL_EXPLANATION_HEIGHT		(184.0f)				//�`���[�g���A���̐������̃|���S���̍���
#define UI_REST_TUTORIAL_EXPLANATION_POS_X		(SCREEN_WIDTH / 2.0f)	//�`���[�g���A���̐������̃|���S����X���W
#define UI_REST_TUTORIAL_EXPLANATION_POS_Y		(628.0f)				//�`���[�g���A���̐������̃|���S����Y���W


//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CUiRest : public CUi
{
public:
	//�e�̎��
	typedef enum
	{
		UI_REST_TYPE_NONE = 0,
		UI_REST_TYPE_MENU_BAND,					//���j���[��ʂ̏㉺�ɂ����
		UI_REST_TYPE_PAUSE,						//�|�[�Y��ʂ̘g
		UI_REST_TYPE_DAMAGE_MASK,				//�_���[�W���󂯂��Ƃ��̃}�X�N
		UI_REST_TYPE_TUTORIAL_EXPLANATION_000,	//�`���[�g���A���̐�����
		UI_REST_TYPE_TUTORIAL_EXPLANATION_001,	//�`���[�g���A���̐�����
		UI_REST_TYPE_TUTORIAL_EXPLANATION_002,	//�`���[�g���A���̐�����
		UI_REST_TYPE_TUTORIAL_EXPLANATION_003,	//�`���[�g���A���̐�����
		UI_REST_TYPE_TUTORIAL_EXPLANATION_004,	//�`���[�g���A���̐�����
		UI_REST_TYPE_TUTORIAL_EXPLANATION_005,	//�`���[�g���A���̐�����
		UI_REST_TYPE_GAME_CLEAR,				//�Q�[���N���A
		UI_REST_TYPE_GAME_OVER,					//�Q�[���I�[�o�[
		UI_REST_TYPE_MAX
	} UI_REST_TYPE;

	CUiRest();					//�R���X�g���N�^
	~CUiRest();					//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CUiRest *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CUiRest::UI_REST_TYPE);

private:
	//�����o�֐�
	D3DXVECTOR3 m_pos;									//�|���S���̈ʒu
	D3DXVECTOR3	m_size;									//�T�C�Y
	static LPDIRECT3DTEXTURE9 m_pTexture;				//���L�e�N�X�`���̃|�C���^
	UI_REST_TYPE m_nType;								//UI�̎��
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_UI_REST_H_