#include "BAnimation.h"

BAnimation::BAnimation()
	: m_frameNum(0)
	, m_frameWidth(0)
	, m_frameHeight(0)
	, m_isLoop(false)
	, m_frameUpdateSec(0)
	, m_elapsedSec(0)
	, m_nowPlayIndex(0)
	, m_isPlay(false)
{
}

BAnimation::~BAnimation()
{
}

void BAnimation::Init(int totalW, int totalH, int frameW, int frameH)
{
	// 한프레임의 가로 크기
	m_frameWidth = frameW;
	int frameNumWidth = totalW / m_frameWidth;

	// 한프레임의 세로 크기
	m_frameHeight = frameH;
	int frameNumHeight = totalH / m_frameHeight;

	// 총 애니메이션 프레임이 몇장인지 계산
	m_frameNum = frameNumWidth * frameNumHeight;

	for (int i = 0; i < frameNumHeight; ++i)
	{
		for (int j = 0; j < frameNumWidth; ++j)
		{
			POINT framePos;

			framePos.x = j * m_frameWidth;
			framePos.y = i * m_frameHeight;

			m_frameList.push_back(framePos);
		}
	}
}

void BAnimation::Release()
{
}

void BAnimation::SetDefinePlayFrame(bool reverse, bool loop)
{
	m_playList.clear();
	m_isLoop = loop;
}

void BAnimation::SetPlayFrame(int start, int end, bool reverse, bool loop)
{
	m_isLoop = loop;
	m_playList.clear();

	if (start > end)
	{
		if (reverse)
		{
			for (int i = start; i >= end; --i)
			{
				m_playList.push_back(i);
			}
		}
		else
		{
			for (int i = end; i <= start; ++i)
			{
				m_playList.push_back(i);
			}
		}
	}
	else
	{
		if (reverse)
		{
			for (int i = end; i >= start; --i)
			{
				m_playList.push_back(i);
			}
		}
		else
		{
			for (int i = start; i <= end; ++i)
			{
				m_playList.push_back(i);
			}
		}
	}
}

void BAnimation::SetFPS(int framePerSec)
{
	m_frameUpdateSec = 1.0f / framePerSec;
}

void BAnimation::FrameUpdate(float elapsedTime)
{
	if (m_isPlay)
	{
		m_elapsedSec += elapsedTime;
		if (m_elapsedSec >= m_frameUpdateSec)
		{
			m_elapsedSec -= m_frameUpdateSec;

			m_nowPlayIndex++;
			if (m_nowPlayIndex == m_playList.size())
			{
				if (m_isLoop)
				{
					m_nowPlayIndex = 0;
				}
				else
				{
					m_nowPlayIndex--;
					m_isPlay = false;
				}
			}
		}
	}
}

void BAnimation::Start()
{
	m_isPlay = true;
	m_nowPlayIndex = 0;
}

void BAnimation::Stop()
{
	m_isPlay = false;
	m_nowPlayIndex = 0;
}

void BAnimation::Pause()
{
	m_isPlay = false;
}

void BAnimation::Resume()
{
	m_isPlay = true;
}
