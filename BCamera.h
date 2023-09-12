#ifndef BCAMERA_H
#define BCAMERA_H

#include "BBasisStd.h"

typedef struct tagCameraInfo
{
	float x;
	float y;

	int width;			// 보여질 영역 가로 크기
	int height;			// 보여질 영역 세로 크기

	int backWidth;		// 배경 이미지 가로 크기
	int backHeight;		// 배경 이미지 세로 크기
}CAMERA_INFO;

class BCamera
{
public:
	BCamera();
	~BCamera();

public:
	void Init(int width, int height, int backWidth, int backHeight);
	void Release();

	bool CheckCameraX();
	bool CheckCameraY();

	void	SetPos(float x, float y) { m_pCameraInfo->x = x; m_pCameraInfo->y = y; }

	void	SetX(float x) { m_pCameraInfo->x = x; }
	float	GetX() { return m_pCameraInfo->x; }

	void	SetY(float y) { m_pCameraInfo->y = y; }
	float	GetY() { return m_pCameraInfo->y; }

	void	SetWidth(int width) { m_pCameraInfo->width = width; }
	int		GetWidth() { return m_pCameraInfo->width; }

	void	SetHeight(int height) { m_pCameraInfo->height = height; }
	int		GetHeight() { return m_pCameraInfo->height; }

	void	SetBackWidth(int width) { m_pCameraInfo->backWidth = width; }
	int		GetBackWidth() { return m_pCameraInfo->backWidth; }

	void	SetBackHeight(int height) { m_pCameraInfo->backHeight = height; }
	int		GetBackHeight() { return m_pCameraInfo->backHeight; }

	int		GetLeft()
	{
		if (!CheckCameraX())
			return (m_pCameraInfo->x <= m_pCameraInfo->backWidth / 2) ? 0 
			: m_pCameraInfo->backWidth - m_pCameraInfo->width;
		return (int)m_pCameraInfo->x - m_pCameraInfo->width / 2;
	}

	int		GetTop()
	{
		if (!CheckCameraY())
			return (m_pCameraInfo->y <= m_pCameraInfo->backHeight / 2) ? 0
			: m_pCameraInfo->backHeight - m_pCameraInfo->height;
		return (int)m_pCameraInfo->y - m_pCameraInfo->height / 2;
	}

	RECT	GetRect()
	{
		RECT rc = { (int)m_pCameraInfo->x - m_pCameraInfo->width / 2,
					(int)m_pCameraInfo->y - m_pCameraInfo->height / 2,
					(int)m_pCameraInfo->x + m_pCameraInfo->width / 2,
					(int)m_pCameraInfo->y + m_pCameraInfo->height / 2 };
		return rc;
	}

private:
	CAMERA_INFO* m_pCameraInfo;

};

#endif // BCAMERA_H

