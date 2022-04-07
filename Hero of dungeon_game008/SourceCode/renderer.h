//===========================================
//�`�揈��
//Author:KatoMizuki
//===========================================
#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "main.h"

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CRenderer
{
public:
	CRenderer();			//�R���X�g���N�^
	~CRenderer();			//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }

private:
#ifdef _DEBUG
	void DrawFPS(void);
	void DrawFrame(void);
#endif //!_DEBUG

	LPDIRECT3D9				m_pD3D;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Device�I�u�W�F�N�g(�`��ɕK�v)
	
#ifdef _DEBUG
	LPD3DXFONT				m_pFont;		// �t�H���g�ւ̃|�C���^
#endif //!_DEBUG
};

#endif // !_RENDERER_H_