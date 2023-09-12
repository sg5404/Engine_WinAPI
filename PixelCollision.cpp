#include "PixelCollision.h"

PixelCollision::PixelCollision()
{
	m_Stage = STAGE::STAGE1;
	m_Player = nullptr;
	m_CurrentPixel = nullptr;
	m_CurruntMemDC = nullptr;
}

PixelCollision::~PixelCollision()
{
	if (m_CurruntMemDC)
	{
		SelectObject(m_CurruntMemDC, m_OldBitmap);
		DeleteDC(m_CurruntMemDC);
	}
}

void PixelCollision::Init()
{
	m_ImagePixel[STAGE::STAGE1].Load(TEXT("Data/BackGround/background_pixel.bmp"));
	m_ImagePixel[STAGE::STAGE2].Load(TEXT("Data/BackGround/background2_pixel.bmp"));
	m_ImagePixel[STAGE::STAGE3].Load(TEXT("Data/BackGround/background3_pixel.bmp"));
}

void PixelCollision::Update(float dt)
{
	// 주인공 픽셀 충돌
	PlayerPixelCollision();

	// 몬스터 픽셀 충돌
	MonstersPixelCollision();
}

void PixelCollision::Render(HDC hdc)
{
}

void PixelCollision::Release()
{
	m_ImagePixel[STAGE::STAGE1].Release();
	m_ImagePixel[STAGE::STAGE2].Release();
	m_ImagePixel[STAGE::STAGE3].Release();
}

void PixelCollision::SetStage(STAGE stage)
{
	if (stage < STAGE1 || stage >= STAGE_COUNT)
		return;

	m_CurrentPixel = &m_ImagePixel[stage];

	if (m_CurruntMemDC)
	{
		SelectObject(m_CurruntMemDC, m_OldBitmap);
		DeleteDC(m_CurruntMemDC);
	}

	HDC hdc = GetDC(g_pEngine->GetWndHandle());
	m_CurruntMemDC = CreateCompatibleDC(hdc);

	m_OldBitmap = (HBITMAP)SelectObject(m_CurruntMemDC, m_CurrentPixel->GetBitmapHandle());
}

void PixelCollision::PlayerPixelCollision()
{
	for (int y = m_Player->GetPos().y; y <= m_Player->GetPos().y + m_Player->GetSize().height; ++y)
	{
		for (int x = m_Player->GetPos().x; x <= m_Player->GetPos().x + m_Player->GetSize().width; ++x)
		{
			COLORREF color = GetPixel(m_CurruntMemDC, x, y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 0 && g == 255 && b == 255))
			{
				if (!m_Player->GetIsOnGround() && !m_Player->IsJumping())
				{
					m_Player->SetIsOnGround(true);
					break;
				}
			}
			else
			{
				if (!(m_Player->IsJumping() || m_Player->IsFalling()))
				{
					m_Player->SetIsOnGround(false);
				}
			}

		}
	}

	for (int y = m_Player->GetPos().y; y <= m_Player->GetPos().y + m_Player->GetSize().height/2; ++y)
	{
		int x = m_Player->IsLeft() ? m_Player->GetPos().x : m_Player->GetPos().x + m_Player->GetSize().width;

		COLORREF color = GetPixel(m_CurruntMemDC, x, y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		
		if ((r == 0 && g == 255 && b == 255))
		{
			if (m_Player->IsLeft())
				m_Player->SetCanMoveLeft(false);
			else
				m_Player->SetCanMoveRight(false);
		}
		else if ((r == 255 && g == 0 && b == 255))
		{
			break;
		}
		else
		{
			m_Player->SetCanMoveLeft(true);
			m_Player->SetCanMoveRight(true);
		}
	}



}

void PixelCollision::MonstersPixelCollision()
{
	for (size_t i = 0; i < m_Monsters->size(); ++i)
	{
		Monster* monster = m_Monsters->at(i);
		for (int y = monster->GetPos().y + monster->GetSize().height - 5; y <= monster->GetPos().y + monster->GetSize().height; ++y)
		{
			int x = monster->GetPos().x;
			COLORREF color = GetPixel(m_CurruntMemDC, x, y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 0 && g == 255 && b == 255))
			{
				monster->SetIsOnGround(true);
			}
			else
			{
				monster->SetIsOnGround(false);
			}
		}

		if (monster->GetState() == MONSTER_STATE::LEFT_MOVE || monster->GetState() == MONSTER_STATE::RIGHT_MOVE)
		{
			int y = monster->GetPos().y;
			int x = monster->IsLeft() ? monster->GetPos().x : monster->GetPos().x + monster->GetSize().width;

			COLORREF color = GetPixel(m_CurruntMemDC, x, y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 0 && g == 255 && b == 255))
			{
				monster->IsLeft() ? monster->SetCanMoveLeft(false) : monster->SetCanMoveRight(false);
			}
			else
			{
				monster->SetCanMoveLeft(true);
				monster->SetCanMoveRight(true);
			}
		}
	}
}
