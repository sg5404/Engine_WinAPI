#include "BackGround.h"

BackGround::BackGround()
{
	m_Stage = STAGE1;
	m_Player = nullptr;
	m_CurrentBG = nullptr;

	memset(m_LoopInfo, 0, sizeof(m_LoopInfo));
	m_LoopInfo[0].Speed = 2;
	m_LoopInfo[1].Speed = 1;
	m_LoopInfo[2].Speed = 0;
	m_LoopInfo[3].Speed = 1;
}

BackGround::~BackGround()
{
}

void BackGround::Init()
{
	m_ImageBackGround[STAGE1].Load(TEXT("Data/BackGround/background.bmp"));
	m_ImageBackGround[STAGE2].Load(TEXT("Data/BackGround/background2.bmp"));
	m_ImageBackGround[STAGE3].Load(TEXT("Data/BackGround/background3.bmp"));

	m_ImageLoopBG[LOOPBG1].Load(TEXT("Data/BackGround/back1.bmp"));
	m_ImageLoopBG[LOOPBG2].Load(TEXT("Data/BackGround/back2.bmp"));
	m_ImageLoopBG[LOOPBG3].Load(TEXT("Data/BackGround/back3.bmp"));
	m_ImageLoopBG[LOOPBG4].Load(TEXT("Data/BackGround/back4.bmp"));
}

void BackGround::Update(float dt)
{
	if (g_pEngine->m_CameraObject.CheckCameraX() && m_Player && m_Player->IsMovingRight())
	{
		for (int i = LOOPBG1; i < LOOPCOUNT; ++i)
		{
			m_LoopInfo[i].PosX += m_LoopInfo[i].Speed;
		}
	}

	if (g_pEngine->m_CameraObject.CheckCameraX() && m_Player && m_Player->IsMovingLeft())
	{
		for (int i = LOOPBG1; i < LOOPCOUNT; ++i)
		{
			m_LoopInfo[i].PosX -= m_LoopInfo[i].Speed;
		}
	}
}

void BackGround::Render(HDC hdc, float dt)
{
	RECT rc = { 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT };
	for (int i = LOOPCOUNT-1; i >= LOOPBG1; --i)
	{
		m_ImageLoopBG[i].DrawLoopRender(hdc, rc, m_LoopInfo[i].PosX, 0);
	}

	if (m_CurrentBG)
		m_CurrentBG->DrawBitmap(hdc, 0, 0, 0, 0);
}

void BackGround::Release()
{
	m_ImageBackGround[STAGE1].Release();
	m_ImageBackGround[STAGE2].Release();
	m_ImageBackGround[STAGE3].Release();

	for (UINT i = LOOPBG1; i < LOOPCOUNT; ++i)
		m_ImageLoopBG[i].Release();
}

void BackGround::SetStage(STAGE stage)
{
	if (stage < 0 || stage >= STAGE_COUNT)
		return;

	m_CurrentBG = &m_ImageBackGround[stage];
}
